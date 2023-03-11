import os
import sys
import numpy as np
import matplotlib.pyplot as plt

filename = ["data_file.txt"]

no_of_pages_in_a_file = 512
no_of_bytes_in_a_page = 18592
no_of_time_instances = 41

time_increment = 10

for this_file_name in filename:
	if not os.path.isfile(this_file_name):
		print(f"E: File {this_file_name} not found..")
		continue

	print(f"I: File {this_file_name} found..")

	# let us read the complete file in one gulp
	complete_data_overall = np.fromfile(this_file_name,dtype = np.uint8).reshape((1,-1))
	print(f"I: Expected no of bytes is {no_of_pages_in_a_file*(no_of_bytes_in_a_page+1)*no_of_time_instances}, got {complete_data_overall.size}")

	if no_of_pages_in_a_file*(no_of_bytes_in_a_page+1)*no_of_time_instances != complete_data_overall.size:
		print(f"E: Expected vs Got mismatch Error!!!!")
		continue

	output_dir = this_file_name.split(".")[0]
	if not os.path.isdir(output_dir):
		os.mkdir(output_dir)

	for each_time in range(no_of_time_instances):

		complete_data = complete_data_overall[:,no_of_pages_in_a_file*(no_of_bytes_in_a_page+1)*each_time:no_of_pages_in_a_file*(no_of_bytes_in_a_page+1)*(each_time+1)]

		# now we have to unpack the data bytes
		complete_data_reshaped = np.reshape(complete_data,(no_of_pages_in_a_file,complete_data.size//no_of_pages_in_a_file))
		complete_data_unpacked = np.unpackbits(complete_data_reshaped[:,:-1],axis=-1)
		print(f"I: Data unpacked to {complete_data_unpacked.shape}")

		print(f"I: writing data for Time index :{each_time}")

		f_out = open(os.path.join(output_dir,"slc_partialprogram_data_"+str(each_time*time_increment)+"us.csv"),"w")
		f_out.write("Page No,Erased Cells,Programmed Cells")

		for each_page in range(no_of_pages_in_a_file):
			ones_position = complete_data_unpacked[each_page,:]==1
			ones_count = len(complete_data_unpacked[each_page,:][ones_position])

			zeros_position = complete_data_unpacked[each_page,:]==0
			zeros_count = len(complete_data_unpacked[each_page,:][zeros_position])

			print(f"Page: {each_page}, E(1) = {ones_count}, P(0) = {zeros_count}")
			f_out.write(f"\n{each_page},{ones_count},{zeros_count}")
		f_out.close()

	for each_page in range(no_of_pages_in_a_file):
		f_out = open(os.path.join(output_dir,f"slc_partialprogram_data_page{each_page}.csv"),"w")
		f_out.write(f"time,erased,programmed")
		for each_time in range(1,no_of_time_instances):
			with open(os.path.join(output_dir,"slc_partialprogram_data_"+str(each_time*time_increment)+"us.csv"),"r") as f_in:
				data_for_this_page_time = f_in.read().split("\n")[each_page+1].split(",")
				f_out.write("\n"+str(each_time*time_increment)+","+data_for_this_page_time[1]+","+data_for_this_page_time[2])
		f_out.close()
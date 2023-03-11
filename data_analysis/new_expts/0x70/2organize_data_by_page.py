import os
import sys
import os.path
import numpy as np
import matplotlib.pyplot as plt

filename = ["1data_file.txt"]

no_of_pages_in_a_file = 100
no_of_bytes_in_a_page = 18592
no_of_reads = 16

# let us create a large numpy array that will hold data for each page
page_data = np.zeros((no_of_pages_in_a_file,no_of_reads,no_of_bytes_in_a_page*8))

for this_file_name in filename:
	if not os.path.isfile(this_file_name):
		print(f"E: File {this_file_name} not found..")
		continue

	print(f"I: File {this_file_name} found..")

	# let us read the complete file in one gulp
	complete_data_overall = np.fromfile(this_file_name,dtype = np.uint8).reshape((1,-1))
	print(f"I: Expected no of bytes is {no_of_pages_in_a_file*(no_of_bytes_in_a_page+1)*no_of_reads}, got {complete_data_overall.size}")

	if no_of_pages_in_a_file*(no_of_bytes_in_a_page+1)*no_of_reads != complete_data_overall.size:
		print(f"E: Expected vs Got mismatch Error!!!!")
		continue

	for each_read in range(no_of_reads):

		# this is the data for this particular time, for all pages
		complete_data = complete_data_overall[:,no_of_pages_in_a_file*(no_of_bytes_in_a_page+1)*each_read:no_of_pages_in_a_file*(no_of_bytes_in_a_page+1)*(each_read+1)]

		# now we have to unpack the data bytes
		complete_data_reshaped = np.reshape(complete_data,(no_of_pages_in_a_file,complete_data.size//no_of_pages_in_a_file))
		complete_data_unpacked = np.unpackbits(complete_data_reshaped[:,:-1],axis=-1)
		print(f"I: Data unpacked to {complete_data_unpacked.shape} @ReadRetry:{each_read}")

		for each_page in range(no_of_pages_in_a_file):
			page_data[each_page,each_read] = complete_data_unpacked[each_page]

	# now writing time
	folder1_name = this_file_name.split(".")[0]
	if not os.path.exists(folder1_name):
		os.makedirs(folder1_name)

	for each_page in range(no_of_pages_in_a_file):
		out_csv_name = os.path.join(folder1_name,str(each_page)+".csv")
		np.savetxt(out_csv_name,page_data[each_page],fmt='%1d',delimiter=",")

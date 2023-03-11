import os
import sys
import numpy as np
import matplotlib.pyplot as plt 

# file_name = ['data_file_45000.txt','data_file_55000.txt','data_file_57500.txt','data_file_60000.txt','data_file_62500.txt','data_file_65000.txt','data_file_67500.txt','data_file_70000.txt','data_file_75000.txt','data_file_complete.txt']
# x_axis = [45,55,57.5,60,62.5,65,67.5,70,75,90]

file_name = ['data_file_complete.txt']#,'data_file_30000.txt','data_file_35000.txt','data_file_40000.txt','data_file_45000.txt','data_file_75000.txt','data_file_85000.txt','data_file_95000.txt','data_file_105000.txt','data_file_complete.txt']
x_axis = [25,30,35,40,45,75,85,95,105,115]
num_pages = 100


zeros = [list() for i in range(num_pages)]
ones = [list() for i in range(num_pages)]

for idx,f_name in enumerate(file_name):
	print(f"I: Opening file {f_name}")

	if not os.path.isfile(f_name):
		print(f"E: File {f_name} not found")
		continue

	total_data = np.fromfile(f_name,dtype = np.uint8).reshape((1,-1))
	print(f"I: .. Total Data obtained is {total_data.shape}")

	total_data_reshaped = total_data.reshape((num_pages,total_data.size//num_pages))
	print(f"I: .. data reshaped to {total_data_reshaped.shape}")

	total_data_unpacked = np.unpackbits(total_data_reshaped[:,:-1],axis=1)
	print(f"I: .. data unpacked into {total_data_unpacked.shape}")

	for each_page in range(num_pages):
		zeros[each_page].append(len(total_data_unpacked[each_page,:][total_data_unpacked[each_page,:]==0]))
		ones[each_page].append(len(total_data_unpacked[each_page,:][total_data_unpacked[each_page,:]==1]))
		print(f"I: .. .. Page {each_page}, 0s: {zeros[each_page][-1]} and 1s: {ones[each_page][-1]}")

# # # # let us iterate through each page available
# for page_num in range(num_pages):
# 	print(f"I: Plotting for page number {page_num}")

# 	plt.plot(x_axis,zeros[page_num],'b', label = "Programmed Cells (0)")
# 	plt.plot(x_axis,ones[page_num],'r', label="Erased Cells (1)")

# 	plt.xlabel("Microseconds")
# 	plt.ylabel("No of flash cells")

# 	plt.legend()

# 	plt.savefig("Page No "+str(page_num)+".jpg",bbox_inches = "tight")
# 	plt.close('all')
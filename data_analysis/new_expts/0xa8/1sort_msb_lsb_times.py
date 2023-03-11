import numpy as np

infile = "all_time_file.txt"

with open(infile,'r') as inf:

	page_indices = set()

	# read the entire file in a big gulp
	f_data = inf.read();
	# let us split based on new line character
	f_data_split = f_data.strip().split("\n")
	print(f"The read data is of {len(f_data_split)} size")

	# let us grab the time from the file
	only_times = list()
	for each_line in f_data_split:
		only_times.append(int(each_line.split()[3]))
		# print(f" Pushing {each_line.split()[3]} to array")

	unshared_page_times = list()
	unshared_page_indices = list()
	unshared_page_times_file = infile.split(".")[0]+"_unsharedwithIndices.txt"

	LSB_page_times = list()
	LSB_page_indices = list()
	LSB_page_times_file = infile.split(".")[0]+"_LSBwithIndices.txt"

	MSB_page_times = list()
	MSB_page_indices = list()
	MSB_page_times_file = infile.split(".")[0]+"_MSBwithIndices.txt"

	# 0 to 31 is unshared
	for i in range(32):
		page_indices.add(i)
		print(f" Appending page {i} to unshared page data")
		unshared_page_times.append(only_times[i])
		unshared_page_indices.append(i)
	# 961 to 1023 are unshared with incr of 2
	for i in range(961,1024,2):
		page_indices.add(i)
		print(f" Appending page {i} to unshared page data")
		unshared_page_times.append(only_times[i])
		unshared_page_indices.append(i)

	unshared_page_times_arr = np.asarray(unshared_page_times)
	unshared_page_indices_arr = np.asarray(unshared_page_indices)
	unshared_page_times_arr = unshared_page_times_arr.reshape((unshared_page_times_arr.size,1))
	unshared_page_indices_arr = unshared_page_indices_arr.reshape((unshared_page_indices_arr.size,1))
	np.savetxt(unshared_page_times_file,np.concatenate((unshared_page_indices_arr, unshared_page_times_arr), axis=1),fmt='%8d')

	# let us take the LSB pages
	for i in range(32,64,1):
		page_indices.add(i)
		page_indices.add(2*i)
		print(f" Appending page {i} to LSB page data")
		LSB_page_times.append(only_times[i])
		LSB_page_indices.append(i)
		print(f" Appending page {2*i} to MSB page data")
		MSB_page_times.append(only_times[2*i])
		MSB_page_indices.append(2*i)

	for i in range(65,1000,2):
		if i in page_indices:
			continue
		page_indices.add(i)
		page_indices.add(i+63)
		print(f" Appending page {i} to LSB page data")
		LSB_page_times.append(only_times[i])
		LSB_page_indices.append(i)
		print(f" Appending page {i+63} to MSB page data")
		MSB_page_times.append(only_times[i+63])		
		MSB_page_indices.append(i+63)

	LSB_page_times_arr = np.asarray(LSB_page_times)
	LSB_page_indices_arr = np.asarray(LSB_page_indices)
	LSB_page_times_arr = LSB_page_times_arr.reshape((LSB_page_times_arr.size,1))
	LSB_page_indices_arr = LSB_page_indices_arr.reshape((LSB_page_indices_arr.size,1))
	np.savetxt(LSB_page_times_file,np.concatenate((LSB_page_indices_arr, LSB_page_times_arr), axis=1),fmt='%8d')

	MSB_page_times_arr = np.asarray(MSB_page_times)
	MSB_page_indices_arr = np.asarray(MSB_page_indices)
	MSB_page_times_arr = MSB_page_times_arr.reshape((MSB_page_times_arr.size,1))
	MSB_page_indices_arr = MSB_page_indices_arr.reshape((MSB_page_indices_arr.size,1))
	np.savetxt(MSB_page_times_file,np.concatenate((MSB_page_indices_arr, MSB_page_times_arr), axis=1),fmt='%8d')

	for i in range(1024):
		if i in page_indices:
			continue
		print(f"Page {i} not found")
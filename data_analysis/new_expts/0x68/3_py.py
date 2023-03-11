infile = '9time_file_ed.txt'

indices = [0,2,4,6,8,10,12,14,16,18,
						
						32, 34, 36, 38, 40, 42, 44, 46, 48, 50,
						64, 68, 72, 76, 80, 84, 88, 92, 96, 100,
						
						105, 113, 121, 129, 137, 145, 153, 161, 169, 177,
						168, 176, 184, 192, 200, 208, 216, 224, 232, 240,
						
						601, 609, 617, 625, 633, 641, 649, 657, 665, 673,
						664, 672, 680, 688, 696, 704, 712, 720, 728, 736,
						
						941, 943, 945, 947, 949, 951, 953, 955, 957, 959,
						1004, 1006, 1008, 1010, 1012, 1014, 1016, 1018, 1020, 1022,
						
						1003, 1005, 1009, 1011, 1013, 1015, 1017, 1019, 1021, 1023]
with open(infile,'r') as fin:
	complete_text = fin.read()

	complete_text_ed = complete_text.strip().split()

	my_op_list = list()
	for each_index in indices:
		my_op_list.append(complete_text_ed[complete_text_ed.index(str(each_index))-1])

	f_out = open(infile.split('.')[0]+'ed.csv','w')
	for each_item in my_op_list:
		f_out.write(f"{each_item},")
	f_out.close()
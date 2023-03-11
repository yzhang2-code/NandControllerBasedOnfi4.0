/*
This file is supposed to provide help. This means it will contain API calls that are designed into
this project. Any user can make call to APIs using the example presented below
*/

/*****************************************************************/
/****** Addresses used up in Micron MLC 3D NAND *****************/
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x2c,0x0};	// this will be used for SLC mode using slc function other than set feature
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x24,0x0};	// this is also SLC block that will be analyzed for partial program operations
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x38,0x0};	// this is also SLC block that will be analyzed for partial erase operations
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x44,0x0};	// this is also SLC block that will be analyzed for partial erase operations
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x48,0x0};	// this is also SLC block that will be analyzed for partial program operations
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x50,0x0};	// this is also SLC block that will be analyzed for partial program operations
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x58,0x0};	// this is also SLC block that will be analyzed for partial program operations
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x60,0x0};	// this is also SLC block that will be analyzed for partial program operations
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x4c,0x0};	// this is also SLC block that will be analyzed for partial erase operations
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x54,0x0};	// this is also SLC block that will be analyzed for partial erase operations
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x5c,0x0};	// this is also SLC block that will be analyzed for partial erase operations
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x64,0x0};	// SLC/MLC thing
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x68,0x0};	//MLC characteristics repeatedly
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x6c,0x0};	//MLC characteristics repeatedly
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x70,0x0};	//read retry operation
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x74,0x0};	//read retry operation
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x78,0x0};	//program time explore
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x7C,0x0};	//program time explore
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x80,0x0};	//program time explore
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x84,0x0};	//program disturb explore, failed move to next
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x8C,0x0};	//program disturb explore, took too long moved to 88
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x88,0x0};	//program disturb explore, did only 5 instances
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x90,0x0};	//program disturb explore, did only 5 instances
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x94,0x0};	//program disturb explore, did only 5 instances, do only a single page and see so aborted
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x98,0x0};	//program disturb explore, did only 5 instances, do only a single page and see so aborted
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x9C,0x0};	//program time depends on data being programmed, all 5 kinds of data
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0xA0,0x0};	//program time depends on data being programmed, with 0xff
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0xA4,0x0};	//program time depends on data being programmed, with 0x00 at last 32 bytes
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0xA0,0x0};	//testing program time hypo for sybblock
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x00,0x0};	//just checking
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0xAC,0x0};	//convert to SLC and see data dependent program
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0xB0,0x0};	//convert to SLC and see data dependent program

	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0xB4,0x0};	// Error: PUF partial program analysis
	// uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0xB8,0x0};	// PUF partial program analysis
	uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0xBC,0x0};	// SLC->MLC
/****************************************************************/
// must do this before anything
// .. onfi_instance is an object of onfi_interface
onfi_instance.initialize_onfi();

// now that the object is created
// .. the object should go and initialize itself by looking at the addresses and map to them
// .. let us test if the LEDs test will succeed
onfi_instance.test_onfi_leds();

//for the NAND chip, let us initialize the chip
// .. this should follow a pattern of power cycle as mentioned in the datasheet
//.. then we will do a reset operation
onfi_instance.device_initialization();

//now let test the NAND chip and print its properties as read from the chip memory itself
// .. please make sure that the pin connections is appropriate as mentioned in hardware_locations.h
// .. this function call is also important to establish the parameters like:
// .. num_bytes_in_page, num_spare_bytes_in_page and num_pages_in_block
onfi_instance.read_ONFI_parameters(true);

// test if the block is bad block
onfi_instance.is_bad_block(my_test_block_address)

// let us erase the block and test if all the bytes in the block is erased or not
//.. send the address from R1 and onwards, thus +2
onfi_instance.erase_block(my_test_block_address+2,true);

// now let us verify if the erase operation was completed
// .. this function will read any random page and tries to verify if it was completely erased
// .. for elaborate verifiying, please use a different function
onfi_instance.verify_block_erase(my_test_block_address);

// program a single page
onfi_instance.program_page(my_test_block_address,data_to_program,true,true);

// this function verifies program operation in a single page
onfi_instance.verify_program_page(my_test_block_address,data_to_program);

// let us read the data from a single page
// .. here the first page of the block
// .. this will log the data into the file data_file.txt
onfi_instance.read_and_spit_page(my_test_block_address,true);

// let us program pages in the block with all 0s
// the paramters are:
// .. my_test_block_address is the address of the block (starting address)
// .. complete_block if this is true all the pages in the block will be programmed
// .. page_indices is an array of indices inside the block that we want to program
// .. num_pages is the number of pages in the page_indices array
// .. verbose is for printing
onfi_instance.program_pages_in_a_block(my_test_block_address);

// let us verify program pages in the block 
// the paramters are:
// .. my_test_block_address is the address of the block (starting address)
// .. complete_block if this is true all the pages in the block will be verified
// .. page_indices is an array of indices inside the block that we want to verify
// .. num_pages is the number of pages in the page_indices array
// .. verbose is for printing
onfi_instance.verify_program_pages_in_a_block(my_test_block_address);

// let us read the block
// .. this function will now just read the pages selected
// .. data will be logged into data_file.txt
onfi_instance.read_block_data(my_test_block_address);


// just an array initialized to random values
uint8_t features_parameters[4] = {12,34,56,43};
// let us read the timing mode parameters
// .. 0x91 reads the SLC/MLC thing
onfi_instance.get_features(0x91,features_parameters);
cout<<"Feature parameters (SLC/MLC) read are "<<endl;
cout<<"\t:"<<(int)features_parameters[0]<<","<<(int)features_parameters[1]<<","<<(int)features_parameters[2]<<","<<(int)features_parameters[3]<<endl;

// this function will convert the configuration of the block to SLC mode
// .. the initialization erase is performed inside the function itself
onfi_instance.convert_to_slc_set_features(my_test_block_address);

// let us program 512 pages in the block with all 0s
// the paramters are:
// .. my_test_block_address is the address of the block (starting address)
// .. num_pages is the number of pages in the page_indices array
// .. verbose is for printing
onfi_instance.program_pages_in_a_block_slc(my_test_block_address);

// this section is to profile the new delay function
// .. make sure to have PROFILE_DELAY_TIME as true if profiling
uint32_t delay = 20000;
for(;delay<125000;delay+=10000)
	onfi_instance.delay_function(delay);


/****************************************************************************************
*************** Page Program Time SLC *****************************************************
*****************************************************************************************/
	// let us create an array with some arbitrary numbers to program the pages in a block
	// .. the selected pages will be programmed with its own index in a block
	// .. all the bytes will have the same data
	onfi_instance.erase_block(my_test_block_address+2);
	uint8_t local_address[5];
	for(uint8_t i = 0;i<5;i++)
		local_address[i] = my_test_block_address[i];

	for(int a = 0;a<20;a++)
	{
		uint16_t this_page_index = slc_page_indices[a];

		uint8_t* my_data_to_write = new uint8_t[onfi_instance.num_spare_bytes_in_page+onfi_instance.num_bytes_in_page];
		for(uint16_t byte_idx = 0; byte_idx < (onfi_instance.num_spare_bytes_in_page+onfi_instance.num_bytes_in_page);byte_idx++)
		{
			my_data_to_write[byte_idx] = (uint8_t)(this_page_index%256);
		}

		// now let us update the address based on this index
		local_address[2] = this_page_index%256;
		local_address[3] = (my_test_block_address[3])|((uint8_t)(0x03&(this_page_index/256)));

		cout<<"Writing "<<std::hex<<(int)my_data_to_write[0]<<" to page "<<std::hex<<(int)local_address[0]<<","<<std::hex<<(int)local_address[1]<<","<<std::hex<<(int)local_address[2]<<","<<std::hex<<(int)local_address[3]<<","<<std::hex<<(int)local_address[4]<<endl;

		onfi_instance.program_page(local_address,my_data_to_write,true,false);

		delete[] my_data_to_write;
	}

/****************************************************************************************
*************** Page Read Time SLC*****************************************************
*****************************************************************************************/
	// let us create an array with some arbitrary numbers to verify the pages in a block
	// .. the selected pages has been programmed with its own index in a block
	// .. all the bytes should have the same data
	uint8_t local_address[5];
	for(uint8_t i = 0;i<5;i++)
		local_address[i] = my_test_block_address[i];

	for(int a = 0;a<20;a++)
	{
		uint16_t this_page_index = slc_page_indices[a];

		uint8_t* my_data_to_write = new uint8_t[onfi_instance.num_spare_bytes_in_page+onfi_instance.num_bytes_in_page];
		for(uint16_t byte_idx = 0; byte_idx < (onfi_instance.num_spare_bytes_in_page+onfi_instance.num_bytes_in_page);byte_idx++)
		{
			my_data_to_write[byte_idx] = (uint8_t)(this_page_index%256);
		}

		// now let us update the address based on this index
		local_address[2] = this_page_index%256;
		local_address[3] = (my_test_block_address[3])|((uint8_t)(0x03&(this_page_index/256)));

		cout<<"Checking "<<std::hex<<(int)my_data_to_write[0]<<" to page "<<std::hex<<(int)local_address[0]<<","<<std::hex<<(int)local_address[1]<<","<<std::hex<<(int)local_address[2]<<","<<std::hex<<(int)local_address[3]<<","<<std::hex<<(int)local_address[4]<<endl;

		onfi_instance.verify_program_page(local_address,my_data_to_write);

		delete[] my_data_to_write;
	}
/****************************************************************************************/

/****************************************************************************************
*************** Partial Erase MLC *****************************************************
*****************************************************************************************/
	// following can be used for MLC partial erase profiling
	for(uint32_t delay_in_us = 006;delay_in_us <= 15006;delay_in_us+= 100)
	{
		//.. first erase the complete block
		onfi_instance.erase_block(my_test_block_address+2);
		onfi_instance.delay_function(50000); // of nearly us
		// .. then verify erase operation
		// onfi_instance.verify_block_erase(my_test_block_address,false,slc_page_indices,20);
		// .. then program the pages of interest
		onfi_instance.program_pages_in_a_block(my_test_block_address);
		// let us just put a delay here for some time
		onfi_instance.delay_function(50000); // of nearly us
		// .. verify the program operation
		// onfi_instance.verify_program_pages_in_a_block(my_test_block_address,false,slc_page_indices,20);
		// .. now let us partial erase the page
		onfi_instance.partial_erase_block(my_test_block_address+2,uint32_t(((1000*delay_in_us)-5298)/15));
		onfi_instance.delay_function(50000); // of nearly us
		onfi_instance.read_block_data(my_test_block_address);
	}
/****************************************************************************************/

/****************************************************************************************
*************** Partial Program SLC *****************************************************
*****************************************************************************************/
	// following can be used for partial program routine of 512 pages
	// let us perform partial program analysis of the following
	// .. let us create an array with indices to program pages
	uint16_t num_slc_pages = 512;
	uint16_t* slc_pages = new uint16_t[num_slc_pages];
	for(uint16_t idx_page = 0;idx_page<num_slc_pages;idx_page++)
		slc_pages[idx_page] = idx_page;

	for(uint32_t delay_in_us = 006;delay_in_us <= 1506;delay_in_us+= 25)
	{
		//.. first erase the complete block
		onfi_instance.erase_block(my_test_block_address+2);
		onfi_instance.delay_function(50000); // of nearly 500 us
		// .. then verify erase operation
		// onfi_instance.verify_block_erase(my_test_block_address,false,slc_page_indices,20);
		// .. then program the pages of interest
		onfi_instance.partial_program_pages_in_a_block(my_test_block_address,uint32_t(((1000*delay_in_us)-5298)/15),false,slc_pages,num_slc_pages);
		onfi_instance.delay_function(50000); // of nearly 500 us
		onfi_instance.read_block_data(my_test_block_address,false,slc_pages,num_slc_pages);
	}
	delete[] slc_pages;
/****************************************************************************************/

/****************************************************************************************
*************** Partial Erase SLC *****************************************************
*****************************************************************************************/
	uint16_t num_slc_pages = 100;
	uint16_t* slc_pages = new uint16_t[num_slc_pages];
	uint16_t idx = 0;
	for(uint16_t idx_page = 0;idx_page<5;idx_page++)
	{
		for(uint16_t inn_idx = 0;inn_idx<20;inn_idx++)
		{
			slc_pages[idx] = idx_page*100+inn_idx;
			idx++;
		}
	}
	// following can be used for MLC partial erase profiling
	for(uint32_t delay_in_us = 006;delay_in_us <= 15006;delay_in_us+= 100)
	{
		//.. first erase the complete block
		onfi_instance.erase_block(my_test_block_address+2);
		onfi_instance.delay_function(50000); // of nearly us
		// .. then verify erase operation
		// onfi_instance.verify_block_erase(my_test_block_address,false,slc_page_indices,20);
		// .. then program the pages of interest
		onfi_instance.program_pages_in_a_block_slc(my_test_block_address);
		// let us just put a delay here for some time
		onfi_instance.delay_function(50000); // of nearly us
		// .. verify the program operation
		// onfi_instance.verify_program_pages_in_a_block(my_test_block_address,false,slc_page_indices,20);
		// .. now let us partial erase the page
		onfi_instance.partial_erase_block(my_test_block_address+2,uint32_t(((1000*delay_in_us)-5298)/15));
		onfi_instance.delay_function(50000); // of nearly us
		onfi_instance.read_block_data(my_test_block_address,false,slc_pages,num_slc_pages);
	}
	delete[] slc_pages;
/****************************************************************************************/


/****************************************************************************************
*************** Read Retry with Partial Erase *****************************************************
*****************************************************************************************/
	//followig is the code to analyze the read retry operation with partial erase
	// .. let us first erase the complete block
	onfi_instance.erase_block(my_test_block_address+2,true);
	// .. then program the pages of interest
	onfi_instance.program_pages_in_a_block(my_test_block_address);
	// let us just put a delay here for some time
	onfi_instance.delay_function(50000); // of nearly us
	// .. now let us partial erase the page with time 1100us
	onfi_instance.partial_erase_block(my_test_block_address+2,uint32_t(((1000*1100)-5298)/15));
	onfi_instance.delay_function(50000); // of nearly us
	// now let us loop through and read using different read retry methods
	uint8_t p_values[4] = {0,0,0,0};
	for(uint16_t p1 = 0;p1<0x10;p1++)
	{
		p_values[0] = (uint8_t)p1;
		// set_features(uint8_t address, uint8_t* data_to_send,bool verbose, uint8_t command)
		// ..set features for read retry option
		onfi_instance.set_features(0x89, p_values, false, 0xef);
		// let us read and spit data from 100 selected pages
		onfi_instance.delay_function(50000); // of nearly us
		onfi_instance.read_block_data(my_test_block_address);
	}
	// reset back the read retry option
	p_values[0] = 0x0;
	onfi_instance.set_features(0x89, p_values, false, 0xef);
/****************************************************************************************/

/****************************************************************************************
*************** Verify Program Time with Different Data**********************************
*****************************************************************************************/
	// calloc has already initialized with 0s so ,let us program the pages that we want progran with 0s
	uint16_t page_indices_0s[] = {0,3,10,
								961,967,1007,
								865,417,529,
								545,507,581,
								832,952,972,
								800,678,576};
	onfi_instance.program_pages_in_a_block(my_test_block_address,false,page_indices_0s,18);

	uint16_t page_indices_some0s[] = {16,19,31,
										993,985,1023,
										929,619,685,
										481,645,695,
										744,1022,220};
	uint8_t local_address[5];
	for(uint8_t i = 0;i<5;i++)
		local_address[i] = my_test_block_address[i];

	sort(page_indices_some0s,page_indices_some0s+15);
	// let us make the first onfi_instance.num_bytes_in_page bytes as ffs
	memset(my_data_to_program,0xff,onfi_instance.num_bytes_in_page);
	for(int i=0;i<15;i++)
	{
		// now let us update the address based on this index
		local_address[2] = page_indices_some0s[i]%256;
		local_address[3] = (my_test_block_address[3])|((uint8_t)(0x03&(page_indices_some0s[i]/256)));

		onfi_instance.program_page(local_address,my_data_to_program,true);
	}
	free(my_data_to_program);
/****************************************************************************************/

/****************************************************************************************
***********************SLC Mode Program Disturb **********************************
*****************************************************************************************/
	// let us convert to SLC mode
	onfi_instance.convert_to_slc(my_test_block_address);
	// let us read the timing mode parameters
	// .. 0x91 reads the SLC/MLC thing
	onfi_instance.get_features(0x91,features_parameters);
	cout<<"Feature parameters (SLC/MLC) read are "<<endl;
	cout<<"\t:"<<(int)features_parameters[0]<<","<<(int)features_parameters[1]<<","<<(int)features_parameters[2]<<","<<(int)features_parameters[3]<<endl;
	// let us create an array that we want to program
	// .. since we want to program disturb, let us create
	// .. an array of 18592 bytes of all 0xff
	// .. with 0x00 as last 32 bits
	uint8_t* provided_array = (uint8_t*)malloc((onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page)*sizeof(uint8_t));
	if(provided_array==NULL)
	{
		cout<<"Error in creating an array using malloc"<<endl;
		return 0;
	}
	// let us memset 0xff to all the positions
	memset(provided_array,0xff,onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page);
	// let us fill 0x00 to last 32 bits
	memset(provided_array+onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page-32,0x0,32);

	// now let us program stress all the pages in the block
	for(int i=0;i<=30000;i+=10000)
	{
		// now let us program all the pages in the block
		onfi_instance.program_n_pages_in_a_block(my_test_block_address,512,true,provided_array);
		onfi_instance.delay_function(50000); // of nearly us
		if(i%5000)
		{

		}else
		{
			// let us read the data out of the 512 pages
			onfi_instance.read_block_data_n_pages(my_test_block_address,512);
		}
	}
	free(provided_array);
/****************************************************************************************/


/****************************************************************************************
***********************Program Time Depends on Data Programmed ? **********************************
*****************************************************************************************/
	
	uint8_t* provided_data = (uint8_t*)malloc((onfi_instance.num_spare_bytes_in_page+onfi_instance.num_bytes_in_page)*sizeof(uint8_t));

	//erase teh block
	onfi_instance.erase_block(my_test_block_address+2);
	//fill the data with 0xff to program
	memset(provided_data,0xff,onfi_instance.num_spare_bytes_in_page+onfi_instance.num_bytes_in_page);
	// program pages in the block with all 1s
	// program_pages_in_a_block_data(uint8_t* my_test_block_address,bool complete_block,uint16_t* page_indices,uint16_t num_pages,uint16_t* provided_data,bool verbose)
	onfi_instance.program_pages_in_a_block_data(my_test_block_address,provided_data,true,NULL,1024);

	//erase teh block
	onfi_instance.erase_block(my_test_block_address+2);
	//fill the data with 0x00 to program
	memset(provided_data,0x00,onfi_instance.num_spare_bytes_in_page+onfi_instance.num_bytes_in_page);
	// program pages in the block with all 0s
	// program_pages_in_a_block_data(uint8_t* my_test_block_address,bool complete_block,uint16_t* page_indices,uint16_t num_pages,uint16_t* provided_data,bool verbose)
	onfi_instance.program_pages_in_a_block_data(my_test_block_address,provided_data,true,NULL,1024);

	//erase teh block
	onfi_instance.erase_block(my_test_block_address+2);
	//fill the data with 0xff to program
	memset(provided_data,0xff,onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page-32);
	//fill the data with 0xff to program
	memset(provided_data+onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page-32,0x00,32);
	// program pages in the block with all 0s
	// program_pages_in_a_block_data(uint8_t* my_test_block_address,bool complete_block,uint16_t* page_indices,uint16_t num_pages,uint16_t* provided_data,bool verbose)
	onfi_instance.program_pages_in_a_block_data(my_test_block_address,provided_data,true,NULL,1024);

	//erase teh block
	onfi_instance.erase_block(my_test_block_address+2);
	//fill the data with 0xff to program
	memset(provided_data,0x55,onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page);
	// program pages in the block with all 0s
	// program_pages_in_a_block_data(uint8_t* my_test_block_address,bool complete_block,uint16_t* page_indices,uint16_t num_pages,uint16_t* provided_data,bool verbose)
	onfi_instance.program_pages_in_a_block_data(my_test_block_address,provided_data,true,NULL,1024);

	//erase teh block
	onfi_instance.erase_block(my_test_block_address+2);
	//fill the data with 0x00 to program
	memset(provided_data,0x00,onfi_instance.num_spare_bytes_in_page+onfi_instance.num_bytes_in_page);
	// program pages in the block with all 0s
	// program_pages_in_a_block_data(uint8_t* my_test_block_address,bool complete_block,uint16_t* page_indices,uint16_t num_pages,uint16_t* provided_data,bool verbose)
	onfi_instance.program_pages_in_a_block_data(my_test_block_address,provided_data,true,NULL,1024);
	free(provided_data);
/****************************************************************************************/

/****************************************************************************************
***********************Write LSB read MSB **********************************
*****************************************************************************************/
		//the first order of business is to test if the block is bad block
	if(onfi_instance.is_bad_block(my_test_block_address))
	{
		// it was a bad block
		cout<<"Block used is bad....."<<endl;
	}

	uint8_t* provided_data = (uint8_t*)malloc((onfi_instance.num_spare_bytes_in_page+onfi_instance.num_bytes_in_page)*sizeof(uint8_t));

	//erase teh block
	onfi_instance.erase_block(my_test_block_address+2);
	//fill the data with 0xff to program
	memset(provided_data,0x00,onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page);
	// now program page index 32 with all 0x00 and read the page data
	uint8_t page_address[5] = {my_test_block_address[0],my_test_block_address[1],32,my_test_block_address[3],my_test_block_address[4]};
	// program_page(uint8_t* page_address,uint8_t* data_to_program,bool including_spare = true,bool verbose = false);
	onfi_instance.program_page(page_address,provided_data,true);
	// change to MSB page to read the data
	page_address[2] = 64;
	onfi_instance.read_and_spit_page(page_address);
/****************************************************************************************/


/****************************************************************************************
*********************** Reverse Order in unshared pages to test progra timr **********************************
*****************************************************************************************/
		uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0xA8,0x0};	//testing program time hypo for sybblock

	//the first order of business is to test if the block is bad block
	if(onfi_instance.is_bad_block(my_test_block_address))
	{
		// it was a bad block
		cout<<"Block used is bad....."<<endl;
	}

	uint8_t* provided_data = (uint8_t*)malloc((onfi_instance.num_spare_bytes_in_page+onfi_instance.num_bytes_in_page)*sizeof(uint8_t));

	//erase teh block
	onfi_instance.erase_block(my_test_block_address+2);
	//fill the data with 0xff to program
	memset(provided_data,0x00,onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page);

	int16_t page_idx = 0;
	uint8_t local_address[5] = {my_test_block_address[0],my_test_block_address[1],my_test_block_address[2],my_test_block_address[3],my_test_block_address[4]};
	// for(page_idx = 31;page_idx>=0;page_idx--)
	for(page_idx = 1023;page_idx>=961;page_idx-=2)
	{
		// now let us update the address based on this index
		local_address[2] = page_idx%256;
		local_address[3] = (my_test_block_address[3])|((uint8_t)(0x03&(page_idx/256)));
		// (uint8_t* page_address,uint8_t* data_to_program,bool including_spare,bool verbose)
		onfi_instance.program_page(local_address,provided_data,true,false);

	}
/****************************************************************************************/
/****************************************************************************************
*********************** Program Time different pages **********************************
*****************************************************************************************/
	uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0xA8,0x0};	//testing program time hypo for sybblock

	//the first order of business is to test if the block is bad block
	if(onfi_instance.is_bad_block(my_test_block_address))
	{
		// it was a bad block
		cout<<"Block used is bad....."<<endl;
	}

	uint8_t* provided_data = (uint8_t*)malloc((onfi_instance.num_spare_bytes_in_page+onfi_instance.num_bytes_in_page)*sizeof(uint8_t));

	//erase teh block
	onfi_instance.erase_block(my_test_block_address+2);
	//fill the data with 0xff to program
	memset(provided_data,0x00,onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page);

	int16_t page_idx = 010;
	uint8_t local_address[5] = {my_test_block_address[0],my_test_block_address[1],my_test_block_address[2],my_test_block_address[3],my_test_block_address[4]};

	local_address[2] = page_idx%256;
	local_address[3] = (my_test_block_address[3])|((uint8_t)(0x03&(page_idx/256)));
	// (uint8_t* page_address,uint8_t* data_to_program,bool including_spare,bool verbose)
	onfi_instance.program_page(local_address,provided_data,true,false);

	page_idx = 15;
	local_address[2] = page_idx%256;
	local_address[3] = (my_test_block_address[3])|((uint8_t)(0x03&(page_idx/256)));
	onfi_instance.program_page(local_address,provided_data,true,false);

	page_idx = 0;
	local_address[2] = page_idx%256;
	local_address[3] = (my_test_block_address[3])|((uint8_t)(0x03&(page_idx/256)));
	onfi_instance.program_page(local_address,provided_data,true,false);


	page_idx = 24;
	local_address[2] = page_idx%256;
	local_address[3] = (my_test_block_address[3])|((uint8_t)(0x03&(page_idx/256)));
	onfi_instance.program_page(local_address,provided_data,true,false);

	page_idx = 31;
	local_address[2] = page_idx%256;
	local_address[3] = (my_test_block_address[3])|((uint8_t)(0x03&(page_idx/256)));
	onfi_instance.program_page(local_address,provided_data,true,false);


	page_idx = 16;
	local_address[2] = page_idx%256;
	local_address[3] = (my_test_block_address[3])|((uint8_t)(0x03&(page_idx/256)));
	onfi_instance.program_page(local_address,provided_data,true,false);
	


	page_idx = 1009;
	local_address[2] = page_idx%256;
	local_address[3] = (my_test_block_address[3])|((uint8_t)(0x03&(page_idx/256)));
	onfi_instance.program_page(local_address,provided_data,true,false);

	page_idx = 1023;
	local_address[2] = page_idx%256;
	local_address[3] = (my_test_block_address[3])|((uint8_t)(0x03&(page_idx/256)));
	onfi_instance.program_page(local_address,provided_data,true,false);


	page_idx = 993;
	local_address[2] = page_idx%256;
	local_address[3] = (my_test_block_address[3])|((uint8_t)(0x03&(page_idx/256)));
	onfi_instance.program_page(local_address,provided_data,true,false);


	page_idx = 979;
	local_address[2] = page_idx%256;
	local_address[3] = (my_test_block_address[3])|((uint8_t)(0x03&(page_idx/256)));
	onfi_instance.program_page(local_address,provided_data,true,false);

	page_idx = 991;
	local_address[2] = page_idx%256;
	local_address[3] = (my_test_block_address[3])|((uint8_t)(0x03&(page_idx/256)));
	onfi_instance.program_page(local_address,provided_data,true,false);

	page_idx = 961;
	local_address[2] = page_idx%256;
	local_address[3] = (my_test_block_address[3])|((uint8_t)(0x03&(page_idx/256)));
	onfi_instance.program_page(local_address,provided_data,true,false);

/****************************************************************************************/
	/****************************************************************************************
*********************** SLC Program Time different pages **********************************
*****************************************************************************************/
	uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0xAC,0x0};	//convert to SLC and see data dependent program

	//the first order of business is to test if the block is bad block
	if(onfi_instance.is_bad_block(my_test_block_address))
	{
		// it was a bad block
		cout<<"Block used is bad....."<<endl;
	}
	// let us convert to SLC mode
	onfi_instance.convert_to_slc(my_test_block_address);
	// let us read the timing mode parameters
	// .. 0x91 reads the SLC/MLC thing
	onfi_instance.get_features(0x91,features_parameters);
	cout<<"Feature parameters (SLC/MLC) read are "<<endl;
	cout<<"\t:"<<(int)features_parameters[0]<<","<<(int)features_parameters[1]<<","<<(int)features_parameters[2]<<","<<(int)features_parameters[3]<<endl;
	uint8_t* provided_data = (uint8_t*)malloc((onfi_instance.num_spare_bytes_in_page+onfi_instance.num_bytes_in_page)*sizeof(uint8_t));
	
	// now erase the block
	onfi_instance.erase_block(my_test_block_address+2);
	// now lets program with 0xff in freshly erased cells
	memset(provided_data,0xff,onfi_instance.num_spare_bytes_in_page+onfi_instance.num_bytes_in_page);
	// let us program 512 pages
	onfi_instance.program_n_pages_in_a_block(my_test_block_address,512,true, provided_data);

	// now erase the block
	onfi_instance.erase_block(my_test_block_address+2);
	// now lets program with 0x00
	memset(provided_data,0x00,onfi_instance.num_spare_bytes_in_page+onfi_instance.num_bytes_in_page);
	// let us program 512 pages
	onfi_instance.program_n_pages_in_a_block(my_test_block_address,512,true, provided_data);

	// now erase the block
	onfi_instance.erase_block(my_test_block_address+2);
	//fill the data with 0xff to program most part of pages
	memset(provided_data,0xff,onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page-32);
	//fill the data with 0x00 to last 32 bytes of pages
	memset(provided_data+onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page-32,0x00,32);
	// let us program 512 pages
	onfi_instance.program_n_pages_in_a_block(my_test_block_address,512,true, provided_data);

	// now erase the block
	onfi_instance.erase_block(my_test_block_address+2);
	// now lets program with 0x55
	memset(provided_data,0x55,onfi_instance.num_spare_bytes_in_page+onfi_instance.num_bytes_in_page);
	// let us program 512 pages
	onfi_instance.program_n_pages_in_a_block(my_test_block_address,512,true, provided_data);

	// now erase the block
	onfi_instance.erase_block(my_test_block_address+2);
	// now lets program with 0x00
	memset(provided_data,0x00,onfi_instance.num_spare_bytes_in_page+onfi_instance.num_bytes_in_page);
	// let us program 512 pages
	onfi_instance.program_n_pages_in_a_block(my_test_block_address,512,true, provided_data);

	// let us move back to MLC
	onfi_instance.revert_to_mlc(my_test_block_address);

	onfi_instance.get_features(0x91,features_parameters);
	cout<<"Feature parameters (SLC/MLC) read are "<<endl;
	cout<<"\t:"<<(int)features_parameters[0]<<","<<(int)features_parameters[1]<<","<<(int)features_parameters[2]<<","<<(int)features_parameters[3]<<endl;
/****************************************************************************************/

	/****************************************************************************************
*********************** SLC PUF **********************************
*****************************************************************************************/
		uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0xB8,0x0};	// PUF partial program analysis

	// let us convert to SLC mode
	onfi_instance.convert_to_slc(my_test_block_address);
	// let us do partial program operation with time from 200 to 600 us
	// .. with erase operation
	uint16_t num_slc_pages = 512;
	uint16_t* slc_pages = new uint16_t[num_slc_pages];
	for(uint16_t idx_page = 0;idx_page<num_slc_pages;idx_page++)
		slc_pages[idx_page] = idx_page;
	for(uint32_t delay_in_us = 200;delay_in_us <= 600;delay_in_us+= 10)
	{
		//.. first erase the complete block
		onfi_instance.erase_block(my_test_block_address+2);
		onfi_instance.delay_function(500); // of nearly 500 us
		// .. then verify erase operation
		// onfi_instance.verify_block_erase(my_test_block_address,false,slc_page_indices,20);
		// .. then program the pages of interest
		onfi_instance.partial_program_pages_in_a_block(my_test_block_address,uint32_t(((1000*delay_in_us)-5298)/15),false,slc_pages,num_slc_pages);
		onfi_instance.delay_function(500); // of nearly 500 us
		onfi_instance.read_block_data(my_test_block_address,false,slc_pages,num_slc_pages);
	}

	// let us move back to MLC
	onfi_instance.revert_to_mlc(my_test_block_address);
/****************************************************************************************/
/****************************************************************************************
*********************** SLC to MLC **********************************
*****************************************************************************************/
	uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0xBC,0x0};	// SLC->MLC

	// let us convert to SLC mode
	onfi_instance.convert_to_slc(my_test_block_address);
	
	//.. first erase the complete block
	onfi_instance.erase_block(my_test_block_address+2);

	// let me program the one of the shared pages with
	// .. since we do not know how the numbering goes in SLC pages
	// .. we will program the first shared page in SLC mode ie Page Index 32
	my_test_block_address[2] = 0x32;
	uint16_t num_bytes_to_prog = onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page;
	uint8_t data_to_program[num_bytes_to_prog];
	for(uint16_t idx = 0;idx<num_bytes_to_prog;idx++)
		data_to_program[idx] = 0x55;
	// void program_page(uint8_t* page_address,uint8_t* data_to_program,bool including_spare = true,bool verbose = false);
	onfi_instance.program_page(my_test_block_address,data_to_program);

	// let us read and spit the same page
	onfi_instance.read_and_spit_page(my_test_block_address);
	
	// let us move back to MLC
	onfi_instance.revert_to_mlc(my_test_block_address);
	my_test_block_address[2] = 0x32;
	// let us read and spit the same page
	onfi_instance.read_and_spit_page(my_test_block_address);
/*********************************************************************************/
/****************************************************************************************
*********************** Read Retry **********************************
*****************************************************************************************/
	// let us start our operation in a test block
	// .. following is the address that we plan on using
	// .. the address of the block is 5-bytes hex number as specified in datasheet
	// .. the address is in the form of C1,C2 and R1,R2,R3
	uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0xCC,0x0};
	// let us try to analyze REF3 voltage
	// .. let us erase the block to all 1s
	// .. and program all MSB pages to all 0s
	// .. all LSB pages will be in 1s state
	// .. individual cells will be in 0x01 (MSB,LSB) state
	uint16_t num_msb_pages = 480;
	uint16_t msb_page_indices[num_msb_pages];
	uint16_t lsb_page_indices[num_msb_pages];
	uint16_t idx_pointer = 0;
	for(uint16_t idx = 32;idx<=63;idx+=1)
	{
		lsb_page_indices[idx_pointer] = idx;
		msb_page_indices[idx_pointer] = 2*idx;
		idx_pointer+=1;
	}
	for(uint16_t idx = 65;idx<=959;idx+=2)
	{
		lsb_page_indices[idx_pointer] = idx;
		msb_page_indices[idx_pointer] = idx+63;
		idx_pointer+=1;
	}
	cout<<"Populated "<<idx_pointer<<" LSB and MSB pages indices"<<endl;
	if(msb_page_indices[idx_pointer-1] != 1022 || idx_pointer!=num_msb_pages)
	{
		cout<<"Error in assigning the msb and lsb indices"<<endl;
		cout<<"\t.. the last msb index should be 1022, found "<<msb_page_indices[idx_pointer-1]<<endl;
		return -1;
	}

	std::fstream read_retry_file;
	read_retry_file.open("read_retry_file.txt",std::fstream::out);
	// erase the entire block
	onfi_instance.erase_block(my_test_block_address+2);
	// program MSB pages to 0x00
	onfi_instance.program_pages_in_a_block(my_test_block_address,false,lsb_page_indices,num_msb_pages);
	// this array contains the value for levels for read-retry
	uint8_t p_values[4] = {0,0,0,0};
	uint8_t *page_data_read = new uint8_t[onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page];

	for(uint8_t read_retry_level=0;read_retry_level<8;read_retry_level++)
	{
		//  out counter for stats
		unsigned int msb_0 = 0,msb_1 = 0,lsb_0 = 0, lsb_1 = 0;

		// let us set the read retry level here
		p_values[0] = read_retry_level;
		// let us use set features option here
		onfi_instance.set_features(0x89, p_values, false, 0xef);

		// now read the pages for analysis
		for(uint16_t page1_idx = 0;page1_idx<num_msb_pages;page1_idx++)
		{
			// read the msb page right now
			onfi_instance.read_page_and_return_value(my_test_block_address,msb_page_indices[page1_idx],page_data_read,true);
			// compare the values of msb with 0x00
			for(uint16_t byte_idx = 0;byte_idx<onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page;byte_idx++)
			{
				if(page_data_read[byte_idx]==0x00)
				{
					msb_0+=8;
				}else if(page_data_read[byte_idx]==0xff)
				{
					msb_1+=8;
				}else
				{
					int num_ones = find_num_1s(page_data_read[byte_idx]);
					msb_1 += num_ones;
					msb_0 += 8-num_ones;
				}
			}


			// read this page right now
			onfi_instance.read_page_and_return_value(my_test_block_address,lsb_page_indices[page1_idx],page_data_read,true);
			// compare the values of msb with 0x00
			for(uint16_t byte_idx = 0;byte_idx<onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page;byte_idx++)
			{
				if(page_data_read[byte_idx]==0x00)
				{
					lsb_0+=8;
				}else if(page_data_read[byte_idx]==0xff)
				{
					lsb_1+=8;
				}else
				{
					int num_ones = find_num_1s(page_data_read[byte_idx]);
					lsb_1 += num_ones;
					lsb_0 += 8-num_ones;
				}
			}
		}
		read_retry_file<<(int)read_retry_level<<","<<msb_0<<","<<msb_1<<","<<lsb_0<<","<<lsb_1<<endl;
	}

	delete[] page_data_read;

	// reset the read retry to default
	p_values[0] = 0;
	onfi_instance.set_features(0x89, p_values, false, 0xef);
	read_retry_file.close();

//////////////////////////////////////////////////////////////
/////////////////// read retry finished with random data /////
// let us start our operation in a test block
	// .. following is the address that we plan on using
	// .. the address of the block is 5-bytes hex number as specified in datasheet
	// .. the address is in the form of C1,C2 and R1,R2,R3
	uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x30,0x01};
	// let us try to analyze REF3 voltage
	// .. let us erase the block to all 1s
	// .. and program all MSB pages to all 0s
	// .. all LSB pages will be in 1s state
	// .. individual cells will be in 0x01 (MSB,LSB) state
	uint16_t num_msb_pages = 32;
	uint16_t msb_page_indices[num_msb_pages];
	uint16_t lsb_page_indices[num_msb_pages];
	uint16_t idx_pointer = 0;
	for(uint16_t l_idx = 65;(l_idx<960&&idx_pointer<32);l_idx+=66,idx_pointer++)
	{
		lsb_page_indices[idx_pointer] = l_idx;
		msb_page_indices[idx_pointer] = l_idx+63;
	}
	num_msb_pages = idx_pointer;
	uint16_t both_lsb_msb_indices[num_msb_pages*2];
	for(uint16_t b_idx = 0;b_idx<num_msb_pages;b_idx++)
	{
		both_lsb_msb_indices[b_idx] = lsb_page_indices[b_idx];
		both_lsb_msb_indices[num_msb_pages+b_idx] = msb_page_indices[b_idx];
	}
	std::sort(both_lsb_msb_indices,both_lsb_msb_indices+2*num_msb_pages);

	cout<<"Populated "<<idx_pointer<<" LSB and MSB pages indices"<<endl;
	// if(msb_page_indices[idx_pointer-1] != 1022 || idx_pointer!=num_msb_pages)
	// {
	// 	cout<<"Error in assigning the msb and lsb indices"<<endl;
	// 	cout<<"\t.. the last msb index should be 1022, found "<<msb_page_indices[idx_pointer-1]<<endl;
	// 	return -1;
	// }

	std::fstream read_retry_file;
	read_retry_file.open("read_retry_file.txt",std::fstream::out);

	// convert to SLC for SLC wala
	// onfi_instance.convert_to_slc(my_test_block_address, true);
	
	// create random data to program into each page
	bool program_provided_data = true;
	uint8_t *provided_data = new uint8_t[onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page];
	srand(time(NULL));
	for(uint16_t data_byte_id = 0;data_byte_id<(onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page);data_byte_id++)
	{
		// the value will be between 1 and 255
		provided_data[data_byte_id] = (uint8_t)(rand()%255 +1);
	}

	// erase the entire block
	onfi_instance.erase_block(my_test_block_address+2,true);
	// onfi_instance.verify_block_erase(my_test_block_address+2,true);
	if(program_provided_data)
		onfi_instance.program_pages_in_a_block_data(my_test_block_address, provided_data, false,msb_page_indices,num_msb_pages);
	else
	{
	// program MSB pages to 0x00
	// onfi_instance.program_pages_in_a_block(my_test_block_address,false,both_lsb_msb_indices,2*num_msb_pages);
	// onfi_instance.verify_program_pages_in_a_block(my_test_block_address,false,lsb_page_indices,num_msb_pages);
	}
	
	// this array contains the value for levels for read-retry
	uint8_t p_values[4] = {0,0,0,0};
	uint8_t *page_data_read_msb = new uint8_t[onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page];
	uint8_t *page_data_read_lsb = new uint8_t[onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page];

	for(uint8_t read_retry_level=0;read_retry_level<16;read_retry_level++)
	{
		//  out counter for stats
		unsigned int msb_0 = 0,msb_1 = 0,lsb_0 = 0, lsb_1 = 0, bit_state_00 = 0, bit_state_10 = 0, bit_state_01 = 0, bit_state_11 = 0;

		// let us set the read retry level here
		p_values[0] = read_retry_level;
		// let us use set features option here
		onfi_instance.set_features(0x89, p_values, false, 0xef);

		// now read the pages for analysis
		for(uint16_t page1_idx = 0;page1_idx<num_msb_pages;page1_idx++)
		{
			// read this page right now
			onfi_instance.read_page_and_return_value(my_test_block_address,lsb_page_indices[page1_idx],page_data_read_lsb,true);
			// compare the values of msb with 0x00
			for(uint16_t byte_idx = 0;byte_idx<onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page;byte_idx++)
			{
				if(page_data_read_lsb[byte_idx]==0x00)
				{
					lsb_0+=8;
				}else if(page_data_read_lsb[byte_idx]==0xff)
				{
					lsb_1+=8;
				}else
				{
					int num_ones = find_num_1s(page_data_read_lsb[byte_idx]);
					lsb_1 += num_ones;
					lsb_0 += 8-num_ones;
				}
			}

			// read the msb page right now
			onfi_instance.read_page_and_return_value(my_test_block_address,msb_page_indices[page1_idx],page_data_read_msb,true);
			// compare the values of msb with 0x00
			for(uint16_t byte_idx = 0;byte_idx<onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page;byte_idx++)
			{
				if(page_data_read_msb[byte_idx]==0x00)
				{
					msb_0+=8;
				}else if(page_data_read_msb[byte_idx]==0xff)
				{
					msb_1+=8;
				}else
				{
					int num_ones = find_num_1s(page_data_read_msb[byte_idx]);
					msb_1 += num_ones;
					msb_0 += 8-num_ones;
				}
			}

			for(uint16_t byte_idx = 0;byte_idx<onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page;byte_idx++)
			{
				uint8_t lsb_data = page_data_read_lsb[byte_idx];
				uint8_t msb_data = page_data_read_msb[byte_idx];
				uint8_t mask = 0x01;

				for(int bit_idx=0;bit_idx<8;bit_idx++)
				{
					if(((msb_data>>bit_idx)&mask)==0 && ((lsb_data>>bit_idx)&mask)==0)
					{
						bit_state_00++;
					}else if(((msb_data>>bit_idx)&mask)==0 && ((lsb_data>>bit_idx)&mask)==0x01)
					{
						bit_state_01++;
					}else if(((msb_data>>bit_idx)&mask)==0x01 && ((lsb_data>>bit_idx)&mask)==0x01)
					{
						bit_state_11++;
					}else if(((msb_data>>bit_idx)&mask)==0x01 && ((lsb_data>>bit_idx)&mask)==0x00)
					{
						bit_state_10++;
					}else
					{
						fprintf(stdout, "Should not be here. Bit state error\n");
					}
				}
			}
		}
		read_retry_file<<(int)read_retry_level<<","<<msb_0<<","<<msb_1<<","<<lsb_0<<","<<lsb_1<<","<<bit_state_11<<","<<bit_state_01<<","<<bit_state_00<<","<<bit_state_10<<endl;
	}

	if(program_provided_data)
	{
		uint8_t mask = 0x01;
		unsigned int provided_data_0_count = 0,provided_data_1_count = 0;
		// in condition that we have provided data ourself, let us find the number of 1's and 0's
		for(uint16_t byte_idx = 0;byte_idx<onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page;byte_idx++)
		{
			for(int bit_idx=0;bit_idx<8;bit_idx++)
			{
				if(((provided_data[byte_idx]>>bit_idx)&mask) == 0)
				{
					// the bit was 0
					provided_data_0_count++;
				}else
				{
					provided_data_1_count++;
				}
			}
		}
		read_retry_file<<"0 Count,"<<(int)provided_data_0_count<<",1 Count,"<<(int)provided_data_1_count<<endl;
	}


	delete[] page_data_read_msb;
	delete[] page_data_read_lsb;
	delete[] provided_data;

	// reset the read retry to default
	p_values[0] = 0;
	// onfi_instance.revert_to_mlc(my_test_block_address);
	onfi_instance.set_features(0x89, p_values, false, 0xef);
	read_retry_file.close();

// read retry finished with random data
/*
File: test_mani.cpp

Description: This source file is to test the basic functionality of the interface designed.
			.. This file tests the connection as well as the major functions like
			.. .. erase, program etc
*/

// onfi_head.h has the necessary functinalities defined
#include "onfi_head.h"

#include <cstdlib>
#include <cstring>
#include <algorithm>    // std::sort
#include <unordered_map>
#include <time.h>

using namespace std;

// these are the page indices that will be used for analysis for SLC
uint16_t slc_page_indices[20] = {0,2,4,6,
	32, 34, 36, 38,
	64, 68, 72, 76,

	105, 113, 121, 129,
	168, 176, 184, 192
};

// just the main function
int main()
{
	// let us make an object for onfi_interface
	// ..all the erase and program are defined inside the onfi interface class
	onfi_interface onfi_instance;

	onfi_instance.initialize_onfi();

	// now that the object is created
	// .. the object should go and initialize itself by looking at the addresses and map to them
	// .. let us test if the LEDs test will succeed
	onfi_instance.test_onfi_leds();

#if PROFILE_TIME
	onfi_instance.open_time_profile_file();
#endif

	//for the NAND chip, let us initialize the chip
	// .. this should follow a pattern of power cycle as mentioned in the datasheet
	//.. then we will do a reset operation
	onfi_instance.device_initialization();

	//now let test the NAND chip and print its properties as read from the chip memory itself
	// .. please make sure that the pin connections is appropriate as mentioned in hardware_locations.h
	// .. this function call is also important to establish the parameters like:
	// .. onfi_instance.num_bytes_in_page, onfi_instance.num_spare_bytes_in_page and num_pages_in_block
	// onfi_instance.read_parameters(JEDEC,true);
	onfi_instance.read_parameters(ONFI,true);

	// just an array initialized to random values
	uint8_t features_parameters[4] = {12,34,56,43};
	// let us read the timing mode parameters
	// .. 0x91 reads the SLC/MLC thing
	onfi_instance.get_features(0x91,features_parameters);
	cout<<"Feature parameters (SLC/MLC) read are "<<endl;
	cout<<"\t:"<<(int)features_parameters[0]<<","<<(int)features_parameters[1]<<","<<(int)features_parameters[2]<<","<<(int)features_parameters[3]<<endl;

	// let us start our operation in a test block
	// .. following is the address that we plan on using
	// .. the address of the block is 5-bytes hex number as specified in datasheet
	// .. the address is in the form of C1,C2 and R1,R2,R3
	uint8_t my_test_block_address[5] = {0x0,0x0,0x0,0x3C,0x01};
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
	// num_msb_pages = idx_pointer;
	num_msb_pages = 1;
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
	// program msb pages
	bool program_msb = false;
	// program lsb pages
	bool program_lsb = true;

	uint8_t *provided_data_msb = new uint8_t[onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page];
	uint8_t *provided_data_lsb = new uint8_t[onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page];
	srand(time(NULL));
	for(uint16_t data_byte_id = 0;data_byte_id<(onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page);data_byte_id++)
	{
		// the value will be between 1 and 255
		provided_data_msb[data_byte_id] = (uint8_t)(rand()%255 +1);
		provided_data_lsb[data_byte_id] = (uint8_t)(rand()%255 +1);
	}

	// erase the entire block
	onfi_instance.erase_block(my_test_block_address+2,true);
	// onfi_instance.verify_block_erase(my_test_block_address+2,true);
	if(program_provided_data)
	{
		if(program_lsb && program_msb)
		{
			onfi_instance.program_pages_in_a_block_data(my_test_block_address, provided_data_lsb, false,lsb_page_indices,num_msb_pages);
			onfi_instance.program_pages_in_a_block_data(my_test_block_address, provided_data_msb, false,msb_page_indices,num_msb_pages);
		}
		else if(program_msb) onfi_instance.program_pages_in_a_block_data(my_test_block_address, provided_data_msb, false,msb_page_indices,num_msb_pages);
		else if(program_lsb) onfi_instance.program_pages_in_a_block_data(my_test_block_address, provided_data_lsb, false,lsb_page_indices,num_msb_pages);
	}
	else
	{

		if(program_lsb && program_msb)	onfi_instance.program_pages_in_a_block(my_test_block_address,false,both_lsb_msb_indices,2*num_msb_pages);
		else if(program_msb) onfi_instance.program_pages_in_a_block(my_test_block_address,false,msb_page_indices,num_msb_pages);
		else if(program_lsb) onfi_instance.program_pages_in_a_block(my_test_block_address,false,lsb_page_indices,num_msb_pages);
	}
	
	// this array contains the value for levels for read-retry
	uint8_t p_values[4] = {0,0,0,0};
	uint8_t *page_data_read_msb = new uint8_t[onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page];
	uint8_t *page_data_read_lsb = new uint8_t[onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page];
	
	// put first line in the read retry file
	read_retry_file<<"read_retry_level"<<", "<<"msb_0 (prog)"<<", "<<"msb_0 (read)"<<", "<<"msb_1 (prog)"<<", "<<"msb_1 (read)"<<", "<<"lsb_0 (prog)"<<", "<<"lsb_0 (read)"<<", "<<"lsb_1 (prog)"<<", "<<"lsb_1 (read)"<<", "<<"bit_state_11 (prog)"<<", "<<"bit_state_11 (read)"<<", "<<"bit_state_01 (prog)"<<", "<<"bit_state_01 (read)"<<", "<<"bit_state_00 (prog)"<<", "<<"bit_state_00 (read)"<<", "<<"bit_state_10 (prog)"<<", "<<"bit_state_10 (read)"<<endl;
	
	for(uint8_t read_retry_level=0;read_retry_level<16;read_retry_level++)
	{
		//  out counter for stats
		unsigned int msb_0_read = 0,msb_1_read = 0,lsb_0_read = 0, lsb_1_read = 0, bit_state_00_read = 0, bit_state_10_read = 0, bit_state_01_read = 0, bit_state_11_read = 0;
		unsigned int msb_0_prog = 0,msb_1_prog = 0,lsb_0_prog = 0, lsb_1_prog = 0, bit_state_00_prog = 0, bit_state_10_prog = 0, bit_state_01_prog = 0, bit_state_11_prog = 0;
		
		unordered_map<string,int> state_mismatch_map;
		unsigned int error_bit_num = 0;

		// let us set the read retry level here
		p_values[0] = read_retry_level;
		// let us use set features option here
		onfi_instance.set_features(0x89, p_values, false, 0xef);

		// now read the pages for analysis
		for(uint16_t page1_idx = 0;page1_idx<num_msb_pages;page1_idx++)
		{
			// read this page right now
			onfi_instance.read_page_and_return_value(my_test_block_address,lsb_page_indices[page1_idx],page_data_read_lsb,true);

			// read the msb page right now
			onfi_instance.read_page_and_return_value(my_test_block_address,msb_page_indices[page1_idx],page_data_read_msb,true);

			// compare the values of msb with 0x00
			for(uint16_t byte_idx = 0;byte_idx<onfi_instance.num_bytes_in_page+onfi_instance.num_spare_bytes_in_page;byte_idx++)
			{
				uint8_t read_lsb_byte = page_data_read_lsb[byte_idx];
				uint8_t read_msb_byte = page_data_read_msb[byte_idx];

				uint8_t prog_lsb_byte = 0x00;
				uint8_t prog_msb_byte = 0x00;

				uint8_t mask = 0x01;
				string read_state;
				string prog_state;


				if(program_provided_data)
				{
					if(program_lsb && program_msb)	
					{
						prog_lsb_byte = provided_data_lsb[byte_idx];
						prog_msb_byte = provided_data_msb[byte_idx];
					}else if(program_msb)
					{
						prog_lsb_byte = 0xff;
						prog_msb_byte = provided_data_msb[byte_idx];
					}else if(program_lsb)
					{
						prog_msb_byte = 0xff;
						prog_lsb_byte = provided_data_lsb[byte_idx];
					}else
					{
						prog_lsb_byte = 0xff;
						prog_msb_byte = 0xff;
					}
				}else
				{
					if(program_lsb && program_msb)
					{
						prog_lsb_byte = 0x00;
						prog_msb_byte = 0x00;
					}else if(program_msb)
					{
						prog_lsb_byte = 0xff;
						prog_msb_byte = 0x00;
					}else if(program_lsb)
					{
						prog_msb_byte = 0xff;
						prog_lsb_byte = 0x00;
					}else
					{
						prog_lsb_byte = 0xff;
						prog_msb_byte = 0xff;
					}
				}

				// compute the number of 0s and 1s in LSB of read data
				if(read_lsb_byte==0x00)
				{
					lsb_0_read+=8;
				}else if(read_lsb_byte==0xff)
				{
					lsb_1_read+=8;
				}else
				{
					int num_ones = find_num_1s(read_lsb_byte);
					lsb_1_read += num_ones;
					lsb_0_read += 8-num_ones;
				}
				// compute the number of 0s and 1s in MSB of read data
				if(read_msb_byte==0x00)
				{
					msb_0_read+=8;
				}else if(read_msb_byte==0xff)
				{
					msb_1_read+=8;
				}else
				{
					int num_ones = find_num_1s(read_msb_byte);
					msb_1_read += num_ones;
					msb_0_read += 8-num_ones;
				}

				// compute the number of 0s and 1s in LSB of prog data
				if(prog_lsb_byte==0x00)
				{
					lsb_0_prog+=8;
				}else if(prog_lsb_byte==0xff)
				{
					lsb_1_prog+=8;
				}else
				{
					int num_ones = find_num_1s(prog_lsb_byte);
					lsb_1_prog += num_ones;
					lsb_0_prog += 8-num_ones;
				}
				// compute the number of 0s and 1s in MSB of prog data
				if(prog_msb_byte==0x00)
				{
					msb_0_prog+=8;
				}else if(prog_msb_byte==0xff)
				{
					msb_1_prog+=8;
				}else
				{
					int num_ones = find_num_1s(prog_msb_byte);
					msb_1_prog += num_ones;
					msb_0_prog += 8-num_ones;
				}

				// compute BER here
				error_bit_num += (find_num_1s(prog_msb_byte^read_msb_byte)+find_num_1s(prog_lsb_byte^read_lsb_byte));

				// compute misclassified states here
				for(uint8_t bit_idx=0;bit_idx<8;bit_idx++)
				{
					uint8_t msb_bit_read = (read_msb_byte>>bit_idx)&mask;
					uint8_t lsb_bit_read = (read_lsb_byte>>bit_idx)&mask;
					if((msb_bit_read==0) && (lsb_bit_read==0))
					{
						bit_state_00_read++;
						read_state = "00";
					}else if((msb_bit_read==0) && (lsb_bit_read==0x01))
					{
						bit_state_01_read++;
						read_state = "01";
					}else if((msb_bit_read==0x01) && (lsb_bit_read==0x01))
					{
						bit_state_11_read++;
						read_state = "11";
					}else if((msb_bit_read==0x01) && (lsb_bit_read==0))
					{
						bit_state_10_read++;
						read_state = "10";
					}else
					{
						fprintf(stdout, "Should not be here. Read bit state error\n");
					}


					uint8_t msb_bit_prog = (prog_msb_byte>>bit_idx)&mask;
					uint8_t lsb_bit_prog = (prog_lsb_byte>>bit_idx)&mask;
					if((msb_bit_prog==0) && (lsb_bit_prog==0))
					{
						bit_state_00_prog++;
						prog_state = "00";
					}else if((msb_bit_prog==0) && (lsb_bit_prog==0x01))
					{
						bit_state_01_prog++;
						prog_state = "01";
					}else if((msb_bit_prog==0x01) && (lsb_bit_prog==0x01))
					{
						bit_state_11_prog++;
						prog_state = "11";
					}else if((msb_bit_prog==0x01) && (lsb_bit_prog==0x00))
					{
						bit_state_10_prog++;
						prog_state = "10";
					}else
					{
						fprintf(stdout, "Should not be here. Prog bit state error\n");
					}

					state_mismatch_map[prog_state+"_"+read_state]++;
				}
			}
		}

		//
		// read_retry_file<<"read_retry_level"<<", "<<"msb_0 (prog)"<<", "<<"msb_0 (read)"<<", "<<"msb_1 (prog)"<<", "<<"msb_1 (read)"<<", "<<"lsb_0 (prog)"<<", "<<"lsb_0 (read)"<<", "<<"lsb_1 (prog)"<<", "<<"lsb_1 (read)"<<", "<<"bit_state_11 (prog)"<<", "<<"bit_state_11 (read)"<<", "<<"bit_state_01 (prog)"<<", "<<"bit_state_01 (read)"<<", "<<"bit_state_00 (prog)"<<", "<<"bit_state_00 (read)"<<", "<<"bit_state_10 (prog)"<<", "<<"bit_state_10 (read)"<<endl;
		read_retry_file<<(int)read_retry_level<<", "<<msb_0_prog<<", "<<msb_0_read<<", "<<msb_1_prog<<", "<<msb_1_read<<", "<<lsb_0_prog<<", "<<lsb_0_read<<", "<<lsb_1_prog<<", "<<lsb_1_read<<", "<<bit_state_11_prog<<", "<<bit_state_11_read<<", "<<bit_state_01_prog<<", "<<bit_state_01_read<<", "<<bit_state_00_prog<<", "<<bit_state_00_read<<", "<<bit_state_10_prog<<", "<<bit_state_10_read;
		// iterate through all the items in the map and print them in the same line
		for(auto my_iter: state_mismatch_map)
		{
			read_retry_file<<", "<<my_iter.first<<", "<<my_iter.second;
		}
		read_retry_file<<", E:"<<error_bit_num<<endl;
	}


	delete[] page_data_read_msb;
	delete[] page_data_read_lsb;
	delete[] provided_data_lsb;
	delete[] provided_data_msb;

	// reset the read retry to default
	p_values[0] = 0;
	// onfi_instance.revert_to_mlc(my_test_block_address);
	onfi_instance.set_features(0x89, p_values, false, 0xef);
	read_retry_file.close();
	return 0;
}

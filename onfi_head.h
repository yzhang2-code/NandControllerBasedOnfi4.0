/*
File:			onfi_head.h
Description:	This file contains the necessary functions that are defined by the ONFI protocol
				.. for interfacing with a serial NAND memory.
				The implementation here is tested on NAND memory from Micron.
Author: 		Prawar Poudel, pp0030 (at) uah (dot) edu
Date: 			18 July 2020
*/

#ifndef ONFI_HEAD
#define ONFI_HEAD

// include our next header
#include "microprocessor_interface.h"

enum param_type 
{
	JEDEC = 0,
	ONFI = 1
};

// print debug messages for ONFI things
#define DEBUG_ONFI false
#define PROFILE_DELAY_TIME false

extern uint16_t num_pages_selected;
extern uint16_t page_indices_selected[];

// finds the number of 1s in the number input
// ..  the algo iscalled Brain-Kernigham algo
unsigned int find_num_1s(int input_number);

// let us define a class that includes all the lowest level functions that are needed for
// .. interfacing with NAND device.
class onfi_interface: public interface
{
private:
	// private items go here
	std::fstream onfi_debug_file;
	std::fstream onfi_data_file;

public:
	// public items go here: this should be almost all the required functions

	// let us create a constructor of onfi_interface that initializes the physical_interface
	onfi_interface(){}
	~onfi_interface()
	{
		deinitialize_onfi();
	}

	// let us make these paramters public
	uint16_t num_bytes_in_page;
	uint16_t num_spare_bytes_in_page;
	uint16_t num_pages_in_block;

	//let us create a function that performs initialization
	// .. opens ONFI debug file
	// .. this function gets the bridge based address
	// .. converts the peripheral addresses
	// .. tests the LEDs
	void initialize_onfi(bool verbose = false);
	void deinitialize_onfi(bool verbose = false);

	// this function can be used to test the LEDs if they are properly set up
	//  since it is called as a part of onfi_interface, if this works
	// .. the interface is set up properly
	void test_onfi_leds(bool verbose = false);
	
	// this function opens the debug file 
	// .. debug file is used to log the debug messages
	// .. the file is only opened when DEBUG_ONFI is true
	// .. unless otherwise, it is suggested to set DEBUG_ONFI to false
	void open_onfi_debug_file();

	// open the data file
	void open_onfi_data_file();
	
	// function to receive data from the NAND device
	// .. data is output from the cache regsiter of selected die
	// .. it is supported following a read operation of NAND array
	void get_data(uint8_t* data_received,uint16_t num_data);

	// this function can be used to test the status of flash operation
	void check_status();

	void wait_on_status();

	// function to initialize the NAND device
	// .. following are the tasks to be performed for initialization of NAND device
	// .. provide Vcc (ie ramp Vcc)
	// .. host must wait for R/B to be valid (R/B should be low for certain duration and be high
	// .. .. to indicate device is ready) R/B is output from the NAND device
	// .. issue 0xFF command after R/B goes high (Reset is the first command to be issued)
	// .. R/B should be monotired again after issuing 0XFF command
	void device_initialization(bool verbose = false);

	// function to reset the whole device
	// .. issue a command 0xFF for reset operation
	// .. following operations should be performed for this
	// .. .. enable command cycle
	// .. .. command to be sent is 0xFF
	// .. .. check for R/B signal to be high after certain duration (should go low(busy) and go high (ready))
	void reset_device();

	// following function reads the ONFI parameter page
	// .. the ONFI parameter page consists of ONFI parameter data structure
	// .. this data structure consists of critical information about the internal organization of memory
	// .. the data structure is 256 bytes
	// .. the data will be available for read with a command sequence of ECh followed by an address of 40h
	void read_parameters(param_type ONFI_OR_JEDEC=ONFI,bool verbose = false);

	// based on the values read from the ONFI paramters, we will figure out the ONFI version
	void decode_ONFI_version(uint8_t byte_4,uint8_t byte_5,uint8_t* ret_whole,uint8_t* ret_decimal);

	// following function will set the size of page based on value read 
	void set_page_size(uint8_t byte_83,uint8_t byte_82,uint8_t byte_81,uint8_t byte_80);

	// following function will set the size of spare bytes in a page based on value read 
	void set_page_size_spare(uint8_t byte_85,uint8_t byte_84);

	// following function will set the number of pages in a block
	void set_block_size(uint8_t byte_95,uint8_t byte_94,uint8_t byte_93,uint8_t byte_92);

	// following function tests if the block address sent was a bad block or not
	// the ONFI requirement is that the first byte in the spare area of the first page
	// .. should have 0x00 in it to indicate if the block is bad
	// this function takes in a block address
	// .. and reads the first spare byte of the first page to determine if it is a bad block
	bool is_bad_block(uint8_t* my_test_block_address);

	// write a function to perform an read operation from NAND flash to cache register
	// .. reads one page from the NAND to the cache register
	// .. during the read, you can use change_read_column and change_row_address
	void read_page(uint8_t* address,uint8_t address_length,bool verbose = false);

	// this function opens a file named time_info_file.txt
	// .. this file will log all the duration from the timing operations as necessary
	void open_time_profile_file();

	// follow the following function call by get_data() function call
	// .. please change this if the device has multiple dies
	void change_read_column(uint8_t* col_address);

	// following function erases the block address provided as the parameter to the function
	// .. the address provided should be three 8-bit number array that corresponds to 
	// .. .. R1,R2 and R3 for the block to be erased
	void erase_block(uint8_t* row_address, bool verbose = false);

	// following function erases the block address provided as the parameter to the function
	// .. the address provided should be three 8-bit number array that corresponds to 
	// .. .. R1,R2 and R3 for the block to be erased
	// .. loop_count is the partial erase times, a value of 10 will correspond to 1 ns delay
	void partial_erase_block(uint8_t* row_address, uint32_t loop_count = 30000,bool verbose = false);

	// following function can be used to read the status following any command
	void read_status(uint8_t* status_value);

	// .. this function will read any random page and tries to verify if it was completely erased
	// .. for elaborate verifiying, please use a different function
	bool verify_block_erase_sample(uint8_t* my_test_block_address, bool verbose = false);

	// this is the function that can be used to elaborately verify the erase operation
	// .. the first argument is the address of the block
	// .. the second argument defines if the complete block is to be verified
	// .. .. if the second argument is false, then the pages from page_indices_selected are taken
	bool verify_block_erase(uint8_t* my_test_block_address,bool complete_block = false,uint16_t* page_indices = page_indices_selected,uint16_t num_pages = num_pages_selected, bool verbose = false);

	// function to disable Program and Erase operation
	// .. when WP is low, program and erase operation are disabled
	// .. when WP is high, program and erase operation are enabled
	void disable_erase();
	void enable_erase();

	// this function only programs a single page as indicated by the address provided
	// for the arguments,
	// .. page_address is the address of the page 5-byte address
	// .. data_to_progra is the data to write
	// .. including_spare is to indicate if you want to program the spare section as well
	// .. .. if including spare  = 1, then length of data_to_program should be (num of bytes in pages + num of spare bytes)
	// .. verbose is for priting messages
	void program_page(uint8_t* page_address,uint8_t* data_to_program,bool including_spare = true,bool verbose = false);
	void partial_program_page(uint8_t* page_address,uint32_t loop_count,uint8_t* data_to_program,bool including_spare = true,bool verbose = false);


	// this function only verifies a single page as indicated by the address provided
	// for the arguments,
	// .. page_address is the address of the page 5-byte address
	// .. data_to_progra is the data expected
	// .. including_spare is to indicate if you want to program the spare section as well
	// .. .. if including spare  = 1, then length of data_to_program should be (num of bytes in pages + num of spare bytes)
	// .. verbose is for priting messages
	bool verify_program_page(uint8_t* page_address,uint8_t* data_to_program,bool verbose = false);

	// let us program pages in the block with all 0s
	// the paramters are:
	// .. my_test_block_address is the address of the block (starting address)
	// .. complete_block if this is true all the pages in the block will be programmed
	// .. page_indices is an array of indices inside the block that we want to program
	// .. num_pages is the number of pages in the page_indices array
	// .. verbose is for printing
	void program_pages_in_a_block(uint8_t* my_test_block_address,bool complete_block = false,uint16_t* page_indices = page_indices_selected,uint16_t num_pages = num_pages_selected,bool verbose = false);


	// let us program pages in the block with all uint8_t* provided_data
	// the paramters are:
	// .. my_test_block_address is the address of the block (starting address)
	// .. complete_block if this is true all the pages in the block will be programmed
	// .. page_indices is an array of indices inside the block that we want to program
	// .. num_pages is the number of pages in the page_indices array
	// .. verbose is for printing
	void program_pages_in_a_block_data(uint8_t* my_test_block_address,uint8_t* provided_data,bool complete_block = false,uint16_t* page_indices = page_indices_selected,uint16_t num_pages = num_pages_selected,bool verbose = false);

	// this function will program all the pages in a block with an array provided by user
	// .. if the user wants to give an array
	// .. .. it is indicated through bool array_provided
	// .. .. the actual array is supposed to be in uint8_t* provided_array (lenght should be total number of bytes in a page)
	void program_n_pages_in_a_block(uint8_t* my_test_block_address,uint16_t num_pages = 512,bool array_provided = false, uint8_t* provided_array = NULL,bool verbose=false);

	// let us program pages in the block with all 0s
	// the paramters are:
	// .. my_test_block_address is the address of the block (starting address)
	// .. num_pages is the number of pages in the page_indices array
	// .. verbose is for printing
	void program_pages_in_a_block_slc(uint8_t* my_test_block_address,uint16_t num_pages = 512,bool verbose=false);
	
	void partial_program_pages_in_a_block(uint8_t* my_test_block_address,uint32_t loop_count,bool complete_block = false,uint16_t* page_indices = page_indices_selected,uint16_t num_pages = num_pages_selected,bool verbose = false);

	// let us verify program pages in the block 
	// the paramters are:
	// .. my_test_block_address is the address of the block (starting address)
	// .. complete_block if this is true all the pages in the block will be verified
	// .. page_indices is an array of indices inside the block that we want to verify
	// .. num_pages is the number of pages in the page_indices array
	// .. verbose is for printing
	bool verify_program_pages_in_a_block(uint8_t* my_test_block_address,bool complete_block = false,uint16_t* page_indices = page_indices_selected,uint16_t num_pages = num_pages_selected,bool verbose = false);
	bool verify_program_pages_in_a_block_slc(uint8_t* my_test_block_address,bool verbose = false);

	// this function reads the single page address provided
	// each value is hex while the sequence is terminated by newline character
	void read_and_spit_page(uint8_t* page_address,bool verbose = false);

	// this function reads the pages in the block
	// .. since the complete data from the block might be too much data, the parameter complete_block can be used to limit the data
	// .. if complete_block is true, the compete block will be read
	// .. if complete_block is false, the indices of the pages to be read cane be provided as an array
	// .. if the indices of pages is used, the num_pages should indicate the numb er of pages listed in the array
	// .. verbose indicates the debug messages to be printed
	void read_block_data(uint8_t* my_test_block_address,bool complete_block = false,uint16_t* page_indices = page_indices_selected,uint16_t num_pages = num_pages_selected,bool verbose = false);
	
	
	//  This function read the page specified by the index value in the 
	// .. block and puts the read value into the array passed " return_value" as argument
	void read_page_and_return_value(uint8_t* my_test_block_address,uint16_t index,uint8_t* return_value,bool including_spare = true);

	// this function reads the pages in the block
	// .. since the complete data from the block might be too much data, the parameter num_pages can be used to limit the data
	// .. the num_pages should indicate the number of pages in block starting from beginning
	// .. verbose indicates the debug messages to be printed
	void read_block_data_n_pages(uint8_t* my_test_block_address,uint16_t num_pages = 1,bool verbose = false);

	//The SET FEATURES (EFh) command writes the subfeature parameters (P1-P4) to the
	// .. specified feature address to enable or disable target-specific features. This command is
	// .. accepted by the target only when all die (LUNs) on the target are idle.
	// .. the parameters P1-P4 are in data_to_send argument
	void set_features(uint8_t address, uint8_t* data_to_send,bool verbose = false, uint8_t command = 0xef);

	//The GET FEATURES (EEh) command reads the subfeature parameters (P1-P4) from the
	// .. specified feature address. This command is accepted by the target only when all die
	// .. (LUNs) on the target are idle.
	// .. the parameters P1-P4 are in data_received argument
	void get_features(uint8_t address, uint8_t* data_received,bool verbose = false, uint8_t command = 0xee);

	// following function will convert a block from MLC mode to SLC mode
	// .. it uses set_features option to convert the block from SLC to MLC
	void convert_to_slc_set_features(uint8_t* my_test_block_address);

	void revert_to_mlc_set_features(uint8_t* my_test_block_address);

	void convert_to_slc(uint8_t* my_test_block_address, bool first_time = false);
	void revert_to_mlc(uint8_t* my_test_block_address);

	// this function introduces delay
	// .. the delay is caused using a for loop
	void delay_function(uint32_t loop_count);
	void profile_time();
};

#endif

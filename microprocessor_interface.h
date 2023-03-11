#ifndef MICROPROCESSOR_INTERFACE
#define MICROPROCESSOR_INTERFACE

#include <stdint.h>
#include <fstream>
#include <iostream>

#include "hardware_locations.h"

// following flag keeps the debug information active
#define DEBUG_INTERFACE false


// this interface class defines the pins, location etc required
// .. this may change based on system in use
// .. please verfiy and change its locations in hardware_locations.h
class interface
{
private:

//define masks and addresses here
protected:
	// these are protected so that they can be accessed from onfi_interface class
	volatile uint32_t* jumper_address;
	volatile uint32_t* jumper_direction;
	volatile uint32_t* push_button;
	volatile uint32_t* red_leds;
	volatile unsigned int* interval_timer;


	std::fstream time_info_file;
	// struct timeval tvInitial,tvFinal;
	struct timespec tvInitialns,tvFinalns;

	// this is the debug file that logs debug messages for hardware interface
	std::fstream interface_debug_file;
	// following is the file descriptor for mmap()
	int fd;
	// this will have the base address of the peripheral where the bridge is
	void* bridge_base_virtual;

public:

	// since the masks and locations are used by other class

	// following function opens a file /dev/mem if not opened already
	// .. and returns the file dresciptor
	int open_physical(int fd,bool verbose = false);

	// this function opens a file to log debug information for interface
	void open_interface_debug_file();
	// this function closes the debug file that was open for logging
	void close_interface_debug_file(bool verbose = false);

	// this function closes a file passed as argument
	void close_physical(int fd, bool verbose = false);

	// this function maps the provided physical address to a virtual address and returns virtual address
	// .. generally the base address is provided and offset of specific devices are added on virtual base
	void* map_physical(int fd,uint32_t base, uint32_t span, bool verbose = false);

	// undo mapping
	void unmap_physical(void* virtual_base, uint32_t span, bool verbose = false);

	// this function returns the virtual address of the base of bridge
	void* get_base_bridge(int *fd);

	// following function gets the physical address of differnt peripherals
	// .. these peripherals are protected members in thet class
	void convert_peripheral_address(void* bridge_base_virtual, bool verbose = false);

	// this function turns on the LEDs
	// .. can be used as an indicator
	void turn_leds_on();

	// this function turns off the LEDs
	void turn_leds_off();

	void test_leds_increment(bool verbose = false);

	void set_ce_low();

	// this function sets the default values of pins
	void set_default_pin_values();

	//function that sets the data lines as input
	//.. to be used when data is to be received from NAND
	// ... please do not forget to reset them to output once done
	void set_datalines_direction_input();

	//function that sets the data lines as output/default
	//.. to be used when sending data or sending command
	// ... this function must be called once the datalines are set as input
	void set_datalines_direction_default();
	
	// function to initialize the data and command lines all in inactive state
	// .. here the data lines are output for MCU and all other lines as well
	// ... set data lines as input right before when needed
	// R/B signal will be set as input
	void set_pin_direction_inactive();

	// function to send an arbitrary command signal to the NAND device
	// .. the procedure is as follows ( in the sequence )
	void send_command(uint8_t command_to_send);

	// .. make this function inline in definition
	// .. param: address_to_send is the address value to be sent to the NAND device
	// .. num_address_bytes is the number of bytes in the address 
	void send_addresses(uint8_t* address_to_send, uint8_t num_address_bytes = 1,bool verbose = false);

	// send data to the flash memory
	// first parameter is the array to be sent
	// second parameter is the number of iterms in the array above
	void send_data(uint8_t* data_to_send,uint16_t num_data);
};

#endif
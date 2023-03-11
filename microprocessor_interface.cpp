#include "microprocessor_interface.h"


#include <fcntl.h>
#include <sys/mman.h>

using namespace std;

// following function opens a file /dev/mem if not opened already
// .. and returns the file dresciptor
// .. fd input parameter is the file descriptor
// .. this function opens the /dev/mem/ file and returns the file descriptor
int interface::open_physical(int fd, bool verbose)
{
#if DEBUG_INTERFACE
	if(interface_debug_file)	interface_debug_file<<"I: Opening physical interface: "<<endl;
	else
		cout<<"I: Opening physical interface: "<<endl;
#else
	if(verbose) cout<<"I: Opening physical interface: "<<endl;
#endif
	if(fd==-1)
	{
		// if the file is not already opened
		if((fd=open("/dev/mem",(O_RDWR|O_SYNC)))==-1)
		{
			// if successful opening of the file fails
			fprintf(stderr,"Error: Could not open the /dev/mem file\n");
		}
	}
#if DEBUG_INTERFACE
	if(interface_debug_file)	interface_debug_file<<"I: .. opening interface successful, fd is:"<<fd<<endl;
	else cout<<"I: .. opening interface successful, fd is:"<<fd<<endl;
#else
	if(verbose) cout<<"I: .. opening interface successful, fd is:"<<fd<<endl;
#endif

	return fd;
}

// this function closes a file passed as argument
void interface::close_physical(int fd, bool verbose)
{
#if DEBUG_INTERFACE
	if(interface_debug_file)	interface_debug_file<<"I: Closing physical interface: "<<endl;
	else cout<<"I: Closing physical interface: "<<endl;
#else
	if(verbose) cout<<"I: Closing physical interface: "<<endl;
#endif

	if(fd) close(fd);

#if DEBUG_INTERFACE
	if(interface_debug_file) interface_debug_file<<"I: .. closing physical interface successful."<<endl;
	else cout<<"I: .. closing physical interface successful."<<endl;
#else
	if(verbose) cout<<"I: .. closing physical interface successful."<<endl;
#endif
}

// this function opens a file to log debug information for interface
void interface::open_interface_debug_file()
{
#if DEBUG_INTERFACE
	interface_debug_file.open("interface_debug_log.txt",std::fstream::out);
#endif
}

// this function maps the provided physical address to a virtual address and returns virtual address
// .. generally the base address is provided and offset of specific devices are added on virtual base
void* interface::map_physical(int fd,uint32_t base, uint32_t span, bool verbose)
{
#if DEBUG_INTERFACE
	if(interface_debug_file)	interface_debug_file<<"I: Mapping physical address :"<<endl;
	else cout<<"I: Mapping physical address :"<<endl;
#else
	if(verbose) cout<<"I: Mapping physical address :"<<endl;
#endif

	void *virtual_base;
	virtual_base = mmap(NULL,span,(PROT_READ|PROT_WRITE),MAP_SHARED,fd,base);

	if(virtual_base==MAP_FAILED)
	{
		fprintf(stderr,"ERROR: mmap() failed\n");
		close(fd);
		return (NULL);
	}

#if DEBUG_INTERFACE
	if(interface_debug_file)	interface_debug_file<<"I: .. returning from mapping physical function."<<endl;
	else
		cout<<"I: .. returning from mapping physical function."<<endl;
#else
	if(verbose) cout<<"I: .. returning from mapping physical function."<<endl;
#endif
	return virtual_base;
}

// undo mapping
void interface::unmap_physical(void* virtual_base, uint32_t span, bool verbose)
{
#if DEBUG_INTERFACE
	if(interface_debug_file)	interface_debug_file<<"I: Unmapping physical :"<<endl;
	else cout<<"I: Unmapping physical :"<<endl;
#else
	if(verbose) cout<<"I: Unmapping physical :"<<endl;
#endif

	if(munmap(virtual_base,span)!=0)
	{
		fprintf(stderr,"ERROR: munmap() failed...\n");
	}
#if DEBUG_INTERFACE
	if(interface_debug_file)	interface_debug_file<<"I: .. unmapping physical successful"<<endl;
	else cout<<"I: .. unmapping physical successful"<<endl;
#else
	if(verbose) cout<<"I: .. unmapping physical successful"<<endl;
#endif
}

void interface::close_interface_debug_file(bool verbose)
{
#if DEBUG_INTERFACE
	if(interface_debug_file)
	{
		interface_debug_file<<"I: Closing the debug file"<<endl;
		interface_debug_file.close();		
	}else
		cout<<"I: Closing the debug file"<<endl;
#else
	if(verbose) cout<<"I: Closing the debug file"<<endl;
#endif
}

// this function returns the virtual address of the base of bridge
void* interface::get_base_bridge(int *fd)
{
	void* return_base_address;

	if((*fd=open_physical(*fd))==-1)
	{
		return NULL;
	}

	return_base_address = map_physical(*fd,LW_BRIDGE_BASE,LW_BRIDGE_SPAN);
	return return_base_address;
}

void interface::convert_peripheral_address(void* bridge_base_virtual, bool verbose)
{
	jumper_address = (uint32_t*)((uint32_t)bridge_base_virtual+JP1_location_OFFSET);
	jumper_direction = (uint32_t*)((uint32_t)bridge_base_virtual+JP1_direction_OFFSET);
	push_button = (uint32_t*)((uint32_t)bridge_base_virtual+PUSH_KEY_LOCATION_OFFSET);
	red_leds = (uint32_t*)((uint32_t)bridge_base_virtual+RLED_OFFSET);
	interval_timer = (uint32_t*)((uint32_t)bridge_base_virtual+INTERVAL_TIMER_OFFSET);

	*(interval_timer+2) = 0xffff; // lower 16-bits for timer
	*(interval_timer+3) = 0xffff; // upper 16-bits for timer

#if DEBUG_INTERFACE
	if(interface_debug_file)
	{
		interface_debug_file<<"************************************************************"<<endl;
		interface_debug_file<<"I: The base received in function is 0x"<<std::hex<<(uint32_t)bridge_base_virtual<<endl;
		interface_debug_file<<"I: JP1_location at offset 0x"<<std::hex<<JP1_location_OFFSET<<" is 0x"<<std::hex<<(uint32_t)jumper_address<<endl;
		interface_debug_file<<"I: JP1_direction at offset 0x"<<std::hex<<JP1_direction_OFFSET<<" is 0x"<<std::hex<<(uint32_t)jumper_direction<<endl;
		interface_debug_file<<"I: push_button at offset 0x"<<std::hex<<PUSH_KEY_LOCATION_OFFSET<<" is 0x"<<std::hex<<(uint32_t)push_button<<endl;
		interface_debug_file<<"I: Red LEDs at offset 0x"<<std::hex<<RLED_OFFSET<<" is 0x"<<std::hex<<(uint32_t)red_leds<<endl;
		interface_debug_file<<"I: Interval Timer at offset 0x"<<std::hex<<INTERVAL_TIMER_OFFSET<<" is 0x"<<std::hex<<(uint32_t)interval_timer<<endl;
		interface_debug_file<<"************************************************************"<<endl;
	}else
	{
		cout<<"************************************************************"<<endl;
		cout<<"I: The base received in function is 0x"<<std::hex<<(uint32_t)bridge_base_virtual<<endl;
		cout<<"I: JP1_location at offset 0x"<<std::hex<<JP1_location_OFFSET<<" is 0x"<<std::hex<<(uint32_t)jumper_address<<endl;
		cout<<"I: JP1_direction at offset 0x"<<std::hex<<JP1_direction_OFFSET<<" is 0x"<<std::hex<<(uint32_t)jumper_direction<<endl;
		cout<<"I: push_button at offset 0x"<<std::hex<<PUSH_KEY_LOCATION_OFFSET<<" is 0x"<<std::hex<<(uint32_t)push_button<<endl;
		cout<<"I: Red LEDs at offset 0x"<<std::hex<<RLED_OFFSET<<" is 0x"<<std::hex<<(uint32_t)red_leds<<endl;
		cout<<"I: Interval Timer at offset 0x"<<std::hex<<INTERVAL_TIMER_OFFSET<<" is 0x"<<std::hex<<(uint32_t)interval_timer<<endl;
		cout<<"************************************************************"<<endl;
	}
#else
	if(verbose) 
	{
		cout<<"************************************************************"<<endl;
		cout<<"I: The base received in function is 0x"<<std::hex<<(uint32_t)bridge_base_virtual<<endl;
		cout<<"I: JP1_location at offset 0x"<<std::hex<<JP1_location_OFFSET<<" is 0x"<<std::hex<<(uint32_t)jumper_address<<endl;
		cout<<"I: JP1_direction at offset 0x"<<std::hex<<JP1_direction_OFFSET<<" is 0x"<<std::hex<<(uint32_t)jumper_direction<<endl;
		cout<<"I: push_button at offset 0x"<<std::hex<<PUSH_KEY_LOCATION_OFFSET<<" is 0x"<<std::hex<<(uint32_t)push_button<<endl;
		cout<<"I: Red LEDs at offset 0x"<<std::hex<<RLED_OFFSET<<" is 0x"<<std::hex<<(uint32_t)red_leds<<endl;
		cout<<"I: Interval Timer at offset 0x"<<std::hex<<INTERVAL_TIMER_OFFSET<<" is 0x"<<std::hex<<(uint32_t)interval_timer<<endl;
		cout<<"************************************************************"<<endl;
	}
#endif
}

// this function turns on the LEDs
// .. can be used as an indicator
void interface::turn_leds_on()
{
	// turns on 10 LEDs
	*red_leds = 0x3ff;
}

// this function turns off the LEDs
void interface::turn_leds_off()
{
	//turns off the LEDs
	*red_leds = 0x0;
}

// this function is to test the LEDs
// .. lights up the loweest LED and slowly light up others after a delay
void interface::test_leds_increment(bool verbose)
{
#if DEBUG_INTERFACE
	if(interface_debug_file)	interface_debug_file<<"I: testing LEDs with a shifting lighting pattern"<<endl;
	else
		cout<<"I: testing LEDs with a shifting lighting pattern"<<endl;
#else
	if(verbose) cout<<"I: testing LEDs with a shifting lighting pattern"<<endl;
#endif
	uint32_t val = 0x01;
	uint8_t reps = 0;
	uint16_t delay = 65530;

	for(;reps<50;reps++)
	{
		while(val<=0x200)
		{
			*red_leds = val;
			while(delay)
			{
				delay--;
			}
			delay = 65530;
			val<<=1;
		}
		val = 0x01;
	}
#if DEBUG_INTERFACE
	if(interface_debug_file)	interface_debug_file<<"I: .. testing LEDs completed"<<endl;
	else 	cout<<"I: .. testing LEDs completed"<<endl;
#else
	if(verbose) cout<<"I: .. testing LEDs completed"<<endl;
#endif
}


// function to initialize the data and command lines all in inactive state
// .. here the data lines are output for MCU and all other lines as well
// ... set data lines as input right before when needed
// R/B signal will be set as input
__attribute__((always_inline)) void interface::set_pin_direction_inactive()
{
	// set the required pins as output from the angle of NIOS machine
	*jumper_direction |= (DQ_mask+CLE_mask+ALE_mask+WP_mask+RE_mask+WE_mask+CE_mask);	// this line just sets the output pins
	*jumper_direction &= ~(RB_mask);	//this line does it for input pin R/B
	
	// let us first reset the DQ pints
	*jumper_address &= ~(DQ_mask);
}

__attribute__((always_inline)) void interface::set_ce_low()
{
	// we do not touch the DQ pin values here
	// .. since CE#, RE# and WE# are active low, we will set them to 1
	// .. since ALE and CLE are active high, we will reset them to 0
	// .. 
	*jumper_address &= ~(CE_mask);
}

__attribute__((always_inline)) void interface::set_default_pin_values()
{
	// we do not touch the DQ pin values here
	// .. since CE#, RE# and WE# are active low, we will set them to 1
	// .. since ALE and CLE are active high, we will reset them to 0
	// .. 
	*jumper_address |= (CE_mask+RE_mask+WE_mask);
	*jumper_address &= ~(ALE_mask+CLE_mask+DQ_mask);
}


//function that sets the data lines as output/default
//.. to be used when sending data or sending command
// ... this function must be called once the datalines are set as input
__attribute__((always_inline)) void interface::set_datalines_direction_default()
{
	//. set the datalines as input
	*jumper_direction |= (DQ_mask);
	// let us reset the DQ pints
	*jumper_address &= ~(DQ_mask);
}

//function that sets the data lines as input
//.. to be used when data is to be received from NAND
// ... please do not forget to reset them to output once done
__attribute__((always_inline)) void interface::set_datalines_direction_input()
{
	//. set the datalines as input
	*jumper_direction &= ~(DQ_mask);
}

// function to send an arbitrary command signal to the NAND device
// .. the procedure is as follows ( in the sequence )
__attribute__((always_inline)) void interface::send_command(uint8_t command_to_send)
{
	// .. Write Enable should go low WE => low
	// .. reset the bit that is connected to WE
	*jumper_address &= ~(WE_mask);
	// .. .. Chip Enable should go low CE => low
	*jumper_address &= ~(CE_mask);
	// .. .. ALE should go low ALE => low
	// .. .. ALE should be zero from before
	// .. ..RE goes high
	// .. ..RE should be high from before
	// .. .. CLE should go high CLE => high
	*jumper_address |= (CLE_mask);

	// .. .. send the command signal in the DQ pins	
	// .. .. the idea is clear the least 8-bits
	// .. .. copy the values to be sent
	// .. .. ..the first part reset the DQ pins
	// .. .. ..the second part has the actual command to send
	*jumper_address = (*jumper_address&(~DQ_mask))|(command_to_send & DQ_mask);

	//insert delay here
	// .. tDS = 40 ns
	SAMPLE_TIME;

	// disable write enable again
	*jumper_address |= (WE_mask);

	//insert delay here
	// .. because the command is written on the rising edge of WE
	// tDH = 20 ns
	// HOLD_TIME;
	asm("NOP");

	// disable CLE
	*jumper_address &= ~(CLE_mask);
	//make sure to call set_default_pin_values()
	set_default_pin_values();
}

// .. make this function inline in definition
// .. param: address_to_send is the address value to be sent to the NAND device
// .. num_address_bytes is the number of bytes in the address 
__attribute__((always_inline)) void interface::send_addresses(uint8_t* address_to_send, uint8_t num_address_bytes, bool verbose)
{
#if DEBUG_INTERFACE
	if(interface_debug_file)
		interface_debug_file<<"I: Sending Addresses "<<num_address_bytes<<" bytes"<<endl;
	else
		cout<<"I: Sending Addresses "<<num_address_bytes<<" bytes"<<endl;
#else
	if(verbose) cout<<"I: Sending Addresses "<<num_address_bytes<<" bytes"<<endl<<"\t:";
#endif

	*jumper_address &= ~CE_mask;
	// .. CLE goes low
	// .. CLE should be 0 from before
	// .. ALE goes high
	*jumper_address |= ALE_mask;
	// .. RE goes high
	// .. RE should be high from before
	uint8_t i=0;
	for(i=0;i<num_address_bytes;i++)
	{
		*jumper_address &= ~(WE_mask);
		// .. Put data on the DQ pin
		// .. .. the idea is clear the least 8-bits
		// .. .. copy the values to be sent
		*jumper_address = (*jumper_address&(~DQ_mask))|(address_to_send[i] & DQ_mask);

#if DEBUG_INTERFACE
	if(interface_debug_file)
		// interface_debug_file<<std::hex<<(uint8_t)(*jumper_address&0xff)<<",";
		fprintf(interface_debug_file,"0x%x,", (uint8_t)*jumper_address&0xff);
	else
		// cout<<std::hex<<(uint8_t)(*jumper_address&0xff)<<",";
		fprintf(stdout,"0x%x,", (uint8_t)*jumper_address&0xff);
#else
		// cout<<std::hex<<(uint8_t)(*jumper_address&0xff)<<",";
		if(verbose) fprintf(stdout,"0x%x,", (uint8_t)*jumper_address&0xff);
#endif
		//.. a simple delay
		SAMPLE_TIME; //tDS

		// .. Address is loaded from DQ on rising edge of WE
		*jumper_address |= WE_mask;
		// .. maintain WE high for certain duration and make it low
		
		// .. put next address bits on DQ and cause rising edge of WE
		// .. address expected is 5-bytes ColAdd1, ColAdd2, RowAdd1, RowAdd2, RowAdd3
		
		//insert delay here
		asm("NOP");
	// tDH
	}
	//make sure to call set_default_pin_values()
	set_default_pin_values();

#if DEBUG_INTERFACE
	if(interface_debug_file)
		interface_debug_file<<endl;
	else
		cout<<endl;
#else
	if(verbose) cout<<endl;
	// fprintf(stderr,"\n");
#endif
}

// send data to the flash memory
// first parameter is the array to be sent
// second parameter is the number of iterms in the array above
__attribute__((always_inline)) void interface::send_data(uint8_t* data_to_send,uint16_t num_data)
{
	// .. CE should be low
	*jumper_address &= ~CE_mask;
	uint16_t i=0;
	for(i=0;i<num_data;i++)
	{
		// .. make WE low and repeat the procedure again for number of bytes required (int num_data)
		*jumper_address &= ~WE_mask;

		// .. put data on DQ and latch WE high for certain duration
		// .. .. the idea is clear the least 8-bits
		// .. .. copy the values to be sent
		*jumper_address = (*jumper_address&(~DQ_mask))|(data_to_send[i] & DQ_mask);
		//.. a simple delay
		SAMPLE_TIME;	// tDS

		*jumper_address |= WE_mask;

		//insert delay here
		// HOLD_TIME;	//tDH
		asm("NOP");


		// reset all the data on DQ pins
		// .. this might be unnecesary
		*jumper_address &= ~(DQ_mask);		
	}
	//make sure to call set_default_pin_values()
	set_default_pin_values();
}
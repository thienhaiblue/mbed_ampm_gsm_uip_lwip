/* mbed USBHost Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "mbed.h"
#include "rtos.h"
#include "mbed_stats.h"
#include "USBHostMSD.h"
#include "usb_host.h"
#include "fatfs.h"
#include "usbh_diskio.h"
#include "lib/sys_tick.h"

USBHostMSD::USBHostMSD(const char * rootdir) : FATFileSystem(rootdir)
{
	MX_USB_HOST_Init();
	tryCnt = 0;
	initTimeout = 0;
	Thread::wait(3000);
	init();
}

void USBHostMSD::init() {
    dev_connected = false;
}


bool USBHostMSD::connected()
{
    return dev_connected;
}

bool USBHostMSD::connect()
{
		if(USBH_status(0) == RES_OK)
		{
			dev_connected = true;
			return true;
		}
		dev_connected = false;;
    return false;
}



unsigned char USBHostMSD::disk_initialize()
    //give the FAT module access to the card setup routine
{
	unsigned char  res;
	if((USBH_status(0) == RES_OK) && tryCnt++ < 3)
	{
		return RES_OK;
	}
	else if(((SysTick_Get()) > initTimeout + 30000))
	{
		tryCnt = 0;
		initTimeout = SysTick_Get();
		res = USBH_initialize(0); 
		Thread::wait(3000);
		return res;
	}
	return RES_ERROR;
}

unsigned char USBHostMSD::disk_status()
    //return card initialization and availability status
{ 
	return USBH_status(0); 

}

unsigned char USBHostMSD::disk_read(unsigned char* buff, unsigned long sector, unsigned char count)
    //give the FAT module access to the multiple-sector reading function
{ 
	return USBH_read(0,buff,sector, count); 
}
unsigned char USBHostMSD::disk_write(const unsigned char* buff, unsigned long sector, unsigned char count)
    //give the FAT module access to the multiple-sector writing function
{ 
	return USBH_write(0,buff,sector, count); 
}

unsigned long USBHostMSD::disk_sector_count()
    //calculate and return the number of sectors on the card from the CSD
{
		return USBH_disk_sector_count();
}
unsigned short USBHostMSD::disk_sector_size()
    //fix the sector size to 512 bytes for all cards versions
{ 
	return USBH_disk_sector_size();
}
unsigned long USBHostMSD::disk_block_size()
    //calculate and return the number of sectors in an erase block from the CSD
{
    return USBH_disk_block_size();
}


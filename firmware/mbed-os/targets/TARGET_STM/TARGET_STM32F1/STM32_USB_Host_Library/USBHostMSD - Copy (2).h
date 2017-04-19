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

#ifndef USBHOSTMSD_H
#define USBHOSTMSD_H

#include "FATFileSystem.h"

/** 
 * A class to communicate a USB flash disk
 */
class USBHostMSD : public FATFileSystem {
public:
    /**
    * Constructor
    *
    * @param rootdir mount name
    */
    USBHostMSD(const char * rootdir);

    /**
    * Check if a MSD device is connected
    *
    * @return true if a MSD device is connected
    */
    bool connected();

    /**
     * Try to connect to a MSD device
     *
     * @return true if connection was successful
     */
    bool connect();

protected:
    //From IUSBEnumerator
		 virtual unsigned char disk_initialize();
        virtual unsigned char disk_status();
        virtual unsigned char disk_read(unsigned char* buff,unsigned long sector, unsigned char count);
        virtual unsigned char disk_write(const unsigned char* buff,unsigned long sector, unsigned char count);
        virtual unsigned char disk_sync(){return 0;}
        virtual unsigned long disk_sector_count();
        virtual unsigned short disk_sector_size();
        virtual unsigned long disk_block_size();
private:

    bool dev_connected;
    void init();

};


#endif

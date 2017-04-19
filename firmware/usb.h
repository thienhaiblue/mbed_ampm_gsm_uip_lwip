/* FILE: usb.h by Chu Van Thiem
*/
#ifndef __USB_H__
#define __USB_H__

#include "USBHostMSD.h"
#include "mbed.h"
#include "string"
#include "vector"

class usb : public USBHostMSD/*, public FATDirHandle*/ {
public:
    // Constructor
    usb(const char * rootdir);
    
    // List all files of the directory
    void listdir(const char *dir);
    
public:
    vector<string> filenames;
};

#endif

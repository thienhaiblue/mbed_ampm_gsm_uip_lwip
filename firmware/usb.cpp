/* FILE: usb.cpp
*/
#include "usb.h"
#include "mbed.h"

extern Serial pc;
usb::usb(const char * rootdir) : USBHostMSD(rootdir)
{
    // Clear list of files
    filenames.clear();
}

void usb::listdir(const char *dir) {
    DIR *d;
    struct dirent *p;
    //vector<string> filenames;
		printf("start opendir()\n");
    d = opendir(dir);
		printf("opendir(%d)\n",d);
    if (d != NULL) {
        //filenames.clear();
        while ((p = readdir(d)) != NULL) {
            printf(" - %s\n", p->d_name);
            //filenames.push_back(string(p->d_name));
        }
			printf("closedir(%d)\n",d);
			closedir(d);
    } else {
        printf("Could not open directory!\n");
    }
}

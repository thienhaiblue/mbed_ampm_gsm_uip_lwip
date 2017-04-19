/* mbed Microcontroller Library
 * Copyright (c) 2006-2012 ARM Limited
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef MBED_FATFILESYSTEM_H
#define MBED_FATFILESYSTEM_H

#include "FileSystemLike.h"
#include "FileHandle.h"
#include "ff.h"
#include <stdint.h>

using namespace mbed;

class FATFileSystem : public FileSystemLike {
public:

    FATFileSystem(const char* n);
    virtual ~FATFileSystem();

    static FATFileSystem * _ffs[_VOLUMES];   // FATFileSystem objects, as parallel to FatFs drives array
    FATFS _fs;                               // Work area (file system object) for logical drive
    int _fsid;

    virtual FileHandle *open(const char* name, int flags);
    virtual int remove(const char *filename);
    virtual int format();
    virtual DirHandle *opendir(const char *name);
    virtual int mkdir(const char *name, mode_t mode);
		virtual int closedir(DirHandle *dir);
		virtual unsigned char disk_initialize() { return 0x00; }
		virtual unsigned char disk_status() { return 0x00; }
		virtual unsigned char disk_read(unsigned char* buff,
				unsigned long sector, unsigned char count) = 0;
		virtual unsigned char disk_write(const unsigned char* buff,
				unsigned long sector, unsigned char count) = 0;
		virtual unsigned char disk_sync() { return 0x00; }
		virtual unsigned long disk_sector_count() = 0;
		virtual unsigned short disk_sector_size() { return 512; }
		virtual unsigned long disk_block_size() { return 1; }

};

#endif

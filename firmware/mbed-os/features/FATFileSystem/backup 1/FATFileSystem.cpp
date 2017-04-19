/* mbed Microcontroller Library - FATFileSystem
   Copyright (c) 2008, sford */

//Modified by Thomas Hamilton, Copyright 2010

#include "FATFileSystem.h"

DWORD get_fattime(void) {
    time_t rawtime;
    time(&rawtime);
    struct tm *ptm = localtime(&rawtime);
    return (DWORD)(ptm->tm_year - 80) << 25
         | (DWORD)(ptm->tm_mon + 1  ) << 21
         | (DWORD)(ptm->tm_mday     ) << 16
         | (DWORD)(ptm->tm_hour     ) << 11
         | (DWORD)(ptm->tm_min      ) << 5
         | (DWORD)(ptm->tm_sec/2    );
}

FATFileSystem* FATFileSystem::DriveArray[_VOLUMES] = {0};

FATFileSystem::FATFileSystem(const char* SystemName) : FileSystemLike(SystemName)
{
		char path[16];
    for (unsigned char i = 0; i < _VOLUMES; i++)
    {
        if(!DriveArray[i])
        {
            DriveArray[i] = this;
            Drive = i;
						sprintf(path,"%d:/",i);
						f_mount(&FileSystemObject, path, 0);
            return;
        }
    }
}

FATFileSystem::~FATFileSystem()
{
		char path[16];
    for (unsigned char i = 0; i < _VOLUMES; i++)
    {
        if (DriveArray[i] == this)
        {
            DriveArray[i] = NULL;
						sprintf(path,"%d:/",i);
            f_mount(NULL,path, 1);
        }
    }
    delete this;
}

FileHandle* FATFileSystem::open(const char* filename, int flags)
{
    FAT_FIL FileObject;
    char FileName[64];
    BYTE ModeFlags = 0;

    sprintf(FileName, "%d:/%s", Drive, filename);
    switch (flags & 3)
    {
        case O_RDONLY: ModeFlags = FA_READ; break;
        case O_WRONLY: ModeFlags = FA_WRITE; break;
        case O_RDWR: ModeFlags = FA_READ | FA_WRITE; break;
    }
    if(flags & O_CREAT)
    {
        if(flags & O_TRUNC)
        {
            ModeFlags |= FA_CREATE_ALWAYS;
        }
        else
        {
            ModeFlags |= FA_OPEN_ALWAYS;
        }
    }
    else
    {
        ModeFlags |= FA_OPEN_EXISTING;
    }
    if (f_open(&FileObject, (const TCHAR*)FileName, ModeFlags))
    { 
        return NULL;
    }
    else
    {
        if (flags & O_APPEND)
        {
            f_lseek(&FileObject, (DWORD)FileObject.fsize);
        }
        return new FATFileHandle(FileObject);
    }
}

int FATFileSystem::remove(const char* filename)
{
    char FileName[64];

    sprintf(FileName, "%d:/%s", Drive, filename);
    if (f_unlink((const TCHAR*)FileName))
    { 
        return -1;
    }
    else
    {
        return 0;
    }
}

int FATFileSystem::rename(const char* oldname, const char* newname)
{
    char OldName[64];

    sprintf(OldName, "%d:/%s", Drive, oldname);
    if (f_rename((const TCHAR*)OldName, (const TCHAR*)newname))
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

DirHandle* FATFileSystem::opendir(const char* name)
{
    FAT_DIR DirectoryObject;
    char DirectoryName[64];

    sprintf(DirectoryName, "%d:%s", Drive, name);
    if (f_opendir(&DirectoryObject, (const TCHAR*)name))
    {
        return NULL;
    }
    else
    {
        return new FATDirHandle(DirectoryObject);
    }
}

int FATFileSystem::mkdir(const char* name, mode_t mode)
{
    char DirectoryName[64];

    sprintf(DirectoryName, "%d:%s", Drive, name);
    if (f_mkdir((const TCHAR*)DirectoryName))
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int FATFileSystem::format(unsigned int allocationunit)
{
		char DriveName[64];
		sprintf(DriveName, "%d:/", Drive);
    if (f_mkfs(DriveName, 0, allocationunit))
    {
        return -1;
    }
    else
    {
        return 0;
    }
}
/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2007        */
/*-----------------------------------------------------------------------*/
/* This is a stub disk I/O module that acts as front end of the existing */
/* disk I/O modules and attach it to FatFs module with common interface. */
/*-----------------------------------------------------------------------*/

//Modified by Thomas Hamilton, Copyright 2010

#include "diskio.h"
#include "mbed_debug.h"
#include "FATFileSystem.h"

using namespace mbed;

DSTATUS disk_initialize(BYTE pdrv) 
{
    if (FATFileSystem::DriveArray[pdrv])
    {
        return (DSTATUS)FATFileSystem::DriveArray[pdrv]->disk_initialize();
    }
    else
    {
        return STA_NOINIT;
    }
}

DSTATUS disk_status (BYTE pdrv) 
{
    if (FATFileSystem::DriveArray[pdrv])
    {
        return (DSTATUS)FATFileSystem::DriveArray[pdrv]->disk_status();
    }
    else
    {
        return STA_NOINIT;
    }
}

DRESULT disk_read (BYTE pdrv, BYTE* buff, DWORD sector, UINT count)
{
    if (FATFileSystem::DriveArray[pdrv])
    {
        return (DRESULT)FATFileSystem::DriveArray[pdrv]->disk_read(buff,sector,count);
    }
    else
    {
        return RES_NOTRDY;
    }
}

#if _USE_WRITE == 1
DRESULT disk_write (BYTE pdrv, const BYTE* buff, DWORD sector, UINT count)
{
    if (FATFileSystem::DriveArray[pdrv])
    {
        return (DRESULT)FATFileSystem::DriveArray[pdrv]->disk_write(buff,sector,count);
    }
    else
    {
        return RES_NOTRDY;
    }
}
#endif
#if _USE_IOCTL == 1
DRESULT disk_ioctl(BYTE pdrv, BYTE ctrl, void* buff)
{
		
    switch (ctrl)
    {
        case CTRL_SYNC:
            if (FATFileSystem::DriveArray[pdrv])
            {
                return (DRESULT)FATFileSystem::DriveArray[pdrv]->disk_sync();
            }
            else
            {
                return RES_NOTRDY;
            } 

        case GET_SECTOR_SIZE:
            if (FATFileSystem::DriveArray[pdrv])
            {
                WORD Result = FATFileSystem::DriveArray[pdrv]->disk_sector_size();
                if (Result > 0)
                {
                    *((WORD*)buff) = Result;
                    return RES_OK;
                }
                else
                {
                    return RES_ERROR;
                }
            }
            else
            {
                return RES_NOTRDY;
            }

        case GET_SECTOR_COUNT:
            if (FATFileSystem::DriveArray[pdrv])
            {
                DWORD Result = FATFileSystem::DriveArray[pdrv]->disk_sector_count();
                if (Result > 0)
                {
                    *((DWORD*)buff) = Result;
                    return RES_OK;
                }
                else
                {
                    return RES_ERROR;
                }
            }
            else
            {
                return RES_NOTRDY;
            }

        case GET_BLOCK_SIZE:
            if (FATFileSystem::DriveArray[pdrv])
            {
                DWORD Result = FATFileSystem::DriveArray[pdrv]->disk_block_size();
                if (Result > 0)
                {
                    *((DWORD*)buff) = Result;
                    return RES_OK;
                }
                else
                {
                    return RES_ERROR;
                }
            }
            else
            {
                return RES_NOTRDY;
            }

        default:
            return RES_PARERR;
    }
}
#endif /* _USE_IOCTL == 1 */


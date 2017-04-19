//mbed Microcontroller Library
//SDCard Interface
//Copyright 2010
//Thomas Hamilton

#ifndef SDCardLibrary
#define SDCardLibrary

#include "stdint.h"
#include "mbed.h"
#include "FATFileSystem.h"
#include "diskio.h"
class SDCard : public FATFileSystem
{
    private:
        
        DigitalOut ChipSelect;
				DigitalOut PowerOn;
				unsigned char status;
				unsigned char CardType;
				unsigned int sector_number_max;
				unsigned int sector_size;
				unsigned long memory_size;
            //physical chip interface
        virtual unsigned char disk_initialize();
        virtual unsigned char disk_status();
        virtual unsigned char disk_read(unsigned char* buff,
            unsigned long sector, unsigned char count);
        virtual unsigned char disk_write(const unsigned char* buff,
            unsigned long sector, unsigned char count);
        virtual unsigned char disk_sync();
        virtual unsigned long disk_sector_count();
        virtual unsigned short disk_sector_size();
        virtual unsigned long disk_block_size();
				void SPI_WriteMutilByte(const unsigned char* buf,uint32_t len);
				void SPI_ReadMutilByte(unsigned char* buf,uint32_t len);
				int wait_ready (uint32_t wt/* Timeout [ms] */);
				void deselect (void);
				int select (void);
				void power_on (void);
				void power_off (void);
				int rcvr_datablock (	/* 1:OK, 0:Error */
										BYTE *buff,			/* Data buffer */
										UINT btr			/* Data block length (byte) */
									);
				int xmit_datablock (	/* 1:OK, 0:Failed */
											const BYTE *buff,	/* Ponter to 512 byte data to be sent */
											BYTE token			/* Token */
										);
				BYTE send_cmd (		/* Return value: R1 resp (bit7==1:Failed to send) */
											BYTE cmd,		/* Command index */
											DWORD arg		/* Argument */
										);
				DSTATUS MMC_disk_initialize (
											BYTE drv		/* Physical drive number (0) */
										);
				DRESULT MMC_disk_read (
											BYTE drv,		/* Physical drive number (0) */
											BYTE *buff,		/* Pointer to the data buffer to store read data */
											DWORD sector,	/* Start sector number (LBA) */
											BYTE count		/* Number of sectors to read (1..128) */
										);
				DRESULT MMC_disk_write (
											BYTE drv,			/* Physical drive number (0) */
											const BYTE *buff,	/* Ponter to the data to write */
											DWORD sector,		/* Start sector number (LBA) */
											BYTE count			/* Number of sectors to write (1..128) */
										);
				DRESULT MMC_disk_ioctl (
											BYTE drv,		/* Physical drive number (0) */
											BYTE cmd,		/* Control command code */
											void *buff		/* Pointer to the conrtol data */
										);
				DRESULT  MMC_disk_info(void);
				uint8_t SPI_WriteByte(uint8_t data);
				void ChipSelectSet(uint8_t value);
				void SPI_SetHighFreq(void);
				void SPI_SetLowFreq(void);
											
    public:
			SPI DataLines;
        SDCard(PinName mosi, PinName miso, PinName sck, PinName cs,PinName pw,
            const char* DiskName);
            //constructor needs SPI pins, DigitalOut pins, and a directory name
        virtual ~SDCard();
				
				
};

#endif


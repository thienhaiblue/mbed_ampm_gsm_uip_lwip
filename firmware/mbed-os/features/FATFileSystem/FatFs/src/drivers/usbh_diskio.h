/**
  ******************************************************************************
  * @file    usbh_diskio.h 
  * @author  MCD Application Team
  * @version V1.3.0
  * @date    08-May-2015
  * @brief   Header for usbh_diskio.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBH_DISKIO_H
#define __USBH_DISKIO_H
#ifdef __cplusplus
#include "ff_gen_drv.h"
 extern "C" {
#endif 
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern const Diskio_drvTypeDef  USBH_Driver;
extern DSTATUS USBH_reinitialize(BYTE);
extern DSTATUS USBH_initialize (BYTE);
extern DSTATUS USBH_status (BYTE);
extern DRESULT USBH_read (BYTE, BYTE*, DWORD, UINT);
#if _USE_WRITE == 1
extern DRESULT USBH_write (BYTE, const BYTE*, DWORD, UINT);
#endif /* _USE_WRITE == 1 */

DWORD USBH_disk_sector_count(void);
DWORD USBH_disk_sector_size(void);
DWORD USBH_disk_block_size(void);

#ifdef __cplusplus
}
#endif
#endif /* __USBH_DISKIO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


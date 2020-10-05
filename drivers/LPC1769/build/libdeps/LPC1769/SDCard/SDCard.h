#ifndef _MMC_SD_H_
#define _MMC_SD_H_		 

#include "mbed.h"

 						    	 
//the type of SD card
#define SD_TYPE_ERR     0X00
#define SD_TYPE_MMC     0X01
#define SD_TYPE_V1      0X02
#define SD_TYPE_V2      0X04
#define SD_TYPE_V2HC    0X06	   
//order of SD card    
#define CMD0    0       //card reset
#define CMD1    1
#define CMD8    8       //order8,SEND_IF_COND
#define CMD9    9       //order9,read CSD data
#define CMD10   10      //order10,read CID data
#define CMD12   12      //order12,stop data transfer
#define CMD16   16      //order16,set SectorSize ,ought to return 0x00
#define CMD17   17      //order17,read sector
#define CMD18   18      //order18,read Multi sector
#define CMD23   23      //order23,set multi setor erase N block before writting
#define CMD24   24      //order24,write sector
#define CMD25   25      //order25,write Multi sector
#define CMD41   41      //order41,should return 0x00
#define CMD55   55      //order55,should return 0x01
#define CMD58   58      //order58,read information of OCR 
#define CMD59   59      //order59,enable/disable CRC,should return 0x00
//the meaning of return data after writing
#define MSD_DATA_OK                0x05
#define MSD_DATA_CRC_ERROR         0x0B
#define MSD_DATA_WRITE_ERROR       0x0D
#define MSD_DATA_OTHER_ERROR       0xFF
//SD card respond sign
#define MSD_RESPONSE_NO_ERROR      0x00
#define MSD_IN_IDLE_STATE          0x01
#define MSD_ERASE_RESET            0x02
#define MSD_ILLEGAL_COMMAND        0x04
#define MSD_COM_CRC_ERROR          0x08
#define MSD_ERASE_SEQUENCE_ERROR   0x10
#define MSD_ADDRESS_ERROR          0x20
#define MSD_PARAMETER_ERROR        0x40
#define MSD_RESPONSE_FAILURE       0xFF
 							   						 	 

#define	SD_CS  PBout(2) //SD Card CS pin				    	  

extern u8  SD_Type;//SD card type



//functions
u8 SD_SPI_ReadWriteByte(u8 data);
void SD_SPI_SpeedLow(void);
void SD_SPI_SpeedHigh(void);
u8 SD_WaitReady(void);							//�ȴ�SD��׼��
u8 SD_GetResponse(u8 Response);					//������Ӧ
u8 SD_Initialize(void);							//��ʼ��
u8 SD_ReadDisk(u8*buf,u32 sector,u8 cnt);		//����
u8 SD_WriteDisk(u8*buf,u32 sector,u8 cnt);		//д��
u32 SD_GetSectorCount(void);   					//��������
u8 SD_GetCID(u8 *cid_data);                     //��SD��CID
u8 SD_GetCSD(u8 *csd_data);                     //��SD��CSD
 
#endif





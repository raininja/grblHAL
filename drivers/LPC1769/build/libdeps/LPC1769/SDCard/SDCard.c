#include "mbed.h"
#include "mmc_sd.h"			   
#include "spi.h"
#include "Serial.h"	

					   
uint8_t  SD_Type=0;//SD Type

//
//data:the data to write
//return:the data read back
uint8_t SD_SPI_ReadWriteByte(uint8_t data)
{
	return SPI_ReadWriteByte(data);
}	  

//SD Card should init in low speed
void SD_SPI_SpeedLow(void)
{
 	SPI_SetSpeed(SPI_SPEED_256);//set in low speed
}
//SD Card work normally
void SD_SPI_SpeedHigh(void)
{
 	SPI_SetSpeed(SPI_SPEED_2);//set in high speed
}
//SPI hardware Init
void SD_SPI_Init(void)
{
	SPI1_Init();
	DigitalOut(SD_CS,1);
}

///////////////////////////////////////////////////////////////////////////////////
//disable select ,release SPI BUS
void SD_DisSelect(void)
{
	SD_CS=1;
 	SD_SPI_ReadWriteByte(0xff);//provide extra 8 clock
}
//select sd card,waiting card ready
u8 SD_Select(void)
{
	SD_CS=0;
	if(SD_WaitReady()==0)return 0;//waiting success
	SD_DisSelect();
	return 1;/waiting failed
}
//waiting card ready
//return:0,ready;other,error code
u8 SD_WaitReady(void)
{
	uint32_t t=0;
	do
	{
		if(SD_SPI_ReadWriteByte(0XFF)==0XFF)return 0;//OK
		t++;		  	
	}while(t<0XFFFFFF);//wait
	return 1;
}
//get SD card total sectors num
//Response:0:get capacity error
//other:SD card capacity(sectors num/512 bytes)
//the num of byte of every sector must be 512,if ain't,the init can't pass
uint8_t SD_GetResponse(uint8_t Response)
{
	u16 Count=0xFFFF;//waiting num count						  
	while ((SD_SPI_ReadWriteByte(0XFF)!=Response)&&Count)Count--;//waiting for accurate respond
	if (Count==0)return MSD_RESPONSE_FAILURE;//response failure
	else return MSD_RESPONSE_NO_ERROR;//respond no error
}
//read a data package from SD card
//buf:block buffer cache
//len:length of data
//return:0 success;other failed
uint8_t SD_RecvData(uint8_t*buf,uint16_t len)
{			  	  
	if(SD_GetResponse(0xFE))return 1;//waiting SD card return start sign 0xfe
    while(len--)//start recieve data
    {
        *buf=SPI_ReadWriteByte(0xFF);
        buf++;
    }
    //two dummy CRC
    SD_SPI_ReadWriteByte(0xFF);
    SD_SPI_ReadWriteByte(0xFF);									  					    
    return 0;//readding success
}
//write a data package to SD card 512 byte
//buf:block buffer cache
//cmd:order
//retrun:0,success;1,failed
uint8_t SD_SendBlock(uint8_t*buf,uint8_t cmd)
{	
	u16 t;		  	  
	if(SD_WaitReady())return 1;//waiting ready failed
	SD_SPI_ReadWriteByte(cmd);
	if(cmd!=0XFD)//not endding order
	{
		for(t=0;t<512;t++)SPI2_ReadWriteByte(buf[t]);//add speed
	    SD_SPI_ReadWriteByte(0xFF);//ignore crc
	    SD_SPI_ReadWriteByte(0xFF);
		t=SD_SPI_ReadWriteByte(0xFF);//receive respond
		if((t&0x1F)!=0x05)return 2;//respond failure							  					    
	}						 									  					    
    return 0;//writing success
}

//write a order to sd card
//input: u8 cmd   order
//      u32 arg  order param
//      u8 crc   crc  check Value  
//return:SD card respond													  
uint8_t SD_SendCmd(uint8_t cmd, uint32_t arg, uint8_t crc)
{
    uint8_t r1;	
	uint8_t Retry=0; 
	SD_DisSelect();//disable last enable
	if(SD_Select())return 0XFF;//select failed
	//send
    SD_SPI_ReadWriteByte(cmd | 0x40);//write order
    SD_SPI_ReadWriteByte(arg >> 24);
    SD_SPI_ReadWriteByte(arg >> 16);
    SD_SPI_ReadWriteByte(arg >> 8);
    SD_SPI_ReadWriteByte(arg);	  
    SD_SPI_ReadWriteByte(crc); 
	if(cmd==CMD12)SD_SPI_ReadWriteByte(0xff);//Skip a stuff byte when stop reading
    //wait for respond or cvertime quit
	Retry=0X1F;
	do
	{
		r1=SD_SPI_ReadWriteByte(0xFF);
	}while((r1&0X80) && Retry--);	 
	//return state value
    return r1;
}		    																			  
//��ȡSD����CID��Ϣ��������������Ϣ
//����: u8 *cid_data(����CID���ڴ棬����16Byte��	  
//����ֵ:0��NO_ERR
//		 1������														   
uint8_t SD_GetCID(uint8_t *cid_data)
{
    uint8_t r1;	   
    //��CMD10�����CID
    r1=SD_SendCmd(CMD10,0,0x01);
    if(r1==0x00)
	{
		r1=SD_RecvData(cid_data,16);//����16���ֽڵ�����	 
    }
	SD_DisSelect();//ȡ��Ƭѡ
	if(r1)return 1;
	else return 0;
}																				  
//��ȡSD����CSD��Ϣ�������������ٶ���Ϣ
//����:u8 *cid_data(����CID���ڴ棬����16Byte��	    
//����ֵ:0��NO_ERR
//		 1������														   
uint8_t SD_GetCSD(uint8_t *csd_data)
{
    uint8_t r1;	 
    r1=SD_SendCmd(CMD9,0,0x01);//��CMD9�����CSD
    if(r1==0)
	{
    	r1=SD_RecvData(csd_data, 16);//����16���ֽڵ����� 
    }
	SD_DisSelect();//ȡ��Ƭѡ
	if(r1)return 1;
	else return 0;
}  
//��ȡSD����������������������   
//����ֵ:0�� ȡ�������� 
//       ����:SD��������(������/512�ֽ�)
//ÿ�������ֽ�����Ϊ512����Ϊ��������512������ʼ������ͨ��.														  
uint32_t SD_GetSectorCount(void)
{
    uint8_t csd[16];
    uint32_t Capacity;  
    uint8_t n;
	uint16_t csize;  					    
	//ȡCSD��Ϣ�������ڼ�����������0
    if(SD_GetCSD(csd)!=0) return 0;	    
    //����ΪSDHC�����������淽ʽ����
    if((csd[0]&0xC0)==0x40)	 //V2.00�Ŀ�
    {	
		csize = csd[9] + ((uint16_t)csd[8] << 8) + 1;
		Capacity = (u32)csize << 10;//�õ�������	 		   
    }else//V1.XX�Ŀ�
    {	
		n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
		csize = (csd[8] >> 6) + ((uint16_t)csd[7] << 2) + ((uint16_t)(csd[6] & 3) << 10) + 1;
		Capacity= (uint32_t)csize << (n - 9);//�õ�������   
    }
    return Capacity;
}
//��ʼ��SD��
uint8_t SD_Initialize(void)
{
    uint8_t r1;      // ����SD���ķ���ֵ
    uint16_t retry;  // �������г�ʱ����
    uint8_t buf[4];  
	uint16_t i;

	SD_SPI_Init();		//��ʼ��IO
 	SD_SPI_SpeedLow();	//���õ�����ģʽ 
 	for(i=0;i<10;i++)SD_SPI_ReadWriteByte(0XFF);//��������74������
	retry=20;
	do
	{
		r1=SD_SendCmd(CMD0,0,0x95);//����IDLE״̬
	}while((r1!=0X01) && retry--);
 	SD_Type=0;//Ĭ���޿�
	if(r1==0X01)
	{
		if(SD_SendCmd(CMD8,0x1AA,0x87)==1)//SD V2.0
		{
			for(i=0;i<4;i++)buf[i]=SD_SPI_ReadWriteByte(0XFF);	//Get trailing return value of R7 resp
			if(buf[2]==0X01&&buf[3]==0XAA)//���Ƿ�֧��2.7~3.6V
			{
				retry=0XFFFE;
				do
				{
					SD_SendCmd(CMD55,0,0X01);	//����CMD55
					r1=SD_SendCmd(CMD41,0x40000000,0X01);//����CMD41
				}while(r1&&retry--);
				if(retry&&SD_SendCmd(CMD58,0,0X01)==0)//����SD2.0���汾��ʼ
				{
					for(i=0;i<4;i++)buf[i]=SD_SPI_ReadWriteByte(0XFF);//�õ�OCRֵ
					if(buf[0]&0x40)SD_Type=SD_TYPE_V2HC;    //����CCS
					else SD_Type=SD_TYPE_V2;   
				}
			}
		}else//SD V1.x/ MMC	V3
		{
			SD_SendCmd(CMD55,0,0X01);		//����CMD55
			r1=SD_SendCmd(CMD41,0,0X01);	//����CMD41
			if(r1<=1)
			{		
				SD_Type=SD_TYPE_V1;
				retry=0XFFFE;
				do //�ȴ��˳�IDLEģʽ
				{
					SD_SendCmd(CMD55,0,0X01);	//����CMD55
					r1=SD_SendCmd(CMD41,0,0X01);//����CMD41
				}while(r1&&retry--);
			}else//MMC����֧��CMD55+CMD41ʶ��
			{
				SD_Type=SD_TYPE_MMC;//MMC V3
				retry=0XFFFE;
				do //�ȴ��˳�IDLEģʽ
				{											    
					r1=SD_SendCmd(CMD1,0,0X01);//����CMD1
				}while(r1&&retry--);  
			}
			if(retry==0||SD_SendCmd(CMD16,512,0X01)!=0)SD_Type=SD_TYPE_ERR;//�����Ŀ�
		}
	}
	SD_DisSelect();//ȡ��Ƭѡ
	SD_SPI_SpeedHigh();//����
	if(SD_Type)return 0;
	else if(r1)return r1; 	   
	return 0xaa;//��������
}
//��SD��
//buf:���ݻ�����
//sector:����
//cnt:������
//����ֵ:0,ok;����,ʧ��.
uint8_t SD_ReadDisk(uint8_t*buf,uint32_t sector,u8 cnt)
{
	uint8_t r1;
	if(SD_Type!=SD_TYPE_V2HC)sector <<= 9;//ת��Ϊ�ֽڵ�ַ
	if(cnt==1)
	{
		r1=SD_SendCmd(CMD17,sector,0X01);//������
		if(r1==0)//ָ��ͳɹ�
		{
			r1=SD_RecvData(buf,512);//����512���ֽ�	   
		}
	}else
	{
		r1=SD_SendCmd(CMD18,sector,0X01);//����������
		do
		{
			r1=SD_RecvData(buf,512);//����512���ֽ�	 
			buf+=512;  
		}while(--cnt && r1==0); 	
		SD_SendCmd(CMD12,0,0X01);	//����ֹͣ����
	}   
	SD_DisSelect();//ȡ��Ƭѡ
	return r1;//
}
//дSD��
//buf:���ݻ�����
//sector:��ʼ����
//cnt:������
//����ֵ:0,ok;����,ʧ��.
uint8_t SD_WriteDisk(uint8_t*buf,uint32_t sector,uint8_t cnt)
{
	uint8_t r1;
	if(SD_Type!=SD_TYPE_V2HC)sector *= 512;//ת��Ϊ�ֽڵ�ַ
	if(cnt==1)
	{
		r1=SD_SendCmd(CMD24,sector,0X01);//������
		if(r1==0)//ָ��ͳɹ�
		{
			r1=SD_SendBlock(buf,0xFE);//д512���ֽ�	   
		}
	}else
	{
		if(SD_Type!=SD_TYPE_MMC)
		{
			SD_SendCmd(CMD55,0,0X01);	
			SD_SendCmd(CMD23,cnt,0X01);//����ָ��	
		}
 		r1=SD_SendCmd(CMD25,sector,0X01);//����������
		if(r1==0)
		{
			do
			{
				r1=SD_SendBlock(buf,0xFC);//����512���ֽ�	 
				buf+=512;  
			}while(--cnt && r1==0);
			r1=SD_SendBlock(0,0xFD);//����512���ֽ� 
		}
	}   
	SD_DisSelect();//ȡ��Ƭѡ
	return r1;//
}	   
























	  







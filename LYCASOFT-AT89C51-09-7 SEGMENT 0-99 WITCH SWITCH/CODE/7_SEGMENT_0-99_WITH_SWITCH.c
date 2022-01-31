#include<reg51.h>

void T1_delay(int a)
{
	int i;
  for(i=0;i<a;i++)
  {
		TL1=0xFD;
    TH1=0x4B;
    TR1=1;
		while(TF1==0);
		TR1=0;
		TF1=0;
	}       
}

#define SEGMENT P2
void sdelay (char d)
{
	for(;d>0;d--);
}

sbit DIG1 = P3^0;
sbit DIG2 = P3^1;
sbit DIG3 = P3^2;
sbit DIG4 = P3^3;

sbit SW = P1^0;

#define ON  1
#define OFF 0

char Data[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0xff,0x67};			//comman cathode type;
//char Data[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};			//comman anode type;

int Count;



void Segment_Runner()
{
	int Disp1_Data,Disp2_Data,Disp3_Data,Disp4_Data;
	int Temp_DATA;
	
	Temp_DATA  = Count;						//6789;
	Disp1_Data = Temp_DATA % 10;	//Disp1=9;
	Temp_DATA  = Temp_DATA / 10;	//678;
	Disp2_Data = Temp_DATA % 10;	//Disp=8;
	Temp_DATA  = Temp_DATA / 10;	//67;
	Disp3_Data = Temp_DATA % 10;	//7;
	Disp4_Data = Temp_DATA / 10;
					
	DIG4=0; 
	SEGMENT = Data[Disp4_Data];
	//	T1_delay(7);
	sdelay(300);
	DIG4=1;

	DIG3=0; 
	SEGMENT = Data[Disp3_Data]; 
	//	T1_delay(7);
	sdelay(300);
	DIG3=1;
					
	DIG2=0; 
	SEGMENT = Data[Disp2_Data];
	//	T1_delay(7);
	sdelay(300);
	DIG2=1;

	DIG1=0; 
	SEGMENT = Data[Disp1_Data]; 
	//	T1_delay(7);
	sdelay(300);
	DIG1=1;
	//	T1_delay(20);
}

void main()
{
	P2 = 0x00;
	P3 = 0X00;
	P1 = 0X01;
	
	while(1)
	{
		while(SW==1)
		{
			Count++;
			if(Count>=10000)
			{
				Count=0;
			}
			while(SW==1);
		}
		Segment_Runner();
	}
}
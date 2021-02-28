#include <ADCTouch.h>
#include <SoftwareSerial.h>
SoftwareSerial Serial1(10, 11);
unsigned char order[4] = {0xAA,0x06,0x00,0xB0};
int ref0;
int threshold ;

void setup()
{
  int th = 550;
  Serial.begin(115200);
  Serial1.begin(9600);
  volume(0x1E);
  ref0 = ADCTouch.read(A0, 500); 
}


void loop()                    
{
 int total1 = ADCTouch.read(A0,10);  
 total1 -= ref0;
   
  if (total1 > 100 && total1  > threshold ) {
      play(0x01);
      delay(7000);
 Serial.println("1");
  }
}

void play(unsigned char Track)
{
unsigned char play[6] = {0xAA,0x07,0x02,0x00,Track,Track+0xB3};//0xB3=0xAA+0x07+0x02+0x00,即最后一位为校验和
Serial1.write(play,6);
}
void volume( unsigned char vol)
{
unsigned char volume[5] = {0xAA,0x13,0x01,vol,vol+0xBE};//0xBE=0xAA+0x13+0x01,即最后一位为校验和
Serial1.write(volume,5);
}
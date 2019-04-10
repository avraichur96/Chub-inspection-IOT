#include "HX711.h"  //load cell library 
 
#define DOUT  10 
#define CLK  9
 
HX711 scale(DOUT, CLK);
float calibration_factor = -727610; // This worked when I calibrated using calibrated weights  
 


int listenn=3,approach=4,call=0,p=0,count=0;
float wt[10]={0};
String drop,delayy;

int ir1=7,ir2=6,dela=1000;
int suc=16,hcyl=19,vcyla=17,vcylb=18;
int a=0;

void routine()
{
  call=1;
}


void setup()
{

pinMode(approach,OUTPUT);
pinMode(listenn,INPUT_PULLUP);

digitalWrite(approach,HIGH);

pinMode(13,OUTPUT);
Serial.begin(9600);
attachInterrupt(digitalPinToInterrupt(listenn),routine,FALLING);

pinMode(8,OUTPUT);
pinMode(11,OUTPUT);
digitalWrite(8,HIGH);
digitalWrite(11,LOW);
   
scale.tare();             //Reset the scale to 0  
scale.set_scale(calibration_factor); //Adjust to this calibration factor

// configure the pin directions   
pinMode(suc,OUTPUT);
pinMode(vcylb,OUTPUT);
pinMode(vcyla,OUTPUT);
pinMode(hcyl,OUTPUT);
digitalWrite(vcylb,HIGH);
digitalWrite(hcyl,HIGH);
digitalWrite(vcyla,HIGH);
digitalWrite(suc,HIGH);
pinMode(ir1,INPUT_PULLUP);
pinMode(ir2,INPUT_PULLUP);
count=0;
}

void loop()
{
String  ip_command="";

if(!digitalRead(ir2)&& !digitalRead(ir1))
{
  count=1;
}
if(count == 1)
{
count = 0;
digitalWrite(suc,LOW);
down();
delay(1400);
stopp();
delay(100);
up();
delay(2000);
stopp();
digitalWrite(19,LOW);
delay(3000);
digitalWrite(suc,HIGH);
delay(6000);  

wt[a]= scale.get_units();
wt[a]= scale.get_units();
wt[a]= scale.get_units();
wt[a]= 1000*scale.get_units();
Serial.println(wt[a]);
a++;
if(a>=9)
{
  a=0;
}

digitalWrite(19,HIGH);
delay(3000);
}


if(call == 1)
{
  char temp;
  call=0;
  delay(100);
  temp = Serial.read();
if(temp == 'A')
  {
delayy = Serial.readStringUntil('N');
drop = Serial.readStringUntil('O');
digitalWrite(approach,HIGH);
}
if(temp = 'P')
  {
digitalWrite(approach,LOW);
delay(30);
kaka = wt[p];
kaka+= "N";
p++;
if(p >= 9 )
{
  p=0;
}
Serial.print(kaka);
digitalWrite(approach,HIGH);
  }
}
}



void down()
{
digitalWrite(vcyla,LOW);
digitalWrite(vcylb,HIGH);
return;
}


void up()
{
digitalWrite(vcyla,HIGH);
digitalWrite(vcylb,LOW);
return;
}


void stopp()
{
digitalWrite(vcyla,HIGH);
digitalWrite(vcylb,HIGH);
return;
}


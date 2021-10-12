
#include <TinyWireM.h>
#include <Tiny4kOLED.h>


#include "font16x32digits.h"


uint8_t width = 64;
uint8_t height = 32;

const uint8_t bpm[] PROGMEM ={0b10000000,0b00111100,0b00000001};


void setup() {
  
  pinMode(4,INPUT_PULLUP);
  pinMode(1,INPUT_PULLUP);
  pinMode(3,OUTPUT);
  oled.begin(width, height, sizeof(tiny4koled_init_64x32br), tiny4koled_init_64x32br);
 
  oled.clear();
  oled.on();

  // Switch the half of RAM that we are writing to, to be the half that is non currently displayed
  oled.switchRenderFrame();
}
int minutes=2;
int seconds=0;
int fase=0;
int chosen=0;
int times[]={2,5,10,15};
int ani=14;

int debounce4=0;
int debounce1=0;
void loop() {

  if(fase==0 || fase==3){
  if(digitalRead(4)==0)
  {
    if(debounce4==0)
      {
      debounce4=1;
      chosen++;
      if(chosen>3)
      chosen=0;
      if(fase==3)
      fase=0;
      }
    }else{debounce4=0;}

    if(digitalRead(1)==0)
    {
    if(debounce1==0)
      {
      debounce1=1;
      minutes=times[chosen];
      fase=1;
      if(fase==3)
      fase=0;
      }
    }else{debounce1=0;}}

  if(fase==1 || fase==2){
 
  delay(1000);
  seconds--;
  if(seconds<=0)
    {
    seconds=59;
    minutes--;
    }}

  if(fase==3)
    {
      digitalWrite(3,1);
      delay(500);
      digitalWrite(3,0);
      delay(500);
      }

   if(minutes==0)
   fase=2;
   if(minutes==-1)
   fase=3;
   
   updateDisplay();
}

void updateDisplay() {

  oled.clear();

  if(fase==0)
     {
      oled.setFont(FONT6X8P);
      oled.setCursor(0, 0);
      oled.print(" SET TIME:");
      oled.setCursor(0, 1);
      oled.print("----------");
      oled.setCursor(0, 2);
      for(int i=0;i<4;i++) 
        {
           oled.print(" ");
           oled.print(times[i]);
        }
        if(chosen>1)
        oled.setCursor(11+chosen*11, 3);
        else
        oled.setCursor(6+chosen*12, 3);
        oled.print("^");
      }

  if(fase==1){
   oled.setFont(FONT6X8P);
   oled.setCursor(8, 0);
   oled.print("TIME:");
   oled.setFont(FONT8X16P);
 
  
  oled.setCursor(8, 1);
 if(minutes<10)
 oled.print(0);
 oled.print(minutes);
 oled.print(" : ");
  if(seconds<10)
 oled.print(0);
 oled.print(seconds);
 oled.setFont(FONT6X8P);
 oled.setCursor(8, 3);
  for(int i=ani;i>0;i--)
  { 
    oled.print(".");
           
  }
     ani--;
     if(ani==0)
     ani=14;
  }

  if(fase==2)
  {
    oled.setFont(FONT16X32DIGITS);
    oled.setCursor(8, 0);
    oled.print(seconds);
  }
  
  oled.switchFrame();
}

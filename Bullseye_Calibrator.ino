// Calibrator for Othernet Bullseye LNB
// Written by Colin Durbridge G4EML for an Arduino Nano. However it should work on any Arduino. 
// Based on data supplied by SY Science and Technology and Othernet. Thanks to Jon and Syed.
//
// This program allows the LO of the Bullseye LNB to be adjusted in steps of approximately 200Hz.
// Three pushbuttons, connected between Arduino pins and ground, are used. Plus, Minus and Save.
// Pressing the Plus or Minus buttons moves the LO by one step in either direction. Holding the button down results in 10 steps per second. 
// Pressing the Save button stores this new calibration as the user setting which will then be used every time the LNB is powered up. 
// Pressing all three buttons together will restore the factory calibration. 
//
// Single character commands can also be sent from a PC connected to the Arduino USB Serial port. Settings are 9600 8,N,1 
// Valid commands are as follows. 
// 
// Q = Decrement by 1    W = Increment by 1    D = Min Frequency
// A = Decrement by 4    S = Increment by 4    E = Max Frequency
// Z = Decrement by 10   X = Increment by 10   C = Mid Frequency
//
// U = Store User Frequency in Memory
// M = Recall User Frequency from Memory
// P = Restore Factory Frequency from Memory
//
// The LNB must be powered up as normal through the Green Port. The serial output of the Arduino on pin 2 must be level shifted with an external circuit to 0-15V (±1V)and connected via a 1K resistor to the Red Port. 
//


#include <SoftwareSerial.h>

SoftwareSerial LNBSerial(3, 2); // RX on Arduino pin 3 (Not Used) , TX on Arduino Pin 2 (Level shifted and connected to Red Port of LNB)

char valid[]="ACDEMPQSUWXZ";    //Valid commands for Bullseye LNB. WARNING! Do not try other commands, they may corrupt the settings)
char inChar[]="#";
int debounce;
int repeatDelay;
int ledDelay;
int buttons;
enum {NONE,PLUS,MINUS,PLUSMINUS,SAVE,PLUSSAVE,MINUSSAVE,ALL};
unsigned long lastTick;
char factoryReset;

#define PLUSBUT 4                  //pin for Plus Button (connect a push botton between this Arduino pin and Ground)
#define SAVEBUT 5                  //pin for Save Button (connect a push botton between this Arduino pin and Ground)
#define MINUSBUT 6                 //pin for Minus Button (connect a push botton between this Arduino pin and Ground)

void setup() 
{
  // initialize Hardware serial port to PC
  Serial.begin(9600);
  //initialise Software Serial port to LNB
  LNBSerial.begin(9600);

  pinMode(PLUSBUT,INPUT_PULLUP);
  pinMode(SAVEBUT,INPUT_PULLUP);
  pinMode(MINUSBUT,INPUT_PULLUP);
  pinMode(LED_BUILTIN,OUTPUT);

  debounce=0;
  repeatDelay=0;
  ledDelay=0;
  lastTick=millis();
  factoryReset=0;
  
}

void loop() 
{
  
// read from PC if available and send to LNB

  if (Serial.available())            //Have we received a character from the PC?
  {
    inChar[0] = Serial.read();       //Get the character from the PC
    if(strpbrk(inChar,valid))        //Test if that Character is a valid command
    {
      digitalWrite(LED_BUILTIN,1);
      ledDelay=10;
      repeatDelay=10;
      LNBSerial.write(inChar[0]);    //Send the character to the LNB
    }

  }

//Read Buttons and combine into one variable

  buttons = NONE;
  if(digitalRead(PLUSBUT)==LOW) buttons = buttons + PLUS;
  if(digitalRead(MINUSBUT)==LOW) buttons = buttons + MINUS;
  if(digitalRead(SAVEBUT)==LOW) buttons = buttons + SAVE;

  switch (buttons)
   {
    case NONE:
      repeatDelay=100;
      break;

    case PLUS:
      if((debounce==0) | (repeatDelay==0))
        {
           LNBSerial.write("W");
           digitalWrite(LED_BUILTIN,1);
           ledDelay=10;
           if(repeatDelay==0) repeatDelay=10;
        }
      if(debounce<20) debounce=20;
      break;
    
    case MINUS:
      if((debounce==0) | (repeatDelay==0))
        {
           LNBSerial.write("Q");
           digitalWrite(LED_BUILTIN,1);
           ledDelay=10;
           if(repeatDelay==0) repeatDelay=10;
        }
      if(debounce<20) debounce=20;
      break;
   
    case SAVE:
      if(debounce==0) 
      {
        LNBSerial.write("U");
        digitalWrite(LED_BUILTIN,1);
        ledDelay=10;
      }
      if (debounce<20) debounce=20; 
      break;

      case ALL:
      factoryReset=1;
      digitalWrite(LED_BUILTIN,1);
      ledDelay=10;
      debounce=100;    
      break;  
   }


//Send factory reset if requested

   if((factoryReset==1) & (debounce==0))
   {
     LNBSerial.write("P");
     factoryReset=0;
     for(int c=0;c<6;c++)
     {
      digitalWrite(LED_BUILTIN,1);
      delay(100);
      digitalWrite(LED_BUILTIN,0);
      delay(100);
     }
   }


//Do this every 10 ms to implement delays.

  if(millis()>=lastTick+10)
    {
      lastTick=millis();
      if(repeatDelay>0)
        {
          repeatDelay=repeatDelay-1;
        }
      if(debounce>0)
        {
          debounce=debounce-1;
        }
      if(ledDelay>0)
        {
          ledDelay=ledDelay-1;
        }
      else
        {
          digitalWrite(LED_BUILTIN,0);
        }
    }



}

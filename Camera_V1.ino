//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//
// This sketch is a good place to start if you're just getting started with 
// Pixy and Arduino.  This program simply prints the detected object blocks 
// (including color codes) through the serial console.  It uses the Arduino's 
// ICSP port.  For more information go here:
//
// http://cmucam.org/projects/cmucam5/wiki/Hooking_up_Pixy_to_a_Microcontroller_(like_an_Arduino)
//
// It prints the detected blocks once per second because printing all of the 
// blocks for all 50 frames per second would overwhelm the Arduino's serial port.
//
   
#include <SPI.h>  
#include <Pixy.h>

// This is the main Pixy object 
Pixy pixy;

void setup()
{
  Serial.begin(9600);
  Serial.print("Starting...\n");

  pixy.init();
}

void loop()
{ 
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32]; 
  int pos[7];
  int tol = 7;
  int x,y, sig;
  
  // grab blocks!
  blocks = pixy.getBlocks();
  
  // If there are detect blocks, print them!
  if (blocks)
  {
    i++;
    
    // do this (print) every 50 frames because printing every
    // frame would bog down the Arduino
    if (i%50==0)
    {
      for(int n = 0; n<7; n++){
          pos[n] = 0;
          
        }

      
      sprintf(buf, "Detected %d:\n", blocks);
      Serial.print(buf);
      for (j=0; j<blocks; j++)
      {

        
        x = pixy.blocks[j].x;
        y = pixy.blocks[j].y;
        sig = pixy.blocks[j].signature;

        

        
        //sig 1 = purple, sig 2 = white, sig 3 = green
        if(sig == 1){
          if(x > 138 - tol && x < 138 + tol && y > 164 - tol && y < 164 + tol){
              pos[5] = 1;
              Serial.print("1OK ");
          }
          if(x > 187 - tol && x < 187 + tol && y > 108 - tol && y < 108 + tol){
              pos[3] = 1;
              Serial.print("2OK ");
          }
          
        }

        if(sig == 2){
          if(x > 235 - tol && x < 235 + tol && y > 153 - tol && y < 153 + tol){
              pos[6] = 2;
              Serial.print("3OK ");
          }
        }
        Serial.print(sig, '\n');



        
        sprintf(buf, "  block %d: ", j);
        Serial.print(buf); 
        pixy.blocks[j].print();

        if(pos[3] == 1 && pos[5] == 1 && pos[6] == 2){
          Serial.print("Kombinacija 3 \n");
          
        }
        
      }
    }
  }  
}


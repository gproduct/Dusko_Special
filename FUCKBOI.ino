#include <SPI.h>  
#include <Pixy.h>

// This is the main Pixy object 
Pixy pixy;

void setup()
{
  Serial.begin(9600);
  Serial.print("Starting... \n");

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

      
//      Serial.print(buf);
      for (j=0; j<blocks; j++)
      {

        
        x = pixy.blocks[j].x;
        y = pixy.blocks[j].y;
        sig = pixy.blocks[j].signature;

        

        
        //sig 1 = purple, sig 2 = white, sig 3 = green


          if(x > 35 - tol && x < 35 + tol && y > 25 - tol && y < 25 + tol){
              pos[1] = sig;
             // Serial.print("1OK ");
          }


          if(x > 153 - tol && x < 153 + tol && y > 56 - tol && y < 56 + tol){
              pos[2] = sig;
              //Serial.print("2OK ");
          }

          if(x > 300 - tol && x < 300 + tol && y > 144 - tol && y < 144 + tol){
              pos[3] = sig;
             // Serial.print("3OK ");
          }


          if(x > 241 - tol && x < 241 + tol && y > 26 - tol && y < 26 + tol){
              pos[4] = sig;
              //Serial.print("4OK ");
          }

          
          
        }

        if(pos[1] == 3 && pos[2] == 1){
        Serial.println("Kombinacija 1");
        }

        if(pos[1] == 1 && pos[2] == 1){
        Serial.println("Kombinacija 2");
        }

        if(pos[1] == 1 && pos[3] == 1 && pos[4] == 2){
        Serial.println("Kombinacija 3");
        }

        if(pos[1] == 2 && pos[3] == 1 && pos[4] == 2){
        Serial.println("Kombinacija 4");
        }

        if(pos[3] == 1 && pos[4] == 3){
        Serial.println("Kombinacija 5");
        }
        /*
        Serial.print(sig, '\n');   
        sprintf(buf, "  block %d: ", j);
        Serial.print(buf); 
        pixy.blocks[j].print();
        */
        /*
        Serial.print(" Pos1:");
        Serial.print(pos[1]);
        Serial.print(" Pos2:");
        Serial.print(pos[2]);
        Serial.print(" Pos3:");
        Serial.print(pos[3]);
        Serial.print(" Pos4:");
        Serial.print(pos[4]);
        Serial.print(" Pos5:");
        Serial.print(pos[5]);
        Serial.print(" Pos6:");
        Serial.print(pos[6]);
        Serial.print("\n");
        
        if(pos[3] == 1 && pos[5] == 1 && pos[6] == 2){
          Serial.print("Kombinacija 3 \n");
          }
          */
          
        
        
      }
    }
  }

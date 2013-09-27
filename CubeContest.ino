//Rainbowduino Contest 

#include <Rainbowduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

int cubeMap[64][3] = {
 
  {0,0,0},{0,0,1},{0,0,2},{0,0,3},
  {0,1,0},{0,1,1},{0,1,2},{0,1,3},
  {0,2,0},{0,2,1},{0,2,2},{0,2,3},
  {0,3,0},{0,3,1},{0,3,2},{0,3,3},
  {1,0,0},{1,0,1},{1,0,2},{1,0,3},
  {1,1,0},{1,1,1},{1,1,2},{1,1,3},
  {1,2,0},{1,2,1},{1,2,2},{1,2,3},
  {1,3,0},{1,3,1},{1,3,2},{1,3,3},
  {2,0,0},{2,0,1},{2,0,2},{2,0,3},
  {2,1,0},{2,1,1},{2,1,2},{2,1,3},
  {2,2,0},{2,2,1},{2,2,2},{2,2,3},
  {2,3,0},{2,3,1},{2,3,2},{2,3,3},
  {3,0,0},{3,0,1},{3,0,2},{3,0,3},
  {3,1,0},{3,1,1},{3,1,2},{3,1,3},
  {3,2,0},{3,2,1},{3,2,2},{3,2,3},
  {3,3,0},{3,3,1},{3,3,2},{3,3,3},
};

unsigned int x,y,z;

int tweetCount;
int ledPos;

byte colorPalette[4] = {0x00FFFF, 0xFF6633, 0xCC33CC,0x0000FF};
int curCol;

int pinVal = 0;

unsigned int starttime;
unsigned int endtime;

boolean shouldAdd;

byte color;

void setup()
{
  color = colorPalette[curCol++];
  x,y,z = 0;
  ledPos = 0;
  tweetCount = 0;
  Serial.begin(9600);
  Rb.init();
  Wire.begin();
}

void loop(){ 
  while (Serial.available() > 0) {
    if (Serial.read()=='1'){
      shouldAdd = true;
      Serial.println("Added!");
      iterateCube();
    }
  }
}

void newColor(){
  color = random(0xFF);
}

void iterateCube(){
  tweetCount++;
  if (ledPos < 63){
    Rb.setPixelZXY(cubeMap[ledPos][0],cubeMap[ledPos][1], cubeMap[ledPos][2],color,color,color);
    ledPos++;
  }
  else{
   celebrate();
  }
}
void celebrate(){
  starttime = millis();
  endtime = starttime;
  
  while((endtime - starttime) <= 1000){
   for(x=0;x<4;x++)  
    {
     for(y=0;y<4;y++)  
     {
      for(z=0;z<4;z++)
        {
         Rb.setPixelZXY(z,x,y,random(0xFF),random(0xFF),random(0xFF)); //uses R, G and B color bytes
        }
     }
   }
   endtime = millis();
  } 
  Rb.blankDisplay();
   newColor();
   ledPos = 0;
}

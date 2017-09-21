/*
 Name:    projectv2.ino
 Created: 3/13/2016 1:45:38 PM
 Author:   John Sader
 Comments: Available for non-commercial use, just ask. :)
           Uses functions provided in the libraries. 
*/

#include <Adafruit_Fingerprint.h>
#include <Adafruit_SleepyDog.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_ILI9341.h>
#include <SoftwareSerial.h>
#include <Adafruit_STMPE610.h>
#include <Adafruit_GFX.h>

SoftwareSerial mySerial(2,3);	//Pin 2 is IN from fingerprint sensor (Green)
				//Pin 3 is out from arduino (white)

#define TS_MINX 150
#define TS_MINY 130 //130
#define TS_MAXX 3800 //3800
#define TS_MAXY 4000 //4000
#define STMPE_CS 8
#define TFT_CS 10
#define TFT_DC 9

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

bool flag1=false;
bool menuflag=false;
int id=-1;
uint8_t ID;

int ledpin = 4;
int lkpin = 7;

// the setup function runs once when you press reset or power the board
void setup() 
{
  Serial.begin(9600);
  finger.begin(57600);
  tft.begin();
  ts.begin();
  pinMode(ledpin,OUTPUT);
  pinMode(lkpin,OUTPUT);
  Watchdog.enable(10000);
  drawStandby(); // Draws waiting screen on tft display
}
void(* resetFunc) (void) = 0;

// the loop function runs over and over again until power down or reset
void loop() 
{
 
  curState(flag1,id);
  curUser(id,menuflag);
  delay(2000);
}

void curUser(int thisid, bool menuFlag)
{
  bool flag2=true;
  if((thisid == 0) && (menuFlag == false)) //Checks if admin menu is drawn, otherwise draws admin menu
  {
    drawMenu();
    menuflag=true;
    curUser(thisid,menuflag);
    Watchdog.reset();
  }
  if((thisid == 0) && (menuFlag == true))
  {
    digitalWrite(lkpin,HIGH);
    digitalWrite(ledpin,HIGH);
    flag2=false;
    do
    {
      if(!ts.bufferEmpty())
      {
        TS_Point p= ts.getPoint();
        p.x = map(p.x, TS_MINY, TS_MAXY, 0, tft.height());
        p.y = map(p.y, TS_MINX, TS_MAXX, 0, tft.width());
        int y = tft.height() - p.x;
        int x = p.y;
        if(ts.touched())
        {
          p=ts.getPoint();
          while(!ts.bufferEmpty())
          {
            p=ts.getPoint();
          }
          p.x = map(p.x, TS_MINY, TS_MAXY, 0, tft.height());
          p.y = map(p.y, TS_MINX, TS_MAXX, 0, tft.width());
          y = tft.height() - p.x;
          x = p.y;
          if((x >10) && (x <110))
            {
              if((y > 80) && (y < 130)) //Touch data on "add user" button
              {
               digitalWrite(lkpin,LOW);
               digitalWrite(ledpin,LOW);
               //call Keypad
               drawKeypad();
               returnID();
               Watchdog.reset();
              }
            }
          if((x > 200) && (x <250)) // Touch data on "resume" button
            {
              if((y > 80) && (y <= 130))
              {
              digitalWrite(lkpin,LOW);
              digitalWrite(ledpin,LOW);
                resetFunc();
              }
            }

            if((x >10) && (x <160)) //Touch data on "delete user" button
            {
              if((y > 160) && (y < 210))
              {
               digitalWrite(lkpin,LOW);
               digitalWrite(ledpin,LOW);
               //call Keypad
               drawKeypad();
               DeleteID();
               Watchdog.reset();
              }
            }
        }
      }
    //Watchdog.reset();
    }while(!flag2);
  }
 
  //USERS 1-9 Welcome Screen
  if((thisid==1))
  {
    //UNLOCK, Display Welcome
    tft.fillScreen(ILI9341_BLUE);
    tft.setRotation(1);
    drawFrame();
    tft.setCursor(50,25);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(2); 
    tft.println("Access Granted!");
    digitalWrite(lkpin,HIGH);
    digitalWrite(ledpin,HIGH);
    delay(3000);
    Watchdog.reset();
    drawFrame();
    tft.setCursor(20,25);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(2); 
    tft.println("WELCOME!");
    delay(3000);
    Watchdog.reset();
    digitalWrite(lkpin,LOW);
    digitalWrite(ledpin,LOW);
    flag1 = false;
    drawStandby();
    menuFlag=false;
    menuflag=false;
    flag2=true;
    id = -1;
    Serial.println(id);
    }

   if((thisid==2))
  {
    //UNLOCK, Display Welcome
    tft.fillScreen(ILI9341_BLUE);
    tft.setRotation(1);
    drawFrame();
    tft.setCursor(50,25);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(2); 
    tft.println("Access Granted!");
    digitalWrite(lkpin,HIGH);
    digitalWrite(ledpin,HIGH);
    delay(3000);
    Watchdog.reset();
    drawFrame();
    tft.setCursor(20,25);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(2); 
    tft.println("WELCOME!");
    delay(3000);
    Watchdog.reset();
    digitalWrite(lkpin,LOW);
    digitalWrite(ledpin,LOW);
    flag1 = false;
    drawStandby();
    menuFlag=false;
    menuflag=false;
    flag2=true;
    id = -1;
    Serial.println(id);
    } 

   if((thisid==3))
  {
    //UNLOCK, Display Welcome
    tft.fillScreen(ILI9341_BLUE);
    tft.setRotation(1);
    drawFrame();
    tft.setCursor(50,25);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(2); 
    tft.println("Access Granted!");
    digitalWrite(lkpin,HIGH);
    digitalWrite(ledpin,HIGH);
    delay(3000);
    Watchdog.reset();
    drawFrame();
    tft.setCursor(20,25);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(2); 
    tft.println("WELCOME!");
    delay(3000);
    Watchdog.reset();
    digitalWrite(lkpin,LOW);
    digitalWrite(ledpin,LOW);
    flag1 = false;
    drawStandby();
    menuFlag=false;
    menuflag=false;
    flag2=true;
    id = -1;
    Serial.println(id);
    }

    if((thisid==4))
  {
    //UNLOCK, Display Welcome
    tft.fillScreen(ILI9341_BLUE);
    tft.setRotation(1);
    drawFrame();
    tft.setCursor(50,25);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(2); 
    tft.println("Access Granted!");
    digitalWrite(lkpin,HIGH);
    digitalWrite(ledpin,HIGH);
    delay(3000);
    Watchdog.reset();
    drawFrame();
    tft.setCursor(20,25);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(2); 
    tft.println("WELCOME!");
    delay(3000);
    Watchdog.reset();
    digitalWrite(lkpin,LOW);
    digitalWrite(ledpin,LOW);
    flag1 = false;
    drawStandby();
    menuFlag=false;
    menuflag=false;
    flag2=true;
    id = -1;
    Serial.println(id);
    }

    if((thisid==5))
  {
    //UNLOCK, Display Welcome
    tft.fillScreen(ILI9341_BLUE);
    tft.setRotation(1);
    drawFrame();
    tft.setCursor(50,25);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(2); 
    tft.println("Access Granted!");
    digitalWrite(lkpin,HIGH);
    digitalWrite(ledpin,HIGH);
    delay(3000);
    Watchdog.reset();
    drawFrame();
    tft.setCursor(20,25);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(2); 
    tft.println("WELCOME!");
    delay(3000);
    Watchdog.reset();
    digitalWrite(lkpin,LOW);
    digitalWrite(ledpin,LOW);
    flag1 = false;
    drawStandby();
    menuFlag=false;
    menuflag=false;
    flag2=true;
    id = -1;
    Serial.println(id);
    }

   if((thisid==6))
  {
    //UNLOCK, Display Welcome
    tft.fillScreen(ILI9341_BLUE);
    tft.setRotation(1);
    drawFrame();
    tft.setCursor(50,25);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(2); 
    tft.println("Access Granted!");
    digitalWrite(lkpin,HIGH);
    digitalWrite(ledpin,HIGH);
    delay(3000);
    Watchdog.reset();
    drawFrame();
    tft.setCursor(20,25);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(2); 
    tft.println("WELCOME!");
    delay(3000);
    Watchdog.reset();
    digitalWrite(lkpin,LOW);
    digitalWrite(ledpin,LOW);
    flag1 = false;
    drawStandby();
    menuFlag=false;
    menuflag=false;
    flag2=true;
    id = -1;
    Serial.println(id);
    }

    if((thisid==7))
  {
    //UNLOCK, Display Welcome
    tft.fillScreen(ILI9341_BLUE);
    tft.setRotation(1);
    drawFrame();
    tft.setCursor(50,25);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(2); 
    tft.println("Access Granted!");
    digitalWrite(lkpin,HIGH);
    digitalWrite(ledpin,HIGH);
    delay(3000);
    Watchdog.reset();
    drawFrame();
    tft.setCursor(20,25);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(2); 
    tft.println("WELCOME!");
    delay(3000);
    Watchdog.reset();
    digitalWrite(lkpin,LOW);
    digitalWrite(ledpin,LOW);
    flag1 = false;
    drawStandby();
    menuFlag=false;
    menuflag=false;
    flag2=true;
    id = -1;
    Serial.println(id);
    }

    if((thisid==8))
  {
    //UNLOCK, Display Welcome
    tft.fillScreen(ILI9341_BLUE);
    tft.setRotation(1);
    drawFrame();
    tft.setCursor(50,25);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(2); 
    tft.println("Access Granted!");
    digitalWrite(lkpin,HIGH);
    digitalWrite(ledpin,HIGH);
    delay(3000);
    Watchdog.reset();
    drawFrame();
    tft.setCursor(20,25);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(2); 
    tft.println("WELCOME!");
    delay(3000);
    Watchdog.reset();
    digitalWrite(lkpin,LOW);
    digitalWrite(ledpin,LOW);
    flag1 = false;
    drawStandby();
    menuFlag=false;
    menuflag=false;
    flag2=true;
    id = -1;
    Serial.println(id);
    }

    if((thisid==9))
  {
    //UNLOCK, Display Welcome
    tft.fillScreen(ILI9341_BLUE);
    tft.setRotation(1);
    drawFrame();
    tft.setCursor(50,25);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(2); 
    tft.println("Access Granted!");
    digitalWrite(lkpin,HIGH);
    digitalWrite(ledpin,HIGH);
    delay(3000);
    Watchdog.reset();
    drawFrame();
    tft.setCursor(20,25);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(2); 
    tft.println("WELCOME!");
    delay(3000);
    Watchdog.reset();    
    digitalWrite(lkpin,LOW);
    digitalWrite(ledpin,LOW);
    flag1 = false;
    drawStandby();
    menuFlag=false;
    menuflag=false;
    flag2=true;
    id = -1;
    Serial.println(id);
    }  
}

void curState(bool flag,int thisid)
{

  delay(250);
  if((!flag) && (thisid==-1))
  {
    Serial.print("Scan: ");
    int thisid = getFingerprintIDez();
    Serial.println(thisid);
    if((thisid==0))
      {
        flag1=true;
        Serial.println(thisid);  
        Watchdog.reset();
        id = thisid;
      }
      else if((thisid==1))
      {
        flag1=true;
        Serial.println(thisid);  
        Watchdog.reset();
        id = thisid;
      }

      else if((thisid==2))
      {
        flag1=true;
        Serial.println(thisid);  
        Watchdog.reset();
        id = thisid;
      }

      else if((thisid==3))
      {
        flag1=true;
        Serial.println(thisid);  
        Watchdog.reset();
        id = thisid;
      }

      else if((thisid==4))
      {
        flag1=true;
        Serial.println(thisid);  
        Watchdog.reset();
        id = thisid;
      }

      else if((thisid==5))
      {
        flag1=true;
        Serial.println(thisid);  
        Watchdog.reset();
        id = thisid;
      }

      else if((thisid==6))
      {
        flag1=true;
        Serial.println(thisid);  
        Watchdog.reset();
        id = thisid;
      }

      else if((thisid==7))
      {
        flag1=true;
        Serial.println(thisid);  
        Watchdog.reset();
        id = thisid;
      }

      else if((thisid==8))
      {
        flag1=true;
        Serial.println(thisid);  
        Watchdog.reset();
        id = thisid;
      }

      else if((thisid==9))
      {
        flag1=true;
        Serial.println(thisid);  
        Watchdog.reset();
        id = thisid;
      }
  }
  else
  {
    thisid = -1;
    Serial.print("curState else return id: ");
    Serial.println(thisid);
  id = thisid;
  Watchdog.reset();
  }
}

void returnID()
{
  Watchdog.reset();
  bool doflag = true;
  do{
  if(!ts.bufferEmpty()){  
  if (ts.touched())
  {   
    Serial.println("touched");
    TS_Point p=ts.getPoint();
    Watchdog.reset();
    while(!ts.bufferEmpty())
    {
      p=ts.getPoint();
      Watchdog.reset();
      } 
    // Scale using the calibration #'s
    // and rotate coordinate system
    p.x = map(p.x, TS_MINY, TS_MAXY, 0, tft.height());
    p.y = map(p.y, TS_MINX, TS_MAXX, 0, tft.width());
    int y = tft.height() - p.x;
    //int y = p.x;
    int x = p.y;
    Serial.println(x);
    Serial.println(y);
    Watchdog.reset();
  if((x > 10) && (x < 60)) 
      {
        if ((y > 60) && (y <= 110)) 
        {
          tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println(" Setting ID: 1");
          getFingerprintEnroll(1);
          doflag=false;
          drawFrame();
          tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println("Enrolled!");
          delay(1000);
          flag1 = false;
          menuflag=false;
          id = -1;
          resetFunc();
          break; 
        }
      }
   if((x > 100) && (x < 150))
   {
      if((y > 60) && (y < 110))
      {
        tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println(" Setting ID: 2");
          getFingerprintEnroll(2);
          doflag=false;
          drawFrame();
          tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println("Enrolled!");
          delay(1000);
          flag1 = false;
          menuflag=false;
          id = -1;
          resetFunc();
          break;
           
       }
    }

   if((x > 190) && (x < 240))
   {
      if((y > 60) && (y < 110))
      {
        tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println(" Setting ID: 3");
          getFingerprintEnroll(3);
          doflag=false;
          drawFrame();
          tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println("Enrolled!");
          delay(1000);
          flag1 = false;
          menuflag=false;
          id = -1;
          resetFunc();
          break; 
       }
    }

    if((x > 10) && (x < 60))
   {
      if((y > 120) && (y < 170))
      {
        tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println(" Setting ID: 4");
          getFingerprintEnroll(4);
          doflag=false;
          drawFrame();
          tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println("Enrolled!");
          delay(1000);
          flag1 = false;
          menuflag=false;
          id = -1;
          resetFunc();
          break; 
       }
    }

    if((x > 100) && (x < 150))
   {
      if((y > 120) && (y < 170))
      {
        tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println(" Setting ID: 5");
          getFingerprintEnroll(5);
          doflag=false;
          drawFrame();
          tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println("Enrolled!");
          delay(1000);
          flag1 = false;
          menuflag=false;
          id = -1;
          resetFunc();
          break; 
       }
    }

    if((x > 190) && (x < 240))
   {
      if((y > 120) && (y < 170))
      {
        tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println(" Setting ID: 6");
          getFingerprintEnroll(6);
          doflag=false;
          drawFrame();
          tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println("Enrolled!");
          delay(1000);
          flag1 = false;
          menuflag=false;
          id = -1;
          resetFunc();
          break; 
       }
    }

    if((x > 10) && (x < 60))
   {
      if((y > 180) && (y < 230))
      {
        tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println(" Setting ID: 7");
          getFingerprintEnroll(7);
          doflag=false;
          drawFrame();
          tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println("Enrolled!");
          delay(1000);
          flag1 = false;
          menuflag=false;
          id = -1;
          resetFunc();
          break; 
       }
    }

    if((x > 100) && (x < 150))
   {
      if((y > 180) && (y < 230))
      {
        tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println(" Setting ID: 8");
          getFingerprintEnroll(8);
          doflag=false;
          drawFrame();
          tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println("Enrolled!");
          delay(1000);
          flag1 = false;
          menuflag=false;
          id = -1;
          resetFunc();
          break; 
       }
    }

    if((x > 190) && (x < 240))
   {
      if((y > 180) && (y < 230))
      {
        tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println(" Setting ID: 9");
          getFingerprintEnroll(9);
          doflag=false;
          drawFrame();
          tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println("Enrolled!");
          delay(1000);
          flag1 = false;
          menuflag=false;
          id = -1;
          resetFunc();
          break; 
       }
    }
}
}
  }while(doflag);
}

void DeleteID()
{
  Watchdog.reset();
  bool doflag = true;
  do{
  if(!ts.bufferEmpty()){  
  if (ts.touched())
  {   
    Serial.println("touched");
    // Retrieve a point  
    TS_Point p=ts.getPoint();
    Watchdog.reset();
    while(!ts.bufferEmpty())
    {
      p=ts.getPoint();
      Watchdog.reset();
      } 
    p.x = map(p.x, TS_MINY, TS_MAXY, 0, tft.height());
    p.y = map(p.y, TS_MINX, TS_MAXX, 0, tft.width());
    int y = tft.height() - p.x;
    //int y = p.x;
    int x = p.y;
    Serial.println(x);
    Serial.println(y);
    Watchdog.reset();
  if((x > 10) && (x < 60)) 
      {
        if ((y > 60) && (y <= 110)) 
        {
          tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println(" DELETING ID: 1");
          deleteFingerprint(1);
          doflag=false;
          delay(2000);
          drawFrame();
          tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println("DELETED!");
          delay(1000);
          flag1 = false;
          menuflag=false;
          id = -1;
          resetFunc();
          break; 
        }
      }
   if((x > 100) && (x < 150))
   {
      if((y > 60) && (y < 110))
      {
        tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println(" DELETING ID: 2");
          deleteFingerprint(2);
          doflag=false;
          delay(2000);
          drawFrame();
          tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println("DELETED!");
          delay(1000);
          flag1 = false;
          menuflag=false;
          id = -1;
          resetFunc();
          break; 
       }
    }

   if((x > 190) && (x < 240))
   {
      if((y > 60) && (y < 110))
      {
        tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println(" DELETING ID: 3");
          deleteFingerprint(3);
          doflag=false;
          delay(2000);
          drawFrame();
          tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println("DELETED!");
          delay(1000);
          flag1 = false;
          menuflag=false;
          id = -1;
          resetFunc();
          break; 
       }
    }

    if((x > 10) && (x < 60))
   {
      if((y > 120) && (y < 170))
      {
        tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println(" DELETING ID: 4");
          deleteFingerprint(4);
          doflag=false;
          delay(2000);
          drawFrame();
          tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println("DELETED!");
          delay(1000);
          flag1 = false;
          menuflag=false;
          id = -1;
          resetFunc();
          break; 
       }
    }

    if((x > 100) && (x < 150))
   {
      if((y > 120) && (y < 170))
      {
        tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println(" DELETING ID: 5");
          deleteFingerprint(5);
          doflag=false;
          delay(2000);
          drawFrame();
          tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println("DELETED!");
          delay(1000);
          flag1 = false;
          menuflag=false;
          id = -1;
          resetFunc();
          break; 
       }
    }

    if((x > 190) && (x < 240))
   {
      if((y > 120) && (y < 170))
      {
        tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println(" DELETING ID: 6");
          deleteFingerprint(6);
          doflag=false;
          delay(2000);
          drawFrame();
          tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println("DELETED!");
          delay(1000);
          flag1 = false;
          menuflag=false;
          id = -1;
          resetFunc();
          break; 
       }
    }

    if((x > 10) && (x < 60))
   {
      if((y > 180) && (y < 230))
      {
        tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println(" DELETING ID: 7");
          deleteFingerprint(7);
          doflag=false;
          delay(2000);
          drawFrame();
          tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println("DELETED!");
          delay(1000);
          flag1 = false;
          menuflag=false;
          id = -1;
          resetFunc();
          break; 
       }
    }

    if((x > 100) && (x < 150))
   {
      if((y > 180) && (y < 230))
      {
        tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println(" DELETING ID: 8");
          deleteFingerprint(8);
          doflag=false;
          delay(2000);
          drawFrame();
          tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println("DELETED!");
          delay(1000);
          flag1 = false;
          menuflag=false;
          id = -1;
          resetFunc();
          break; 
       }
    }

    if((x > 190) && (x < 240))
   {
      if((y > 180) && (y < 230))
      {
        tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println(" DELETING ID: 9");
          deleteFingerprint(9);
          doflag=false;
          delay(2000);
          drawFrame();
          tft.setCursor(20,25);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(2); 
          tft.println("DELETED!");
          delay(1000);
          flag1 = false;
          menuflag=false;
          id = -1;
          resetFunc();
          break; 
       }
    }
}
}
  }while(doflag);
}


void button1()
{
  tft.fillRect(10,60,50,50, ILI9341_RED);
  tft.setCursor(30,80);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("1");
  
}

void button2()
{
  tft.fillRect(100,60,50,50, ILI9341_RED);
  tft.setCursor(120,80);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("2");
  
}

void button3()
{
  tft.fillRect(190,60,50,50, ILI9341_RED);
  tft.setCursor(210,80);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("3");
  
}

void button4()
{
  tft.fillRect(10,120,50,50, ILI9341_RED);
  tft.setCursor(30,140);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("4");
  
}

void button5()
{
  tft.fillRect(100,120,50,50, ILI9341_RED);
  tft.setCursor(120,140);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("5");
  
}

void button6()
{
  tft.fillRect(190,120,50,50, ILI9341_RED);
  tft.setCursor(210,140);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("6");
  
}

void button7()
{
  tft.fillRect(10,180,50,50, ILI9341_RED);
  tft.setCursor(30,200);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("7");
  
}

void button8()
{
  tft.fillRect(100,180,50,50, ILI9341_RED);
  tft.setCursor(120,200);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("8");
  
}

void button9()
{
  tft.fillRect(190,180,50,50, ILI9341_RED);
  tft.setCursor(210,200);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("9");
  
}

void drawFrame()
{
  tft.fillRect(10,10,300,45,ILI9341_WHITE);
  tft.drawRect(10, 10, 300, 45, ILI9341_BLACK);
  
}

void drawKeypad()
{
  tft.fillScreen(ILI9341_BLUE);
  tft.setRotation(1);
  button1();
  button2();
  button3();
  button4();
  button5();
  button6();
  button7();
  button8();
  button9();
  drawFrame();
  
}

void drawMenu()
{
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLUE);
  tft.fillRect(10,80,150,50, ILI9341_GREEN);
  tft.setCursor(30,90);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("Add User");

  
  tft.fillRect(10,160,150,50, ILI9341_RED);
  tft.setCursor(30,170);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("Delete User");

  drawResumeButton();
}

void drawResumeButton()
{
  tft.fillRect(200,80,100,50,ILI9341_GREEN);
  tft.setCursor(210,90);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("Resume");
}

void drawStandby()
{
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLUE);
  drawFrame();
  tft.setCursor(30,25);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.println("Waiting");
}

//Adafruit Fingerprint library source
uint8_t getFingerprintEnroll(int thisID) {

  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(thisID);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  Serial.println("Remove finger");
  delay(2000);
  Watchdog.reset();
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  Serial.print("Creating model for #");  Serial.println(thisID);
  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  Serial.print("ID "); Serial.println(thisID);
  p = finger.storeModel(thisID);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
}
//Adafruit Fingerprint library source
uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 
}
//Adafruit Fingerprint library source
// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
}
//Adafruit Fingerprint library source 
uint8_t deleteFingerprint(uint8_t id) {
  uint8_t p = -1;
  
  p = finger.deleteModel(id);

  if (p == FINGERPRINT_OK) {
    Serial.println("Deleted!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not delete in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.print("Unknown error: 0x"); Serial.println(p, HEX);
    return p;
  }   
}

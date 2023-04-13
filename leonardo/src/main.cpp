  #include <PS4USB.h>
  #include <usbhub.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
PS4USB PS4(&Usb);
//USBHub Hub1(&Usb);

//BTD Btd(&Usb);
//PS4BT PS4(&Btd, PAIR);
//PS4BT PS4(&Btd );

int k = 0;
int l = 0;
int r = 0;
int data = 0;

int l1 = 1;
int r1 = 1;

int a;


void setup() {
  Serial1.begin(9600);

  if (Usb.Init() == -1) {
    Serial1.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
Serial.print(F("\r\nPS4 USB Library Started"));
}


void loop() {
Usb.Task();

  if (PS4.connected()) {

//назад
 if ((PS4.getAnalogHat(LeftHatY) - 128) > abs(PS4.getAnalogHat(LeftHatX) - 128) )
    {
     k = map( PS4.getAnalogHat(LeftHatY), 150, 255, 1, 49);
    }
//вперед
 if ((PS4.getAnalogHat(LeftHatY) - 128) < abs(PS4.getAnalogHat(LeftHatX) - 128) )
    {
    k = map( PS4.getAnalogHat(LeftHatY), 90, 0, 50, 99);
    }
//влево
 if (abs(PS4.getAnalogHat(LeftHatY) - 128) < (abs(PS4.getAnalogHat(LeftHatX) - 128)))
    {
     k = map( PS4.getAnalogHat(LeftHatX), 90, 0, 150, 199);
    }
//вправо
 if (abs(PS4.getAnalogHat(LeftHatY) - 128) < (PS4.getAnalogHat(LeftHatX) - 128) )
    {
     k = map( PS4.getAnalogHat(LeftHatX), 150, 255, 100, 149);
    }

      if (PS4.getAnalogHat(LeftHatX) <= 150 && PS4.getAnalogHat(LeftHatX) >= 90 && 
          PS4.getAnalogHat(LeftHatY) <= 150 && PS4.getAnalogHat(LeftHatY) >= 90)
    {
          k = 0;
    }

    
    if (PS4.getButtonClick(TRIANGLE))
    {
      k = 401;
    }
    
    if (PS4.getButtonClick(CIRCLE)) 
    {
      k = 400;
    }
    if (PS4.getButtonClick(SQUARE)) 
    {
      k = 406;
    }
    if (PS4.getButtonClick(CROSS)) 
    {
      k = 402;
    }
    
    if (PS4.getButtonClick(RIGHT)) 
    {
      k = 404;
    } 
    if (PS4.getButtonClick(DOWN)) 
    {
      k = 403;
    } 
    if (PS4.getButtonClick(LEFT)) 
    {
      k = 405;
    }
    if (PS4.getButtonClick(UP)) 
    {
      k = 407;
    }
    
    if (PS4.getButtonClick(L1))
    {
     l1 ++;
     if ( l1 == 2)
     l1 = 0;
    }
    
    if (PS4.getButtonClick(R1))
    {
     r1 ++;
     if ( r1 == 2)
     r1 = 0;
    }
    if (PS4.getButtonClick(OPTIONS))
    {
      k = 409;
    }
    if (PS4.getButtonClick(SHARE))
    {
      k = 408;
    }
  
    if (PS4.getAnalogButton(L2) && l1 == 1) 
    {
      l = map(PS4.getAnalogButton(L2), 10, 255, 200, 299);
      if (l >= 200 && l <= 299)
      k = l;
//      Serial.println(k);
    }
    
    if (PS4.getAnalogButton(R2) && r1 == 1) 
    {  
      r = map(PS4.getAnalogButton(R2), 10, 255, 300, 399);
      if (r >= 300 && l <= 399) 
      k = r;
//      Serial.println(k);
    }
}
  a = k;
    
 
  //  Serial1.println(a);
    Serial1.println(a);
    
    delay(10);
  }
  

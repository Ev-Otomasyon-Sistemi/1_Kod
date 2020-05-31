#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27, 16, 2); 

#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT evotomasyonu(DHTPIN, DHTTYPE);

#include <Servo.h>
Servo kapiservo;
Servo pencereservo;

const int mileri=9;
const int mgeri=10;

const int pirPin = 8;
const int gazsensor=A0;
const int trig = 3;   
const int echo = 4;

const byte  latchPin = 7;  // Pin connected to Pin 12 of 74HC595 (Latch)
const byte dataPin  = 6;   // Pin connected to Pin 14 of 74HC595 (Data)
const byte clockPin = 5;   // Pin connected to Pin 11 of 74HC595 (Clock)
int x = 0;                          
int sayac=0,btgelen,btgelenveri,gazdegeri,nemdegeri,sicaklikdegeri,mesafedegeri,skontrol;

int buzzerpin=13;

byte led1,led2,led3,led4,led5,led6;

byte kapi,penc;

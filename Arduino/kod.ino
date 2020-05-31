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
void setup()
{
  Serial.begin(9600);
  lcd.begin(); //lcd hazırlandı
  lcd.backlight(); // arka plan ışığı ayarlandı
  kapiservo.attach(A3);  // attaches the servo on pin 9 to the servo object
  pencereservo.attach(A1 );
  pinMode(latchPin, OUTPUT);   
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(pirPin, INPUT);
  pinMode(mileri,OUTPUT);
  pinMode(mgeri,OUTPUT);
  pinMode(buzzerpin,OUTPUT);

//  for(int i=0;i<=13;i++){
//    digitalWrite(i,LOW);
//  }

    lcd.setCursor(7,0); //yazının lcd ekrandaki konumu belirlendi
    lcd.print("EV");
    lcd.setCursor(3,1);
    lcd.print("OTOMASYONU");
    delay(3000);
    lcd.clear();

    
}
 
void loop()
{
  if(Serial.available() > 0){     
      btgelenveri = Serial.read();   
    }
 //Serial.println(btgelenveri);  
 
bluetoothkontrol(btgelenveri);
gazdegeri=gaz();
nemdegeri=topraknem();
sicaklikdegeri=sicaklik();
mesafedegeri=mesafeolc();
lcdyaz(gazdegeri,nemdegeri,mesafedegeri,sicaklikdegeri,btgelenveri);   


if(gazdegeri>300){
  buzzer(50);
}
if(mesafedegeri<6){
  buzzer(50);
}
if(nemdegeri<600){
    digitalWrite(mileri,1);
    digitalWrite(mgeri,0);

}
else{
   digitalWrite(mileri,0);
  digitalWrite(mgeri,0);

}


//Serial.print(gazdegeri);//çoklu veri için
//Serial.print("*");
//Serial.print(nemdegeri);
//Serial.print("*");
//Serial.print(sicaklikdegeri);
//Serial.print("*");
//Serial.println(mesafedegeri);




 
}
int bluetoothkontrol(int btgelen){

  
     if(btgelen==65)
    led1=1;
    if(btgelen==66)
    led1=0;

     if(btgelen==67)
    led2=1;
    if(btgelen==68)
    led2=0;

     if(btgelen==69)
    led3=1;
    if(btgelen==70)
    led3=0;

     if(btgelen==71)
    led4=1;
    if(btgelen==72)
    led4=0;

     if(btgelen==73)
    led5=1;
    if(btgelen==74)
    led5=0;

     if(btgelen==75)
    led6=1;
    if(btgelen==76)
    led6=0;

    if(btgelen==77)
    kapi=0;
    if(btgelen==78)
    kapi=45;

    if(btgelen==80)
    penc=45;
    if(btgelen==82)
    penc=0;
    


    
    if(hareket()==1 && kapi==45 )
    buzzer(50);
    

  

     led(led1,led2,led3,led4,led5,led6);
     kapiservo.write(kapi); 
     delay(20);
      pencereservo.write(penc); 
    
     delay(150  );
 
}

int led(byte a,byte b,byte c,byte d,byte e,byte f){
  boolean dizi[] = {0, 0, f, e, d, c, b, a};  //nokta,g,f,e,d,c,b,a  = 1 acık 0 kapali
  digitalWrite(latchPin, 0);       
 
  for (int i = 0 ; i < 8 ; i++)     
  {
    x = dizi[i];                    //for dönügü boyunca dizinin i. değeri x'e atanır
 
    digitalWrite(dataPin, x);       //datapin'e x değeri verilir
    digitalWrite(clockPin, 1);      //saat darbesi ile yazma ve kaydırma işlemi yapılır
    digitalWrite(clockPin, 0);
  }
  digitalWrite(latchPin, 1);        //8 bitli dizi çıkışa verilir
}


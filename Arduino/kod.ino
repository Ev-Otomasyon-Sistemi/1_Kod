#include <Wire.h> /*bağlantı fonksiyonlarını bulundurur.*/
#include <LiquidCrystal_I2C.h>  /*LCD ekran çalışma ve bağlantısı*/
LiquidCrystal_I2C lcd(0x27, 16, 2); /* lcd nin adresini ve kaca kac lcd olduguu tanımladık*/


#include "DHT.h" /*sıcaklık-nem sensörü bulunduran kütüphane*/
#define DHTPIN 2 /*sabit bir değişken olan DHT11PIN olarak Dijital 2"yi belirliyoruz.*/
#define DHTTYPE DHT11 /**/
DHT evotomasyonu(DHTPIN, DHTTYPE);

#include <Servo.h> /*servo motor kütüphanesi*/
Servo kapiservo;  /*servo kütüphaneini kullancaklar*/
Servo pencereservo;

const int mileri=9;  /*motroun dönüşü*/
const int mgeri=10; /*motroun dönüşü*/
/*Hareket sensörü ortamdaki sıcaklık ve kızılötesi dalga değişimlerini algılamaya yarayan sensörler*/
const int pirPin = 8; /*Pır sensörünü takıldığı sabir pin*/
const int gazsensor=A0; /*gaz sensörünü takıldığı sabir pin*/
/*Hareket sensörü için*/
const int trig = 3;   /* Sensorun trig pini Arduinonun 3 numaralı ayağına bağlandı */
const int echo = 4; /* Sensorun echo pini Arduinonun 4 numaralı ayağına bağlandı */
/*çoklu led kontrlolü*/ /*ÇIKIŞ PİNLERİ*/

const byte  latchPin = 7;  // Pin connected to Pin 12 of 74HC595 (Latch)  /*74Hc595 SHİFT REGİSTER ENTEGRESİ*/
const byte dataPin  = 6;   // Pin connected to Pin 14 of 74HC595 (Data)
const byte clockPin = 5;   // Pin connected to Pin 11 of 74HC595 (Clock)
int x = 0;                          
int sayac=0,btgelen,btgelenveri,gazdegeri,nemdegeri,sicaklikdegeri,mesafedegeri,skontrol; /*Kullılıcak değişkenlerimizi tanımladık*/

int buzzerpin=13; /*buzzerimızın(alrm) takılı oluğu pin*/


byte led1,led2,led3,led4,led5,led6;

byte kapi,penc;
/*void setup()
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

}*/

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

void lcdyaz(int gazveri,int nemverisi,int mesafeverisi,int sicaklikverisi,int bluetoothveri){

  //Serial.println(bluetoothveri);

 if(bluetoothveri==90){
  
    lcd.setCursor(7,0); 
    lcd.print("SIC");
    lcd.setCursor(9,1); 
    lcd.print(" ");
    lcd.setCursor(7,1);
    lcd.print(sicaklikverisi);
 }
 
 if(bluetoothveri==79){
    if(mesafeverisi<100){
    lcd.setCursor(9,1);
    lcd.print(" ");
    lcd.setCursor(10,1);
    lcd.print(" ");
  }
   if(mesafeverisi<10){
    lcd.setCursor(8,1);
    lcd.print(" ");
    lcd.setCursor(9,1);
    lcd.print(" ");
  }
    lcd.setCursor(7,0);
    lcd.print("MES");
    lcd.setCursor(7,1);
    lcd.print(mesafeverisi);
 }
 
 if(bluetoothveri==83){
    if(gazveri<100){
    lcd.setCursor(9,1);
    lcd.print(" ");
    lcd.setCursor(10,1);
    lcd.print(" ");
  }
    lcd.setCursor(7,0); 
    lcd.print("GAZ");
    lcd.setCursor(7,1);
    lcd.print(gazveri);
  
 }
 
 if(bluetoothveri==87){
    if(nemverisi<1000){
    lcd.setCursor(10,1);
    lcd.print(" ");
    lcd.setCursor(11,1);
    lcd.print(" ");
  }
     lcd.setCursor(7,0); 
    lcd.print("NEM");
    lcd.setCursor(7,1);
    lcd.print(nemverisi);
 }




}
int gaz(){
  int gazdeger=analogRead(gazsensor);
  return gazdeger;
}
int mesafeolc(){
  int sure,mesafe;
  digitalWrite(trig, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig, LOW);
  sure = pulseIn(echo, HIGH);
  mesafe = (sure/2) / 29.1; 
  return mesafe;
}

float sicaklik(){
  float t = evotomasyonu.readTemperature();
return t;
}


int hareket(){
  int hdeger;
  int pirDeger = digitalRead(pirPin);
  
if (pirDeger == HIGH) 
hdeger=1;
else
hdeger=0;

return hdeger;

}
int servokapi(int kapiderece){
kapiservo.write(kapiderece);   
}
int servopencere(int pencerederece){  
 pencereservo.write(pencerederece);  
}
void motor(int msure){

  
  delay(1000);
  sayac=sayac+1;
  if(sayac>msure){
   digitalWrite(mileri,0);
  digitalWrite(mgeri,0);
  }
  else{
    digitalWrite(mileri,0);
  digitalWrite(mgeri,1);
  }
//Serial.println(sayac);

}

int topraknem(){
  int nemdeger=analogRead(A2);
   return nemdeger;
}
void buzzer(int ton){
  digitalWrite(buzzerpin,1);
  delay(ton);
   digitalWrite(buzzerpin,0);
  delay(ton);
  
}

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

//gelen verilere göre  kontrol yapıyor ve uygulama ile burada uggulamadaki harf sistemini asci tablouna göre yapıldı
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
/*çoklu led olduğu için bir diziye kayıt edildi ayrıca for döngüünde koylık sağlayacak*/
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

void lcdyaz(int gazveri,int nemverisi,int mesafeverisi,int sicaklikverisi,int bluetoothveri){ //Lcd ekranına yazı yazmak için lcdyaz adında bir fonksiyon tanımlandı.

  //Serial.println(bluetoothveri);

 if(bluetoothveri==90){//İf komutu bluetooth verisini kontrol eder. Eğer bluetooth verisi 90(sıcaklığı göster anlamına gelir) değerine eşit ise; 
  
    lcd.setCursor(7,0); // hangi satırda hangi sutunda olacağını belirtir. 7. sutun, 0.satıra ekran imlecini ayarlar. 7.sutun, 0.satır  
    lcd.print("SIC"); //itibariyle ekrana “SIC” yazar.
    lcd.setCursor(9,1); //9. sutun, 1.satıra ekran imlecini ayarlar. 9.sutun, 1.satır 
    lcd.print(" "); //ekrana “ ” yazar.
    lcd.setCursor(7,1);//7. sutun, 1.satıra ekran imlecini ayarlar. 7.sutun, 1.satır
    lcd.print(sicaklikverisi);  // ekrana DHT11 sensöründen aldığı sicaklikverisi’ni yazar
 }
 
 if(bluetoothveri==79){ //İf komutu bluetooth verisini kontrol eder. Eğer bluetooth verisi 79 değerine eşit ise;  

    if(mesafeverisi<100){ //Eğer mesafeverisi 100 değerinden küçük ise
    lcd.setCursor(9,1); //9. sutun, 1.satıra ekran imlecini ayarlar. 9.sutun, 1.satır
    lcd.print(" ");  // ekrana “ ” yazar. 
    lcd.setCursor(10,1); //10. sutun, 1.satıra ekran imlecini ayarlar. 10.sutun, 1.satır 
    lcd.print(" ");  // ekrana “ “ yazar. 
  }
   if(mesafeverisi<10){   //Eğer mesafeverisi 10 değerinden küçük ise; 
    lcd.setCursor(8,1);  //8. sutun, 1.satıra ekran imlecini ayarlar. 8.sutun, 1.satır
    lcd.print(" ");  // ekrana “ ” yazar. 
    lcd.setCursor(9,1);   //9. sutun, 1.satıra ekran imlecini ayarlar. 9.sutun, 1.satır
    lcd.print(" ");  //ekrana “ “ yazar
  }   //Eğer hiçbiri değil ise; 
    lcd.setCursor(7,0);  //7. sutun, 0.satıra ekran imlecini ayarlar. 7.sutun, 0.satır 
    lcd.print("MES"); // ekrana “ MES” yazar
    lcd.setCursor(7,1); //7. sutun, 1.satıra ekran imlecini ayarlar. 7.sutun, 1.satır itibariyle 
    lcd.print(mesafeverisi); //ekrana HC-SR04 sensöründen aldığı mesafeverisi yazar. 
 }
 
 if(bluetoothveri==83){  //İf komutu bluetooth verisini kontrol eder. Eğer bluetooth verisi 83 değerine eşit ise;  
 
    if(gazveri<100){  // Eğer gazverisi 100 değerinden küçük ise; 
    lcd.setCursor(9,1);  //9. sutun, 1.satıra ekran imlecini ayarlar. 9.sutun, 1.satır 
    lcd.print(" ");   //ekrana “ ” yazar
    lcd.setCursor(10,1);  //10. sutun, 1.satıra ekran imlecini ayarlar. 10.sutun, 1.satır
    lcd.print(" ");  //ekrana “ “ yazar
  } //Eğer gazverisi 100 değerinden büyük ise; 
    lcd.setCursor(7,0);  //7. sutun, 0.satıra ekran imlecini ayarlar. 7.sutun, 0.satır 
    lcd.print("GAZ"); //ekrana “ GAZ” yazar.
    lcd.setCursor(7,1);  //7. sutun, 1.satıra ekran imlecini ayarlar. 7.sutun, 1.satır
    lcd.print(gazveri);  //ekrana MQ-2 sensöründen aldığı gazverisi yazar 
  
 }
 
 if(bluetoothveri==87){  //İf komutu bluetooth verisini kontrol eder. Eğer bluetooth verisi 87 değerine eşit ise
    if(nemverisi<1000){  // Eğer nemverisi 1000 değerinden küçük ise; 
    lcd.setCursor(10,1);  //10. sutun, 1.satıra ekran imlecini ayarlar. 10.sutun, 1.satır
    lcd.print(" ");  //ekrana “ ” yazar. 
    lcd.setCursor(11,1); //11. sutun, 1.satıra ekran imlecini ayarlar. 11.sutun, 1.satır 
    lcd.print(" ");
  }   //Eğer nemverisi 1000 değerinden büyük ise
     lcd.setCursor(7,0);   //7. sutun, 0.satıra ekran imlecini ayarlar. 7.sutun, 0.satır 
    lcd.print("NEM");  //ekrana “ NEM” yazar. 
    lcd.setCursor(7,1);
    lcd.print(nemverisi); //ekrana DHT11 sensöründen aldığı nemverisi yazar. 
 }




}
int gaz(){ //Gaz ın çıkış pininden bir değer okunur ve o değer return olarak ana fonksiyona döndürülür. 
  int gazdeger=analogRead(gazsensor);  //MQ-2 sensöründen okunan analog değer gazdeger isimli değişkene aktarılır. 
  return gazdeger;   //Sonuç olarak sensörden aldığı gazdegeri’ni return olarak ana fonksiyona döndürür ve ekrana yazdırılır
}
int mesafeolc(){ 
  int sure,mesafe;  // Sure ve mesafe isminde 2 tane değişken oluşturuldu.
  digitalWrite(trig, HIGH); //trig pinini HIGH durumunda başlatıyoruz.
  delayMicroseconds(1000);  //1 saniye aralıklarla ses dalgası yayılır. 
  digitalWrite(trig, LOW);
  sure = pulseIn(echo, HIGH);
  mesafe = (sure/2) / 29.1;  //Mikrofona bir ses dalgası çarparsa bunun için bir süre tutar. Bu süreyi 2 ye bölüp, 29.1(sesin havada yayılma hızı)’e bölünür ve mesafe adlı değişkene atanır. 
  return mesafe;   //Sonuç olarak geriye mesafe değişkeni return olarak ana fonksiyona döndürülür ve ekrana yazdırılır. 
}

float sicaklik(){   //Sicaklik isminde float tipinde değer döndüren bir fonksiyon oluşturuldu
  float t = evotomasyonu.readTemperature();   //DHT11 sensöründen sıcaklık değeri okunur ve t değişkenine aktarılır.  
return t;   //sensörden aldığı sıcaklık değeri return olarak ana fonksiyona döndürülür ve ekrana yazdırılır.  
 
}


int hareket(){
  int hdeger;
  int pirDeger = digitalRead(pirPin);  // PIR sensöründen okuma yapılır ve pirDegerine aktarılır
  
if (pirDeger == HIGH) 
hdeger=1;  //Eğer alınan pirDegerinde hareketlilik var ise hdeger yani hareket değeri 1 olur
else
hdeger=0;  //Eğer alınan pirDegerinde hareketlilik yok ise hdeger yani hareket değeri 0 olur.

return hdeger;  //sensörden aldığı hareket değeri döndürülür.

}
int servokapi(int kapiderece){
kapiservo.write(kapiderece);     //kodu ile servo motorun kapiderecesi açı değerine dönmesini sağlar. 

}
int servopencere(int pencerederece){  
 pencereservo.write(pencerederece);  //kodu ile servo motorun pencerederece açı değerine dönmesini sağlar.  
}
void motor(int msure){

  
  delay(1000);  //1000 milisaniye bekletilir. 
  sayac=sayac+1;  //Sayaç oluşturulur ve her seferinde sayaç 1 arttırılır.
  if(sayac>msure){  //Eğer sayaç değeri motor süresinden büyükse
   digitalWrite(mileri,0);   // motor ileri pini logıc 0 ve motor geri pini logic 0 yapılır. 
  digitalWrite(mgeri,0);
  }
  else{   //Sayaç değeri motor süresinden küçükse
    digitalWrite(mileri,0);  // motor ileri pini logic 0 ve motor geri pini logıc 1 yapılır.
  digitalWrite(mgeri,1);
  }
//Serial.println(sayac);

}

int topraknem(){
  int nemdeger=analogRead(A2);   //Toprak nem sensöründen okunan analog değer nemdeger isimli değişkene aktarılır
   return nemdeger;   //Sonuç olarak sensörden aldığı nemdegeri döndürür
}
void buzzer(int ton){
  digitalWrite(buzzerpin,1);  // buzzerpin pini logıc 1 yapılır. Delay(ton) fonksiyonu sayesinde buzzer ses çıkartır. 
  delay(ton);
   digitalWrite(buzzerpin,0);  //buzzerpin pini logıc 0 yapılır. Delay(ton) fonksiyonu sayesinde buzzer ses çıkartır. 
  delay(ton);
  
}

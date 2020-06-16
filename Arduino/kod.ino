//BÜTÜN PROGRAM KODLARI TÜM EKİP ÜYELERİNİN ORTAK ÇALIŞMASI İLE YAZILMIŞTIR!
//Yazan,Test Eden,Hata Ayıklayan: Esra YÜCE, Feyza YILMAZ, Halil SEÇİLMİŞ, Özlem ÖZKAYA


#include <Wire.h>                        //bağlantı fonksiyonlarını bulundurur.
#include <LiquidCrystal_I2C.h>           // LCD ekran çalışma ve bağlantısı.
LiquidCrystal_I2C lcd(0x27, 16, 2);      // lcd'nin adresi ve kaça kaç lcd oldugu tanımlandı.


#include "DHT.h"       //sıcaklık-nem sensörü bulunduran kütüphane.
#define DHTPIN 2       // sabit bir değişken olan DHT11PIN olarak Dijital 2"yi belirliyoruz.
#define DHTTYPE DHT11 
DHT evotomasyonu(DHTPIN, DHTTYPE);

#include <Servo.h>   //servo motor kütüphanesi.
Servo kapiservo;     //servo kütüphanesini kullancaklar.
Servo pencereservo;

const int mileri=9;     //motorun dönüşü.
const int mgeri=10;     // motorun dönüşü.

const int pirPin = 8;   // Pır sensörünün takıldığı sabit pin.
const int gazsensor=A0; // gaz sensörünün takıldığı sabit pin.

/*Hareket sensörü için*/
const int trig = 3;     // Sensorun trig pini Arduinonun 3 numaralı ayağına bağlandı.
const int echo = 4;     // Sensorun echo pini Arduinonun 4 numaralı ayağına bağlandı.

// çoklu led kontrlolü ÇIKIŞ PİNLERİ

const byte  latchPin = 7;  // Pin connected to Pin 12 of 74HC595 (Latch)  // 74Hc595 SHİFT REGİSTER ENTEGRESİ.
const byte dataPin  = 6;   // Pin connected to Pin 14 of 74HC595 (Data)
const byte clockPin = 5;   // Pin connected to Pin 11 of 74HC595 (Clock)
int x = 0;                          
int sayac=0,btgelen,btgelenveri,gazdegeri,nemdegeri,sicaklikdegeri,mesafedegeri,skontrol; // Kullanılıcak değişkenler tanımlandı.

int buzzerpin=13; // buzzerın(alrm) takılı oluğu pin.


byte led1,led2,led3,led4,led5,led6;

byte kapi,penc;



void setup() /*Genel ayarlamlar yapıldı 1kere çalışır*/
{
  Serial.begin(9600);/*seri haberleşme hızı*/
  /*lcd boyutlarını ayarlanması*/
  lcd.begin(); //lcd hazırlandı
  lcd.backlight(); // arka plan ışığı ayarlandı
 kapiservo.attach(A3);  // kapi için oluşturduğumuz nesneyi A3 pinine takarak servo motrunmuzu kulllanılamsı
  pencereservo.attach(A1 );  // perde için oluşturduğumuz nesneyi A3 pinine takarak servo motrunmuzu kulllanılamsı
    /*ledler için tanımlalan pinleri çıkış olarak ayarlandır*/
  pinMode(latchPin, OUTPUT);   
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(pirPin, INPUT);
  pinMode(mileri,OUTPUT);
  pinMode(mgeri,OUTPUT);
  pinMode(buzzerpin,OUTPUT);




    lcd.setCursor(7,0); // //yazının lcd ekrandaki konumu belirlendi
    lcd.print("EV"); //lcd yi metin yazdırma işlemi
    lcd.setCursor(3,1);
    lcd.print("OTOMASYONU");
      delay(3000); //bekletem saniyesi 3 saniye
    lcd.clear(); //lcd tezmiler ekranı
    
}
 
void loop() /*Arduino'nun yapması gereken işlemler buraya yazılır*/

{
  if(Serial.available() > 0){     
      btgelenveri = Serial.read();   
    }

//Uygulama ile haberleşme, uygulamadaki harflere ascii tablosunda karşılık gelen decimal sayılar yardımıyla sağlandı. Haberleşme ile gelen verilere göre  kontrol yapılır.
int bluetoothkontrol(int btgelen)
{

  
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

// çoklu ledler bir diziye kayıt edildi. bu durum for döngüsünde kolaylık sağlayacak.

int led(byte a,byte b,byte c,byte d,byte e,byte f)
{
  boolean dizi[] = {0, 0, f, e, d, c, b, a};         // nokta,g,f,e,d,c,b,a  = 1 acık 0 kapali
  digitalWrite(latchPin, 0);       
 
  for (int i = 0 ; i < 8 ; i++)     
    {
    x = dizi[i];                    // for dönügü boyunca dizinin i. değeri x'e atanır.
    digitalWrite(dataPin, x);       // datapin'e x değeri verilir.
    digitalWrite(clockPin, 1);      // saat darbesi ile yazma ve kaydırma işlemi yapılır.
    digitalWrite(clockPin, 0);
    }
    digitalWrite(latchPin, 1);      // 8 bitli dizi çıkışa verilir.
}

void lcdyaz(int gazveri,int nemverisi,int mesafeverisi,int sicaklikverisi,int bluetoothveri)   //Lcd ekranına yazı yazmak için lcdyaz adında bir fonksiyon tanımlandı.

{

 if(bluetoothveri==90)          // İf komutu bluetooth verisini kontrol eder. Eğer bluetooth verisi 90(sıcaklığı göster anlamına gelir) değerine eşit ise; 
  {
    lcd.setCursor(7,0);         // hangi satırda hangi sutunda olacağını belirtir. 7. sütun, 0.satıra ekran imlecini ayarlar.  
    lcd.print("SIC");           // 7.sütun, 0. satıritibariyle ekrana “SIC” yazar.
    lcd.setCursor(9,1);         // 9. sütun, 1. satıra ekran imlecini ayarlar.  
    lcd.print(" ");             // 9.sütun, 1. satırda ekrana “ ” yazar.
    lcd.setCursor(7,1);         // 7. sütun, 1. satıra ekran imlecini ayarlar. 
    lcd.print(sicaklikverisi);  // 7.sütun, 1. satırda ekrana DHT11 sensöründen aldığı sicaklikverisi’ni yazar.
  }
 
 if(bluetoothveri==79)   // İf komutu bluetooth verisini kontrol eder. Eğer bluetooth verisi 79 değerine eşit ise;  
  {
    if(mesafeverisi<100) // Eğer mesafeverisi 100 değerinden küçük ise
      {
    lcd.setCursor(9,1);  // 9. sütun, 1. satıra ekran imlecini ayarlar. 
    lcd.print(" ");      // 9.sütun, 1. satırda ekrana “ ” yazar. 
    lcd.setCursor(10,1); // 10. sütun, 1. satıra ekran imlecini ayarlar. 
    lcd.print(" ");      // 10.sütun, 1. satırda ekrana “ “ yazar. 
     }
   if(mesafeverisi<10)    // Eğer mesafeverisi 10 değerinden küçük ise; 
     {
    lcd.setCursor(8,1);   // 8. sütun, 1. satıra ekran imlecini ayarlar. 
    lcd.print(" ");       // 8.sütun, 1. satırda ekrana “ ” yazar. 
    lcd.setCursor(9,1);   // 9. sütun, 1. satıra ekran imlecini ayarlar. 
    lcd.print(" ");       // 9. sütun, 1. satırda ekrana “ “ yazar.
     }  
   //Eğer hiçbiri değil ise; 
    lcd.setCursor(7,0);      // 7. sütun, 0. satıra ekran imlecini ayarlar.  
    lcd.print("MES");        // 7. sütun, 0.satırda ekrana “ MES ” yazar.
    lcd.setCursor(7,1);      // 7. sütun, 1. satıra ekran imlecini ayarlar. 
    lcd.print(mesafeverisi); // 7. sütun, 1. satırda ekrana HC-SR04 sensöründen aldığı mesafeverisi yazar. 
 }
 
 if(bluetoothveri==83)   // İf komutu bluetooth verisini kontrol eder. Eğer bluetooth verisi 83 değerine eşit ise;  
 { 
    if(gazveri<100)      // Eğer gazverisi 100 değerinden küçük ise; 
    { 
    lcd.setCursor(9,1);  // 9. sütun, 1. satıra ekran imlecini ayarlar.  
    lcd.print(" ");      // 9. sütun, 1. satırda ekrana “ ” yazar.
    lcd.setCursor(10,1); // 10. sütun, 1. satıra ekran imlecini ayarlar. 
    lcd.print(" ");      // 10. sütun, 1.satırda ekrana “ “ yazar.
    } 
   
   //Eğer gazverisi 100 değerinden büyük ise; 
    lcd.setCursor(7,0);  // 7. sütun, 0. satıra ekran imlecini ayarlar.  
    lcd.print("GAZ");    // 7.sütun, 0. satırda ekrana “ GAZ ” yazar.
    lcd.setCursor(7,1);  // 7. sütun, 1. satıra ekran imlecini ayarlar. 
    lcd.print(gazveri);  // 7.sutun, 1.satırda ekrana MQ-2 sensöründen aldığı gazverisi yazar. 
  
 }
 
 if(bluetoothveri==87)   //İf komutu bluetooth verisini kontrol eder. Eğer bluetooth verisi 87 değerine eşit ise;
 {
    if(nemverisi>400)    // Eğer nemverisi 400 değerinden büyük ise; 
    { 
    lcd.setCursor(10,1); // 10. sütun, 1. satıra ekran imlecini ayarlar. 
    lcd.print(" ");      // 10. sütun, 1. satırda ekrana “ ” yazar. 
    lcd.setCursor(11,1); // 11. sütun, 1. satıra ekran imlecini ayarlar.  
    lcd.print(" ");      // 11.sütun, 1. satırda ekrana “ “ yazar.
    }   
   
   //Eğer nemverisi 400 değerinden küçük ise;
    lcd.setCursor(7,0);  // 7. sütun, 0 .satıra ekran imlecini ayarlar.  
    lcd.print("NEM");     // 7. sütun, 0. satırda ekrana “ NEM ” yazar. 
    lcd.setCursor(7,1);
    lcd.print(nemverisi); // ekrana DHT11 sensöründen aldığı nemverisi yazar. 
 }

}

int gaz()           //Gaz'ın çıkış pininden bir değer okunur ve o değer return olarak ana fonksiyona döndürülür. 
  {
  int gazdeger=analogRead(gazsensor);  // MQ-2 sensöründen okunan analog değer gazdeger isimli değişkene aktarılır. 
  return gazdeger;                     //Sonuç olarak sensörden aldığı gazdegeri’ni return olarak ana fonksiyona döndürür ve ekrana yazdırılır.
  }

int mesafeolc()
  { 
  int sure,mesafe;             // Sure ve mesafe isminde 2 tane değişken oluşturuldu.
  digitalWrite(trig, HIGH);    // trig pini HIGH durumunda başlatılıyor.
  delayMicroseconds(1000);     // 1 saniye aralıklarla ses dalgası yayılır. 
  digitalWrite(trig, LOW);
  sure = pulseIn(echo, HIGH);
  mesafe = (sure/2) / 29.1;    // Mikrofona bir ses dalgası çarparsa anlaşılması için bir süre tutar. Bu süreyi 2'ye bölüp 29.1(sesin havada yayılma hızı)’e bölünür ve mesafe adlı değişkene atanır. 
  return mesafe;               // Sonuç olarak geriye mesafe değişkeni return olarak ana fonksiyona döndürülür ve ekrana yazdırılır. 
  }

float sicaklik()               // Sicaklik isminde float tipinde değer döndüren bir fonksiyon oluşturuldu.
  {   
  float t = evotomasyonu.readTemperature();   // DHT11 sensöründen sıcaklık değeri okunur ve t değişkenine aktarılır.  
  return t;                                   // Sensörden aldığı sıcaklık değeri return olarak ana fonksiyona döndürülür ve ekrana yazdırılır.  
  }


int hareket()
  {
  int hdeger;
  int pirDeger = digitalRead(pirPin);    // PIR sensöründen okuma yapılır ve pirDegerine aktarılır.
  
     if (pirDeger == HIGH) 
     hdeger=1;               // Eğer alınan pirDegerinde hareket var ise hdeger yani hareket değeri 1 olur.
     
     else
     hdeger=0;               // Eğer alınan pirDegerinde hareket yok ise hdeger yani hareket değeri 0 olur.

     return hdeger;          // sensörden aldığı hareket değeri döndürülür.

   }

int servokapi(int kapiderece)
   {
   kapiservo.write(kapiderece);   // Servo motorun kapiderecesi açı değerine dönmesini sağlar. 
   }

int servopencere(int pencerederece)
   {  
   pencereservo.write(pencerederece);  // Servo motorun pencerederece açı değerine dönmesini sağlar.  
   }

void motor(int msure)
 {
  delay(1000);               // 1000 milisaniye bekletilir. 
  sayac=sayac+1;             // Sayaç oluşturulur ve her seferinde sayaç 1 arttırılır.
  
  if(sayac>msure)            // Eğer sayaç değeri motor süresinden büyükse
    {
    digitalWrite(mileri,0);  // motor ileri pini logıc 0 ve motor geri pini logic 0 yapılır. 
    digitalWrite(mgeri,0);
    }
  
  else                       // Sayaç değeri motor süresinden küçükse;
    {
    digitalWrite(mileri,0);  // motor ileri pini logic 0 ve motor geri pini logıc 1 yapılır.
    digitalWrite(mgeri,1);
    }
 }

int topraknem()
{
  int nemdeger=analogRead(A2);   // Toprak nem sensöründen okunan analog değer nemdeger isimli değişkene aktarılır.
   return nemdeger;              //Sonuç olarak sensörden aldığı nemdegeri döndürür.
}
void buzzer(int ton)
{
  digitalWrite(buzzerpin,1);    // buzzerpin pini logıc 1 yapılır. Delay(ton) fonksiyonu sayesinde buzzer ses çıkartır. 
  delay(ton);
  digitalWrite(buzzerpin,0);   // buzzerpin logıc 0 yapılır. Delay(ton) fonksiyonu sayesinde buzzer ses çıkartır. 
  delay(ton);  
}

----------------------------------------------------Mobil Uygulama-------------------------------------------------------------------
AppInventor Nedir?
App Inventor, Massachusetts Institute of Technology(MIT) tarafından geliştirilen, programlama konusunda tecrübesi olmayan kimselerin kullanması için yapılmış olan ve Android uygulaması geliştirmesine olanak sağlayan bir uygulama geliştirme platformudur. En önemli özelliği drag and drop yani sürükle ve bırak şeklinde programlanabilmesidir.
NOT: Uygulamaya girebilmek için gmail hesabı gerekmektedir.

Proje Dosyasını Çalıştırma
App Inventor ana sayfasında üst kısımda bulunan 'My Projects' seçeneğine tıklayınca birkaç işlem seçeneği ile karşılaşırız. Bunlardan 'Import project (.aia) from my computer ...' seçeneğini seçtikten sonra bilgisayarınızdan indirmiş olduğunuz .aia uzantılı dosyayı seçerek açabilirsiniz.

.apk uzantılı dosyayı telefonunuza indirip kurarak uygulamayı kullanabilirsiniz. 
Uygulamaya giriş yapmak için mevcut kullanıcı hesapları ve şifreler bulunur. Ekli kullanıcı hesapları aşağıda yer almaktadır.

Çocuk Girişi için 
Kullanıcı adı: esra     Şifre: 1234
Kullanıcı adı: feyza    Şifre: abc1

Yetişkin Girişi için
Kullanıcı adı: halil    Şifre: H123
Kullanıcı adı: özlem    Şifre: O123

----------------------------------------------------------Arduino---------------------------------------------------------------------
İndirilen kod dosyası Arduino ide'de açılır ve sistem için gerekli kütüphaneler (“<Wire.h>, <LiquidCrystal_I2C.h>, <Servo.h>, "DHT.h”) dahil edilir. Derlenen kod arduino uno arabirimine yüklenir. 
Mobil uygulama ile sistemin haberleşme hızı Serial.begin() yardımı ile belirlenir . Mobil uygulamadan gelen veriler Serial.read() aktarılır ve mobil uygulamadaki değişken isimlerinin karşılıkları ASCII tablosu yardımı ile sisteme entegre edilir. Ayrıca açma kapama işlemleri “0: kapat,1: aç” şeklinde yapılır.

--------------------------------------------------------------------------------------------------------------------------------------
Iriun Webcam programı aracılığı ile kamera sistemine bağlanılır.
Setup1 dosyası içinden Debug klasöründe->Setup1.msi tıklayın ve kurlum başlatın
Bilgisayarın sunucu adını değiştiriniz.
Kurulacak bilgisayarın veri tabanı kurullumu için
1.sql servere girin 
2.Database klasörüne Attach yapın. 
3.Yapılandırı ve Add tıklayın.
4. Seçilen dosyayı veri tabanına ekleyin. (db klasörü içinde (arduino_veri) ).

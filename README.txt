AppInventor Nedir?-------------------------------------------------
App Inventor, Massachusetts Institute of Technology(MIT) tarafından geliştirilen, programlama konusunda tecrübesi olmayan kimselerin kullanması için yapılmış olan ve Android uygulaması geliştirmesine olanak sağlayan bir uygulama geliştirme platformudur. En önemli özelliği drag and drop yani sürükle ve bırak şeklinde programlanabilmesidir.
NOT: Uygulamaya girebilmek için gmail hesabı gerekmektedir.

Proje Dosyasını Çalıştırma----------------------------------------
App Inventor ana sayfasında üst kısımda bulunan 'My Projects' seçeneğine tıklayınca birkaç işlem seçeneği ile karşılaşırız. bunlardan 'Import project (.aia) from my computer ...' seçeneğini seçtikten sonra bilgisayarınızdan indirmiş olduğunuz .aia uzantılı dosyayı seçerek açabilirsiniz.

.apk uzantılı dosyayı telefonuza indirip kurarak uygulamayı kullanabilirsiniz.
Uygulamaya giriş yapmak için mevcut kullanıcı hesapları ve şifreler bulunur. Ekli kullanıcı hesaplanı aşağıda yer almaktadır.

Çocuk Girişi için 
Kullanıcı adı: esra     Şifre: 1234
Kullanıcı adı: feyza    Şifre: abc1

Yetişkin Girişi için
Kullanıcı adı: halil    Şifre: H123
Kullanıcı adı: özlem    Şifre: O123



Uygulama Kodları Hakkında-----------------------------------------
Uygulama 5 ayrı sayfadan oluşmaktadır. Sayfa düzeni için dikey sıralamada 'VerticalArrangement'(Birbirinin altında görüntülenmesi gereken bileşenlerin yerleştirileceği bir biçimlendirme öğesi.), yatay sıralamada ise HorizontalArrangement(Soldan sağa görüntülenmesi gereken bileşenlerin yerleştirileceği bir biçimlendirme öğesi.) kullanılmıştır. Bu öğelerin içerisine gerekli Button, TextBox ve Label bileşenleri yerleştirilmiştir.

İlk sayfada iki tane buton yer almaktadır. Butonlara tıklanarak 'open another screen' komutu ile butona atanan sayfaya yönlendirme yapılır. Bu iki butonun her birine atanan farklı sayfalar dolayısıyla farklı sayfalara geçiş sağlarnır. 
Açılan sayfalar Çocuk Girişi ve Yetişkin Girişi sayfalarıdır. Bu sayfalarda kullanıcı, kullanıcı adını ve şifresini girer. 
Girilen bilgiler giriş kontrolüne bağlı olan matematik ve lojik yapılar sayesinde kayıtlı kullanıcı bilgileri ile karşılaştırılır.
Bilgiler doğru ise butona atanan sayfaya geçiş yapılır, bilgiler yanlış ise 'kullanıcı adı veya şifre hatalı' uyarısı verip 'tekrar dene' seçeneği sunar. 
Bu hata mesajı 'Notifier'(uyarı iletişim kutularını, iletileri ve geçici uyarıları görüntüler) öğesi ile sağlanır. 
Giriş sağlandıktan sonra son olarak Akıllı Ev maketinde bulunan sensörlerin kontrolünün sağlandığı ana sayfa açılır. 
Bluetooth bağlantısını sağlamak için ilk olarak '.BeforePickink' komutu ile bluetooth adresleri aranır ve '.AfterPicking' kontrolünde '.Connect address' ile çıkan ve bluetooth cihazımız ile eşleşen adres seçilir. Aynı şekilde bağlantıyı kesmek için '.Disconnect' kullanılır. 
Sensör kontrolünü sağlayan her bir buton bluetooth bağlantısı sayesinde '.SendText' komutu ile veri göndererek sensör kontrolünü sağlar. 
Oda sıcaklığını görüntülemek için ilgili sensöre '.SendText' ile veri gönderilir 'if' kontrol yapısı ile bluetooth bağlantısı kontrol edilir. 
Bağlantı sağlandıysa tekrar bir kontrol yapısına girilir '.ReceiveText' ile  alınan veri ilgili label'a yazılması için lojik yapısı kullanılarak eşitleme sağlandı ise veri label'a yazılır.

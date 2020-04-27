#### *App Inventor Hakkında Bilgi* 
##### *AppInventor Nedir?*
*App Inventor, Massachusetts Institute of Technology(MIT) tarafından geliştirilen, programlama konusunda tecrübesi olmayan kimselerin kullanması için yapılmış olan ve Android uygulaması geliştirmesine olanak sağlayan bir uygulama geliştirme platformudur. En önemli özelliği drag and drop yani sürükle ve bırak şeklinde programlanabilmesidir.
NOT: Uygulamaya girebilmek için gmail hesabı gerekmektedir.*
##### *Nasıl Giriş Yapılır?*
*AppInventor’a giriş yapabilmek için http://appinventor.mit.edu/ adresinden, üstteki menüde bulunan **'create appss!'** sekmesine tıklamamız gerekmekte.*
*Bu sekmeye tıkladıktan sonra site bizi http://ai2.appinventor.mit.edu/ adresinde yönlendiriyor ve buradan google hesabımız ile giriş yapmamızı istiyor. Giriş yaptıktan sonra verilen uyarıya **'izin ver'** diyerek geçebilirsiniz.
İzni verdikten karşımıza çıkacak olan ekran bizim proje oluşturma ekranımız olup daha önce oluşturduğumuz projelere bu ekrandan ulaşabiliriz.*
*Start New Project butonuna basılıp ve bir proje ismi girip OK butonuna tıklıyoruz.
Karşımıza çıkacak ekran 5 parçaya ayrılmış durumdadır. Bunlar;*
1. *Palette: Uygulamaya koyabileceğimiz görsel ya da işlevsel her şeyin bulunduğu kısım. Örneğin buton, onay kutusu, tarayıcı, bluetooth*
2. *Viewer: Uygulamamızın göründüğü kısımdır. Uygulamayı bitirdiğimizde, görsel arayüz bu ekrandaki gibi gözükür*
3. *Components: Uygulamamızda kullanacağımız nesnelerin ismini görüp değiştirebileceğimiz kısım*
4. *Media: Kullanacağımız ses, fotoğraf gibi dosyaların yükleneceği yer.*
5. *Properties: Eklediğimiz nesnelerin ayarları ile bu kısımdan oynayabiliriz. Örneğin bir buton eklediğimizde, butonun üzerindeki yazıyı, boyutunu veya rengini buradan değiştirebiliriz.*

*Sağ üst kısımda **designer/block** isminde iki buton bulunmaktadır. Bu butonlardan designer kısmı şuana kadar gördüğümüz kısımken block kısmı ise parçaları birleştirerek, kodlama yaptığımız kısımdır. Buradan, kontrol yapılarını, mantıksal işlemleri, matematiksel işlemleri yapabiliriz.*
   
*Burada Block kısmı, kodlama yaparken birbiri ile birleştireceğimiz tüm blokların bulunduğu kısımdır. Media kısmı designer kısmı ile aynı işlevde olup Viewer kısmı ise blokların sürüklenip birbirleri ile birleştirildiği kısımdır.
Uygulama hazırlanıp deneme aşamasına gelindiğinde Android telefonlarda QR kodu okutturmak için öncelikle, https://play.google.com/store/apps/details?id=edu.mit.appinventor.aicompanion3 adresinden MIT AI2 Companion isimli uygulamayı indirmemiz gerekiyor.*

*İnternet sitesinde üstteki sekmelerden Build sekmesine geldiğimizde site uygulamamızı derleyip bize bir QR kod veriyor. Bu kodu telefona indirdiğimiz uygulamamıza okuttuğumuzda yaptığımız uygulamayı indirip telefona kuruyor ve işlem tamamlanıyor.*

*Eğer Android işletim sistemi bulunmayan bir mobil cihaza sahipseniz app inventor’ü bir emulatör üzerinden de kullanabilirsiniz. Bu bağlantı çok stabil olmamakla beraber sensör verilerini de kullanmamıza olanak sağlamıyor. Bilgisayarınıza kurmanız gereken emulatörü Windows, Mac ve Linux için  http://appinventor.mit.edu/explore/ai2/setup-emulator.html linkinden indirebilirsiniz.*
   
*Emulatörü bilgisayara yükledikten sonra açmamız ve web ara yüzünden Connect-Emulator seçeneğini seçmemiz gerekiyor. Emulator seçeneği seçildikten 1-2 dakika içerisinde uygulamamız sanal olarak çalışmaya başlayacaktır.*
________________________________________________________________________________________________________________________________________
#### *Proje Dosyasını Çalıştırma*
*App Inventor ana sayfasında üst kısımda bulunan **'My Projects'** seçeneğine tıklayınca birkaç işlem seçeneği ile karşılaşırız. bunlardan **'Import project (.aia) from my computer ...'** seçeneğini seçtikten sonra bilgisayarınızdan indirmiş olduğunuz .aia uzantılı dosyayı seçerek çalıştırabilirsiniz.*
*.apk *uzantılı dosyayı telefonuza kurarak uygulamayı kullanabilirsiniz.*

#### *Uygulama Kodları Hakkında*
*Uygulama 5 ayrı sayfadan oluşmaktadır. Sayfa düzeni için dikey sıralamada **VerticalArrangement**(Birbirinin altında görüntülenmesi gereken bileşenlerin yerleştirileceği bir biçimlendirme öğesi.), yatay sıralamada ise **HorizontalArrangement**(Soldan sağa görüntülenmesi gereken bileşenlerin yerleştirileceği bir biçimlendirme öğesi.) kullanılmıştır. Bu öğelerin içerisine gerekli Button, TextBox ve Label bileşenleri yerleştirilmiştir.*

*İlk sayfada iki tane buton yer almaktadır. Butonlara tıklanarak **open another screen** komutu ile butona atanan sayfaya yönlendirme yapılır. Bu iki butonun her birine atanan farklı sayfalar dolayısıyla farklı sayfalara geçiş sağlarnır. Açılan sayfalar Çocuk Girişi ve Yetişkin Girişi sayfalarıdır. Bu sayfalarda kullanıcı, kullanıcı adını ve şifresini girer. Girilen bilgiler giriş kontrolüne bağlı olan **matematik** ve **lojik** yapılar sayesinde kayıtlı kullanıcı bilgileri ile karşılaştırılır. Bilgiler doğru ise butona atanan sayfaya geçiş yapılır, bilgiler yanlış ise **'kullanıcı adı veya şifre hatalı'** uyarısı verip **'tekrar dene'** seçeneği sunar. Bu hata mesajı **Notifier**(uyarı iletişim kutularını, iletileri ve geçici uyarıları görüntüler) öğesi ile sağlanır. Giriş sağlandıktan sonra son olarak Akıllı Ev maketinde bulunan sensörlerin kontrolünün sağlandığı ana sayfa açılır. Bluetooth bağlantısını sağlamak için ilk olarak **.BeforePickink** komutu ile bluetooth adresleri aranır ve **.AfterPicking** kontrolünde **.Connect address** ile çıkan ve bluetooth cihazımız ile eşleşen adres seçilir. aynı şekilde bağlantıyı kesmek için **.Disconnect** kullanılır. Sensör kontrolünü sağlayan her bir buton bluetooth bağlantısı sayesinde **.SendText** komutu ile veri göndererek sensör kontrolünü sağlar. Oda sıcaklığını görüntülemek için ilgili sensöre **.SendText** ile veri gönderilir **if** kontrol yapısı ile bluetooth bağlantısı kontrol edilir. Bağlantı sağlandıysa tekrar bir kontrol yapısına girilir **.ReceiveText** ile  alınan veri ilgili label'a yazılması için lojik yapısı kullanılarak eşitleme sağlandı ise veri label'a yazılır.* 

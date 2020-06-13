using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using AForge.Video; 
using AForge.Video.DirectShow; 
using System.IO;

//BÜTÜN PROGRAM KODLARI TÜM EKİP ÜYELERİNİN ORTAK ÇALIŞMASI İLE YAZILMIŞTIR!
//Yazan,Test Eden,Hata Ayıklayan; Esra YÜCE, Feyza YILMAZ, Halil SEÇİLMİŞ, Özlem ÖZKAYA

//Güvenlik_Ekranı
namespace Güvenlik_Veri
{
    public partial class Kamera : Form
    {
        public Kamera()
        {
            InitializeComponent();
        }

        private FilterInfoCollection webcamsayisi; //Kamera nesnelerini yaratıyoruz
        private VideoCaptureDevice kamera;
        private void Kamera_Load(object sender, EventArgs e)
        {
            webcamsayisi = new FilterInfoCollection(FilterCategory.VideoInputDevice);
            foreach (FilterInfo videocapturedevice in webcamsayisi)
            {
                comboBox1.Items.Add(videocapturedevice.Name); //Kayıtlı kameralar
            }
            //    comboBox1.SelectedIndex = 0;
        }
        private void kullanilacakcihaz_NewFrame(object sender, NewFrameEventArgs eventArgs)
        {
            Bitmap bit = (Bitmap)eventArgs.Frame.Clone();
            pictureBox1.Image = bit;
        }
        private void btn_basla_Click(object sender, EventArgs e)
        {
            //BAŞLA BUTONU
            kamera = new VideoCaptureDevice(webcamsayisi[comboBox1.SelectedIndex].MonikerString);
            kamera.NewFrame += new NewFrameEventHandler(kullanilacakcihaz_NewFrame);
            kamera.Start();
        }

        private void btn_dur_Click(object sender, EventArgs e)
        {
            //DURDUR BUTONU
            if (kamera.IsRunning) //kamera açıksa kapatıyoruz.
            {
                kamera.Stop();
            }
        }

        private void btn_kyıt_Click(object sender, EventArgs e)
        {
            //KAYDET BUTONU
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();
            saveFileDialog1.Filter = "Jpeg Resmi|*.jpg|Bitmap Resmi|*.bmp|Gif Resmi|*.gif";
            saveFileDialog1.Title = "Görüntüyü Kaydet";
            saveFileDialog1.ShowDialog();

            if (saveFileDialog1.FileName != "")
            {
                FileStream DosyaAkisi = (FileStream)saveFileDialog1.OpenFile();

                switch (saveFileDialog1.FilterIndex)
                {
                    case 1:
                        pictureBox1.Image.Save(DosyaAkisi, System.Drawing.Imaging.ImageFormat.Jpeg);
                        break;

                    case 2:
                        pictureBox1.Image.Save(DosyaAkisi, System.Drawing.Imaging.ImageFormat.Bmp);
                        break;

                    case 3:
                        pictureBox1.Image.Save(DosyaAkisi, System.Drawing.Imaging.ImageFormat.Gif);
                        break;
                }
                DosyaAkisi.Close();
            }
        }

        private void btn_cikis_Click(object sender, EventArgs e)
        {
            //ÇIKIŞ BUTONU
            this.Close();
            Application.Exit(); //çıkış
        }

       

        private void button1_Click(object sender, EventArgs e)
        {

            secme s = new secme();
            s.Show();
        }
    }
}

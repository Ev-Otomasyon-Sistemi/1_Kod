using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;
namespace Güvenlik_Veri
{
    //kullanici_giris
    public partial class Kullanici_Giris : Form
    {
        SqlConnection Baglanti = new SqlConnection("Data Source=LAPTOP-1SLQI3BT\\SQLEXPRESS;Initial Catalog=Arduino_Veri;Integrated Security=True");

     

        public Kullanici_Giris()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Application.Exit();

        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                Baglanti.Open();
                string sql = "Select * From kullanici_giris where k_adi=@adi And k_sifre=@sifre ";
                SqlParameter prm1 = new SqlParameter("adi", textBox3.Text.Trim());
                SqlParameter prm2 = new SqlParameter("sifre", textBox4.Text.Trim());
                SqlCommand komut = new SqlCommand(sql, Baglanti);
                komut.Parameters.Add(prm1);
                komut.Parameters.Add(prm2);
                DataTable dt = new DataTable();
                SqlDataAdapter da = new SqlDataAdapter(komut);
                da.Fill(dt);

                if (dt.Rows.Count > 0)
                {
                    secme f2 = new secme();
                    f2.Show();

                }
            }
            catch (Exception)
            {
                MessageBox.Show("Kullanıcı Adı veya Şifre Hatalı.");

            }
        }

       

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox1.Checked)
            {
                textBox4.PasswordChar = '\0';
            }
            else
            {
                textBox4.PasswordChar = '*';
            }
        }

        private void btn_cikis_Click(object sender, EventArgs e)
        {
            Application.Exit();

        }

    }
}

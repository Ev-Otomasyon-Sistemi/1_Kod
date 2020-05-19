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


namespace _Arduino_Kayit
{
    public partial class Giris_Ekrani : Form
    {
        public Giris_Ekrani()
        {
            InitializeComponent();
        }

        SqlConnection Baglanti = new SqlConnection(@"Data Source=.;Initial Catalog=kullanici;Integrated Security=True");
        

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                Baglanti.Open();
                string sql = "Select * From kullanici_giris where k_adi=@adi And k_sifre=@sifre ";
                SqlParameter prm1 = new SqlParameter("adi", textBox1.Text.Trim());
                SqlParameter prm2 = new SqlParameter("sifre", textBox2.Text.Trim());
                SqlCommand komut = new SqlCommand(sql, Baglanti);
                komut.Parameters.Add(prm1);
                komut.Parameters.Add(prm2);
                DataTable dt = new DataTable();
                SqlDataAdapter da = new SqlDataAdapter(komut);
                da.Fill(dt);

                if (dt.Rows.Count > 0)
                {
                    _Ana_Ekran ae = new _Ana_Ekran();
                    ae.Show();
                    
                }
            }
            catch (Exception)
            {
                MessageBox.Show("Kullanıcı Adı veya Şifre Hatalı.");

            }
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void Button2_Click(object sender, EventArgs e)
        {
            Application.Exit();

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
    }
}

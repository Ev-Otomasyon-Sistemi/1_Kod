using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Data.SqlClient;
using System.IO.Ports;

namespace _arduino_kayit
{
    public partial class Form1 : Form
    {
        SqlConnection BAGLANTİ = new SqlConnection("Data Source=.;Initial Catalog=Sensor_Veri;Integrated Security=True");
        SqlCommand komut = new SqlCommand();
        DataTable tablo = new DataTable();

        string[] portlar = SerialPort.GetPortNames();




        public Form1()
        {
            InitializeComponent();
            serialPort1.BaudRate = 900;

        }

     
        

        private void Form1_Load(object sender, EventArgs e)
        {
            foreach(string port in portlar)
            {
                comboBox1.Items.Add(port);
                comboBox1.SelectedIndex = 0;

            }
        }

        private void btn_baglan_Click(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen)
            {
                if(comboBox1.Text=="")
                {
                    return;
                    serialPort1.PortName = comboBox1.Text;
                    try
                    {
                        serialPort1.Open();
                        MessageBox.Show("Bağlantı başarıyla kuruldu.");
                        timer1.Start();
                    }

                    catch(Exception ex)
                    {
                        timer1.Stop();
                        MessageBox.Show(ex.Message);
                    }
                }
            }
        }

        private void btn_durdur_Click(object sender, EventArgs e)
        {
            timer1.Stop();
            serialPort1.Close();
            MessageBox.Show("Bağlantı sonlandırıldı.");

        }

        private void btn_goster_Click(object sender, EventArgs e)
        {

            if(serialPort1.IsOpen)
            {
                SqlDataAdapter adaptr = new SqlDataAdapter("SELECT Sensor_Veri FROM eylem", BAGLANTİ);
                adaptr.Fill(tablo);
                dataGridView1.DataSource = tablo;
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            try
            {
                serialPort1.Write("a");
                int data = Convert.ToInt16(serialPort1.ReadLine());
                textBox1.Text = data.ToString();

                if (BAGLANTİ.State == ConnectionState.Closed) BAGLANTİ.Open();
                SqlCommand komut = new SqlCommand("INSERT INTO Sensor_Veri (eylem) VALUES ('" + textBox1.Text + "')", BAGLANTİ);
                komut.ExecuteNonQuery();
                BAGLANTİ.Close();
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
                BAGLANTİ.Close();
            }
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            timer1.Stop();
            serialPort1.Close();

        }
    }
}

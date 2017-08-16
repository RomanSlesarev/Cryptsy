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
using System.IO.Ports;
using System.Threading;
using System.Net;
using xNet.Net;
using xNet.Text;

namespace ArduinoCryptsy
{
    public partial class Form1 : Form
    {
        Thread th;
        SerialPort port = new SerialPort("COM3", 9600);
        bool flag;
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            flag = true;
            th = new Thread(delegate()
            {
                while (true)
                {
                    string sURL = "https://bitcoins123.com/api/usd";
                    HttpRequest gURL = new HttpRequest();
                    HttpResponse rURL = gURL.Get(sURL);
                    string page = rURL.ToString();
                    string[] buyStrings = page.Substrings("BUY\":", ",\"USD");
                    string[] sellStrings = page.Substrings("SELL\":", "}");
                    port.Open();
                    port.Write(buyStrings[0].Length.ToString() + buyStrings[0] + sellStrings[0]);
                    port.Close();
                    Thread.Sleep(1000);
                }
            });
            th.Start();

        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (flag)
              th.Abort();
        }

    }
}

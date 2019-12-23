using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Windows.Forms;

namespace IOT
{
	public partial class Form1 : Form
	{
		static SerialPort serialPort;
		public Form1()
		{
			InitializeComponent();
			serialPort = new SerialPort();

			serialPort.PortName = "COM5";
			serialPort.BaudRate = 9600;

			serialPort.Open();
		}

		private void btnFWD_Click(object sender, EventArgs e)
		{
			serialPort.Write("w");
		}

		private void btnLFT_Click(object sender, EventArgs e)
		{
			serialPort.Write("a");
		}

		private void btnRHT_Click(object sender, EventArgs e)
		{
			serialPort.Write("d");
		}

		private void btnRVS_Click(object sender, EventArgs e)
		{
			serialPort.Write("s");
		}

		private void btnStop_Click(object sender, EventArgs e)
		{
			serialPort.Write(" ");
		}

		private void btnAutoMove_Click(object sender, EventArgs e)
		{
			serialPort.Write("t");
		}
	}
}

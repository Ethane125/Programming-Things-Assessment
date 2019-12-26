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
			serialPort.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);

		}

		private void DataReceivedHandler(object sender, SerialDataReceivedEventArgs e)
		{

			SerialPort sp = (SerialPort)sender;
			UpdateOutputTextBox(sp.ReadExisting());
		}

		public void UpdateOutputTextBox(string value)
		{
			if (InvokeRequired)
			{
				this.Invoke(new Action<string>(UpdateOutputTextBox), new object[] { value });
				return;
			}
			txtOutput.Text += value;
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
			txtOutput.Clear();
			serialPort.Write("t");
			btnFWD.Enabled = false;
			btnLFT.Enabled = false;
			btnRHT.Enabled = false;
			btnRVS.Enabled = false;
			btnStop.Enabled = false;


		}

		private void txtOutput_TextChanged(object sender, EventArgs e)
		{
			if(txtOutput.Text == "Reached a wall, changing to manual control, press the 'auto move' button to resume automatic movement.\n")
			{
				btnFWD.Enabled = true;
				btnLFT.Enabled = true;
				btnRHT.Enabled = true;
				btnRVS.Enabled = true;
				btnStop.Enabled = true;
			}
		}
	}
}

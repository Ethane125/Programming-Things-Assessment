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
using System.Text.RegularExpressions;

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
			btnTurnLeft.Enabled = false;
			btnTurnRight.Enabled = false;

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
			btnTurnLeft.Enabled = false;
			btnTurnRight.Enabled = false;


		}

		private void txtOutput_TextChanged(object sender, EventArgs e)
		{
			if (txtOutput.Text.Contains("Reached a wall, Turn the zumo either left or right\n"))
			{
				btnTurnLeft.Enabled = true;
				btnTurnRight.Enabled = true;
			}
			if(txtOutput.Text.Contains("swapping to auto movement"))
			{
				btnTurnLeft.Enabled = false;
				btnTurnRight.Enabled = false;
				serialPort.Write("t");
				//txtOutput.Clear();
			}
			if(txtOutput.Text.Contains("Found a room") && txtOutput.Text.Contains("."))
			{

				//String[] results = new String[2];
				MatchCollection matches = Regex.Matches(txtOutput.Text, "[0-9]+");
				var arr = Regex.Matches(txtOutput.Text, "[0-9]+")
								.Cast<Match>()
								.Select(m => m.Value)
								.ToArray();
				txtReport.Text += "Room ID: " + arr[0] + " Direction: " + (arr[1] == "0"? "Left" : "Right") +" Object? " + (arr[2] == "0" ? "False" : "True") + "\n";
				txtOutput.Clear();
			}
		}

		private void btnTurnLeft_Click(object sender, EventArgs e)
		{
			serialPort.Write("l");
			btnTurnLeft.Enabled = false;
			btnTurnRight.Enabled = false;
			txtOutput.Clear();
		}

		private void btnTurnRight_Click(object sender, EventArgs e)
		{
			serialPort.Write("r");
			btnTurnLeft.Enabled = false;
			btnTurnRight.Enabled = false;
			txtOutput.Clear();
		}

		private void btnRoom_Click(object sender, EventArgs e)
		{
			serialPort.Write("o");
			btnTurnLeft.Enabled = true;
			btnTurnRight.Enabled = true;
		}

		private void btnTestleft_Click(object sender, EventArgs e)
		{
			serialPort.Write("l");
		}

		private void btnTestRight_Click(object sender, EventArgs e)
		{
			serialPort.Write("r");
		}
	}
}

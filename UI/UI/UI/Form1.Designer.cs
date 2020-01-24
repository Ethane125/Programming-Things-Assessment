namespace IOT
{
	partial class Form1
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.btnFWD = new System.Windows.Forms.Button();
			this.btnLFT = new System.Windows.Forms.Button();
			this.btnRHT = new System.Windows.Forms.Button();
			this.btnRVS = new System.Windows.Forms.Button();
			this.btnStop = new System.Windows.Forms.Button();
			this.btnAutoMove = new System.Windows.Forms.Button();
			this.txtOutput = new System.Windows.Forms.RichTextBox();
			this.btnTurnLeft = new System.Windows.Forms.Button();
			this.btnTurnRight = new System.Windows.Forms.Button();
			this.btnRoom = new System.Windows.Forms.Button();
			this.txtReport = new System.Windows.Forms.RichTextBox();
			this.btnTestleft = new System.Windows.Forms.Button();
			this.btnTestRight = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// btnFWD
			// 
			this.btnFWD.Enabled = false;
			this.btnFWD.Location = new System.Drawing.Point(247, 39);
			this.btnFWD.Name = "btnFWD";
			this.btnFWD.Size = new System.Drawing.Size(123, 75);
			this.btnFWD.TabIndex = 0;
			this.btnFWD.Text = "Forward";
			this.btnFWD.UseVisualStyleBackColor = true;
			this.btnFWD.Click += new System.EventHandler(this.btnFWD_Click);
			// 
			// btnLFT
			// 
			this.btnLFT.Enabled = false;
			this.btnLFT.Location = new System.Drawing.Point(96, 142);
			this.btnLFT.Name = "btnLFT";
			this.btnLFT.Size = new System.Drawing.Size(123, 75);
			this.btnLFT.TabIndex = 1;
			this.btnLFT.Text = "Left";
			this.btnLFT.UseVisualStyleBackColor = true;
			this.btnLFT.Click += new System.EventHandler(this.btnLFT_Click);
			// 
			// btnRHT
			// 
			this.btnRHT.Enabled = false;
			this.btnRHT.Location = new System.Drawing.Point(396, 142);
			this.btnRHT.Name = "btnRHT";
			this.btnRHT.Size = new System.Drawing.Size(123, 75);
			this.btnRHT.TabIndex = 2;
			this.btnRHT.Text = "Right";
			this.btnRHT.UseVisualStyleBackColor = true;
			this.btnRHT.Click += new System.EventHandler(this.btnRHT_Click);
			// 
			// btnRVS
			// 
			this.btnRVS.Enabled = false;
			this.btnRVS.Location = new System.Drawing.Point(247, 245);
			this.btnRVS.Name = "btnRVS";
			this.btnRVS.Size = new System.Drawing.Size(123, 75);
			this.btnRVS.TabIndex = 3;
			this.btnRVS.Text = "Reverse";
			this.btnRVS.UseVisualStyleBackColor = true;
			this.btnRVS.Click += new System.EventHandler(this.btnRVS_Click);
			// 
			// btnStop
			// 
			this.btnStop.Enabled = false;
			this.btnStop.Location = new System.Drawing.Point(225, 120);
			this.btnStop.Name = "btnStop";
			this.btnStop.Size = new System.Drawing.Size(165, 119);
			this.btnStop.TabIndex = 4;
			this.btnStop.Text = "Stop";
			this.btnStop.UseVisualStyleBackColor = true;
			this.btnStop.Click += new System.EventHandler(this.btnStop_Click);
			// 
			// btnAutoMove
			// 
			this.btnAutoMove.Location = new System.Drawing.Point(188, 369);
			this.btnAutoMove.Name = "btnAutoMove";
			this.btnAutoMove.Size = new System.Drawing.Size(236, 81);
			this.btnAutoMove.TabIndex = 5;
			this.btnAutoMove.Text = "Auto move toggle";
			this.btnAutoMove.UseVisualStyleBackColor = true;
			this.btnAutoMove.Click += new System.EventHandler(this.btnAutoMove_Click);
			// 
			// txtOutput
			// 
			this.txtOutput.Location = new System.Drawing.Point(558, 39);
			this.txtOutput.Name = "txtOutput";
			this.txtOutput.ReadOnly = true;
			this.txtOutput.Size = new System.Drawing.Size(839, 677);
			this.txtOutput.TabIndex = 6;
			this.txtOutput.Text = "";
			this.txtOutput.TextChanged += new System.EventHandler(this.txtOutput_TextChanged);
			// 
			// btnTurnLeft
			// 
			this.btnTurnLeft.Location = new System.Drawing.Point(107, 610);
			this.btnTurnLeft.Name = "btnTurnLeft";
			this.btnTurnLeft.Size = new System.Drawing.Size(123, 75);
			this.btnTurnLeft.TabIndex = 7;
			this.btnTurnLeft.Text = "turn left 90°";
			this.btnTurnLeft.UseVisualStyleBackColor = true;
			this.btnTurnLeft.Click += new System.EventHandler(this.btnTurnLeft_Click);
			// 
			// btnTurnRight
			// 
			this.btnTurnRight.Location = new System.Drawing.Point(358, 610);
			this.btnTurnRight.Name = "btnTurnRight";
			this.btnTurnRight.Size = new System.Drawing.Size(123, 75);
			this.btnTurnRight.TabIndex = 8;
			this.btnTurnRight.Text = "turn right 90°";
			this.btnTurnRight.UseVisualStyleBackColor = true;
			this.btnTurnRight.Click += new System.EventHandler(this.btnTurnRight_Click);
			// 
			// btnRoom
			// 
			this.btnRoom.Location = new System.Drawing.Point(204, 492);
			this.btnRoom.Name = "btnRoom";
			this.btnRoom.Size = new System.Drawing.Size(202, 81);
			this.btnRoom.TabIndex = 9;
			this.btnRoom.Text = "Room";
			this.btnRoom.UseVisualStyleBackColor = true;
			this.btnRoom.Click += new System.EventHandler(this.btnRoom_Click);
			// 
			// txtReport
			// 
			this.txtReport.Location = new System.Drawing.Point(1456, 39);
			this.txtReport.Name = "txtReport";
			this.txtReport.ReadOnly = true;
			this.txtReport.Size = new System.Drawing.Size(352, 677);
			this.txtReport.TabIndex = 10;
			this.txtReport.Text = "";
			// 
			// btnTestleft
			// 
			this.btnTestleft.Location = new System.Drawing.Point(107, 749);
			this.btnTestleft.Name = "btnTestleft";
			this.btnTestleft.Size = new System.Drawing.Size(123, 75);
			this.btnTestleft.TabIndex = 11;
			this.btnTestleft.Text = "turn left 90°";
			this.btnTestleft.UseVisualStyleBackColor = true;
			this.btnTestleft.Click += new System.EventHandler(this.btnTestleft_Click);
			// 
			// btnTestRight
			// 
			this.btnTestRight.Location = new System.Drawing.Point(358, 749);
			this.btnTestRight.Name = "btnTestRight";
			this.btnTestRight.Size = new System.Drawing.Size(123, 75);
			this.btnTestRight.TabIndex = 12;
			this.btnTestRight.Text = "turn right 90°";
			this.btnTestRight.UseVisualStyleBackColor = true;
			this.btnTestRight.Click += new System.EventHandler(this.btnTestRight_Click);
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(1894, 858);
			this.Controls.Add(this.btnTestRight);
			this.Controls.Add(this.btnTestleft);
			this.Controls.Add(this.txtReport);
			this.Controls.Add(this.btnRoom);
			this.Controls.Add(this.btnTurnRight);
			this.Controls.Add(this.btnTurnLeft);
			this.Controls.Add(this.txtOutput);
			this.Controls.Add(this.btnAutoMove);
			this.Controls.Add(this.btnStop);
			this.Controls.Add(this.btnRVS);
			this.Controls.Add(this.btnRHT);
			this.Controls.Add(this.btnLFT);
			this.Controls.Add(this.btnFWD);
			this.Name = "Form1";
			this.Text = "Form1";
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Button btnFWD;
		private System.Windows.Forms.Button btnLFT;
		private System.Windows.Forms.Button btnRHT;
		private System.Windows.Forms.Button btnRVS;
		private System.Windows.Forms.Button btnStop;
		private System.Windows.Forms.Button btnAutoMove;
		private System.Windows.Forms.RichTextBox txtOutput;
		private System.Windows.Forms.Button btnTurnLeft;
		private System.Windows.Forms.Button btnTurnRight;
		private System.Windows.Forms.Button btnRoom;
		private System.Windows.Forms.RichTextBox txtReport;
		private System.Windows.Forms.Button btnTestleft;
		private System.Windows.Forms.Button btnTestRight;
	}
}


﻿namespace IOT
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
			this.txtReport = new System.Windows.Forms.RichTextBox();
			this.btnRoom = new System.Windows.Forms.Button();
			this.btnTJunc = new System.Windows.Forms.Button();
			this.btnEndJunc = new System.Windows.Forms.Button();
			this.btnEnd = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// btnFWD
			// 
			this.btnFWD.Location = new System.Drawing.Point(198, 12);
			this.btnFWD.Name = "btnFWD";
			this.btnFWD.Size = new System.Drawing.Size(110, 75);
			this.btnFWD.TabIndex = 0;
			this.btnFWD.Text = "Forward";
			this.btnFWD.UseVisualStyleBackColor = true;
			this.btnFWD.Click += new System.EventHandler(this.btnFWD_Click);
			// 
			// btnLFT
			// 
			this.btnLFT.Location = new System.Drawing.Point(82, 93);
			this.btnLFT.Name = "btnLFT";
			this.btnLFT.Size = new System.Drawing.Size(110, 75);
			this.btnLFT.TabIndex = 1;
			this.btnLFT.Text = "Left";
			this.btnLFT.UseVisualStyleBackColor = true;
			this.btnLFT.Click += new System.EventHandler(this.btnLFT_Click);
			// 
			// btnRHT
			// 
			this.btnRHT.Location = new System.Drawing.Point(314, 93);
			this.btnRHT.Name = "btnRHT";
			this.btnRHT.Size = new System.Drawing.Size(110, 75);
			this.btnRHT.TabIndex = 2;
			this.btnRHT.Text = "Right";
			this.btnRHT.UseVisualStyleBackColor = true;
			this.btnRHT.Click += new System.EventHandler(this.btnRHT_Click);
			// 
			// btnRVS
			// 
			this.btnRVS.Location = new System.Drawing.Point(198, 174);
			this.btnRVS.Name = "btnRVS";
			this.btnRVS.Size = new System.Drawing.Size(110, 75);
			this.btnRVS.TabIndex = 3;
			this.btnRVS.Text = "Reverse";
			this.btnRVS.UseVisualStyleBackColor = true;
			this.btnRVS.Click += new System.EventHandler(this.btnRVS_Click);
			// 
			// btnStop
			// 
			this.btnStop.Location = new System.Drawing.Point(198, 93);
			this.btnStop.Name = "btnStop";
			this.btnStop.Size = new System.Drawing.Size(110, 75);
			this.btnStop.TabIndex = 4;
			this.btnStop.Text = "Stop";
			this.btnStop.UseVisualStyleBackColor = true;
			this.btnStop.Click += new System.EventHandler(this.btnStop_Click);
			// 
			// btnAutoMove
			// 
			this.btnAutoMove.Location = new System.Drawing.Point(82, 265);
			this.btnAutoMove.Name = "btnAutoMove";
			this.btnAutoMove.Size = new System.Drawing.Size(342, 75);
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
			this.btnTurnLeft.Location = new System.Drawing.Point(82, 346);
			this.btnTurnLeft.Name = "btnTurnLeft";
			this.btnTurnLeft.Size = new System.Drawing.Size(110, 75);
			this.btnTurnLeft.TabIndex = 7;
			this.btnTurnLeft.Text = "turn left 90°";
			this.btnTurnLeft.UseVisualStyleBackColor = true;
			this.btnTurnLeft.Click += new System.EventHandler(this.btnTurnLeft_Click);
			// 
			// btnTurnRight
			// 
			this.btnTurnRight.Location = new System.Drawing.Point(314, 346);
			this.btnTurnRight.Name = "btnTurnRight";
			this.btnTurnRight.Size = new System.Drawing.Size(110, 75);
			this.btnTurnRight.TabIndex = 8;
			this.btnTurnRight.Text = "turn right 90°";
			this.btnTurnRight.UseVisualStyleBackColor = true;
			this.btnTurnRight.Click += new System.EventHandler(this.btnTurnRight_Click);
			// 
			// txtReport
			// 
			this.txtReport.Location = new System.Drawing.Point(1456, 39);
			this.txtReport.Name = "txtReport";
			this.txtReport.ReadOnly = true;
			this.txtReport.Size = new System.Drawing.Size(504, 677);
			this.txtReport.TabIndex = 10;
			this.txtReport.Text = "";
			// 
			// btnRoom
			// 
			this.btnRoom.Location = new System.Drawing.Point(82, 453);
			this.btnRoom.Name = "btnRoom";
			this.btnRoom.Size = new System.Drawing.Size(150, 75);
			this.btnRoom.TabIndex = 9;
			this.btnRoom.Text = "Room";
			this.btnRoom.UseVisualStyleBackColor = true;
			this.btnRoom.Click += new System.EventHandler(this.btnRoom_Click);
			// 
			// btnTJunc
			// 
			this.btnTJunc.Location = new System.Drawing.Point(274, 453);
			this.btnTJunc.Name = "btnTJunc";
			this.btnTJunc.Size = new System.Drawing.Size(150, 75);
			this.btnTJunc.TabIndex = 11;
			this.btnTJunc.Text = "T Junction";
			this.btnTJunc.UseVisualStyleBackColor = true;
			this.btnTJunc.Click += new System.EventHandler(this.btnTJunc_Click);
			// 
			// btnEndJunc
			// 
			this.btnEndJunc.Location = new System.Drawing.Point(274, 534);
			this.btnEndJunc.Name = "btnEndJunc";
			this.btnEndJunc.Size = new System.Drawing.Size(150, 75);
			this.btnEndJunc.TabIndex = 12;
			this.btnEndJunc.Text = "End of Junction";
			this.btnEndJunc.UseVisualStyleBackColor = true;
			this.btnEndJunc.Click += new System.EventHandler(this.btnEndJunc_Click);
			// 
			// btnEnd
			// 
			this.btnEnd.Location = new System.Drawing.Point(82, 632);
			this.btnEnd.Name = "btnEnd";
			this.btnEnd.Size = new System.Drawing.Size(342, 75);
			this.btnEnd.TabIndex = 13;
			this.btnEnd.Text = "REACHED END";
			this.btnEnd.UseVisualStyleBackColor = true;
			this.btnEnd.Click += new System.EventHandler(this.btnEnd_Click);
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.AutoSize = true;
			this.ClientSize = new System.Drawing.Size(2020, 858);
			this.Controls.Add(this.btnEnd);
			this.Controls.Add(this.btnEndJunc);
			this.Controls.Add(this.btnTJunc);
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
		private System.Windows.Forms.RichTextBox txtReport;
		private System.Windows.Forms.Button btnRoom;
		private System.Windows.Forms.Button btnTJunc;
		private System.Windows.Forms.Button btnEndJunc;
		private System.Windows.Forms.Button btnEnd;
	}
}


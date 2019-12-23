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
			this.SuspendLayout();
			// 
			// btnFWD
			// 
			this.btnFWD.Location = new System.Drawing.Point(269, 66);
			this.btnFWD.Name = "btnFWD";
			this.btnFWD.Size = new System.Drawing.Size(123, 75);
			this.btnFWD.TabIndex = 0;
			this.btnFWD.Text = "Forward";
			this.btnFWD.UseVisualStyleBackColor = true;
			this.btnFWD.Click += new System.EventHandler(this.btnFWD_Click);
			// 
			// btnLFT
			// 
			this.btnLFT.Location = new System.Drawing.Point(140, 142);
			this.btnLFT.Name = "btnLFT";
			this.btnLFT.Size = new System.Drawing.Size(123, 75);
			this.btnLFT.TabIndex = 1;
			this.btnLFT.Text = "Left";
			this.btnLFT.UseVisualStyleBackColor = true;
			this.btnLFT.Click += new System.EventHandler(this.btnLFT_Click);
			// 
			// btnRHT
			// 
			this.btnRHT.Location = new System.Drawing.Point(398, 142);
			this.btnRHT.Name = "btnRHT";
			this.btnRHT.Size = new System.Drawing.Size(123, 75);
			this.btnRHT.TabIndex = 2;
			this.btnRHT.Text = "Right";
			this.btnRHT.UseVisualStyleBackColor = true;
			this.btnRHT.Click += new System.EventHandler(this.btnRHT_Click);
			// 
			// btnRVS
			// 
			this.btnRVS.Location = new System.Drawing.Point(269, 214);
			this.btnRVS.Name = "btnRVS";
			this.btnRVS.Size = new System.Drawing.Size(123, 75);
			this.btnRVS.TabIndex = 3;
			this.btnRVS.Text = "Reverse";
			this.btnRVS.UseVisualStyleBackColor = true;
			this.btnRVS.Click += new System.EventHandler(this.btnRVS_Click);
			// 
			// btnStop
			// 
			this.btnStop.Location = new System.Drawing.Point(575, 278);
			this.btnStop.Name = "btnStop";
			this.btnStop.Size = new System.Drawing.Size(167, 89);
			this.btnStop.TabIndex = 4;
			this.btnStop.Text = "Stop";
			this.btnStop.UseVisualStyleBackColor = true;
			this.btnStop.Click += new System.EventHandler(this.btnStop_Click);
			// 
			// btnAutoMove
			// 
			this.btnAutoMove.Location = new System.Drawing.Point(575, 135);
			this.btnAutoMove.Name = "btnAutoMove";
			this.btnAutoMove.Size = new System.Drawing.Size(167, 89);
			this.btnAutoMove.TabIndex = 5;
			this.btnAutoMove.Text = "Auto move";
			this.btnAutoMove.UseVisualStyleBackColor = true;
			this.btnAutoMove.Click += new System.EventHandler(this.btnAutoMove_Click);
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(800, 450);
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
	}
}


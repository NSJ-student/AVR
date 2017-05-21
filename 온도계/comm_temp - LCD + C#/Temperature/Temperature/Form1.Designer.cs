namespace Temperature
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
            this.lblTemp = new System.Windows.Forms.Label();
            this.lblPort = new System.Windows.Forms.Label();
            this.cbPort = new System.Windows.Forms.ComboBox();
            this.btnOpen = new System.Windows.Forms.Button();
            this.btnClose = new System.Windows.Forms.Button();
            this.btnGet = new System.Windows.Forms.Button();
            this.btnStop = new System.Windows.Forms.Button();
            this.lblTimer = new System.Windows.Forms.Label();
            this.cbInterval = new System.Windows.Forms.ComboBox();
            this.lblSec = new System.Windows.Forms.Label();
            this.lblRxTemp = new System.Windows.Forms.Label();
            this.lblUnit = new System.Windows.Forms.Label();
            this.gbSetting = new System.Windows.Forms.GroupBox();
            this.gbResult = new System.Windows.Forms.GroupBox();
            this.ssBar = new System.Windows.Forms.StatusStrip();
            this.lblStatus = new System.Windows.Forms.ToolStripStatusLabel();
            this.gbSetting.SuspendLayout();
            this.gbResult.SuspendLayout();
            this.ssBar.SuspendLayout();
            this.SuspendLayout();
            // 
            // lblTemp
            // 
            this.lblTemp.AutoSize = true;
            this.lblTemp.Location = new System.Drawing.Point(13, 28);
            this.lblTemp.Name = "lblTemp";
            this.lblTemp.Size = new System.Drawing.Size(41, 12);
            this.lblTemp.TabIndex = 0;
            this.lblTemp.Text = "온도 : ";
            // 
            // lblPort
            // 
            this.lblPort.AutoSize = true;
            this.lblPort.Location = new System.Drawing.Point(13, 26);
            this.lblPort.Name = "lblPort";
            this.lblPort.Size = new System.Drawing.Size(41, 12);
            this.lblPort.TabIndex = 2;
            this.lblPort.Text = "포트 : ";
            // 
            // cbPort
            // 
            this.cbPort.FormattingEnabled = true;
            this.cbPort.Items.AddRange(new object[] {
            "COM1",
            "COM2",
            "COM3",
            "COM4",
            "COM5",
            "COM6",
            "COM7",
            "COM8",
            "COM9",
            "COM10"});
            this.cbPort.Location = new System.Drawing.Point(75, 23);
            this.cbPort.Name = "cbPort";
            this.cbPort.Size = new System.Drawing.Size(121, 20);
            this.cbPort.TabIndex = 3;
            // 
            // btnOpen
            // 
            this.btnOpen.Location = new System.Drawing.Point(202, 20);
            this.btnOpen.Name = "btnOpen";
            this.btnOpen.Size = new System.Drawing.Size(55, 23);
            this.btnOpen.TabIndex = 4;
            this.btnOpen.Text = "Open";
            this.btnOpen.UseVisualStyleBackColor = true;
            this.btnOpen.Click += new System.EventHandler(this.btnOpen_Click);
            // 
            // btnClose
            // 
            this.btnClose.Location = new System.Drawing.Point(263, 20);
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new System.Drawing.Size(55, 23);
            this.btnClose.TabIndex = 5;
            this.btnClose.Text = "Close";
            this.btnClose.UseVisualStyleBackColor = true;
            this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
            // 
            // btnGet
            // 
            this.btnGet.Location = new System.Drawing.Point(202, 23);
            this.btnGet.Name = "btnGet";
            this.btnGet.Size = new System.Drawing.Size(55, 23);
            this.btnGet.TabIndex = 6;
            this.btnGet.Text = "Get";
            this.btnGet.UseVisualStyleBackColor = true;
            this.btnGet.Click += new System.EventHandler(this.btnGet_Click);
            // 
            // btnStop
            // 
            this.btnStop.Location = new System.Drawing.Point(263, 23);
            this.btnStop.Name = "btnStop";
            this.btnStop.Size = new System.Drawing.Size(55, 23);
            this.btnStop.TabIndex = 7;
            this.btnStop.Text = "Stop";
            this.btnStop.UseVisualStyleBackColor = true;
            this.btnStop.Click += new System.EventHandler(this.btnStop_Click);
            // 
            // lblTimer
            // 
            this.lblTimer.AutoSize = true;
            this.lblTimer.Location = new System.Drawing.Point(13, 56);
            this.lblTimer.Name = "lblTimer";
            this.lblTimer.Size = new System.Drawing.Size(65, 12);
            this.lblTimer.TabIndex = 8;
            this.lblTimer.Text = "시간간격 : ";
            // 
            // cbInterval
            // 
            this.cbInterval.FormattingEnabled = true;
            this.cbInterval.Items.AddRange(new object[] {
            "500",
            "1000",
            "1500",
            "2000"});
            this.cbInterval.Location = new System.Drawing.Point(84, 53);
            this.cbInterval.Name = "cbInterval";
            this.cbInterval.Size = new System.Drawing.Size(65, 20);
            this.cbInterval.TabIndex = 9;
            // 
            // lblSec
            // 
            this.lblSec.AutoSize = true;
            this.lblSec.Location = new System.Drawing.Point(158, 56);
            this.lblSec.Name = "lblSec";
            this.lblSec.Size = new System.Drawing.Size(23, 12);
            this.lblSec.TabIndex = 10;
            this.lblSec.Text = "ms";
            // 
            // lblRxTemp
            // 
            this.lblRxTemp.AutoSize = true;
            this.lblRxTemp.Location = new System.Drawing.Point(82, 28);
            this.lblRxTemp.Name = "lblRxTemp";
            this.lblRxTemp.Size = new System.Drawing.Size(11, 12);
            this.lblRxTemp.TabIndex = 11;
            this.lblRxTemp.Text = "?";
            // 
            // lblUnit
            // 
            this.lblUnit.AutoSize = true;
            this.lblUnit.Location = new System.Drawing.Point(158, 28);
            this.lblUnit.Name = "lblUnit";
            this.lblUnit.Size = new System.Drawing.Size(11, 12);
            this.lblUnit.TabIndex = 12;
            this.lblUnit.Text = "?";
            // 
            // gbSetting
            // 
            this.gbSetting.Controls.Add(this.lblTimer);
            this.gbSetting.Controls.Add(this.cbInterval);
            this.gbSetting.Controls.Add(this.lblSec);
            this.gbSetting.Controls.Add(this.lblPort);
            this.gbSetting.Controls.Add(this.cbPort);
            this.gbSetting.Controls.Add(this.btnClose);
            this.gbSetting.Controls.Add(this.btnOpen);
            this.gbSetting.Location = new System.Drawing.Point(12, 12);
            this.gbSetting.Name = "gbSetting";
            this.gbSetting.Size = new System.Drawing.Size(332, 83);
            this.gbSetting.TabIndex = 13;
            this.gbSetting.TabStop = false;
            this.gbSetting.Text = "설정";
            // 
            // gbResult
            // 
            this.gbResult.Controls.Add(this.lblTemp);
            this.gbResult.Controls.Add(this.btnGet);
            this.gbResult.Controls.Add(this.lblUnit);
            this.gbResult.Controls.Add(this.btnStop);
            this.gbResult.Controls.Add(this.lblRxTemp);
            this.gbResult.Location = new System.Drawing.Point(12, 116);
            this.gbResult.Name = "gbResult";
            this.gbResult.Size = new System.Drawing.Size(332, 56);
            this.gbResult.TabIndex = 14;
            this.gbResult.TabStop = false;
            this.gbResult.Text = "온도 값";
            // 
            // ssBar
            // 
            this.ssBar.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.lblStatus});
            this.ssBar.Location = new System.Drawing.Point(0, 186);
            this.ssBar.Name = "ssBar";
            this.ssBar.Size = new System.Drawing.Size(355, 22);
            this.ssBar.TabIndex = 15;
            this.ssBar.Text = "상태바";
            // 
            // lblStatus
            // 
            this.lblStatus.Name = "lblStatus";
            this.lblStatus.Size = new System.Drawing.Size(31, 17);
            this.lblStatus.Text = "시작";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(355, 208);
            this.Controls.Add(this.ssBar);
            this.Controls.Add(this.gbResult);
            this.Controls.Add(this.gbSetting);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "AVR 온도 측정";
            this.gbSetting.ResumeLayout(false);
            this.gbSetting.PerformLayout();
            this.gbResult.ResumeLayout(false);
            this.gbResult.PerformLayout();
            this.ssBar.ResumeLayout(false);
            this.ssBar.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblTemp;
        private System.Windows.Forms.Label lblPort;
        private System.Windows.Forms.ComboBox cbPort;
        private System.Windows.Forms.Button btnOpen;
        private System.Windows.Forms.Button btnClose;
        private System.Windows.Forms.Button btnGet;
        private System.Windows.Forms.Button btnStop;
        private System.Windows.Forms.Label lblTimer;
        private System.Windows.Forms.ComboBox cbInterval;
        private System.Windows.Forms.Label lblSec;
        private System.Windows.Forms.Label lblRxTemp;
        private System.Windows.Forms.Label lblUnit;
        private System.Windows.Forms.GroupBox gbSetting;
        private System.Windows.Forms.GroupBox gbResult;
        private System.Windows.Forms.StatusStrip ssBar;
        private System.Windows.Forms.ToolStripStatusLabel lblStatus;
    }
}


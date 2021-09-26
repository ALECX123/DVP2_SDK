namespace ImageAcquisition
{
    partial class ImageAcquisition
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
			this.General = new System.Windows.Forms.GroupBox();
			this.PropertSet = new System.Windows.Forms.Button();
			this.StartPlay = new System.Windows.Forms.Button();
			this.ScanDev = new System.Windows.Forms.Button();
			this.OpenDev = new System.Windows.Forms.Button();
			this.DevNameCombo = new System.Windows.Forms.ComboBox();
			this.pictureBox = new System.Windows.Forms.PictureBox();
			this.label1 = new System.Windows.Forms.Label();
			this.Configuration = new System.Windows.Forms.GroupBox();
			this.EditWait = new System.Windows.Forms.TextBox();
			this.SoftTrigger = new System.Windows.Forms.CheckBox();
			this.DisplayImage = new System.Windows.Forms.GroupBox();
			this.Display = new System.Windows.Forms.CheckBox();
			this.SaveImage = new System.Windows.Forms.GroupBox();
			this.OpenFolder = new System.Windows.Forms.Button();
			this.SelectPath = new System.Windows.Forms.Button();
			this.EditPath = new System.Windows.Forms.TextBox();
			this.Counts = new System.Windows.Forms.Label();
			this.SaveImageCheck = new System.Windows.Forms.CheckBox();
			this.General.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
			this.Configuration.SuspendLayout();
			this.DisplayImage.SuspendLayout();
			this.SaveImage.SuspendLayout();
			this.SuspendLayout();
			// 
			// General
			// 
			this.General.Controls.Add(this.PropertSet);
			this.General.Controls.Add(this.StartPlay);
			this.General.Controls.Add(this.ScanDev);
			this.General.Controls.Add(this.OpenDev);
			this.General.Controls.Add(this.DevNameCombo);
			this.General.Location = new System.Drawing.Point(12, 12);
			this.General.Name = "General";
			this.General.Size = new System.Drawing.Size(232, 85);
			this.General.TabIndex = 17;
			this.General.TabStop = false;
			this.General.Text = "General";
			// 
			// PropertSet
			// 
			this.PropertSet.Location = new System.Drawing.Point(159, 54);
			this.PropertSet.Name = "PropertSet";
			this.PropertSet.Size = new System.Drawing.Size(57, 23);
			this.PropertSet.TabIndex = 5;
			this.PropertSet.Text = "Property";
			this.PropertSet.UseVisualStyleBackColor = true;
			this.PropertSet.Click += new System.EventHandler(this.PropertSet_Click);
			// 
			// StartPlay
			// 
			this.StartPlay.Location = new System.Drawing.Point(87, 54);
			this.StartPlay.Name = "StartPlay";
			this.StartPlay.Size = new System.Drawing.Size(57, 23);
			this.StartPlay.TabIndex = 4;
			this.StartPlay.Text = "Start";
			this.StartPlay.UseVisualStyleBackColor = true;
			this.StartPlay.Click += new System.EventHandler(this.StsartPlay_Click);
			// 
			// ScanDev
			// 
			this.ScanDev.Location = new System.Drawing.Point(159, 27);
			this.ScanDev.Name = "ScanDev";
			this.ScanDev.Size = new System.Drawing.Size(57, 23);
			this.ScanDev.TabIndex = 3;
			this.ScanDev.Text = "Scan";
			this.ScanDev.UseVisualStyleBackColor = true;
			this.ScanDev.Click += new System.EventHandler(this.ScanDev_Click);
			// 
			// OpenDev
			// 
			this.OpenDev.Location = new System.Drawing.Point(15, 54);
			this.OpenDev.Name = "OpenDev";
			this.OpenDev.Size = new System.Drawing.Size(57, 23);
			this.OpenDev.TabIndex = 2;
			this.OpenDev.Text = "Open";
			this.OpenDev.UseVisualStyleBackColor = true;
			this.OpenDev.Click += new System.EventHandler(this.OpenDev_Click);
			// 
			// DevNameCombo
			// 
			this.DevNameCombo.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.DevNameCombo.FormattingEnabled = true;
			this.DevNameCombo.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.DevNameCombo.Location = new System.Drawing.Point(15, 28);
			this.DevNameCombo.Name = "DevNameCombo";
			this.DevNameCombo.Size = new System.Drawing.Size(138, 20);
			this.DevNameCombo.TabIndex = 0;
			// 
			// pictureBox
			// 
			this.pictureBox.BackColor = System.Drawing.SystemColors.ActiveBorder;
			this.pictureBox.Location = new System.Drawing.Point(250, 12);
			this.pictureBox.Name = "pictureBox";
			this.pictureBox.Size = new System.Drawing.Size(653, 571);
			this.pictureBox.TabIndex = 16;
			this.pictureBox.TabStop = false;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(10, 23);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(89, 12);
			this.label1.TabIndex = 18;
			this.label1.Text = "Wait Timer(ms)";
			// 
			// Configuration
			// 
			this.Configuration.Controls.Add(this.EditWait);
			this.Configuration.Controls.Add(this.SoftTrigger);
			this.Configuration.Controls.Add(this.label1);
			this.Configuration.Location = new System.Drawing.Point(15, 107);
			this.Configuration.Name = "Configuration";
			this.Configuration.Size = new System.Drawing.Size(228, 72);
			this.Configuration.TabIndex = 19;
			this.Configuration.TabStop = false;
			this.Configuration.Text = "Configuration";
			// 
			// EditWait
			// 
			this.EditWait.Location = new System.Drawing.Point(105, 20);
			this.EditWait.Name = "EditWait";
			this.EditWait.Size = new System.Drawing.Size(100, 21);
			this.EditWait.TabIndex = 21;
			// 
			// SoftTrigger
			// 
			this.SoftTrigger.AutoSize = true;
			this.SoftTrigger.Location = new System.Drawing.Point(12, 47);
			this.SoftTrigger.Name = "SoftTrigger";
			this.SoftTrigger.Size = new System.Drawing.Size(96, 16);
			this.SoftTrigger.TabIndex = 19;
			this.SoftTrigger.Text = "Soft Trigger";
			this.SoftTrigger.UseVisualStyleBackColor = true;
			// 
			// DisplayImage
			// 
			this.DisplayImage.Controls.Add(this.Display);
			this.DisplayImage.Location = new System.Drawing.Point(17, 191);
			this.DisplayImage.Name = "DisplayImage";
			this.DisplayImage.Size = new System.Drawing.Size(225, 47);
			this.DisplayImage.TabIndex = 21;
			this.DisplayImage.TabStop = false;
			this.DisplayImage.Text = "Display Image";
			// 
			// Display
			// 
			this.Display.AutoSize = true;
			this.Display.Location = new System.Drawing.Point(33, 23);
			this.Display.Name = "Display";
			this.Display.Size = new System.Drawing.Size(66, 16);
			this.Display.TabIndex = 0;
			this.Display.Text = "Display";
			this.Display.UseVisualStyleBackColor = true;
			// 
			// SaveImage
			// 
			this.SaveImage.Controls.Add(this.OpenFolder);
			this.SaveImage.Controls.Add(this.SelectPath);
			this.SaveImage.Controls.Add(this.EditPath);
			this.SaveImage.Controls.Add(this.Counts);
			this.SaveImage.Controls.Add(this.SaveImageCheck);
			this.SaveImage.Location = new System.Drawing.Point(17, 244);
			this.SaveImage.Name = "SaveImage";
			this.SaveImage.Size = new System.Drawing.Size(225, 96);
			this.SaveImage.TabIndex = 22;
			this.SaveImage.TabStop = false;
			this.SaveImage.Text = "Save Image";
			// 
			// OpenFolder
			// 
			this.OpenFolder.Location = new System.Drawing.Point(115, 66);
			this.OpenFolder.Name = "OpenFolder";
			this.OpenFolder.Size = new System.Drawing.Size(88, 23);
			this.OpenFolder.TabIndex = 25;
			this.OpenFolder.Text = "Open Folder";
			this.OpenFolder.UseVisualStyleBackColor = true;
			this.OpenFolder.Click += new System.EventHandler(this.OpenFolder_Click);
			// 
			// SelectPath
			// 
			this.SelectPath.Location = new System.Drawing.Point(10, 66);
			this.SelectPath.Name = "SelectPath";
			this.SelectPath.Size = new System.Drawing.Size(88, 23);
			this.SelectPath.TabIndex = 24;
			this.SelectPath.Text = "Select Path";
			this.SelectPath.UseVisualStyleBackColor = true;
			this.SelectPath.Click += new System.EventHandler(this.SelectPath_Click);
			// 
			// EditPath
			// 
			this.EditPath.Location = new System.Drawing.Point(10, 42);
			this.EditPath.Name = "EditPath";
			this.EditPath.ReadOnly = true;
			this.EditPath.Size = new System.Drawing.Size(201, 21);
			this.EditPath.TabIndex = 23;
			// 
			// Counts
			// 
			this.Counts.AutoSize = true;
			this.Counts.Location = new System.Drawing.Point(147, 23);
			this.Counts.Name = "Counts";
			this.Counts.Size = new System.Drawing.Size(41, 12);
			this.Counts.TabIndex = 1;
			this.Counts.Text = "Counts";
			// 
			// SaveImageCheck
			// 
			this.SaveImageCheck.AutoSize = true;
			this.SaveImageCheck.Location = new System.Drawing.Point(33, 21);
			this.SaveImageCheck.Name = "SaveImageCheck";
			this.SaveImageCheck.Size = new System.Drawing.Size(84, 16);
			this.SaveImageCheck.TabIndex = 0;
			this.SaveImageCheck.Text = "Save Image";
			this.SaveImageCheck.UseVisualStyleBackColor = true;
			// 
			// ImageAcquisition
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(910, 589);
			this.Controls.Add(this.SaveImage);
			this.Controls.Add(this.DisplayImage);
			this.Controls.Add(this.Configuration);
			this.Controls.Add(this.General);
			this.Controls.Add(this.pictureBox);
			this.Name = "ImageAcquisition";
			this.Text = "Form1";
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.ImageAcquisition_FormClosing);
			this.General.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
			this.Configuration.ResumeLayout(false);
			this.Configuration.PerformLayout();
			this.DisplayImage.ResumeLayout(false);
			this.DisplayImage.PerformLayout();
			this.SaveImage.ResumeLayout(false);
			this.SaveImage.PerformLayout();
			this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox General;
        private System.Windows.Forms.Button PropertSet;
        private System.Windows.Forms.Button StartPlay;
        private System.Windows.Forms.Button ScanDev;
        private System.Windows.Forms.Button OpenDev;
        private System.Windows.Forms.ComboBox DevNameCombo;
        private System.Windows.Forms.PictureBox pictureBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox Configuration;
        private System.Windows.Forms.TextBox EditWait;
		private System.Windows.Forms.CheckBox SoftTrigger;
        private System.Windows.Forms.GroupBox DisplayImage;
        private System.Windows.Forms.CheckBox Display;
        private System.Windows.Forms.GroupBox SaveImage;
        private System.Windows.Forms.Button OpenFolder;
        private System.Windows.Forms.Button SelectPath;
        private System.Windows.Forms.TextBox EditPath;
        private System.Windows.Forms.Label Counts;
        private System.Windows.Forms.CheckBox SaveImageCheck;
    }
}


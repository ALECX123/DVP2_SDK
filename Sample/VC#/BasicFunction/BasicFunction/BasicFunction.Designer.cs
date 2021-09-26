namespace BasicFunction
{
    partial class BasicFunction
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
            this.COMBO_DEVICES = new System.Windows.Forms.ComboBox();
            this.BUTTON_OPEN = new System.Windows.Forms.Button();
            this.BUTTON_SCAN = new System.Windows.Forms.Button();
            this.BUTTON_START = new System.Windows.Forms.Button();
            this.BUTTON_PROPERTY = new System.Windows.Forms.Button();
            this.pictureBox = new System.Windows.Forms.PictureBox();
            this.BUTTON_SAVE = new System.Windows.Forms.Button();
            this.SLIDER_EXPOSURE_TIME = new System.Windows.Forms.TrackBar();
            this.COMBO_FLICK = new System.Windows.Forms.ComboBox();
            this.General = new System.Windows.Forms.GroupBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.CHECK_AEOPERATION = new System.Windows.Forms.CheckBox();
            this.COMBO_AE_MODE = new System.Windows.Forms.ComboBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.AE_Mode = new System.Windows.Forms.Label();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.STATIC_EXPOTIME = new System.Windows.Forms.Label();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.groupBox11 = new System.Windows.Forms.GroupBox();
            this.label5 = new System.Windows.Forms.Label();
            this.STATIC_EXPOGAIN = new System.Windows.Forms.Label();
            this.SLIDER_GAIN = new System.Windows.Forms.TrackBar();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.COMBO_RESOLUTION = new System.Windows.Forms.ComboBox();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.SLIDER_EXPOSURE_TIME)).BeginInit();
            this.General.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.groupBox11.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.SLIDER_GAIN)).BeginInit();
            this.groupBox7.SuspendLayout();
            this.SuspendLayout();
            // 
            // COMBO_DEVICES
            // 
            this.COMBO_DEVICES.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.COMBO_DEVICES.FormattingEnabled = true;
            this.COMBO_DEVICES.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.COMBO_DEVICES.Location = new System.Drawing.Point(15, 28);
            this.COMBO_DEVICES.Name = "COMBO_DEVICES";
            this.COMBO_DEVICES.Size = new System.Drawing.Size(138, 20);
            this.COMBO_DEVICES.TabIndex = 0;
            // 
            // BUTTON_OPEN
            // 
            this.BUTTON_OPEN.Location = new System.Drawing.Point(15, 54);
            this.BUTTON_OPEN.Name = "BUTTON_OPEN";
            this.BUTTON_OPEN.Size = new System.Drawing.Size(57, 23);
            this.BUTTON_OPEN.TabIndex = 2;
            this.BUTTON_OPEN.Text = "Open";
            this.BUTTON_OPEN.UseVisualStyleBackColor = true;
            this.BUTTON_OPEN.Click += new System.EventHandler(this.BUTTON_OPEN_Click);
            // 
            // BUTTON_SCAN
            // 
            this.BUTTON_SCAN.Location = new System.Drawing.Point(159, 27);
            this.BUTTON_SCAN.Name = "BUTTON_SCAN";
            this.BUTTON_SCAN.Size = new System.Drawing.Size(57, 23);
            this.BUTTON_SCAN.TabIndex = 3;
            this.BUTTON_SCAN.Text = "Scan";
            this.BUTTON_SCAN.UseVisualStyleBackColor = true;
            this.BUTTON_SCAN.Click += new System.EventHandler(this.BUTTON_SCAN_Click);
            // 
            // BUTTON_START
            // 
            this.BUTTON_START.Location = new System.Drawing.Point(87, 54);
            this.BUTTON_START.Name = "BUTTON_START";
            this.BUTTON_START.Size = new System.Drawing.Size(57, 23);
            this.BUTTON_START.TabIndex = 4;
            this.BUTTON_START.Text = "Start";
            this.BUTTON_START.UseVisualStyleBackColor = true;
            this.BUTTON_START.Click += new System.EventHandler(this.BUTTON_START_Click);
            // 
            // BUTTON_PROPERTY
            // 
            this.BUTTON_PROPERTY.Location = new System.Drawing.Point(159, 54);
            this.BUTTON_PROPERTY.Name = "BUTTON_PROPERTY";
            this.BUTTON_PROPERTY.Size = new System.Drawing.Size(57, 23);
            this.BUTTON_PROPERTY.TabIndex = 5;
            this.BUTTON_PROPERTY.Text = "Property";
            this.BUTTON_PROPERTY.UseVisualStyleBackColor = true;
            this.BUTTON_PROPERTY.Click += new System.EventHandler(this.BUTTON_PROPERTY_Click);
            // 
            // pictureBox
            // 
            this.pictureBox.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.pictureBox.Location = new System.Drawing.Point(248, 7);
            this.pictureBox.Name = "pictureBox";
            this.pictureBox.Size = new System.Drawing.Size(653, 571);
            this.pictureBox.TabIndex = 6;
            this.pictureBox.TabStop = false;
            // 
            // BUTTON_SAVE
            // 
            this.BUTTON_SAVE.Location = new System.Drawing.Point(144, 16);
            this.BUTTON_SAVE.Name = "BUTTON_SAVE";
            this.BUTTON_SAVE.Size = new System.Drawing.Size(72, 23);
            this.BUTTON_SAVE.TabIndex = 7;
            this.BUTTON_SAVE.Text = "Save";
            this.BUTTON_SAVE.UseVisualStyleBackColor = true;
            this.BUTTON_SAVE.Click += new System.EventHandler(this.BUTTON_SAVE_Click);
            // 
            // SLIDER_EXPOSURE_TIME
            // 
            this.SLIDER_EXPOSURE_TIME.AutoSize = false;
            this.SLIDER_EXPOSURE_TIME.LargeChange = 1;
            this.SLIDER_EXPOSURE_TIME.Location = new System.Drawing.Point(25, 23);
            this.SLIDER_EXPOSURE_TIME.Name = "SLIDER_EXPOSURE_TIME";
            this.SLIDER_EXPOSURE_TIME.Size = new System.Drawing.Size(186, 23);
            this.SLIDER_EXPOSURE_TIME.TabIndex = 10;
            this.SLIDER_EXPOSURE_TIME.TickStyle = System.Windows.Forms.TickStyle.None;
            this.SLIDER_EXPOSURE_TIME.ValueChanged += new System.EventHandler(this.SLIDER_EXPOSURE_TIME_ValueChanged);
            // 
            // COMBO_FLICK
            // 
            this.COMBO_FLICK.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.COMBO_FLICK.FormattingEnabled = true;
            this.COMBO_FLICK.Location = new System.Drawing.Point(25, 24);
            this.COMBO_FLICK.Name = "COMBO_FLICK";
            this.COMBO_FLICK.Size = new System.Drawing.Size(187, 20);
            this.COMBO_FLICK.TabIndex = 11;
            this.COMBO_FLICK.SelectedIndexChanged += new System.EventHandler(this.COMBO_FLICK_SelectedIndexChanged);
            // 
            // General
            // 
            this.General.Controls.Add(this.BUTTON_PROPERTY);
            this.General.Controls.Add(this.BUTTON_START);
            this.General.Controls.Add(this.BUTTON_SCAN);
            this.General.Controls.Add(this.BUTTON_OPEN);
            this.General.Controls.Add(this.COMBO_DEVICES);
            this.General.Location = new System.Drawing.Point(10, 7);
            this.General.Name = "General";
            this.General.Size = new System.Drawing.Size(232, 85);
            this.General.TabIndex = 15;
            this.General.TabStop = false;
            this.General.Text = "General";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.BUTTON_SAVE);
            this.groupBox3.Location = new System.Drawing.Point(10, 99);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(231, 48);
            this.groupBox3.TabIndex = 16;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Save Picture";
            // 
            // CHECK_AEOPERATION
            // 
            this.CHECK_AEOPERATION.AutoSize = true;
            this.CHECK_AEOPERATION.Location = new System.Drawing.Point(13, 20);
            this.CHECK_AEOPERATION.Name = "CHECK_AEOPERATION";
            this.CHECK_AEOPERATION.Size = new System.Drawing.Size(78, 16);
            this.CHECK_AEOPERATION.TabIndex = 8;
            this.CHECK_AEOPERATION.Text = "AE Enable";
            this.CHECK_AEOPERATION.UseVisualStyleBackColor = true;
            this.CHECK_AEOPERATION.Click += new System.EventHandler(this.CHECK_AEOPERATION_Click);
            // 
            // COMBO_AE_MODE
            // 
            this.COMBO_AE_MODE.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.COMBO_AE_MODE.FormattingEnabled = true;
            this.COMBO_AE_MODE.Location = new System.Drawing.Point(67, 52);
            this.COMBO_AE_MODE.Name = "COMBO_AE_MODE";
            this.COMBO_AE_MODE.Size = new System.Drawing.Size(147, 20);
            this.COMBO_AE_MODE.TabIndex = 9;
            this.COMBO_AE_MODE.SelectedIndexChanged += new System.EventHandler(this.COMBO_AE_MODE_SelectedIndexChanged);
            this.COMBO_AE_MODE.ImeModeChanged += new System.EventHandler(this.COMBO_AE_MODE_ImeModeChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.AE_Mode);
            this.groupBox1.Controls.Add(this.COMBO_AE_MODE);
            this.groupBox1.Controls.Add(this.CHECK_AEOPERATION);
            this.groupBox1.Location = new System.Drawing.Point(12, 153);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(214, 78);
            this.groupBox1.TabIndex = 14;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Auto Exposure";
            // 
            // AE_Mode
            // 
            this.AE_Mode.AutoSize = true;
            this.AE_Mode.Location = new System.Drawing.Point(11, 52);
            this.AE_Mode.Name = "AE_Mode";
            this.AE_Mode.Size = new System.Drawing.Size(47, 12);
            this.AE_Mode.TabIndex = 10;
            this.AE_Mode.Text = "AE Mode";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.label1);
            this.groupBox4.Controls.Add(this.label3);
            this.groupBox4.Controls.Add(this.STATIC_EXPOTIME);
            this.groupBox4.Controls.Add(this.SLIDER_EXPOSURE_TIME);
            this.groupBox4.Location = new System.Drawing.Point(10, 236);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(231, 67);
            this.groupBox4.TabIndex = 17;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Exposure Time";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(122, 49);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(17, 12);
            this.label1.TabIndex = 19;
            this.label1.Text = "us";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(112, 48);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(0, 12);
            this.label3.TabIndex = 18;
            // 
            // STATIC_EXPOTIME
            // 
            this.STATIC_EXPOTIME.AutoSize = true;
            this.STATIC_EXPOTIME.Location = new System.Drawing.Point(31, 49);
            this.STATIC_EXPOTIME.Name = "STATIC_EXPOTIME";
            this.STATIC_EXPOTIME.Size = new System.Drawing.Size(11, 12);
            this.STATIC_EXPOTIME.TabIndex = 18;
            this.STATIC_EXPOTIME.Text = "0";
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.COMBO_FLICK);
            this.groupBox5.Location = new System.Drawing.Point(14, 309);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(226, 51);
            this.groupBox5.TabIndex = 19;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Anti Flick";
            // 
            // groupBox11
            // 
            this.groupBox11.Controls.Add(this.label5);
            this.groupBox11.Controls.Add(this.STATIC_EXPOGAIN);
            this.groupBox11.Controls.Add(this.SLIDER_GAIN);
            this.groupBox11.Location = new System.Drawing.Point(14, 375);
            this.groupBox11.Name = "groupBox11";
            this.groupBox11.Size = new System.Drawing.Size(231, 67);
            this.groupBox11.TabIndex = 20;
            this.groupBox11.TabStop = false;
            this.groupBox11.Text = "Gain";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(112, 48);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(0, 12);
            this.label5.TabIndex = 18;
            // 
            // STATIC_EXPOGAIN
            // 
            this.STATIC_EXPOGAIN.AutoSize = true;
            this.STATIC_EXPOGAIN.Location = new System.Drawing.Point(31, 48);
            this.STATIC_EXPOGAIN.Name = "STATIC_EXPOGAIN";
            this.STATIC_EXPOGAIN.Size = new System.Drawing.Size(11, 12);
            this.STATIC_EXPOGAIN.TabIndex = 18;
            this.STATIC_EXPOGAIN.Text = "0";
            // 
            // SLIDER_GAIN
            // 
            this.SLIDER_GAIN.AutoSize = false;
            this.SLIDER_GAIN.LargeChange = 1;
            this.SLIDER_GAIN.Location = new System.Drawing.Point(25, 23);
            this.SLIDER_GAIN.Name = "SLIDER_GAIN";
            this.SLIDER_GAIN.Size = new System.Drawing.Size(186, 23);
            this.SLIDER_GAIN.TabIndex = 10;
            this.SLIDER_GAIN.TickStyle = System.Windows.Forms.TickStyle.None;
            this.SLIDER_GAIN.ValueChanged += new System.EventHandler(this.SLIDER_GAIN_ValueChanged);
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.COMBO_RESOLUTION);
            this.groupBox7.Location = new System.Drawing.Point(19, 455);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(226, 51);
            this.groupBox7.TabIndex = 21;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "Quick ROI";
            // 
            // COMBO_RESOLUTION
            // 
            this.COMBO_RESOLUTION.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.COMBO_RESOLUTION.FormattingEnabled = true;
            this.COMBO_RESOLUTION.Location = new System.Drawing.Point(20, 24);
            this.COMBO_RESOLUTION.Name = "COMBO_RESOLUTION";
            this.COMBO_RESOLUTION.Size = new System.Drawing.Size(192, 20);
            this.COMBO_RESOLUTION.TabIndex = 11;
            this.COMBO_RESOLUTION.SelectedIndexChanged += new System.EventHandler(this.COMBO_RESOLUTION_SelectedIndexChanged);
            // 
            // BasicFunction
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(904, 581);
            this.Controls.Add(this.groupBox7);
            this.Controls.Add(this.groupBox11);
            this.Controls.Add(this.groupBox5);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.General);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.pictureBox);
            this.MinimizeBox = false;
            this.Name = "BasicFunction";
            this.Text = "BasicFunction";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.BasicFunction_FormClosing);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.SLIDER_EXPOSURE_TIME)).EndInit();
            this.General.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox11.ResumeLayout(false);
            this.groupBox11.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.SLIDER_GAIN)).EndInit();
            this.groupBox7.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ComboBox COMBO_DEVICES;
        private System.Windows.Forms.Button BUTTON_OPEN;
        private System.Windows.Forms.Button BUTTON_SCAN;
        private System.Windows.Forms.Button BUTTON_START;
        private System.Windows.Forms.Button BUTTON_PROPERTY;
        private System.Windows.Forms.PictureBox pictureBox;
        private System.Windows.Forms.Button BUTTON_SAVE;
        private System.Windows.Forms.TrackBar SLIDER_EXPOSURE_TIME;
        private System.Windows.Forms.ComboBox COMBO_FLICK;
        private System.Windows.Forms.GroupBox General;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.CheckBox CHECK_AEOPERATION;
        private System.Windows.Forms.ComboBox COMBO_AE_MODE;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label AE_Mode;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label STATIC_EXPOTIME;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.GroupBox groupBox11;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label STATIC_EXPOGAIN;
        private System.Windows.Forms.TrackBar SLIDER_GAIN;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.ComboBox COMBO_RESOLUTION;
        private System.Windows.Forms.Label label1;
    }
}


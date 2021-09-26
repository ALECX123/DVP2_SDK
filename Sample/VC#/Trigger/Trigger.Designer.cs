namespace Trigger
{
    partial class Trigger
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
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.ApplyDelay = new System.Windows.Forms.Button();
			this.ApplyLoop = new System.Windows.Forms.Button();
			this.label2 = new System.Windows.Forms.Label();
			this.label1 = new System.Windows.Forms.Label();
			this.SoftTriggerFire = new System.Windows.Forms.Button();
			this.LoopTrigger = new System.Windows.Forms.CheckBox();
			this.TriggerMode = new System.Windows.Forms.CheckBox();
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.FilterApply = new System.Windows.Forms.Button();
			this.label5 = new System.Windows.Forms.Label();
			this.InputSignalTypeCombo = new System.Windows.Forms.ComboBox();
			this.InputIOCombo = new System.Windows.Forms.ComboBox();
			this.InputSignalType = new System.Windows.Forms.Label();
			this.InputIO = new System.Windows.Forms.Label();
			this.EnableIn = new System.Windows.Forms.CheckBox();
			this.groupBox3 = new System.Windows.Forms.GroupBox();
			this.OutputSignalType = new System.Windows.Forms.ComboBox();
			this.OutIOCombo = new System.Windows.Forms.ComboBox();
			this.label7 = new System.Windows.Forms.Label();
			this.label8 = new System.Windows.Forms.Label();
			this.EnableOut = new System.Windows.Forms.CheckBox();
			this.pictureBox = new System.Windows.Forms.PictureBox();
			this.TriggerLoop = new System.Windows.Forms.TextBox();
			this.TriggerDelay = new System.Windows.Forms.TextBox();
			this.EditFilter = new System.Windows.Forms.TextBox();
			this.General.SuspendLayout();
			this.groupBox1.SuspendLayout();
			this.groupBox2.SuspendLayout();
			this.groupBox3.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
			this.SuspendLayout();
			// 
			// General
			// 
			this.General.Controls.Add(this.PropertSet);
			this.General.Controls.Add(this.StartPlay);
			this.General.Controls.Add(this.ScanDev);
			this.General.Controls.Add(this.OpenDev);
			this.General.Controls.Add(this.DevNameCombo);
			this.General.Location = new System.Drawing.Point(2, 9);
			this.General.Name = "General";
			this.General.Size = new System.Drawing.Size(260, 72);
			this.General.TabIndex = 18;
			this.General.TabStop = false;
			this.General.Text = "General";
			// 
			// PropertSet
			// 
			this.PropertSet.Location = new System.Drawing.Point(187, 43);
			this.PropertSet.Name = "PropertSet";
			this.PropertSet.Size = new System.Drawing.Size(67, 23);
			this.PropertSet.TabIndex = 5;
			this.PropertSet.Text = "Property";
			this.PropertSet.UseVisualStyleBackColor = true;
			this.PropertSet.Click += new System.EventHandler(this.PropertSet_Click);
			// 
			// StartPlay
			// 
			this.StartPlay.Location = new System.Drawing.Point(101, 43);
			this.StartPlay.Name = "StartPlay";
			this.StartPlay.Size = new System.Drawing.Size(80, 23);
			this.StartPlay.TabIndex = 4;
			this.StartPlay.Text = "Start";
			this.StartPlay.UseVisualStyleBackColor = true;
			this.StartPlay.Click += new System.EventHandler(this.StartPlay_Click);
			// 
			// ScanDev
			// 
			this.ScanDev.Location = new System.Drawing.Point(187, 17);
			this.ScanDev.Name = "ScanDev";
			this.ScanDev.Size = new System.Drawing.Size(67, 23);
			this.ScanDev.TabIndex = 3;
			this.ScanDev.Text = "Scan";
			this.ScanDev.UseVisualStyleBackColor = true;
			this.ScanDev.Click += new System.EventHandler(this.ScanDev_Click);
			// 
			// OpenDev
			// 
			this.OpenDev.Location = new System.Drawing.Point(10, 43);
			this.OpenDev.Name = "OpenDev";
			this.OpenDev.Size = new System.Drawing.Size(80, 23);
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
			this.DevNameCombo.Location = new System.Drawing.Point(10, 18);
			this.DevNameCombo.Name = "DevNameCombo";
			this.DevNameCombo.Size = new System.Drawing.Size(171, 20);
			this.DevNameCombo.TabIndex = 0;
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.TriggerDelay);
			this.groupBox1.Controls.Add(this.TriggerLoop);
			this.groupBox1.Controls.Add(this.ApplyDelay);
			this.groupBox1.Controls.Add(this.ApplyLoop);
			this.groupBox1.Controls.Add(this.label2);
			this.groupBox1.Controls.Add(this.label1);
			this.groupBox1.Controls.Add(this.SoftTriggerFire);
			this.groupBox1.Controls.Add(this.LoopTrigger);
			this.groupBox1.Controls.Add(this.TriggerMode);
			this.groupBox1.Location = new System.Drawing.Point(2, 87);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(259, 123);
			this.groupBox1.TabIndex = 19;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Trigger";
			// 
			// ApplyDelay
			// 
			this.ApplyDelay.Location = new System.Drawing.Point(187, 95);
			this.ApplyDelay.Name = "ApplyDelay";
			this.ApplyDelay.Size = new System.Drawing.Size(66, 21);
			this.ApplyDelay.TabIndex = 8;
			this.ApplyDelay.Text = "Apply";
			this.ApplyDelay.UseVisualStyleBackColor = true;
			this.ApplyDelay.Click += new System.EventHandler(this.ApplyDelay_Click);
			// 
			// ApplyLoop
			// 
			this.ApplyLoop.Location = new System.Drawing.Point(187, 66);
			this.ApplyLoop.Name = "ApplyLoop";
			this.ApplyLoop.Size = new System.Drawing.Size(66, 21);
			this.ApplyLoop.TabIndex = 7;
			this.ApplyLoop.Text = "Apply";
			this.ApplyLoop.UseVisualStyleBackColor = true;
			this.ApplyLoop.Click += new System.EventHandler(this.ApplyLoop_Click);
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(10, 97);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(59, 12);
			this.label2.TabIndex = 4;
			this.label2.Text = "Delay(us)";
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(10, 68);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(89, 12);
			this.label1.TabIndex = 3;
			this.label1.Text = "Loop Timer(us)";
			// 
			// SoftTriggerFire
			// 
			this.SoftTriggerFire.Location = new System.Drawing.Point(129, 16);
			this.SoftTriggerFire.Name = "SoftTriggerFire";
			this.SoftTriggerFire.Size = new System.Drawing.Size(124, 23);
			this.SoftTriggerFire.TabIndex = 2;
			this.SoftTriggerFire.Text = "Soft Trigger Fire";
			this.SoftTriggerFire.UseVisualStyleBackColor = true;
			this.SoftTriggerFire.Click += new System.EventHandler(this.SoftTriggerFire_Click);
			// 
			// LoopTrigger
			// 
			this.LoopTrigger.AutoSize = true;
			this.LoopTrigger.Location = new System.Drawing.Point(10, 42);
			this.LoopTrigger.Name = "LoopTrigger";
			this.LoopTrigger.Size = new System.Drawing.Size(90, 16);
			this.LoopTrigger.TabIndex = 1;
			this.LoopTrigger.Text = "LoopTrigger";
			this.LoopTrigger.UseVisualStyleBackColor = true;
			this.LoopTrigger.CheckedChanged += new System.EventHandler(this.LoopTrigger_CheckedChanged);
			// 
			// TriggerMode
			// 
			this.TriggerMode.AutoSize = true;
			this.TriggerMode.Location = new System.Drawing.Point(10, 20);
			this.TriggerMode.Name = "TriggerMode";
			this.TriggerMode.Size = new System.Drawing.Size(90, 16);
			this.TriggerMode.TabIndex = 0;
			this.TriggerMode.Text = "TriggerMode";
			this.TriggerMode.UseVisualStyleBackColor = true;
			this.TriggerMode.CheckedChanged += new System.EventHandler(this.TriggerMode_CheckedChanged);
			// 
			// groupBox2
			// 
			this.groupBox2.Controls.Add(this.EditFilter);
			this.groupBox2.Controls.Add(this.FilterApply);
			this.groupBox2.Controls.Add(this.label5);
			this.groupBox2.Controls.Add(this.InputSignalTypeCombo);
			this.groupBox2.Controls.Add(this.InputIOCombo);
			this.groupBox2.Controls.Add(this.InputSignalType);
			this.groupBox2.Controls.Add(this.InputIO);
			this.groupBox2.Controls.Add(this.EnableIn);
			this.groupBox2.Location = new System.Drawing.Point(3, 216);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(259, 132);
			this.groupBox2.TabIndex = 20;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "Ext Trigger In";
			// 
			// FilterApply
			// 
			this.FilterApply.Location = new System.Drawing.Point(187, 98);
			this.FilterApply.Name = "FilterApply";
			this.FilterApply.Size = new System.Drawing.Size(66, 23);
			this.FilterApply.TabIndex = 7;
			this.FilterApply.Text = "Apply";
			this.FilterApply.UseVisualStyleBackColor = true;
			this.FilterApply.Click += new System.EventHandler(this.FilterApply_Click);
			// 
			// label5
			// 
			this.label5.AutoSize = true;
			this.label5.Location = new System.Drawing.Point(10, 105);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(107, 12);
			this.label5.TabIndex = 5;
			this.label5.Text = "Jitter Filter(us)";
			// 
			// InputSignalTypeCombo
			// 
			this.InputSignalTypeCombo.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.InputSignalTypeCombo.FormattingEnabled = true;
			this.InputSignalTypeCombo.Location = new System.Drawing.Point(152, 70);
			this.InputSignalTypeCombo.Name = "InputSignalTypeCombo";
			this.InputSignalTypeCombo.Size = new System.Drawing.Size(100, 20);
			this.InputSignalTypeCombo.TabIndex = 4;
			this.InputSignalTypeCombo.SelectedIndexChanged += new System.EventHandler(this.InputSignalTypeCombo_SelectedIndexChanged);
			// 
			// InputIOCombo
			// 
			this.InputIOCombo.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.InputIOCombo.FormattingEnabled = true;
			this.InputIOCombo.Location = new System.Drawing.Point(152, 44);
			this.InputIOCombo.Name = "InputIOCombo";
			this.InputIOCombo.Size = new System.Drawing.Size(100, 20);
			this.InputIOCombo.TabIndex = 3;
			this.InputIOCombo.SelectedIndexChanged += new System.EventHandler(this.InputIOCombo_SelectedIndexChanged);
			// 
			// InputSignalType
			// 
			this.InputSignalType.AutoSize = true;
			this.InputSignalType.Location = new System.Drawing.Point(10, 75);
			this.InputSignalType.Name = "InputSignalType";
			this.InputSignalType.Size = new System.Drawing.Size(107, 12);
			this.InputSignalType.TabIndex = 2;
			this.InputSignalType.Text = "Input Signal Type";
			// 
			// InputIO
			// 
			this.InputIO.AutoSize = true;
			this.InputIO.Location = new System.Drawing.Point(10, 47);
			this.InputIO.Name = "InputIO";
			this.InputIO.Size = new System.Drawing.Size(53, 12);
			this.InputIO.TabIndex = 1;
			this.InputIO.Text = "Input IO";
			// 
			// EnableIn
			// 
			this.EnableIn.AutoSize = true;
			this.EnableIn.Location = new System.Drawing.Point(10, 21);
			this.EnableIn.Name = "EnableIn";
			this.EnableIn.Size = new System.Drawing.Size(60, 16);
			this.EnableIn.TabIndex = 0;
			this.EnableIn.Text = "Enable";
			this.EnableIn.UseVisualStyleBackColor = true;
			this.EnableIn.CheckedChanged += new System.EventHandler(this.EnableIn_CheckedChanged);
			// 
			// groupBox3
			// 
			this.groupBox3.Controls.Add(this.OutputSignalType);
			this.groupBox3.Controls.Add(this.OutIOCombo);
			this.groupBox3.Controls.Add(this.label7);
			this.groupBox3.Controls.Add(this.label8);
			this.groupBox3.Controls.Add(this.EnableOut);
			this.groupBox3.Location = new System.Drawing.Point(3, 354);
			this.groupBox3.Name = "groupBox3";
			this.groupBox3.Size = new System.Drawing.Size(259, 93);
			this.groupBox3.TabIndex = 21;
			this.groupBox3.TabStop = false;
			this.groupBox3.Text = "Ext Strobe Out";
			// 
			// OutputSignalType
			// 
			this.OutputSignalType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.OutputSignalType.FormattingEnabled = true;
			this.OutputSignalType.Location = new System.Drawing.Point(153, 61);
			this.OutputSignalType.Name = "OutputSignalType";
			this.OutputSignalType.Size = new System.Drawing.Size(100, 20);
			this.OutputSignalType.TabIndex = 4;
			this.OutputSignalType.SelectedIndexChanged += new System.EventHandler(this.OutputSignalType_SelectedIndexChanged);
			// 
			// OutIOCombo
			// 
			this.OutIOCombo.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.OutIOCombo.FormattingEnabled = true;
			this.OutIOCombo.Location = new System.Drawing.Point(153, 37);
			this.OutIOCombo.Name = "OutIOCombo";
			this.OutIOCombo.Size = new System.Drawing.Size(100, 20);
			this.OutIOCombo.TabIndex = 3;
			this.OutIOCombo.SelectedIndexChanged += new System.EventHandler(this.OutIOCombo_SelectedIndexChanged);
			// 
			// label7
			// 
			this.label7.AutoSize = true;
			this.label7.Location = new System.Drawing.Point(10, 66);
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size(113, 12);
			this.label7.TabIndex = 2;
			this.label7.Text = "Output Signal Type";
			// 
			// label8
			// 
			this.label8.AutoSize = true;
			this.label8.Location = new System.Drawing.Point(10, 44);
			this.label8.Name = "label8";
			this.label8.Size = new System.Drawing.Size(59, 12);
			this.label8.TabIndex = 1;
			this.label8.Text = "Output IO";
			// 
			// EnableOut
			// 
			this.EnableOut.AutoSize = true;
			this.EnableOut.Location = new System.Drawing.Point(10, 22);
			this.EnableOut.Name = "EnableOut";
			this.EnableOut.Size = new System.Drawing.Size(60, 16);
			this.EnableOut.TabIndex = 0;
			this.EnableOut.Text = "Enable";
			this.EnableOut.UseVisualStyleBackColor = true;
			this.EnableOut.CheckedChanged += new System.EventHandler(this.EnableOut_CheckedChanged);
			// 
			// pictureBox
			// 
			this.pictureBox.BackColor = System.Drawing.SystemColors.ActiveBorder;
			this.pictureBox.Location = new System.Drawing.Point(268, 9);
			this.pictureBox.Name = "pictureBox";
			this.pictureBox.Size = new System.Drawing.Size(716, 593);
			this.pictureBox.TabIndex = 22;
			this.pictureBox.TabStop = false;
			// 
			// TriggerLoop
			// 
			this.TriggerLoop.Location = new System.Drawing.Point(105, 66);
			this.TriggerLoop.Name = "TriggerLoop";
			this.TriggerLoop.Size = new System.Drawing.Size(76, 21);
			this.TriggerLoop.TabIndex = 23;
			this.TriggerLoop.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.TriggerLoop_KeyPress);
			// 
			// TriggerDelay
			// 
			this.TriggerDelay.Location = new System.Drawing.Point(105, 93);
			this.TriggerDelay.Name = "TriggerDelay";
			this.TriggerDelay.Size = new System.Drawing.Size(76, 21);
			this.TriggerDelay.TabIndex = 24;
			this.TriggerDelay.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.TriggerDelay_KeyPress);
			// 
			// EditFilter
			// 
			this.EditFilter.Location = new System.Drawing.Point(123, 100);
			this.EditFilter.Name = "EditFilter";
			this.EditFilter.Size = new System.Drawing.Size(58, 21);
			this.EditFilter.TabIndex = 23;
			this.EditFilter.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.EditFilter_KeyPress);
			// 
			// Trigger
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(986, 609);
			this.Controls.Add(this.pictureBox);
			this.Controls.Add(this.groupBox3);
			this.Controls.Add(this.groupBox2);
			this.Controls.Add(this.groupBox1);
			this.Controls.Add(this.General);
			this.Name = "Trigger";
			this.Text = "Form1";
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Trigger_FormClosing);
			this.General.ResumeLayout(false);
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			this.groupBox2.ResumeLayout(false);
			this.groupBox2.PerformLayout();
			this.groupBox3.ResumeLayout(false);
			this.groupBox3.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
			this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox General;
        private System.Windows.Forms.Button PropertSet;
        private System.Windows.Forms.Button StartPlay;
        private System.Windows.Forms.Button ScanDev;
        private System.Windows.Forms.Button OpenDev;
        private System.Windows.Forms.ComboBox DevNameCombo;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button ApplyDelay;
        private System.Windows.Forms.Button ApplyLoop;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button SoftTriggerFire;
        private System.Windows.Forms.CheckBox LoopTrigger;
        private System.Windows.Forms.CheckBox TriggerMode;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button FilterApply;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox InputSignalTypeCombo;
        private System.Windows.Forms.ComboBox InputIOCombo;
        private System.Windows.Forms.Label InputSignalType;
        private System.Windows.Forms.Label InputIO;
        private System.Windows.Forms.CheckBox EnableIn;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.ComboBox OutputSignalType;
        private System.Windows.Forms.ComboBox OutIOCombo;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.CheckBox EnableOut;
		private System.Windows.Forms.PictureBox pictureBox;
		private System.Windows.Forms.TextBox TriggerDelay;
		private System.Windows.Forms.TextBox TriggerLoop;
		private System.Windows.Forms.TextBox EditFilter;
    }
}


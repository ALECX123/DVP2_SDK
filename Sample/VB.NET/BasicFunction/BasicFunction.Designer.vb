<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class BasicFunction
	Inherits System.Windows.Forms.Form

	'Form 重写 Dispose，以清理组件列表。
	<System.Diagnostics.DebuggerNonUserCode()> _
	Protected Overrides Sub Dispose(ByVal disposing As Boolean)
		Try
			If disposing AndAlso components IsNot Nothing Then
				components.Dispose()
			End If
		Finally
			MyBase.Dispose(disposing)
		End Try
	End Sub

	'Windows 窗体设计器所必需的
	Private components As System.ComponentModel.IContainer

	'注意: 以下过程是 Windows 窗体设计器所必需的
	'可以使用 Windows 窗体设计器修改它。
	'不要使用代码编辑器修改它。
	<System.Diagnostics.DebuggerStepThrough()> _
	Private Sub InitializeComponent()
		Me.groupBox11 = New System.Windows.Forms.GroupBox()
		Me.label5 = New System.Windows.Forms.Label()
		Me.STATIC_EXPOGAIN = New System.Windows.Forms.Label()
		Me.SLIDER_GAIN = New System.Windows.Forms.TrackBar()
		Me.groupBox5 = New System.Windows.Forms.GroupBox()
		Me.COMBO_FLICK = New System.Windows.Forms.ComboBox()
		Me.groupBox4 = New System.Windows.Forms.GroupBox()
		Me.label1 = New System.Windows.Forms.Label()
		Me.label3 = New System.Windows.Forms.Label()
		Me.STATIC_EXPOTIME = New System.Windows.Forms.Label()
		Me.SLIDER_EXPOSURE_TIME = New System.Windows.Forms.TrackBar()
		Me.groupBox7 = New System.Windows.Forms.GroupBox()
		Me.COMBO_RESOLUTION = New System.Windows.Forms.ComboBox()
		Me.AE_Mode = New System.Windows.Forms.Label()
		Me.COMBO_DEVICES = New System.Windows.Forms.ComboBox()
		Me.groupBox1 = New System.Windows.Forms.GroupBox()
		Me.COMBO_AE_MODE = New System.Windows.Forms.ComboBox()
		Me.CHECK_AEOPERATION = New System.Windows.Forms.CheckBox()
		Me.BUTTON_PROPERTY = New System.Windows.Forms.Button()
		Me.BUTTON_START = New System.Windows.Forms.Button()
		Me.BUTTON_SCAN = New System.Windows.Forms.Button()
		Me.BUTTON_OPEN = New System.Windows.Forms.Button()
		Me.pictureBox = New System.Windows.Forms.PictureBox()
		Me.BUTTON_SAVE = New System.Windows.Forms.Button()
		Me.groupBox3 = New System.Windows.Forms.GroupBox()
		Me.General = New System.Windows.Forms.GroupBox()
		Me.groupBox11.SuspendLayout()
		CType(Me.SLIDER_GAIN, System.ComponentModel.ISupportInitialize).BeginInit()
		Me.groupBox5.SuspendLayout()
		Me.groupBox4.SuspendLayout()
		CType(Me.SLIDER_EXPOSURE_TIME, System.ComponentModel.ISupportInitialize).BeginInit()
		Me.groupBox7.SuspendLayout()
		Me.groupBox1.SuspendLayout()
		CType(Me.pictureBox, System.ComponentModel.ISupportInitialize).BeginInit()
		Me.groupBox3.SuspendLayout()
		Me.General.SuspendLayout()
		Me.SuspendLayout()
		'
		'groupBox11
		'
		Me.groupBox11.Controls.Add(Me.label5)
		Me.groupBox11.Controls.Add(Me.STATIC_EXPOGAIN)
		Me.groupBox11.Controls.Add(Me.SLIDER_GAIN)
		Me.groupBox11.Location = New System.Drawing.Point(9, 377)
		Me.groupBox11.Name = "groupBox11"
		Me.groupBox11.Size = New System.Drawing.Size(231, 67)
		Me.groupBox11.TabIndex = 28
		Me.groupBox11.TabStop = False
		Me.groupBox11.Text = "Gain"
		'
		'label5
		'
		Me.label5.AutoSize = True
		Me.label5.Location = New System.Drawing.Point(112, 48)
		Me.label5.Name = "label5"
		Me.label5.Size = New System.Drawing.Size(0, 12)
		Me.label5.TabIndex = 18
		'
		'STATIC_EXPOGAIN
		'
		Me.STATIC_EXPOGAIN.AutoSize = True
		Me.STATIC_EXPOGAIN.Location = New System.Drawing.Point(31, 48)
		Me.STATIC_EXPOGAIN.Name = "STATIC_EXPOGAIN"
		Me.STATIC_EXPOGAIN.Size = New System.Drawing.Size(11, 12)
		Me.STATIC_EXPOGAIN.TabIndex = 18
		Me.STATIC_EXPOGAIN.Text = "0"
		'
		'SLIDER_GAIN
		'
		Me.SLIDER_GAIN.AutoSize = False
		Me.SLIDER_GAIN.LargeChange = 1
		Me.SLIDER_GAIN.Location = New System.Drawing.Point(25, 23)
		Me.SLIDER_GAIN.Name = "SLIDER_GAIN"
		Me.SLIDER_GAIN.Size = New System.Drawing.Size(186, 23)
		Me.SLIDER_GAIN.TabIndex = 10
		Me.SLIDER_GAIN.TickStyle = System.Windows.Forms.TickStyle.None
		'
		'groupBox5
		'
		Me.groupBox5.Controls.Add(Me.COMBO_FLICK)
		Me.groupBox5.Location = New System.Drawing.Point(9, 311)
		Me.groupBox5.Name = "groupBox5"
		Me.groupBox5.Size = New System.Drawing.Size(226, 51)
		Me.groupBox5.TabIndex = 27
		Me.groupBox5.TabStop = False
		Me.groupBox5.Text = "Anti Flick"
		'
		'COMBO_FLICK
		'
		Me.COMBO_FLICK.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
		Me.COMBO_FLICK.FormattingEnabled = True
		Me.COMBO_FLICK.Location = New System.Drawing.Point(25, 24)
		Me.COMBO_FLICK.Name = "COMBO_FLICK"
		Me.COMBO_FLICK.Size = New System.Drawing.Size(187, 20)
		Me.COMBO_FLICK.TabIndex = 11
		'
		'groupBox4
		'
		Me.groupBox4.Controls.Add(Me.label1)
		Me.groupBox4.Controls.Add(Me.label3)
		Me.groupBox4.Controls.Add(Me.STATIC_EXPOTIME)
		Me.groupBox4.Controls.Add(Me.SLIDER_EXPOSURE_TIME)
		Me.groupBox4.Location = New System.Drawing.Point(5, 238)
		Me.groupBox4.Name = "groupBox4"
		Me.groupBox4.Size = New System.Drawing.Size(231, 67)
		Me.groupBox4.TabIndex = 26
		Me.groupBox4.TabStop = False
		Me.groupBox4.Text = "Exposure Time"
		'
		'label1
		'
		Me.label1.AutoSize = True
		Me.label1.Location = New System.Drawing.Point(122, 49)
		Me.label1.Name = "label1"
		Me.label1.Size = New System.Drawing.Size(17, 12)
		Me.label1.TabIndex = 19
		Me.label1.Text = "us"
		'
		'label3
		'
		Me.label3.AutoSize = True
		Me.label3.Location = New System.Drawing.Point(112, 48)
		Me.label3.Name = "label3"
		Me.label3.Size = New System.Drawing.Size(0, 12)
		Me.label3.TabIndex = 18
		'
		'STATIC_EXPOTIME
		'
		Me.STATIC_EXPOTIME.AutoSize = True
		Me.STATIC_EXPOTIME.Location = New System.Drawing.Point(31, 49)
		Me.STATIC_EXPOTIME.Name = "STATIC_EXPOTIME"
		Me.STATIC_EXPOTIME.Size = New System.Drawing.Size(11, 12)
		Me.STATIC_EXPOTIME.TabIndex = 18
		Me.STATIC_EXPOTIME.Text = "0"
		'
		'SLIDER_EXPOSURE_TIME
		'
		Me.SLIDER_EXPOSURE_TIME.AutoSize = False
		Me.SLIDER_EXPOSURE_TIME.LargeChange = 1
		Me.SLIDER_EXPOSURE_TIME.Location = New System.Drawing.Point(25, 23)
		Me.SLIDER_EXPOSURE_TIME.Name = "SLIDER_EXPOSURE_TIME"
		Me.SLIDER_EXPOSURE_TIME.Size = New System.Drawing.Size(186, 23)
		Me.SLIDER_EXPOSURE_TIME.TabIndex = 10
		Me.SLIDER_EXPOSURE_TIME.TickStyle = System.Windows.Forms.TickStyle.None
		'
		'groupBox7
		'
		Me.groupBox7.Controls.Add(Me.COMBO_RESOLUTION)
		Me.groupBox7.Location = New System.Drawing.Point(5, 450)
		Me.groupBox7.Name = "groupBox7"
		Me.groupBox7.Size = New System.Drawing.Size(235, 51)
		Me.groupBox7.TabIndex = 29
		Me.groupBox7.TabStop = False
		Me.groupBox7.Text = "Quick ROI"
		'
		'COMBO_RESOLUTION
		'
		Me.COMBO_RESOLUTION.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
		Me.COMBO_RESOLUTION.FormattingEnabled = True
		Me.COMBO_RESOLUTION.Location = New System.Drawing.Point(20, 24)
		Me.COMBO_RESOLUTION.Name = "COMBO_RESOLUTION"
		Me.COMBO_RESOLUTION.Size = New System.Drawing.Size(192, 20)
		Me.COMBO_RESOLUTION.TabIndex = 11
		'
		'AE_Mode
		'
		Me.AE_Mode.AutoSize = True
		Me.AE_Mode.Location = New System.Drawing.Point(11, 52)
		Me.AE_Mode.Name = "AE_Mode"
		Me.AE_Mode.Size = New System.Drawing.Size(47, 12)
		Me.AE_Mode.TabIndex = 10
		Me.AE_Mode.Text = "AE Mode"
		'
		'COMBO_DEVICES
		'
		Me.COMBO_DEVICES.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
		Me.COMBO_DEVICES.FormattingEnabled = True
		Me.COMBO_DEVICES.ImeMode = System.Windows.Forms.ImeMode.NoControl
		Me.COMBO_DEVICES.Location = New System.Drawing.Point(15, 28)
		Me.COMBO_DEVICES.Name = "COMBO_DEVICES"
		Me.COMBO_DEVICES.Size = New System.Drawing.Size(138, 20)
		Me.COMBO_DEVICES.TabIndex = 0
		'
		'groupBox1
		'
		Me.groupBox1.Controls.Add(Me.AE_Mode)
		Me.groupBox1.Controls.Add(Me.COMBO_AE_MODE)
		Me.groupBox1.Controls.Add(Me.CHECK_AEOPERATION)
		Me.groupBox1.Location = New System.Drawing.Point(7, 155)
		Me.groupBox1.Name = "groupBox1"
		Me.groupBox1.Size = New System.Drawing.Size(214, 78)
		Me.groupBox1.TabIndex = 23
		Me.groupBox1.TabStop = False
		Me.groupBox1.Text = "Auto Exposure"
		'
		'COMBO_AE_MODE
		'
		Me.COMBO_AE_MODE.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
		Me.COMBO_AE_MODE.FormattingEnabled = True
		Me.COMBO_AE_MODE.Location = New System.Drawing.Point(67, 52)
		Me.COMBO_AE_MODE.Name = "COMBO_AE_MODE"
		Me.COMBO_AE_MODE.Size = New System.Drawing.Size(147, 20)
		Me.COMBO_AE_MODE.TabIndex = 9
		'
		'CHECK_AEOPERATION
		'
		Me.CHECK_AEOPERATION.AutoSize = True
		Me.CHECK_AEOPERATION.Location = New System.Drawing.Point(13, 20)
		Me.CHECK_AEOPERATION.Name = "CHECK_AEOPERATION"
		Me.CHECK_AEOPERATION.Size = New System.Drawing.Size(78, 16)
		Me.CHECK_AEOPERATION.TabIndex = 8
		Me.CHECK_AEOPERATION.Text = "AE Enable"
		Me.CHECK_AEOPERATION.UseVisualStyleBackColor = True
		'
		'BUTTON_PROPERTY
		'
		Me.BUTTON_PROPERTY.Location = New System.Drawing.Point(159, 54)
		Me.BUTTON_PROPERTY.Name = "BUTTON_PROPERTY"
		Me.BUTTON_PROPERTY.Size = New System.Drawing.Size(57, 23)
		Me.BUTTON_PROPERTY.TabIndex = 5
		Me.BUTTON_PROPERTY.Text = "Property"
		Me.BUTTON_PROPERTY.UseVisualStyleBackColor = True
		'
		'BUTTON_START
		'
		Me.BUTTON_START.Location = New System.Drawing.Point(87, 54)
		Me.BUTTON_START.Name = "BUTTON_START"
		Me.BUTTON_START.Size = New System.Drawing.Size(57, 23)
		Me.BUTTON_START.TabIndex = 4
		Me.BUTTON_START.Text = "Start"
		Me.BUTTON_START.UseVisualStyleBackColor = True
		'
		'BUTTON_SCAN
		'
		Me.BUTTON_SCAN.Location = New System.Drawing.Point(159, 27)
		Me.BUTTON_SCAN.Name = "BUTTON_SCAN"
		Me.BUTTON_SCAN.Size = New System.Drawing.Size(57, 23)
		Me.BUTTON_SCAN.TabIndex = 3
		Me.BUTTON_SCAN.Text = "Scan"
		Me.BUTTON_SCAN.UseVisualStyleBackColor = True
		'
		'BUTTON_OPEN
		'
		Me.BUTTON_OPEN.Location = New System.Drawing.Point(15, 54)
		Me.BUTTON_OPEN.Name = "BUTTON_OPEN"
		Me.BUTTON_OPEN.Size = New System.Drawing.Size(57, 23)
		Me.BUTTON_OPEN.TabIndex = 2
		Me.BUTTON_OPEN.Text = "Open"
		Me.BUTTON_OPEN.UseVisualStyleBackColor = True
		'
		'pictureBox
		'
		Me.pictureBox.BackColor = System.Drawing.SystemColors.ActiveBorder
		Me.pictureBox.Location = New System.Drawing.Point(243, 9)
		Me.pictureBox.Name = "pictureBox"
		Me.pictureBox.Size = New System.Drawing.Size(653, 571)
		Me.pictureBox.TabIndex = 22
		Me.pictureBox.TabStop = False
		'
		'BUTTON_SAVE
		'
		Me.BUTTON_SAVE.Location = New System.Drawing.Point(144, 16)
		Me.BUTTON_SAVE.Name = "BUTTON_SAVE"
		Me.BUTTON_SAVE.Size = New System.Drawing.Size(72, 23)
		Me.BUTTON_SAVE.TabIndex = 7
		Me.BUTTON_SAVE.Text = "Save"
		Me.BUTTON_SAVE.UseVisualStyleBackColor = True
		'
		'groupBox3
		'
		Me.groupBox3.Controls.Add(Me.BUTTON_SAVE)
		Me.groupBox3.Location = New System.Drawing.Point(5, 101)
		Me.groupBox3.Name = "groupBox3"
		Me.groupBox3.Size = New System.Drawing.Size(231, 48)
		Me.groupBox3.TabIndex = 25
		Me.groupBox3.TabStop = False
		Me.groupBox3.Text = "Save Picture"
		'
		'General
		'
		Me.General.Controls.Add(Me.BUTTON_PROPERTY)
		Me.General.Controls.Add(Me.BUTTON_START)
		Me.General.Controls.Add(Me.BUTTON_SCAN)
		Me.General.Controls.Add(Me.BUTTON_OPEN)
		Me.General.Controls.Add(Me.COMBO_DEVICES)
		Me.General.Location = New System.Drawing.Point(5, 9)
		Me.General.Name = "General"
		Me.General.Size = New System.Drawing.Size(232, 85)
		Me.General.TabIndex = 24
		Me.General.TabStop = False
		Me.General.Text = "General"
		'
		'BasicFunction
		'
		Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 12.0!)
		Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
		Me.ClientSize = New System.Drawing.Size(903, 594)
		Me.Controls.Add(Me.groupBox11)
		Me.Controls.Add(Me.groupBox5)
		Me.Controls.Add(Me.groupBox4)
		Me.Controls.Add(Me.groupBox7)
		Me.Controls.Add(Me.groupBox1)
		Me.Controls.Add(Me.pictureBox)
		Me.Controls.Add(Me.groupBox3)
		Me.Controls.Add(Me.General)
		Me.Name = "BasicFunction"
		Me.Text = "BasicFunction"
		Me.groupBox11.ResumeLayout(False)
		Me.groupBox11.PerformLayout()
		CType(Me.SLIDER_GAIN, System.ComponentModel.ISupportInitialize).EndInit()
		Me.groupBox5.ResumeLayout(False)
		Me.groupBox4.ResumeLayout(False)
		Me.groupBox4.PerformLayout()
		CType(Me.SLIDER_EXPOSURE_TIME, System.ComponentModel.ISupportInitialize).EndInit()
		Me.groupBox7.ResumeLayout(False)
		Me.groupBox1.ResumeLayout(False)
		Me.groupBox1.PerformLayout()
		CType(Me.pictureBox, System.ComponentModel.ISupportInitialize).EndInit()
		Me.groupBox3.ResumeLayout(False)
		Me.General.ResumeLayout(False)
		Me.ResumeLayout(False)

	End Sub
	Private WithEvents groupBox11 As System.Windows.Forms.GroupBox
	Private WithEvents label5 As System.Windows.Forms.Label
	Private WithEvents STATIC_EXPOGAIN As System.Windows.Forms.Label
	Private WithEvents SLIDER_GAIN As System.Windows.Forms.TrackBar
	Private WithEvents groupBox5 As System.Windows.Forms.GroupBox
	Private WithEvents COMBO_FLICK As System.Windows.Forms.ComboBox
	Private WithEvents groupBox4 As System.Windows.Forms.GroupBox
	Private WithEvents label1 As System.Windows.Forms.Label
	Private WithEvents label3 As System.Windows.Forms.Label
	Private WithEvents STATIC_EXPOTIME As System.Windows.Forms.Label
	Private WithEvents SLIDER_EXPOSURE_TIME As System.Windows.Forms.TrackBar
	Private WithEvents groupBox7 As System.Windows.Forms.GroupBox
	Private WithEvents COMBO_RESOLUTION As System.Windows.Forms.ComboBox
	Private WithEvents AE_Mode As System.Windows.Forms.Label
	Private WithEvents COMBO_DEVICES As System.Windows.Forms.ComboBox
	Private WithEvents groupBox1 As System.Windows.Forms.GroupBox
	Private WithEvents COMBO_AE_MODE As System.Windows.Forms.ComboBox
	Private WithEvents CHECK_AEOPERATION As System.Windows.Forms.CheckBox
	Private WithEvents BUTTON_PROPERTY As System.Windows.Forms.Button
	Private WithEvents BUTTON_START As System.Windows.Forms.Button
	Private WithEvents BUTTON_SCAN As System.Windows.Forms.Button
	Private WithEvents BUTTON_OPEN As System.Windows.Forms.Button
	Private WithEvents pictureBox As System.Windows.Forms.PictureBox
	Private WithEvents BUTTON_SAVE As System.Windows.Forms.Button
	Private WithEvents groupBox3 As System.Windows.Forms.GroupBox
	Private WithEvents General As System.Windows.Forms.GroupBox

End Class

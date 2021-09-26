<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Trigger
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
		Me.General = New System.Windows.Forms.GroupBox()
		Me.PropertSet = New System.Windows.Forms.Button()
		Me.StartPlay = New System.Windows.Forms.Button()
		Me.ScanDev = New System.Windows.Forms.Button()
		Me.OpenDev = New System.Windows.Forms.Button()
		Me.DevNameCombo = New System.Windows.Forms.ComboBox()
		Me.InputIOCombo = New System.Windows.Forms.ComboBox()
		Me.ApplyLoop = New System.Windows.Forms.Button()
		Me.InputSignalType = New System.Windows.Forms.Label()
		Me.InputIO = New System.Windows.Forms.Label()
		Me.EnableIn = New System.Windows.Forms.CheckBox()
		Me.ApplyDelay = New System.Windows.Forms.Button()
		Me.groupBox3 = New System.Windows.Forms.GroupBox()
		Me.OutputSignalType = New System.Windows.Forms.ComboBox()
		Me.OutIOCombo = New System.Windows.Forms.ComboBox()
		Me.label7 = New System.Windows.Forms.Label()
		Me.label8 = New System.Windows.Forms.Label()
		Me.EnableOut = New System.Windows.Forms.CheckBox()
		Me.label2 = New System.Windows.Forms.Label()
		Me.label1 = New System.Windows.Forms.Label()
		Me.SoftTriggerFire = New System.Windows.Forms.Button()
		Me.LoopTrigger = New System.Windows.Forms.CheckBox()
		Me.InputSignalTypeCombo = New System.Windows.Forms.ComboBox()
		Me.pictureBox = New System.Windows.Forms.PictureBox()
		Me.groupBox2 = New System.Windows.Forms.GroupBox()
		Me.FilterApply = New System.Windows.Forms.Button()
		Me.label5 = New System.Windows.Forms.Label()
		Me.TriggerMode = New System.Windows.Forms.CheckBox()
		Me.groupBox1 = New System.Windows.Forms.GroupBox()
		Me.TriggerLoop = New System.Windows.Forms.TextBox()
		Me.TriggerDelay = New System.Windows.Forms.TextBox()
		Me.EditFilter = New System.Windows.Forms.TextBox()
		Me.General.SuspendLayout()
		Me.groupBox3.SuspendLayout()
		CType(Me.pictureBox, System.ComponentModel.ISupportInitialize).BeginInit()
		Me.groupBox2.SuspendLayout()
		Me.groupBox1.SuspendLayout()
		Me.SuspendLayout()
		'
		'General
		'
		Me.General.Controls.Add(Me.PropertSet)
		Me.General.Controls.Add(Me.StartPlay)
		Me.General.Controls.Add(Me.ScanDev)
		Me.General.Controls.Add(Me.OpenDev)
		Me.General.Controls.Add(Me.DevNameCombo)
		Me.General.Location = New System.Drawing.Point(2, 3)
		Me.General.Name = "General"
		Me.General.Size = New System.Drawing.Size(260, 72)
		Me.General.TabIndex = 23
		Me.General.TabStop = False
		Me.General.Text = "General"
		'
		'PropertSet
		'
		Me.PropertSet.Location = New System.Drawing.Point(187, 43)
		Me.PropertSet.Name = "PropertSet"
		Me.PropertSet.Size = New System.Drawing.Size(67, 23)
		Me.PropertSet.TabIndex = 5
		Me.PropertSet.Text = "Property"
		Me.PropertSet.UseVisualStyleBackColor = True
		'
		'StartPlay
		'
		Me.StartPlay.Location = New System.Drawing.Point(101, 43)
		Me.StartPlay.Name = "StartPlay"
		Me.StartPlay.Size = New System.Drawing.Size(80, 23)
		Me.StartPlay.TabIndex = 4
		Me.StartPlay.Text = "Start"
		Me.StartPlay.UseVisualStyleBackColor = True
		'
		'ScanDev
		'
		Me.ScanDev.Location = New System.Drawing.Point(187, 17)
		Me.ScanDev.Name = "ScanDev"
		Me.ScanDev.Size = New System.Drawing.Size(67, 23)
		Me.ScanDev.TabIndex = 3
		Me.ScanDev.Text = "Scan"
		Me.ScanDev.UseVisualStyleBackColor = True
		'
		'OpenDev
		'
		Me.OpenDev.Location = New System.Drawing.Point(10, 43)
		Me.OpenDev.Name = "OpenDev"
		Me.OpenDev.Size = New System.Drawing.Size(80, 23)
		Me.OpenDev.TabIndex = 2
		Me.OpenDev.Text = "Open"
		Me.OpenDev.UseVisualStyleBackColor = True
		'
		'DevNameCombo
		'
		Me.DevNameCombo.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
		Me.DevNameCombo.FormattingEnabled = True
		Me.DevNameCombo.ImeMode = System.Windows.Forms.ImeMode.NoControl
		Me.DevNameCombo.Location = New System.Drawing.Point(10, 18)
		Me.DevNameCombo.Name = "DevNameCombo"
		Me.DevNameCombo.Size = New System.Drawing.Size(171, 20)
		Me.DevNameCombo.TabIndex = 0
		'
		'InputIOCombo
		'
		Me.InputIOCombo.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
		Me.InputIOCombo.FormattingEnabled = True
		Me.InputIOCombo.Location = New System.Drawing.Point(152, 44)
		Me.InputIOCombo.Name = "InputIOCombo"
		Me.InputIOCombo.Size = New System.Drawing.Size(100, 20)
		Me.InputIOCombo.TabIndex = 3
		'
		'ApplyLoop
		'
		Me.ApplyLoop.Location = New System.Drawing.Point(187, 66)
		Me.ApplyLoop.Name = "ApplyLoop"
		Me.ApplyLoop.Size = New System.Drawing.Size(66, 21)
		Me.ApplyLoop.TabIndex = 7
		Me.ApplyLoop.Text = "Apply"
		Me.ApplyLoop.UseVisualStyleBackColor = True
		'
		'InputSignalType
		'
		Me.InputSignalType.AutoSize = True
		Me.InputSignalType.Location = New System.Drawing.Point(10, 75)
		Me.InputSignalType.Name = "InputSignalType"
		Me.InputSignalType.Size = New System.Drawing.Size(107, 12)
		Me.InputSignalType.TabIndex = 2
		Me.InputSignalType.Text = "Input Signal Type"
		'
		'InputIO
		'
		Me.InputIO.AutoSize = True
		Me.InputIO.Location = New System.Drawing.Point(10, 47)
		Me.InputIO.Name = "InputIO"
		Me.InputIO.Size = New System.Drawing.Size(53, 12)
		Me.InputIO.TabIndex = 1
		Me.InputIO.Text = "Input IO"
		'
		'EnableIn
		'
		Me.EnableIn.AutoSize = True
		Me.EnableIn.Location = New System.Drawing.Point(10, 21)
		Me.EnableIn.Name = "EnableIn"
		Me.EnableIn.Size = New System.Drawing.Size(60, 16)
		Me.EnableIn.TabIndex = 0
		Me.EnableIn.Text = "Enable"
		Me.EnableIn.UseVisualStyleBackColor = True
		'
		'ApplyDelay
		'
		Me.ApplyDelay.Location = New System.Drawing.Point(187, 95)
		Me.ApplyDelay.Name = "ApplyDelay"
		Me.ApplyDelay.Size = New System.Drawing.Size(66, 21)
		Me.ApplyDelay.TabIndex = 8
		Me.ApplyDelay.Text = "Apply"
		Me.ApplyDelay.UseVisualStyleBackColor = True
		'
		'groupBox3
		'
		Me.groupBox3.Controls.Add(Me.OutputSignalType)
		Me.groupBox3.Controls.Add(Me.OutIOCombo)
		Me.groupBox3.Controls.Add(Me.label7)
		Me.groupBox3.Controls.Add(Me.label8)
		Me.groupBox3.Controls.Add(Me.EnableOut)
		Me.groupBox3.Location = New System.Drawing.Point(3, 348)
		Me.groupBox3.Name = "groupBox3"
		Me.groupBox3.Size = New System.Drawing.Size(259, 93)
		Me.groupBox3.TabIndex = 26
		Me.groupBox3.TabStop = False
		Me.groupBox3.Text = "Ext Strobe Out"
		'
		'OutputSignalType
		'
		Me.OutputSignalType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
		Me.OutputSignalType.FormattingEnabled = True
		Me.OutputSignalType.Location = New System.Drawing.Point(153, 61)
		Me.OutputSignalType.Name = "OutputSignalType"
		Me.OutputSignalType.Size = New System.Drawing.Size(100, 20)
		Me.OutputSignalType.TabIndex = 4
		'
		'OutIOCombo
		'
		Me.OutIOCombo.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
		Me.OutIOCombo.FormattingEnabled = True
		Me.OutIOCombo.Location = New System.Drawing.Point(153, 37)
		Me.OutIOCombo.Name = "OutIOCombo"
		Me.OutIOCombo.Size = New System.Drawing.Size(100, 20)
		Me.OutIOCombo.TabIndex = 3
		'
		'label7
		'
		Me.label7.AutoSize = True
		Me.label7.Location = New System.Drawing.Point(10, 66)
		Me.label7.Name = "label7"
		Me.label7.Size = New System.Drawing.Size(113, 12)
		Me.label7.TabIndex = 2
		Me.label7.Text = "Output Signal Type"
		'
		'label8
		'
		Me.label8.AutoSize = True
		Me.label8.Location = New System.Drawing.Point(10, 44)
		Me.label8.Name = "label8"
		Me.label8.Size = New System.Drawing.Size(59, 12)
		Me.label8.TabIndex = 1
		Me.label8.Text = "Output IO"
		'
		'EnableOut
		'
		Me.EnableOut.AutoSize = True
		Me.EnableOut.Location = New System.Drawing.Point(10, 22)
		Me.EnableOut.Name = "EnableOut"
		Me.EnableOut.Size = New System.Drawing.Size(60, 16)
		Me.EnableOut.TabIndex = 0
		Me.EnableOut.Text = "Enable"
		Me.EnableOut.UseVisualStyleBackColor = True
		'
		'label2
		'
		Me.label2.AutoSize = True
		Me.label2.Location = New System.Drawing.Point(10, 97)
		Me.label2.Name = "label2"
		Me.label2.Size = New System.Drawing.Size(59, 12)
		Me.label2.TabIndex = 4
		Me.label2.Text = "Delay(us)"
		'
		'label1
		'
		Me.label1.AutoSize = True
		Me.label1.Location = New System.Drawing.Point(10, 68)
		Me.label1.Name = "label1"
		Me.label1.Size = New System.Drawing.Size(89, 12)
		Me.label1.TabIndex = 3
		Me.label1.Text = "Loop Timer(us)"
		'
		'SoftTriggerFire
		'
		Me.SoftTriggerFire.Location = New System.Drawing.Point(129, 16)
		Me.SoftTriggerFire.Name = "SoftTriggerFire"
		Me.SoftTriggerFire.Size = New System.Drawing.Size(124, 23)
		Me.SoftTriggerFire.TabIndex = 2
		Me.SoftTriggerFire.Text = "Soft Trigger Fire"
		Me.SoftTriggerFire.UseVisualStyleBackColor = True
		'
		'LoopTrigger
		'
		Me.LoopTrigger.AutoSize = True
		Me.LoopTrigger.Location = New System.Drawing.Point(10, 42)
		Me.LoopTrigger.Name = "LoopTrigger"
		Me.LoopTrigger.Size = New System.Drawing.Size(90, 16)
		Me.LoopTrigger.TabIndex = 1
		Me.LoopTrigger.Text = "LoopTrigger"
		Me.LoopTrigger.UseVisualStyleBackColor = True
		'
		'InputSignalTypeCombo
		'
		Me.InputSignalTypeCombo.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
		Me.InputSignalTypeCombo.FormattingEnabled = True
		Me.InputSignalTypeCombo.Location = New System.Drawing.Point(152, 70)
		Me.InputSignalTypeCombo.Name = "InputSignalTypeCombo"
		Me.InputSignalTypeCombo.Size = New System.Drawing.Size(100, 20)
		Me.InputSignalTypeCombo.TabIndex = 4
		'
		'pictureBox
		'
		Me.pictureBox.BackColor = System.Drawing.SystemColors.ActiveBorder
		Me.pictureBox.Location = New System.Drawing.Point(268, 3)
		Me.pictureBox.Name = "pictureBox"
		Me.pictureBox.Size = New System.Drawing.Size(716, 593)
		Me.pictureBox.TabIndex = 27
		Me.pictureBox.TabStop = False
		'
		'groupBox2
		'
		Me.groupBox2.Controls.Add(Me.EditFilter)
		Me.groupBox2.Controls.Add(Me.FilterApply)
		Me.groupBox2.Controls.Add(Me.label5)
		Me.groupBox2.Controls.Add(Me.InputSignalTypeCombo)
		Me.groupBox2.Controls.Add(Me.InputIOCombo)
		Me.groupBox2.Controls.Add(Me.InputSignalType)
		Me.groupBox2.Controls.Add(Me.InputIO)
		Me.groupBox2.Controls.Add(Me.EnableIn)
		Me.groupBox2.Location = New System.Drawing.Point(3, 210)
		Me.groupBox2.Name = "groupBox2"
		Me.groupBox2.Size = New System.Drawing.Size(259, 132)
		Me.groupBox2.TabIndex = 25
		Me.groupBox2.TabStop = False
		Me.groupBox2.Text = "Ext Trigger In"
		'
		'FilterApply
		'
		Me.FilterApply.Location = New System.Drawing.Point(187, 98)
		Me.FilterApply.Name = "FilterApply"
		Me.FilterApply.Size = New System.Drawing.Size(66, 23)
		Me.FilterApply.TabIndex = 7
		Me.FilterApply.Text = "Apply"
		Me.FilterApply.UseVisualStyleBackColor = True
		'
		'label5
		'
		Me.label5.AutoSize = True
		Me.label5.Location = New System.Drawing.Point(10, 105)
		Me.label5.Name = "label5"
		Me.label5.Size = New System.Drawing.Size(107, 12)
		Me.label5.TabIndex = 5
		Me.label5.Text = "Jitter Filter(us)"
		'
		'TriggerMode
		'
		Me.TriggerMode.AutoSize = True
		Me.TriggerMode.Location = New System.Drawing.Point(10, 20)
		Me.TriggerMode.Name = "TriggerMode"
		Me.TriggerMode.Size = New System.Drawing.Size(90, 16)
		Me.TriggerMode.TabIndex = 0
		Me.TriggerMode.Text = "TriggerMode"
		Me.TriggerMode.UseVisualStyleBackColor = True
		'
		'groupBox1
		'
		Me.groupBox1.Controls.Add(Me.TriggerDelay)
		Me.groupBox1.Controls.Add(Me.TriggerLoop)
		Me.groupBox1.Controls.Add(Me.ApplyDelay)
		Me.groupBox1.Controls.Add(Me.ApplyLoop)
		Me.groupBox1.Controls.Add(Me.label2)
		Me.groupBox1.Controls.Add(Me.label1)
		Me.groupBox1.Controls.Add(Me.SoftTriggerFire)
		Me.groupBox1.Controls.Add(Me.LoopTrigger)
		Me.groupBox1.Controls.Add(Me.TriggerMode)
		Me.groupBox1.Location = New System.Drawing.Point(2, 81)
		Me.groupBox1.Name = "groupBox1"
		Me.groupBox1.Size = New System.Drawing.Size(259, 123)
		Me.groupBox1.TabIndex = 24
		Me.groupBox1.TabStop = False
		Me.groupBox1.Text = "Trigger"
		'
		'TriggerLoop
		'
		Me.TriggerLoop.Location = New System.Drawing.Point(105, 66)
		Me.TriggerLoop.Name = "TriggerLoop"
		Me.TriggerLoop.Size = New System.Drawing.Size(76, 21)
		Me.TriggerLoop.TabIndex = 9
		'
		'TriggerDelay
		'
		Me.TriggerDelay.Location = New System.Drawing.Point(105, 94)
		Me.TriggerDelay.Name = "TriggerDelay"
		Me.TriggerDelay.Size = New System.Drawing.Size(76, 21)
		Me.TriggerDelay.TabIndex = 10
		'
		'EditFilter
		'
		Me.EditFilter.Location = New System.Drawing.Point(128, 100)
		Me.EditFilter.Name = "EditFilter"
		Me.EditFilter.Size = New System.Drawing.Size(53, 21)
		Me.EditFilter.TabIndex = 10
		'
		'Trigger
		'
		Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 12.0!)
		Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
		Me.ClientSize = New System.Drawing.Size(987, 599)
		Me.Controls.Add(Me.General)
		Me.Controls.Add(Me.groupBox3)
		Me.Controls.Add(Me.pictureBox)
		Me.Controls.Add(Me.groupBox2)
		Me.Controls.Add(Me.groupBox1)
		Me.Name = "Trigger"
		Me.Text = "Trigger"
		Me.General.ResumeLayout(False)
		Me.groupBox3.ResumeLayout(False)
		Me.groupBox3.PerformLayout()
		CType(Me.pictureBox, System.ComponentModel.ISupportInitialize).EndInit()
		Me.groupBox2.ResumeLayout(False)
		Me.groupBox2.PerformLayout()
		Me.groupBox1.ResumeLayout(False)
		Me.groupBox1.PerformLayout()
		Me.ResumeLayout(False)

	End Sub
	Private WithEvents General As System.Windows.Forms.GroupBox
	Private WithEvents PropertSet As System.Windows.Forms.Button
	Private WithEvents StartPlay As System.Windows.Forms.Button
	Private WithEvents ScanDev As System.Windows.Forms.Button
	Private WithEvents OpenDev As System.Windows.Forms.Button
	Private WithEvents DevNameCombo As System.Windows.Forms.ComboBox
	Private WithEvents InputIOCombo As System.Windows.Forms.ComboBox
	Private WithEvents ApplyLoop As System.Windows.Forms.Button
	Private WithEvents InputSignalType As System.Windows.Forms.Label
	Private WithEvents InputIO As System.Windows.Forms.Label
	Private WithEvents EnableIn As System.Windows.Forms.CheckBox
	Private WithEvents ApplyDelay As System.Windows.Forms.Button
	Private WithEvents groupBox3 As System.Windows.Forms.GroupBox
	Private WithEvents OutputSignalType As System.Windows.Forms.ComboBox
	Private WithEvents OutIOCombo As System.Windows.Forms.ComboBox
	Private WithEvents label7 As System.Windows.Forms.Label
	Private WithEvents label8 As System.Windows.Forms.Label
	Private WithEvents EnableOut As System.Windows.Forms.CheckBox
	Private WithEvents label2 As System.Windows.Forms.Label
	Private WithEvents label1 As System.Windows.Forms.Label
	Private WithEvents SoftTriggerFire As System.Windows.Forms.Button
	Private WithEvents LoopTrigger As System.Windows.Forms.CheckBox
	Private WithEvents InputSignalTypeCombo As System.Windows.Forms.ComboBox
	Private WithEvents pictureBox As System.Windows.Forms.PictureBox
	Private WithEvents groupBox2 As System.Windows.Forms.GroupBox
	Private WithEvents FilterApply As System.Windows.Forms.Button
	Private WithEvents label5 As System.Windows.Forms.Label
	Private WithEvents TriggerMode As System.Windows.Forms.CheckBox
	Private WithEvents groupBox1 As System.Windows.Forms.GroupBox
	Friend WithEvents EditFilter As System.Windows.Forms.TextBox
	Friend WithEvents TriggerDelay As System.Windows.Forms.TextBox
	Friend WithEvents TriggerLoop As System.Windows.Forms.TextBox

End Class

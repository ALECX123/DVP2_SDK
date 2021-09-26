<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class ImageAcquisition
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
		Me.Display = New System.Windows.Forms.CheckBox()
		Me.SaveImage = New System.Windows.Forms.GroupBox()
		Me.OpenFolder = New System.Windows.Forms.Button()
		Me.SelectPath = New System.Windows.Forms.Button()
		Me.EditPath = New System.Windows.Forms.TextBox()
		Me.Counts = New System.Windows.Forms.Label()
		Me.SaveImageCheck = New System.Windows.Forms.CheckBox()
		Me.DisplayImage = New System.Windows.Forms.GroupBox()
		Me.General = New System.Windows.Forms.GroupBox()
		Me.PropertSet = New System.Windows.Forms.Button()
		Me.StartPlay = New System.Windows.Forms.Button()
		Me.ScanDev = New System.Windows.Forms.Button()
		Me.OpenDev = New System.Windows.Forms.Button()
		Me.DevNameCombo = New System.Windows.Forms.ComboBox()
		Me.EditWait = New System.Windows.Forms.TextBox()
		Me.SoftTrigger = New System.Windows.Forms.CheckBox()
		Me.Configuration = New System.Windows.Forms.GroupBox()
		Me.label1 = New System.Windows.Forms.Label()
		Me.pictureBox = New System.Windows.Forms.PictureBox()
		Me.SaveImage.SuspendLayout()
		Me.DisplayImage.SuspendLayout()
		Me.General.SuspendLayout()
		Me.Configuration.SuspendLayout()
		CType(Me.pictureBox, System.ComponentModel.ISupportInitialize).BeginInit()
		Me.SuspendLayout()
		'
		'Display
		'
		Me.Display.AutoSize = True
		Me.Display.Location = New System.Drawing.Point(33, 23)
		Me.Display.Name = "Display"
		Me.Display.Size = New System.Drawing.Size(66, 16)
		Me.Display.TabIndex = 0
		Me.Display.Text = "Display"
		Me.Display.UseVisualStyleBackColor = True
		'
		'SaveImage
		'
		Me.SaveImage.Controls.Add(Me.OpenFolder)
		Me.SaveImage.Controls.Add(Me.SelectPath)
		Me.SaveImage.Controls.Add(Me.EditPath)
		Me.SaveImage.Controls.Add(Me.Counts)
		Me.SaveImage.Controls.Add(Me.SaveImageCheck)
		Me.SaveImage.Location = New System.Drawing.Point(10, 237)
		Me.SaveImage.Name = "SaveImage"
		Me.SaveImage.Size = New System.Drawing.Size(225, 96)
		Me.SaveImage.TabIndex = 28
		Me.SaveImage.TabStop = False
		Me.SaveImage.Text = "Save Image"
		'
		'OpenFolder
		'
		Me.OpenFolder.Location = New System.Drawing.Point(115, 66)
		Me.OpenFolder.Name = "OpenFolder"
		Me.OpenFolder.Size = New System.Drawing.Size(88, 23)
		Me.OpenFolder.TabIndex = 25
		Me.OpenFolder.Text = "Open Folder"
		Me.OpenFolder.UseVisualStyleBackColor = True
		'
		'SelectPath
		'
		Me.SelectPath.Location = New System.Drawing.Point(10, 66)
		Me.SelectPath.Name = "SelectPath"
		Me.SelectPath.Size = New System.Drawing.Size(88, 23)
		Me.SelectPath.TabIndex = 24
		Me.SelectPath.Text = "Select Path"
		Me.SelectPath.UseVisualStyleBackColor = True
		'
		'EditPath
		'
		Me.EditPath.Location = New System.Drawing.Point(10, 42)
		Me.EditPath.Name = "EditPath"
		Me.EditPath.ReadOnly = True
		Me.EditPath.Size = New System.Drawing.Size(201, 21)
		Me.EditPath.TabIndex = 23
		'
		'Counts
		'
		Me.Counts.AutoSize = True
		Me.Counts.Location = New System.Drawing.Point(147, 23)
		Me.Counts.Name = "Counts"
		Me.Counts.Size = New System.Drawing.Size(41, 12)
		Me.Counts.TabIndex = 1
		Me.Counts.Text = "Counts"
		'
		'SaveImageCheck
		'
		Me.SaveImageCheck.AutoSize = True
		Me.SaveImageCheck.Location = New System.Drawing.Point(33, 21)
		Me.SaveImageCheck.Name = "SaveImageCheck"
		Me.SaveImageCheck.Size = New System.Drawing.Size(84, 16)
		Me.SaveImageCheck.TabIndex = 0
		Me.SaveImageCheck.Text = "Save Image"
		Me.SaveImageCheck.UseVisualStyleBackColor = True
		'
		'DisplayImage
		'
		Me.DisplayImage.Controls.Add(Me.Display)
		Me.DisplayImage.Location = New System.Drawing.Point(10, 184)
		Me.DisplayImage.Name = "DisplayImage"
		Me.DisplayImage.Size = New System.Drawing.Size(225, 47)
		Me.DisplayImage.TabIndex = 27
		Me.DisplayImage.TabStop = False
		Me.DisplayImage.Text = "Display Image"
		'
		'General
		'
		Me.General.Controls.Add(Me.PropertSet)
		Me.General.Controls.Add(Me.StartPlay)
		Me.General.Controls.Add(Me.ScanDev)
		Me.General.Controls.Add(Me.OpenDev)
		Me.General.Controls.Add(Me.DevNameCombo)
		Me.General.Location = New System.Drawing.Point(5, 5)
		Me.General.Name = "General"
		Me.General.Size = New System.Drawing.Size(232, 85)
		Me.General.TabIndex = 24
		Me.General.TabStop = False
		Me.General.Text = "General"
		'
		'PropertSet
		'
		Me.PropertSet.Location = New System.Drawing.Point(159, 54)
		Me.PropertSet.Name = "PropertSet"
		Me.PropertSet.Size = New System.Drawing.Size(57, 23)
		Me.PropertSet.TabIndex = 5
		Me.PropertSet.Text = "Property"
		Me.PropertSet.UseVisualStyleBackColor = True
		'
		'StartPlay
		'
		Me.StartPlay.Location = New System.Drawing.Point(87, 54)
		Me.StartPlay.Name = "StartPlay"
		Me.StartPlay.Size = New System.Drawing.Size(57, 23)
		Me.StartPlay.TabIndex = 4
		Me.StartPlay.Text = "Start"
		Me.StartPlay.UseVisualStyleBackColor = True
		'
		'ScanDev
		'
		Me.ScanDev.Location = New System.Drawing.Point(159, 27)
		Me.ScanDev.Name = "ScanDev"
		Me.ScanDev.Size = New System.Drawing.Size(57, 23)
		Me.ScanDev.TabIndex = 3
		Me.ScanDev.Text = "Scan"
		Me.ScanDev.UseVisualStyleBackColor = True
		'
		'OpenDev
		'
		Me.OpenDev.Location = New System.Drawing.Point(15, 54)
		Me.OpenDev.Name = "OpenDev"
		Me.OpenDev.Size = New System.Drawing.Size(57, 23)
		Me.OpenDev.TabIndex = 2
		Me.OpenDev.Text = "Open"
		Me.OpenDev.UseVisualStyleBackColor = True
		'
		'DevNameCombo
		'
		Me.DevNameCombo.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
		Me.DevNameCombo.FormattingEnabled = True
		Me.DevNameCombo.ImeMode = System.Windows.Forms.ImeMode.NoControl
		Me.DevNameCombo.Location = New System.Drawing.Point(15, 28)
		Me.DevNameCombo.Name = "DevNameCombo"
		Me.DevNameCombo.Size = New System.Drawing.Size(138, 20)
		Me.DevNameCombo.TabIndex = 0
		'
		'EditWait
		'
		Me.EditWait.Location = New System.Drawing.Point(105, 20)
		Me.EditWait.Name = "EditWait"
		Me.EditWait.Size = New System.Drawing.Size(100, 21)
		Me.EditWait.TabIndex = 21
		'
		'SoftTrigger
		'
		Me.SoftTrigger.AutoSize = True
		Me.SoftTrigger.Location = New System.Drawing.Point(12, 47)
		Me.SoftTrigger.Name = "SoftTrigger"
		Me.SoftTrigger.Size = New System.Drawing.Size(96, 16)
		Me.SoftTrigger.TabIndex = 19
		Me.SoftTrigger.Text = "Soft Trigger"
		Me.SoftTrigger.UseVisualStyleBackColor = True
		'
		'Configuration
		'
		Me.Configuration.Controls.Add(Me.EditWait)
		Me.Configuration.Controls.Add(Me.SoftTrigger)
		Me.Configuration.Controls.Add(Me.label1)
		Me.Configuration.Location = New System.Drawing.Point(8, 100)
		Me.Configuration.Name = "Configuration"
		Me.Configuration.Size = New System.Drawing.Size(228, 72)
		Me.Configuration.TabIndex = 25
		Me.Configuration.TabStop = False
		Me.Configuration.Text = "Configuration"
		'
		'label1
		'
		Me.label1.AutoSize = True
		Me.label1.Location = New System.Drawing.Point(10, 23)
		Me.label1.Name = "label1"
		Me.label1.Size = New System.Drawing.Size(89, 12)
		Me.label1.TabIndex = 18
		Me.label1.Text = "Wait Timer(ms)"
		'
		'pictureBox
		'
		Me.pictureBox.BackColor = System.Drawing.SystemColors.ActiveBorder
		Me.pictureBox.Location = New System.Drawing.Point(243, 5)
		Me.pictureBox.Name = "pictureBox"
		Me.pictureBox.Size = New System.Drawing.Size(653, 571)
		Me.pictureBox.TabIndex = 23
		Me.pictureBox.TabStop = False
		'
		'ImageAcquisition
		'
		Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 12.0!)
		Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
		Me.ClientSize = New System.Drawing.Size(901, 581)
		Me.Controls.Add(Me.SaveImage)
		Me.Controls.Add(Me.DisplayImage)
		Me.Controls.Add(Me.General)
		Me.Controls.Add(Me.Configuration)
		Me.Controls.Add(Me.pictureBox)
		Me.Name = "ImageAcquisition"
		Me.Text = "ImageAcquisition"
		Me.SaveImage.ResumeLayout(False)
		Me.SaveImage.PerformLayout()
		Me.DisplayImage.ResumeLayout(False)
		Me.DisplayImage.PerformLayout()
		Me.General.ResumeLayout(False)
		Me.Configuration.ResumeLayout(False)
		Me.Configuration.PerformLayout()
		CType(Me.pictureBox, System.ComponentModel.ISupportInitialize).EndInit()
		Me.ResumeLayout(False)

	End Sub
	Private WithEvents Display As System.Windows.Forms.CheckBox
	Private WithEvents SaveImage As System.Windows.Forms.GroupBox
	Private WithEvents OpenFolder As System.Windows.Forms.Button
	Private WithEvents SelectPath As System.Windows.Forms.Button
	Private WithEvents EditPath As System.Windows.Forms.TextBox
	Private WithEvents Counts As System.Windows.Forms.Label
	Private WithEvents SaveImageCheck As System.Windows.Forms.CheckBox
	Private WithEvents DisplayImage As System.Windows.Forms.GroupBox
	Private WithEvents General As System.Windows.Forms.GroupBox
	Private WithEvents PropertSet As System.Windows.Forms.Button
	Private WithEvents StartPlay As System.Windows.Forms.Button
	Private WithEvents ScanDev As System.Windows.Forms.Button
	Private WithEvents OpenDev As System.Windows.Forms.Button
	Private WithEvents DevNameCombo As System.Windows.Forms.ComboBox
	Private WithEvents EditWait As System.Windows.Forms.TextBox
	Private WithEvents SoftTrigger As System.Windows.Forms.CheckBox
	Private WithEvents Configuration As System.Windows.Forms.GroupBox
	Private WithEvents label1 As System.Windows.Forms.Label
	Private WithEvents pictureBox As System.Windows.Forms.PictureBox

End Class

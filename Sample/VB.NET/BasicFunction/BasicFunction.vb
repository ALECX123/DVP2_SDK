Imports DVPCameraType
Imports DVPCameraType.DVPCamera

Public Class BasicFunction
	Private m_handle As UInteger
	Private m_bAeOp As Boolean
	Private m_strFriendlyName As String
	Private m_b_start As Boolean
    Public m_ptr_wnd As IntPtr

    ' 打开相机
	Private Sub BUTTON_OPEN_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BUTTON_OPEN.Click
		OpenCamera()
	End Sub

    ' 播放相机
	Private Sub BUTTON_START_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BUTTON_START.Click
		StartCamera()
	End Sub

    ' 设置参数
	Private Sub BUTTON_PROPERTY_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BUTTON_PROPERTY.Click
		SetParam()
	End Sub

    ' 保存文件
	Private Sub BUTTON_SAVE_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BUTTON_SAVE.Click
		SaveFile()
	End Sub

    ' 程序加载
	Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
		m_handle = 0
		m_b_start = False
		m_strFriendlyName = ""
		m_bAeOp = False
		m_ptr_wnd = pictureBox.Handle
		ScanCamera()
	End Sub

    ' 枚举相机
	Private Sub BUTTON_SCAN_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BUTTON_SCAN.Click
		ScanCamera()
	End Sub

    ' 检查相机是否打开
	Private Function IsValidHandle(ByVal handleid As UInteger) As Boolean
		Dim bValidHandle As Boolean
		Dim status As dvpStatus
		bValidHandle = False

		status = DVPCamera.dvpIsValid(handleid, bValidHandle)
		Return bValidHandle
	End Function

    ' 枚举相机并添加到下拉框
    Private Sub ScanCamera()

        ' 清楚下拉框原有的的数据
        COMBO_DEVICES.Items.Clear()
        Dim iNum As Integer
        Dim iCamCount As Integer            ' 相机数量
        Dim sDevList As New dvpCameraInfo() ' 相机信息结构

        ' 获取连接的相机数量
        If dvpStatus.DVP_STATUS_OK = DVPCamera.dvpRefresh(iCamCount) Then

            ' 获取相机的型号等信息并添加到控件
            For iNum = 0 To iCamCount - 1
                If dvpStatus.DVP_STATUS_OK = DVPCamera.dvpEnum(iNum, sDevList) Then
                    COMBO_DEVICES.Items.Add(sDevList.FriendlyName)
                End If
            Next

            ' 设置下拉框当前选择项
            If iCamCount > 0 Then
                COMBO_DEVICES.SelectedIndex = 0
            End If
        End If
        InitCtrl()
    End Sub

    ' 设置控件状态
	Private Sub InitCtrl()

		Dim Status As dvpStatus

        ' 检查相机是否打开
        If IsValidHandle(m_handle) Then
            BUTTON_OPEN.Enabled = True
            BUTTON_START.Enabled = True
            BUTTON_PROPERTY.Enabled = True
            BUTTON_OPEN.Text = "Close"

            COMBO_RESOLUTION.Enabled = True
            COMBO_AE_MODE.Enabled = True
            COMBO_FLICK.Enabled = True
            CHECK_AEOPERATION.Enabled = True
            BUTTON_SAVE.Enabled = True
            Dim state As DVPCameraType.dvpStreamState
            If dvpStatus.DVP_STATUS_OK = DVPCamera.dvpGetStreamState(m_handle, state) Then
                If state = DVPCameraType.dvpStreamState.STATE_STOPED Then
                    BUTTON_START.Text = "Start"
                ElseIf state = DVPCameraType.dvpStreamState.STATE_STARTED Then
                    BUTTON_START.Text = "Stop"
                End If
            Else
                BUTTON_START.Text = "Start"
            End If

            ' 更新自动曝光操作控件
            Dim AeOp As dvpAeOperation
            Dim AeMode As dvpAeMode

			Status = DVPCamera.dvpGetAeOperation(m_handle, AeOp)
			Status = DVPCamera.dvpGetAeMode(m_handle, AeMode)

            If AeOp = dvpAeOperation.AE_OP_OFF Then
                m_bAeOp = False
                SLIDER_EXPOSURE_TIME.Enabled = True
                SLIDER_GAIN.Enabled = True
			Else
				m_bAeOp = True
				If AeMode = dvpAeMode.AE_MODE_AG_ONLY Then
					SLIDER_EXPOSURE_TIME.Enabled = True
				Else
					SLIDER_EXPOSURE_TIME.Enabled = False
				End If

				If AeMode = dvpAeMode.AE_MODE_AE_ONLY Then
					SLIDER_GAIN.Enabled = True
				Else
					SLIDER_GAIN.Enabled = False
				End If

            End If

            CHECK_AEOPERATION.Checked = m_bAeOp

            ' 获取自动曝光模式并更新自动曝光模式设置控件、使能曝光时间和模拟增益调节的控件
            COMBO_AE_MODE.SelectedIndex = AeMode

            ' 更新抗频闪设置控件
            Dim AntiFlick As dvpAntiFlick
            Status = DVPCamera.dvpGetAntiFlick(m_handle, AntiFlick)
            If COMBO_FLICK.Items.Count > 0 Then
                COMBO_FLICK.SelectedIndex = AntiFlick
            End If

            ' 更新曝光时间
            Dim fExpoTime As Double
            Dim strExpoTime As String
            Status = DVPCamera.dvpGetExposure(m_handle, fExpoTime)
            strExpoTime = String.Format("{0:00000}", fExpoTime)
            STATIC_EXPOTIME.Text = strExpoTime

            ' 更新增益
            Dim strGain As String
            Dim fGain As Double
            Status = DVPCamera.dvpGetAnalogGain(m_handle, fGain)
            strGain = String.Format("{0:0.00}", fGain)
            STATIC_EXPOGAIN.Text = strGain

            ' 更新分辨率
            Dim QRoiSel As UInteger
            Status = DVPCamera.dvpGetQuickRoiSel(m_handle, QRoiSel)
            If COMBO_RESOLUTION.Items.Count > 0 Then
                COMBO_RESOLUTION.SelectedIndex = QRoiSel
            End If

            ' 更新曝光时间和增益的当前设置值
            UpdateControlExposure()
            UpdateControlGain()

        Else
            BUTTON_START.Text = "Start"
            BUTTON_PROPERTY.Enabled = False
            If COMBO_DEVICES.Items.Count > 0 Then
                BUTTON_OPEN.Enabled = True
            Else
                BUTTON_OPEN.Enabled = False
            End If


            BUTTON_OPEN.Text = "Open"
            BUTTON_START.Enabled = False
            BUTTON_PROPERTY.Enabled = False
            BUTTON_SAVE.Enabled = False

            SLIDER_EXPOSURE_TIME.Enabled = False
            SLIDER_GAIN.Enabled = False
            COMBO_RESOLUTION.Enabled = False
            COMBO_AE_MODE.Enabled = False
            COMBO_FLICK.Enabled = False
        End If
	End Sub

	Private Sub UpdateControlExposure()
		Dim fExpoTime As Double
		fExpoTime = 0.0F
		Dim strValue As String
		strValue = ""
		Dim ExpoTimeDescr As New dvpDoubleDescr()
		Dim status As dvpStatus

        ' 获取曝光时间的描述信息
		status = DVPCamera.dvpGetExposureDescr(m_handle, ExpoTimeDescr)
		If status = dvpStatus.DVP_STATUS_OK Then

            ' 设置曝光时间拖动条的范围
			SLIDER_EXPOSURE_TIME.SetRange(ExpoTimeDescr.fMin, ExpoTimeDescr.fMax)
		End If

        ' 获取曝光时间的初值
		status = DVPCamera.dvpGetExposure(m_handle, fExpoTime)
		If status = dvpStatus.DVP_STATUS_OK Then

            ' 设置曝光时间拖动条初始值
			SLIDER_EXPOSURE_TIME.Value = fExpoTime
			strValue = String.Format("{0:#0.000}", fExpoTime)
			STATIC_EXPOTIME.Text = strValue
		End If
	End Sub

	Private Sub UpdateControlGain()
		Dim status As dvpStatus
		Dim fAnalogGain As Double
		fAnalogGain = 0.0
		Dim strValue As String
		strValue = ""
		Dim AnalogGainDescr As New dvpFloatDescr()

        ' 获取模拟增益的描述信息
        status = DVPCamera.dvpGetAnalogGainDescr(m_handle, AnalogGainDescr)
		If status = dvpStatus.DVP_STATUS_OK Then

            ' 设置模拟增益拖动条的范围
			SLIDER_GAIN.SetRange(AnalogGainDescr.fMin * 100, AnalogGainDescr.fMax * 100) '单位x
		End If

        ' 获取模拟增益并设置模拟增益的初始值
		status = DVPCamera.dvpGetAnalogGain(m_handle, fAnalogGain)

        If (status = dvpStatus.DVP_STATUS_OK) Then

            ' 设置增益拖动条初始值
            SLIDER_GAIN.Value = (fAnalogGain * 100)
            strValue = String.Format("{0:#0.000}", fAnalogGain)
            STATIC_EXPOGAIN.Text = strValue + "x"
        End If
	End Sub

    ' 分辨率
	Private Sub InitControlResolution()
		Dim QuickRoiSel As UInteger
		Dim QuickRoiDetail As New dvpQuickRoi()
		Dim status As dvpStatus
		Dim QuickRoiDescr As New dvpSelectionDescr()

		COMBO_RESOLUTION.Items.Clear()
		If IsValidHandle(m_handle) = False Then
			COMBO_RESOLUTION.Enabled = False
			Return
		End If

        ' 获取相机分辨率索引号
		status = DVPCamera.dvpGetQuickRoiSelDescr(m_handle, QuickRoiDescr)
		If status = dvpStatus.DVP_STATUS_OK Then
			For iNum = 0 To QuickRoiDescr.uCount - 1
				status = DVPCamera.dvpGetQuickRoiSelDetail(m_handle, iNum, QuickRoiDetail)
				If (status = dvpStatus.DVP_STATUS_OK) Then
					COMBO_RESOLUTION.Items.Add(QuickRoiDetail.selection._string)
				End If
			Next
		End If

        ' 获取分辨率模式索引
		status = DVPCamera.dvpGetResolutionModeSel(m_handle, QuickRoiSel)
		If (status = dvpStatus.DVP_STATUS_OK) Then
			COMBO_RESOLUTION.SelectedIndex = QuickRoiSel
		End If

		COMBO_RESOLUTION.Enabled = True

	End Sub

    ' AE设置
	Private Sub InitControlAeMode()
		COMBO_AE_MODE.Items.Clear()
		If IsValidHandle(m_handle) = False Then
			COMBO_AE_MODE.Enabled = False
			Return
		End If

		COMBO_AE_MODE.Items.Add("AE_MODE_AE_AG")
		COMBO_AE_MODE.Items.Add("AE_MODE_AG_AE")
		COMBO_AE_MODE.Items.Add("AE_MODE_AE_ONLY")
		COMBO_AE_MODE.Items.Add("AE_MODE_AG_ONLY")
		COMBO_AE_MODE.SelectedIndex = 0
		COMBO_AE_MODE.Enabled = True
	End Sub

    ' Flick设置
	Private Sub InitControlFlick()
		COMBO_FLICK.Items.Clear()
		If (m_handle = 0) Then
			COMBO_FLICK.Enabled = False
			Return
		End If

		COMBO_FLICK.Items.Add("ANTIFLICK_DISABLE")
		COMBO_FLICK.Items.Add("ANTIFLICK_50HZ")
		COMBO_FLICK.Items.Add("ANTIFLICK_60HZ")
		COMBO_FLICK.SelectedIndex = 1
		COMBO_FLICK.Enabled = True

	End Sub

	Private Sub OpenCamera()
		Static Dim pCallBack As New DVPCamera.dvpStreamCallback(AddressOf _dvpStreamCallback)
		Dim status As dvpStatus

		If IsValidHandle(m_handle) = False Then
			Dim i As UInteger
			i = COMBO_DEVICES.SelectedIndex
			status = DVPCamera.dvpOpen(i, dvpOpenMode.OPEN_NORMAL, m_handle)
			If status = dvpStatus.DVP_STATUS_OK Then
				m_strFriendlyName = COMBO_DEVICES.Text
				status = DVPCamera.dvpRegisterStreamCallback(m_handle, pCallBack, dvpStreamEvent.STREAM_EVENT_PROCESSED, 0)
                ' 分辨率
				InitControlResolution()

                ' AE设置
                InitControlAeMode()

                ' Flick设置
				InitControlFlick()
				UpdateControlExposure()
				UpdateControlGain()
			Else
				m_handle = 0
				MessageBox.Show("打开失败")
			End If
		Else
			DVPCamera.dvpStop(m_handle)
			m_b_start = False
			DVPCamera.dvpUnregisterStreamCallback(Handle, pCallBack, dvpStreamEvent.STREAM_EVENT_PROCESSED, 0)
			DVPCamera.dvpClose(m_handle)
			m_handle = 0
			pictureBox.Invalidate()
		End If
		InitCtrl()
	End Sub

	Private Sub StartCamera()
		Dim state As dvpStreamState
		state = dvpStreamState.STATE_STOPED
		Dim status As dvpStatus
		status = dvpStatus.DVP_STATUS_UNKNOW

		If IsValidHandle(m_handle) = True Then

            ' 根据当前视频状态，执行相反的操作，实现一个按钮既能启动又能停止
			status = DVPCamera.dvpGetStreamState(m_handle, state)
			If (state = dvpStreamState.STATE_STARTED) Then
				status = DVPCamera.dvpStop(m_handle)
				If status = dvpStatus.DVP_STATUS_OK Then
					m_b_start = False
				Else
					m_b_start = True
				End If
			Else
				status = DVPCamera.dvpStart(m_handle)
				If status = dvpStatus.DVP_STATUS_OK Then
					m_b_start = True
				Else
					m_b_start = False
				End If

			End If
		End If
		InitCtrl()
	End Sub
	Private Sub SetParam()
		If IsValidHandle(m_handle) = True Then
			Dim status As dvpStatus
            status = DVPCamera.dvpShowPropertyModalDialog(m_handle, Me.Handle())

            ' 此时一些配置可能发生改变，将同步到界面
			InitCtrl()
		End If
	End Sub

    ' 保存文件
	Private Sub SaveFile()
		If m_b_start = False Then
			Return
		End If
		Dim sfd As New SaveFileDialog()
		Dim file_path As String
		sfd.Filter = "bmp文件(*.bmp)|*.bmp|jpg文件(*.jpeg)|*.jpeg|png文件(*.png)|*.png"

		If (sfd.ShowDialog() = DialogResult.OK) Then
			file_path = sfd.FileName
			Dim buffer As IntPtr
			Dim frame As New dvpFrame()
			Dim status As dvpStatus

            ' 从视频流中抓取一帧图像，要求5000ms以内
			status = DVPCamera.dvpGetFrame(m_handle, frame, buffer, 5000)
            If (status = dvpStatus.DVP_STATUS_OK) Then

                ' 将图像保存为图片文件
                status = DVPCamera.dvpSavePicture(frame, buffer, file_path, 100)
            ElseIf (status = dvpStatus.DVP_STATUS_TIME_OUT) Then
                MessageBox.Show(("获取图像数据超时!"))
            Else
                MessageBox.Show(("获取图像数据时发生错误!"))
            End If
		End If
	End Sub


	Private Sub COMBO_FLICK_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles COMBO_FLICK.SelectedIndexChanged
		Dim status As dvpStatus
		status = dvpStatus.DVP_STATUS_OK

        ' 获取自动曝光索引
        If (COMBO_FLICK.SelectedIndex > 2) Then
            Return
        End If

		If (COMBO_FLICK.SelectedIndex = 0) Then
			status = DVPCamera.dvpSetAntiFlick(m_handle, dvpAntiFlick.ANTIFLICK_DISABLE)
		ElseIf (COMBO_FLICK.SelectedIndex = 2) Then
			status = DVPCamera.dvpSetAntiFlick(m_handle, dvpAntiFlick.ANTIFLICK_60HZ)
		ElseIf (COMBO_FLICK.SelectedIndex = 1) Then
			status = DVPCamera.dvpSetAntiFlick(m_handle, dvpAntiFlick.ANTIFLICK_50HZ)
		End If

	End Sub

	Private Sub COMBO_AE_MODE_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles COMBO_AE_MODE.SelectedIndexChanged
		Dim status As dvpStatus
        status = dvpStatus.DVP_STATUS_OK

        ' 获取自动曝光模式索引
		Dim iSel As Integer

		iSel = COMBO_AE_MODE.SelectedIndex

		If (iSel > 3) Then
			Return
        ElseIf (iSel = 2) Then

            ' 仅打开自动曝光
            status = DVPCamera.dvpSetAeMode(m_handle, dvpAeMode.AE_MODE_AE_ONLY)
        ElseIf (iSel = 3) Then

            ' 仅打开自动增益
            status = DVPCamera.dvpSetAeMode(m_handle, dvpAeMode.AE_MODE_AG_ONLY)
        ElseIf (iSel = 1) Then

            ' 自动增益优先
            status = DVPCamera.dvpSetAeMode(m_handle, dvpAeMode.AE_MODE_AG_AE)
		End If

        ' 自动曝光优先
		If (iSel = 0) Then
			status = DVPCamera.dvpSetAeMode(m_handle, dvpAeMode.AE_MODE_AE_AG)
		End If

		InitCtrl()
	End Sub

	Private Sub COMBO_RESOLUTION_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles COMBO_RESOLUTION.SelectedIndexChanged
		Dim status As dvpStatus
		status = dvpStatus.DVP_STATUS_OK

		If m_b_start = False Then
			Return
		End If

        ' 获取分辨率选择索引
        Dim iSel As Integer
		iSel = COMBO_RESOLUTION.SelectedIndex
		If (iSel < 0) Then
			Return
		End If

        ' 关闭视频流
		status = DVPCamera.dvpStop(m_handle)
		If status = dvpStatus.DVP_STATUS_OK Then
            m_b_start = False

            ' 设置相机分辨率
			status = DVPCamera.dvpSetQuickRoiSel(m_handle, iSel)
			If status = dvpStatus.DVP_STATUS_OK Then
                ' 打开视频流
				status = DVPCamera.dvpStart(m_handle)
				If (status = dvpStatus.DVP_STATUS_OK) Then
					m_b_start = True
				Else
					MessageBox.Show(("启动视频流失败!"))
				End If
			Else
				MessageBox.Show(("设置分辨率错误!"))
			End If
		Else
			MessageBox.Show(("关闭视频流失败!"))
		End If

	End Sub

	Private Sub SLIDER_EXPOSURE_TIME_ValueChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles SLIDER_EXPOSURE_TIME.ValueChanged
		Dim strExpoTime As String
		strExpoTime = ""
		Dim fExpoTime As Double
		fExpoTime = 0.0F
		Dim ExpDescr As New dvpDoubleDescr()
		Dim status As dvpStatus


		If (IsValidHandle(m_handle)) Then

            ' 获取所设置的曝光时间拖动条的值
			fExpoTime = SLIDER_EXPOSURE_TIME.Value

            ' 设置曝光时间
            ' 获取曝光时间的范围，避免设置值超出范围
			status = DVPCamera.dvpGetExposureDescr(m_handle, ExpDescr)

			If (fExpoTime > ExpDescr.fMax) Then
				fExpoTime = ExpDescr.fMax

				If (fExpoTime < ExpDescr.fMin) Then
					fExpoTime = ExpDescr.fMin
				End If
			End If
			' 先设置曝光时间
			status = DVPCamera.dvpSetExposure(m_handle, fExpoTime)

			'  再获取曝光时间，由于调节精度(步进值)的问题，获取值可能与设置值有些差异，以获取值为准
			status = DVPCamera.dvpSetExposure(m_handle, fExpoTime)


			' 设置曝光时间文本
			strExpoTime = String.Format("{0:#0.000}", fExpoTime)
			STATIC_EXPOTIME.Text = strExpoTime
		End If
	End Sub

	Private Sub SLIDER_GAIN_ValueChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles SLIDER_GAIN.ValueChanged
		Dim strGain As String
		strGain = ""
		Dim fGain As Double
		fGain = 0.0
		Dim status As dvpStatus

        If (IsValidHandle(m_handle)) Then

            ' 获取所设置的模拟增益拖动条值
            fGain = SLIDER_GAIN.Value * 1.0F / 100

            ' 先设置增益值
            status = DVPCamera.dvpSetAnalogGain(m_handle, fGain)

            ' 再获取增益值，由于调节精度(步进值)的问题，获取值可能与设置值有些差异，以获取值为准
            status = DVPCamera.dvpGetAnalogGain(m_handle, fGain)

            ' 设置模拟增益文本
            strGain = String.Format("{0:0.000}", fGain)
            STATIC_EXPOGAIN.Text = strGain + "x"
        End If
	End Sub

	Private Sub COMBO_AE_MODE_ImeModeChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles COMBO_AE_MODE.ImeModeChanged
		Dim status As dvpStatus
		status = dvpStatus.DVP_STATUS_OK

        ' 获取自动曝光模式索引
		If (COMBO_AE_MODE.SelectedIndex > 3) Then
			Return
		End If

        If (COMBO_AE_MODE.SelectedIndex = 0) Then

            ' 自动曝光优先
            status = DVPCamera.dvpSetAeMode(m_handle, dvpAeMode.AE_MODE_AE_AG)
        ElseIf (COMBO_AE_MODE.SelectedIndex = 1) Then

            ' 自动增益优先
            status = DVPCamera.dvpSetAeMode(m_handle, dvpAeMode.AE_MODE_AG_AE)
        ElseIf (COMBO_AE_MODE.SelectedIndex = 2) Then

            ' 仅打开自动曝光
            status = DVPCamera.dvpSetAeMode(m_handle, dvpAeMode.AE_MODE_AE_ONLY)
        ElseIf (COMBO_AE_MODE.SelectedIndex = 3) Then

            ' 仅打开自动增益
            status = DVPCamera.dvpSetAeMode(m_handle, dvpAeMode.AE_MODE_AG_ONLY)
        End If

		InitCtrl()
	End Sub

    ' 回调函数
	Public Function _dvpStreamCallback(ByVal handle As UInteger, ByVal _event As dvpStreamEvent, ByVal pContext As IntPtr, ByRef refFrame As dvpFrame, ByVal pBuffer As IntPtr) As Integer
		Dim status As dvpStatus
		Dim ptr As IntPtr
		ptr = 0

		status = DVPCamera.dvpDrawPicture(refFrame, pBuffer, m_ptr_wnd, ptr, ptr)
		Return status
	End Function

	Private Sub BasicFunction_FormClosing(ByVal sender As System.Object, ByVal e As System.Windows.Forms.FormClosingEventArgs) Handles MyBase.FormClosing
		If (IsValidHandle(m_handle)) Then
			Static Dim pCallBack As New DVPCamera.dvpStreamCallback(AddressOf _dvpStreamCallback)
			DVPCamera.dvpStop(m_handle)
			m_b_start = False
			DVPCamera.dvpUnregisterStreamCallback(m_handle, pCallBack, dvpStreamEvent.STREAM_EVENT_PROCESSED, 0)
			DVPCamera.dvpClose(m_handle)
			m_handle = 0
		End If
	End Sub

	Private Sub CHECK_AEOPERATION_CheckedChanged(sender As System.Object, e As System.EventArgs) Handles CHECK_AEOPERATION.CheckedChanged
		If IsValidHandle(m_handle) Then
			If CHECK_AEOPERATION.Checked Then
				DVPCamera.dvpSetAeOperation(m_handle, dvpAeOperation.AE_OP_CONTINUOUS)
			Else
				DVPCamera.dvpSetAeOperation(m_handle, dvpAeOperation.AE_OP_OFF)
			End If
			InitCtrl()
		End If
	End Sub

End Class
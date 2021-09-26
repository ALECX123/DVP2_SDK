Imports DVPCameraType
Imports DVPCameraType.DVPCamera
Imports System.Runtime.InteropServices

Public Class Trigger
	Dim m_handle As UInteger
	Dim m_bAeOp As Boolean
	Dim m_n_dev_count As Integer
	Dim m_strFriendlyName As String

	Dim m_ptr_wnd As IntPtr
	Dim m_b_start As Boolean

	Dim m_DelayDescr As New dvpDoubleDescr()
	Dim m_FilterDescr As New dvpDoubleDescr()
	Dim m_LoopDescr As New dvpDoubleDescr()

	Dim m_TriggerDelay As Double
	Dim m_TriggerFilter As Double
	Dim m_TriggerLoop As Double
	
    ' 检查相机是否打开
	Private Function IsValidHandle(ByVal handleid As UInteger) As Boolean
		Dim bValidHandle As Boolean
		Dim status As dvpStatus
		bValidHandle = False
		status = DVPCamera.dvpIsValid(handleid, bValidHandle)
		Return bValidHandle
	End Function

	Private Sub InitDevList()
		Dim status As dvpStatus
		Dim i As UInteger
		Dim n As UInteger

		Dim dev_info As New dvpCameraInfo()
        DevNameCombo.Items.Clear()

        ' 获得当前能连接的相机数量
		status = DVPCamera.dvpRefresh(n)
		m_n_dev_count = n
		If status = dvpStatus.DVP_STATUS_OK Then
            For i = 0 To n - 1

                ' 逐个枚举出每个相机的信息
                status = DVPCamera.dvpEnum(i, dev_info)
                If (status = dvpStatus.DVP_STATUS_OK) Then

                    ' 界面使用的是UNICODE，枚举的设备信息为ANSI字符串，需要将ANSI转UNICODE
                    Dim item As Integer
                    item = DevNameCombo.Items.Add(dev_info.FriendlyName)
                    If (item = 0) Then
                        DevNameCombo.SelectedIndex = item
                    End If
                End If
            Next
		End If

		If (n = 0) Then
			OpenDev.Enabled = False
		Else
			OpenDev.Enabled = True
		End If
		InitCtrls()
	End Sub

    ' 设置控件状态
	Private Sub InitCtrls()
		Dim status As dvpStatus

        If (IsValidHandle(m_handle)) Then

            ' 此时已经打开了一个设备
            Dim state As New dvpStreamState()
            status = DVPCamera.dvpGetStreamState(m_handle, state)
            OpenDev.Text = "Close"
            If state = dvpStreamState.STATE_STARTED Then
                StartPlay.Text = "Stop"
            Else
                StartPlay.Text = "Start"
            End If

            StartPlay.Enabled = True
            PropertSet.Enabled = True

            ' 以下使能示例相关功能的控件
            InputIOCombo.Enabled = True
            InputSignalTypeCombo.Enabled = True
            OutputSignalType.Enabled = True
            OutIOCombo.Enabled = True
            EditFilter.Enabled = True
            TriggerDelay.Enabled = True
            TriggerLoop.Enabled = True
            TriggerMode.Enabled = True
            LoopTrigger.Enabled = True
            EnableIn.Enabled = True
            EnableOut.Enabled = True
            SoftTriggerFire.Enabled = True
            ApplyLoop.Enabled = True
            ApplyDelay.Enabled = True
            FilterApply.Enabled = True

            ' 以下更新触发功能相关的界面
            Dim bTrig As Boolean
            Dim bLoop As Boolean
            bTrig = False
            bLoop = False

            ' 触发模式使能状态
            status = DVPCamera.dvpGetTriggerState(m_handle, bTrig)
            TriggerMode.Checked = bTrig
            status = DVPCamera.dvpSetTriggerState(m_handle, bTrig)
            If (status <> dvpStatus.DVP_STATUS_OK) Then

                ' 此时要确认相机是否支持触发功能
                TriggerMode.Enabled = False
            End If

            SoftTriggerFire.Enabled = bTrig

            ' 循环触发使能状态
            status = DVPCamera.dvpGetSoftTriggerLoopState(m_handle, bLoop)
			LoopTrigger.Checked = bLoop
			If status = dvpStatus.DVP_STATUS_OK Then
				LoopTrigger.Enabled = True
			Else
				LoopTrigger.Enabled = False
			End If
			' 外部触发输入IO相关状态
			Dim bExtTrigIn As Boolean
			bExtTrigIn = False
			Dim UserIoInfo As New dvpUserIoInfo()
			Dim InIoFunc As New dvpInputIoFunction()

			' 枚举出所有UserIO，并检查是否有IO用于触发输入功能
			status = DVPCamera.dvpGetUserIoInfo(m_handle, UserIoInfo)

			InputIOCombo.Items.Clear()
			Dim nLength As Integer
			nLength = IIf(8 < UserIoInfo.inputValid.Length, 8, UserIoInfo.inputValid.Length)


			Dim inputValid() As Char = UserIoInfo.inputValid.ToCharArray()
			Dim c As Char

			For i = 0 To nLength - 1
				If inputValid(i) > c Then
					Dim str As String
					Dim InputIo As dvpInputIo
					InputIo = i + dvpInputIo.INPUT_IO_1

					' 把IO名称添加到下拉列表中
					Dim nInItem As Integer
					nInItem = i + 1
					str = "IN_" + nInItem.ToString()
					Dim item As Integer
					item = InputIOCombo.Items.Add(str)

					' 检查是否有输入IO被设置为触发输入功能
					status = DVPCamera.dvpGetInputIoFunction(m_handle, InputIo, InIoFunc)
					If (bExtTrigIn <> True And InIoFunc = dvpInputIoFunction.INPUT_FUNCTION_TRIGGER) Then

						' 找到一个IO已经被设置为触发输入信号
						bExtTrigIn = True

						' 在下拉列表中选取那个被设置为触发输入功能的IO
						InputIOCombo.SelectedIndex = i
					End If
				End If
			Next

			If bExtTrigIn Then

				' 在界面上指示出已经有触发输入信号被使用
				EnableIn.Checked = True
				InputIOCombo.Enabled = True
			Else

				' 没有IO被设置为触发输入，默认在下拉列表中选取第一个
				If (InputIOCombo.Items.Count > 0) Then
					InputIOCombo.SelectedIndex = 0
				End If

				' 在界面上指示出没有Strobe输出信号被使用
				EnableIn.Checked = False
			End If

			' 更新触发输入信号类型列表
			InputSignalTypeCombo.Items.Clear()
			InputSignalTypeCombo.Items.Add(("Off"))
			InputSignalTypeCombo.Items.Add(("Falling Edge"))
			InputSignalTypeCombo.Items.Add(("Low Level"))
			InputSignalTypeCombo.Items.Add(("Rising Edge"))
			InputSignalTypeCombo.Items.Add(("High Level"))

			Dim TriggerType As dvpTriggerInputType
			status = DVPCamera.dvpGetTriggerInputType(m_handle, TriggerType)
			InputSignalTypeCombo.SelectedIndex = TriggerType

			' 以下更新Strobe功能相关的界面
			Dim bExtStrobeOut As Boolean
			bExtStrobeOut = False
			Dim OutIoFunc As dvpOutputIoFunction

			' 枚举出所有UserIO，并检查是否有IO用于Strobe输出功能
			OutIOCombo.Items.Clear()

			Dim outputValid() As Char = UserIoInfo.outputValid.ToCharArray()
			nLength = IIf(8 < UserIoInfo.outputValid.Length, 8, UserIoInfo.outputValid.Length)
			For i = 0 To nLength - 1

				If outputValid(i) > c Then
					Dim str1 As String
					Dim OutputIo As dvpOutputIo
					OutputIo = (i + dvpOutputIo.OUTPUT_IO_1)

					' 把IO名称添加到下拉列表中
					Dim nOutItem As Integer
					nOutItem = i + 1
					str1 = "OUT_" + nOutItem.ToString()
					OutIOCombo.Items.Add(str1)

					' 检查是否有输出IO被设置为Strobe输出功能
					status = DVPCamera.dvpGetOutputIoFunction(m_handle, OutputIo, OutIoFunc)
					If (bExtStrobeOut = False And OutIoFunc = dvpOutputIoFunction.OUTPUT_FUNCTION_STROBE) Then

						' 找到一个IO已经被设置为strobe输出功能的IO
						bExtStrobeOut = True

						' 在下拉列表中选取那个被设置为strobe输出功能的IO
						OutIOCombo.SelectedIndex = i
					End If
				End If
			Next

			If bExtStrobeOut Then

				' 在界面上指示出已经有Strobe输出信号被使用
				EnableOut.Checked = True
			Else

				' 没有IO被设置为触发输入，默认在下拉列表中选取第一个
				If (OutIOCombo.Items.Count > 0) Then
					OutIOCombo.SelectedIndex = 0
				Else
					OutIOCombo.Items.Add("OUT_1")
					OutIOCombo.SelectedIndex = 0
				End If

				' 在界面上指示出没有Strobe输出信号被使用
				EnableOut.Checked = False
			End If

			' 更新Strobe输出信号类型列表
			OutputSignalType.Items.Clear()
			OutputSignalType.Items.Add(("Off"))
			OutputSignalType.Items.Add(("Low Level"))
			OutputSignalType.Items.Add(("High Level"))

			' 获取Strobe信号类型
			Dim StrobeType As dvpStrobeOutputType
			status = DVPCamera.dvpGetStrobeOutputType(m_handle, StrobeType)
			OutputSignalType.SelectedIndex = StrobeType

			' 以下这些获取的描述信息将用于更新编辑框中设置值的范围
			status = DVPCamera.dvpGetTriggerDelayDescr(m_handle, m_DelayDescr)

			status = DVPCamera.dvpGetTriggerJitterFilterDescr(m_handle, m_FilterDescr)
			status = DVPCamera.dvpGetSoftTriggerLoopDescr(m_handle, m_LoopDescr)

			' 以下更新编辑框中的设置值
			status = DVPCamera.dvpGetSoftTriggerLoop(m_handle, m_TriggerLoop)
			TriggerLoop.Text = m_TriggerLoop.ToString()
			
			status = DVPCamera.dvpGetTriggerDelay(m_handle, m_TriggerDelay)
			TriggerDelay.Text = m_TriggerDelay.ToString()

			status = DVPCamera.dvpGetTriggerJitterFilter(m_handle, m_TriggerFilter)
			If m_TriggerFilter < 1 Then
				m_TriggerFilter = 1
			End If
			EditFilter.Text = m_TriggerFilter.ToString()
		Else

			' 此时还没有设备被打开
			' 更新基本功能控件
			OpenDev.Text = "Open"
			StartPlay.Enabled = False
			PropertSet.Enabled = False
			If (DevNameCombo.Items.Count = 0) Then

				' 没有设备存在
				OpenDev.Enabled = False
			Else
				OpenDev.Enabled = True
			End If

			' 更新本示例相关功能的控件
			InputIOCombo.Enabled = False
			InputSignalTypeCombo.Enabled = False
			OutputSignalType.Enabled = False
			OutIOCombo.Enabled = False
			EditFilter.Enabled = False
			TriggerDelay.Enabled = False
			TriggerLoop.Enabled = False
			TriggerMode.Enabled = False
			LoopTrigger.Enabled = False
			EnableIn.Enabled = False
			EnableOut.Enabled = False
			SoftTriggerFire.Enabled = False
			ApplyLoop.Enabled = False
			ApplyDelay.Enabled = False
			FilterApply.Enabled = False
		End If
	End Sub

    ' 回调函数
	Public Function _dvpStreamCallback(ByVal handle As UInteger, ByVal _event As dvpStreamEvent, ByVal pContext As IntPtr, ByRef refFrame As dvpFrame, ByVal pBuffer As IntPtr) As Integer
		Dim status As dvpStatus
		Dim ptr As IntPtr
		ptr = 0

		status = DVPCamera.dvpDrawPicture(refFrame, pBuffer, m_ptr_wnd, ptr, ptr)
		Return status
	End Function

	Private Sub OpenCamera()
		Static Dim pCallBack As New DVPCamera.dvpStreamCallback(AddressOf _dvpStreamCallback)
		Dim status As dvpStatus
		status = dvpStatus.DVP_STATUS_OK
		Dim strName As String
		strName = ""

		If IsValidHandle(m_handle) = False Then
			strName = DevNameCombo.Text
            If (strName <> "") Then

                ' 通过枚举到并选择的FriendlyName打开指定设备
                status = DVPCamera.dvpOpenByName(strName, dvpOpenMode.OPEN_NORMAL, m_handle)

                If (status <> dvpStatus.DVP_STATUS_OK) Then
                    MessageBox.Show("打开失败")
                Else
                    m_strFriendlyName = strName

                    ' 如果需要图像显示，可以注册回调函数，在回调函数中完成绘图操作
                    ' 注意：回调函数中执行的绘图操作，可能会对dvpGetFrame接口获取的图像数据造成延时
                    status = DVPCamera.dvpRegisterStreamCallback(m_handle, pCallBack, dvpStreamEvent.STREAM_EVENT_PROCESSED, 0)
                End If
            End If
		Else
			status = DVPCamera.dvpClose(m_handle)
			m_handle = 0
			pictureBox.Invalidate()
		End If
		InitCtrls()
	End Sub

    ' 播放视频
	Private Sub StartCamera()
		If IsValidHandle(m_handle) Then
			Dim state As dvpStreamState
            Dim status As dvpStatus

            ' 根据当前视频状态，执行相反的操作，实现一个按钮既能启动又能停止
			status = DVPCamera.dvpGetStreamState(m_handle, state)

			If (state = dvpStreamState.STATE_STARTED) Then
				status = DVPCamera.dvpStop(m_handle)
			Else
				status = DVPCamera.dvpStart(m_handle)
			End If
		End If
		InitCtrls()
	End Sub

	Private Sub SetParam()
		If IsValidHandle(m_handle) = True Then
			Dim status As dvpStatus
            status = DVPCamera.dvpShowPropertyModalDialog(m_handle, Me.Handle())

            ' 此时一些配置可能发生改变，将同步到界面
			InitCtrls()
		End If
	End Sub

	Private Sub Trigger_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
		m_handle = 0
		m_bAeOp = False
		m_n_dev_count = 0
		m_strFriendlyName = ""
		m_ptr_wnd = 0
		m_b_start = False
		m_TriggerDelay = 0.0
		m_TriggerFilter = 0.0
		m_TriggerLoop = 0.0
		m_ptr_wnd = pictureBox.Handle
		InitDevList()
	End Sub

	Private Sub Trigger_FormClosing(ByVal sender As System.Object, ByVal e As System.Windows.Forms.FormClosingEventArgs) Handles MyBase.FormClosing
		If (IsValidHandle(m_handle)) Then
			DVPCamera.dvpClose(m_handle)
			m_handle = 0
		End If
	End Sub

	Private Sub ScanDev_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ScanDev.Click
		InitDevList()
	End Sub

	Private Sub OpenDev_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles OpenDev.Click
		OpenCamera()
	End Sub

	Private Sub StartPlay_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles StartPlay.Click
		StartCamera()
	End Sub

	Private Sub PropertSet_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PropertSet.Click
		SetParam()
	End Sub

	Private Sub TriggerMode_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TriggerMode.CheckedChanged
        If IsValidHandle(m_handle) Then

            ' 使能/禁用触发模式
            DVPCamera.dvpSetTriggerState(m_handle, TriggerMode.Checked)
            InitCtrls()
        End If
	End Sub

	Private Sub SoftTriggerFire_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles SoftTriggerFire.Click
        If (IsValidHandle(m_handle)) Then

            ' 这个函数执行一次，相当于产生一次外触发
            ' 注意：如果曝光时间较长时，过快的点击"Soft Trigger Fire"有可能导致触发失败，因为上一帧还可能出于曝光或未输出完的状态
            DVPCamera.dvpTriggerFire(m_handle)
        End If
	End Sub

	Private Sub LoopTrigger_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles LoopTrigger.CheckedChanged
		DVPCamera.dvpSetSoftTriggerLoopState(m_handle, LoopTrigger.Checked)
	End Sub

	Private Sub ApplyLoop_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ApplyLoop.Click
		If (IsValidHandle(m_handle)) Then
			m_TriggerLoop = CType(Val(TriggerLoop.Text), Single)
			DVPCamera.dvpSetSoftTriggerLoop(m_handle, m_TriggerLoop)
		End If
	End Sub

	Private Sub ApplyDelay_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ApplyDelay.Click
		If (IsValidHandle(m_handle)) Then
			m_TriggerDelay = CType(Val(TriggerDelay.Text), Single)
			DVPCamera.dvpSetTriggerDelay(m_handle, m_TriggerDelay)
		End If
	End Sub

	Private Sub EnableInCheck()
		If (IsValidHandle(m_handle)) Then
			Dim UserIoInfo As New dvpUserIoInfo()
			Dim i As Integer
			Dim status As dvpStatus
			status = DVPCamera.dvpGetUserIoInfo(m_handle, UserIoInfo)

            ' 先将所有INPUT IO设置为Normal模式
            Dim nInLength As Integer
            nInLength = IIf(8 < UserIoInfo.inputValid.Length, 8, UserIoInfo.inputValid.Length)
			Dim inputValid() As Char = UserIoInfo.inputValid.ToCharArray()
			Dim c As Char

			For i = 0 To nInLength - 1
				If inputValid(i) > c Then
					DVPCamera.dvpSetInputIoFunction(m_handle, (dvpInputIo.INPUT_IO_1 + i), dvpInputIoFunction.INPUT_FUNCTION_NORMAL)
				End If
			Next

			' 如果使能了ExtTriggerIn，则将选择的InputIo配置为触发输入功能
			If (EnableIn.Checked) Then
				Dim j As Integer
				j = InputIOCombo.SelectedIndex
				Dim InputIo As dvpInputIo

				If (j >= 0) Then
					InputIo = j + dvpInputIo.INPUT_IO_1
					DVPCamera.dvpSetInputIoFunction(m_handle, InputIo, dvpInputIoFunction.INPUT_FUNCTION_TRIGGER)
				End If

			End If
		End If
	End Sub
       
	Private Sub EnableIn_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles EnableIn.CheckedChanged
		EnableInCheck()
	End Sub

	Private Sub InputIOCombo_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles InputIOCombo.SelectedIndexChanged
        If (IsValidHandle(m_handle)) Then

            ' 触发输入IO的改变和勾选触发输入使能是同样的处理过程
            EnableInCheck()
        End If
	End Sub

	Private Sub InputSignalTypeCombo_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles InputSignalTypeCombo.SelectedIndexChanged
		If (IsValidHandle(m_handle)) Then
			Dim TriggerType As dvpTriggerInputType
			TriggerType = (dvpTriggerInputType.TRIGGER_IN_OFF + InputSignalTypeCombo.SelectedIndex)
			DVPCamera.dvpSetTriggerInputType(m_handle, TriggerType)
		End If
	End Sub

	Private Sub EnableOutCheck()
		If (IsValidHandle(m_handle)) Then
			Dim UserIoInfo As New dvpUserIoInfo()
			Dim i As Integer
			Dim status As dvpStatus
			status = DVPCamera.dvpGetUserIoInfo(m_handle, UserIoInfo)

            ' 先将所有OUTPUT IO设置为Normal模式
            Dim nOutLength As Integer
            nOutLength = IIf(8 < UserIoInfo.outputValid.Length, 8, UserIoInfo.outputValid.Length)

			Dim outputValid() As Char = UserIoInfo.outputValid.ToCharArray()
			Dim c As Char

			For i = 0 To nOutLength - 1
				If outputValid(i) > c Then
					status = DVPCamera.dvpSetOutputIoFunction(m_handle, (dvpOutputIo.OUTPUT_IO_1 + i), dvpOutputIoFunction.OUTPUT_FUNCTION_NORMAL)
				End If

				' 如果使能了ExtStrobeOut，则将选择的OutputIo配置为Strobe输出功能
				If (EnableOut.Checked) Then
					Dim j As Integer
					j = OutIOCombo.SelectedIndex
					Dim OutputIo As New dvpOutputIo()
					If (j >= 0) Then
						OutputIo = (j + dvpOutputIo.OUTPUT_IO_1)
						status = DVPCamera.dvpSetOutputIoFunction(m_handle, OutputIo, dvpOutputIoFunction.OUTPUT_FUNCTION_STROBE)
					End If
				End If
			Next
		End If
	End Sub

	Private Sub OutIOCombo_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles OutIOCombo.SelectedIndexChanged
        If IsValidHandle(m_handle) Then

            ' Strobe输出IO的改变和勾选Strobe输出使能是同样的处理过程
            EnableOutCheck()
        End If
	End Sub

	Private Sub OutputSignalType_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles OutputSignalType.SelectedIndexChanged
		If (IsValidHandle(m_handle)) Then
			Dim StrobeType As dvpStrobeOutputType
			StrobeType = dvpStrobeOutputType.STROBE_OUT_OFF + OutputSignalType.SelectedIndex
			DVPCamera.dvpSetStrobeOutputType(m_handle, StrobeType)
		End If
	End Sub

	Private Sub EnableOut_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles EnableOut.CheckedChanged
		EnableOutCheck()
	End Sub

	Private Sub FilterApply_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles FilterApply.Click
		If (IsValidHandle(m_handle)) Then
			m_TriggerFilter = CType(Val(EditFilter.Text), Single)
			DVPCamera.dvpSetTriggerJitterFilter(m_handle, m_TriggerFilter)
		End If
	End Sub

	Private Sub TriggerLoop_KeyPress(sender As System.Object, e As System.Windows.Forms.KeyPressEventArgs) Handles TriggerLoop.KeyPress
		Dim str As String
		str = TriggerLoop.Text

		If Char.IsNumber(e.KeyChar) Then
			e.Handled = False
		ElseIf e.KeyChar = "." And str.Length > 0 Then
			If InStr(str, ".") Then
				e.Handled = True
			Else
				e.Handled = False
			End If
		ElseIf Char.IsControl(e.KeyChar) Then
			e.Handled = False
		Else
			e.Handled = True
		End If
	End Sub

	Private Sub TriggerDelay_KeyPress(sender As System.Object, e As System.Windows.Forms.KeyPressEventArgs) Handles TriggerDelay.KeyPress
		Dim str As String
		str = TriggerLoop.Text

		If Char.IsNumber(e.KeyChar) Then
			e.Handled = False
		ElseIf e.KeyChar = "." And str.Length > 0 Then
			If InStr(str, ".") Then
				e.Handled = True
			Else
				e.Handled = False
			End If
		ElseIf Char.IsControl(e.KeyChar) Then
			e.Handled = False
		Else
			e.Handled = True
		End If
	End Sub

	Private Sub EditFilter_KeyPress(sender As System.Object, e As System.Windows.Forms.KeyPressEventArgs) Handles EditFilter.KeyPress
		Dim str As String
		str = TriggerLoop.Text

		If Char.IsNumber(e.KeyChar) Then
			e.Handled = False
		ElseIf e.KeyChar = "." And str.Length > 0 Then
			If InStr(str, ".") Then
				e.Handled = True
			Else
				e.Handled = False
			End If
		ElseIf Char.IsControl(e.KeyChar) Then
			e.Handled = False
		Else
			e.Handled = True
		End If
	End Sub
End Class



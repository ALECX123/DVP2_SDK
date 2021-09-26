
Imports DVPCameraType
Imports DVPCameraType.DVPCamera
Imports System.Runtime.InteropServices


Public Class MultipleCamera

	Dim m_n_dev_count_0 As Integer
	Dim m_handle_0 As UInteger
	Dim m_n_dev_count_1 As Integer
	Dim m_handle_1 As UInteger
	Dim m_n_dev_count_2 As Integer
	Dim m_handle_2 As UInteger
	Dim m_n_dev_count_3 As Integer
	Dim m_handle_3 As UInteger

	Dim m_ptr_wnd0 As IntPtr
	Dim m_ptr_wnd1 As IntPtr
	Dim m_ptr_wnd2 As IntPtr
	Dim m_ptr_wnd3 As IntPtr

	Private Sub MultipleCamera_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
		m_ptr_wnd0 = pictureBox.Handle
		m_ptr_wnd1 = pictureBox1.Handle
		m_ptr_wnd2 = pictureBox2.Handle
		m_ptr_wnd3 = pictureBox3.Handle
		InitDevList_0()
		InitDevList_1()
		InitDevList_2()
		InitDevList_3()
	End Sub

	Private Sub MultipleCamera_FormClosing(ByVal sender As System.Object, ByVal e As System.Windows.Forms.FormClosingEventArgs) Handles MyBase.FormClosing
		If (IsValidHandle(m_handle_0)) Then
			DVPCamera.dvpClose(m_handle_0)
			m_handle_0 = 0
		End If

		If (IsValidHandle(m_handle_1)) Then
			DVPCamera.dvpClose(m_handle_1)
			m_handle_1 = 0
		End If

		If (IsValidHandle(m_handle_2)) Then
			DVPCamera.dvpClose(m_handle_2)
			m_handle_2 = 0
		End If

		If (IsValidHandle(m_handle_3)) Then
			DVPCamera.dvpClose(m_handle_3)
			m_handle_3 = 0
		End If
	End Sub

    ' 检查相机是否打开
	Private Function IsValidHandle(ByVal handleid As UInteger) As Boolean
		Dim bValidHandle As Boolean
		Dim status As dvpStatus
		bValidHandle = False
		status = DVPCamera.dvpIsValid(handleid, bValidHandle)
		Return bValidHandle
	End Function

	Private Sub InitDevList_0()
		Dim status As dvpStatus
		Dim i As UInteger
		Dim n As UInteger
		
		Dim dev_info As New dvpCameraInfo()
        DevNameCombo.Items.Clear()

        ' 获得当前能连接的相机数量
		status = DVPCamera.dvpRefresh(n)
		m_n_dev_count_0 = n
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
		InitCtrls_0()
	End Sub

	Private Sub InitDevList_1()
		Dim status As dvpStatus
		Dim i As UInteger
		Dim n As UInteger

		Dim dev_info As New dvpCameraInfo()
        DevNameCombo1.Items.Clear()

        ' 获得当前能连接的相机数量
		status = DVPCamera.dvpRefresh(n)
		m_n_dev_count_1 = n
		If status = dvpStatus.DVP_STATUS_OK Then

            For i = 0 To n - 1

                ' 逐个枚举出每个相机的信息
                status = DVPCamera.dvpEnum(i, dev_info)
                If (status = dvpStatus.DVP_STATUS_OK) Then

                    ' 界面使用的是UNICODE，枚举的设备信息为ANSI字符串，需要将ANSI转UNICODE
                    Dim item As Integer
                    item = DevNameCombo1.Items.Add(dev_info.FriendlyName)
                    If (item = 0) Then
                        DevNameCombo1.SelectedIndex = item
                    End If
                End If
            Next
		End If

		If (n = 0) Then
			OpenDev1.Enabled = False
		Else
			OpenDev1.Enabled = True
		End If
		InitCtrls_1()
	End Sub

	Private Sub InitDevList_2()
		Dim status As dvpStatus
		Dim i As UInteger
		Dim n As UInteger

		Dim dev_info As New dvpCameraInfo()
        DevNameCombo2.Items.Clear()

        ' 获得当前能连接的相机数量
		status = DVPCamera.dvpRefresh(n)
		m_n_dev_count_2 = n
		If status = dvpStatus.DVP_STATUS_OK Then

            For i = 0 To n - 1

                ' 逐个枚举出每个相机的信息
                status = DVPCamera.dvpEnum(i, dev_info)
                If (status = dvpStatus.DVP_STATUS_OK) Then

                    ' 界面使用的是UNICODE，枚举的设备信息为ANSI字符串，需要将ANSI转UNICODE
                    Dim item As Integer
                    item = DevNameCombo2.Items.Add(dev_info.FriendlyName)
                    If (item = 0) Then
                        DevNameCombo2.SelectedIndex = item
                    End If
                End If
            Next
		End If

		If (n = 0) Then
			OpenDev2.Enabled = False
		Else
			OpenDev2.Enabled = True
		End If
		InitCtrls_2()
	End Sub

	Private Sub InitDevList_3()
		Dim status As dvpStatus
		Dim i As UInteger
		Dim n As UInteger

		Dim dev_info As New dvpCameraInfo()
        DevNameCombo3.Items.Clear()

        ' 获得当前能连接的相机数量
		status = DVPCamera.dvpRefresh(n)
		m_n_dev_count_3 = n
		If status = dvpStatus.DVP_STATUS_OK Then

            For i = 0 To n - 1

                ' 逐个枚举出每个相机的信息
                status = DVPCamera.dvpEnum(i, dev_info)
                If (status = dvpStatus.DVP_STATUS_OK) Then

                    ' 界面使用的是UNICODE，枚举的设备信息为ANSI字符串，需要将ANSI转UNICODE
                    Dim item As Integer
                    item = DevNameCombo3.Items.Add(dev_info.FriendlyName)
                    If (item = 0) Then
                        DevNameCombo3.SelectedIndex = item
                    End If
                End If
            Next
		End If

		If (n = 0) Then
			OpenDev3.Enabled = False
		Else
			OpenDev3.Enabled = True
		End If
		InitCtrls_3()
	End Sub

	Private Sub InitCtrls_0()
		Dim status As dvpStatus
        If (IsValidHandle(m_handle_0)) Then

            ' 此时已经有设备被打开
            Dim info As New dvpCameraInfo()
            Dim state As New dvpStreamState()

            status = DVPCamera.dvpGetStreamState(m_handle_0, state)

            ' 设置基本功能控件
            OpenDev.Text = "Close"
			If dvpStreamState.STATE_STARTED = state Then
				StartPlay.Text = "Stop"
			Else
				StartPlay.Text = "Start"
			End If
            StartPlay.Enabled = True

            ' 设置本示例相关功能控件的使能状态
            PropertSet.Enabled = True
            EditUserID.Enabled = True
            SetUserID.Enabled = True

            ' 获取相机信息
            DVPCamera.dvpGetCameraInfo(m_handle_0, info)

			EditUserID.Text = info.UserID
        Else
            ' 此时还没有设备被打开
            ' 设置基本功能控件
            OpenDev.Text = "Open"
            FriendlyName.Text = "Friendly Name"
            StartPlay.Text = "Start"
            StartPlay.Enabled = False

            ' 设置本示例相关功能控件的使能状态()
            EditUserID.Text = ""
            PropertSet.Enabled = False
            SetUserID.Enabled = False
        End If
	End Sub

	Private Sub InitCtrls_1()
		Dim status As dvpStatus
        If (IsValidHandle(m_handle_1)) Then

            ' 此时已经有设备被打开
            Dim info As New dvpCameraInfo()
            Dim state As New dvpStreamState()

            status = DVPCamera.dvpGetStreamState(m_handle_1, state)

            ' 设置基本功能控件
            OpenDev1.Text = "Close"
			If dvpStreamState.STATE_STARTED = state Then
				StartPlay1.Text = "Stop"
			Else
				StartPlay1.Text = "Start"
			End If
            StartPlay1.Enabled = True

            ' 设置本示例相关功能控件的使能状态
            PropertSet1.Enabled = True
            EditUserID1.Enabled = True
            SetUserID1.Enabled = True

            ' 获取相机信息
            DVPCamera.dvpGetCameraInfo(m_handle_1, info)
            EditUserID1.Text = info.UserID
        Else
            ' 此时还没有设备被打开
            ' 设置基本功能控件
            OpenDev1.Text = "Open"
            FriendlyName1.Text = "Friendly Name"
            StartPlay1.Text = "Start"
            StartPlay1.Enabled = False

            ' 设置本示例相关功能控件的使能状态()
            EditUserID1.Text = ""
            PropertSet1.Enabled = False
            SetUserID1.Enabled = False
        End If
	End Sub

	Private Sub InitCtrls_2()
		Dim status As dvpStatus
        If (IsValidHandle(m_handle_2)) Then

            ' 此时已经有设备被打开
            Dim info As New dvpCameraInfo()
            Dim state As New dvpStreamState()

            status = DVPCamera.dvpGetStreamState(m_handle_2, state)

            ' 设置基本功能控件
            OpenDev2.Text = "Close"
			If dvpStreamState.STATE_STARTED = state Then
				StartPlay2.Text = "Stop"
			Else
				StartPlay2.Text = "Start"
			End If
            StartPlay2.Enabled = True

            ' 设置本示例相关功能控件的使能状态
            PropertSet2.Enabled = True
            EditUserID2.Enabled = True
            SetUserID2.Enabled = True

            ' 获取相机信息
            DVPCamera.dvpGetCameraInfo(m_handle_2, info)
            EditUserID2.Text = info.UserID
        Else
            ' 此时还没有设备被打开
            ' 设置基本功能控件
            OpenDev2.Text = "Open"
            FriendlyName2.Text = "Friendly Name"
            StartPlay2.Text = "Start"
            StartPlay2.Enabled = False

            ' 设置本示例相关功能控件的使能状态()
            EditUserID2.Text = ""
            PropertSet2.Enabled = False
            SetUserID2.Enabled = False
        End If
	End Sub

	Private Sub InitCtrls_3()
		Dim status As dvpStatus
        If (IsValidHandle(m_handle_3)) Then

            ' 此时已经有设备被打开
            Dim info As New dvpCameraInfo()
            Dim state As New dvpStreamState()

            status = DVPCamera.dvpGetStreamState(m_handle_3, state)

            ' 设置基本功能控件
			OpenDev3.Text = "Close"
			If dvpStreamState.STATE_STARTED = state Then
				StartPlay3.Text = "Stop"
			Else
				StartPlay3.Text = "Start"
			End If
			StartPlay3.Enabled = True

			' 设置本示例相关功能控件的使能状态
			PropertSet3.Enabled = True
			EditUserID3.Enabled = True
			SetUserID3.Enabled = True

			' 获取相机信息
			DVPCamera.dvpGetCameraInfo(m_handle_3, info)
			EditUserID3.Text = info.UserID
		Else
			' 此时还没有设备被打开
			' 设置基本功能控件
			OpenDev3.Text = "Open"
			FriendlyName3.Text = "Friendly Name"
			StartPlay3.Text = "Start"
			StartPlay3.Enabled = False

			' 设置本示例相关功能控件的使能状态()
			EditUserID3.Text = ""
			PropertSet3.Enabled = False
			SetUserID3.Enabled = False
		End If
	End Sub

	Private Sub ScanDev_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ScanDev.Click
		InitDevList_0()
	End Sub

	Private Sub ScanDev1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ScanDev1.Click
		InitDevList_1()
	End Sub

	Private Sub ScanDev2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ScanDev2.Click
		InitDevList_2()
	End Sub

	Private Sub ScanDev3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ScanDev3.Click
		InitDevList_3()
	End Sub

    ' 数据接收回调函数
	Public Function _dvpStreamCallback0(ByVal handle As UInteger, ByVal _event As dvpStreamEvent, ByVal pContext As IntPtr, ByRef refFrame As dvpFrame, ByVal pBuffer As IntPtr) As Integer
		Dim status As dvpStatus
		status = DVPCamera.dvpDrawPicture(refFrame, pBuffer, m_ptr_wnd0, 0, 0)
		Return status
	End Function

    ' 数据接收回调函数
	Public Function _dvpStreamCallback1(ByVal handle As UInteger, ByVal _event As dvpStreamEvent, ByVal pContext As IntPtr, ByRef refFrame As dvpFrame, ByVal pBuffer As IntPtr) As Integer
		Dim status As dvpStatus
		status = DVPCamera.dvpDrawPicture(refFrame, pBuffer, m_ptr_wnd1, 0, 0)
		Return status
	End Function

    ' 数据接收回调函数
	Public Function _dvpStreamCallback2(ByVal handle As UInteger, ByVal _event As dvpStreamEvent, ByVal pContext As IntPtr, ByRef refFrame As dvpFrame, ByVal pBuffer As IntPtr) As Integer
		Dim status As dvpStatus
		status = DVPCamera.dvpDrawPicture(refFrame, pBuffer, m_ptr_wnd2, 0, 0)
		Return status
	End Function

    ' 数据接收回调函数
	Public Function _dvpStreamCallback3(ByVal handle As UInteger, ByVal _event As dvpStreamEvent, ByVal pContext As IntPtr, ByRef refFrame As dvpFrame, ByVal pBuffer As IntPtr) As Integer
		Dim status As dvpStatus
		status = DVPCamera.dvpDrawPicture(refFrame, pBuffer, m_ptr_wnd3, 0, 0)
		Return status
	End Function

	Private Sub OpenDev_0()
		Static Dim pCallBack As New DVPCamera.dvpStreamCallback(AddressOf _dvpStreamCallback0)
		Dim status As dvpStatus
		Dim strName As String

		If IsValidHandle(m_handle_0) = False Then
			strName = DevNameCombo.Text
            If (strName <> "") Then

                ' 通过枚举到并选择的FriendlyName打开指定设备
                status = DVPCamera.dvpOpenByName(strName, dvpOpenMode.OPEN_NORMAL, m_handle_0)
                If (status <> dvpStatus.DVP_STATUS_OK) Then
                    MessageBox.Show("打开失败")
				Else
					FriendlyName.Text = strName
					status = DVPCamera.dvpRegisterStreamCallback(m_handle_0, pCallBack, dvpStreamEvent.STREAM_EVENT_PROCESSED, 0)
                End If
            End If
		Else
			status = DVPCamera.dvpClose(m_handle_0)
			m_handle_0 = 0
			pictureBox.Invalidate()
		End If
		InitCtrls_0()
	End Sub

	Private Sub OpenDev_1()
		Static Dim pCallBack As New DVPCamera.dvpStreamCallback(AddressOf _dvpStreamCallback1)
		Dim status As dvpStatus
		Dim strName As String

		If IsValidHandle(m_handle_1) = False Then
			strName = DevNameCombo1.Text
			If (strName <> "") Then

				' 通过枚举到并选择的FriendlyName打开指定设备
				status = DVPCamera.dvpOpenByName(strName, dvpOpenMode.OPEN_NORMAL, m_handle_1)
				If (status <> dvpStatus.DVP_STATUS_OK) Then
					MessageBox.Show("打开失败")
				Else
					FriendlyName1.Text = strName
					status = DVPCamera.dvpRegisterStreamCallback(m_handle_1, pCallBack, dvpStreamEvent.STREAM_EVENT_PROCESSED, 0)
				End If
			End If
		Else
			status = DVPCamera.dvpClose(m_handle_1)
			m_handle_1 = 0
			pictureBox1.Invalidate()
		End If
		InitCtrls_1()
	End Sub

	Private Sub OpenDev_2()
		Static Dim pCallBack As New DVPCamera.dvpStreamCallback(AddressOf _dvpStreamCallback2)
		Dim status As dvpStatus
		Dim strName As String

		If IsValidHandle(m_handle_2) = False Then
			strName = DevNameCombo2.Text
            If (strName <> "") Then

                ' 通过枚举到并选择的FriendlyName打开指定设备
                status = DVPCamera.dvpOpenByName(strName, dvpOpenMode.OPEN_NORMAL, m_handle_2)
                If (status <> dvpStatus.DVP_STATUS_OK) Then
                    MessageBox.Show("打开失败")
				Else
					FriendlyName2.Text = strName
					status = DVPCamera.dvpRegisterStreamCallback(m_handle_2, pCallBack, dvpStreamEvent.STREAM_EVENT_PROCESSED, 0)
                End If
            End If
		Else
			status = DVPCamera.dvpClose(m_handle_2)
			m_handle_2 = 0
			pictureBox2.Invalidate()
		End If
		InitCtrls_2()
	End Sub

	Private Sub OpenDev_3()
		Static Dim pCallBack As New DVPCamera.dvpStreamCallback(AddressOf _dvpStreamCallback3)
		Dim status As dvpStatus
		Dim strName As String

		If IsValidHandle(m_handle_3) = False Then
			strName = DevNameCombo3.Text
            If (strName <> "") Then

                ' 通过枚举到并选择的FriendlyName打开指定设备
                status = DVPCamera.dvpOpenByName(strName, dvpOpenMode.OPEN_NORMAL, m_handle_3)
                If (status <> dvpStatus.DVP_STATUS_OK) Then
                    MessageBox.Show("打开失败")
				Else
					FriendlyName3.Text = strName
					status = DVPCamera.dvpRegisterStreamCallback(m_handle_3, pCallBack, dvpStreamEvent.STREAM_EVENT_PROCESSED, 0)
                End If
            End If
		Else
			status = DVPCamera.dvpClose(m_handle_3)
			m_handle_3 = 0
			pictureBox3.Invalidate()
		End If
		InitCtrls_3()
	End Sub

	Private Sub OpenDev_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles OpenDev.Click
		OpenDev_0()
	End Sub

	Private Sub OpenDev1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles OpenDev1.Click
		OpenDev_1()
	End Sub

	Private Sub OpenDev2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles OpenDev2.Click
		OpenDev_2()
	End Sub

	Private Sub OpenDev3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles OpenDev3.Click
		OpenDev_3()
	End Sub

	Private Sub StartCamera0()
		If IsValidHandle(m_handle_0) Then
			Dim state As New dvpStreamState()
            Dim status As New dvpStatus()

            ' 根据当前视频状态，执行相反的操作，实现一个按钮既能启动又能停止
			status = DVPCamera.dvpGetStreamState(m_handle_0, state)
			If (state = dvpStreamState.STATE_STARTED) Then
				status = DVPCamera.dvpStop(m_handle_0)
			Else
				status = DVPCamera.dvpStart(m_handle_0)
			End If
			InitCtrls_0()
		End If
	End Sub

	Private Sub StartCamera1()
		If IsValidHandle(m_handle_1) Then
			Dim state As New dvpStreamState()
            Dim status As New dvpStatus()

            ' 根据当前视频状态，执行相反的操作，实现一个按钮既能启动又能停止
			status = DVPCamera.dvpGetStreamState(m_handle_1, state)
			If (state = dvpStreamState.STATE_STARTED) Then
				status = DVPCamera.dvpStop(m_handle_1)
			Else
				status = DVPCamera.dvpStart(m_handle_1)
			End If
			InitCtrls_1()
		End If
	End Sub

	Private Sub StartCamera2()
		If IsValidHandle(m_handle_2) Then
			Dim state As New dvpStreamState()
            Dim status As New dvpStatus()

            ' 根据当前视频状态，执行相反的操作，实现一个按钮既能启动又能停止
			status = DVPCamera.dvpGetStreamState(m_handle_2, state)
			If (state = dvpStreamState.STATE_STARTED) Then
				status = DVPCamera.dvpStop(m_handle_2)
			Else
				status = DVPCamera.dvpStart(m_handle_2)
			End If
			InitCtrls_2()
		End If
	End Sub

	Private Sub StartCamera3()
		If IsValidHandle(m_handle_3) Then
			Dim state As New dvpStreamState()
            Dim status As New dvpStatus()

            ' 根据当前视频状态，执行相反的操作，实现一个按钮既能启动又能停止
			status = DVPCamera.dvpGetStreamState(m_handle_3, state)
			If (state = dvpStreamState.STATE_STARTED) Then
				status = DVPCamera.dvpStop(m_handle_3)
			Else
				status = DVPCamera.dvpStart(m_handle_3)
			End If
			InitCtrls_3()
		End If
	End Sub

	Private Sub StartPlay_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles StartPlay.Click
		StartCamera0()
	End Sub

	Private Sub StartPlay1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles StartPlay1.Click
		StartCamera1()
	End Sub

	Private Sub StartPlay2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles StartPlay2.Click
		StartCamera2()
	End Sub

	Private Sub StartPlay3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles StartPlay3.Click
		StartCamera3()
	End Sub

	Private Sub PropertSet_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PropertSet.Click
		If (IsValidHandle(m_handle_0)) Then
			DVPCamera.dvpShowPropertyModalDialog(m_handle_0, Me.Handle)
		End If
	End Sub

	Private Sub PropertSet1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PropertSet1.Click
		If (IsValidHandle(m_handle_1)) Then
			DVPCamera.dvpShowPropertyModalDialog(m_handle_1, Me.Handle)
		End If
	End Sub

	
	Private Sub PropertSet2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PropertSet2.Click
		If (IsValidHandle(m_handle_2)) Then
			DVPCamera.dvpShowPropertyModalDialog(m_handle_2, Me.Handle)
		End If
	End Sub

	Private Sub PropertSet3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PropertSet3.Click
		If (IsValidHandle(m_handle_3)) Then
			DVPCamera.dvpShowPropertyModalDialog(m_handle_3, Me.Handle)
		End If
	End Sub

	Private Sub SetUserID_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles SetUserID.Click
		If (IsValidHandle(m_handle_0)) Then
			Dim Length As UInteger
			Dim str As String
			Dim status As dvpStatus
			str = EditUserID.Text
            Length = str.Length

            ' 设置用户ID
			status = DVPCamera.dvpSetUserId(m_handle_0, str, Length)
			SaveBind.Enabled = True
		End If
	End Sub

	Private Sub SetUserID1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles SetUserID1.Click
		If (IsValidHandle(m_handle_1)) Then
			Dim Length As UInteger
			Dim str As String
			Dim status As dvpStatus
			str = EditUserID.Text
            Length = str.Length

            ' 设置用户ID
			status = DVPCamera.dvpSetUserId(m_handle_1, str, Length)
			SaveBind.Enabled = True
		End If
	End Sub

	Private Sub SetUserID2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles SetUserID2.Click
		If (IsValidHandle(m_handle_2)) Then
			Dim Length As UInteger
			Dim str As String
			Dim status As dvpStatus
			str = EditUserID.Text
            Length = str.Length

            ' 设置用户ID
			status = DVPCamera.dvpSetUserId(m_handle_2, str, Length)
			SaveBind.Enabled = True
		End If
	End Sub

	Private Sub SetUserID3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles SetUserID3.Click
		If (IsValidHandle(m_handle_3)) Then
			Dim Length As UInteger
			Dim str As String
			Dim status As dvpStatus
			str = EditUserID.Text
            Length = str.Length

            ' 设置用户ID
			status = DVPCamera.dvpSetUserId(m_handle_3, str, Length)
			SaveBind.Enabled = True
		End If
	End Sub

	
	Private Sub SaveBind_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles SaveBind.Click
		Dim strUserId0 As String
		strUserId0 = EditUserID.Text

		Dim strUserId1 As String
		strUserId1 = EditUserID1.Text

		Dim strUserId2 As String
		strUserId2 = EditUserID2.Text

		Dim strUserId3 As String
		strUserId3 = EditUserID3.Text

		Dim b_error_flg As Boolean
		b_error_flg = False

		If (strUserId0.Length > 0) Then
			If (strUserId1.Length > 0) Then
				If (strUserId0 = strUserId1) Then
					b_error_flg = True
				End If
			End If

			If (strUserId2.Length > 0) Then
				If (strUserId0 = strUserId2) Then
					b_error_flg = True
				End If
			End If

			If (strUserId3.Length > 0) Then
				If (strUserId0 = strUserId3) Then
					b_error_flg = True
				End If
			End If
		End If

		If (strUserId1.Length > 0) Then
			If (strUserId2.Length > 0) Then
				If (strUserId1 = strUserId2) Then
					b_error_flg = True
				End If
			End If
			If (strUserId3.Length > 0) Then
				If (strUserId1 = strUserId3) Then
					b_error_flg = True
				End If
			End If
		End If

		If (strUserId2.Length > 0) Then
			If (strUserId3.Length > 0) Then
				If (strUserId2 = strUserId3) Then
					b_error_flg = True
				End If
			End If
		End If

		If (b_error_flg) Then
			MessageBox.Show(("User id repetition"), ("Save Failed"))
			Return
		End If

        ' 如果不存在重复的“user id”则将绑定关系保存到注册表
		DVPCamera.dvpWriteProfileString(("UserId"), ("0"), strUserId0)
		DVPCamera.dvpWriteProfileString(("UserId"), ("1"), strUserId1)
		DVPCamera.dvpWriteProfileString(("UserId"), ("2"), strUserId2)
		DVPCamera.dvpWriteProfileString(("UserId"), ("3"), strUserId3)

		SaveBind.Enabled = False
	End Sub

	Private Sub LoadBind_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles LoadBind.Click

		Dim strUserId0 As String
		Dim strUserId1 As String
		Dim strUserId2 As String
		Dim strUserId3 As String

		Dim str As String
		str = ""

		strUserId0 = DVPCamera.dvpGetProfileString(("UserId"), ("0"), 0)
		strUserId1 = DVPCamera.dvpGetProfileString(("UserId"), ("1"), 0)
		strUserId2 = DVPCamera.dvpGetProfileString(("UserId"), ("2"), 0)
		strUserId3 = DVPCamera.dvpGetProfileString(("UserId"), ("3"), 0)

		Dim b_error_flg As Boolean
		b_error_flg = False
		If (strUserId0.Length > 0) Then
			If (strUserId1.Length > 0) Then
				If (strUserId0 Is strUserId1) Then
					b_error_flg = True
				End If
			End If

			If (strUserId2.Length > 0) Then
				If (strUserId0 Is strUserId2) Then
					b_error_flg = True
				End If
			End If

			If (strUserId3.Length > 0) Then
				If (strUserId0 Is strUserId3) Then
					b_error_flg = True
				End If
			End If
		End If

		If (strUserId1.Length > 0) Then
			If (strUserId2.Length > 0) Then
				If (strUserId1 Is strUserId2) Then
					b_error_flg = True
				End If
			End If

			If (strUserId3.Length > 0) Then
				If (strUserId1 Is strUserId3) Then
					b_error_flg = True
				End If
			End If
		End If

		If (strUserId2.Length > 0) Then
			If (strUserId3.Length > 0) Then
				If (strUserId2 Is strUserId3) Then
					b_error_flg = True
				End If
			End If
		End If

		If (b_error_flg) Then
			MessageBox.Show(("User id repetition"), ("Save Failed"))
			Return
		End If

        Dim status As dvpStatus

        ' 若相机已打开，则逐个关闭相机
		If (IsValidHandle(m_handle_0)) Then
			status = DVPCamera.dvpClose(m_handle_0)
			m_handle_0 = 0
		End If
		If (IsValidHandle(m_handle_1)) Then

			status = DVPCamera.dvpClose(m_handle_1)
			m_handle_1 = 0
		End If
		If (IsValidHandle(m_handle_2)) Then

			status = DVPCamera.dvpClose(m_handle_2)
			m_handle_2 = 0
		End If
		If (IsValidHandle(m_handle_3)) Then

			status = DVPCamera.dvpClose(m_handle_3)
			m_handle_3 = 0
        End If

        ' 根据用户ID打开相机
		OpenByUserId(strUserId0, m_handle_0)
		OpenByUserId(strUserId1, m_handle_1)
		OpenByUserId(strUserId2, m_handle_2)
		OpenByUserId(strUserId3, m_handle_3)

        ' 初始化相机
		InitCtrls_1()
		InitCtrls_2()
		InitCtrls_3()
		InitCtrls_0()
	End Sub


	Private Sub OpenByUserId(ByVal UserId As String, ByRef pHandle As UInteger)
		If (UserId.Length < 1) Then
			Return
		End If
		Dim str_UserId As String
		str_UserId = UserId
		Dim status As dvpStatus
		Dim info As New dvpCameraInfo()
		Dim nCameraCount As UInteger
        nCameraCount = 0

        ' 只有先刷新相机数目，才能进行后续的相机枚举
		status = DVPCamera.dvpRefresh(nCameraCount)

        For i = 0 To nCameraCount - 1

            ' 依次根据索引来枚举相机
            status = DVPCamera.dvpEnum(i, info)

            ' 对比枚举所得相机的“user id”来判断，是否为寻找对象
            If (str_UserId = info.UserID) Then

                ' 成功找到相机，再根据 FriendlyName 来打开相机，同时得到相机句柄
                status = DVPCamera.dvpOpenByName(info.FriendlyName, dvpOpenMode.OPEN_NORMAL, pHandle)
                If status = dvpStatus.DVP_STATUS_OK Then
                    Return
                End If
            Else

                ' 如果打开失败，则根据状态码获得一个相应的参考字符串
                ' 注意：此字符串，并未恒定，可能会随语言和版本而发生变化
                MessageBox.Show("打开失败")
                Return
            End If
        Next

	End Sub

End Class

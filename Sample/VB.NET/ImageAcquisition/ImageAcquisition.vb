Imports DVPCameraType
Imports DVPCameraType.DVPCamera

Public Class ImageAcquisition

	Private m_handle As UInteger
	Public m_ptr_wnd As IntPtr
	Public m_strFriendlyName As String
	Public m_strfiledir As String
	Public m_strfilepath As String
	Dim m_pThread As Threading.Thread
	Dim m_ia As ImageAcquisition
	Private Shared m_ThreadEvent As New System.Threading.AutoResetEvent(False)
	Dim m_b_thread_start As Boolean
	Dim m_uImageCount As Integer
	Private WithEvents m_Timer As New Timer()
	Private Sub ImageAcquisition_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
		m_handle = 0
		m_ptr_wnd = pictureBox.Handle
		m_strFriendlyName = ""
		
		m_ia = Me
        m_ThreadEvent.Set()         ' 设置为有信号
		m_b_thread_start = False
		m_uImageCount = 0
		ScanCamera()

		Display.Checked = True
		Form.CheckForIllegalCrossThreadCalls = False
        m_Timer.Interval = 500

        ' 是否执行System.Timers.Timer.Elapsed事件
        m_Timer.Enabled = True
		m_strfiledir = Application.StartupPath()
		EditPath.Text = m_strfiledir
		m_strfilepath = ""
	End Sub

	Public Sub theout(ByVal sender As Object, ByVal e As EventArgs) Handles m_Timer.Tick
        If (IsValidHandle(m_handle)) Then

            ' 更新帧率信息
            Dim count As New dvpFrameCount
            Dim str As String
            DVPCamera.dvpGetFrameCount(m_handle, count)
            str = m_strFriendlyName + " [" + count.uFrameCount.ToString() + " frames, " + String.Format("{0:#0.00}", count.fFrameRate) + " fps]"
            Me.Text = str
            Counts.Text = m_uImageCount.ToString()
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
        DevNameCombo.Items.Clear()
        Dim iNum As Integer
        Dim iCamCount As Integer                ' 相机数量
        Dim sDevList As New dvpCameraInfo()     ' 相机信息结构

        ' 获取连接的相机数量
        If dvpStatus.DVP_STATUS_OK = DVPCamera.dvpRefresh(iCamCount) Then

            ' 获取相机的型号等信息并添加到控件
            For iNum = 0 To iCamCount - 1
                If dvpStatus.DVP_STATUS_OK = DVPCamera.dvpEnum(iNum, sDevList) Then
                    DevNameCombo.Items.Add(sDevList.FriendlyName)
                End If
            Next

            ' 设置下拉框当前选择项
            If iCamCount > 0 Then
                DevNameCombo.SelectedIndex = 0
            End If
        End If
        InitCtrl()
    End Sub

    ' 设置控件状态
	Private Sub InitCtrl()
		Dim status As New dvpStatus()
		Dim state As New dvpStreamState()
		If IsValidHandle(m_handle) = True Then
			state = dvpStreamState.STATE_STOPED
			status = DVPCamera.dvpGetStreamState(m_handle, state)
			OpenDev.Text = "Close"
			OpenDev.Enabled = True
			StartPlay.Text = IIf(state = dvpStreamState.STATE_STARTED, "Stop", "Start")

			StartPlay.Enabled = True
            PropertSet.Enabled = True

            ' 更新示例相关功能控件
			If (state = dvpStreamState.STATE_STARTED) Then

                ' 如果采集线程还在继续，禁用一些操作，可以简化多线程同步的问题
				SaveImageCheck.Enabled = False
				Display.Enabled = False
				SelectPath.Enabled = False
				EditPath.Enabled = False
				EditWait.Enabled = False
				SoftTrigger.Enabled = False
				StartPlay.Text = "Stop"
			Else
				OpenDev.Enabled = IIf(DevNameCombo.Items.Count > 0, True, False)
				SaveImageCheck.Enabled = True
				Display.Enabled = True
				SelectPath.Enabled = True
				EditPath.Enabled = True
				OpenFolder.Enabled = True
				EditWait.Enabled = True
				SoftTrigger.Enabled = True
				StartPlay.Text = "Start"
			End If
		Else
            ' 没有设备被打开
            ' 更新基本功能控件
			OpenDev.Text = "Open"
			StartPlay.Enabled = False
			PropertSet.Enabled = False
			OpenDev.Enabled = IIf(DevNameCombo.Items.Count > 0, True, False)

            ' 更新示例相关功能的控件
			SaveImageCheck.Enabled = False
			Display.Enabled = False
			SelectPath.Enabled = False
			OpenFolder.Enabled = False
			SaveImageCheck.Enabled = False
		End If
	End Sub

    ' 打开相机
	Private Sub OpenCamera()
		Dim status As New dvpStatus()
		Dim strName As String
		strName = ""

		If IsValidHandle(m_handle) = False Then
			strName = DevNameCombo.Text
            If (strName.Length > 0) Then

                ' 通过枚举到并选择的FriendlyName打开指定设备
                status = DVPCamera.dvpOpenByName(strName, dvpOpenMode.OPEN_NORMAL, m_handle)
                If (status <> dvpStatus.DVP_STATUS_OK) Then
                    MessageBox.Show("打开失败")
                End If
            Else
                m_strFriendlyName = strName
            End If
		Else
			status = DVPCamera.dvpClose(m_handle)
			m_handle = 0
			pictureBox.Invalidate()

		End If
		InitCtrl()
	End Sub

	Private Sub StartCamera()
		Dim state As New dvpStreamState()
		Dim status As dvpStatus
        If IsValidHandle(m_handle) = True Then  ' 停止打开
            state = dvpStreamState.STATE_STOPED

            ' 根据当前视频状态，执行相反的操作，实现一个按钮既能启动又能停止

            status = DVPCamera.dvpGetStreamState(m_handle, state)
            If (state <> dvpStreamState.STATE_STOPED) Then
                status = DVPCamera.dvpStop(m_handle)
                If m_pThread.ThreadState <> System.Threading.ThreadState.Aborted And m_pThread.ThreadState <> System.Threading.ThreadState.Stopped Then '线程还在运行

                    ' 有信号表示停止
                    m_ThreadEvent.Set()
                    While m_pThread.ThreadState = ThreadState.Running
                        System.Threading.Thread.Sleep(100)
                    End While
                End If
            Else
                ' 在dvpStart之前先设置为触发模式
                Dim flg As Boolean
                flg = False
                flg = IIf(SoftTrigger.Checked, True, False)
                status = DVPCamera.dvpSetTriggerState(m_handle, flg)
                If (status <> dvpStatus.DVP_STATUS_OK) Then

                    ' 此时要确认相机是否支持触发功能
                    MessageBox.Show("设置触发模式失败")
                End If

                status = DVPCamera.dvpStart(m_handle)
                If (status <> dvpStatus.DVP_STATUS_OK) Then
                    MessageBox.Show("启动失败")
                Else
                    ' 重置线程事件,设置无信号，表示线程一直运行
                    m_ThreadEvent.Reset()

                    ' 创建图像采集线程
                    m_pThread = New Threading.Thread(AddressOf ImageThread)
                    m_pThread.Start()
                    m_b_thread_start = True
                End If
            End If
            InitCtrl()
        End If
	End Sub

    ' 图像采集线程函数
	Private Sub ImageThread()
		Dim status As dvpStatus
        Dim m_systm As New DateTime()

        ' 等待事件超时时间
        Dim time_out As Integer
		time_out = 40

		If EditWait.Text.Length > 0 Then
			time_out = CUInt(EditWait.Text)
		End If

		If (time_out > 40) Then
			time_out = 40
		End If

		If (time_out < 1) Then
			time_out = 40
		End If

		While m_ThreadEvent.WaitOne(time_out) = False
			Dim pBuffer As New IntPtr()
			pBuffer = 0
			Dim frame As New dvpFrame()

			If (SoftTrigger.Checked) Then
				status = DVPCamera.dvpTriggerFire(m_handle)
                If (status <> dvpStatus.DVP_STATUS_OK) Then

                    ' 有可能是触发信号间隔太过密集所导致
                    Console.WriteLine("dvpTriggerFire操作失败, status:%d\r\n", status)
                End If
			End If

            ' 从视频流中抓取一帧图像，超时时间通常不应小于曝光时间
			status = DVPCamera.dvpGetFrame(m_handle, frame, pBuffer, 4000)
			If (status <> dvpStatus.DVP_STATUS_OK) Then
				Console.WriteLine("dvpGetFrame操作失败, status:%d\r\n", status)
				Continue While
            End If

            ' 如果需要保存图像
            If (SaveImageCheck.Checked) Then

                ' 以系统时间为文件名保存新的bmp图像
                Dim now As New DateTime()
				now = DateTime.Now
				Dim strfilepath As String

				strfilepath = m_strfiledir + "\\" + now.ToString("yyyy-MM-dd") + " " + now.TimeOfDay.ToString().Replace(":", "-").Replace(".", "-") + ".bmp"
				status = DVPCamera.dvpSavePicture(frame, pBuffer, strfilepath, 100)
				m_strfilepath = strfilepath
				m_uImageCount = m_uImageCount + 1
            End If

            ' 如果需要，则显示图像到预览窗口
			If (Display.Checked) Then
				status = DVPCamera.dvpDrawPicture(frame, pBuffer, m_ia.pictureBox.Handle, 0, 0)
			End If
		End While
		m_pThread.Abort()
		m_b_thread_start = False
	End Sub

    ' 设置参数
	Private Sub SetParam()
		If IsValidHandle(m_handle) = True Then
			Dim status As dvpStatus
            status = DVPCamera.dvpShowPropertyModalDialog(m_handle, Me.Handle())

            ' 此时一些配置可能发生改变，将同步到界面
			InitCtrl()
		End If
	End Sub

	Private Sub ScanDev_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ScanDev.Click
		ScanCamera()
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

	Private Sub SelectPath_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles SelectPath.Click
		Dim dlg As New FolderBrowserDialog()
		dlg.SelectedPath = m_strfiledir
		dlg.ShowNewFolderButton = True
		If (dlg.ShowDialog() = DialogResult.OK) Then
			m_strfiledir = dlg.SelectedPath
			EditPath.Text = m_strfiledir
		End If
	End Sub

	Private Sub OpenFolder_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles OpenFolder.Click
		If m_strfiledir.Length > 0 Then
			'ShellExecute(0, "Open", m_strfilepath, "", "", 1)
			'Shell(m_strfilepath, AppWinStyle.NormalNoFocus)
			System.Diagnostics.Process.Start(m_strfiledir)
		End If
	End Sub

	Private Sub ShellExecute(ByVal m_handle As UInteger, ByVal p2 As String, ByVal m_strfilepath As String, ByVal p4 As String, ByVal p5 As String, ByVal p6 As Integer)
		Throw New NotImplementedException
	End Sub

	Private Sub ImageAcquisition_FormClosing(ByVal sender As System.Object, ByVal e As System.Windows.Forms.FormClosingEventArgs) Handles MyBase.FormClosing
		If (IsValidHandle(m_handle)) Then
			If (m_b_thread_start) Then
				m_ThreadEvent.Set()
				While (m_pThread.ThreadState = ThreadState.Running)
					System.Threading.Thread.Sleep(100)
				End While
			End If
			DVPCamera.dvpClose(m_handle)
			m_handle = 0
			pictureBox.Invalidate()
		End If
	End Sub
End Class

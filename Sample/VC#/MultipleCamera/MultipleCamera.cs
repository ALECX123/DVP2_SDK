using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DVPCameraType;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace MultipleCamera
{
    public partial class MultipleCamera : Form
    {
        public int m_n_dev_count_0;
        uint m_handle_0 = 0;

        public int m_n_dev_count_1;
        uint m_handle_1 = 0;

        public int m_n_dev_count_2;
        uint m_handle_2 = 0;

        public int m_n_dev_count_3;
        uint m_handle_3 = 0;

        public static IntPtr m_ptr_wnd0 = new IntPtr();
        public static IntPtr m_ptr0 = new IntPtr();
        public static IntPtr m_ptr_wnd1 = new IntPtr();
        public static IntPtr m_ptr1 = new IntPtr();
        public static IntPtr m_ptr_wnd2 = new IntPtr();
        public static IntPtr m_ptr2 = new IntPtr();
        public static IntPtr m_ptr_wnd3 = new IntPtr();
        public static IntPtr m_ptr3 = new IntPtr();

        public MultipleCamera()
        {
            InitializeComponent();

            m_ptr_wnd0 = pictureBox.Handle;
            m_ptr_wnd1 = pictureBox1.Handle;
            m_ptr_wnd2 = pictureBox2.Handle;
            m_ptr_wnd3 = pictureBox3.Handle;

            InitDevList_0();
            InitDevList_1();
            InitDevList_2();
            InitDevList_3();
        }

        public void InitDevList_0()
        {
            dvpStatus status;
            uint i, n = 0;
            dvpCameraInfo dev_info = new dvpCameraInfo();

            // 此时，n为成功枚举到的相机数量，将添加到下拉列表中，下拉列表中的内容为每个相机的FriendlyName
            DevNameCombo.Items.Clear();

            // 获得当前能连接的相机数量
            status = DVPCamera.dvpRefresh(ref n);
            m_n_dev_count_0 = (int)n;
            if (status == dvpStatus.DVP_STATUS_OK)
            {
                for (i = 0; i < n; i++)
                {
                    // 逐个枚举出每个相机的信息
                    status = DVPCamera.dvpEnum(i, ref dev_info);

                    if (status == dvpStatus.DVP_STATUS_OK)
                    {
                        // 界面使用的是UNICODE，枚举的设备信息为ANSI字符串，需要将ANSI转UNICODE
                        int item = DevNameCombo.Items.Add(dev_info.FriendlyName);
                        if (item == 0)
                        {
                            DevNameCombo.SelectedIndex = item;
                        }
                    }
                }
            }
            if (n == 0)
            {
                OpenDev.Enabled = false;
            }
            else
            {
                OpenDev.Enabled = true;
            }
            InitCtrls_0();

        }

        public void InitDevList_1()
        {
            dvpStatus status;
            uint i, n = 0;
            dvpCameraInfo dev_info = new dvpCameraInfo();

            // 此时，n为成功枚举到的相机数量，将添加到下拉列表中，下拉列表中的内容为每个相机的FriendlyName
            DevNameCombo1.Items.Clear();

            // 获得当前能连接的相机数量
            status = DVPCamera.dvpRefresh(ref n);
            m_n_dev_count_1 = (int)n;
            if (status == dvpStatus.DVP_STATUS_OK)
            {
                for (i = 0; i < n; i++)
                {
                    // 逐个枚举出每个相机的信息
                    status = DVPCamera.dvpEnum(i, ref dev_info);

                    if (status == dvpStatus.DVP_STATUS_OK)
                    {
                        // 界面使用的是UNICODE，枚举的设备信息为ANSI字符串，需要将ANSI转UNICODE
                        int item = DevNameCombo1.Items.Add(dev_info.FriendlyName);
                        if (item == 0)
                        {
                            DevNameCombo1.SelectedIndex = item;
                        }
                    }
                }
            }
            if (n == 0)
            {
                OpenDev1.Enabled = false;
            }
            else
            {
                OpenDev1.Enabled = true;
            }
            InitCtrls_1();
        }

        public void InitDevList_2()
        {
            dvpStatus status;
            uint i, n = 0;
            dvpCameraInfo dev_info = new dvpCameraInfo();

            // 此时，n为成功枚举到的相机数量，将添加到下拉列表中，下拉列表中的内容为每个相机的FriendlyName
            DevNameCombo2.Items.Clear();

            // 获得当前能连接的相机数量
            status = DVPCamera.dvpRefresh(ref n);
            m_n_dev_count_2 = (int)n;
            if (status == dvpStatus.DVP_STATUS_OK)
            {
                for (i = 0; i < n; i++)
                {
                    // 逐个枚举出每个相机的信息
                    status = DVPCamera.dvpEnum(i, ref dev_info);

                    if (status == dvpStatus.DVP_STATUS_OK)
                    {
                        // 界面使用的是UNICODE，枚举的设备信息为ANSI字符串，需要将ANSI转UNICODE
                        int item = DevNameCombo2.Items.Add(dev_info.FriendlyName);
                        if (item == 0)
                        {
                            DevNameCombo2.SelectedIndex = item;
                        }
                    }
                }
            }
            if (n == 0)
            {
                OpenDev2.Enabled = false;
            }
            else
            {
                OpenDev2.Enabled = true;
            }
            InitCtrls_2();
        }

        public void InitDevList_3()
        {
            dvpStatus status;
            uint i, n = 0;
            dvpCameraInfo dev_info = new dvpCameraInfo();

            // 此时，n为成功枚举到的相机数量，将添加到下拉列表中，下拉列表中的内容为每个相机的FriendlyName
            DevNameCombo3.Items.Clear();

            // 获得当前能连接的相机数量
            status = DVPCamera.dvpRefresh(ref n);
            m_n_dev_count_3 = (int)n;
            if (status == dvpStatus.DVP_STATUS_OK)
            {
                for (i = 0; i < n; i++)
                {
                    // 逐个枚举出每个相机的信息
                    status = DVPCamera.dvpEnum(i, ref dev_info);

                    if (status == dvpStatus.DVP_STATUS_OK)
                    {
                        // 界面使用的是UNICODE，枚举的设备信息为ANSI字符串，需要将ANSI转UNICODE
                        int item = DevNameCombo3.Items.Add(dev_info.FriendlyName);
                        if (item == 0)
                        {
                            DevNameCombo3.SelectedIndex = item;
                        }
                    }
                }
            }
            if (n == 0)
            {
                OpenDev3.Enabled = false;
            }
            else
            {
                OpenDev3.Enabled = true;
            }
            InitCtrls_3();
        }

        public bool IsValidHandle(uint handle)
        {
            bool bValidHandle = false;
            dvpStatus status = DVPCamera.dvpIsValid(handle, ref bValidHandle);
            return bValidHandle;
        }

        // 初始化第2台相机
        public void InitCtrls_0()
        {
	        dvpStatus status;
	        if (IsValidHandle(m_handle_0))
	        {
		        // 此时已经有设备被打开
		        dvpCameraInfo info = new dvpCameraInfo();
		        dvpStreamState state = new dvpStreamState();

                status = DVPCamera.dvpGetStreamState(m_handle_0, ref state);
                // 设置基本功能控件
                OpenDev.Text = "Close";
                StartPlay.Text = (state == dvpStreamState.STATE_STARTED ? ("Stop") : ("Start"));
                StartPlay.Enabled = true;
		       
		        // 设置本示例相关功能控件的使能状态
                PropertSet.Enabled = true;
                EditUserID.Enabled = true;
                SetUserID.Enabled = true;
		        
		        // 获取相机信息
                DVPCamera.dvpGetCameraInfo(m_handle_0, ref info);
                EditUserID.Text = info.UserID;
	        }
	        else
	        {
		        // 此时还没有设备被打开
		        // 设置基本功能控件
                OpenDev.Text = "Open";
		        FriendlyName.Text = "Friendly Name";
                StartPlay.Text = "Start";
                StartPlay.Enabled = false;

		        // 设置本示例相关功能控件的使能状态
                EditUserID.Text ="";
                PropertSet.Enabled = false;
                SetUserID.Enabled = false;
	        }
        }

        public void InitCtrls_3()
        {
            dvpStatus status;
            if (IsValidHandle(m_handle_3))
            {
                // 此时已经有设备被打开
                dvpCameraInfo info = new dvpCameraInfo();
                dvpStreamState state = new dvpStreamState();

                status = DVPCamera.dvpGetStreamState(m_handle_3, ref state);
                // 设置基本功能控件
                OpenDev3.Text = "Close";
                StartPlay3.Text = (state == dvpStreamState.STATE_STARTED ? ("Stop") : ("Start"));
                StartPlay3.Enabled = true;

                // 设置本示例相关功能控件的使能状态
                PropertSet3.Enabled = true;
                EditUserID3.Enabled = true;
                SetUserID3.Enabled = true;

                // 获取相机信息
                DVPCamera.dvpGetCameraInfo(m_handle_3, ref info);
                EditUserID3.Text = info.UserID;
            }
            else
            {
                // 此时还没有设备被打开
                // 设置基本功能控件
                OpenDev3.Text = "Open";
                FriendlyName3.Text = "Friendly Name";
                StartPlay3.Text = "Start";
                StartPlay3.Enabled = false;

                // 设置本示例相关功能控件的使能状态
                EditUserID3.Text = "";
                PropertSet3.Enabled = false;
                SetUserID3.Enabled = false;
            }
        }

        public void InitCtrls_1()
        {
            dvpStatus status;
            if (IsValidHandle(m_handle_1))
            {
                // 此时已经有设备被打开
                dvpCameraInfo info = new dvpCameraInfo();
                dvpStreamState state = new dvpStreamState();

                status = DVPCamera.dvpGetStreamState(m_handle_1, ref state);

                // 设置基本功能控件
                OpenDev1.Text = "Close";
                StartPlay1.Text = (state == dvpStreamState.STATE_STARTED ? ("Stop") : ("Start"));
                StartPlay1.Enabled = true;

                // 设置本示例相关功能控件的使能状态
                PropertSet1.Enabled = true;
                EditUserID1.Enabled = true;
                SetUserID1.Enabled = true;

                // 获取相机信息
                DVPCamera.dvpGetCameraInfo(m_handle_1, ref info);
                EditUserID1.Text = info.UserID;
            }
            else
            {
                // 此时还没有设备被打开
                // 设置基本功能控件
                OpenDev1.Text = "Open";
                FriendlyName1.Text = "Friendly Name";
                StartPlay1.Text = "Start";
                StartPlay1.Enabled = false;

                // 设置本示例相关功能控件的使能状态
                EditUserID1.Text = "";
                PropertSet1.Enabled = false;
                SetUserID1.Enabled = false;
            }
        }

        public void InitCtrls_2()
        {
            dvpStatus status;
            if (IsValidHandle(m_handle_2))
            {
                // 此时已经有设备被打开
                dvpCameraInfo info = new dvpCameraInfo();
                dvpStreamState state = new dvpStreamState();

                status = DVPCamera.dvpGetStreamState(m_handle_2, ref state);
                // 设置基本功能控件
                OpenDev2.Text = "Close";
                StartPlay2.Text = (state == dvpStreamState.STATE_STARTED ? ("Stop") : ("Start"));
                StartPlay2.Enabled = true;

                // 设置本示例相关功能控件的使能状态
                PropertSet2.Enabled = true;
                EditUserID2.Enabled = true;
                SetUserID2.Enabled = true;

                // 获取相机信息
                DVPCamera.dvpGetCameraInfo(m_handle_2, ref info);
                EditUserID2.Text = info.UserID;
            }
            else
            {
                // 此时还没有设备被打开
                // 设置基本功能控件
                OpenDev2.Text = "Open";
                FriendlyName2.Text = "Friendly Name";
                StartPlay2.Text = "Start";
                StartPlay2.Enabled = false;

                // 设置本示例相关功能控件的使能状态
                EditUserID2.Text = "";
                PropertSet2.Enabled = false;
                SetUserID2.Enabled = false;
            }
        }

        private void ScanDev_Click(object sender, EventArgs e)
        {
            InitDevList_0();
        }

        private void ScanDev1_Click(object sender, EventArgs e)
        {
            InitDevList_1();
        }

        private void ScanDev2_Click(object sender, EventArgs e)
        {
            InitDevList_2();
        }

        private void ScanDev3_Click(object sender, EventArgs e)
        {
            InitDevList_3();
        }

        private DVPCamera.dvpStreamCallback _proc0;
        private DVPCamera.dvpStreamCallback _proc1;
        private DVPCamera.dvpStreamCallback _proc2;
        private DVPCamera.dvpStreamCallback _proc3;

        // 数据接收回调函数
        public static int _dvpStreamCallback0(/*dvpHandle*/uint handle, dvpStreamEvent _event, /*void **/IntPtr pContext, ref dvpFrame refFrame, /*void **/IntPtr pBuffer)
        {
            // 刷新显示
            dvpStatus s = DVPCamera.dvpDrawPicture(ref refFrame, pBuffer, m_ptr_wnd0, m_ptr0, m_ptr0);
            return 1;
        }
        public static int _dvpStreamCallback1(/*dvpHandle*/uint handle, dvpStreamEvent _event, /*void **/IntPtr pContext, ref dvpFrame refFrame, /*void **/IntPtr pBuffer)
        {
            // 刷新显示
            dvpStatus s = DVPCamera.dvpDrawPicture(ref refFrame, pBuffer, m_ptr_wnd1, m_ptr1, m_ptr1);
            return 1;
        }
        public static int _dvpStreamCallback2(/*dvpHandle*/uint handle, dvpStreamEvent _event, /*void **/IntPtr pContext, ref dvpFrame refFrame, /*void **/IntPtr pBuffer)
        {
            // 刷新显示
            dvpStatus s = DVPCamera.dvpDrawPicture(ref refFrame, pBuffer, m_ptr_wnd2, m_ptr2, m_ptr2);
            return 1;
        }
        public static int _dvpStreamCallback3(/*dvpHandle*/uint handle, dvpStreamEvent _event, /*void **/IntPtr pContext, ref dvpFrame refFrame, /*void **/IntPtr pBuffer)
        {
            // 刷新显示
            dvpStatus s = DVPCamera.dvpDrawPicture(ref refFrame, pBuffer, m_ptr_wnd3, m_ptr3, m_ptr3);
            return 1;
        }

        private void OpenDev_Click(object sender, EventArgs e)
        {
            dvpStatus status;
            string strName;

            if (!IsValidHandle(m_handle_0))
            {
                strName = DevNameCombo.Text;
                if (strName != "")
                {
                    // 通过枚举到并选择的FriendlyName打开指定设备
                    status = DVPCamera.dvpOpenByName(strName, dvpOpenMode.OPEN_NORMAL, ref m_handle_0);
                    if (status != dvpStatus.DVP_STATUS_OK)
                    {
                        MessageBox.Show("打开失败");
                    }
                    else
                    {
                        // 如果需要图像显示，可以注册回调函数，在回调函数中完成绘图操作
                        // 注意：回调函数中执行的绘图操作，可能会对dvpGetFrame接口获取的图像数据造成延时
						FriendlyName.Text = strName;
                        _proc0 = _dvpStreamCallback0;
                        using (Process curProcess = Process.GetCurrentProcess())
                        using (ProcessModule curModule = curProcess.MainModule)
                        {
                            dvpStatus s = DVPCamera.dvpRegisterStreamCallback(m_handle_0, _proc0, dvpStreamEvent.STREAM_EVENT_PROCESSED, m_ptr0);
                        }
                        
                    }
                }
            }
            else
            {
                status = DVPCamera.dvpClose(m_handle_0);
                m_handle_0 = 0;
				pictureBox.Invalidate();
            }
            InitCtrls_0();
        }

        private void OpenDev1_Click(object sender, EventArgs e)
        {
            dvpStatus status;
            string strName;

            if (!IsValidHandle(m_handle_1))
            {
                strName = DevNameCombo1.Text;
                if (strName != "")
                {
                    // 通过枚举到并选择的FriendlyName打开指定设备
                    status = DVPCamera.dvpOpenByName(strName, dvpOpenMode.OPEN_NORMAL, ref m_handle_1);
                    if (status != dvpStatus.DVP_STATUS_OK)
                    {
                        MessageBox.Show("打开失败");
                    }
                    else
                    {
						FriendlyName1.Text = strName;
                        // 如果需要图像显示，可以注册回调函数，在回调函数中完成绘图操作
                        // 注意：回调函数中执行的绘图操作，可能会对dvpGetFrame接口获取的图像数据造成延时
                        _proc1 = _dvpStreamCallback1;
                        using (Process curProcess = Process.GetCurrentProcess())
                        using (ProcessModule curModule = curProcess.MainModule)
                        {
                            dvpStatus s = DVPCamera.dvpRegisterStreamCallback(m_handle_1, _proc1, dvpStreamEvent.STREAM_EVENT_PROCESSED, m_ptr1);
                        }
                    }
                }
            }

            else
            {
                status = DVPCamera.dvpClose(m_handle_1);
				pictureBox1.Invalidate();
                m_handle_1 = 0;
            }
            InitCtrls_1();
        }

        private void OpenDev2_Click(object sender, EventArgs e)
        {
            dvpStatus status;
            string strName;

            if (!IsValidHandle(m_handle_2))
            {
                strName = DevNameCombo2.Text;
                if (strName != "")
                {
                    // 通过枚举到并选择的FriendlyName打开指定设备
                    status = DVPCamera.dvpOpenByName(strName, dvpOpenMode.OPEN_NORMAL, ref m_handle_2);
                    if (status != dvpStatus.DVP_STATUS_OK)
                    {
                        MessageBox.Show("打开失败");
                    }
                    else
                    {
						FriendlyName2.Text = strName;
                        // 如果需要图像显示，可以注册回调函数，在回调函数中完成绘图操作
                        // 注意：回调函数中执行的绘图操作，可能会对dvpGetFrame接口获取的图像数据造成延时
                        _proc2 = _dvpStreamCallback2;
                        using (Process curProcess = Process.GetCurrentProcess())
                        using (ProcessModule curModule = curProcess.MainModule)
                        {
                            dvpStatus s = DVPCamera.dvpRegisterStreamCallback(m_handle_2, _proc2, dvpStreamEvent.STREAM_EVENT_PROCESSED, m_ptr2);
                        }
                    }
                }
            }

            else
            {
                status = DVPCamera.dvpClose(m_handle_2);
                m_handle_2 = 0;
				pictureBox2.Invalidate();
            }
            InitCtrls_2();
        }

        private void OpenDev3_Click(object sender, EventArgs e)
        {
            dvpStatus status;
            string strName;

            if (!IsValidHandle(m_handle_3))
            {
                strName = DevNameCombo3.Text;
                if (strName != "")
                {
                    // 通过枚举到并选择的FriendlyName打开指定设备
                    status = DVPCamera.dvpOpenByName(strName, dvpOpenMode.OPEN_NORMAL, ref m_handle_3);
                    if (status != dvpStatus.DVP_STATUS_OK)
                    {
                        MessageBox.Show("打开失败");
                    }
                    else
                    {
						FriendlyName3.Text = strName;
                        // 如果需要图像显示，可以注册回调函数，在回调函数中完成绘图操作
                        // 注意：回调函数中执行的绘图操作，可能会对dvpGetFrame接口获取的图像数据造成延时
                        _proc3 = _dvpStreamCallback3;
                        using (Process curProcess = Process.GetCurrentProcess())
                        using (ProcessModule curModule = curProcess.MainModule)
                        {
                            dvpStatus s = DVPCamera.dvpRegisterStreamCallback(m_handle_3, _proc3, dvpStreamEvent.STREAM_EVENT_PROCESSED, m_ptr3);
                        }
                    }
                }
            }

            else
            {
                status = DVPCamera.dvpClose(m_handle_3);
                m_handle_3 = 0;
				pictureBox3.Invalidate();
            }
            InitCtrls_3();
        }

        private void StartPlay_Click(object sender, EventArgs e)
        {
            if (IsValidHandle(m_handle_0))
            {
                dvpStreamState state = new dvpStreamState();
                dvpStatus status = new dvpStatus();

                // 根据当前视频状态，执行相反的操作，实现一个按钮既能启动又能停止
                status = DVPCamera.dvpGetStreamState(m_handle_0, ref state);

                if (state == dvpStreamState.STATE_STARTED)
                {
                    status = DVPCamera.dvpStop(m_handle_0);
                }
                else
                {
                    status = DVPCamera.dvpStart(m_handle_0);
                }

                InitCtrls_0();
            }
        }

        private void StartPlay1_Click(object sender, EventArgs e)
        {
            if (IsValidHandle(m_handle_1))
            {
                dvpStreamState state = new dvpStreamState();
                dvpStatus status = new dvpStatus();

                // 根据当前视频状态，执行相反的操作，实现一个按钮既能启动又能停止
                status = DVPCamera.dvpGetStreamState(m_handle_1, ref state);

                if (state == dvpStreamState.STATE_STARTED)
                {
                    status = DVPCamera.dvpStop(m_handle_1);
                }
                else
                {
                    status = DVPCamera.dvpStart(m_handle_1);
                }

                InitCtrls_1();
            }
        }

        private void StartPlay2_Click(object sender, EventArgs e)
        {
            if (IsValidHandle(m_handle_2))
            {
                dvpStreamState state = new dvpStreamState();
                dvpStatus status = new dvpStatus();

                // 根据当前视频状态，执行相反的操作，实现一个按钮既能启动又能停止
                status = DVPCamera.dvpGetStreamState(m_handle_2, ref state);

                if (state == dvpStreamState.STATE_STARTED)
                {
                    status = DVPCamera.dvpStop(m_handle_2);
                }
                else
                {
                    status = DVPCamera.dvpStart(m_handle_2);
                }

                InitCtrls_2();
            }
        }

        private void StartPlay3_Click(object sender, EventArgs e)
        {
            if (IsValidHandle(m_handle_3))
            {
                dvpStreamState state = new dvpStreamState();
                dvpStatus status = new dvpStatus();

                // 根据当前视频状态，执行相反的操作，实现一个按钮既能启动又能停止
                status = DVPCamera.dvpGetStreamState(m_handle_3, ref state);

                if (state == dvpStreamState.STATE_STARTED)
                {
                    status = DVPCamera.dvpStop(m_handle_3);
                }
                else
                {
                    status = DVPCamera.dvpStart(m_handle_3);
                }

                InitCtrls_3();
            }
        }

        private void PropertSet_Click(object sender, EventArgs e)
        {
            if (IsValidHandle(m_handle_0))
            {
                dvpStatus status = DVPCamera.dvpShowPropertyModalDialog(m_handle_0, this.Handle);
            }
        }

        private void PropertSet1_Click(object sender, EventArgs e)
        {
            if (IsValidHandle(m_handle_1))
            {
                dvpStatus status = DVPCamera.dvpShowPropertyModalDialog(m_handle_1, this.Handle);
            }
        }

        private void PropertSet2_Click(object sender, EventArgs e)
        {
            if (IsValidHandle(m_handle_2))
            {
                dvpStatus status = DVPCamera.dvpShowPropertyModalDialog(m_handle_2, this.Handle);
            }
        }

        private void PropertSet3_Click(object sender, EventArgs e)
        {
            if (IsValidHandle(m_handle_3))
            {
                dvpStatus status = DVPCamera.dvpShowPropertyModalDialog(m_handle_3, this.Handle);
            }
        }

        private void SetUserID_Click_1(object sender, EventArgs e)
        {
            if (IsValidHandle(m_handle_0))
            {
                string str;
                str = EditUserID.Text;
                uint Length = (uint)str.Length;

                // 设置用户ID
                dvpStatus status = DVPCamera.dvpSetUserId(m_handle_0, str, ref Length);
                SaveBind.Enabled = true;
            }
        }

        private void SetUserID1_Click(object sender, EventArgs e)
        {
            if (IsValidHandle(m_handle_1))
            {
                string str;
                str = EditUserID1.Text;
                uint Length = (uint)str.Length;

                // 设置用户ID
                dvpStatus status = DVPCamera.dvpSetUserId(m_handle_1, str, ref Length);
                SaveBind.Enabled = true;
            }
        }

        private void SetUserID2_Click(object sender, EventArgs e)
        {
            if (IsValidHandle(m_handle_2))
            {
                string str;
                str = EditUserID2.Text;
                uint Length = (uint)str.Length;

                // 设置用户ID
                dvpStatus status = DVPCamera.dvpSetUserId(m_handle_2, str, ref Length);
                SaveBind.Enabled = true;
            }
        }

        private void SetUserID3_Click(object sender, EventArgs e)
        {
            if (IsValidHandle(m_handle_3))
            {
                string str;
                str = EditUserID3.Text;
                uint Length = (uint)str.Length;

                // 设置用户ID
                dvpStatus status = DVPCamera.dvpSetUserId(m_handle_3, str, ref Length);
                SaveBind.Enabled = true;
            }
        }

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern int WriteProfileString(string lpszSection, string lpszKeyName, string lpszString);
        [DllImport("kernel32")]
        private static extern bool GetProfileString(string lpApplicationName, string lpKeyName, string lpDefault, StringBuilder lpReturnedString, int nSize);

        private void SaveBind_Click(object sender, EventArgs e)
        {
            string strUserId0 = EditUserID.Text;
            string strUserId1 = EditUserID1.Text;
            string strUserId2 = EditUserID2.Text;
            string strUserId3 = EditUserID3.Text;
            bool b_error_flg = false;

            if ( strUserId0.Length > 0)
            {
                if (strUserId1.Length > 0)
                {
                    if (strUserId0 == strUserId1)
                    {
                        b_error_flg = true;
                    }
                }

                if (strUserId2.Length > 0)
                {
                    if (strUserId0 == strUserId2)
                    {
                        b_error_flg = true;
                    }
                }

                if (strUserId3.Length > 0)
                {
                    if (strUserId0 == strUserId3)
                    {
                        b_error_flg = true;
                    }
                }
            }

            if (strUserId1.Length > 0)
            {
                
                if (strUserId2.Length > 0)
                {
                    if (strUserId1 == strUserId2)
                    {
                        b_error_flg = true;
                    }
                }

                if (strUserId3.Length > 0)
                {
                    if (strUserId1 == strUserId3)
                    {
                        b_error_flg = true;
                    }
                }
            }

            if (strUserId2.Length > 0)
            {

                if (strUserId3.Length > 0)
                {
                    if (strUserId2 == strUserId3)
                    {
                        b_error_flg = true;
                    }
                }
            }

            if (b_error_flg)
            {
                MessageBox.Show(("User id repetition"), ("Save Failed"));
                return;
            }

            // 如果不存在重复的“user id”则将绑定关系保存到注册表
            WriteProfileString(("UserId"), ("0"), strUserId0);
            WriteProfileString(("UserId"), ("1"), strUserId1);
            WriteProfileString(("UserId"), ("2"), strUserId2);
            WriteProfileString(("UserId"), ("3"), strUserId3);
            SaveBind.Enabled = false;

        }

        private void LoadBind_Click(object sender, EventArgs e)
        {
            StringBuilder strUserId0 = new StringBuilder(256);
            StringBuilder strUserId1 = new StringBuilder(256);
            StringBuilder strUserId2 = new StringBuilder(256);
            StringBuilder strUserId3 = new StringBuilder(256);

            string str = "";
            GetProfileString(("UserId"), ("0"), str, strUserId0, 256);
            GetProfileString(("UserId"), ("1"), str, strUserId1, 256);
            GetProfileString(("UserId"), ("2"), str, strUserId2, 256);
            GetProfileString(("UserId"), ("3"), str, strUserId3, 256);

            bool b_error_flg = false;

            if (strUserId0.Length > 0)
            {
                if (strUserId1.Length > 0)
                {
                    if (strUserId0 == strUserId1)
                    {
                        b_error_flg = true;
                    }
                }

                if (strUserId2.Length > 0)
                {
                    if (strUserId0 == strUserId2)
                    {
                        b_error_flg = true;
                    }
                }

                if (strUserId3.Length > 0)
                {
                    if (strUserId0 == strUserId3)
                    {
                        b_error_flg = true;
                    }
                }
            }

            if (strUserId1.Length > 0)
            {

                if (strUserId2.Length > 0)
                {
                    if (strUserId1 == strUserId2)
                    {
                        b_error_flg = true;
                    }
                }

                if (strUserId3.Length > 0)
                {
                    if (strUserId1 == strUserId3)
                    {
                        b_error_flg = true;
                    }
                }
            }

            if (strUserId2.Length > 0)
            {

                if (strUserId3.Length > 0)
                {
                    if (strUserId2 == strUserId3)
                    {
                        b_error_flg = true;
                    }
                }
            }

            if (b_error_flg)
            {
                MessageBox.Show(("User id repetition"), ("Save Failed"));
                return;
            }

            // 若相机已打开，则逐个关闭相机
            if (IsValidHandle(m_handle_0))
            {
                dvpStatus status = DVPCamera.dvpClose(m_handle_0);
                m_handle_0 = 0;
            }
            if (IsValidHandle(m_handle_1))
            {
                dvpStatus status = DVPCamera.dvpClose(m_handle_1);
                m_handle_1 = 0;
            }
            if (IsValidHandle(m_handle_2))
            {
                dvpStatus status = DVPCamera.dvpClose(m_handle_2);
                m_handle_2 = 0;
            }
            if (IsValidHandle(m_handle_3))
            {
                dvpStatus status = DVPCamera.dvpClose(m_handle_3);
                m_handle_3 = 0;
            }

            // 根据用户ID打开相机
            OpenByUserId(strUserId0, ref m_handle_0);
            OpenByUserId(strUserId1, ref m_handle_1);
            OpenByUserId(strUserId2, ref m_handle_2);
            OpenByUserId(strUserId3, ref m_handle_3);

            // 初始化相机
            InitCtrls_1();
            InitCtrls_2();
            InitCtrls_3();
            InitCtrls_0();
        }

        public bool OpenByUserId(StringBuilder UserId, ref uint pHandle)
        {
            if (UserId.Length < 1)
	        {
		        return false;
	        }
            string str_UserId = string.Format("%s", UserId);
           
            dvpStatus status = new dvpStatus(); ;
	        dvpCameraInfo info = new dvpCameraInfo();
	        uint nCameraCount = 0;

	        // 只有先刷新相机数目，才能进行后续的相机枚举
            status = DVPCamera.dvpRefresh(ref nCameraCount);
	        
	        for (uint i = 0; i < nCameraCount; i++)
	        {
		        // 依次根据索引来枚举相机
                status = DVPCamera.dvpEnum(i, ref info);
		       
		        // 对比枚举所得相机的“user id”来判断，是否为寻找对象
                if (str_UserId == info.UserID)
		        {
			        // 成功找到相机，再根据 FriendlyName 来打开相机，同时得到相机句柄
                    status = DVPCamera.dvpOpenByName(info.FriendlyName, dvpOpenMode.OPEN_NORMAL, ref pHandle);
                    if (status == dvpStatus.DVP_STATUS_OK)
			        {
				        return true;
			        }
			        else
			        {
				        // 如果打开失败，则根据状态码获得一个相应的参考字符串
				        // 注意：此字符串，并未恒定，可能会随语言和版本而发生变化
				        MessageBox.Show("打开失败");
				        return false;
			        }

		        }
	        }
            return false;
        }

        private void MultipleCamera_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (IsValidHandle(m_handle_0))
            {
                DVPCamera.dvpClose(m_handle_0);
                m_handle_0 = 0;
            }
            if (IsValidHandle(m_handle_1))
            {
                DVPCamera.dvpClose(m_handle_1);
                m_handle_1 = 0;
            }
            if (IsValidHandle(m_handle_2))
            {
                DVPCamera.dvpClose(m_handle_2);
                m_handle_2 = 0;
            }
            if (IsValidHandle(m_handle_3))
            {
                DVPCamera.dvpClose(m_handle_3);
                m_handle_3 = 0;
            }
        }
    }
}

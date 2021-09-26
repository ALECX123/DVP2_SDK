using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DVPCameraType;
using System.Threading;
using System.Runtime.InteropServices;

namespace ImageAcquisition
{
    public partial class ImageAcquisition : Form
    {
        public uint m_handle = 0;
        public bool m_bAeOp = false;
        public int m_n_dev_count = 0;
        string m_strFriendlyName;
        
        public static IntPtr m_ptr_wnd = new IntPtr();
        public static IntPtr m_ptr = new IntPtr();
        public static bool m_b_start = false;
        public static int m_uImageCount = 0;
        static AutoResetEvent m_ThreadEvent = new AutoResetEvent(false);
        Thread m_pThread;
        public string m_strfilepath;
        public string m_strfiledir;

        public ImageAcquisition()
        {
            InitializeComponent();
            InitDevList();
            Display.Checked = true;
            Form.CheckForIllegalCrossThreadCalls = false;

            System.Timers.Timer t = new System.Timers.Timer(500);

            // 到达时间的时候执行事件
            t.Elapsed += new System.Timers.ElapsedEventHandler(theout);

            // 设置是执行一次（false）还是一直执行(true)
            t.AutoReset = true;

            // 是否执行System.Timers.Timer.Elapsed事件
            t.Enabled = true;

            m_strfiledir = System.Windows.Forms.Application.StartupPath;
            EditPath.Text = m_strfiledir;

        }
        public void theout(object source, System.Timers.ElapsedEventArgs e)
        {
            if (IsValidHandle(m_handle))
            {
                // 更新帧率信息
                dvpFrameCount count = new dvpFrameCount();
                dvpStatus status = DVPCamera.dvpGetFrameCount(m_handle, ref count);
                string str = m_strFriendlyName + " [" + count.uFrameCount.ToString() + " frames, " + string.Format("{0:#0.00}", count.fFrameRate) + " fps]";           
                this.Text = str;
                Counts.Text = m_uImageCount.ToString();
            }
        } 

        public bool IsValidHandle(uint handle)
        {
            bool bValidHandle = false;
            dvpStatus status = DVPCamera.dvpIsValid(handle, ref bValidHandle);
            return bValidHandle;
        }

        public void InitDevList()
        {
            dvpStatus status;
            uint i, n = 0;
            dvpCameraInfo dev_info = new dvpCameraInfo();

            // 此时，n为成功枚举到的相机数量，将添加到下拉列表中，下拉列表中的内容为每个相机的FriendlyName
            DevNameCombo.Items.Clear();

            // 获得当前能连接的相机数量
            status = DVPCamera.dvpRefresh(ref n);
            m_n_dev_count = (int)n;
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

            UpdateControls();
        }

        private void UpdateControls()
        {
	        dvpStatus status;

	        if (IsValidHandle(m_handle))
	        {
		        // 此时已经打开了一个设备
		        // 以下更新和使能基本功能的控件
                dvpStreamState state = dvpStreamState.STATE_STOPED;
                status = DVPCamera.dvpGetStreamState(m_handle, ref state);
                OpenDev.Text = "Close";
                StartPlay.Text = state == dvpStreamState.STATE_STARTED ? ("Stop") : "Start";
                StartPlay.Enabled = true;
                PropertSet.Enabled = true;
		        
		        // 更新示例相关功能控件
                if (state == dvpStreamState.STATE_STARTED)
		        {
                    // 如果采集线程还在继续，禁用一些操作，可以简化多线程同步的问题
                    SaveImageCheck.Enabled = false;
                    Display.Enabled = false;
                    SelectPath.Enabled = false;
                    EditPath.Enabled = false;
                    OpenDev.Enabled = false;
                    EditWait.Enabled = false;
                    SoftTrigger.Enabled = false;

		        }
		        else
		        {
                    if ( DevNameCombo.Items.Count > 0 )
                        OpenDev.Enabled = true;
                    else
                        OpenDev.Enabled = false;

                    SaveImageCheck.Enabled = true;
                    Display.Enabled = true;
                    SelectPath.Enabled = true;
                    EditPath.Enabled = true;
                    OpenFolder.Enabled = true;
                    EditWait.Enabled = true;
                    SoftTrigger.Enabled = true;
		        }
	        }
	        else
	        {
		        // 没有设备被打开
		        // 更新基本功能控件
                OpenDev.Text = "Open";
                StartPlay.Enabled = false;
                PropertSet.Enabled = false;
                OpenDev.Enabled = m_n_dev_count > 0 ? true : false;

		        // 更新示例相关功能的控件
                SaveImageCheck.Enabled = false;
                Display.Enabled = false;
                SelectPath.Enabled = false;
                OpenFolder.Enabled = false;
                SaveImageCheck.Enabled = false;		       
	        }
	       
        }

        private void ScanDev_Click(object sender, EventArgs e)
        {
            InitDevList();
        }

        private void OpenDev_Click(object sender, EventArgs e)
        {
            dvpStatus status;
            string strName;

            if (!IsValidHandle(m_handle))
            {
                strName = DevNameCombo.Text;
                
                if (strName != "")
                {
                    // 通过枚举到并选择的FriendlyName打开指定设备
                    status = DVPCamera.dvpOpenByName(strName, dvpOpenMode.OPEN_NORMAL, ref m_handle);
                    if (status != dvpStatus.DVP_STATUS_OK)
                    {
                        MessageBox.Show("打开失败");
                    }
                    else
                    {
                        m_strFriendlyName = strName;
                    }
                }
            }
            else
            {
                status = DVPCamera.dvpClose(m_handle);
                m_handle = 0;
				pictureBox.Invalidate();
            }

            UpdateControls();
        }

        private void StsartPlay_Click(object sender, EventArgs e)
        {
            if (IsValidHandle(m_handle))
            {
                dvpStreamState state = dvpStreamState.STATE_STOPED;
                dvpStatus status;

                // 根据当前视频状态，执行相反的操作，实现一个按钮既能启动又能停止
                status = DVPCamera.dvpGetStreamState(m_handle, ref state);

                if (state != dvpStreamState.STATE_STOPED)
                {
                    status = DVPCamera.dvpStop(m_handle);

                    if ( (m_pThread.ThreadState & ThreadState.Stopped) == 0 )
                    {
                        m_ThreadEvent.Set();
                        while (m_pThread.ThreadState == ThreadState.Running)
                        {
                            Thread.Sleep(100);
                        }
                    }
                }
                else
                {                   
                    // 在dvpStart之前先设置为触发模式
                    status = DVPCamera.dvpSetTriggerState(m_handle, SoftTrigger.Checked ? true : false);
                    if (status != dvpStatus.DVP_STATUS_OK)
                    {
                        // 此时要确认相机是否支持触发功能
                        MessageBox.Show("设置触发模式失败");
                    }
                    //else 
                    {
                        status = DVPCamera.dvpStart(m_handle);
                        if (status != dvpStatus.DVP_STATUS_OK)
                        {
                            MessageBox.Show("启动失败");
                        }
                        else 
                        {
                            // 重置线程退出事件
                            m_ThreadEvent.Reset();

                            // 创建图像采集线程
                            ParameterizedThreadStart ParStart = new ParameterizedThreadStart(ImageThread);
                            m_pThread = new Thread(ParStart);
                            m_pThread.Start(this);
                            m_b_thread_start = true;
                        }                  
                    }
                }
            }
            UpdateControls();
        }

        static void ImageThread(object obj)
        {
            ImageAcquisition ia = (ImageAcquisition)obj;
            ia.ImageThread();
            return ;
        }

        public static bool m_b_thread_start = false;
        public void ImageThread()
        {
	        dvpStatus status;
            int time_out = 40;

	        // 等待线程退出事件           
            if (EditWait.Text.Length > 0)
            {
                time_out = int.Parse(EditWait.Text);
            }
            if (time_out > 40)
            {
                time_out = 40;
            }
            if (time_out < 1)
            {
                time_out = 40;
            }
            while (!m_ThreadEvent.WaitOne(time_out))
            {
		        IntPtr pBuffer = new IntPtr();
                dvpFrame frame = new dvpFrame();

                if ( SoftTrigger.Checked )
                {
                    status = DVPCamera.dvpTriggerFire(m_handle);
                    if (status != dvpStatus.DVP_STATUS_OK)
                    {
                        // 有可能是触发信号间隔太过密集所导致
                         Console.WriteLine("dvpTriggerFire操作失败, status:%d\r\n", status);
                    }
                }

		        // 从视频流中抓取一帧图像，超时时间通常不应小于曝光时间
		        status = DVPCamera.dvpGetFrame(m_handle, ref frame, ref pBuffer, 4000);
		        if (status != dvpStatus.DVP_STATUS_OK)
		        {
                    Console.WriteLine("dvpGetFrame操作失败, status:%d\r\n", status);
                    continue;
		        }
	
		        // 如果需要保存图像
		        if ( SaveImageCheck.Checked ) 
		        {
			        // 以系统时间为文件名保存新的bmp图像
                    DateTime now = DateTime.Now;
                    m_strfilepath = m_strfiledir + "\\" + now.ToString("yyyy-MM-dd") + " " + now.TimeOfDay.ToString().Replace(":", "-").Replace(".", "-") +".bmp";
                    status = DVPCamera.dvpSavePicture(ref frame, pBuffer, m_strfilepath, 100);
			       
                    m_uImageCount++;
		        }

		        // 如果需要，则显示图像到预览窗口
		        if ( Display.Checked )
		        {
                    status = DVPCamera.dvpDrawPicture(
                                            ref frame,
                                            pBuffer,
                                            this.pictureBox.Handle,
                                            m_ptr,
                                            m_ptr);
		        }		
	        }

            m_pThread.Abort();
            m_b_thread_start = false;
	        return ; 
        }
       
        private void PropertSet_Click(object sender, EventArgs e)
        {
            if (IsValidHandle(m_handle))
            {
                DVPCamera.dvpShowPropertyModalDialog(m_handle, this.Handle);

                // 此时一些配置可能发生改变，将同步到界面
                UpdateControls();
            }
        }

        private void SelectPath_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog dlg = new FolderBrowserDialog();
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                m_strfiledir = dlg.SelectedPath;
                EditPath.Text = m_strfiledir;
            }   
        }

        [DllImport("shell32.dll")]
        static extern IntPtr ShellExecute(
            IntPtr hwnd,
            string lpOperation,
            string lpFile,
            string lpParameters,
            string lpDirectory,
            uint nShowCmd);

        private void OpenFolder_Click(object sender, EventArgs e)
        {
			ShellExecute(m_ptr, ("open"), m_strfiledir, "", "", 1);
        }

        private void ImageAcquisition_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (IsValidHandle(m_handle))
            {              
                if (m_b_thread_start)
                {
                    m_ThreadEvent.Set();
                    while (m_pThread.ThreadState == ThreadState.Running)
                    {
                        Thread.Sleep(100);
                    }
                }
                
                dvpStatus status = DVPCamera.dvpClose(m_handle);
                m_handle = 0;
            }
        }
    }
}

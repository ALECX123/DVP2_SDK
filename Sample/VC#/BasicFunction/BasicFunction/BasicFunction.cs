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

namespace BasicFunction
{
    public partial class BasicFunction : Form
    {

        public uint m_handle = 0;
        public bool m_bAeOp = false;
        public int m_n_dev_count = 0;
        string m_strFriendlyName;

        public static IntPtr m_ptr_wnd = new IntPtr();
        public static IntPtr m_ptr = new IntPtr();
        public static bool m_b_start = false;

        public BasicFunction()
        {
            
            InitializeComponent();
            m_ptr_wnd = pictureBox.Handle;
            InitDevList();
        }

        public bool IsValidHandle(uint handle)
        {
            bool bValidHandle = false;
            dvpStatus status = DVPCamera.dvpIsValid(handle, ref bValidHandle);
            return bValidHandle;
        }

        private void BUTTON_SCAN_Click(object sender, EventArgs e)
        {
            InitDevList();
        }

        //初始化列表
        public void InitDevList()
        {
            dvpStatus status;
	        uint i,n = 0;
	        dvpCameraInfo dev_info = new dvpCameraInfo();

	        // 此时，n为成功枚举到的相机数量，将添加到下拉列表中，下拉列表中的内容为每个相机的FriendlyName
	        COMBO_DEVICES.Items.Clear();


	        // 获得当前能连接的相机数量
            status = DVPCamera.dvpRefresh(ref n);
            m_n_dev_count = (int)n;
            if (status == dvpStatus.DVP_STATUS_OK)
            {
	            for (i=0; i<n; i++)
	            {
		            // 逐个枚举出每个相机的信息
                    status = DVPCamera.dvpEnum(i, ref dev_info);

                    if (status == dvpStatus.DVP_STATUS_OK)
                    {
		                // 界面使用的是UNICODE，枚举的设备信息为ANSI字符串，需要将ANSI转UNICODE
                        int item = COMBO_DEVICES.Items.Add(dev_info.FriendlyName);
                        if (item == 0)
                        {
                            COMBO_DEVICES.SelectedIndex = item;
                        }
                    }
	            }
            }
            if (n == 0)
            {
                BUTTON_OPEN.Enabled = false;
            }
            else
            {
                BUTTON_OPEN.Enabled = true;
            }

            if (!IsValidHandle(m_handle))
            {
                BUTTON_START.Enabled = false;
                BUTTON_PROPERTY.Enabled = false;
                BUTTON_SAVE.Enabled = false;
                CHECK_AEOPERATION.Enabled = false;
                COMBO_AE_MODE.Enabled = false;
                SLIDER_EXPOSURE_TIME.Enabled = false;
                COMBO_FLICK.Enabled = false;
                SLIDER_GAIN.Enabled = false;
                COMBO_RESOLUTION.Enabled = false;
            }    
        }

        private DVPCamera.dvpStreamCallback _proc;   

        // 数据接收回调函数
        public static int _dvpStreamCallback(/*dvpHandle*/uint handle, dvpStreamEvent _event, /*void **/IntPtr pContext, ref dvpFrame refFrame, /*void **/IntPtr pBuffer)
        {
            RECT rt = new RECT();
            rt.Bottom = 100;
            rt.Left = 0;
            rt.Top = 0;
            rt.Right = 100;

            // 刷新显示
            dvpStatus s = DVPCamera.dvpDrawPicture(ref refFrame, pBuffer, m_ptr_wnd, m_ptr, m_ptr);
            Debug.Assert(s == dvpStatus.DVP_STATUS_OK, "Draw pictures fail!");
            return 1;
        }

        private void BUTTON_OPEN_Click(object sender, EventArgs e)
        {
            if (!IsValidHandle(m_handle))
            {
                uint i = (uint)COMBO_DEVICES.SelectedIndex;
                dvpStatus status = DVPCamera.dvpOpen(i, dvpOpenMode.OPEN_NORMAL, ref m_handle);
                if (status != dvpStatus.DVP_STATUS_OK)
                {
                    m_handle = 0;
                    MessageBox.Show("打开失败");
                }
                else
                {
                    m_strFriendlyName = COMBO_DEVICES.Text;                 
                    _proc = _dvpStreamCallback;
                    using (Process curProcess = Process.GetCurrentProcess())
                    using (ProcessModule curModule = curProcess.MainModule)
                    {
                        dvpStatus s = DVPCamera.dvpRegisterStreamCallback(m_handle, _proc, dvpStreamEvent.STREAM_EVENT_PROCESSED, m_ptr);
                    }
                    
                    // 分辨率
                    InitControlResolution();

                    // AE设置
                    InitControlAeMode();

                    // Flick设置
                    InitControlFlick();

                    UpdateControlExposure();
                    UpdateControlGain();
                }
            }
            else 
            {
                DVPCamera.dvpStop(m_handle);
                m_b_start = false;
                DVPCamera.dvpStreamCallback pf = new DVPCamera.dvpStreamCallback(_dvpStreamCallback);
                dvpStatus s = DVPCamera.dvpUnregisterStreamCallback(m_handle, pf, dvpStreamEvent.STREAM_EVENT_PROCESSED, m_ptr);
                DVPCamera.dvpClose(m_handle);
                m_handle = 0;
				pictureBox.Invalidate();
            }
            UpdateControls();
        }

        public void InitControlResolution()
        {
	        uint QuickRoiSel = 0;
	        dvpQuickRoi QuickRoiDetail = new dvpQuickRoi();
	        dvpStatus status; 
	        dvpSelectionDescr QuickRoiDescr = new dvpSelectionDescr();
            COMBO_RESOLUTION.Items.Clear();

            if ( !IsValidHandle(m_handle) )
            {
                COMBO_RESOLUTION.Enabled = false;
                return ;
            }

	        // 获取相机分辨率索引号
	        status = DVPCamera.dvpGetQuickRoiSelDescr(m_handle, ref QuickRoiDescr);
	        if (status == dvpStatus.DVP_STATUS_OK)
	        {
		        for (uint iNum = 0; iNum < QuickRoiDescr.uCount; iNum++)
		        {
			        status = DVPCamera.dvpGetQuickRoiSelDetail(m_handle,iNum, ref QuickRoiDetail);
			        if (status == dvpStatus.DVP_STATUS_OK)
			        {			
                        COMBO_RESOLUTION.Items.Add(QuickRoiDetail.selection._string);
			        }
		        }
	        }

	        // 获取分辨率模式索引
            status = DVPCamera.dvpGetResolutionModeSel(m_handle, ref QuickRoiSel);
            if (status == dvpStatus.DVP_STATUS_OK)
	        {
                COMBO_RESOLUTION.SelectedIndex = (int)QuickRoiSel;
	        }
            COMBO_RESOLUTION.Enabled = true;
        }

        public void InitControlAeMode()
        {
            COMBO_AE_MODE.Items.Clear();
            if (!IsValidHandle(m_handle))
            {
                COMBO_AE_MODE.Enabled = false;
                return;
            }
            COMBO_AE_MODE.Items.Add("AE_MODE_AE_AG");
            COMBO_AE_MODE.Items.Add("AE_MODE_AG_AE");
            COMBO_AE_MODE.Items.Add("AE_MODE_AE_ONLY");
            COMBO_AE_MODE.Items.Add("AE_MODE_AG_ONLY");
            COMBO_AE_MODE.SelectedIndex = 0;		        
            COMBO_AE_MODE.Enabled = true;
        }

        public void InitControlFlick()
        {
            COMBO_FLICK.Items.Clear();
            if (m_handle == 0)
            {
                COMBO_FLICK.Enabled = false;
                return;
            }
            COMBO_FLICK.Items.Add("ANTIFLICK_DISABLE");
            COMBO_FLICK.Items.Add("ANTIFLICK_50HZ");
            COMBO_FLICK.Items.Add("ANTIFLICK_60HZ");
            COMBO_FLICK.SelectedIndex = 1;		    
            COMBO_FLICK.Enabled = true;
        }

        public void UpdateControlExposure()
        {
	        double fExpoTime = 0.0f;
	        string strValue;
            dvpDoubleDescr ExpoTimeDescr = new dvpDoubleDescr(); ;
            dvpStatus status;

	        // 获取曝光时间的描述信息
            status = DVPCamera.dvpGetExposureDescr(m_handle, ref ExpoTimeDescr);
            if (status == dvpStatus.DVP_STATUS_OK)
	        {
		        // 设置曝光时间拖动条的范围
                SLIDER_EXPOSURE_TIME.SetRange((int)ExpoTimeDescr.fMin, (int)ExpoTimeDescr.fMax);
	        }

	        // 获取曝光时间的初值
            status = DVPCamera.dvpGetExposure(m_handle, ref fExpoTime);
            if (status == dvpStatus.DVP_STATUS_OK)
	        {
		        // 设置曝光时间拖动条初始值
                SLIDER_EXPOSURE_TIME.Value = (int)fExpoTime;
                strValue = string.Format("{0:#0.000}", fExpoTime);
                STATIC_EXPOTIME.Text = strValue;
	        }
        }

        public void UpdateControlGain()
        {
	        dvpStatus  status;
	        float fAnalogGain = 0.0F;
	        string strValue;
	        dvpFloatDescr AnalogGainDescr = new dvpFloatDescr();

            // 获取模拟增益的描述信息
            status = DVPCamera.dvpGetAnalogGainDescr(m_handle, ref AnalogGainDescr);
            if (status == dvpStatus.DVP_STATUS_OK)
            {
                // 设置模拟增益拖动条的范围
                SLIDER_GAIN.SetRange((int)AnalogGainDescr.fMin * 100, (int)AnalogGainDescr.fMax * 100); //单位x
            }

            // 获取模拟增益并设置模拟增益的初始值
            status = DVPCamera.dvpGetAnalogGain(m_handle, ref fAnalogGain);         
            if (status == dvpStatus.DVP_STATUS_OK)
            {
                // 设置增益拖动条初始值
                SLIDER_GAIN.Value = (int)(fAnalogGain * 100);
                strValue = string.Format("{0:#0.000}", fAnalogGain);
                STATIC_EXPOGAIN.Text = strValue + "x";
            }
        }

        private void BUTTON_START_Click(object sender, EventArgs e)
        {
            dvpStreamState state = dvpStreamState.STATE_STOPED;
            dvpStatus status = dvpStatus.DVP_STATUS_UNKNOW;

            if ( IsValidHandle(m_handle) )
            {
                // 根据当前视频状态，执行相反的操作，实现一个按钮既能启动又能停止
                status = DVPCamera.dvpGetStreamState(m_handle, ref state);
                if (state == dvpStreamState.STATE_STARTED)
                {
                    status = DVPCamera.dvpStop(m_handle);
                    m_b_start = status == dvpStatus.DVP_STATUS_OK? false: true;
                }
                else
                {
                    status = DVPCamera.dvpStart(m_handle);
                    m_b_start = status == dvpStatus.DVP_STATUS_OK ? true : false;
                }

            }

            UpdateControls();
        }

        public void UpdateControls()
        {
            dvpStatus status = dvpStatus.DVP_STATUS_UNKNOW;
            if ( IsValidHandle(m_handle) )
	        {
		        // 此时已经打开了一个设备
		        // 更新基本功能控件
                dvpStreamState state = new dvpStreamState();
                status = DVPCamera.dvpGetStreamState(m_handle, ref state);
                BUTTON_START.Text = (state == dvpStreamState.STATE_STARTED ? ("Stop") : ("Start"));
                BUTTON_OPEN.Text = "Close";
                BUTTON_START.Enabled = true;
                BUTTON_PROPERTY.Enabled = true;
                BUTTON_SAVE.Enabled = true;
	            
		        // 以下更新示例相关功能控件
                COMBO_RESOLUTION.Enabled = true;
                COMBO_AE_MODE.Enabled = true;
                COMBO_FLICK.Enabled = true;
                CHECK_AEOPERATION.Enabled = true;	      

		        // 更新自动曝光操作控件
                dvpAeOperation AeOp = new dvpAeOperation();
                dvpAeMode AeMode = new dvpAeMode();

                status = DVPCamera.dvpGetAeOperation(m_handle, ref AeOp);              
                status = DVPCamera.dvpGetAeMode(m_handle, ref AeMode);

                if (AeOp == dvpAeOperation.AE_OP_OFF)
                {
                    m_bAeOp = false;
                    SLIDER_EXPOSURE_TIME.Enabled = true;
                    SLIDER_GAIN.Enabled = true;
                }
                else if (AeOp == dvpAeOperation.AE_OP_CONTINUOUS || AeOp == dvpAeOperation.AE_OP_ONCE)
                {		
                    m_bAeOp = true;
                    SLIDER_EXPOSURE_TIME.Enabled = AeMode == dvpAeMode.AE_MODE_AG_ONLY;
                    SLIDER_GAIN.Enabled = AeMode == dvpAeMode.AE_MODE_AE_ONLY;                  
                }

                CHECK_AEOPERATION.Checked = m_bAeOp;

		        // 获取自动曝光模式并更新自动曝光模式设置控件、使能曝光时间和模拟增益调节的控件
                COMBO_AE_MODE.SelectedIndex = (int)AeMode;

		        // 更新抗频闪设置控件
                dvpAntiFlick AntiFlick = new dvpAntiFlick();
                status = DVPCamera.dvpGetAntiFlick(m_handle, ref AntiFlick);
                if (COMBO_FLICK.Items.Count > 0)
                    COMBO_FLICK.SelectedIndex = (int)AntiFlick;

		        // 更新曝光时间
		        double fExpoTime = 0.0f;
		        string strExpoTime;
                status = DVPCamera.dvpGetExposure(m_handle, ref fExpoTime);
                strExpoTime = string.Format("{0:00000}", fExpoTime);
                STATIC_EXPOTIME.Text = strExpoTime;				 
		        
		        // 更新增益
		        string strGain;
		        float fGain = 0.0f;
                status = DVPCamera.dvpGetAnalogGain(m_handle, ref fGain);
                strGain = string.Format("{0:0.00}", fGain);
                STATIC_EXPOGAIN.Text = strGain;
		        
                // 更新分辨率
		        uint QRoiSel = 0;
                status = DVPCamera.dvpGetQuickRoiSel(m_handle, ref QRoiSel);
                if (COMBO_RESOLUTION.Items.Count > 0)
                    COMBO_RESOLUTION.SelectedIndex = (int)QRoiSel;
		        
                // 更新曝光时间和增益的当前设置值
                UpdateControlExposure();
                UpdateControlGain();
	        }
	        else
	        {
		        // 此时设备还没有被打开
		        // 更新基本功能控件
                BUTTON_OPEN.Text = "Open";
                BUTTON_START.Enabled = false;
                BUTTON_PROPERTY.Enabled = false;
                BUTTON_SAVE.Enabled = false;

                BUTTON_OPEN.Enabled = m_n_dev_count == 0 ? false:true;
                SLIDER_EXPOSURE_TIME.Enabled = false;
                SLIDER_GAIN.Enabled = false;
                COMBO_RESOLUTION.Enabled = false;
                COMBO_AE_MODE.Enabled = false;
                COMBO_FLICK.Enabled = false;               
	        }	        
        }

        private void BUTTON_PROPERTY_Click(object sender, EventArgs e)
        {
            if (IsValidHandle(m_handle))
            {
                dvpStatus status = DVPCamera.dvpShowPropertyModalDialog(m_handle, this.Handle);
                
                // 此时一些配置可能发生改变，将同步到界面
                UpdateControls();
            }
        }

        private void COMBO_RESOLUTION_SelectedIndexChanged(object sender, EventArgs e)
        {
            dvpStatus status;

            if ( !m_b_start)
                return;

            // 获取分辨率选择索引
            int iSel = COMBO_RESOLUTION.SelectedIndex ;
            if (iSel < 0)
            {
                return;
            }

            // 关闭视频流
            status = DVPCamera.dvpStop(m_handle);
            if (status != dvpStatus.DVP_STATUS_OK)
            {
                MessageBox.Show(("关闭视频流失败!"));
            }
            m_b_start = false;

            // 设置相机分辨率
            status = DVPCamera.dvpSetQuickRoiSel(m_handle, (uint)iSel);
            if (status != dvpStatus.DVP_STATUS_OK)
            {
                MessageBox.Show(("设置分辨率错误!"));
            }

            // 打开视频流
            status = DVPCamera.dvpStart(m_handle);
            if (status != dvpStatus.DVP_STATUS_OK)
            {
                MessageBox.Show(("启动视频流失败!"));
            }
            m_b_start = true;
        }

        private void BasicFunction_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (IsValidHandle(m_handle))
            {
                DVPCamera.dvpStop(m_handle);
                m_b_start = false;

                DVPCamera.dvpStreamCallback pf = new DVPCamera.dvpStreamCallback(_dvpStreamCallback);
                dvpStatus s = DVPCamera.dvpUnregisterStreamCallback(m_handle, pf, dvpStreamEvent.STREAM_EVENT_PROCESSED, m_ptr);
                DVPCamera.dvpClose(m_handle);
                m_handle = 0;
            }
        }

        private void CHECK_AEOPERATION_Click(object sender, EventArgs e)
        {
            dvpStatus status;

            m_bAeOp = CHECK_AEOPERATION.Checked;

            if (m_bAeOp)
            {
                status = DVPCamera.dvpSetAeOperation(m_handle, dvpAeOperation.AE_OP_CONTINUOUS);
            }
            else
            {
                status = DVPCamera.dvpSetAeOperation(m_handle, dvpAeOperation.AE_OP_OFF);
            }

            UpdateControls();
        }

        private void COMBO_FLICK_SelectedIndexChanged(object sender, EventArgs e)
        {
            dvpStatus status = dvpStatus.DVP_STATUS_OK;

            // 获取自动曝光索引
            if ( COMBO_FLICK.SelectedIndex > 2 )
            {
                return;
            }

            if (COMBO_FLICK.SelectedIndex == 0)
            {
                status = DVPCamera.dvpSetAntiFlick(m_handle, dvpAntiFlick.ANTIFLICK_DISABLE);
            }
            else if (COMBO_FLICK.SelectedIndex == 2)
            {
                status = DVPCamera.dvpSetAntiFlick(m_handle, dvpAntiFlick.ANTIFLICK_60HZ);
            }
            else if (COMBO_FLICK.SelectedIndex == 1)
            {
                status = DVPCamera.dvpSetAntiFlick(m_handle, dvpAntiFlick.ANTIFLICK_50HZ);
            }
            
        }

        private void COMBO_AE_MODE_ImeModeChanged(object sender, EventArgs e)
        {
            dvpStatus status = dvpStatus.DVP_STATUS_OK;

            // 获取自动曝光模式索引          
            if (COMBO_AE_MODE.SelectedIndex > 3)
            {
                return;
            }

            // 自动曝光优先
            if (COMBO_AE_MODE.SelectedIndex == 0)
            {
                status = DVPCamera.dvpSetAeMode(m_handle, dvpAeMode.AE_MODE_AE_AG);
            }

            // 自动增益优先
            else if (COMBO_AE_MODE.SelectedIndex == 1)
            {
                status = DVPCamera.dvpSetAeMode(m_handle, dvpAeMode.AE_MODE_AG_AE);
            }

            // 仅打开自动曝光
            else if (COMBO_AE_MODE.SelectedIndex == 2)
            {
                status = DVPCamera.dvpSetAeMode(m_handle, dvpAeMode.AE_MODE_AE_ONLY);
            }

            // 仅打开自动增益
            else if (COMBO_AE_MODE.SelectedIndex == 3)
            {
                status = DVPCamera.dvpSetAeMode(m_handle, dvpAeMode.AE_MODE_AG_ONLY);
            }
           
            UpdateControls();
        }

        private void SLIDER_EXPOSURE_TIME_ValueChanged(object sender, EventArgs e)
        {
            string strExpoTime;
            double fExpoTime = 0.0f;
            dvpDoubleDescr ExpDescr = new dvpDoubleDescr();
            dvpStatus status;

            if (IsValidHandle(m_handle))
            {
                // 获取所设置的曝光时间拖动条的值
                fExpoTime = SLIDER_EXPOSURE_TIME.Value ;

                // 设置曝光时间
                // 获取曝光时间的范围，避免设置值超出范围
                status = DVPCamera.dvpGetExposureDescr(m_handle, ref ExpDescr);              

                if (fExpoTime > ExpDescr.fMax)
                    fExpoTime = ExpDescr.fMax;

                if (fExpoTime < ExpDescr.fMin)
                    fExpoTime = ExpDescr.fMin;

                // 先设置曝光时间
                status = DVPCamera.dvpSetExposure(m_handle, fExpoTime);
               
                // 再获取曝光时间，由于调节精度(步进值)的问题，获取值可能与设置值有些差异，以获取值为准
                status = DVPCamera.dvpSetExposure(m_handle, fExpoTime);
                
                // 设置曝光时间文本
                strExpoTime = string.Format("{0:#0.000}", fExpoTime);
                STATIC_EXPOTIME.Text = strExpoTime;               
            }
        }

        private void SLIDER_GAIN_ValueChanged(object sender, EventArgs e)
        {
            string strGain;
            float fGain = 0.0f;
            dvpStatus status;

            if (IsValidHandle(m_handle))
            {
                // 获取所设置的模拟增益拖动条值
                fGain = SLIDER_GAIN.Value *1.0f / 100;

                // 先设置增益值
                status = DVPCamera.dvpSetAnalogGain(m_handle, fGain);
                
                // 再获取增益值，由于调节精度(步进值)的问题，获取值可能与设置值有些差异，以获取值为准
                status = DVPCamera.dvpGetAnalogGain(m_handle, ref fGain);
                
                // 设置模拟增益文本
                strGain = string.Format("{0:0.000}", fGain);
                STATIC_EXPOGAIN.Text = strGain + "x";
            }
        }

        private void BUTTON_SAVE_Click(object sender, EventArgs e)
        {
            if (!m_b_start)
                return;

            SaveFileDialog sfd = new SaveFileDialog();
            string file_path;

            sfd.Filter = "bmp文件(*.bmp)|*.bmp|jpeg文件(*.jpeg)|*.jpg|png文件(*.png)|*.png";
            
            if (sfd.ShowDialog() == DialogResult.OK)
            {
                file_path = sfd.FileName;
                IntPtr buffer = new IntPtr();
                dvpFrame frame = new dvpFrame();
                dvpStatus status;

                // 从视频流中抓取一帧图像，要求5000ms以内
                status = DVPCamera.dvpGetFrame(m_handle, ref frame, ref buffer, 5000);
                if (status == dvpStatus.DVP_STATUS_OK)
                {
                    // 将图像保存为图片文件
                    status = DVPCamera.dvpSavePicture(ref frame, buffer, file_path, 100);                   
                }
                else if (status == dvpStatus.DVP_STATUS_TIME_OUT)
                {
                    MessageBox.Show(("获取图像数据超时!"));
                }
                else
                {
                    MessageBox.Show(("获取图像数据时发生错误!"));
                }
            }
        }

        private void COMBO_AE_MODE_SelectedIndexChanged(object sender, EventArgs e)
        {
            dvpStatus status = new dvpStatus();

            // 获取自动曝光模式索引
            int iSel = COMBO_AE_MODE.SelectedIndex;
            if (iSel > 3)
            {         
                return;
            }

            // 仅打开自动曝光
            else if (iSel == 2)
            {
                status = DVPCamera.dvpSetAeMode(m_handle, dvpAeMode.AE_MODE_AE_ONLY);
            }

            // 仅打开自动增益
            else if (iSel == 3)
            {
                status = DVPCamera.dvpSetAeMode(m_handle, dvpAeMode.AE_MODE_AG_ONLY);
            }
            // 自动增益优先
            else if (iSel == 1)
            {
                status = DVPCamera.dvpSetAeMode(m_handle, dvpAeMode.AE_MODE_AG_AE);
            }
            // 自动曝光优先
            if (iSel == 0)
            {
                status = DVPCamera.dvpSetAeMode(m_handle, dvpAeMode.AE_MODE_AE_AG);
            }

            UpdateControls();
        }      
    }
}

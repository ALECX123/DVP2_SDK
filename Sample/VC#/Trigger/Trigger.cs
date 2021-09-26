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

namespace Trigger
{
    public partial class Trigger : Form
    {
        public uint m_handle = 0;
        public bool m_bAeOp = false;
        public int m_n_dev_count = 0;
        string m_strFriendlyName = "";

        public static IntPtr m_ptr_wnd = new IntPtr();
        public static IntPtr m_ptr = new IntPtr();
        public static bool m_b_start = false;

        public static double m_TriggerDelay = 0.0f;
        public static double m_TriggerFilter = 0.0f;
        public static double m_TriggerLoop = 0.0f;
        dvpDoubleDescr m_DelayDescr = new dvpDoubleDescr();
        dvpDoubleDescr m_FilterDescr = new dvpDoubleDescr();
        dvpDoubleDescr m_LoopDescr = new dvpDoubleDescr();

        public bool IsValidHandle(uint handle)
        {
            bool bValidHandle = false;
            dvpStatus status = DVPCamera.dvpIsValid(handle, ref bValidHandle);
            return bValidHandle;
        }

        public void InitDevList()
        {
	        dvpStatus status = new dvpStatus();
	        uint i,n=0;
	        dvpCameraInfo info = new dvpCameraInfo();

	        // 此时，n为成功枚举到的相机数量，将添加到下拉列表中，下拉列表中的内容为每个相机的FriendlyName
            DevNameCombo.Items.Clear();

	        // 获得当前能连接的相机数量
            status = DVPCamera.dvpRefresh(ref n);

            if (status == dvpStatus.DVP_STATUS_OK)
	        {
		        // 枚举最多16台相机
		        if (n>16)
			        n = 16;

		        for (i=0; i<n; i++)
		        {
			        // 逐个枚举出每个相机的信息
                    status = DVPCamera.dvpEnum(i, ref info);

                    if (status == dvpStatus.DVP_STATUS_OK)
			        {
				        // 界面使用的是UNICODE，枚举的设备信息为ANSI字符串，需要将ANSI转UNICODE
                        DevNameCombo.Items.Add(info.FriendlyName);
			        }
		        }

		        if (i != 0)
		        {
                    DevNameCombo.SelectedIndex = 0;
		        }

		        UpdateControls();
	        }
        }

        public void UpdateControls()
        {
	        dvpStatus status;

 	        if (IsValidHandle(m_handle))
	        {	
		        // 此时已经打开了一个设备
		        // 以下更新和使能基本功能的控件
		        dvpStreamState state = new dvpStreamState();
		        status = DVPCamera.dvpGetStreamState(m_handle, ref state);
		        OpenDev.Text = "Close";
                StartPlay.Text  = state == dvpStreamState.STATE_STARTED ? ("Stop") :("Start");
                StartPlay.Enabled = true;
                PropertSet.Enabled = true;

		        // 以下使能示例相关功能的控件
                InputIOCombo.Enabled = true;
                InputSignalTypeCombo.Enabled = true;
                OutputSignalType.Enabled = true;
                OutIOCombo.Enabled = true;
                EditFilter.Enabled = true;
		        TriggerDelay.Enabled = true;
                TriggerLoop.Enabled = true;
                TriggerMode.Enabled = true;
                LoopTrigger.Enabled = true;
                EnableIn.Enabled = true;
                EnableOut.Enabled = true;
                SoftTriggerFire.Enabled = true;
                ApplyLoop.Enabled = true;
                ApplyDelay.Enabled = true;
                FilterApply.Enabled = true;

		        // 以下更新触发功能相关的界面
		        bool bTrig = false;
                bool bLoop = false;

		        // 触发模式使能状态
		        status = DVPCamera.dvpGetTriggerState(m_handle, ref bTrig);
                TriggerMode.Checked = bTrig;
                status = DVPCamera.dvpSetTriggerState(m_handle, bTrig);
                if (status != dvpStatus.DVP_STATUS_OK)
                {
                    // 此时要确认相机是否支持触发功能
                    TriggerMode.Enabled = false;
                }
		       
                SoftTriggerFire.Enabled = bTrig;
	       
		        // 循环触发使能状态
		        status = DVPCamera.dvpGetSoftTriggerLoopState(m_handle, ref bLoop);
		        LoopTrigger.Checked = bLoop;
				if (status == dvpStatus.DVP_STATUS_OK)
					LoopTrigger.Enabled = true;
				else
					LoopTrigger.Enabled = false;

		        // 外部触发输入IO相关状态
		        bool bExtTrigIn = false;
		        dvpUserIoInfo UserIoInfo = new dvpUserIoInfo();
		        dvpInputIoFunction InIoFunc = new dvpInputIoFunction();
		        int i = 0;

		        // 枚举出所有UserIO，并检查是否有IO用于触发输入功能
		        status = DVPCamera.dvpGetUserIoInfo(m_handle, ref UserIoInfo);
		        
		        InputIOCombo.Items.Clear();
                int nInLength = 8 < UserIoInfo.inputValid.Length? 8 : UserIoInfo.inputValid.Length;
                for (i = 0; i < nInLength; i++)
		        {
			        if ( UserIoInfo.inputValid[i] > 0 )
			        {
				        string str;
				        dvpInputIo InputIo = (dvpInputIo)(i + (int)dvpInputIo.INPUT_IO_1);

				        // 把IO名称添加到下拉列表中
                        int nInItem = i + 1;
                        str = "IN_" + nInItem.ToString();
				        int item = InputIOCombo.Items.Add(str);

				        // 检查是否有输入IO被设置为触发输入功能
				        status = DVPCamera.dvpGetInputIoFunction(m_handle, InputIo, ref InIoFunc);
				        
				        if (!bExtTrigIn && InIoFunc == dvpInputIoFunction.INPUT_FUNCTION_TRIGGER)
				        {
					        // 找到一个IO已经被设置为触发输入信号
					        bExtTrigIn = true;

					        // 在下拉列表中选取那个被设置为触发输入功能的IO
					        InputIOCombo.SelectedIndex = i;
				        }
			        }
		        }
				if ( bExtTrigIn )
                {
					//在界面上指示出已经有触发输入信号被使用
					InputIOCombo.Enabled = true;
                }
                else
                {
					if (InputIOCombo.Items.Count > 0)
					{
						// 没有IO被设置为触发输入，默认在下拉列表中选取第一个
						InputIOCombo.SelectedIndex = 0;
					}

                    InputIOCombo.Enabled = true;
                }

                // 在界面上指示出已经有触发输入信号被使用
                EnableIn.Checked = bExtTrigIn;


		        // 更新触发输入信号类型列表
		        InputSignalTypeCombo.Items.Clear();
		        InputSignalTypeCombo.Items.Add(("Off"));
		        InputSignalTypeCombo.Items.Add(("Falling Edge"));
		        InputSignalTypeCombo.Items.Add(("Low Level"));
		        InputSignalTypeCombo.Items.Add(("Rising Edge"));
		        InputSignalTypeCombo.Items.Add(("High Level"));

		        dvpTriggerInputType TriggerType = new dvpTriggerInputType();
		        status = DVPCamera.dvpGetTriggerInputType(m_handle, ref TriggerType);
		        InputSignalTypeCombo.SelectedIndex = (int)TriggerType;		      

		        // 以下更新Strobe功能相关的界面
		        bool bExtStrobeOut = false;
		        dvpOutputIoFunction OutIoFunc = new dvpOutputIoFunction();
               
		        // 枚举出所有UserIO，并检查是否有IO用于Strobe输出功能
		        OutIOCombo.Items.Clear();
		        for (i=0; i<8; i++)
		        {
                    status = DVPCamera.dvpGetOutputIoFunction(m_handle, (dvpOutputIo)(dvpOutputIo.OUTPUT_IO_1+i), ref OutIoFunc);

                    if ( OutIoFunc == dvpOutputIoFunction.OUTPUT_FUNCTION_STROBE)
			        {
				        string str;
				        dvpOutputIo OutputIo = (dvpOutputIo)(i + dvpOutputIo.OUTPUT_IO_1);

				        // 把IO名称添加到下拉列表中
                        int nOutItem = i + 1;
                        str = "OUT_" + nOutItem.ToString();
                        OutIOCombo.Items.Add(str);

				        // 检查是否有输出IO被设置为Strobe输出功能
                        status = DVPCamera.dvpGetOutputIoFunction(m_handle, OutputIo, ref OutIoFunc);

                        if (!bExtStrobeOut && OutIoFunc == dvpOutputIoFunction.OUTPUT_FUNCTION_STROBE)
				        {
					        // 找到一个IO已经被设置为strobe输出功能的IO
					        bExtStrobeOut = true;

					        // 在下拉列表中选取那个被设置为strobe输出功能的IO
                            OutIOCombo.SelectedIndex = i;

				        }
			        }
		        }
				if (bExtStrobeOut) 
				{
					//在界面上指示出已经有Strobe输出信号被使用
					EnableOut.Checked = true;
				}
				else
				{
					//没有IO被设置为触发输入，默认在下拉列表中选取第一个
					if (OutIOCombo.Items.Count > 0) 
					{	
						OutIOCombo.SelectedIndex = 0;
					}
					else
					{
						OutIOCombo.Items.Add("OUT_1");
						OutIOCombo.SelectedIndex = 0;
					}
				
					//在界面上指示出没有Strobe输出信号被使用
					EnableOut.Checked = false;
				}
				
		        // 更新Strobe输出信号类型列表
                OutputSignalType.Items.Clear();
                OutputSignalType.Items.Add(("Off"));
                OutputSignalType.Items.Add(("Low Level"));
                OutputSignalType.Items.Add(("High Level"));

		        // 获取Strobe信号类型
		        dvpStrobeOutputType StrobeType = new dvpStrobeOutputType();
                status = DVPCamera.dvpGetStrobeOutputType(m_handle, ref StrobeType);
                OutputSignalType.SelectedIndex = (int)StrobeType;
		        
		        // 以下这些获取的描述信息将用于更新编辑框中设置值的范围
                status = DVPCamera.dvpGetTriggerDelayDescr(m_handle, ref m_DelayDescr);		        
                status = DVPCamera.dvpGetTriggerJitterFilterDescr(m_handle, ref m_FilterDescr);		        
                status = DVPCamera.dvpGetSoftTriggerLoopDescr(m_handle, ref m_LoopDescr);
		        
		        // 以下更新编辑框中的设置值
                status = DVPCamera.dvpGetSoftTriggerLoop(m_handle, ref m_TriggerLoop);
				TriggerLoop.Text = m_TriggerLoop.ToString();
                status = DVPCamera.dvpGetTriggerDelay(m_handle, ref m_TriggerDelay);
				TriggerDelay.Text = m_TriggerDelay.ToString();
                status = DVPCamera.dvpGetTriggerJitterFilter(m_handle, ref m_TriggerFilter);
				if (m_TriggerFilter < 1)
				{
					m_TriggerFilter = 1;
				}
				EditFilter.Text = m_TriggerFilter.ToString();
	        }
	        else
	        {
		        // 此时还没有设备被打开
		        // 更新基本功能控件
                OpenDev.Text = "Open";
                StartPlay.Enabled = false;
                PropertSet.Enabled = false;

                if (DevNameCombo.Items.Count == 0 )
		        {
			        // 没有设备存在
                    OpenDev.Enabled = false;
		        }
		        else
		        {
                    OpenDev.Enabled = true;
		        }

		        // 更新本示例相关功能的控件
                InputIOCombo.Enabled = false;
                InputSignalTypeCombo.Enabled = false;
                OutputSignalType.Enabled = false;
                OutIOCombo.Enabled = false;
                EditFilter.Enabled = false;
                TriggerDelay.Enabled = false;
                TriggerLoop.Enabled = false;
                TriggerMode.Enabled = false;
                LoopTrigger.Enabled = false;
                EnableIn.Enabled = false;
                EnableOut.Enabled = false;
                SoftTriggerFire.Enabled = false;
                ApplyLoop.Enabled = false;
                ApplyDelay.Enabled = false;
                FilterApply.Enabled = false;
	        }
        }

        public Trigger()
        {
            InitializeComponent();
            m_ptr_wnd = pictureBox.Handle;
            InitDevList();
            System.Timers.Timer t = new System.Timers.Timer(500);
            
            // 到达时间的时候执行事件
            t.Elapsed += new System.Timers.ElapsedEventHandler(theout);
            
            // 设置执行方式
            t.AutoReset = true;

            // 是否执行System.Timers.Timer.Elapsed事件
            t.Enabled = true;
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
            }
        } 

        private void ScanDev_Click(object sender, EventArgs e)
        {
            InitDevList();
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
            return 1;
        }

        private void OpenDev_Click(object sender, EventArgs e)
        {
            dvpStatus status = dvpStatus.DVP_STATUS_OK;
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

                        // 如果需要图像显示，可以注册回调函数，在回调函数中完成绘图操作
                        // 注意：回调函数中执行的绘图操作，可能会对dvpGetFrame接口获取的图像数据造成延时
                        _proc = _dvpStreamCallback;
                        using (Process curProcess = Process.GetCurrentProcess())
                        using (ProcessModule curModule = curProcess.MainModule)
                        {
                            DVPCamera.dvpRegisterStreamCallback(m_handle, _proc, dvpStreamEvent.STREAM_EVENT_PROCESSED, m_ptr);
                        }
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

        private void StartPlay_Click(object sender, EventArgs e)
        {
            if (IsValidHandle(m_handle))
            {
                dvpStreamState state = new dvpStreamState();
                dvpStatus status;

                // 根据当前视频状态，执行相反的操作，实现一个按钮既能启动又能停止
                status = DVPCamera.dvpGetStreamState(m_handle, ref state);

                if (state == dvpStreamState.STATE_STARTED)
                {
                    status = DVPCamera.dvpStop(m_handle);
                }
                else
                {
                    status = DVPCamera.dvpStart(m_handle);
                }

            }

            UpdateControls();
        }

        private void PropertSet_Click(object sender, EventArgs e)
        {
            if (IsValidHandle(m_handle))
            {
                dvpStatus status = DVPCamera.dvpShowPropertyModalDialog(m_handle, this.Handle);
                
                // 此时一些配置可能发生改变，将同步到界面
                UpdateControls();
            }
        }

        private void TriggerMode_CheckedChanged(object sender, EventArgs e)
        {
            if (IsValidHandle(m_handle))
            {
                // 使能/禁用触发模式
                dvpStatus status = DVPCamera.dvpSetTriggerState(m_handle, TriggerMode.Checked);
                
                UpdateControls();
            }
        }

        private void SoftTriggerFire_Click(object sender, EventArgs e)
        {
            if (IsValidHandle(m_handle))
            {
                // 这个函数执行一次，相当于产生一次外触发
                // 注意：如果曝光时间较长时，过快的点击"Soft Trigger Fire"有可能导致触发失败，因为上一帧还可能出于曝光或未输出完的状态
                dvpStatus status = DVPCamera.dvpTriggerFire(m_handle);
            }
        }

        private void LoopTrigger_CheckedChanged(object sender, EventArgs e)
        {
            dvpStatus status = DVPCamera.dvpSetSoftTriggerLoopState(m_handle, LoopTrigger.Checked);
        }

        private void ApplyLoop_Click(object sender, EventArgs e)
        {
            if (IsValidHandle(m_handle))
            {
				m_TriggerLoop = float.Parse(TriggerLoop.Text);
                dvpStatus status = DVPCamera.dvpSetSoftTriggerLoop(m_handle, m_TriggerLoop);
            }
        }

        private void ApplyDelay_Click(object sender, EventArgs e)
        {
            if (IsValidHandle(m_handle))
            {
				m_TriggerDelay = float.Parse(TriggerDelay.Text);
				
                dvpStatus status = DVPCamera.dvpSetTriggerDelay(m_handle, m_TriggerDelay);
            }
        }

        private void EnableInCheck()
        {
            if (IsValidHandle(m_handle))
            {
                dvpUserIoInfo UserIoInfo = new dvpUserIoInfo();
                int i = 0;
                dvpStatus status;

                status = DVPCamera.dvpGetUserIoInfo(m_handle, ref UserIoInfo);

                // 先将所有INPUT IO设置为Normal模式
                int nInLength  = 8 < UserIoInfo.inputValid.Length ? 8 : UserIoInfo.inputValid.Length;
                for (i = 0; i < nInLength; i++)
                {
                    if (UserIoInfo.inputValid[i] > 0)
                    {
                        DVPCamera.dvpSetInputIoFunction(m_handle, (dvpInputIo)(dvpInputIo.INPUT_IO_1 + i), dvpInputIoFunction.INPUT_FUNCTION_NORMAL);
                    }
                }

                // 如果使能了ExtTriggerIn，则将选择的InputIo配置为触发输入功能
                if (EnableIn.Checked)
                {
                    int j = InputIOCombo.SelectedIndex;
                    dvpInputIo InputIo = new dvpInputIo();
                    if (j >= 0)
                    {
                        InputIo = (dvpInputIo)(j + dvpInputIo.INPUT_IO_1);
                        DVPCamera.dvpSetInputIoFunction(m_handle, InputIo, dvpInputIoFunction.INPUT_FUNCTION_TRIGGER);
                    }
                }
            }
        }

        private void EnableIn_CheckedChanged(object sender, EventArgs e)
        {
            EnableInCheck();
        }

        private void InputIOCombo_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (IsValidHandle(m_handle))
            {
                // 触发输入IO的改变和勾选触发输入使能是同样的处理过程
                EnableInCheck();
            }
        }

        private void InputSignalTypeCombo_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (IsValidHandle(m_handle))
            {
                dvpTriggerInputType TriggerType = (dvpTriggerInputType)(dvpTriggerInputType.TRIGGER_IN_OFF + InputSignalTypeCombo.SelectedIndex);
                dvpStatus status = DVPCamera.dvpSetTriggerInputType(m_handle, TriggerType);                
            }
        }

        private void OutIOCombo_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (IsValidHandle(m_handle))
            {
                // Strobe输出IO的改变和勾选Strobe输出使能是同样的处理过程
                EnableOutCheck();
            }
        }

        private void OutputSignalType_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (IsValidHandle(m_handle))
            {
                dvpStrobeOutputType StrobeType = (dvpStrobeOutputType)(dvpStrobeOutputType.STROBE_OUT_OFF + OutputSignalType.SelectedIndex);
                dvpStatus status = DVPCamera.dvpSetStrobeOutputType(m_handle, StrobeType);
            }
        }

        private void EnableOutCheck()
        {
            if (IsValidHandle(m_handle))
            {
                dvpUserIoInfo UserIoInfo = new dvpUserIoInfo();
                int i;
                dvpStatus status;

                status = DVPCamera.dvpGetUserIoInfo(m_handle, ref UserIoInfo);

                // 先将所有OUTPUT IO设置为Normal模式
                int nOutLength = 8 < UserIoInfo.outputValid.Length ? 8 : UserIoInfo.outputValid.Length;
                for (i = 0; i < nOutLength; i++)
                {
                    if (UserIoInfo.outputValid[i] > 0)
                    {
                        status = DVPCamera.dvpSetOutputIoFunction(m_handle, (dvpOutputIo)(dvpOutputIo.OUTPUT_IO_1 + i), dvpOutputIoFunction.OUTPUT_FUNCTION_NORMAL);
                    }
                }

                // 如果使能了ExtStrobeOut，则将选择的OutputIo配置为Strobe输出功能
                if (EnableOut.Checked)
                {
                    int j = OutIOCombo.SelectedIndex;
                    dvpOutputIo OutputIo;
                    if (j >= 0)
                    {
                        OutputIo = (dvpOutputIo)(j + dvpOutputIo.OUTPUT_IO_1);
                        status = DVPCamera.dvpSetOutputIoFunction(m_handle, OutputIo, dvpOutputIoFunction.OUTPUT_FUNCTION_STROBE);
                    }
                }
            }
        }

        private void EnableOut_CheckedChanged(object sender, EventArgs e)
        {
            EnableOutCheck();
        }

        private void Trigger_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (IsValidHandle(m_handle))
            {
                dvpStatus status = DVPCamera.dvpClose(m_handle);
                m_handle = 0;
            }
        }

        private void FilterApply_Click(object sender, EventArgs e)
        {
			if (IsValidHandle(m_handle))
			{
				m_TriggerFilter = float.Parse(EditFilter.Text);
				DVPCamera.dvpSetTriggerJitterFilter(m_handle, m_TriggerFilter);
			}			
        }

		private void TriggerLoop_KeyPress(object sender, KeyPressEventArgs e)
		{
			String str ;
			str = TriggerLoop.Text;
			if (e.KeyChar >= '0' && e.KeyChar <= '9')
			{
				 e.Handled = false;
			}
			else if (e.KeyChar == '.' )
			{
				if ( str.Contains('.') )
				{
					e.Handled = true;
				}
				else
				{
					e.Handled = false;
				}
			}
			else if (Char.IsControl(e.KeyChar))
			{
				e.Handled = false;
			}
			else
			{
				e.Handled = true;
			}
		}

		private void TriggerDelay_KeyPress(object sender, KeyPressEventArgs e)
		{
			String str;
			str = TriggerLoop.Text;
			if (e.KeyChar >= '0' && e.KeyChar <= '9')
			{
				e.Handled = false;
			}
			else if (e.KeyChar == '.')
			{
				if (str.Contains('.'))
				{
					e.Handled = true;
				}
				else
				{
					e.Handled = false;
				}
			}
			else if (Char.IsControl(e.KeyChar))
			{
				e.Handled = false;
			}
			else
			{
				e.Handled = true;
			}
		}

		private void EditFilter_KeyPress(object sender, KeyPressEventArgs e)
		{
			String str;
			str = TriggerLoop.Text;
			if (e.KeyChar >= '0' && e.KeyChar <= '9')
			{
				e.Handled = false;
			}
			else if (e.KeyChar == '.')
			{
				if (str.Contains('.'))
				{
					e.Handled = true;
				}
				else
				{
					e.Handled = false;
				}
			}
			else if (Char.IsControl(e.KeyChar))
			{
				e.Handled = false;
			}
			else
			{
				e.Handled = true;
			}
		}
    }
}

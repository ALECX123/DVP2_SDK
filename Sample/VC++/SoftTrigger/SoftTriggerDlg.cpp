
// TriggerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SoftTrigger.h"
#include "SoftTriggerDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// DVP API所依赖的
#ifdef _M_X64
#pragma comment(lib, "../../../library/Visual C++/lib/x64/DVPCamera64.lib")
#else
#pragma comment(lib, "../../../library/Visual C++/lib/x86/DVPCamera.lib")
#endif



// ANSI字符串转UNICODE字符串
std::wstring a2w(LPCCH str)
{
	std::wstring wstr;
	wstr.resize(MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0) - 1);
	MultiByteToWideChar(CP_ACP, 0, str, -1, &wstr[0], wstr.size());
	return wstr;
}

// UNICODE字符串转ANSI字符串
std::string w2a(LPCWCH wstr)
{
	std::string str;
	str.resize(WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL) - 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, &str[0], str.size(), NULL, NULL);
	return str;
}


struct FrameImage
{
	dvpFrame stFrame;
	void *pBuffer;
};
FrameImage *g_lpFrameImage = NULL;

// CSoftTriggerDlg 对话框
// 用于获取视频流的回调函数，尽量不要阻塞
int CSoftTriggerDlg::OnDrawPicture(dvpHandle handle,
	dvpStreamEvent event, 
	void *pContext, 
	dvpFrame *pFrame, 
	void *pBuffer)
{
	if ( pContext == NULL )
		return 0;

	CSoftTriggerDlg *pDlg = ((CSoftTriggerDlg*)pContext);
	pDlg->m_b_read_image_flg = true;
	// 这里只演示了最常见的视频绘图操作，建议回调函数中不宜进行耗时较长的操作，以免影响帧率和图像采集的实时性；
	// 此时获得的图像数据缓存，只在本函数返回前有效，不宜把缓存指针传递出去；但是，用户可以自行申请内存，复制图像数据；
	dvpStatus status = dvpDrawPicture(	pFrame, 
										pBuffer, 
										pDlg->GetDlgItem(IDC_STATIC_PREVIEW)->GetSafeHwnd(),
										nullptr, 
										nullptr);

	if ( pDlg->m_trigger_state == 2  )
	{
		//软件触发图像处理
		//保存触发抓拍的图
		char sz_file_path[MAX_PATH] = {0};
		
		GetModuleFileNameA(theApp.m_hInstance, sz_file_path, sizeof(sz_file_path)); 
		char *lp = strrchr(sz_file_path, '\\');
		strcpy(lp+1, "SoftTrigger.bmp");

		dvpSavePicture(pFrame, pBuffer, sz_file_path, 0);
		pDlg->m_trigger_state = 1;
		//软件触发转化到正常预览模式
		dvpSetTriggerState(pDlg->m_handle, false);
		pDlg->m_trigger_state = 0;

	}

	pDlg->m_b_read_image_flg = false;

	// 返回0，表示图像数据已经可以丢弃，将不再被使用
	return 0;
}


CSoftTriggerDlg::CSoftTriggerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSoftTriggerDlg::IDD, pParent)
	, m_TriggerDelay(0)
	, m_TriggerFilter(0)
	, m_TriggerLoop(0)
{
	m_handle = 0;
	dvpDoubleDescr descrd = {0,};
	m_DelayDescr = m_FilterDescr = m_LoopDescr = descrd;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_b_read_image_flg = false;
	m_trigger_state = 0;//初始化
}


void CSoftTriggerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_INPUT_IO, m_InputIo);
	DDX_Control(pDX, IDC_COMBO_TRIGGER_INPUT_TYPE, m_TriggerInputType);
	DDX_Control(pDX, IDC_COMBO_STROBE_OUTPUT_TYPE, m_StrobeOutputType);	
	DDX_Control(pDX, IDC_COMBO_OUTPUT_IO, m_OutputIo);
	DDX_Text(pDX, IDC_EDIT_TRIGGER_DELAY, m_TriggerDelay);
	DDV_MinMaxDouble(pDX, m_TriggerDelay, m_DelayDescr.fMin, m_DelayDescr.fMax);
	DDX_Text(pDX, IDC_EDIT_TRIGGER_FILTER, m_TriggerFilter);
	DDV_MinMaxDouble(pDX, m_TriggerFilter, m_FilterDescr.fMin, m_FilterDescr.fMax);
	DDX_Text(pDX, IDC_EDIT_TRIGGER_LOOP, m_TriggerLoop);
	DDV_MinMaxDouble(pDX, m_TriggerLoop, m_LoopDescr.fMin, m_LoopDescr.fMax);
	DDX_Control(pDX, IDC_COMBO_DEVICES, m_listDevices);
}

// 集中更新界面上控件
void CSoftTriggerDlg::UpdateControls()
{
	dvpStatus status;
	
 	if (IsValidHandle(m_handle))
	{	
		// 此时已经打开了一个设备

		// 以下更新和使能基本功能的控件
		dvpStreamState state;
		status = dvpGetStreamState(m_handle, &state);
		//ASSERT(status == DVP_STATUS_OK);

		GetDlgItem(IDC_BUTTON_OPEN)->SetWindowTextW(_T("Close"));
		GetDlgItem(IDC_BUTTON_PLAY)->SetWindowText(state == STATE_STARTED ? _T("Stop") : _T("Start"));
		GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_PROPERTY)->EnableWindow(TRUE);


		// 以下使能示例相关功能的控件
		GetDlgItem(IDC_COMBO_INPUT_IO)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_TRIGGER_INPUT_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_STROBE_OUTPUT_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_OUTPUT_IO)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_TRIGGER_FILTER)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_TRIGGER_DELAY)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_TRIGGER_LOOP)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_TRIGGER)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_LOOP)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_TRIG_IN)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_STROBE_OUT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_TRIGGER_FIRE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_APPLY_DELAY)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_APPLY_LOOP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_APPLY_FILTER)->EnableWindow(TRUE);


		// 以下更新触发功能相关的界面
		bool bTrig,bLoop;

		// 触发模式使能状态
		status = dvpGetTriggerState(m_handle, &bTrig);
		if ( status != DVP_STATUS_OK )
		{
			GetDlgItem(IDC_CHECK_TRIGGER)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_TRIGGER_FIRE)->EnableWindow(FALSE);
		}
		else
		{
			GetDlgItem(IDC_CHECK_TRIGGER)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_TRIGGER_FIRE)->EnableWindow(TRUE);
		}
		//禁用触发功能
		((CButton*)GetDlgItem(IDC_CHECK_TRIGGER))->SetCheck((int)bTrig);
		
		
		
		// 循环触发使能状态
		status = dvpGetSoftTriggerLoopState(m_handle, &bLoop);
		//ASSERT(status == DVP_STATUS_OK);
		
		((CButton*)GetDlgItem(IDC_CHECK_LOOP))->SetCheck((int)bLoop);

		// 外部触发输入IO相关状态
		bool bExtTrigIn = FALSE;
		dvpUserIoInfo UserIoInfo;
		dvpInputIoFunction InIoFunc;
		dvpUint32 i;

		// 枚举出所有UserIO，并检查是否有IO用于触发输入功能
		status = dvpGetUserIoInfo(m_handle, &UserIoInfo);
		//ASSERT(status == DVP_STATUS_OK);

		m_InputIo.ResetContent();
		for (i=0; i<8; i++)
		{
			if (UserIoInfo.inputValid[i])
			{
				CString str;
				dvpInputIo InputIo = dvpInputIo(i + INPUT_IO_1);

				// 把IO名称添加到下拉列表中
				str.Format(L"IN_%d", i + 1);
				m_InputIo.AddString(str);
				m_InputIo.SetItemData(i, InputIo);

				// 检查是否有输入IO被设置为触发输入功能
				status = dvpGetInputIoFunction(m_handle, InputIo, &InIoFunc);
				//ASSERT(status == DVP_STATUS_OK);

				if (!bExtTrigIn && InIoFunc == INPUT_FUNCTION_TRIGGER)
				{
					// 找到一个IO已经被设置为触发输入信号
					bExtTrigIn = TRUE;

					// 在下拉列表中选取那个被设置为触发输入功能的IO
					m_InputIo.SetCurSel(i);
				}
			}
		}

		if (bExtTrigIn)
		{
			// 在界面上指示出已经有触发输入信号被使用
			((CButton*)GetDlgItem(IDC_CHECK_TRIG_IN))->SetCheck(1);
		}
		else
		{
			// 没有IO被设置为触发输入，默认在下拉列表中选取第一个
			m_InputIo.SetCurSel(0);

			// 在界面上指示出没有触发输入信号被使用
			((CButton*)GetDlgItem(IDC_CHECK_TRIG_IN))->SetCheck(0);
		}

		// 更新触发输入信号类型列表
		m_TriggerInputType.ResetContent();
		m_TriggerInputType.AddString(_T("Off"));
		m_TriggerInputType.AddString(_T("Falling Edge"));
		m_TriggerInputType.AddString(_T("Low Level"));
		m_TriggerInputType.AddString(_T("Rising Edge"));
		m_TriggerInputType.AddString(_T("High Level"));

		dvpTriggerInputType TriggerType;
		status = dvpGetTriggerInputType(m_handle, &TriggerType);
		//ASSERT(status == DVP_STATUS_OK);

		m_TriggerInputType.SetCurSel(TriggerType);


		// 以下更新Strobe功能相关的界面
		bool bExtStrobeOut = FALSE;
		dvpOutputIoFunction OutIoFunc;

		// 枚举出所有UserIO，并检查是否有IO用于Strobe输出功能
		m_OutputIo.ResetContent();
		for (i=0; i<8; i++)
		{
			if (UserIoInfo.outputValid[i])
			{
				CString str;
				dvpOutputIo OutputIo = dvpOutputIo(i + OUTPUT_IO_1);

				// 把IO名称添加到下拉列表中
				str.Format(L"OUT_%d", i + 1);
				m_OutputIo.AddString(str);
				m_OutputIo.SetItemData(i, OutputIo);

				// 检查是否有输出IO被设置为Strobe输出功能
				status = dvpGetOutputIoFunction(m_handle, OutputIo, &OutIoFunc);
				//ASSERT(status == DVP_STATUS_OK);

				if (!bExtStrobeOut && OutIoFunc == OUTPUT_FUNCTION_STROBE)
				{
					// 找到一个IO已经被设置为strobe输出功能的IO
					bExtStrobeOut = TRUE;

					// 在下拉列表中选取那个被设置为strobe输出功能的IO
					m_OutputIo.SetCurSel(i);

				}
			}
		}

		if (bExtStrobeOut)
		{
			// 在界面上指示出已经有Strobe输出信号被使用
			((CButton*)GetDlgItem(IDC_CHECK_STROBE_OUT))->SetCheck(1);
		}
		else
		{
			// 没有IO被设置为触发输入，默认在下拉列表中选取第一个
			m_OutputIo.SetCurSel(0);

			// 在界面上指示出没有Strobe输出信号被使用
			((CButton*)GetDlgItem(IDC_CHECK_STROBE_OUT))->SetCheck(0);
		}

		// 更新Strobe输出信号类型列表
		m_StrobeOutputType.ResetContent();
		m_StrobeOutputType.AddString(_T("Off"));
		m_StrobeOutputType.AddString(_T("Low Level"));
		m_StrobeOutputType.AddString(_T("High Level"));

		//获取Strobe信号类型
		dvpStrobeOutputType StrobeType;
		status = dvpGetStrobeOutputType(m_handle, &StrobeType);
		//ASSERT(status == DVP_STATUS_OK);

		m_StrobeOutputType.SetCurSel(StrobeType);


		// 以下这些获取的描述信息将用于更新编辑框中设置值的范围
		status = dvpGetTriggerDelayDescr(m_handle, &m_DelayDescr);
		//ASSERT(status == DVP_STATUS_OK);

		status = dvpGetTriggerJitterFilterDescr(m_handle, &m_FilterDescr);
		//ASSERT(status == DVP_STATUS_OK);

		status = dvpGetSoftTriggerLoopDescr(m_handle, &m_LoopDescr);
		//ASSERT(status == DVP_STATUS_OK);

		// 以下更新编辑框中的设置值
		status = dvpGetSoftTriggerLoop(m_handle, &m_TriggerLoop);
		//ASSERT(status == DVP_STATUS_OK);

		status = dvpGetTriggerDelay(m_handle, &m_TriggerDelay);
		//ASSERT(status == DVP_STATUS_OK);

		status = dvpGetTriggerJitterFilter(m_handle, &m_TriggerFilter);
		//ASSERT(status == DVP_STATUS_OK);

		UpdateData(FALSE);
	}
	else
	{
		// 此时还没有设备被打开
		// 更新基本功能控件
		GetDlgItem(IDC_BUTTON_OPEN)->SetWindowTextW(_T("Open"));
		GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PROPERTY)->EnableWindow(FALSE);

		if (m_listDevices.GetCount() == 0)
		{
			// 没有设备存在
			GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(FALSE);
		}
		else
		{
			GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(TRUE);
		}


		// 更新本示例相关功能的控件
		GetDlgItem(IDC_COMBO_INPUT_IO)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_TRIGGER_INPUT_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_STROBE_OUTPUT_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_OUTPUT_IO)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_TRIGGER_FILTER)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_TRIGGER_DELAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_TRIGGER_LOOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_TRIGGER)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_LOOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_TRIG_IN)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_STROBE_OUT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_TRIGGER_FIRE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_APPLY_DELAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_APPLY_LOOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_APPLY_FILTER)->EnableWindow(FALSE);
	}

	SendMessage(WM_SIZE);
}


BEGIN_MESSAGE_MAP(CSoftTriggerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CSoftTriggerDlg::OnBnClickedButtonOpen)
	ON_CBN_SELCHANGE(IDC_COMBO_INPUT_IO, &CSoftTriggerDlg::OnCbnSelchangeComboInputIo)
	ON_CBN_SELCHANGE(IDC_COMBO_TRIGGER_INPUT_TYPE, &CSoftTriggerDlg::OnCbnSelchangeComboTriggerInputType)
	ON_BN_CLICKED(IDC_BUTTON_PROPERTY, &CSoftTriggerDlg::OnBnClickedButtonProperty)
	ON_CBN_SELCHANGE(IDC_COMBO_OUTPUT_IO, &CSoftTriggerDlg::OnCbnSelchangeComboOutputIo)
	ON_BN_CLICKED(IDC_BUTTON_TRIGGER_FIRE, &CSoftTriggerDlg::OnBnClickedButtonTriggerFire)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CSoftTriggerDlg::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_CHECK_LOOP, &CSoftTriggerDlg::OnBnClickedCheckLoop)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_CHECK_TRIGGER, &CSoftTriggerDlg::OnBnClickedCheckTrigger)
	ON_CBN_SELCHANGE(IDC_COMBO_STROBE_OUTPUT_TYPE, &CSoftTriggerDlg::OnCbnSelchangeComboStrobeOutputType)
	ON_BN_CLICKED(IDC_BUTTON_SCAN, &CSoftTriggerDlg::OnBnClickedButtonScan)
	ON_BN_CLICKED(IDC_BUTTON_APPLY_LOOP, &CSoftTriggerDlg::OnBnClickedButtonApplyLoop)
	ON_BN_CLICKED(IDC_BUTTON_APPLY_DELAY, &CSoftTriggerDlg::OnBnClickedButtonApplyDelay)
	ON_BN_CLICKED(IDC_CHECK_TRIG_IN, &CSoftTriggerDlg::OnBnClickedCheckTrigIn)
	ON_BN_CLICKED(IDC_CHECK_STROBE_OUT, &CSoftTriggerDlg::OnBnClickedCheckStrobeOut)
END_MESSAGE_MAP()


BOOL CSoftTriggerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	
	// 预先扫描出已经连接的设备
	OnBnClickedButtonScan();

	// 定时器用于更新当前帧率信息
	SetTimer(0, 500, NULL);

	return TRUE; 
}


void CSoftTriggerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


HCURSOR CSoftTriggerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSoftTriggerDlg::OnBnClickedButtonTriggerFire()
{
	if (IsValidHandle(m_handle))
	{
		// 这个函数执行一次，相当于产生一次外触发
		// 注意：如果曝光时间较长时，过快的点击"Soft Trigger Fire"有可能导致触发失败，因为上一帧还可能出于曝光或未输出完的状态
		dvpStatus status = dvpTriggerFire(m_handle);
		//ASSERT(status == DVP_STATUS_OK);
	}
}

void CSoftTriggerDlg::OnOK()
{
	if (IsValidHandle(m_handle))
	{
		// 点"OK"退出，将进行配置参数的存档操作，如果不指定路径，存档的目录一般为:C:\ProgramData\DO3THINK\DVP2
		dvpStatus status = dvpSaveConfig(m_handle, NULL);
		//ASSERT(status == DVP_STATUS_OK);
	}

	CDialogEx::OnOK();
}

void CSoftTriggerDlg::OnBnClickedCheckTrigger()
{
	if (IsValidHandle(m_handle))
	{
		// 使能/禁用触发模式
		dvpStatus status = dvpSetTriggerState(m_handle, ((CButton*)GetDlgItem(IDC_CHECK_TRIGGER))->GetCheck() ? true : false);
		//ASSERT(status == DVP_STATUS_OK);

		UpdateControls();
	}
}

void CSoftTriggerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// 界面结束的时候，同时关闭设备
	if (IsValidHandle(m_handle))
	{
		dvpStatus status = dvpClose(m_handle);
		//ASSERT(status == DVP_STATUS_OK);
		m_handle= 0;
	}
}

void CSoftTriggerDlg::OnTimer(UINT_PTR nIDEvent)
{
	
	if (nIDEvent == 0)
	{
		if (IsValidHandle(m_handle))
		{
			// 更新帧率信息
			dvpFrameCount count;
			dvpStatus status = dvpGetFrameCount(m_handle, &count);
			//ASSERT(status == DVP_STATUS_OK);
			
			CString str;
			str.Format(_T("%s [%d frames, %.3f fps]"),m_strFriendlyName,count.uFrameCount,count.fFrameRate);
			SetWindowText(str);
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CSoftTriggerDlg::OnBnClickedCheckLoop()
{
	bool bLoop = ((CButton*)GetDlgItem(IDC_CHECK_LOOP))->GetCheck() ? true : false;

	dvpStatus status = dvpSetSoftTriggerLoopState(m_handle, bLoop);
	//ASSERT(status == DVP_STATUS_OK);
}

void CSoftTriggerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// 根据窗体大小，自动调节视频绘图窗口
	if (IsValidHandle(m_handle))
	{
		dvpRegion roi;
		dvpStatus status = dvpGetRoi(m_handle, &roi);

		CRect rc, rcPreview, rcOld;
		GetDlgItem(IDC_STATIC_PREVIEW)->GetWindowRect(rcOld);
		ScreenToClient(rcOld);

		GetClientRect(rc);
		rc.left += rcOld.left;
		rc.right -= 6;
		rc.top += rcOld.top;
		rc.bottom -= 6;

		rcPreview.SetRect(0, 0, roi.W, roi.H);

		if(rc.Width() * rcPreview.Height() > 
			rc.Height() * rcPreview.Width())
		{
			rcPreview.SetRect(
				0,
				0,
				rc.Height() * roi.W / roi.H, 
				rc.Height());
		}
		else
		{
			rcPreview.SetRect(
				0, 
				0,
				rc.Width(),
				rc.Width() * roi.H / roi.W);
		}

		rcPreview.MoveToXY(rc.TopLeft());

		GetDlgItem(IDC_STATIC_PREVIEW)->MoveWindow(rcPreview);
	}
}

void CSoftTriggerDlg::OnBnClickedButtonScan()
{
	dvpStatus status;
	dvpUint32 i,n=0;
	dvpCameraInfo info = {0};

	// 此时，n为成功枚举到的相机数量，将添加到下拉列表中，下拉列表中的内容为每个相机的FriendlyName
	m_listDevices.ResetContent();

	// 获得当前能连接的相机数量
	status = dvpRefresh(&n);
	//ASSERT(status == DVP_STATUS_OK);
	
	if (status == DVP_STATUS_OK)
	{
		// 枚举最多16台相机
		if (n>16)
			n = 16;

		for (i=0; i<n; i++)
		{
			// 逐个枚举出每个相机的信息
			status = dvpEnum(i, &info);
			//ASSERT(status == DVP_STATUS_OK);

			if (status == DVP_STATUS_OK)
			{
				// 界面使用的是UNICODE，枚举的设备信息为ANSI字符串，需要将ANSI转UNICODE
				m_listDevices.AddString(a2w(info.FriendlyName).c_str());
			}
		}

		if (i != 0)
		{
			m_listDevices.SetCurSel(0);
		}

		UpdateControls();

	}
}

void CSoftTriggerDlg::OnBnClickedButtonOpen()
{
	dvpStatus status = DVP_STATUS_OK;
	CString strName;

	if (!IsValidHandle(m_handle))
	{
		m_listDevices.GetWindowText(strName);
		if (strName != "")
		{
			// 通过枚举到并选择的FriendlyName打开指定设备
			status = dvpOpenByName(w2a(strName).c_str(), OPEN_NORMAL, &m_handle);
			//ASSERT(status == DVP_STATUS_OK);

			if(status != DVP_STATUS_OK)
			{
				MessageBox(_T("打开失败"));
			}
			else
			{
				m_strFriendlyName = strName;	

				// 如果需要图像显示，可以注册回调函数，在回调函数中完成绘图操作
				// 注意：回调函数中执行的绘图操作，可能会对dvpGetFrame接口获取的图像数据造成延时
				dvpRegisterStreamCallback(m_handle, OnDrawPicture, STREAM_EVENT_PROCESSED, this);
			}
		}
	}
	else
	{
		status = dvpClose(m_handle);
		//ASSERT(status == DVP_STATUS_OK);
		m_handle= 0;
		GetDlgItem(IDC_STATIC_PREVIEW)->InvalidateRect(NULL);
	}

	UpdateControls();
}


void CSoftTriggerDlg::OnBnClickedButtonPlay()
{
	if (IsValidHandle(m_handle))
	{
		dvpStreamState state;
		dvpStatus status;

		// 根据当前视频状态，执行相反的操作，实现一个按钮既能启动又能停止
		status = dvpGetStreamState(m_handle, &state);
		//ASSERT(status == DVP_STATUS_OK);

		if (state == STATE_STARTED)
		{
			status = dvpStop(m_handle);
		}
		else
		{
			status = dvpStart(m_handle);
		}

		//ASSERT(status == DVP_STATUS_OK);
	}

	UpdateControls();
}

void CSoftTriggerDlg::OnBnClickedButtonProperty()
{
	if (IsValidHandle(m_handle))
	{
		dvpStatus status = dvpShowPropertyModalDialog(m_handle, GetSafeHwnd());

		// 此时一些配置可能发生改变，将同步到界面
		UpdateControls();
	}
}

void CSoftTriggerDlg::OnBnClickedButtonApplyLoop()
{
	if (IsValidHandle(m_handle))
	{
		UpdateData();
		
		dvpStatus status = dvpSetSoftTriggerLoop(m_handle, m_TriggerLoop);
		//ASSERT(status == DVP_STATUS_OK);
	}
}

void CSoftTriggerDlg::OnBnClickedButtonApplyDelay()
{
	if (IsValidHandle(m_handle))
	{
		UpdateData();

		dvpStatus status = dvpSetTriggerDelay(m_handle, m_TriggerDelay);
		//ASSERT(status == DVP_STATUS_OK);
	}
}


void CSoftTriggerDlg::OnBnClickedCheckTrigIn()
{
	if (IsValidHandle(m_handle))
	{
		dvpUserIoInfo UserIoInfo;
		dvpUint32 i;
		dvpStatus status;

		status = dvpGetUserIoInfo(m_handle, &UserIoInfo);
		//ASSERT(status == DVP_STATUS_OK);

		// 先将所有INPUT IO设置为Normal模式
		for (i=0; i<8; i++)
		{
			if (UserIoInfo.inputValid[i])
			{
				dvpSetInputIoFunction(m_handle, dvpInputIo(INPUT_IO_1+i), INPUT_FUNCTION_NORMAL);
				//ASSERT(status == DVP_STATUS_OK);
			}
		}

		// 如果使能了ExtTriggerIn，则将选择的InputIo配置为触发输入功能
		if (((CButton*)GetDlgItem(IDC_CHECK_TRIG_IN))->GetCheck())
		{
			int j = m_InputIo.GetCurSel();
			dvpInputIo InputIo;
			if (j >= 0)
			{
				InputIo = dvpInputIo(m_InputIo.GetItemData(j));
				dvpSetInputIoFunction(m_handle, InputIo, INPUT_FUNCTION_TRIGGER);
				//ASSERT(status == DVP_STATUS_OK);
			}
		}
	}
}


void CSoftTriggerDlg::OnBnClickedCheckStrobeOut()
{
	if (IsValidHandle(m_handle))
	{
		dvpUserIoInfo UserIoInfo;
		dvpUint32 i;
		dvpStatus status;

		status = dvpGetUserIoInfo(m_handle, &UserIoInfo);
		//ASSERT(status == DVP_STATUS_OK);

		// 先将所有OUTPUT IO设置为Normal模式
		for (i=0; i<8; i++)
		{
			if (UserIoInfo.outputValid[i])
			{
				status = dvpSetOutputIoFunction(m_handle, dvpOutputIo(OUTPUT_IO_1+i), OUTPUT_FUNCTION_NORMAL);
				//ASSERT(status == DVP_STATUS_OK);
			}
		}

		// 如果使能了ExtStrobeOut，则将选择的OutputIo配置为Strobe输出功能
		if (((CButton*)GetDlgItem(IDC_CHECK_STROBE_OUT))->GetCheck())
		{
			int j = m_OutputIo.GetCurSel();
			dvpOutputIo OutputIo;
			if (j >= 0)
			{
				OutputIo = dvpOutputIo(m_OutputIo.GetItemData(j));
				status = dvpSetOutputIoFunction(m_handle, OutputIo, OUTPUT_FUNCTION_STROBE);
				//ASSERT(status == DVP_STATUS_OK);
			}
		}
	}
}

void CSoftTriggerDlg::OnCbnSelchangeComboInputIo()
{
	if (IsValidHandle(m_handle))
	{
		// 触发输入IO的改变和勾选触发输入使能是同样的处理过程
		OnBnClickedCheckTrigIn();
	}
}

void CSoftTriggerDlg::OnCbnSelchangeComboOutputIo()
{
	if (IsValidHandle(m_handle))
	{
		// Strobe输出IO的改变和勾选Strobe输出使能是同样的处理过程
		OnBnClickedCheckStrobeOut();
	}
}

void CSoftTriggerDlg::OnCbnSelchangeComboTriggerInputType()
{
	if (IsValidHandle(m_handle))
	{
		dvpTriggerInputType TriggerType = (dvpTriggerInputType)(TRIGGER_IN_OFF + m_TriggerInputType.GetCurSel());
		dvpStatus status = dvpSetTriggerInputType(m_handle, TriggerType);
		//ASSERT(status == DVP_STATUS_OK);
	}
}

void CSoftTriggerDlg::OnCbnSelchangeComboStrobeOutputType()
{
	if (IsValidHandle(m_handle))
	{
		dvpStrobeOutputType StrobeType = (dvpStrobeOutputType)(STROBE_OUT_OFF + m_StrobeOutputType.GetCurSel());
		dvpStatus status = dvpSetStrobeOutputType(m_handle, StrobeType);
		//ASSERT(status == DVP_STATUS_OK);
	}
}

//普通模式转化到软件触发
void CSoftTriggerDlg::OnBnClickedSofttriggerPreview()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IsValidHandle(m_handle) && m_trigger_state == 0)
	{
		bool bTrig = false;
		dvpStatus status = dvpGetTriggerState(m_handle, &bTrig);
		if ( status == DVP_STATUS_OK )
		{
			status = dvpSetTriggerState(m_handle, true);
			if ( status == DVP_STATUS_OK )
			{
				//设置为触发模式
				m_trigger_state = 1; 

				//等待当前帧数据处理完
				while ( m_b_read_image_flg )
				{
					Sleep(1);
				}
				
				// 这个函数执行一次，相当于产生一次外触发
				// 注意：如果曝光时间较长时，过快的点击"Soft Trigger Fire"有可能导致触发失败，因为上一帧还可能出于曝光或未输出完的状态
				status = dvpTriggerFire(m_handle);
				if ( status == DVP_STATUS_OK )
				{
					m_trigger_state = 2; //发送触发信号成功
				}
				
			}
			
			
		}

	}
}

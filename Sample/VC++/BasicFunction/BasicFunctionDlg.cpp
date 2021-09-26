
// BasicFunctionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BasicFunction.h"
#include "BasicFunctionDlg.h"
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

// CBasicFunctionDlg 对话框

// 用于获取视频流的回调函数
int CBasicFunctionDlg::OnDrawPicture(dvpHandle handle,
	dvpStreamEvent event, 
	void *pContext, 
	dvpFrame *pFrame, 
	void *pBuffer)
{
	CBasicFunctionDlg *pDlg = ((CBasicFunctionDlg*)pContext);

	// 这里只演示了最常见的视频绘图操作，建议回调函数中不宜进行耗时较长的操作，以免影响帧率和图像采集的实时性；
	// 此时获得的图像数据缓存，只在本函数返回前有效，不宜把缓存指针传递出去；但是，用户可以自行申请内存，复制图像数据；
	
	dvpStatus status = dvpDrawPicture(	pFrame, 
		pBuffer, 
		pDlg->GetDlgItem(IDC_STATIC_PREVIEW)->GetSafeHwnd(),
		nullptr, 
		nullptr);

	// 返回0，表示图像数据已经可以丢弃，将不再被使用
	return 0;
}


CBasicFunctionDlg::CBasicFunctionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBasicFunctionDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bAeOp = FALSE;
}

void CBasicFunctionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DEVICES, m_listDevices);
	DDX_Check(pDX, IDC_CHECK_AEENABLE, m_bAeOp);
}

BEGIN_MESSAGE_MAP(CBasicFunctionDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SCAN, &CBasicFunctionDlg::OnBnClickedButtonScan)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CBasicFunctionDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_START, &CBasicFunctionDlg::OnBnClickedButtonStart)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_EXPOSURE_TIME, &CBasicFunctionDlg::OnNMCustomdrawSliderExposureTime)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_GAIN, &CBasicFunctionDlg::OnNMCustomdrawSliderExposureGain)
	ON_CBN_SELCHANGE(IDC_COMBO_RESOLUTION, &CBasicFunctionDlg::OnCbnSelchangeComboResolution)
	ON_BN_CLICKED(IDC_BUTTON_PROPERTY, &CBasicFunctionDlg::OnBnClickedButtonProperty)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CBasicFunctionDlg::OnBnClickedButtonSave)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO_AE_MODE, &CBasicFunctionDlg::OnCbnSelchangeComboAeMode)
	ON_CBN_SELCHANGE(IDC_COMBO_FLICK, &CBasicFunctionDlg::OnCbnSelchangeComboFlick)
	ON_BN_CLICKED(IDC_CHECK_AEOPERATION, &CBasicFunctionDlg::OnBnClickedCheckAeoperation)
END_MESSAGE_MAP()


// CBasicFunctionDlg 消息处理程序

BOOL CBasicFunctionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 预先扫描出已经连接的设备
	OnBnClickedButtonScan();

	SetTimer(0, 500, NULL);
	return TRUE;  
}

void CBasicFunctionDlg::OnPaint()
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


void CBasicFunctionDlg::OnSize(UINT nType, int cx, int cy)
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

void CBasicFunctionDlg::OnTimer(UINT_PTR nIDEvent)
{

	if (nIDEvent == 0)
	{
		if (IsValidHandle(m_handle))
		{
			// 更新帧率信息
			dvpFrameCount count;
			dvpStatus status = dvpGetFrameCount(m_handle, &count);
            ASSERT(status == DVP_STATUS_OK);

			CString str;
			str.Format(_T("%s [%d frames, %.3f fps]"),m_strFriendlyName,count.uFrameCount,count.fFrameRate);
			SetWindowText(str);
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CBasicFunctionDlg::OnOK()
{
	if (IsValidHandle(m_handle))
	{
		// 点"OK"退出，将进行配置参数的存档操作，如果不指定路径，存档的目录一般为:C:\ProgramData\DO3THINK\DVP2
		dvpStatus status = dvpSaveConfig(m_handle, NULL);
        ASSERT(status == DVP_STATUS_OK);
	}

	CDialogEx::OnOK();
}

HCURSOR CBasicFunctionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBasicFunctionDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// 界面结束的时候，同时关闭设备
	if (IsValidHandle(m_handle))
	{
		dvpClose(m_handle);
		m_handle= 0;
	}
}

void CBasicFunctionDlg::UpdateControls()
{
	dvpStatus status;
	if (IsValidHandle(m_handle))
	{
		// 此时已经打开了一个设备
		// 更新基本功能控件
		dvpStreamState state;
		status = dvpGetStreamState(m_handle, &state);
        ASSERT(status == DVP_STATUS_OK);

		GetDlgItem(IDC_BUTTON_START)->SetWindowText(state == STATE_STARTED ? _T("Stop") : _T("Start"));
		GetDlgItem(IDC_BUTTON_OPEN)->SetWindowTextW(_T("Close"));
	    GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_PROPERTY)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(TRUE);

		// 以下更新示例相关功能控件
		GetDlgItem(IDC_COMBO_RESOLUTION)->EnableWindow(TRUE);
	    GetDlgItem(IDC_COMBO_AE_MODE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_FLICK)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_AEENABLE)->EnableWindow(TRUE);

		// 更新自动曝光操作控件
		dvpAeOperation AeOp;
        dvpAeMode AeMode;

		status = dvpGetAeOperation(m_handle,&AeOp);
        ASSERT(status == DVP_STATUS_OK);

        status = dvpGetAeMode(m_handle, &AeMode);
        ASSERT(status == DVP_STATUS_OK);

 
        if (AeOp == AE_OP_OFF)
        {
            m_bAeOp = FALSE;
            UpdateData(FALSE);
            GetDlgItem(IDC_SLIDER_EXPOSURE_TIME)->EnableWindow(TRUE);
            GetDlgItem(IDC_SLIDER_GAIN)->EnableWindow(TRUE);
        }
        else if (AeOp == AE_OP_CONTINUOUS || AeOp == AE_OP_ONCE)
        {		
            m_bAeOp = TRUE;
            UpdateData(FALSE);
            GetDlgItem(IDC_SLIDER_EXPOSURE_TIME)->EnableWindow(AeMode == AE_MODE_AG_ONLY);                
            GetDlgItem(IDC_SLIDER_GAIN)->EnableWindow(AeMode == AE_MODE_AE_ONLY);

        }
		
		// 获取自动曝光模式并更新自动曝光模式设置控件、使能曝光时间和模拟增益调节的控件
		((CComboBox*)GetDlgItem(IDC_COMBO_AE_MODE))->SetCurSel(AeMode);

		// 更新抗频闪设置控件
		dvpAntiFlick AntiFlick;
		status = dvpGetAntiFlick(m_handle, &AntiFlick);
        ASSERT(status == DVP_STATUS_OK);
        ((CComboBox*)GetDlgItem(IDC_COMBO_FLICK))->SetCurSel(AntiFlick);

		// 更新曝光时间
		double fExpoTime;
		CString strExpoTime;
		status = dvpGetExposure(m_handle,&fExpoTime);
        ASSERT(status == DVP_STATUS_OK);
		strExpoTime.Format(_T("%5f"),fExpoTime);					 
		SetDlgItemText(IDC_STATIC_EXPOTIME,strExpoTime);
		 
		// 更新增益
		CString strGain;
		float fGain;
		status = dvpGetAnalogGain(m_handle,&fGain);
        ASSERT(status == DVP_STATUS_OK);
		strGain.Format(_T("%1.2f"),fGain);				
		SetDlgItemText(IDC_STATIC_EXPOGAIN,strGain);

		// 更新分辨率
		dvpUint32 QRoiSel;
		status = dvpGetQuickRoiSel(m_handle, &QRoiSel);
		ASSERT(status == DVP_STATUS_OK);
		((CComboBox*)GetDlgItem(IDC_COMBO_RESOLUTION))->SetCurSel(QRoiSel);
	
        // 更新曝光时间和增益的当前设置值
        UpdateControlExposure();
        UpdateControlGain();
	}
	else
	{
		// 此时设备还没有被打开
		// 更新基本功能控件
		GetDlgItem(IDC_BUTTON_OPEN)->SetWindowTextW(_T("Open"));	
		GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PROPERTY)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);

		if (m_listDevices.GetCount() == 0)
		{
			// 没有设备存在
			GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(FALSE);
		}
		else
		{
			GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(TRUE);
		}

		GetDlgItem(IDC_SLIDER_EXPOSURE_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLIDER_GAIN)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_RESOLUTION)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_AE_MODE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_FLICK)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_PREVIEW)->InvalidateRect(NULL);
	}
	SendMessage(WM_SIZE);
}

void CBasicFunctionDlg::UpdateControlExposure()
{
	double fExpoTime;
	CString strValue;
	dvpDoubleDescr ExpoTimeDescr;
    dvpStatus status;

	// 获取曝光时间的描述信息
    status = dvpGetExposureDescr(m_handle, &ExpoTimeDescr);
    ASSERT(status == DVP_STATUS_OK);
	if (status == DVP_STATUS_OK)
	{
		// 设置曝光时间拖动条的范围
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER_EXPOSURE_TIME))->SetRange(static_cast<int>(ExpoTimeDescr.fMin),static_cast<int>(ExpoTimeDescr.fMax));//单位us
	}


	// 获取曝光时间的初值
    status = dvpGetExposure(m_handle, &fExpoTime);
    ASSERT(status == DVP_STATUS_OK);
	if (status == DVP_STATUS_OK)
	{
		// 设置曝光时间拖动条初始值
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER_EXPOSURE_TIME))->SetPos((int)(fExpoTime));
		strValue.Format(_T("%.3f"),fExpoTime);
		SetDlgItemText(IDC_STATIC_EXPOTIME,strValue);
	}
}

void CBasicFunctionDlg::UpdateControlGain()
{
	dvpStatus  status;
	float fAnalogGain;
	CString strValue;
	dvpFloatDescr AnalogGainDescr;

    // 获取模拟增益的描述信息
    status = dvpGetAnalogGainDescr(m_handle,&AnalogGainDescr);
    ASSERT(status == DVP_STATUS_OK);
    if (status == DVP_STATUS_OK)
    {
        // 设置模拟增益拖动条的范围
        ((CSliderCtrl*)GetDlgItem(IDC_SLIDER_GAIN))->SetRange(static_cast<int>(AnalogGainDescr.fMin*100),static_cast<int>(AnalogGainDescr.fMax*100));//单位x
    }

    // 获取模拟增益并设置模拟增益的初始值
    status = dvpGetAnalogGain(m_handle, &fAnalogGain);
    ASSERT(status == DVP_STATUS_OK);
    if (status == DVP_STATUS_OK)
    {
        // 设置增益拖动条初始值
        ((CSliderCtrl*)GetDlgItem(IDC_SLIDER_GAIN))->SetPos((int)(fAnalogGain*100));
        strValue.Format(_T("%1.3f%s"),fAnalogGain,"x");
        SetDlgItemText(IDC_STATIC_EXPOGAIN,strValue);
    }

}

void CBasicFunctionDlg:: OnInitControlResolution()
{
	dvpUint32 QuickRoiSel = 0;
	dvpQuickRoi QuickRoiDetail;
	dvpStatus status; 
	dvpSelectionDescr QuickRoiDescr;

	((CComboBox*)(GetDlgItem(IDC_COMBO_RESOLUTION)))->ResetContent();

	// 获取相机分辨率索引号
	status = dvpGetQuickRoiSelDescr(m_handle, &QuickRoiDescr);
    ASSERT(status == DVP_STATUS_OK);
	if (status == DVP_STATUS_OK)
	{
		for (UINT iNum = 0; iNum<QuickRoiDescr.uCount; iNum++)
		{
			status = dvpGetQuickRoiSelDetail(m_handle,iNum, &QuickRoiDetail);
            ASSERT(status == DVP_STATUS_OK);
			if (status == DVP_STATUS_OK)
			{			
				((CComboBox*)GetDlgItem(IDC_COMBO_RESOLUTION))->InsertString(iNum,a2w(QuickRoiDetail.selection.string).c_str());
			}
		}
	}

	// 获取分辨率模式索引
	status = dvpGetResolutionModeSel(m_handle,&QuickRoiSel);
    ASSERT(status == DVP_STATUS_OK);
	if (status == DVP_STATUS_OK)
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_RESOLUTION))->SetCurSel(QuickRoiSel);
	}
}

void CBasicFunctionDlg:: OnInitControlAeMode()
{
	((CComboBox*)(GetDlgItem(IDC_COMBO_AE_MODE)))->ResetContent();
	
	if (IsValidHandle(m_handle))
	{
		// 插入自动曝光模式索引
		((CComboBox*)GetDlgItem(IDC_COMBO_AE_MODE))->InsertString(0,a2w("AE_MODE_AE_AG").c_str());
		((CComboBox*)GetDlgItem(IDC_COMBO_AE_MODE))->InsertString(1,a2w("AE_MODE_AG_AE").c_str());
		((CComboBox*)GetDlgItem(IDC_COMBO_AE_MODE))->InsertString(2,a2w("AE_MODE_AE_ONLY").c_str());	
		((CComboBox*)GetDlgItem(IDC_COMBO_AE_MODE))->InsertString(3,a2w("AE_MODE_AG_ONLY").c_str());

		// 设置当前的自动曝光模式
		((CComboBox*)GetDlgItem(IDC_COMBO_AE_MODE))->SetCurSel(3);	
	}
}

void CBasicFunctionDlg:: OnInitControlFlick()
{
	((CComboBox*)(GetDlgItem(IDC_COMBO_FLICK)))->ResetContent();
	if (IsValidHandle(m_handle))
	{
		// 插入频闪设置索引
		((CComboBox*)GetDlgItem(IDC_COMBO_FLICK))->InsertString(0,a2w("ANTIFLICK_DISABLE").c_str());
		((CComboBox*)GetDlgItem(IDC_COMBO_FLICK))->InsertString(1,a2w("ANTIFLICK_50HZ").c_str());
		((CComboBox*)GetDlgItem(IDC_COMBO_FLICK))->InsertString(2,a2w("ANTIFLICK_60HZ").c_str());	

		// 设置当前的频闪状态
		((CComboBox*)GetDlgItem(IDC_COMBO_FLICK))->SetCurSel(2);
	}
}

void CBasicFunctionDlg::OnBnClickedButtonScan()
{
	dvpStatus status;
	dvpUint32 i,n = 0;
	//dvpCameraInfo *p_ingo = new dvpCameraInfo[16];
	//dvpCameraInfo info[16];
	dvpCameraInfo info = {0};
	// 此时，n为成功枚举到的相机数量，将添加到下拉列表中，下拉列表中的内容为每个相机的FriendlyName
	m_listDevices.ResetContent();


	// 获得当前能连接的相机数量
	status = dvpRefresh(&n);
    ASSERT(status == DVP_STATUS_OK);

    if (status == DVP_STATUS_OK)
    {
	    // 枚举最多16台相机
	    if (n>16)
		    n = 16;

	    for (i=0; i<n; i++)
	    {
		    // 逐个枚举出每个相机的信息
		    status = dvpEnum(i, &info);
            ASSERT(status == DVP_STATUS_OK);

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

	//delete p_ingo;
	//p_ingo = NULL;
}


void CBasicFunctionDlg::OnBnClickedButtonOpen()
{
	dvpStatus status;
	CString strName;

	if (!IsValidHandle(m_handle))
	{
		m_listDevices.GetWindowText(strName);
		if (strName != "")
		{
			// 通过枚举到并选择的FriendlyName打开指定设备
			status = dvpOpenByName(w2a(strName).c_str(), OPEN_NORMAL, &m_handle);
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

				// 初始化曝光时间、增益、分辨率和自动曝光模式
				OnInitControlResolution();
				OnInitControlAeMode();
				OnInitControlFlick();

				UpdateControlExposure();
				UpdateControlGain();

			}
		}
	}
	else
	{
		status = dvpClose(m_handle);
        ASSERT(status == DVP_STATUS_OK);
		m_handle = 0;
		GetDlgItem(IDC_STATIC_PREVIEW)->InvalidateRect(NULL);
	}

	UpdateControls();
}


void CBasicFunctionDlg::OnBnClickedButtonStart()
{
	dvpStreamState state;
	dvpStatus status;

	if (IsValidHandle(m_handle))
	{
		// 根据当前视频状态，执行相反的操作，实现一个按钮既能启动又能停止
		status = dvpGetStreamState(m_handle, &state);
		ASSERT(status == DVP_STATUS_OK);

		if (state == STATE_STARTED)
		{
			status = dvpStop(m_handle);
		}
		else
		{
			status = dvpStart(m_handle);
		}

        ASSERT(status == DVP_STATUS_OK);
	}

	UpdateControls();
}


void CBasicFunctionDlg::OnNMCustomdrawSliderExposureTime(NMHDR *pNMHDR, LRESULT *pResult)
{
	CString strExpoTime;
	double  fExpoTime;
    dvpDoubleDescr ExpDescr;
    
    dvpStatus status;
    

    if (IsValidHandle(m_handle))
    {
	    // 获取所设置的曝光时间拖动条的值
	    fExpoTime = ((CSliderCtrl*)GetDlgItem(IDC_SLIDER_EXPOSURE_TIME))->GetPos();

	    // 设置曝光时间
        // 获取曝光时间的范围，避免设置值超出范围
        status = dvpGetExposureDescr(m_handle, &ExpDescr);
        ASSERT(status == DVP_STATUS_OK);

        if (fExpoTime > ExpDescr.fMax)
            fExpoTime = ExpDescr.fMax;

        if (fExpoTime < ExpDescr.fMin)
            fExpoTime = ExpDescr.fMin;

        // 先设置曝光时间
        status = dvpSetExposure(m_handle,fExpoTime);
        ASSERT(status == DVP_STATUS_OK);

        // 再获取曝光时间，由于调节精度(步进值)的问题，获取值可能与设置值有些差异，以获取值为准
        status = dvpSetExposure(m_handle,fExpoTime);
        ASSERT(status == DVP_STATUS_OK);

	    // 设置曝光时间文本
	    strExpoTime.Format(_T("%.3f"),fExpoTime);					
	    SetDlgItemText(IDC_STATIC_EXPOTIME,strExpoTime);
    }

	*pResult = 0;
}


void CBasicFunctionDlg::OnNMCustomdrawSliderExposureGain(NMHDR *pNMHDR, LRESULT *pResult)
{
	CString strGain;
	float fGain;
    dvpStatus status;

    if (IsValidHandle(m_handle))
    {
	    // 获取所设置的模拟增益拖动条值
	    fGain = static_cast<float>(((CSliderCtrl*)GetDlgItem(IDC_SLIDER_GAIN))->GetPos()) / 100;

        // 先设置增益值
        status = dvpSetAnalogGain(m_handle,fGain);
        ASSERT(status == DVP_STATUS_OK);

        // 再获取增益值，由于调节精度(步进值)的问题，获取值可能与设置值有些差异，以获取值为准
        status = dvpGetAnalogGain(m_handle, &fGain);
        ASSERT(status == DVP_STATUS_OK);

	    // 设置模拟增益文本
	    strGain.Format(_T("%1.3f%s"),fGain,"x");				
	    SetDlgItemText(IDC_STATIC_EXPOGAIN, strGain);
    }

	*pResult = 0;
}


void CBasicFunctionDlg::OnCbnSelchangeComboResolution()
{
	dvpStatus status;

	// 获取分辨率选择索引
	int iSel = ((CComboBox*)GetDlgItem(IDC_COMBO_RESOLUTION))->GetCurSel();	
	if (iSel < 0)
    {
        ASSERT(FALSE);
        return;
    }

	// 关闭视频流
    status = dvpStop(m_handle);
	if (status != DVP_STATUS_OK)
	{
		MessageBox(_T("关闭视频流失败!"));
	}

	// 设置相机分辨率
	status = dvpSetQuickRoiSel(m_handle,iSel);
	if (status != DVP_STATUS_OK)
	{
		MessageBox(_T("设置分辨率错误!"));
	}

	// 打开视频流
    status = dvpStart(m_handle);
	if (status != DVP_STATUS_OK)
	{
		MessageBox(_T("启动视频流失败!"));
	}
}


void CBasicFunctionDlg::OnBnClickedButtonProperty()
{
	if (IsValidHandle(m_handle))
	{
		dvpStatus status = dvpShowPropertyModalDialog(m_handle, GetSafeHwnd());
		
		// 此时一些配置可能发生改变，将同步到界面
		UpdateControls();
	}
}


void CBasicFunctionDlg::OnBnClickedButtonSave()
{
	// 显示图片保存对话框
	CFileDialog file(
		FALSE, 
		_T("Picture"),
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("BITMAP Files(*.bmp)|*.bmp|JPEG Files(*.jpeg)|*.jpeg|TIFF Files(*.tiff)|\
		   *.tiff|PNG Files(*.png)|*.png|GIF Files(*.gif)|*.gif|Image Data Files(*.dat)|*.dat|"),
		   this);

	if (file.DoModal() == IDOK)
	{
		void *buffer;
		dvpFrame frame;
        dvpStatus status;

		// 从视频流中抓取一帧图像，要求5000ms以内
        status = dvpGetFrame(m_handle, &frame, &buffer, 5000);
		if (status == DVP_STATUS_OK)
		{
			// 将图像保存为图片文件
			status = dvpSavePicture(&frame, buffer, w2a(file.GetPathName().GetBuffer()).c_str(), 100);
            ASSERT(status == DVP_STATUS_OK);
		}
        else if (status == DVP_STATUS_TIME_OUT)
        {
            MessageBox(_T("获取图像数据超时!"));
        }
        else
        {
            MessageBox(_T("获取图像数据时发生错误!"));
        }
	}
}


void CBasicFunctionDlg::OnCbnSelchangeComboAeMode()
{
	dvpStatus  status = DVP_STATUS_OK;
	
	// 获取自动曝光模式索引
	int iSel = ((CComboBox*)GetDlgItem(IDC_COMBO_AE_MODE))->GetCurSel();	
    if (iSel > 3)
    {
        ASSERT(FALSE);
        return;
    }

    // 自动曝光优先
    if (iSel == 0 )
    {
        status = dvpSetAeMode(m_handle, AE_MODE_AE_AG);
    }

    // 自动增益优先
    else if (iSel == 1)
    {
        status = dvpSetAeMode(m_handle, AE_MODE_AG_AE);
    }

    // 仅打开自动曝光
    else if (iSel == 2)
    {
        status = dvpSetAeMode(m_handle, AE_MODE_AE_ONLY);
    }

    // 仅打开自动增益
    else if (iSel == 3)
    {
        status = dvpSetAeMode(m_handle, AE_MODE_AG_ONLY);
    }

    ASSERT(status == DVP_STATUS_OK);

    UpdateControls();
}


void CBasicFunctionDlg::OnCbnSelchangeComboFlick()
{
	dvpStatus status = DVP_STATUS_OK;

	// 获取自动曝光索引
	int iSel = ((CComboBox*)GetDlgItem(IDC_COMBO_FLICK))->GetCurSel();
    if (iSel > 2)
    {
		ASSERT(FALSE);;
    }

	if (iSel == 0)
	{
		status = dvpSetAntiFlick(m_handle, ANTIFLICK_DISABLE);
	}
	else if (iSel == 1)
	{
		status = dvpSetAntiFlick(m_handle, ANTIFLICK_50HZ);
	}
    else if (iSel == 2)
	{
		status = dvpSetAntiFlick(m_handle, ANTIFLICK_60HZ);
	}

    ASSERT(status == DVP_STATUS_OK);
}


void CBasicFunctionDlg::OnBnClickedCheckAeoperation()
{
     
	UpdateData(TRUE);
    dvpStatus status;

	if (m_bAeOp == TRUE)
	{
		status = dvpSetAeOperation(m_handle, AE_OP_CONTINUOUS);
	}
	else
	{
		status = dvpSetAeOperation(m_handle, AE_OP_OFF);
	}

    ASSERT(status == DVP_STATUS_OK);

    UpdateControls();
    
}

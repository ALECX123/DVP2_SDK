
// BasicFunctionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BasicFunction.h"
#include "BasicFunctionDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// DVP API��������
#ifdef _M_X64
#pragma comment(lib, "../../../library/Visual C++/lib/x64/DVPCamera64.lib")
#else
#pragma comment(lib, "../../../library/Visual C++/lib/x86/DVPCamera.lib")
#endif

// ANSI�ַ���תUNICODE�ַ���
std::wstring a2w(LPCCH str)
{
	std::wstring wstr;
	wstr.resize(MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0) - 1);
	MultiByteToWideChar(CP_ACP, 0, str, -1, &wstr[0], wstr.size());
	return wstr;
}

// UNICODE�ַ���תANSI�ַ���
std::string w2a(LPCWCH wstr)
{
	std::string str;
	str.resize(WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL) - 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, &str[0], str.size(), NULL, NULL);
	return str;
}

// CBasicFunctionDlg �Ի���

// ���ڻ�ȡ��Ƶ���Ļص�����
int CBasicFunctionDlg::OnDrawPicture(dvpHandle handle,
	dvpStreamEvent event, 
	void *pContext, 
	dvpFrame *pFrame, 
	void *pBuffer)
{
	CBasicFunctionDlg *pDlg = ((CBasicFunctionDlg*)pContext);

	// ����ֻ��ʾ���������Ƶ��ͼ����������ص������в��˽��к�ʱ�ϳ��Ĳ���������Ӱ��֡�ʺ�ͼ��ɼ���ʵʱ�ԣ�
	// ��ʱ��õ�ͼ�����ݻ��棬ֻ�ڱ���������ǰ��Ч�����˰ѻ���ָ�봫�ݳ�ȥ�����ǣ��û��������������ڴ棬����ͼ�����ݣ�
	
	dvpStatus status = dvpDrawPicture(	pFrame, 
		pBuffer, 
		pDlg->GetDlgItem(IDC_STATIC_PREVIEW)->GetSafeHwnd(),
		nullptr, 
		nullptr);

	// ����0����ʾͼ�������Ѿ����Զ����������ٱ�ʹ��
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


// CBasicFunctionDlg ��Ϣ�������

BOOL CBasicFunctionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// Ԥ��ɨ����Ѿ����ӵ��豸
	OnBnClickedButtonScan();

	SetTimer(0, 500, NULL);
	return TRUE;  
}

void CBasicFunctionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
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

	// ���ݴ����С���Զ�������Ƶ��ͼ����
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
			// ����֡����Ϣ
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
		// ��"OK"�˳������������ò����Ĵ浵�����������ָ��·�����浵��Ŀ¼һ��Ϊ:C:\ProgramData\DO3THINK\DVP2
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

	// ���������ʱ��ͬʱ�ر��豸
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
		// ��ʱ�Ѿ�����һ���豸
		// ���»������ܿؼ�
		dvpStreamState state;
		status = dvpGetStreamState(m_handle, &state);
        ASSERT(status == DVP_STATUS_OK);

		GetDlgItem(IDC_BUTTON_START)->SetWindowText(state == STATE_STARTED ? _T("Stop") : _T("Start"));
		GetDlgItem(IDC_BUTTON_OPEN)->SetWindowTextW(_T("Close"));
	    GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_PROPERTY)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(TRUE);

		// ���¸���ʾ����ع��ܿؼ�
		GetDlgItem(IDC_COMBO_RESOLUTION)->EnableWindow(TRUE);
	    GetDlgItem(IDC_COMBO_AE_MODE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_FLICK)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_AEENABLE)->EnableWindow(TRUE);

		// �����Զ��ع�����ؼ�
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
		
		// ��ȡ�Զ��ع�ģʽ�������Զ��ع�ģʽ���ÿؼ���ʹ���ع�ʱ���ģ��������ڵĿؼ�
		((CComboBox*)GetDlgItem(IDC_COMBO_AE_MODE))->SetCurSel(AeMode);

		// ���¿�Ƶ�����ÿؼ�
		dvpAntiFlick AntiFlick;
		status = dvpGetAntiFlick(m_handle, &AntiFlick);
        ASSERT(status == DVP_STATUS_OK);
        ((CComboBox*)GetDlgItem(IDC_COMBO_FLICK))->SetCurSel(AntiFlick);

		// �����ع�ʱ��
		double fExpoTime;
		CString strExpoTime;
		status = dvpGetExposure(m_handle,&fExpoTime);
        ASSERT(status == DVP_STATUS_OK);
		strExpoTime.Format(_T("%5f"),fExpoTime);					 
		SetDlgItemText(IDC_STATIC_EXPOTIME,strExpoTime);
		 
		// ��������
		CString strGain;
		float fGain;
		status = dvpGetAnalogGain(m_handle,&fGain);
        ASSERT(status == DVP_STATUS_OK);
		strGain.Format(_T("%1.2f"),fGain);				
		SetDlgItemText(IDC_STATIC_EXPOGAIN,strGain);

		// ���·ֱ���
		dvpUint32 QRoiSel;
		status = dvpGetQuickRoiSel(m_handle, &QRoiSel);
		ASSERT(status == DVP_STATUS_OK);
		((CComboBox*)GetDlgItem(IDC_COMBO_RESOLUTION))->SetCurSel(QRoiSel);
	
        // �����ع�ʱ�������ĵ�ǰ����ֵ
        UpdateControlExposure();
        UpdateControlGain();
	}
	else
	{
		// ��ʱ�豸��û�б���
		// ���»������ܿؼ�
		GetDlgItem(IDC_BUTTON_OPEN)->SetWindowTextW(_T("Open"));	
		GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PROPERTY)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);

		if (m_listDevices.GetCount() == 0)
		{
			// û���豸����
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

	// ��ȡ�ع�ʱ���������Ϣ
    status = dvpGetExposureDescr(m_handle, &ExpoTimeDescr);
    ASSERT(status == DVP_STATUS_OK);
	if (status == DVP_STATUS_OK)
	{
		// �����ع�ʱ���϶����ķ�Χ
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER_EXPOSURE_TIME))->SetRange(static_cast<int>(ExpoTimeDescr.fMin),static_cast<int>(ExpoTimeDescr.fMax));//��λus
	}


	// ��ȡ�ع�ʱ��ĳ�ֵ
    status = dvpGetExposure(m_handle, &fExpoTime);
    ASSERT(status == DVP_STATUS_OK);
	if (status == DVP_STATUS_OK)
	{
		// �����ع�ʱ���϶�����ʼֵ
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

    // ��ȡģ�������������Ϣ
    status = dvpGetAnalogGainDescr(m_handle,&AnalogGainDescr);
    ASSERT(status == DVP_STATUS_OK);
    if (status == DVP_STATUS_OK)
    {
        // ����ģ�������϶����ķ�Χ
        ((CSliderCtrl*)GetDlgItem(IDC_SLIDER_GAIN))->SetRange(static_cast<int>(AnalogGainDescr.fMin*100),static_cast<int>(AnalogGainDescr.fMax*100));//��λx
    }

    // ��ȡģ�����沢����ģ������ĳ�ʼֵ
    status = dvpGetAnalogGain(m_handle, &fAnalogGain);
    ASSERT(status == DVP_STATUS_OK);
    if (status == DVP_STATUS_OK)
    {
        // ���������϶�����ʼֵ
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

	// ��ȡ����ֱ���������
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

	// ��ȡ�ֱ���ģʽ����
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
		// �����Զ��ع�ģʽ����
		((CComboBox*)GetDlgItem(IDC_COMBO_AE_MODE))->InsertString(0,a2w("AE_MODE_AE_AG").c_str());
		((CComboBox*)GetDlgItem(IDC_COMBO_AE_MODE))->InsertString(1,a2w("AE_MODE_AG_AE").c_str());
		((CComboBox*)GetDlgItem(IDC_COMBO_AE_MODE))->InsertString(2,a2w("AE_MODE_AE_ONLY").c_str());	
		((CComboBox*)GetDlgItem(IDC_COMBO_AE_MODE))->InsertString(3,a2w("AE_MODE_AG_ONLY").c_str());

		// ���õ�ǰ���Զ��ع�ģʽ
		((CComboBox*)GetDlgItem(IDC_COMBO_AE_MODE))->SetCurSel(3);	
	}
}

void CBasicFunctionDlg:: OnInitControlFlick()
{
	((CComboBox*)(GetDlgItem(IDC_COMBO_FLICK)))->ResetContent();
	if (IsValidHandle(m_handle))
	{
		// ����Ƶ����������
		((CComboBox*)GetDlgItem(IDC_COMBO_FLICK))->InsertString(0,a2w("ANTIFLICK_DISABLE").c_str());
		((CComboBox*)GetDlgItem(IDC_COMBO_FLICK))->InsertString(1,a2w("ANTIFLICK_50HZ").c_str());
		((CComboBox*)GetDlgItem(IDC_COMBO_FLICK))->InsertString(2,a2w("ANTIFLICK_60HZ").c_str());	

		// ���õ�ǰ��Ƶ��״̬
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
	// ��ʱ��nΪ�ɹ�ö�ٵ����������������ӵ������б��У������б��е�����Ϊÿ�������FriendlyName
	m_listDevices.ResetContent();


	// ��õ�ǰ�����ӵ��������
	status = dvpRefresh(&n);
    ASSERT(status == DVP_STATUS_OK);

    if (status == DVP_STATUS_OK)
    {
	    // ö�����16̨���
	    if (n>16)
		    n = 16;

	    for (i=0; i<n; i++)
	    {
		    // ���ö�ٳ�ÿ���������Ϣ
		    status = dvpEnum(i, &info);
            ASSERT(status == DVP_STATUS_OK);

            if (status == DVP_STATUS_OK)
            {
		        // ����ʹ�õ���UNICODE��ö�ٵ��豸��ϢΪANSI�ַ�������Ҫ��ANSIתUNICODE
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
			// ͨ��ö�ٵ���ѡ���FriendlyName��ָ���豸
			status = dvpOpenByName(w2a(strName).c_str(), OPEN_NORMAL, &m_handle);
			if(status != DVP_STATUS_OK)
			{
				MessageBox(_T("��ʧ��"));
			}
			else
			{
				m_strFriendlyName = strName;	

				// �����Ҫͼ����ʾ������ע��ص��������ڻص���������ɻ�ͼ����
				// ע�⣺�ص�������ִ�еĻ�ͼ���������ܻ��dvpGetFrame�ӿڻ�ȡ��ͼ�����������ʱ
				dvpRegisterStreamCallback(m_handle, OnDrawPicture, STREAM_EVENT_PROCESSED, this);

				// ��ʼ���ع�ʱ�䡢���桢�ֱ��ʺ��Զ��ع�ģʽ
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
		// ���ݵ�ǰ��Ƶ״̬��ִ���෴�Ĳ�����ʵ��һ����ť������������ֹͣ
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
	    // ��ȡ�����õ��ع�ʱ���϶�����ֵ
	    fExpoTime = ((CSliderCtrl*)GetDlgItem(IDC_SLIDER_EXPOSURE_TIME))->GetPos();

	    // �����ع�ʱ��
        // ��ȡ�ع�ʱ��ķ�Χ����������ֵ������Χ
        status = dvpGetExposureDescr(m_handle, &ExpDescr);
        ASSERT(status == DVP_STATUS_OK);

        if (fExpoTime > ExpDescr.fMax)
            fExpoTime = ExpDescr.fMax;

        if (fExpoTime < ExpDescr.fMin)
            fExpoTime = ExpDescr.fMin;

        // �������ع�ʱ��
        status = dvpSetExposure(m_handle,fExpoTime);
        ASSERT(status == DVP_STATUS_OK);

        // �ٻ�ȡ�ع�ʱ�䣬���ڵ��ھ���(����ֵ)�����⣬��ȡֵ����������ֵ��Щ���죬�Ի�ȡֵΪ׼
        status = dvpSetExposure(m_handle,fExpoTime);
        ASSERT(status == DVP_STATUS_OK);

	    // �����ع�ʱ���ı�
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
	    // ��ȡ�����õ�ģ�������϶���ֵ
	    fGain = static_cast<float>(((CSliderCtrl*)GetDlgItem(IDC_SLIDER_GAIN))->GetPos()) / 100;

        // ����������ֵ
        status = dvpSetAnalogGain(m_handle,fGain);
        ASSERT(status == DVP_STATUS_OK);

        // �ٻ�ȡ����ֵ�����ڵ��ھ���(����ֵ)�����⣬��ȡֵ����������ֵ��Щ���죬�Ի�ȡֵΪ׼
        status = dvpGetAnalogGain(m_handle, &fGain);
        ASSERT(status == DVP_STATUS_OK);

	    // ����ģ�������ı�
	    strGain.Format(_T("%1.3f%s"),fGain,"x");				
	    SetDlgItemText(IDC_STATIC_EXPOGAIN, strGain);
    }

	*pResult = 0;
}


void CBasicFunctionDlg::OnCbnSelchangeComboResolution()
{
	dvpStatus status;

	// ��ȡ�ֱ���ѡ������
	int iSel = ((CComboBox*)GetDlgItem(IDC_COMBO_RESOLUTION))->GetCurSel();	
	if (iSel < 0)
    {
        ASSERT(FALSE);
        return;
    }

	// �ر���Ƶ��
    status = dvpStop(m_handle);
	if (status != DVP_STATUS_OK)
	{
		MessageBox(_T("�ر���Ƶ��ʧ��!"));
	}

	// ��������ֱ���
	status = dvpSetQuickRoiSel(m_handle,iSel);
	if (status != DVP_STATUS_OK)
	{
		MessageBox(_T("���÷ֱ��ʴ���!"));
	}

	// ����Ƶ��
    status = dvpStart(m_handle);
	if (status != DVP_STATUS_OK)
	{
		MessageBox(_T("������Ƶ��ʧ��!"));
	}
}


void CBasicFunctionDlg::OnBnClickedButtonProperty()
{
	if (IsValidHandle(m_handle))
	{
		dvpStatus status = dvpShowPropertyModalDialog(m_handle, GetSafeHwnd());
		
		// ��ʱһЩ���ÿ��ܷ����ı䣬��ͬ��������
		UpdateControls();
	}
}


void CBasicFunctionDlg::OnBnClickedButtonSave()
{
	// ��ʾͼƬ����Ի���
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

		// ����Ƶ����ץȡһ֡ͼ��Ҫ��5000ms����
        status = dvpGetFrame(m_handle, &frame, &buffer, 5000);
		if (status == DVP_STATUS_OK)
		{
			// ��ͼ�񱣴�ΪͼƬ�ļ�
			status = dvpSavePicture(&frame, buffer, w2a(file.GetPathName().GetBuffer()).c_str(), 100);
            ASSERT(status == DVP_STATUS_OK);
		}
        else if (status == DVP_STATUS_TIME_OUT)
        {
            MessageBox(_T("��ȡͼ�����ݳ�ʱ!"));
        }
        else
        {
            MessageBox(_T("��ȡͼ������ʱ��������!"));
        }
	}
}


void CBasicFunctionDlg::OnCbnSelchangeComboAeMode()
{
	dvpStatus  status = DVP_STATUS_OK;
	
	// ��ȡ�Զ��ع�ģʽ����
	int iSel = ((CComboBox*)GetDlgItem(IDC_COMBO_AE_MODE))->GetCurSel();	
    if (iSel > 3)
    {
        ASSERT(FALSE);
        return;
    }

    // �Զ��ع�����
    if (iSel == 0 )
    {
        status = dvpSetAeMode(m_handle, AE_MODE_AE_AG);
    }

    // �Զ���������
    else if (iSel == 1)
    {
        status = dvpSetAeMode(m_handle, AE_MODE_AG_AE);
    }

    // �����Զ��ع�
    else if (iSel == 2)
    {
        status = dvpSetAeMode(m_handle, AE_MODE_AE_ONLY);
    }

    // �����Զ�����
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

	// ��ȡ�Զ��ع�����
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

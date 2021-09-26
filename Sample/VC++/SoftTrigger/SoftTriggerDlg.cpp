
// TriggerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SoftTrigger.h"
#include "SoftTriggerDlg.h"
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


struct FrameImage
{
	dvpFrame stFrame;
	void *pBuffer;
};
FrameImage *g_lpFrameImage = NULL;

// CSoftTriggerDlg �Ի���
// ���ڻ�ȡ��Ƶ���Ļص�������������Ҫ����
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
	// ����ֻ��ʾ���������Ƶ��ͼ����������ص������в��˽��к�ʱ�ϳ��Ĳ���������Ӱ��֡�ʺ�ͼ��ɼ���ʵʱ�ԣ�
	// ��ʱ��õ�ͼ�����ݻ��棬ֻ�ڱ���������ǰ��Ч�����˰ѻ���ָ�봫�ݳ�ȥ�����ǣ��û��������������ڴ棬����ͼ�����ݣ�
	dvpStatus status = dvpDrawPicture(	pFrame, 
										pBuffer, 
										pDlg->GetDlgItem(IDC_STATIC_PREVIEW)->GetSafeHwnd(),
										nullptr, 
										nullptr);

	if ( pDlg->m_trigger_state == 2  )
	{
		//�������ͼ����
		//���津��ץ�ĵ�ͼ
		char sz_file_path[MAX_PATH] = {0};
		
		GetModuleFileNameA(theApp.m_hInstance, sz_file_path, sizeof(sz_file_path)); 
		char *lp = strrchr(sz_file_path, '\\');
		strcpy(lp+1, "SoftTrigger.bmp");

		dvpSavePicture(pFrame, pBuffer, sz_file_path, 0);
		pDlg->m_trigger_state = 1;
		//�������ת��������Ԥ��ģʽ
		dvpSetTriggerState(pDlg->m_handle, false);
		pDlg->m_trigger_state = 0;

	}

	pDlg->m_b_read_image_flg = false;

	// ����0����ʾͼ�������Ѿ����Զ����������ٱ�ʹ��
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
	m_trigger_state = 0;//��ʼ��
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

// ���и��½����Ͽؼ�
void CSoftTriggerDlg::UpdateControls()
{
	dvpStatus status;
	
 	if (IsValidHandle(m_handle))
	{	
		// ��ʱ�Ѿ�����һ���豸

		// ���¸��º�ʹ�ܻ������ܵĿؼ�
		dvpStreamState state;
		status = dvpGetStreamState(m_handle, &state);
		//ASSERT(status == DVP_STATUS_OK);

		GetDlgItem(IDC_BUTTON_OPEN)->SetWindowTextW(_T("Close"));
		GetDlgItem(IDC_BUTTON_PLAY)->SetWindowText(state == STATE_STARTED ? _T("Stop") : _T("Start"));
		GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_PROPERTY)->EnableWindow(TRUE);


		// ����ʹ��ʾ����ع��ܵĿؼ�
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


		// ���¸��´���������صĽ���
		bool bTrig,bLoop;

		// ����ģʽʹ��״̬
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
		//���ô�������
		((CButton*)GetDlgItem(IDC_CHECK_TRIGGER))->SetCheck((int)bTrig);
		
		
		
		// ѭ������ʹ��״̬
		status = dvpGetSoftTriggerLoopState(m_handle, &bLoop);
		//ASSERT(status == DVP_STATUS_OK);
		
		((CButton*)GetDlgItem(IDC_CHECK_LOOP))->SetCheck((int)bLoop);

		// �ⲿ��������IO���״̬
		bool bExtTrigIn = FALSE;
		dvpUserIoInfo UserIoInfo;
		dvpInputIoFunction InIoFunc;
		dvpUint32 i;

		// ö�ٳ�����UserIO��������Ƿ���IO���ڴ������빦��
		status = dvpGetUserIoInfo(m_handle, &UserIoInfo);
		//ASSERT(status == DVP_STATUS_OK);

		m_InputIo.ResetContent();
		for (i=0; i<8; i++)
		{
			if (UserIoInfo.inputValid[i])
			{
				CString str;
				dvpInputIo InputIo = dvpInputIo(i + INPUT_IO_1);

				// ��IO������ӵ������б���
				str.Format(L"IN_%d", i + 1);
				m_InputIo.AddString(str);
				m_InputIo.SetItemData(i, InputIo);

				// ����Ƿ�������IO������Ϊ�������빦��
				status = dvpGetInputIoFunction(m_handle, InputIo, &InIoFunc);
				//ASSERT(status == DVP_STATUS_OK);

				if (!bExtTrigIn && InIoFunc == INPUT_FUNCTION_TRIGGER)
				{
					// �ҵ�һ��IO�Ѿ�������Ϊ���������ź�
					bExtTrigIn = TRUE;

					// �������б���ѡȡ�Ǹ�������Ϊ�������빦�ܵ�IO
					m_InputIo.SetCurSel(i);
				}
			}
		}

		if (bExtTrigIn)
		{
			// �ڽ�����ָʾ���Ѿ��д��������źű�ʹ��
			((CButton*)GetDlgItem(IDC_CHECK_TRIG_IN))->SetCheck(1);
		}
		else
		{
			// û��IO������Ϊ�������룬Ĭ���������б���ѡȡ��һ��
			m_InputIo.SetCurSel(0);

			// �ڽ�����ָʾ��û�д��������źű�ʹ��
			((CButton*)GetDlgItem(IDC_CHECK_TRIG_IN))->SetCheck(0);
		}

		// ���´��������ź������б�
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


		// ���¸���Strobe������صĽ���
		bool bExtStrobeOut = FALSE;
		dvpOutputIoFunction OutIoFunc;

		// ö�ٳ�����UserIO��������Ƿ���IO����Strobe�������
		m_OutputIo.ResetContent();
		for (i=0; i<8; i++)
		{
			if (UserIoInfo.outputValid[i])
			{
				CString str;
				dvpOutputIo OutputIo = dvpOutputIo(i + OUTPUT_IO_1);

				// ��IO������ӵ������б���
				str.Format(L"OUT_%d", i + 1);
				m_OutputIo.AddString(str);
				m_OutputIo.SetItemData(i, OutputIo);

				// ����Ƿ������IO������ΪStrobe�������
				status = dvpGetOutputIoFunction(m_handle, OutputIo, &OutIoFunc);
				//ASSERT(status == DVP_STATUS_OK);

				if (!bExtStrobeOut && OutIoFunc == OUTPUT_FUNCTION_STROBE)
				{
					// �ҵ�һ��IO�Ѿ�������Ϊstrobe������ܵ�IO
					bExtStrobeOut = TRUE;

					// �������б���ѡȡ�Ǹ�������Ϊstrobe������ܵ�IO
					m_OutputIo.SetCurSel(i);

				}
			}
		}

		if (bExtStrobeOut)
		{
			// �ڽ�����ָʾ���Ѿ���Strobe����źű�ʹ��
			((CButton*)GetDlgItem(IDC_CHECK_STROBE_OUT))->SetCheck(1);
		}
		else
		{
			// û��IO������Ϊ�������룬Ĭ���������б���ѡȡ��һ��
			m_OutputIo.SetCurSel(0);

			// �ڽ�����ָʾ��û��Strobe����źű�ʹ��
			((CButton*)GetDlgItem(IDC_CHECK_STROBE_OUT))->SetCheck(0);
		}

		// ����Strobe����ź������б�
		m_StrobeOutputType.ResetContent();
		m_StrobeOutputType.AddString(_T("Off"));
		m_StrobeOutputType.AddString(_T("Low Level"));
		m_StrobeOutputType.AddString(_T("High Level"));

		//��ȡStrobe�ź�����
		dvpStrobeOutputType StrobeType;
		status = dvpGetStrobeOutputType(m_handle, &StrobeType);
		//ASSERT(status == DVP_STATUS_OK);

		m_StrobeOutputType.SetCurSel(StrobeType);


		// ������Щ��ȡ��������Ϣ�����ڸ��±༭��������ֵ�ķ�Χ
		status = dvpGetTriggerDelayDescr(m_handle, &m_DelayDescr);
		//ASSERT(status == DVP_STATUS_OK);

		status = dvpGetTriggerJitterFilterDescr(m_handle, &m_FilterDescr);
		//ASSERT(status == DVP_STATUS_OK);

		status = dvpGetSoftTriggerLoopDescr(m_handle, &m_LoopDescr);
		//ASSERT(status == DVP_STATUS_OK);

		// ���¸��±༭���е�����ֵ
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
		// ��ʱ��û���豸����
		// ���»������ܿؼ�
		GetDlgItem(IDC_BUTTON_OPEN)->SetWindowTextW(_T("Open"));
		GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PROPERTY)->EnableWindow(FALSE);

		if (m_listDevices.GetCount() == 0)
		{
			// û���豸����
			GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(FALSE);
		}
		else
		{
			GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(TRUE);
		}


		// ���±�ʾ����ع��ܵĿؼ�
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

	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	
	// Ԥ��ɨ����Ѿ����ӵ��豸
	OnBnClickedButtonScan();

	// ��ʱ�����ڸ��µ�ǰ֡����Ϣ
	SetTimer(0, 500, NULL);

	return TRUE; 
}


void CSoftTriggerDlg::OnPaint()
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


HCURSOR CSoftTriggerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSoftTriggerDlg::OnBnClickedButtonTriggerFire()
{
	if (IsValidHandle(m_handle))
	{
		// �������ִ��һ�Σ��൱�ڲ���һ���ⴥ��
		// ע�⣺����ع�ʱ��ϳ�ʱ������ĵ��"Soft Trigger Fire"�п��ܵ��´���ʧ�ܣ���Ϊ��һ֡�����ܳ����ع��δ������״̬
		dvpStatus status = dvpTriggerFire(m_handle);
		//ASSERT(status == DVP_STATUS_OK);
	}
}

void CSoftTriggerDlg::OnOK()
{
	if (IsValidHandle(m_handle))
	{
		// ��"OK"�˳������������ò����Ĵ浵�����������ָ��·�����浵��Ŀ¼һ��Ϊ:C:\ProgramData\DO3THINK\DVP2
		dvpStatus status = dvpSaveConfig(m_handle, NULL);
		//ASSERT(status == DVP_STATUS_OK);
	}

	CDialogEx::OnOK();
}

void CSoftTriggerDlg::OnBnClickedCheckTrigger()
{
	if (IsValidHandle(m_handle))
	{
		// ʹ��/���ô���ģʽ
		dvpStatus status = dvpSetTriggerState(m_handle, ((CButton*)GetDlgItem(IDC_CHECK_TRIGGER))->GetCheck() ? true : false);
		//ASSERT(status == DVP_STATUS_OK);

		UpdateControls();
	}
}

void CSoftTriggerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// ���������ʱ��ͬʱ�ر��豸
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
			// ����֡����Ϣ
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

void CSoftTriggerDlg::OnBnClickedButtonScan()
{
	dvpStatus status;
	dvpUint32 i,n=0;
	dvpCameraInfo info = {0};

	// ��ʱ��nΪ�ɹ�ö�ٵ����������������ӵ������б��У������б��е�����Ϊÿ�������FriendlyName
	m_listDevices.ResetContent();

	// ��õ�ǰ�����ӵ��������
	status = dvpRefresh(&n);
	//ASSERT(status == DVP_STATUS_OK);
	
	if (status == DVP_STATUS_OK)
	{
		// ö�����16̨���
		if (n>16)
			n = 16;

		for (i=0; i<n; i++)
		{
			// ���ö�ٳ�ÿ���������Ϣ
			status = dvpEnum(i, &info);
			//ASSERT(status == DVP_STATUS_OK);

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
			// ͨ��ö�ٵ���ѡ���FriendlyName��ָ���豸
			status = dvpOpenByName(w2a(strName).c_str(), OPEN_NORMAL, &m_handle);
			//ASSERT(status == DVP_STATUS_OK);

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

		// ���ݵ�ǰ��Ƶ״̬��ִ���෴�Ĳ�����ʵ��һ����ť������������ֹͣ
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

		// ��ʱһЩ���ÿ��ܷ����ı䣬��ͬ��������
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

		// �Ƚ�����INPUT IO����ΪNormalģʽ
		for (i=0; i<8; i++)
		{
			if (UserIoInfo.inputValid[i])
			{
				dvpSetInputIoFunction(m_handle, dvpInputIo(INPUT_IO_1+i), INPUT_FUNCTION_NORMAL);
				//ASSERT(status == DVP_STATUS_OK);
			}
		}

		// ���ʹ����ExtTriggerIn����ѡ���InputIo����Ϊ�������빦��
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

		// �Ƚ�����OUTPUT IO����ΪNormalģʽ
		for (i=0; i<8; i++)
		{
			if (UserIoInfo.outputValid[i])
			{
				status = dvpSetOutputIoFunction(m_handle, dvpOutputIo(OUTPUT_IO_1+i), OUTPUT_FUNCTION_NORMAL);
				//ASSERT(status == DVP_STATUS_OK);
			}
		}

		// ���ʹ����ExtStrobeOut����ѡ���OutputIo����ΪStrobe�������
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
		// ��������IO�ĸı�͹�ѡ��������ʹ����ͬ���Ĵ������
		OnBnClickedCheckTrigIn();
	}
}

void CSoftTriggerDlg::OnCbnSelchangeComboOutputIo()
{
	if (IsValidHandle(m_handle))
	{
		// Strobe���IO�ĸı�͹�ѡStrobe���ʹ����ͬ���Ĵ������
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

//��ͨģʽת�����������
void CSoftTriggerDlg::OnBnClickedSofttriggerPreview()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (IsValidHandle(m_handle) && m_trigger_state == 0)
	{
		bool bTrig = false;
		dvpStatus status = dvpGetTriggerState(m_handle, &bTrig);
		if ( status == DVP_STATUS_OK )
		{
			status = dvpSetTriggerState(m_handle, true);
			if ( status == DVP_STATUS_OK )
			{
				//����Ϊ����ģʽ
				m_trigger_state = 1; 

				//�ȴ���ǰ֡���ݴ�����
				while ( m_b_read_image_flg )
				{
					Sleep(1);
				}
				
				// �������ִ��һ�Σ��൱�ڲ���һ���ⴥ��
				// ע�⣺����ع�ʱ��ϳ�ʱ������ĵ��"Soft Trigger Fire"�п��ܵ��´���ʧ�ܣ���Ϊ��һ֡�����ܳ����ع��δ������״̬
				status = dvpTriggerFire(m_handle);
				if ( status == DVP_STATUS_OK )
				{
					m_trigger_state = 2; //���ʹ����źųɹ�
				}
				
			}
			
			
		}

	}
}

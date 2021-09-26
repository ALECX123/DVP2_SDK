
// ImageAcquisitionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageAcquisition.h"
#include "ImageAcquisitionDlg.h"
#include "afxdialogex.h"
#include <string> 
#include <sstream>
#include <queue> 
#include <afxdlgs.h>
#include <time.h>

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

// CImageAcquisitionDlg �Ի���
CImageAcquisitionDlg::CImageAcquisitionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CImageAcquisitionDlg::IDD, pParent),
	 m_pThread(NULL)
	, strPicturePath(_T("."))
	, m_RecentCount(100)
	, m_bDisplay(TRUE)
	, m_bSave(FALSE)
    , m_uWaitTimer(0)
    , m_bSoftTrigger(FALSE)
    , m_uImageCount(0)
    , m_uGrabTimeout(4000)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    
    // ���ؽ������
    m_bDisplay = GetPrivateProfileInt(_T("param"), _T("display"), m_bDisplay, _T(".\\ImageAcquisition.ini"));
    m_bSave = GetPrivateProfileInt(_T("param"), _T("save"), m_bSave, _T(".\\ImageAcquisition.ini"));
    m_uWaitTimer = GetPrivateProfileInt(_T("param"), _T("wait"), m_uWaitTimer, _T(".\\ImageAcquisition.ini"));
    m_uGrabTimeout = GetPrivateProfileInt(_T("param"), _T("timeout"), m_uGrabTimeout, _T(".\\ImageAcquisition.ini"));
    m_bSoftTrigger = GetPrivateProfileInt(_T("param"), _T("SoftTrig"), m_bSoftTrigger, _T(".\\ImageAcquisition.ini"));

    TCHAR tmp[MAX_PATH];
    GetPrivateProfileString(_T("param"), _T("path"), strPicturePath, tmp, MAX_PATH, _T(".\\ImageAcquisition.ini"));
    strPicturePath = tmp;
	
}

CImageAcquisitionDlg::~CImageAcquisitionDlg()
{
    // ����������
    CString str;

    str.Format(_T("%d"), m_bDisplay);
    WritePrivateProfileString(_T("param"), _T("display"), str, _T(".\\ImageAcquisition.ini"));
    str.Format(_T("%d"), m_bSave);
    WritePrivateProfileString(_T("param"), _T("save"), str, _T(".\\ImageAcquisition.ini"));
    str.Format(_T("%d"), m_uWaitTimer);
    WritePrivateProfileString(_T("param"), _T("wait"), str, _T(".\\ImageAcquisition.ini"));
    str.Format(_T("%d"), m_uGrabTimeout);
    WritePrivateProfileString(_T("param"), _T("timeout"), str, _T(".\\ImageAcquisition.ini"));
    str.Format(_T("%d"), m_bSoftTrigger);
    WritePrivateProfileString(_T("param"), _T("SoftTrig"), str, _T(".\\ImageAcquisition.ini"));
    WritePrivateProfileString(_T("param"), _T("path"), strPicturePath, _T(".\\ImageAcquisition.ini"));
}


void CImageAcquisitionDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHECK_DISPLAY, m_bDisplay);
    DDX_Check(pDX, IDC_CHECK_SAVE, m_bSave);
    DDX_Control(pDX, IDC_COMBO_DEVICES, m_listDevices);
    DDX_Control(pDX,IDC_STATIC_PREVIEW,m_Picture);
    DDX_Text(pDX, IDC_EDIT_SAVEPATH, strPicturePath);
    DDX_Text(pDX, IDC_EDIT_WAIT, m_uWaitTimer);
    DDX_Check(pDX, IDC_CHECK_SOFT_TRIGGER, m_bSoftTrigger);
    DDX_Text(pDX, IDC_EDIT_TIMEOUT, m_uGrabTimeout);
}

BEGIN_MESSAGE_MAP(CImageAcquisitionDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CImageAcquisitionDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_PROPERTY, &CImageAcquisitionDlg::OnBnClickedButtonProperty)
	ON_BN_CLICKED(IDC_BUTTON_SCAN, &CImageAcquisitionDlg::OnBnClickedButtonScan)
	ON_BN_CLICKED(IDC_BUTTON_START, &CImageAcquisitionDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_FILE, &CImageAcquisitionDlg::OnBnClickedButtonOpenFile)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_SELECTPATH, &CImageAcquisitionDlg::OnBnClickedButtonSelectpath)
    ON_WM_CLOSE()
END_MESSAGE_MAP()

// CImageAcquisitionDlg ��Ϣ�������
BOOL CImageAcquisitionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	
	// Ԥ��ɨ������豸
	OnBnClickedButtonScan();

	SetTimer(0, 500, NULL);
	return TRUE;  
}

void CImageAcquisitionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);// ���ڻ��Ƶ��豸������

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


void CImageAcquisitionDlg::OnSize(UINT nType, int cx, int cy)
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

void CImageAcquisitionDlg::OnTimer(UINT_PTR nIDEvent)
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

            str.Format(_T("%d"), m_uImageCount);
            GetDlgItem(IDC_STATIC_COUNT)->SetWindowText(str);

		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

HCURSOR CImageAcquisitionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CImageAcquisitionDlg::OnBnClickedButtonOpen()
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
            }
        }
    }
    else
    {
        status = dvpClose(m_handle);
        ASSERT(status == DVP_STATUS_OK);
        m_handle = 0;
		GetDlgItem(IDC_STATIC_PREVIEW)->Invalidate(TRUE);
    }

    UpdateControls();
}

void CImageAcquisitionDlg::UpdateControls()
{
	dvpStatus status;

	if (IsValidHandle(m_handle))
	{
		// ��ʱ�Ѿ�����һ���豸
		// ���¸��º�ʹ�ܻ������ܵĿؼ�
		dvpStreamState state;
		status = dvpGetStreamState(m_handle, &state);

		GetDlgItem(IDC_BUTTON_OPEN)->SetWindowText(_T("Close"));
        GetDlgItem(IDC_BUTTON_START)->SetWindowText(state == STATE_STARTED ? _T("Stop") : _T("Start"));
		GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_PROPERTY)->EnableWindow(TRUE);


		// ����ʾ����ع��ܿؼ�
		if (state == STATE_STARTED)
		{
            // ����ɼ��̻߳��ڼ���������һЩ���������Լ򻯶��߳�ͬ��������
			GetDlgItem(IDC_CHECK_SAVE)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHECK_DISPLAY)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_SELECTPATH)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SAVEPATH)->EnableWindow(FALSE);
            GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(FALSE);
            GetDlgItem(IDC_EDIT_WAIT)->EnableWindow(FALSE);
            GetDlgItem(IDC_EDIT_TIMEOUT)->EnableWindow(FALSE);
            GetDlgItem(IDC_CHECK_SOFT_TRIGGER)->EnableWindow(FALSE);
		}
		else
		{
			GetDlgItem(IDC_CHECK_SAVE)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK_DISPLAY)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_SELECTPATH)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_SAVEPATH)->EnableWindow(TRUE);
            GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(TRUE);
            GetDlgItem(IDC_EDIT_WAIT)->EnableWindow(TRUE);
            GetDlgItem(IDC_EDIT_TIMEOUT)->EnableWindow(TRUE);
            GetDlgItem(IDC_CHECK_SOFT_TRIGGER)->EnableWindow(TRUE);
		}
	}
	else
	{
		// û���豸����
		// ���»������ܿؼ�
		GetDlgItem(IDC_BUTTON_OPEN)->SetWindowTextW(_T("Open"));
		GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
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

		// ����ʾ����ع��ܵĿؼ�
		GetDlgItem(IDC_STATIC_PREVIEW)->InvalidateRect(NULL);
		GetDlgItem(IDC_CHECK_SAVE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_DISPLAY)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SELECTPATH)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SAVEPATH)->EnableWindow(TRUE);
	}
	SendMessage(WM_SIZE);
}

// �ڶ������߳���ץȡͼ�񣬲��Ҹ�����Ҫ����֡IDΪ�ļ����������������֡ͼ���ٽ�ͼ����ʾ��Ԥ������
UINT CImageAcquisitionDlg::ImageThread()
{
	dvpStatus status;
	SYSTEMTIME m_systm;

	// �ȴ��߳��˳��¼�
	while (WaitForSingleObject(m_evtExit, m_uWaitTimer) != WAIT_OBJECT_0) 
	{
		void *pBuffer;
		dvpFrame frame;

        if (m_bSoftTrigger)
        {
            status = dvpTriggerFire(m_handle);
            if (status != DVP_STATUS_OK)
            {
                // �п����Ǵ����źż��̫���ܼ�������
                TRACE("dvpTriggerFire����ʧ��, status:%d\r\n", status);
            }
        }

		// ����Ƶ����ץȡһ֡ͼ�񣬳�ʱʱ��ͨ����ӦС���ع�ʱ��
		status = dvpGetFrame(m_handle, &frame, &pBuffer, m_uGrabTimeout);
		if (status != DVP_STATUS_OK)
		{
            TRACE("dvpGetFrame����ʧ��, status:%d\r\n", status);
            continue;
		}
	
		// �����Ҫ����ͼ��
		if (m_bSave) 
		{
			// ��ϵͳʱ��Ϊ�ļ��������µ�bmpͼ��
			::GetLocalTime(&m_systm);
			strFileName.Format(_T("%s\\%d_%d_%d_%d_%d_%d_%d.bmp"),strPicturePath,m_systm.wYear,m_systm.wMonth,m_systm.wDay,m_systm.wHour,m_systm.wMinute,m_systm.wSecond,m_systm.wMilliseconds);

            status = dvpSavePicture(&frame, pBuffer, w2a(strFileName).c_str(), 100);
			ASSERT(status == DVP_STATUS_OK);

            m_uImageCount++;
		}

		// �����Ҫ������ʾͼ��Ԥ������
		if (m_bDisplay)
		{
			status = dvpDrawPicture(
									&frame, 
									pBuffer,
									GetDlgItem(IDC_STATIC_PREVIEW)->GetSafeHwnd(), 
									NULL, 
									NULL);
			ASSERT(status == DVP_STATUS_OK);
		}		
	}


    m_pThread->ExitInstance();
	return 0; 
}


UINT CImageAcquisitionDlg::ImageThread(void *pParam)
{
	return ((CImageAcquisitionDlg*)pParam)->ImageThread();
}

void CImageAcquisitionDlg::OnDestroy()
{
    if (IsValidHandle(m_handle))
    {
        dvpClose(m_handle);
        m_handle = 0;
    }

	CDialogEx::OnDestroy();
}

// ��ʾ������ԶԻ���
void CImageAcquisitionDlg::OnBnClickedButtonProperty()
{
	if (IsValidHandle(m_handle))
	{
		dvpShowPropertyModalDialog(m_handle, GetSafeHwnd());

		// ��ʱһЩ���ÿ��ܷ����ı䣬��ͬ��������
		UpdateControls();
	}
}

void CImageAcquisitionDlg::OnBnClickedButtonScan()
{
	dvpStatus status;
	dvpUint32 i,n=0;
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
}


void CImageAcquisitionDlg::OnBnClickedButtonStart()
{
	if (IsValidHandle(m_handle))
	{
		dvpStreamState state;
		dvpStatus status;

		// ���ݵ�ǰ��Ƶ״̬��ִ���෴�Ĳ�����ʵ��һ����ť������������ֹͣ
		status = dvpGetStreamState(m_handle, &state);
		ASSERT(status == DVP_STATUS_OK);

		if (state != STATE_STOPED)
		{
            status = dvpStop(m_handle);
            ASSERT(status == DVP_STATUS_OK);

            if (m_pThread != NULL)
            {
                m_evtExit.SetEvent();

                // �ȴ��ɼ��߳̽���������10���ӣ����������ڻῨ��
                if (m_pThread->m_hThread != INVALID_HANDLE_VALUE)
                {
                    DWORD dw = WaitForSingleObject(m_pThread->m_hThread, 100000);

                    // ��������²�Ӧ�ó�ʱ
                    ASSERT(dw == WAIT_OBJECT_0);
                }

                m_pThread->Delete();
                m_pThread = NULL;           
            }

        }
		else
		{
            if (UpdateData(TRUE))
            {
                // ��dvpStart֮ǰ������Ϊ����ģʽ
                status = dvpSetTriggerState(m_handle, m_bSoftTrigger?TRUE:FALSE);
                if (status != DVP_STATUS_OK)
                {
                    // ��ʱҪȷ������Ƿ�֧�ִ�������
                    MessageBox(_T("���ô���ģʽʧ��"));
                }

                status = dvpStart(m_handle);
                if (status != DVP_STATUS_OK)
                {
                    MessageBox(_T("����ʧ��"));
                }

                // �����߳��˳��¼�
                m_evtExit.ResetEvent();

                // ����ͼ��ɼ��߳�
                m_pThread = AfxBeginThread(ImageThread, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
                if (m_pThread != NULL)
                {
                    m_pThread->m_bAutoDelete = FALSE;

                    // �����߳�
                    m_pThread->ResumeThread();
                }
                else
                {
                    ASSERT(FALSE);
                }



            }
			
		}
	}
	UpdateControls();
}

void CImageAcquisitionDlg::OnBnClickedButtonOpenFile()
{
	ShellExecute(NULL,_T("open"),strPicturePath,NULL,NULL,SW_SHOWNORMAL); 
}

 void CImageAcquisitionDlg::OnBnClickedButtonSelectpath()
 {
	 BROWSEINFO bi;
	 char Buffer[MAX_PATH];

	 // ��ʼ����ڲ���bi��ʼ
	 bi.hwndOwner = NULL;

	 // ��ʼ���ƶ���rootĿ¼
	 bi.pidlRoot =NULL;
     
	 // �˲�����ΪNULL������ʾ�Ի���
	 bi.pszDisplayName =(LPWSTR)Buffer;
	 bi.lpszTitle = _T("ѡ���ļ�·��");
	 
	 // ���༭��ķ��
	 bi.ulFlags = 0x0040 | BIF_RETURNONLYFSDIRS | BIF_EDITBOX;
	 bi.lpfn = NULL;
	 bi.lParam = 0;
	 bi.iImage=IDR_MAINFRAME;

	 // ��ʼ����ڲ���bi����
	
	 // ������ʾѡ��Ի���
	 LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);

	 if(pIDList)
	 {
		// ȡ���ļ���·����Buffer��
		 SHGetPathFromIDList(pIDList, (LPWSTR)Buffer);

		 // ��·��������һ��CString������
		 strPicturePath = (LPWSTR)Buffer;
	 }
	 m_bSave = TRUE;
	 UpdateData(FALSE);
 }


 void CImageAcquisitionDlg::OnClose()
 {
     UpdateData(TRUE);
     CDialogEx::OnClose();
 }

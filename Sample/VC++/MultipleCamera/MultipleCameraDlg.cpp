
// MultipleCameraDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MultipleCamera.h"
#include "MultipleCameraDlg.h"
#include "afxdialogex.h" 
#include <set>

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
	MultiByteToWideChar(CP_ACP, 0, str, -1, (LPWSTR)wstr.data(), wstr.size());
	return wstr;
}

// UNICODE�ַ���תANSI�ַ���
std::string w2a(LPCWCH wstr)
{
	std::string str;
	str.resize(WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL) - 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, (LPSTR)str.data(), str.size(), NULL, NULL);
	return str;
}

// CMultipleCameraDlg �Ի���

// ����������Ƿ���Ч
bool IsValidHandle(dvpHandle handle)
{
	bool bValidHandle;
	dvpStatus status = dvpIsValid(handle, &bValidHandle);
	ASSERT(status == DVP_STATUS_OK);
	return bValidHandle;
}

// ���ڻ�ȡ�����Ƶ���Ļص�����
INT CMultipleCameraDlg::OnDrawPicture(dvpHandle handle,
	dvpStreamEvent event, 
	void *pContext, 
	dvpFrame *pFrame, 
	void *pBuffer)
{
	// �ڻص�������Ԥ����Ƶ
	CWnd *pWnd = ((CWnd*)pContext);

	// ����ֻ��ʾ���������Ƶ��ͼ����������ص������в��˽��к�ʱ�ϳ��Ĳ���������Ӱ��֡�ʺ�ͼ��ɼ���ʵʱ�ԣ�
	// ��ʱ��õ�ͼ�����ݻ��棬ֻ�ڱ���������ǰ��Ч�����˰ѻ���ָ�봫�ݳ�ȥ�����ǣ��û��������������ڴ棬����ͼ�����ݣ�
	dvpStatus status = dvpDrawPicture(	pFrame, 
										pBuffer, 
										pWnd->GetSafeHwnd(),
										nullptr, 
										nullptr);
	
	// ����0����ʾͼ�������Ѿ����Զ����������ٱ�ʹ��
	return 0;
}


CMultipleCameraDlg::CMultipleCameraDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMultipleCameraDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMultipleCameraDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DEVICES1, m_listDevices1);
	DDX_Control(pDX, IDC_COMBO_DEVICES2, m_listDevices2);
	DDX_Control(pDX, IDC_COMBO_DEVICES3, m_listDevices3);
	DDX_Control(pDX, IDC_COMBO_DEVICES4, m_listDevices4);
}

BEGIN_MESSAGE_MAP(CMultipleCameraDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SCAN1, &CMultipleCameraDlg::OnBnClickedButtonScan1)
	ON_BN_CLICKED(IDC_BUTTON_SCAN2, &CMultipleCameraDlg::OnBnClickedButtonScan2)
	ON_BN_CLICKED(IDC_BUTTON_SCAN3, &CMultipleCameraDlg::OnBnClickedButtonScan3)
	ON_BN_CLICKED(IDC_BUTTON_SCAN4, &CMultipleCameraDlg::OnBnClickedButtonScan4)
	ON_BN_CLICKED(IDC_BUTTON_OPEN1, &CMultipleCameraDlg::OnBnClickedButtonOpen1)
	ON_BN_CLICKED(IDC_BUTTON_OPEN2, &CMultipleCameraDlg::OnBnClickedButtonOpen2)
	ON_BN_CLICKED(IDC_BUTTON_OPEN3, &CMultipleCameraDlg::OnBnClickedButtonOpen3)
	ON_BN_CLICKED(IDC_BUTTON_OPEN4, &CMultipleCameraDlg::OnBnClickedButtonOpen4)
	ON_BN_CLICKED(IDC_BUTTON_PROPERTY1, &CMultipleCameraDlg::OnBnClickedButtonProperty1)
	ON_BN_CLICKED(IDC_BUTTON_PROPERTY2, &CMultipleCameraDlg::OnBnClickedButtonProperty2)
	ON_BN_CLICKED(IDC_BUTTON_PROPERTY3, &CMultipleCameraDlg::OnBnClickedButtonProperty3)
	ON_BN_CLICKED(IDC_BUTTON_PROPERTY4, &CMultipleCameraDlg::OnBnClickedButtonProperty4)
	ON_BN_CLICKED(IDC_BUTTON_SET1, &CMultipleCameraDlg::OnBnClickedButtonSet1)
	ON_BN_CLICKED(IDC_BUTTON_SET2, &CMultipleCameraDlg::OnBnClickedButtonSet2)
	ON_BN_CLICKED(IDC_BUTTON_SET3, &CMultipleCameraDlg::OnBnClickedButtonSet3)
	ON_BN_CLICKED(IDC_BUTTON_SET4, &CMultipleCameraDlg::OnBnClickedButtonSet4)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_BIND, &CMultipleCameraDlg::OnBnClickedButtonSaveBind)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_BIND, &CMultipleCameraDlg::OnBnClickedButtonLoadBind)
	ON_BN_CLICKED(IDC_BUTTON_PLAY1, &CMultipleCameraDlg::OnBnClickedButtonPlay1)
	ON_BN_CLICKED(IDC_BUTTON_PLAY2, &CMultipleCameraDlg::OnBnClickedButtonPlay2)
	ON_BN_CLICKED(IDC_BUTTON_PLAY3, &CMultipleCameraDlg::OnBnClickedButtonPlay3)
	ON_BN_CLICKED(IDC_BUTTON_PLAY4, &CMultipleCameraDlg::OnBnClickedButtonPlay4)
END_MESSAGE_MAP()


BOOL CMultipleCameraDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// ��ʼ��������id
	m_handle[0] = 0;
	m_handle[1] = 0;
	m_handle[2] = 0;
	m_handle[3] = 0;

	// Ԥ��ɨ������豸
	OnBnClickedButtonScan1();
	OnBnClickedButtonScan2();
	OnBnClickedButtonScan3();
	OnBnClickedButtonScan4();

	return TRUE;  
}

void CMultipleCameraDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	for (UINT i = 0; i < 4; i++)
	{
		if(IsValidHandle(m_handle[i]))
		{
			dvpStatus status = dvpClose(m_handle[i]);
			ASSERT(status == DVP_STATUS_OK);

			m_handle[i] = 0;
		}
	}
}


void CMultipleCameraDlg::OnPaint()
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


HCURSOR CMultipleCameraDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// ���ݡ�user id���������
BOOL CMultipleCameraDlg::OpenByUserId(const std::string &UserId, dvpHandle *pHandle)
{
	if(UserId.empty())
	{
		return FALSE;
	}

	dvpStatus status;
	dvpCameraInfo info;
	dvpUint32 nCameraCount;

	// ֻ����ˢ�������Ŀ�����ܽ��к��������ö��
	status = dvpRefresh(&nCameraCount);
	ASSERT(status == DVP_STATUS_OK);

	for (UINT i = 0; i < nCameraCount; i++)
	{
		// ���θ���������ö�����
		status = dvpEnum(i, &info);
		ASSERT(status == DVP_STATUS_OK);

		// �Ա�ö����������ġ�user id�����жϣ��Ƿ�ΪѰ�Ҷ���
		if (UserId == info.UserID)
		{
			// �ɹ��ҵ�������ٸ��� FriendlyName ���������ͬʱ�õ�������
			status = dvpOpenByName(info.FriendlyName, OPEN_NORMAL, pHandle);
			if (status == DVP_STATUS_OK)
			{
				return TRUE;
			}
			else
			{
				// �����ʧ�ܣ������״̬����һ����Ӧ�Ĳο��ַ���
				// ע�⣺���ַ�������δ�㶨�����ܻ������ԺͰ汾�������仯
				MessageBox(_T("��ʧ��"));
				return FALSE;
			}

		}
	}
	return FALSE;
}


// ��ʼ����1̨���
void CMultipleCameraDlg::InitCtrls1()
{
	dvpStatus status;
	if (IsValidHandle(m_handle[0]))
	{
		// ��ʱ�Ѿ����豸����
		dvpCameraInfo info;
		dvpStreamState state;
		status = dvpGetStreamState(m_handle[0], &state);
		ASSERT(status == DVP_STATUS_OK);

		// ���û������ܿؼ�
		GetDlgItem(IDC_BUTTON_OPEN1)->SetWindowText(_T("Close"));
		GetDlgItem(IDC_BUTTON_PLAY1)->SetWindowText(state == STATE_STARTED ? _T("Stop") : _T("Start"));
		GetDlgItem(IDC_BUTTON_PLAY1)->EnableWindow(TRUE);
	
		// ���ñ�ʾ����ع��ܿؼ���ʹ��״̬
		GetDlgItem(IDC_BUTTON_PROPERTY1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_USER_ID1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SET1)->EnableWindow(TRUE);

		// ��ȡ�����Ϣ
		dvpGetCameraInfo(m_handle[0], &info);
		ASSERT(status == DVP_STATUS_OK);

		GetDlgItem(IDC_STATIC_OPEN1)->SetWindowText(a2w(info.FriendlyName).c_str());
		GetDlgItem(IDC_EDIT_USER_ID1)->SetWindowText(a2w(info.UserID).c_str());
	}
	else
	{
		// ��ʱ��û���豸����
		// ���û������ܿؼ�
		GetDlgItem(IDC_BUTTON_OPEN1)->SetWindowText(_T("Open"));
		GetDlgItem(IDC_STATIC_OPEN1)->SetWindowText(_T("Friendly Name"));
		GetDlgItem(IDC_BUTTON_PLAY1)->EnableWindow(FALSE);

		// ����ʾ����ع��ܿؼ���ʹ��״̬
		GetDlgItem(IDC_BUTTON_PROPERTY1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_USER_ID1)->SetWindowText(NULL);
		GetDlgItem(IDC_STATIC_PREVIEW1)->InvalidateRect(NULL);
		GetDlgItem(IDC_BUTTON_SET1)->EnableWindow(FALSE);
	}
}

// ��ʼ����2̨���
void CMultipleCameraDlg::InitCtrls2()
{
	dvpStatus status;
	if (IsValidHandle(m_handle[1]))
	{
		// ��ʱ�Ѿ����豸����
		dvpCameraInfo info;
		dvpStreamState state;
		status = dvpGetStreamState(m_handle[1], &state);
		ASSERT(status == DVP_STATUS_OK);

		// ���û������ܿؼ�
		GetDlgItem(IDC_BUTTON_OPEN2)->SetWindowText(_T("Close"));
		GetDlgItem(IDC_BUTTON_PLAY2)->SetWindowText(state == STATE_STARTED ? _T("Stop") : _T("Start"));
		GetDlgItem(IDC_BUTTON_PLAY2)->EnableWindow(TRUE);

		// ���ñ�ʾ����ع��ܿؼ���ʹ��״̬
		GetDlgItem(IDC_BUTTON_PROPERTY2)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_USER_ID2)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SET2)->EnableWindow(TRUE);	

		// ��ȡ�����Ϣ
		dvpGetCameraInfo(m_handle[1], &info);
		ASSERT(status == DVP_STATUS_OK);

		GetDlgItem(IDC_STATIC_OPEN2)->SetWindowText(a2w(info.FriendlyName).c_str());
		GetDlgItem(IDC_EDIT_USER_ID2)->SetWindowText(a2w(info.UserID).c_str());
	}
	else
	{
		// ��ʱ��û���豸����
		// ���û������ܿؼ�
		GetDlgItem(IDC_BUTTON_OPEN2)->SetWindowText(_T("Open"));
		GetDlgItem(IDC_STATIC_OPEN2)->SetWindowText(_T("Friendly Name"));
		GetDlgItem(IDC_BUTTON_PLAY2)->EnableWindow(FALSE);

		// ���ñ�ʾ����ع��ܿؼ���ʹ��״̬
		GetDlgItem(IDC_EDIT_USER_ID2)->SetWindowText(NULL);
		GetDlgItem(IDC_STATIC_PREVIEW2)->InvalidateRect(NULL);	
		GetDlgItem(IDC_BUTTON_PROPERTY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SET2)->EnableWindow(FALSE);
	}
}

// ��ʼ����3̨���
void CMultipleCameraDlg::InitCtrls3()
{
	dvpStatus status;
	if (IsValidHandle(m_handle[2]))
	{
		// ��ʱ�Ѿ����豸��
		dvpCameraInfo info;	
		dvpStreamState state;
		status = dvpGetStreamState(m_handle[2], &state);
		ASSERT(status == DVP_STATUS_OK);

		// ���û������ܿؼ�
		GetDlgItem(IDC_BUTTON_OPEN3)->SetWindowText(_T("Close"));
		GetDlgItem(IDC_BUTTON_PLAY3)->SetWindowText(state == STATE_STARTED ? _T("Stop") : _T("Start"));
		GetDlgItem(IDC_BUTTON_PLAY3)->EnableWindow(TRUE);

		// ���ñ�ʾ����ع��ܿؼ���ʹ��״̬
		GetDlgItem(IDC_BUTTON_PROPERTY3)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_USER_ID3)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SET3)->EnableWindow(TRUE);	

		// ��������Ϣ
		dvpGetCameraInfo(m_handle[2], &info);
		ASSERT(status == DVP_STATUS_OK);

		GetDlgItem(IDC_STATIC_OPEN3)->SetWindowText(a2w(info.FriendlyName).c_str());
		GetDlgItem(IDC_EDIT_USER_ID3)->SetWindowText(a2w(info.UserID).c_str());
	}
	else
	{
		// ��ʱ��û���豸����
		// ���û������ܿؼ�
		GetDlgItem(IDC_BUTTON_OPEN3)->SetWindowText(_T("Open"));
		GetDlgItem(IDC_STATIC_OPEN3)->SetWindowText(_T("Friendly Name"));
		GetDlgItem(IDC_BUTTON_PLAY3)->EnableWindow(FALSE);

		// ���ñ�ʾ����ع��ܿؼ���ʹ��״̬
		GetDlgItem(IDC_EDIT_USER_ID3)->SetWindowText(NULL);
		GetDlgItem(IDC_STATIC_PREVIEW3)->InvalidateRect(NULL);
		GetDlgItem(IDC_BUTTON_PROPERTY3)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SET3)->EnableWindow(FALSE);
	}
}

// ��ʼ����4̨���
void CMultipleCameraDlg::InitCtrls4()
{
	dvpStatus status;
	if (IsValidHandle(m_handle[3]))
	{
		// ��ʱ�Ѿ����豸����
		dvpCameraInfo info;	
		dvpStreamState state;
		status = dvpGetStreamState(m_handle[3], &state);
		ASSERT(status == DVP_STATUS_OK);

		// ���û������ܿؼ�
		GetDlgItem(IDC_BUTTON_OPEN4)->SetWindowText(_T("Close"));
		GetDlgItem(IDC_BUTTON_PLAY4)->SetWindowText(state == STATE_STARTED ? _T("Stop") : _T("Start"));
		GetDlgItem(IDC_BUTTON_PLAY4)->EnableWindow(TRUE);

		// ���ñ�ʾ����ع��ܿؼ���ʹ��״̬
		GetDlgItem(IDC_BUTTON_PROPERTY4)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_USER_ID4)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SET4)->EnableWindow(TRUE);	

		// ��ȡ�����Ϣ
		dvpGetCameraInfo(m_handle[3], &info);
		ASSERT(status == DVP_STATUS_OK);

		GetDlgItem(IDC_STATIC_OPEN4)->SetWindowText(a2w(info.FriendlyName).c_str());
		GetDlgItem(IDC_EDIT_USER_ID4)->SetWindowText(a2w(info.UserID).c_str());
	}
	else
	{
		// ��ʱ��û���豸����
		// ���û������ܿؼ�
		GetDlgItem(IDC_BUTTON_OPEN4)->SetWindowText(_T("Open"));
		GetDlgItem(IDC_STATIC_OPEN4)->SetWindowText(_T("Friendly Name"));
		GetDlgItem(IDC_BUTTON_PLAY4)->EnableWindow(FALSE);

		// ���ñ�ʾ����ع��ܿؼ���ʹ��״̬
		GetDlgItem(IDC_EDIT_USER_ID4)->SetWindowText(NULL);
		GetDlgItem(IDC_STATIC_PREVIEW4)->InvalidateRect(NULL);
		GetDlgItem(IDC_BUTTON_PROPERTY4)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SET4)->EnableWindow(FALSE);
	}
}

void CMultipleCameraDlg::OnBnClickedButtonScan1()
{
	dvpStatus status;
	dvpUint32 i,n = 0;
	dvpCameraInfo info = {0};

	// ��ʱ��nΪ�ɹ�ö�ٵ����������������ӵ������б��У������б��е�����Ϊÿ�������FriendlyName
	m_listDevices1.ResetContent();

	// ��õ�ǰ�����ӵ��������
	status = dvpRefresh(&n);
	ASSERT(status == DVP_STATUS_OK);

	if (status == DVP_STATUS_OK)
	{
		// ö�����16̨���
		if (n > 16)
			n = 16;

		for  (i = 0; i < n; i++)
		{
			// ���ö�ٳ�ÿ���������Ϣ
			status = dvpEnum(i, &info);
			ASSERT(status == DVP_STATUS_OK);

			if (status == DVP_STATUS_OK)
			{
				// ����ʹ�õ���UNICODE��ö�ٵ��豸��ϢΪANSI�ַ�������Ҫ��ANSIתUNICODE
				m_listDevices1.AddString(a2w(info.FriendlyName).c_str());
			}
		}

		if (i != 0)
		{
			m_listDevices1.SetCurSel(0);
		}

		InitCtrls1();
	}
}


void CMultipleCameraDlg::OnBnClickedButtonScan2()
{
	dvpStatus status;
	dvpUint32 i,n = 0;
	dvpCameraInfo info = {0};

	// ��ʱ��nΪ�ɹ�ö�ٵ����������������ӵ������б��У������б��е�����Ϊÿ�������FriendlyName
	m_listDevices2.ResetContent();

	// ��õ�ǰ�����ӵ��������
	status = dvpRefresh(&n);
	ASSERT(status == DVP_STATUS_OK);

	if (status == DVP_STATUS_OK)
	{
		// ö�����16̨���
		if (n > 16)
			n = 16;

		for (i = 0; i < n; i++)
		{
			// ���ö�ٳ�ÿ���������Ϣ
			status = dvpEnum(i, &info);
			ASSERT(status == DVP_STATUS_OK);

			if (status == DVP_STATUS_OK)
			{
				// ����ʹ�õ���UNICODE��ö�ٵ��豸��ϢΪANSI�ַ�������Ҫ��ANSIתUNICODE
				m_listDevices2.AddString(a2w(info.FriendlyName).c_str());
			}
		}

		if (i != 0)
		{
			m_listDevices2.SetCurSel(1);
		}

		InitCtrls2();
	}
}


void CMultipleCameraDlg::OnBnClickedButtonScan3()
{
	dvpStatus status;
	dvpUint32 i,n = 0;
	dvpCameraInfo info = {0};

	// ��ʱ��nΪ�ɹ�ö�ٵ����������������ӵ������б��У������б��е�����Ϊÿ�������FriendlyName
	m_listDevices3.ResetContent();

	// ��õ�ǰ�����ӵ��������
	status = dvpRefresh(&n);
	ASSERT(status == DVP_STATUS_OK);

	if (status == DVP_STATUS_OK)
	{
		// ö�����16̨���
		if (n > 16)
			n = 16;

		for (i = 0; i < n; i++)
		{
			// ���ö�ٳ�ÿ���������Ϣ
			status = dvpEnum(i, &info);
			ASSERT(status == DVP_STATUS_OK);

			if (status == DVP_STATUS_OK)
			{
				// ����ʹ�õ���UNICODE��ö�ٵ��豸��ϢΪANSI�ַ�������Ҫ��ANSIתUNICODE
				m_listDevices3.AddString(a2w(info.FriendlyName).c_str());
			}
		}

		if (i != 0)
		{
			m_listDevices3.SetCurSel(2);
		}

		InitCtrls3();
	}
}


void CMultipleCameraDlg::OnBnClickedButtonScan4()
{
	dvpStatus status;
	dvpUint32 i,n = 0;
	dvpCameraInfo info = {0};

	// ��ʱ��nΪ�ɹ�ö�ٵ����������������ӵ������б��У������б��е�����Ϊÿ�������FriendlyName
	m_listDevices4.ResetContent();

	// ��õ�ǰ�����ӵ��������
	status = dvpRefresh(&n);
	ASSERT(status == DVP_STATUS_OK);

	if (status == DVP_STATUS_OK)
	{
		// ö�����16̨���
		if (n > 16)
			n = 16;

		for (i = 0; i < n; i++)
		{
			// ���ö�ٳ�ÿ���������Ϣ
			status = dvpEnum(i, &info);
			ASSERT(status == DVP_STATUS_OK);

			if (status == DVP_STATUS_OK)
			{
				// ����ʹ�õ���UNICODE��ö�ٵ��豸��ϢΪANSI�ַ�������Ҫ��ANSIתUNICODE
				m_listDevices4.AddString(a2w(info.FriendlyName).c_str());
			}
		}

		if (i != 0)
		{
			m_listDevices4.SetCurSel(3);
		}

		InitCtrls4();
	}

}


void CMultipleCameraDlg::OnBnClickedButtonOpen1()
{
	dvpStatus status;
	CString strName;

	if (!IsValidHandle(m_handle[0]))
	{
		m_listDevices1.GetWindowText(strName);
		if (strName != "")
		{
			// ͨ��ö�ٵ���ѡ���FriendlyName��ָ���豸
			status = dvpOpenByName(w2a(strName).c_str(), OPEN_NORMAL, &m_handle[0]);
			if (status != DVP_STATUS_OK)
			{
				MessageBox(_T("��ʧ��"));
			}	
			else
			{
				// �����Ҫͼ����ʾ������ע��ص��������ڻص���������ɻ�ͼ����
				// ע�⣺�ص�������ִ�еĻ�ͼ���������ܻ��dvpGetFrame�ӿڻ�ȡ��ͼ�����������ʱ
				dvpRegisterStreamCallback(m_handle[0], OnDrawPicture, STREAM_EVENT_PROCESSED, GetDlgItem(IDC_STATIC_PREVIEW1));	
			}
		}
	}

	else
	{
		status = dvpClose(m_handle[0]);
		ASSERT(status == DVP_STATUS_OK);
		m_handle[0] = 0;
		GetDlgItem(IDC_STATIC_PREVIEW1)->InvalidateRect(NULL);
	}
	InitCtrls1();
}


void CMultipleCameraDlg::OnBnClickedButtonOpen2()
{
	dvpStatus status;
	CString strName;

	if (!IsValidHandle(m_handle[1]))
	{
		m_listDevices2.GetWindowText(strName);
		if (strName != "")
		{
			// ͨ��ö�ٵ���ѡ���FriendlyName��ָ���豸
			status = dvpOpenByName(w2a(strName).c_str(), OPEN_NORMAL, &m_handle[1]);
			if (status != DVP_STATUS_OK)
			{
				MessageBox(_T("��ʧ��"));
			}
			else
			{
				// �����Ҫͼ����ʾ������ע��ص��������ڻص���������ɻ�ͼ����
				// ע�⣺�ص�������ִ�еĻ�ͼ���������ܻ��dvpGetFrame�ӿڻ�ȡ��ͼ�����������ʱ
				dvpRegisterStreamCallback(m_handle[1], OnDrawPicture, STREAM_EVENT_PROCESSED, GetDlgItem(IDC_STATIC_PREVIEW2));	
			}
		}
	}
	else
	{
		status = dvpClose(m_handle[1]);
		ASSERT(status == DVP_STATUS_OK);
		m_handle[1] = 0;
		GetDlgItem(IDC_STATIC_PREVIEW2)->InvalidateRect(NULL);
	}
	InitCtrls2();
}


void CMultipleCameraDlg::OnBnClickedButtonOpen3()
{
	dvpStatus status;
	CString strName;

	if (!IsValidHandle(m_handle[2]))
	{
		m_listDevices3.GetWindowText(strName);
		if (strName != "")
		{
			// ͨ��ö�ٵ���ѡ���FriendlyName��ָ���豸
			status = dvpOpenByName(w2a(strName).c_str(), OPEN_NORMAL, &m_handle[2]);
			if (status != DVP_STATUS_OK)
			{
				MessageBox(_T("��ʧ��"));
			}
			else
			{
				// �����Ҫͼ����ʾ������ע��ص��������ڻص���������ɻ�ͼ����
				// ע�⣺�ص�������ִ�еĻ�ͼ���������ܻ��dvpGetFrame�ӿڻ�ȡ��ͼ�����������ʱ
				dvpRegisterStreamCallback(m_handle[2], OnDrawPicture, STREAM_EVENT_PROCESSED, GetDlgItem(IDC_STATIC_PREVIEW3));
			}
		}
	}
	else
	{
		status = dvpClose(m_handle[2]);
		ASSERT(status == DVP_STATUS_OK);
		m_handle[2] = 0;
		GetDlgItem(IDC_STATIC_PREVIEW3)->InvalidateRect(NULL);
	}
	InitCtrls3();
}

 
void CMultipleCameraDlg::OnBnClickedButtonOpen4()
{
	dvpStatus status;
	CString strName;

	if (!IsValidHandle(m_handle[3]))
	{
		m_listDevices4.GetWindowText(strName);
		if (strName != "")
		{
			// ͨ��ö�ٵ���ѡ���FriendlyName��ָ���豸
			status = dvpOpenByName(w2a(strName).c_str(), OPEN_NORMAL, &m_handle[3]);
			if (status != DVP_STATUS_OK)
			{
				MessageBox(_T("��ʧ��"));
			}
			else
			{
				// �����Ҫͼ����ʾ������ע��ص��������ڻص���������ɻ�ͼ����
				// ע�⣺�ص�������ִ�еĻ�ͼ���������ܻ��dvpGetFrame�ӿڻ�ȡ��ͼ�����������ʱ
				dvpRegisterStreamCallback(m_handle[3], OnDrawPicture, STREAM_EVENT_PROCESSED, GetDlgItem(IDC_STATIC_PREVIEW4));
			}
		}
	}
	else
	{
		status = dvpClose(m_handle[3]);
		ASSERT(status == DVP_STATUS_OK);
		m_handle[3] = 0;
		GetDlgItem(IDC_STATIC_PREVIEW4)->InvalidateRect(NULL);
	}
	InitCtrls4();
}

// ��ʾ�������öԻ���
void CMultipleCameraDlg::OnBnClickedButtonProperty1()
{
	if (IsValidHandle(m_handle[0]))
	{
		dvpStatus status = dvpShowPropertyModalDialog(m_handle[0], GetSafeHwnd());
	}
}

void CMultipleCameraDlg::OnBnClickedButtonProperty2()
{
	if (IsValidHandle(m_handle[1]))
	{
		dvpStatus status = dvpShowPropertyModalDialog(m_handle[1], GetSafeHwnd());
	}
}

void CMultipleCameraDlg::OnBnClickedButtonProperty3()
{
	if (IsValidHandle(m_handle[2]))
	{
		dvpStatus status = dvpShowPropertyModalDialog(m_handle[2], GetSafeHwnd());
	}
}

void CMultipleCameraDlg::OnBnClickedButtonProperty4()
{
	if (IsValidHandle(m_handle[3]))
	{
		dvpStatus status = dvpShowPropertyModalDialog(m_handle[3], GetSafeHwnd());
	}
}

// ���õ�0̨����ġ�user id��
void CMultipleCameraDlg::OnBnClickedButtonSet1()
{
	if (IsValidHandle(m_handle[0]))
	{
		CString str;
		GetDlgItem(IDC_EDIT_USER_ID1)->GetWindowText(str);
		UINT Length = str.GetLength();
		
		// �����û�ID
		dvpStatus status = dvpSetUserId(m_handle[0], w2a(str.GetBuffer()).c_str(), &Length);
		ASSERT(status == DVP_STATUS_OK);

		GetDlgItem(IDC_BUTTON_SAVE_BIND)->EnableWindow(TRUE);
	}
}

// ���õ�1̨����ġ�user id��
void CMultipleCameraDlg::OnBnClickedButtonSet2()
{
	if (IsValidHandle(m_handle[1]))
	{
		CString str;
		GetDlgItem(IDC_EDIT_USER_ID2)->GetWindowText(str);
		UINT Length = str.GetLength();
		
		// �����û�ID
		dvpStatus status = dvpSetUserId(m_handle[1], w2a(str.GetBuffer()).c_str(), &Length);
		ASSERT(status == DVP_STATUS_OK);

		GetDlgItem(IDC_BUTTON_SAVE_BIND)->EnableWindow(TRUE);
	}
}

// ���õ�2̨����ġ�user id��
void CMultipleCameraDlg::OnBnClickedButtonSet3()
{
	if (IsValidHandle(m_handle[2]))
	{
		CString str;
		GetDlgItem(IDC_EDIT_USER_ID3)->GetWindowText(str);
		UINT Length = str.GetLength();
		
		// �����û�ID
		dvpStatus status = dvpSetUserId(m_handle[2], w2a(str.GetBuffer()).c_str(), &Length);
		ASSERT(status == DVP_STATUS_OK);

		GetDlgItem(IDC_BUTTON_SAVE_BIND)->EnableWindow(TRUE);
	}
}

// ���õ�3̨����ġ�user id��
void CMultipleCameraDlg::OnBnClickedButtonSet4()
{
	if (IsValidHandle(m_handle[3]))
	{
		CString str;
		GetDlgItem(IDC_EDIT_USER_ID4)->GetWindowText(str);
		UINT Length = str.GetLength();
	
		// �����û�ID
		dvpStatus status = dvpSetUserId(m_handle[3], w2a(str.GetBuffer()).c_str(), &Length);
		ASSERT(status == DVP_STATUS_OK);

		GetDlgItem(IDC_BUTTON_SAVE_BIND)->EnableWindow(TRUE);
	}
}


void CMultipleCameraDlg::OnBnClickedButtonSaveBind()
{
	CString strUserId0, strUserId1, strUserId2, strUserId3;
	GetDlgItem(IDC_EDIT_USER_ID1)->GetWindowText(strUserId0);
	GetDlgItem(IDC_EDIT_USER_ID2)->GetWindowText(strUserId1);
	GetDlgItem(IDC_EDIT_USER_ID3)->GetWindowText(strUserId2);
	GetDlgItem(IDC_EDIT_USER_ID4)->GetWindowText(strUserId3);

	// �ա�user id���ļ���
	UINT nNotEmptyCount = 0;
	std::set<CString> check;

	// ��������ظ���"user id"������󶨹�ϵ�޷�����
	if (!strUserId0.IsEmpty()) {check.insert(strUserId0); nNotEmptyCount++;}
	if (!strUserId1.IsEmpty()) {check.insert(strUserId1); nNotEmptyCount++;}
	if (!strUserId2.IsEmpty()) {check.insert(strUserId2); nNotEmptyCount++;}
	if (!strUserId3.IsEmpty()) {check.insert(strUserId3); nNotEmptyCount++;}

	// �жϳ��ա�user id�����Ƿ�����ظ���
	if (check.size() != nNotEmptyCount)
	{
		// ��������ظ�����ܾ�����󶨹�ϵ
		MessageBox(_T("User id repetition"), _T("Save Failed"), MB_ICONSTOP);
		return;
	}

	// ����������ظ��ġ�user id���򽫰󶨹�ϵ���浽ע���
	AfxGetApp()->WriteProfileString(_T("UserId"), _T("0"), strUserId0);
	AfxGetApp()->WriteProfileString(_T("UserId"), _T("1"), strUserId1);
	AfxGetApp()->WriteProfileString(_T("UserId"), _T("2"), strUserId2);
	AfxGetApp()->WriteProfileString(_T("UserId"), _T("3"), strUserId3);

	GetDlgItem(IDC_BUTTON_SAVE_BIND)->EnableWindow(FALSE);
}


void CMultipleCameraDlg::OnBnClickedButtonLoadBind()
{
	CString strUserId0 = AfxGetApp()->GetProfileString(_T("UserId"), _T("0"));
	CString strUserId1 = AfxGetApp()->GetProfileString(_T("UserId"), _T("1"));
	CString strUserId2 = AfxGetApp()->GetProfileString(_T("UserId"), _T("2"));
	CString strUserId3 = AfxGetApp()->GetProfileString(_T("UserId"), _T("3"));

	// �ա�user id���ļ���
	UINT nNotEmptyCount = 0;
	std::set<CString> check;

	// ��������ظ���"user id"������󶨹�ϵ�޷�����
	if (!strUserId0.IsEmpty()) {check.insert(strUserId0); nNotEmptyCount++;}
	if (!strUserId1.IsEmpty()) {check.insert(strUserId1); nNotEmptyCount++;}
	if (!strUserId2.IsEmpty()) {check.insert(strUserId2); nNotEmptyCount++;}
	if (!strUserId3.IsEmpty()) {check.insert(strUserId3); nNotEmptyCount++;}

	if (check.size() != nNotEmptyCount)
	{
		MessageBox(_T("User id repetition"), _T("Save Failed"), MB_ICONSTOP);
		return;
	}

	//������Ѵ򿪣�������ر����
	for (UINT i = 0; i < 4; i++)
	{
		if (IsValidHandle(m_handle[i]))
		{
			dvpStatus status = dvpClose(m_handle[i]);
			ASSERT(status == DVP_STATUS_OK);

			m_handle[i] = 0;
		}
	}

	// �����û�ID�����
	OpenByUserId(w2a(strUserId0.GetBuffer()), &m_handle[0]);
	OpenByUserId(w2a(strUserId1.GetBuffer()), &m_handle[1]);
	OpenByUserId(w2a(strUserId2.GetBuffer()), &m_handle[2]);
	OpenByUserId(w2a(strUserId3.GetBuffer()), &m_handle[3]);

	// ��ʼ�����
	InitCtrls1();
	InitCtrls2();
	InitCtrls3();
	InitCtrls4();
}


void CMultipleCameraDlg::OnBnClickedButtonPlay1()
{
	if (IsValidHandle(m_handle[0]))
	{
		dvpStreamState state;
		dvpStatus status;

		// ���ݵ�ǰ��Ƶ״̬��ִ���෴�Ĳ�����ʵ��һ����ť������������ֹͣ
		status = dvpGetStreamState(m_handle[0], &state);
		ASSERT(status == DVP_STATUS_OK);

		if (state == STATE_STARTED)
		{
			status = dvpStop(m_handle[0]);
		}
		else
		{
			status = dvpStart(m_handle[0]);
			
		}

		ASSERT(status == DVP_STATUS_OK);
		InitCtrls1();
	}
}


void CMultipleCameraDlg::OnBnClickedButtonPlay2()
{
	if (IsValidHandle(m_handle[1]))
	{
		dvpStreamState state;
		dvpStatus status;

		// ���ݵ�ǰ��Ƶ״̬��ִ���෴�Ĳ�����ʵ��һ����ť������������ֹͣ
		status = dvpGetStreamState(m_handle[1], &state);
		ASSERT(status == DVP_STATUS_OK);

		if (state == STATE_STARTED)
		{
			status = dvpStop(m_handle[1]);
			
		}
		else
		{
			status = dvpStart(m_handle[1]);
		}

		ASSERT(status == DVP_STATUS_OK);
		InitCtrls2();
	}
}


void CMultipleCameraDlg::OnBnClickedButtonPlay3()
{
	if (IsValidHandle(m_handle[2]))
	{
		dvpStreamState state;
		dvpStatus status;

		// ���ݵ�ǰ��Ƶ״̬��ִ���෴�Ĳ�����ʵ��һ����ť������������ֹͣ
		status = dvpGetStreamState(m_handle[2], &state);
		ASSERT(status == DVP_STATUS_OK);

		if (state == STATE_STARTED)
		{
			status = dvpStop(m_handle[2]);
		}
		else
		{
			status = dvpStart(m_handle[2]);
		}

		ASSERT(status == DVP_STATUS_OK);
		InitCtrls3();
	}
}


void CMultipleCameraDlg::OnBnClickedButtonPlay4()
{
	if (IsValidHandle(m_handle[3]))
	{
		dvpStreamState state;
		dvpStatus status;

		// ���ݵ�ǰ��Ƶ״̬��ִ���෴�Ĳ�����ʵ��һ����ť������������ͣ
		status = dvpGetStreamState(m_handle[3], &state);
		ASSERT(status == DVP_STATUS_OK);

		if (state == STATE_STARTED)
		{
			status = dvpStop(m_handle[3]);

		}
		else
		{
			status = dvpStart(m_handle[3]);  
		}

		ASSERT(status == DVP_STATUS_OK);
		InitCtrls4();
	}
}

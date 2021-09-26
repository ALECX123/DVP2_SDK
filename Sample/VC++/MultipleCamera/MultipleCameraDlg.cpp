
// MultipleCameraDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MultipleCamera.h"
#include "MultipleCameraDlg.h"
#include "afxdialogex.h" 
#include <set>

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
	MultiByteToWideChar(CP_ACP, 0, str, -1, (LPWSTR)wstr.data(), wstr.size());
	return wstr;
}

// UNICODE字符串转ANSI字符串
std::string w2a(LPCWCH wstr)
{
	std::string str;
	str.resize(WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL) - 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, (LPSTR)str.data(), str.size(), NULL, NULL);
	return str;
}

// CMultipleCameraDlg 对话框

// 检查相机句柄是否有效
bool IsValidHandle(dvpHandle handle)
{
	bool bValidHandle;
	dvpStatus status = dvpIsValid(handle, &bValidHandle);
	ASSERT(status == DVP_STATUS_OK);
	return bValidHandle;
}

// 用于获取相机视频流的回调函数
INT CMultipleCameraDlg::OnDrawPicture(dvpHandle handle,
	dvpStreamEvent event, 
	void *pContext, 
	dvpFrame *pFrame, 
	void *pBuffer)
{
	// 在回调函数中预览视频
	CWnd *pWnd = ((CWnd*)pContext);

	// 这里只演示了最常见的视频绘图操作，建议回调函数中不宜进行耗时较长的操作，以免影响帧率和图像采集的实时性；
	// 此时获得的图像数据缓存，只在本函数返回前有效，不宜把缓存指针传递出去；但是，用户可以自行申请内存，复制图像数据；
	dvpStatus status = dvpDrawPicture(	pFrame, 
										pBuffer, 
										pWnd->GetSafeHwnd(),
										nullptr, 
										nullptr);
	
	// 返回0，表示图像数据已经可以丢弃，将不再被使用
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

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 初始化相机句柄id
	m_handle[0] = 0;
	m_handle[1] = 0;
	m_handle[2] = 0;
	m_handle[3] = 0;

	// 预先扫描相机设备
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


HCURSOR CMultipleCameraDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 根据“user id”来打开相机
BOOL CMultipleCameraDlg::OpenByUserId(const std::string &UserId, dvpHandle *pHandle)
{
	if(UserId.empty())
	{
		return FALSE;
	}

	dvpStatus status;
	dvpCameraInfo info;
	dvpUint32 nCameraCount;

	// 只有先刷新相机数目，才能进行后续的相机枚举
	status = dvpRefresh(&nCameraCount);
	ASSERT(status == DVP_STATUS_OK);

	for (UINT i = 0; i < nCameraCount; i++)
	{
		// 依次根据索引来枚举相机
		status = dvpEnum(i, &info);
		ASSERT(status == DVP_STATUS_OK);

		// 对比枚举所得相机的“user id”来判断，是否为寻找对象
		if (UserId == info.UserID)
		{
			// 成功找到相机，再根据 FriendlyName 来打开相机，同时得到相机句柄
			status = dvpOpenByName(info.FriendlyName, OPEN_NORMAL, pHandle);
			if (status == DVP_STATUS_OK)
			{
				return TRUE;
			}
			else
			{
				// 如果打开失败，则根据状态码获得一个相应的参考字符串
				// 注意：此字符串，并未恒定，可能会随语言和版本而发生变化
				MessageBox(_T("打开失败"));
				return FALSE;
			}

		}
	}
	return FALSE;
}


// 初始化第1台相机
void CMultipleCameraDlg::InitCtrls1()
{
	dvpStatus status;
	if (IsValidHandle(m_handle[0]))
	{
		// 此时已经有设备被打开
		dvpCameraInfo info;
		dvpStreamState state;
		status = dvpGetStreamState(m_handle[0], &state);
		ASSERT(status == DVP_STATUS_OK);

		// 设置基本功能控件
		GetDlgItem(IDC_BUTTON_OPEN1)->SetWindowText(_T("Close"));
		GetDlgItem(IDC_BUTTON_PLAY1)->SetWindowText(state == STATE_STARTED ? _T("Stop") : _T("Start"));
		GetDlgItem(IDC_BUTTON_PLAY1)->EnableWindow(TRUE);
	
		// 设置本示例相关功能控件的使能状态
		GetDlgItem(IDC_BUTTON_PROPERTY1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_USER_ID1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SET1)->EnableWindow(TRUE);

		// 获取相机信息
		dvpGetCameraInfo(m_handle[0], &info);
		ASSERT(status == DVP_STATUS_OK);

		GetDlgItem(IDC_STATIC_OPEN1)->SetWindowText(a2w(info.FriendlyName).c_str());
		GetDlgItem(IDC_EDIT_USER_ID1)->SetWindowText(a2w(info.UserID).c_str());
	}
	else
	{
		// 此时还没有设备被打开
		// 设置基本功能控件
		GetDlgItem(IDC_BUTTON_OPEN1)->SetWindowText(_T("Open"));
		GetDlgItem(IDC_STATIC_OPEN1)->SetWindowText(_T("Friendly Name"));
		GetDlgItem(IDC_BUTTON_PLAY1)->EnableWindow(FALSE);

		// 设置示例相关功能控件的使能状态
		GetDlgItem(IDC_BUTTON_PROPERTY1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_USER_ID1)->SetWindowText(NULL);
		GetDlgItem(IDC_STATIC_PREVIEW1)->InvalidateRect(NULL);
		GetDlgItem(IDC_BUTTON_SET1)->EnableWindow(FALSE);
	}
}

// 初始化第2台相机
void CMultipleCameraDlg::InitCtrls2()
{
	dvpStatus status;
	if (IsValidHandle(m_handle[1]))
	{
		// 此时已经有设备被打开
		dvpCameraInfo info;
		dvpStreamState state;
		status = dvpGetStreamState(m_handle[1], &state);
		ASSERT(status == DVP_STATUS_OK);

		// 设置基本功能控件
		GetDlgItem(IDC_BUTTON_OPEN2)->SetWindowText(_T("Close"));
		GetDlgItem(IDC_BUTTON_PLAY2)->SetWindowText(state == STATE_STARTED ? _T("Stop") : _T("Start"));
		GetDlgItem(IDC_BUTTON_PLAY2)->EnableWindow(TRUE);

		// 设置本示例相关功能控件的使能状态
		GetDlgItem(IDC_BUTTON_PROPERTY2)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_USER_ID2)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SET2)->EnableWindow(TRUE);	

		// 获取相机信息
		dvpGetCameraInfo(m_handle[1], &info);
		ASSERT(status == DVP_STATUS_OK);

		GetDlgItem(IDC_STATIC_OPEN2)->SetWindowText(a2w(info.FriendlyName).c_str());
		GetDlgItem(IDC_EDIT_USER_ID2)->SetWindowText(a2w(info.UserID).c_str());
	}
	else
	{
		// 此时还没有设备被打开
		// 设置基本功能控件
		GetDlgItem(IDC_BUTTON_OPEN2)->SetWindowText(_T("Open"));
		GetDlgItem(IDC_STATIC_OPEN2)->SetWindowText(_T("Friendly Name"));
		GetDlgItem(IDC_BUTTON_PLAY2)->EnableWindow(FALSE);

		// 设置本示例相关功能控件的使能状态
		GetDlgItem(IDC_EDIT_USER_ID2)->SetWindowText(NULL);
		GetDlgItem(IDC_STATIC_PREVIEW2)->InvalidateRect(NULL);	
		GetDlgItem(IDC_BUTTON_PROPERTY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SET2)->EnableWindow(FALSE);
	}
}

// 初始化第3台相机
void CMultipleCameraDlg::InitCtrls3()
{
	dvpStatus status;
	if (IsValidHandle(m_handle[2]))
	{
		// 此时已经有设备打开
		dvpCameraInfo info;	
		dvpStreamState state;
		status = dvpGetStreamState(m_handle[2], &state);
		ASSERT(status == DVP_STATUS_OK);

		// 设置基本功能控件
		GetDlgItem(IDC_BUTTON_OPEN3)->SetWindowText(_T("Close"));
		GetDlgItem(IDC_BUTTON_PLAY3)->SetWindowText(state == STATE_STARTED ? _T("Stop") : _T("Start"));
		GetDlgItem(IDC_BUTTON_PLAY3)->EnableWindow(TRUE);

		// 设置本示例相关功能控件的使能状态
		GetDlgItem(IDC_BUTTON_PROPERTY3)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_USER_ID3)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SET3)->EnableWindow(TRUE);	

		// 获得相机信息
		dvpGetCameraInfo(m_handle[2], &info);
		ASSERT(status == DVP_STATUS_OK);

		GetDlgItem(IDC_STATIC_OPEN3)->SetWindowText(a2w(info.FriendlyName).c_str());
		GetDlgItem(IDC_EDIT_USER_ID3)->SetWindowText(a2w(info.UserID).c_str());
	}
	else
	{
		// 此时还没有设备被打开
		// 设置基本功能控件
		GetDlgItem(IDC_BUTTON_OPEN3)->SetWindowText(_T("Open"));
		GetDlgItem(IDC_STATIC_OPEN3)->SetWindowText(_T("Friendly Name"));
		GetDlgItem(IDC_BUTTON_PLAY3)->EnableWindow(FALSE);

		// 设置本示例相关功能控件的使能状态
		GetDlgItem(IDC_EDIT_USER_ID3)->SetWindowText(NULL);
		GetDlgItem(IDC_STATIC_PREVIEW3)->InvalidateRect(NULL);
		GetDlgItem(IDC_BUTTON_PROPERTY3)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SET3)->EnableWindow(FALSE);
	}
}

// 初始化第4台相机
void CMultipleCameraDlg::InitCtrls4()
{
	dvpStatus status;
	if (IsValidHandle(m_handle[3]))
	{
		// 此时已经有设备被打开
		dvpCameraInfo info;	
		dvpStreamState state;
		status = dvpGetStreamState(m_handle[3], &state);
		ASSERT(status == DVP_STATUS_OK);

		// 设置基本功能控件
		GetDlgItem(IDC_BUTTON_OPEN4)->SetWindowText(_T("Close"));
		GetDlgItem(IDC_BUTTON_PLAY4)->SetWindowText(state == STATE_STARTED ? _T("Stop") : _T("Start"));
		GetDlgItem(IDC_BUTTON_PLAY4)->EnableWindow(TRUE);

		// 设置本示例相关功能控件的使能状态
		GetDlgItem(IDC_BUTTON_PROPERTY4)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_USER_ID4)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SET4)->EnableWindow(TRUE);	

		// 获取相机信息
		dvpGetCameraInfo(m_handle[3], &info);
		ASSERT(status == DVP_STATUS_OK);

		GetDlgItem(IDC_STATIC_OPEN4)->SetWindowText(a2w(info.FriendlyName).c_str());
		GetDlgItem(IDC_EDIT_USER_ID4)->SetWindowText(a2w(info.UserID).c_str());
	}
	else
	{
		// 此时还没有设备被打开
		// 设置基本功能控件
		GetDlgItem(IDC_BUTTON_OPEN4)->SetWindowText(_T("Open"));
		GetDlgItem(IDC_STATIC_OPEN4)->SetWindowText(_T("Friendly Name"));
		GetDlgItem(IDC_BUTTON_PLAY4)->EnableWindow(FALSE);

		// 设置本示例相关功能控件的使能状态
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

	// 此时，n为成功枚举到的相机数量，将添加到下拉列表中，下拉列表中的内容为每个相机的FriendlyName
	m_listDevices1.ResetContent();

	// 获得当前能连接的相机数量
	status = dvpRefresh(&n);
	ASSERT(status == DVP_STATUS_OK);

	if (status == DVP_STATUS_OK)
	{
		// 枚举最多16台相机
		if (n > 16)
			n = 16;

		for  (i = 0; i < n; i++)
		{
			// 逐个枚举出每个相机的信息
			status = dvpEnum(i, &info);
			ASSERT(status == DVP_STATUS_OK);

			if (status == DVP_STATUS_OK)
			{
				// 界面使用的是UNICODE，枚举的设备信息为ANSI字符串，需要将ANSI转UNICODE
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

	// 此时，n为成功枚举到的相机数量，将添加到下拉列表中，下拉列表中的内容为每个相机的FriendlyName
	m_listDevices2.ResetContent();

	// 获得当前能连接的相机数量
	status = dvpRefresh(&n);
	ASSERT(status == DVP_STATUS_OK);

	if (status == DVP_STATUS_OK)
	{
		// 枚举最多16台相机
		if (n > 16)
			n = 16;

		for (i = 0; i < n; i++)
		{
			// 逐个枚举出每个相机的信息
			status = dvpEnum(i, &info);
			ASSERT(status == DVP_STATUS_OK);

			if (status == DVP_STATUS_OK)
			{
				// 界面使用的是UNICODE，枚举的设备信息为ANSI字符串，需要将ANSI转UNICODE
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

	// 此时，n为成功枚举到的相机数量，将添加到下拉列表中，下拉列表中的内容为每个相机的FriendlyName
	m_listDevices3.ResetContent();

	// 获得当前能连接的相机数量
	status = dvpRefresh(&n);
	ASSERT(status == DVP_STATUS_OK);

	if (status == DVP_STATUS_OK)
	{
		// 枚举最多16台相机
		if (n > 16)
			n = 16;

		for (i = 0; i < n; i++)
		{
			// 逐个枚举出每个相机的信息
			status = dvpEnum(i, &info);
			ASSERT(status == DVP_STATUS_OK);

			if (status == DVP_STATUS_OK)
			{
				// 界面使用的是UNICODE，枚举的设备信息为ANSI字符串，需要将ANSI转UNICODE
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

	// 此时，n为成功枚举到的相机数量，将添加到下拉列表中，下拉列表中的内容为每个相机的FriendlyName
	m_listDevices4.ResetContent();

	// 获得当前能连接的相机数量
	status = dvpRefresh(&n);
	ASSERT(status == DVP_STATUS_OK);

	if (status == DVP_STATUS_OK)
	{
		// 枚举最多16台相机
		if (n > 16)
			n = 16;

		for (i = 0; i < n; i++)
		{
			// 逐个枚举出每个相机的信息
			status = dvpEnum(i, &info);
			ASSERT(status == DVP_STATUS_OK);

			if (status == DVP_STATUS_OK)
			{
				// 界面使用的是UNICODE，枚举的设备信息为ANSI字符串，需要将ANSI转UNICODE
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
			// 通过枚举到并选择的FriendlyName打开指定设备
			status = dvpOpenByName(w2a(strName).c_str(), OPEN_NORMAL, &m_handle[0]);
			if (status != DVP_STATUS_OK)
			{
				MessageBox(_T("打开失败"));
			}	
			else
			{
				// 如果需要图像显示，可以注册回调函数，在回调函数中完成绘图操作
				// 注意：回调函数中执行的绘图操作，可能会对dvpGetFrame接口获取的图像数据造成延时
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
			// 通过枚举到并选择的FriendlyName打开指定设备
			status = dvpOpenByName(w2a(strName).c_str(), OPEN_NORMAL, &m_handle[1]);
			if (status != DVP_STATUS_OK)
			{
				MessageBox(_T("打开失败"));
			}
			else
			{
				// 如果需要图像显示，可以注册回调函数，在回调函数中完成绘图操作
				// 注意：回调函数中执行的绘图操作，可能会对dvpGetFrame接口获取的图像数据造成延时
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
			// 通过枚举到并选择的FriendlyName打开指定设备
			status = dvpOpenByName(w2a(strName).c_str(), OPEN_NORMAL, &m_handle[2]);
			if (status != DVP_STATUS_OK)
			{
				MessageBox(_T("打开失败"));
			}
			else
			{
				// 如果需要图像显示，可以注册回调函数，在回调函数中完成绘图操作
				// 注意：回调函数中执行的绘图操作，可能会对dvpGetFrame接口获取的图像数据造成延时
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
			// 通过枚举到并选择的FriendlyName打开指定设备
			status = dvpOpenByName(w2a(strName).c_str(), OPEN_NORMAL, &m_handle[3]);
			if (status != DVP_STATUS_OK)
			{
				MessageBox(_T("打开失败"));
			}
			else
			{
				// 如果需要图像显示，可以注册回调函数，在回调函数中完成绘图操作
				// 注意：回调函数中执行的绘图操作，可能会对dvpGetFrame接口获取的图像数据造成延时
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

// 显示属性设置对话框
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

// 设置第0台相机的“user id”
void CMultipleCameraDlg::OnBnClickedButtonSet1()
{
	if (IsValidHandle(m_handle[0]))
	{
		CString str;
		GetDlgItem(IDC_EDIT_USER_ID1)->GetWindowText(str);
		UINT Length = str.GetLength();
		
		// 设置用户ID
		dvpStatus status = dvpSetUserId(m_handle[0], w2a(str.GetBuffer()).c_str(), &Length);
		ASSERT(status == DVP_STATUS_OK);

		GetDlgItem(IDC_BUTTON_SAVE_BIND)->EnableWindow(TRUE);
	}
}

// 设置第1台相机的“user id”
void CMultipleCameraDlg::OnBnClickedButtonSet2()
{
	if (IsValidHandle(m_handle[1]))
	{
		CString str;
		GetDlgItem(IDC_EDIT_USER_ID2)->GetWindowText(str);
		UINT Length = str.GetLength();
		
		// 设置用户ID
		dvpStatus status = dvpSetUserId(m_handle[1], w2a(str.GetBuffer()).c_str(), &Length);
		ASSERT(status == DVP_STATUS_OK);

		GetDlgItem(IDC_BUTTON_SAVE_BIND)->EnableWindow(TRUE);
	}
}

// 设置第2台相机的“user id”
void CMultipleCameraDlg::OnBnClickedButtonSet3()
{
	if (IsValidHandle(m_handle[2]))
	{
		CString str;
		GetDlgItem(IDC_EDIT_USER_ID3)->GetWindowText(str);
		UINT Length = str.GetLength();
		
		// 设置用户ID
		dvpStatus status = dvpSetUserId(m_handle[2], w2a(str.GetBuffer()).c_str(), &Length);
		ASSERT(status == DVP_STATUS_OK);

		GetDlgItem(IDC_BUTTON_SAVE_BIND)->EnableWindow(TRUE);
	}
}

// 设置第3台相机的“user id”
void CMultipleCameraDlg::OnBnClickedButtonSet4()
{
	if (IsValidHandle(m_handle[3]))
	{
		CString str;
		GetDlgItem(IDC_EDIT_USER_ID4)->GetWindowText(str);
		UINT Length = str.GetLength();
	
		// 设置用户ID
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

	// 空“user id”的计数
	UINT nNotEmptyCount = 0;
	std::set<CString> check;

	// 避免出现重复的"user id"，否则绑定关系无法成立
	if (!strUserId0.IsEmpty()) {check.insert(strUserId0); nNotEmptyCount++;}
	if (!strUserId1.IsEmpty()) {check.insert(strUserId1); nNotEmptyCount++;}
	if (!strUserId2.IsEmpty()) {check.insert(strUserId2); nNotEmptyCount++;}
	if (!strUserId3.IsEmpty()) {check.insert(strUserId3); nNotEmptyCount++;}

	// 判断除空“user id”外是否存在重复的
	if (check.size() != nNotEmptyCount)
	{
		// 如果存在重复，则拒绝保存绑定关系
		MessageBox(_T("User id repetition"), _T("Save Failed"), MB_ICONSTOP);
		return;
	}

	// 如果不存在重复的“user id”则将绑定关系保存到注册表
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

	// 空“user id”的计数
	UINT nNotEmptyCount = 0;
	std::set<CString> check;

	// 避免出现重复的"user id"，否则绑定关系无法成立
	if (!strUserId0.IsEmpty()) {check.insert(strUserId0); nNotEmptyCount++;}
	if (!strUserId1.IsEmpty()) {check.insert(strUserId1); nNotEmptyCount++;}
	if (!strUserId2.IsEmpty()) {check.insert(strUserId2); nNotEmptyCount++;}
	if (!strUserId3.IsEmpty()) {check.insert(strUserId3); nNotEmptyCount++;}

	if (check.size() != nNotEmptyCount)
	{
		MessageBox(_T("User id repetition"), _T("Save Failed"), MB_ICONSTOP);
		return;
	}

	//若相机已打开，则逐个关闭相机
	for (UINT i = 0; i < 4; i++)
	{
		if (IsValidHandle(m_handle[i]))
		{
			dvpStatus status = dvpClose(m_handle[i]);
			ASSERT(status == DVP_STATUS_OK);

			m_handle[i] = 0;
		}
	}

	// 根据用户ID打开相机
	OpenByUserId(w2a(strUserId0.GetBuffer()), &m_handle[0]);
	OpenByUserId(w2a(strUserId1.GetBuffer()), &m_handle[1]);
	OpenByUserId(w2a(strUserId2.GetBuffer()), &m_handle[2]);
	OpenByUserId(w2a(strUserId3.GetBuffer()), &m_handle[3]);

	// 初始化相机
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

		// 根据当前视频状态，执行相反的操作，实现一个按钮既能启动又能停止
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

		// 根据当前视频状态，执行相反的操作，实现一个按钮既能启动又能停止
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

		// 根据当前视频状态，执行相反的操作，实现一个按钮既能启动又能停止
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

		// 根据当前视频状态，执行相反的操作，实现一个按钮既能启动又能停
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

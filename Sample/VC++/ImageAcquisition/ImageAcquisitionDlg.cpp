
// ImageAcquisitionDlg.cpp : 实现文件
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

// CImageAcquisitionDlg 对话框
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
    
    // 加载界面参数
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
    // 保存界面参数
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

// CImageAcquisitionDlg 消息处理程序
BOOL CImageAcquisitionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	// 预先扫描相机设备
	OnBnClickedButtonScan();

	SetTimer(0, 500, NULL);
	return TRUE;  
}

void CImageAcquisitionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);// 用于绘制的设备上下文

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


void CImageAcquisitionDlg::OnSize(UINT nType, int cx, int cy)
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

void CImageAcquisitionDlg::OnTimer(UINT_PTR nIDEvent)
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
            // 通过枚举到并选择的FriendlyName打开指定设备
            status = dvpOpenByName(w2a(strName).c_str(), OPEN_NORMAL, &m_handle);
            if(status != DVP_STATUS_OK)
            {
                MessageBox(_T("打开失败"));
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
		// 此时已经打开了一个设备
		// 以下更新和使能基本功能的控件
		dvpStreamState state;
		status = dvpGetStreamState(m_handle, &state);

		GetDlgItem(IDC_BUTTON_OPEN)->SetWindowText(_T("Close"));
        GetDlgItem(IDC_BUTTON_START)->SetWindowText(state == STATE_STARTED ? _T("Stop") : _T("Start"));
		GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_PROPERTY)->EnableWindow(TRUE);


		// 更新示例相关功能控件
		if (state == STATE_STARTED)
		{
            // 如果采集线程还在继续，禁用一些操作，可以简化多线程同步的问题
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
		// 没有设备被打开
		// 更新基本功能控件
		GetDlgItem(IDC_BUTTON_OPEN)->SetWindowTextW(_T("Open"));
		GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
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

		// 更新示例相关功能的控件
		GetDlgItem(IDC_STATIC_PREVIEW)->InvalidateRect(NULL);
		GetDlgItem(IDC_CHECK_SAVE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_DISPLAY)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SELECTPATH)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SAVEPATH)->EnableWindow(TRUE);
	}
	SendMessage(WM_SIZE);
}

// 在独立的线程中抓取图像，并且根据需要，以帧ID为文件名保存最近的若干帧图像，再将图像显示到预览窗口
UINT CImageAcquisitionDlg::ImageThread()
{
	dvpStatus status;
	SYSTEMTIME m_systm;

	// 等待线程退出事件
	while (WaitForSingleObject(m_evtExit, m_uWaitTimer) != WAIT_OBJECT_0) 
	{
		void *pBuffer;
		dvpFrame frame;

        if (m_bSoftTrigger)
        {
            status = dvpTriggerFire(m_handle);
            if (status != DVP_STATUS_OK)
            {
                // 有可能是触发信号间隔太过密集所导致
                TRACE("dvpTriggerFire操作失败, status:%d\r\n", status);
            }
        }

		// 从视频流中抓取一帧图像，超时时间通常不应小于曝光时间
		status = dvpGetFrame(m_handle, &frame, &pBuffer, m_uGrabTimeout);
		if (status != DVP_STATUS_OK)
		{
            TRACE("dvpGetFrame操作失败, status:%d\r\n", status);
            continue;
		}
	
		// 如果需要保存图像
		if (m_bSave) 
		{
			// 以系统时间为文件名保存新的bmp图像
			::GetLocalTime(&m_systm);
			strFileName.Format(_T("%s\\%d_%d_%d_%d_%d_%d_%d.bmp"),strPicturePath,m_systm.wYear,m_systm.wMonth,m_systm.wDay,m_systm.wHour,m_systm.wMinute,m_systm.wSecond,m_systm.wMilliseconds);

            status = dvpSavePicture(&frame, pBuffer, w2a(strFileName).c_str(), 100);
			ASSERT(status == DVP_STATUS_OK);

            m_uImageCount++;
		}

		// 如果需要，则显示图像到预览窗口
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

// 显示相机属性对话框
void CImageAcquisitionDlg::OnBnClickedButtonProperty()
{
	if (IsValidHandle(m_handle))
	{
		dvpShowPropertyModalDialog(m_handle, GetSafeHwnd());

		// 此时一些配置可能发生改变，将同步到界面
		UpdateControls();
	}
}

void CImageAcquisitionDlg::OnBnClickedButtonScan()
{
	dvpStatus status;
	dvpUint32 i,n=0;
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
}


void CImageAcquisitionDlg::OnBnClickedButtonStart()
{
	if (IsValidHandle(m_handle))
	{
		dvpStreamState state;
		dvpStatus status;

		// 根据当前视频状态，执行相反的操作，实现一个按钮既能启动又能停止
		status = dvpGetStreamState(m_handle, &state);
		ASSERT(status == DVP_STATUS_OK);

		if (state != STATE_STOPED)
		{
            status = dvpStop(m_handle);
            ASSERT(status == DVP_STATUS_OK);

            if (m_pThread != NULL)
            {
                m_evtExit.SetEvent();

                // 等待采集线程结束；最多等10秒钟，这样不至于会卡死
                if (m_pThread->m_hThread != INVALID_HANDLE_VALUE)
                {
                    DWORD dw = WaitForSingleObject(m_pThread->m_hThread, 100000);

                    // 正常情况下不应该超时
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
                // 在dvpStart之前先设置为触发模式
                status = dvpSetTriggerState(m_handle, m_bSoftTrigger?TRUE:FALSE);
                if (status != DVP_STATUS_OK)
                {
                    // 此时要确认相机是否支持触发功能
                    MessageBox(_T("设置触发模式失败"));
                }

                status = dvpStart(m_handle);
                if (status != DVP_STATUS_OK)
                {
                    MessageBox(_T("启动失败"));
                }

                // 重置线程退出事件
                m_evtExit.ResetEvent();

                // 创建图像采集线程
                m_pThread = AfxBeginThread(ImageThread, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
                if (m_pThread != NULL)
                {
                    m_pThread->m_bAutoDelete = FALSE;

                    // 启动线程
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

	 // 初始化入口参数bi开始
	 bi.hwndOwner = NULL;

	 // 初始化制定的root目录
	 bi.pidlRoot =NULL;
     
	 // 此参数如为NULL则不能显示对话框
	 bi.pszDisplayName =(LPWSTR)Buffer;
	 bi.lpszTitle = _T("选择文件路径");
	 
	 // 带编辑框的风格
	 bi.ulFlags = 0x0040 | BIF_RETURNONLYFSDIRS | BIF_EDITBOX;
	 bi.lpfn = NULL;
	 bi.lParam = 0;
	 bi.iImage=IDR_MAINFRAME;

	 // 初始化入口参数bi结束
	
	 // 调用显示选择对话框
	 LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);

	 if(pIDList)
	 {
		// 取得文件夹路径到Buffer里
		 SHGetPathFromIDList(pIDList, (LPWSTR)Buffer);

		 // 将路径保存在一个CString对象里
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


// ImageAcquisitionDlg.h : ͷ�ļ�
//

#pragma once

#include "../../../library/Visual C++/include/DVPCamera.h"
#include "afxwin.h"


// CImageAcquisitionDlg �Ի���
class CImageAcquisitionDlg : public CDialogEx
{
//����
public:
	CImageAcquisitionDlg(CWnd* pParent = NULL);	// ��׼���캯��
    ~CImageAcquisitionDlg();

// �Ի�������
	enum { IDD = IDD_IMAGEACQUISITION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	void UpdateControls();
	BOOL OpenCamera(dvpHandle *pHandle);
	void StopCloseCamera(dvpHandle handle);
	UINT ImageThread();
	static UINT ImageThread(void *pParam);

	bool IsValidHandle(dvpHandle handle)
	{
		bool bValidHandle;
		dvpStatus status = dvpIsValid(handle, &bValidHandle);
		ASSERT(status == DVP_STATUS_OK);
		return bValidHandle;
	}

// ʵ��
protected:
	HICON m_hIcon;
	CWinThread *m_pThread;
	CEvent m_evtExit;
	dvpHandle m_handle;
	CComboBox m_listDevices;
    CListBox  m_listbox;
	CString m_strFriendlyName;
    BOOL m_bSoftTrigger;
    UINT m_uImageCount;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString strPicturePath;
	CString strFileName;
	UINT m_RecentCount;
	BOOL m_bDisplay;
	BOOL m_bSave;
	CWnd m_Picture;
    UINT m_uWaitTimer;
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonPath();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnDeltaposSpinRecentCount(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonProperty();
	afx_msg void OnBnClickedButtonScan();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonOpenFile();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonSelectpath();


    UINT m_uGrabTimeout;
    afx_msg void OnClose();
};


// BasicFunctionDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "../../../library/Visual C++/include/DVPCamera.h"
#include <string>
#include "afxcmn.h"

// CBasicFunctionDlg �Ի���
class CBasicFunctionDlg : public CDialogEx
{
// ����
public:
	CBasicFunctionDlg(CWnd* pParent = NULL);	// ��׼���캯��
	int iHoTemp,iVTemp,iWTemp,iHTemp;
// �Ի�������
	enum { IDD = IDD_BASICFUNCTION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	void UpdateControls();

	static int OnDrawPicture(dvpHandle handle,
		dvpStreamEvent event, 
		void *pContext, 
		dvpFrame *pFrame, 
		void *pBuffer);

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
	CComboBox m_listDevices;
	dvpHandle m_handle;
	CString m_strFriendlyName;
	

	// ���ɵ���Ϣӳ�亯��
	void OnInitControlResolution();
	void UpdateControlExposure();
	void UpdateControlGain();
	void OnInitControlAeMode();
	void OnInitControlFlick();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bAeOp;
	afx_msg void OnBnClickedButtonScan();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnNMCustomdrawSliderExposureTime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderExposureGain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboResolution();
	afx_msg void OnBnClickedButtonProperty();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnCbnSelchangeComboAeMode();
	virtual void OnOK();
	afx_msg void OnBnClickedCheckAntiFlick();
	afx_msg void OnCbnSelchangeComboFlick();
	afx_msg void OnBnClickedCheckAeoperation();
};

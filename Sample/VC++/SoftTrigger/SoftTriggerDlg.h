
// TriggerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "../../../library/Visual C++/include/DVPCamera.h"
#include <string>
#include "afxcmn.h"

// CSoftTriggerDlg �Ի���
class CSoftTriggerDlg : public CDialogEx
{
// ����
public:
	CSoftTriggerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TRIGGER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	void UpdateControls();
	BOOL ReOpenCamera();

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
	dvpHandle m_handle;
	CString m_strFriendlyName;
	CComboBox m_TriggerInputType;
	CComboBox m_StrobeOutputType;
	CComboBox m_OutputIo;
	CComboBox m_InputIo;
	CComboBox m_listDevices;
	double m_TriggerDelay;
	double m_TriggerFilter;
	double m_TriggerLoop;
	dvpDoubleDescr m_DelayDescr, m_FilterDescr, m_LoopDescr;


	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnCbnSelchangeComboInputIo();
	afx_msg void OnCbnSelchangeComboInputFunction();
	afx_msg void OnCbnSelchangeComboTriggerInputType();
	afx_msg void OnBnClickedButtonProperty();
	afx_msg void OnCbnSelchangeComboOutputIo();
	afx_msg void OnBnClickedRadioOutputLow();
	afx_msg void OnBnClickedRadioOutputHigh();
	virtual void OnOK();
	afx_msg void OnBnClickedButtonApplyEdit();
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCheckLoop();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonTriggerFire();
	afx_msg void OnBnClickedCheckTrigger();
	afx_msg void OnCbnSelchangeComboStrobeOutputType();
	afx_msg void OnBnClickedButtonDebug();
	afx_msg void OnBnClickedButtonScan();
	afx_msg void OnBnClickedButtonApplyLoop();
	afx_msg void OnBnClickedButtonApplyDelay();
	afx_msg void OnBnClickedCheckTrigIn();
	afx_msg void OnBnClickedCheckStrobeOut();
//	afx_msg void OnCbnSelchangeComboDevices();
	afx_msg void OnBnClickedSofttriggerPreview();
public:
	int m_trigger_state;//��������״̬
	bool m_b_read_image_flg;//ͼ������  false= ��ǰ֡������ɣ�  true= ��ǰ֡���ڴ���

};

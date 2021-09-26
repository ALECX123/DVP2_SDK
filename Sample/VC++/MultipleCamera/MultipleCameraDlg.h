
// MultipleCameraDlg.h : 头文件
//

#pragma once

#include <string>
#include "../../../library/Visual C++/include/DVPCamera.h"


// CMultipleCameraDlg 对话框
class CMultipleCameraDlg : public CDialogEx
{
// 构造
public:
	CMultipleCameraDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MULTIPLECAMERA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	
	dvpHandle m_handle[4];

	static INT OnDrawPicture(dvpHandle handle, 
		dvpStreamEvent event,
		void *pContext, 
		dvpFrame *pFrame, 
		void *pBuffer);

// 实现
protected:
	HICON m_hIcon;
	CComboBox m_listDevices1;
	CComboBox m_listDevices2;
	CComboBox m_listDevices3;
	CComboBox m_listDevices4;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	BOOL OpenByUserId(const std::string &UserId, dvpHandle *pHandle);

	void InitCtrls1();
	void InitCtrls2();
	void InitCtrls3();
	void InitCtrls4();	
public:
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonScan1();
	afx_msg void OnBnClickedButtonScan2();
	afx_msg void OnBnClickedButtonScan3();
	afx_msg void OnBnClickedButtonScan4();
	afx_msg void OnBnClickedButtonOpen1();
	afx_msg void OnBnClickedButtonOpen2();
	afx_msg void OnBnClickedButtonOpen3();
	afx_msg void OnBnClickedButtonOpen4();
	afx_msg void OnBnClickedButtonProperty1();
	afx_msg void OnBnClickedButtonProperty2();
	afx_msg void OnBnClickedButtonProperty3();
	afx_msg void OnBnClickedButtonProperty4();
	afx_msg void OnBnClickedButtonSet1();
	afx_msg void OnBnClickedButtonSet2();
	afx_msg void OnBnClickedButtonSet3();
	afx_msg void OnBnClickedButtonSet4();
	afx_msg void OnBnClickedButtonSaveBind();
	afx_msg void OnBnClickedButtonLoadBind();
	afx_msg void OnBnClickedButtonPlay1();
	afx_msg void OnBnClickedButtonPlay2();
	afx_msg void OnBnClickedButtonPlay3();
	afx_msg void OnBnClickedButtonPlay4();
};

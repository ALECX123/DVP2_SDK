
// ImageAcquisition.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// ������


// CImageAcquisitionApp:
// �йش����ʵ�֣������ImageAcquisition.cpp 
//

class CImageAcquisitionApp : public CWinApp
{
public:
	CImageAcquisitionApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CImageAcquisitionApp theApp;
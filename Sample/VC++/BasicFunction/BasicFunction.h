
// BasicFunction.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBasicFunctionApp:
// �йش����ʵ�֣������ BasicFunction.cpp
//

class CBasicFunctionApp : public CWinApp
{
public:
	CBasicFunctionApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBasicFunctionApp theApp;
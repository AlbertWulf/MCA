
// MFCApplication1.h : MFCApplication1 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMCAApp:
// �йش����ʵ�֣������ MFCApplication1.cpp
//

class CMCAApp : public CWinApp
{
public:
	CMCAApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMCAApp theApp;

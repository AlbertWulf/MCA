
// MYAPPLICATION1.h : MYAPPLICATION1 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMYAPPLICATION1App:
// �йش����ʵ�֣������ MYAPPLICATION1.cpp
//

class CMYAPPLICATION1App : public CWinAppEx
{
public:
	CMYAPPLICATION1App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMYAPPLICATION1App theApp;

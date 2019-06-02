#pragma once
#include "afxwin.h"



// CControlView 窗体视图

class CControlView : public CFormView
{
	DECLARE_DYNCREATE(CControlView)

protected:
	CControlView();           // 动态创建所使用的受保护的构造函数
	virtual ~CControlView();

public:
	enum { IDD = IDD_DIALOG_CONTROL };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedDialogControl();
	afx_msg void OnEnChangeEdit2();
	CEdit m_EditPeriod;
	CEdit m_EditHight;
	CEdit m_nEditprecount;
	CEdit m_nEditpretime;
	double m_nHight;
	double m_nPeriod;
	CButton m_ButtonPaint;
	CButton m_ButtonClear;
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButtonPaint();
	afx_msg void OnMenuPaint();
	afx_msg void OnMenuClear();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	BOOL m_bCheckAuto;
	BOOL m_bwillpaint;
	afx_msg void OnBnClickedCheckTimer();
	int mul ;
	int m_nprecount;
	int m_npretime;
	int runtime;
	int pre_count;
	int pre_time;
	CBrush m_brush;
	CBrush m_redbrush,m_bluebrush,m_greenbrush;
    COLORREF m_redcolor,m_bluecolor,m_textcolor,m_greencolor;

	//int m_nCount;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void PAINTNEW();
	
	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//afx_msg void OnEnChangeEditDetailsum();
	//afx_msg void OnEnChangeEditDetailsum();
	
	afx_msg void OnBnClickedButtonExport2txt();
	afx_msg void OnBnClickedButtonImporttxt();
};



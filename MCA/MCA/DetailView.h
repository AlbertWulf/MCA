#pragma once


// CDetailView 视图

class CDetailView : public CView
{
	DECLARE_DYNCREATE(CDetailView)
	bool m_bMouseDown;
	int m_nSel;

protected:
	CDetailView();           // 动态创建所使用的受保护的构造函数
	virtual ~CDetailView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};



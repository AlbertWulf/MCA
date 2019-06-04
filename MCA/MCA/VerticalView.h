#pragma once


// CVerticalView 视图

class CVerticalView : public CView
{
	DECLARE_DYNCREATE(CVerticalView)

protected:
	CVerticalView();           // 动态创建所使用的受保护的构造函数
	virtual ~CVerticalView();

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
};



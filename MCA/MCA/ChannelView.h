#pragma once


// CChannelView ��ͼ

class CChannelView : public CView
{
	DECLARE_DYNCREATE(CChannelView)

protected:
	CChannelView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CChannelView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
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



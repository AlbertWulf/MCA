#pragma once


// CDetailView ��ͼ

class CDetailView : public CView
{
	DECLARE_DYNCREATE(CDetailView)
	bool m_bMouseDown ;
	bool m_RBMouseClick;
	int m_nSel;
	int Cursor_Pos;
	int judge_first;
	int sumroi;//��¼�ڸ���Ȥ������ƶ��˶��ٸ����ص�
protected:
	CDetailView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CDetailView();

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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nflags,CPoint point);
};



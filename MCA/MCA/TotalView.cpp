// TotalView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MCA.h"
#include "TotalView.h"


// CTotalView

IMPLEMENT_DYNCREATE(CTotalView, CView)

CTotalView::CTotalView()
{

}

CTotalView::~CTotalView()
{
}

BEGIN_MESSAGE_MAP(CTotalView, CView)
END_MESSAGE_MAP()


// CTotalView ��ͼ

void CTotalView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CTotalView ���

#ifdef _DEBUG
void CTotalView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CTotalView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTotalView ��Ϣ�������

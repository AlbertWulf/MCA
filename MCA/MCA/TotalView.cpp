// TotalView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MCA.h"
#include "TotalView.h"
#include "MCADOc.h"


// CTotalView

IMPLEMENT_DYNCREATE(CTotalView, CView)

CTotalView::CTotalView()
{

}

CTotalView::~CTotalView()
{
}

BEGIN_MESSAGE_MAP(CTotalView, CView)
	ON_WM_PAINT()
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


void CTotalView::OnPaint()
{
	CPaintDC dc(this);
	//��������ɫ 
	CRect rect; 
	GetClientRect(&rect); 
	
	dc.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(139,35,134)); //��ɫ����
	
	
	
	//����������ɫ 
	if(((CMCADoc*)m_pDocument)->lbtn_beg>0&&((CMCADoc*)m_pDocument)->lbtn_beg<512){
	CPen pen;
	pen.CreatePen(PS_SOLID,2,RGB(255,0,0));
	CPen* oldpen = dc.SelectObject(&pen);
	//������ 

	int gap = (int) 512/(((CMCADoc*)m_pDocument)->lbtn_end-((CMCADoc*)m_pDocument)->lbtn_beg+1);
	dc.MoveTo(0,rect.Height()-((CMCADoc*)m_pDocument)->m_Dot[((CMCADoc*)m_pDocument)->lbtn_beg]);
	int bg = 0;
	for (int i=((CMCADoc*)m_pDocument)->lbtn_beg;i<((CMCADoc*)m_pDocument)->lbtn_end+2 ;i++)
	{ 
		dc.LineTo(bg*gap,rect.Height()-4*((CMCADoc*)m_pDocument)->m_Dot[i]); 
		bg++;
	} 
	//�ͷ���Դ 
	dc.SelectObject(oldpen); 
	pen.DeleteObject();
	}
}

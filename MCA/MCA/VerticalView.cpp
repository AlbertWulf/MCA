// VerticalView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MCA.h"
#include "VerticalView.h"
#include "MCADoc.h"

// CVerticalView

IMPLEMENT_DYNCREATE(CVerticalView, CView)

CVerticalView::CVerticalView()
{

}

CVerticalView::~CVerticalView()
{
}

BEGIN_MESSAGE_MAP(CVerticalView, CView)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CVerticalView ��ͼ

void CVerticalView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
	CPaintDC dc(this);
	//��������ɫ 
	CRect rect; 
	GetClientRect(&rect); 
	
	
	dc.FillSolidRect(0,0,20,20,RGB(0,255,0)); //��ɫ����
	//CDC *pDC = GetDC();
	CString strText; 
	for(int i =0;i<17;i++){
	strText.Format(_T("%3d "), 64*i); 
		//CDC  * pDC = GetDC();
	pDC->TextOutW(0,i*20,strText);
	}
	//dc.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(255,121,100)); //��ɫ����
	// TODO: �ڴ���ӻ��ƴ���
}


// CVerticalView ���

#ifdef _DEBUG
void CVerticalView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CVerticalView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CVerticalView ��Ϣ�������


void CVerticalView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CDC *pDC = GetDC();
	//��������ɫ 
	CRect rect; 
	GetClientRect(&rect); 
	
	
	dc.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(178,105,135)); //��ɫ����
	//CDC *pDC = GetDC();
	CString strText; 
	for(int i =0;i<6;i++){
	strText.Format(_T("%3d "), 50*i*((CMCADoc*)m_pDocument)->mult); 
		//CDC  * pDC = GetDC();
	pDC->TextOutW(0,rect.Height()-i*50-58,strText);
	}
}

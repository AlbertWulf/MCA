// TotalView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MCA.h"
#include "TotalView.h"
#include "MCADOc.h"
#include "ControlView.h"
#include "MainFrm.h"
#include "DetailView.h"
#include <exception>
#include <stdio.h>
#include <algorithm>
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
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
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
	using namespace std;
	
	
	CPaintDC dc(this);
	//��������ɫ 
	CRect rect; 
	GetClientRect(&rect); 
	
	dc.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(255,121,100)); //��ɫ����
	dc.FillSolidRect(pointx,0,2,rect.Height(),RGB(255,209,71)); //��ɫ����
	
	
	
	//����������ɫ 
	if(((CMCADoc*)m_pDocument)->lbtn_beg>0&&((CMCADoc*)m_pDocument)->lbtn_beg<1024){
	CPen pen;
	pen.CreatePen(PS_SOLID,2,RGB(0,134,155));
	CPen* oldpen = dc.SelectObject(&pen);
	//������ 
	//int a[] = {1,2,3,4,5};
	//int b = *max_element(a,a+5);

	//
	int gap = (int) 1024/(((CMCADoc*)m_pDocument)->lbtn_end-((CMCADoc*)m_pDocument)->lbtn_beg+1);
	dc.MoveTo(0,rect.Height()-((CMCADoc*)m_pDocument)->m_Dot[((CMCADoc*)m_pDocument)->lbtn_beg]);
	int bg = 0;
	for (int i=((CMCADoc*)m_pDocument)->lbtn_beg;i<((CMCADoc*)m_pDocument)->lbtn_end+2 ;i++)
	{ 
		dc.LineTo(bg*gap,rect.Height()-((CMCADoc*)m_pDocument)->m_Dot[i]); 
		bg++;
	} 
	//�ͷ���Դ 
	dc.SelectObject(oldpen); 
	pen.DeleteObject();
	}

}

 
void CTotalView::DrawLine(int x){
	CPaintDC dc(this);
	//��������ɫ 
	CRect rect; 
	GetClientRect(&rect); 
	
	dc.FillSolidRect(x,0,2,rect.Height(),RGB(255,121,100)); //��ɫ����
	
	
}


void CTotalView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//((CMCADoc*)m_pDocument)->m_nChannel = point.x;
	pointx = point.x;
	OnPaint();
	UpdateData(FALSE);
	
	
	int gap = ((CMCADoc*)m_pDocument)->lbtn_end-((CMCADoc*)m_pDocument)->lbtn_beg;
	CString str_Channel,str_Counts,str_detail_sum;
	int chan = ((CMCADoc*)m_pDocument)->lbtn_beg+point.x*gap/1024;
	((CMCADoc*)m_pDocument)->total_mouse_pos = point.x;
	int detail_sum=0;//�Ŵ����ܼ���
	for(int i = ((CMCADoc*)m_pDocument)->lbtn_beg;i<=((CMCADoc*)m_pDocument)->lbtn_end;i++)
	{
		try{detail_sum = detail_sum + ((CMCADoc*)m_pDocument)->m_Dot[i];}
		catch(...)
		{}
	}
	detail_sum = detail_sum*((CMCADoc*)m_pDocument)->mult;
	((CMCADoc*)m_pDocument)->m_nChannel = chan;
	((CMCADoc*)m_pDocument)->m_nCount = ((CMCADoc*)m_pDocument)->m_Dot[chan];
	((CMCADoc*)m_pDocument)->m_nDetailSum = detail_sum;
	str_Channel.Format(_T("%d"),chan);
	str_Counts.Format(_T("%d"),((CMCADoc*)m_pDocument)->mult*((CMCADoc*)m_pDocument)->m_Dot[chan]);
	str_detail_sum.Format(_T("%d"),detail_sum);
	((CMCADoc*)m_pDocument)->m_EditChannel.SetWindowText(str_Channel);
	((CMCADoc*)m_pDocument)->m_EditCount.SetWindowText(str_Counts);
	((CMCADoc*)m_pDocument)->m_EditDetailSum.SetWindowText(str_detail_sum);
    ((CMCADoc*)m_pDocument)->m_nCount = ((CMCADoc*)m_pDocument)->m_Dot[chan];
	
	//((CMCADoc*)GetDocument())->UpdateAllViews(this); //�ػ�����
	((CMainFrame *)AfxGetApp()->m_pMainWnd)->GetActiveDocument()->UpdateAllViews( NULL ) ;
	//((CMCADoc*)m_pDocument)->m_EditChannel.UpdateData(TRUE);
	
	CView::OnLButtonDown(nFlags, point);
}


void CTotalView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	char cChar;//��ǰ�����µ��ַ�
    HCURSOR hCursor = 0;//��ʾ�����
    HCURSOR hPrevCursor = 0;//��ǰ�Ĺ����
    cChar = char(nChar);//�����µļ�ת��Ϊ�ַ�
    CRect rect; 
	GetClientRect(&rect); 
	CPaintDC dc(this);
	//UpdateData(TRUE);
	if (cChar == 'A'){
        //���ؼ�ͷ��CpPaintDC dc(this);
	//��������ɫ 
		pointx--;
		pointx = pointx%1024;
		if(pointx<=0){pointx = 0;}
		dc.MoveTo(pointx,0);
		dc.LineTo(pointx,rect.Height());
		//
		UpdateData(FALSE);
	
	
	int gap = ((CMCADoc*)m_pDocument)->lbtn_end-((CMCADoc*)m_pDocument)->lbtn_beg;
	CString str_Channel,str_Counts,str_detail_sum;
	int chan = ((CMCADoc*)m_pDocument)->lbtn_beg+pointx*gap/1024;
	((CMCADoc*)m_pDocument)->total_mouse_pos = pointx;
	int detail_sum=0;//�Ŵ����ܼ���
	for(int i = ((CMCADoc*)m_pDocument)->lbtn_beg;i<=((CMCADoc*)m_pDocument)->lbtn_end;i++)
	{
		detail_sum = detail_sum + ((CMCADoc*)m_pDocument)->m_Dot[i];
	}
	detail_sum = detail_sum*((CMCADoc*)m_pDocument)->mult;
	((CMCADoc*)m_pDocument)->m_nChannel = chan;
	((CMCADoc*)m_pDocument)->m_nCount = ((CMCADoc*)m_pDocument)->m_Dot[chan];
	((CMCADoc*)m_pDocument)->m_nDetailSum = detail_sum;
	str_Channel.Format(_T("%d"),chan);
	str_Counts.Format(_T("%d"),((CMCADoc*)m_pDocument)->mult*((CMCADoc*)m_pDocument)->m_Dot[chan]);
	str_detail_sum.Format(_T("%d"),detail_sum);
	((CMCADoc*)m_pDocument)->m_EditChannel.SetWindowText(str_Channel);
	((CMCADoc*)m_pDocument)->m_EditCount.SetWindowText(str_Counts);
	((CMCADoc*)m_pDocument)->m_EditDetailSum.SetWindowText(str_detail_sum);
    ((CMCADoc*)m_pDocument)->m_nCount = ((CMCADoc*)m_pDocument)->m_Dot[chan];
		//
		Invalidate(TRUE);

		//((CMainFrame *)AfxGetApp()->m_pMainWnd)->GetActiveDocument()->UpdateAllViews(NULL) ;
        hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
    }
	else if(nChar == 'D')
	{
		pointx++;
		pointx = pointx%1024;
		dc.MoveTo(pointx,0);
		dc.LineTo(pointx,rect.Height());
		//
		UpdateData(FALSE);
	
	
	int gap = ((CMCADoc*)m_pDocument)->lbtn_end-((CMCADoc*)m_pDocument)->lbtn_beg;
	CString str_Channel,str_Counts,str_detail_sum;
	int chan = ((CMCADoc*)m_pDocument)->lbtn_beg+pointx*gap/1024;
	((CMCADoc*)m_pDocument)->total_mouse_pos = pointx;
	int detail_sum=0;//�Ŵ����ܼ���
	for(int i = ((CMCADoc*)m_pDocument)->lbtn_beg;i<=((CMCADoc*)m_pDocument)->lbtn_end;i++)
	{
		detail_sum = detail_sum + ((CMCADoc*)m_pDocument)->m_Dot[i];
	}
	detail_sum = detail_sum*((CMCADoc*)m_pDocument)->mult;
	((CMCADoc*)m_pDocument)->m_nChannel = chan;
	((CMCADoc*)m_pDocument)->m_nCount = ((CMCADoc*)m_pDocument)->m_Dot[chan];
	((CMCADoc*)m_pDocument)->m_nDetailSum = detail_sum;
	str_Channel.Format(_T("%d"),chan);
	str_Counts.Format(_T("%d"),((CMCADoc*)m_pDocument)->mult*((CMCADoc*)m_pDocument)->m_Dot[chan]);
	str_detail_sum.Format(_T("%d"),detail_sum);
	((CMCADoc*)m_pDocument)->m_EditChannel.SetWindowText(str_Channel);
	((CMCADoc*)m_pDocument)->m_EditCount.SetWindowText(str_Counts);
	((CMCADoc*)m_pDocument)->m_EditDetailSum.SetWindowText(str_detail_sum);
    ((CMCADoc*)m_pDocument)->m_nCount = ((CMCADoc*)m_pDocument)->m_Dot[chan];
		//
		Invalidate(TRUE);

		//((CMainFrame *)AfxGetApp()->m_pMainWnd)->GetActiveDocument()->UpdateAllViews(NULL) ;
        hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);

	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

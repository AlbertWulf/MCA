// DetailView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MCA.h"
#include "DetailView.h"
#include "MCADOc.h"


// CDetailView

IMPLEMENT_DYNCREATE(CDetailView, CView)

CDetailView::CDetailView()
{

}

CDetailView::~CDetailView()
{
}

BEGIN_MESSAGE_MAP(CDetailView, CView)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
END_MESSAGE_MAP()


// CDetailView ��ͼ

void CDetailView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}
void CDetailView::DrawAxis(CDC &MemDC, LPTSTR TitleForX, LPTSTR TitleForY)
{
    //ѡ��������Ļ���
    CPen PenForDrawAxis(PS_SOLID, 1, RGB(255,251,13));
    MemDC.SelectObject(PenForDrawAxis);
 
    //����X��
    MemDC.MoveTo(60, 220);
    MemDC.LineTo(520, 220);
    //���Ƽ�ͷ
    MemDC.LineTo(510, 223);
    MemDC.LineTo(510, 217);
    MemDC.LineTo(520, 220);
 
    //����Y��
    MemDC.MoveTo(60, 220);
    MemDC.LineTo(60, 30);
    //���Ƽ�ͷ
    MemDC.LineTo(57, 40);
    MemDC.LineTo(63, 40);
    MemDC.LineTo(60, 30);
 
    //�����ı�����ɫ
    COLORREF OldColor = MemDC.SetTextColor(RGB(255, 255, 0));
 
    //���Ʊ�ע
    MemDC.TextOut(480, 230, TitleForX);
    MemDC.TextOut(40, 10, TitleForY);
 
    //��ԭ�ı���ɫ
    MemDC.SetTextColor(OldColor);
}


// CDetailView ���

#ifdef _DEBUG
void CDetailView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CDetailView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDetailView ��Ϣ�������


void CDetailView::OnPaint()
{
	CPaintDC dc(this);
	CRect rect; 
	GetClientRect(&rect); 
    CDC *pDC = GetDC();
	CDC MemDC;
    MemDC.CreateCompatibleDC(NULL); 
    CBitmap MemBitmap;
    MemBitmap.CreateCompatibleBitmap(pDC, rect.Width(),rect.Height());
	MemDC.SelectObject(&MemBitmap); 

	//��������ɫ 
	
	MemDC.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(85,85,85));
	//DrawAxis(MemDC, _T("time(s)"), _T("length(kbit)"));

	
	//dc.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(85,85,85)); //��ɫ����
	
	
	
	//����������ɫ 
	CPen pen;
	
	CPen* oldpen = MemDC.SelectObject(&pen);
	//������ 
	DrawAxis(MemDC, _T("time(s)"), _T("length(kbit)"));
	pen.CreatePen(PS_SOLID,2,RGB(255,251,13));
	MemDC.MoveTo(1,rect.Height()-((CMCADoc*)m_pDocument)->m_Dot[0]);
	for (int i=0;i<512;i++)
	{ 
		MemDC.LineTo(i+1,rect.Height()-((CMCADoc*)m_pDocument)->m_Dot[i]); } 
	//�ͷ���Դ 
	if(((CMCADoc*)m_pDocument)->lbtn_beg<Cursor_Pos){
		MemDC.FillSolidRect(((CMCADoc*)m_pDocument)->lbtn_beg,0,Cursor_Pos-((CMCADoc*)m_pDocument)->lbtn_beg,rect.Height(),RGB(0,255,255));}
	pDC->BitBlt(0, 0,rect.Width(),rect.Height(), &MemDC, 0, 0, SRCCOPY); 

	MemDC.SelectObject(oldpen); 
	pen.DeleteObject();
	ReleaseDC(pDC);

	
	

}

void CDetailView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�������;�����/�����Ĭ��ֵ
	Cursor_Pos = ((CMCADoc*)m_pDocument)->lbtn_beg;
	m_RBMouseClick = TRUE;
	CView::OnRButtonDblClk(nFlags, point);
}

void CDetailView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	((CMCADoc*)m_pDocument) ->lbtn_beg = point.x;
	m_bMouseDown = TRUE;
	CView::OnLButtonDown(nFlags, point);
}


void CDetailView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	((CMCADoc*)m_pDocument) ->lbtn_end = point.x;
	
	m_bMouseDown = FALSE;
	CView::OnLButtonUp(nFlags, point);
}


void CDetailView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDC  * pDC = GetDC();
	
		
	((CMCADoc*)m_pDocument) ->cha = point.x;
	
	if (m_bMouseDown) 
	{   
		sumroi++;
		Cursor_Pos = point.x;
		int nX = point.x; 
		int nY = ((CMCADoc*)m_pDocument) -> m_Dot[nX];
		CString strText; 
		strText.Format(_T("��ַ%3d��ֵ%2d "), nX, nY); 
		//CDC  * pDC = GetDC();
		pDC->TextOutW(10,80,strText);
		CPen pen;
	pen.CreatePen(PS_SOLID,2,RGB(0,255,0));
	CPen* oldpen = pDC->SelectObject(&pen);	   

	CRect rect;
	GetClientRect(&rect);
	
    //pDC->SetROP2(R2_XORPEN);   //����
   // pDC->MoveTo(m_nSel,0);
    //pDC->LineTo(m_nSel,rect.Height());

    pDC->MoveTo(nX,0);         //���ƹ��
    pDC->LineTo(nX,rect.Height());

    m_nSel = nX;
	pDC->SelectObject(oldpen);
	pen.DeleteObject();
	}
	
		 
	
	CView::OnMouseMove(nFlags, point);

}

// TotalView.cpp : 实现文件
//

#include "stdafx.h"
#include "MCA.h"
#include "TotalView.h"
#include "MCADOc.h"
#include "ControlView.h"
#include "MainFrm.h"


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
END_MESSAGE_MAP()


// CTotalView 绘图

void CTotalView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}
 

// CTotalView 诊断

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


// CTotalView 消息处理程序


void CTotalView::OnPaint()
{
	CPaintDC dc(this);
	//画背景颜色 
	CRect rect; 
	GetClientRect(&rect); 
	
	dc.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(255,121,100)); //紫色背景
	
	
	
	//设置曲线颜色 
	if(((CMCADoc*)m_pDocument)->lbtn_beg>0&&((CMCADoc*)m_pDocument)->lbtn_beg<512){
	CPen pen;
	pen.CreatePen(PS_SOLID,2,RGB(0,134,155));
	CPen* oldpen = dc.SelectObject(&pen);
	//画曲线 

	int gap = (int) 512/(((CMCADoc*)m_pDocument)->lbtn_end-((CMCADoc*)m_pDocument)->lbtn_beg+1);
	dc.MoveTo(0,rect.Height()-((CMCADoc*)m_pDocument)->m_Dot[((CMCADoc*)m_pDocument)->lbtn_beg]);
	int bg = 0;
	for (int i=((CMCADoc*)m_pDocument)->lbtn_beg;i<((CMCADoc*)m_pDocument)->lbtn_end+2 ;i++)
	{ 
		dc.LineTo(bg*gap,rect.Height()-4*((CMCADoc*)m_pDocument)->m_Dot[i]); 
		bg++;
	} 
	//释放资源 
	dc.SelectObject(oldpen); 
	pen.DeleteObject();
	}

}



void CTotalView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//((CMCADoc*)m_pDocument)->m_nChannel = point.x;
	UpdateData(FALSE);
	int gap = ((CMCADoc*)m_pDocument)->lbtn_end-((CMCADoc*)m_pDocument)->lbtn_beg;
	CString str_Channel,str_Counts,str_detail_sum;
	int chan = ((CMCADoc*)m_pDocument)->lbtn_beg+point.x*gap/512;
	int detail_sum=0;//放大区总计数
	for(int i = ((CMCADoc*)m_pDocument)->lbtn_beg;i<=((CMCADoc*)m_pDocument)->lbtn_end;i++)
	{
		detail_sum = detail_sum + ((CMCADoc*)m_pDocument)->m_Dot[i];
	}
	((CMCADoc*)m_pDocument)->m_nChannel = chan;
	((CMCADoc*)m_pDocument)->m_nCount = ((CMCADoc*)m_pDocument)->m_Dot[chan];
	str_Channel.Format(_T("%d"),chan);
	str_Counts.Format(_T("%d"),((CMCADoc*)m_pDocument)->m_Dot[chan]);
	((CMCADoc*)m_pDocument)->m_EditChannel.SetWindowText(str_Channel);
	((CMCADoc*)m_pDocument)->m_EditCount.SetWindowText(str_Counts);
    //((CMCADoc*)m_pDocument)->m_nCount = ((CMCADoc*)m_pDocument)->m_Dot[chan];
	//((CMCADoc*)GetDocument())->UpdateAllViews(NULL); //重画曲线
	//((CMainFrame *)AfxGetApp()->m_pMainWnd)->GetActiveDocument()->UpdateAllViews( NULL ) ;
	((CMCADoc*)m_pDocument)->m_EditChannel.UpdateData(TRUE);
	CView::OnLButtonDown(nFlags, point);
}

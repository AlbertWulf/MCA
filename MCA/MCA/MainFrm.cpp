
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "MCA.h"
#include "MainFrm.h"
#include "Controlview.h"
#include "TotalView.h"
#include "DetailView.h"
#include "ChannelView.h"
#include "VerticalView.h"
//#pragma comment(lib,"SkinMagic.lib")//调用皮肤lib  
//#include "SkinMagicLib.h" 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	VERIFY(m_wndSplitter.CreateStatic(this, 1,
		3,WS_CHILD|WS_VISIBLE, AFX_IDW_PANE_FIRST));
	//创建左窗口视图 
	VERIFY(m_wndSplitter.CreateView(0,0,
		RUNTIME_CLASS(CControlView), CSize(165, 500), pContext));  
	VERIFY(m_wndSplitter.CreateView(0,1,
		RUNTIME_CLASS(CVerticalView), CSize(165, 50), pContext));  
	//创建右边上下拆分窗口
	VERIFY(m_wndSplitter2.CreateStatic(&m_wndSplitter, 3,
		1,WS_CHILD | WS_VISIBLE,
		m_wndSplitter.IdFromRowCol(0,2))); 
	//创建右下窗口视图 
	VERIFY(m_wndSplitter2.CreateView(0, 0,
	RUNTIME_CLASS(CTotalView), CSize( 1024, 250), pContext)); 
	//
	VERIFY(m_wndSplitter2.CreateView(2, 0, 
	RUNTIME_CLASS(CChannelView), CSize( 1024, 20), pContext));
	//创建右上窗口视图 
	VERIFY(m_wndSplitter2.CreateView(1, 0, 
	RUNTIME_CLASS(CDetailView), CSize( 1024, 250), pContext));
	//
	CRect r;
    GetClientRect(&r);
    m_wndSplitter.SetColumnInfo( 0, r.Width()/6.7, 0 );
	 m_wndSplitter.SetColumnInfo( 1, r.Width()/36, 0 );
    //m_wndSplitter.SetColumnInfo( 0, r.Width()/6, 1 );
    m_wndSplitter.RecalcLayout();
	m_wndSplitter2.SetRowInfo( 0, r.Height()/2.4, 0);
	m_wndSplitter2.SetColumnInfo( 0, r.Width()/1.19, 0);

	//m_wndSplitter2.SetRowInfo( 0, r.Width()/2, 0 );
	m_wndSplitter2.SetRowInfo( 1, r.Height()/2.4, 0);
	m_wndSplitter2.SetRowInfo( 2, r.Height()/6, 0);

    m_wndSplitter2.RecalcLayout();
	//
	return TRUE;
	//return m_wndSplitter.Create(this,
	//	2, 2,               // TODO: 调整行数和列数
	//	CSize(10, 10),      // TODO: 调整最小窗格大小
	//	pContext);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	
	
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.cx = 1350;
	cs.cy = 700;
	cs.style = cs.style & (~WS_THICKFRAME);
	cs.style = cs.style & (~WS_SIZEBOX);
	cs.style &= ~WS_MAXIMIZEBOX; 
	
	return TRUE;
}


// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序


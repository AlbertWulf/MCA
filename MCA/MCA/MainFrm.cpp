
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "MCA.h"
#include "MainFrm.h"
#include "Controlview.h"
#include "TotalView.h"
#include "DetailView.h"

//#pragma comment(lib,"SkinMagic.lib")//����Ƥ��lib  
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
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
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
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: �������Ҫ��ͣ������������ɾ��������
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	VERIFY(m_wndSplitter.CreateStatic(this, 1,
		2,WS_CHILD|WS_VISIBLE, AFX_IDW_PANE_FIRST));
	//�����󴰿���ͼ 
	VERIFY(m_wndSplitter.CreateView(0,0,
		RUNTIME_CLASS(CControlView), CSize(165, 0), pContext));         
	//�����ұ����²�ִ���
	VERIFY(m_wndSplitter2.CreateStatic(&m_wndSplitter, 2,
		1,WS_CHILD | WS_VISIBLE,
		m_wndSplitter.IdFromRowCol(0,1))); 
	//�������´�����ͼ 
	VERIFY(m_wndSplitter2.CreateView(0, 0,
	RUNTIME_CLASS(CTotalView), CSize( 0, 120), pContext)); 
	//�������ϴ�����ͼ 
	VERIFY(m_wndSplitter2.CreateView(1, 0, 
	RUNTIME_CLASS(CDetailView), CSize( 0, 0), pContext));
	return TRUE;
	//return m_wndSplitter.Create(this,
	//	2, 2,               // TODO: ��������������
	//	CSize(10, 10),      // TODO: ������С�����С
	//	pContext);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

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


// CMainFrame ��Ϣ�������


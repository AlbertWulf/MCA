
// MYAPPLICATION1View.cpp : CMYAPPLICATION1View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MYAPPLICATION1.h"
#endif

#include "MYAPPLICATION1Doc.h"
#include "MYAPPLICATION1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMYAPPLICATION1View

IMPLEMENT_DYNCREATE(CMYAPPLICATION1View, CView)

BEGIN_MESSAGE_MAP(CMYAPPLICATION1View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMYAPPLICATION1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMYAPPLICATION1View 构造/析构

CMYAPPLICATION1View::CMYAPPLICATION1View()
{
	// TODO: 在此处添加构造代码

}

CMYAPPLICATION1View::~CMYAPPLICATION1View()
{
}

BOOL CMYAPPLICATION1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMYAPPLICATION1View 绘制

void CMYAPPLICATION1View::OnDraw(CDC* /*pDC*/)
{
	CMYAPPLICATION1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMYAPPLICATION1View 打印


void CMYAPPLICATION1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMYAPPLICATION1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMYAPPLICATION1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMYAPPLICATION1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMYAPPLICATION1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMYAPPLICATION1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMYAPPLICATION1View 诊断

#ifdef _DEBUG
void CMYAPPLICATION1View::AssertValid() const
{
	CView::AssertValid();
}

void CMYAPPLICATION1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMYAPPLICATION1Doc* CMYAPPLICATION1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMYAPPLICATION1Doc)));
	return (CMYAPPLICATION1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMYAPPLICATION1View 消息处理程序

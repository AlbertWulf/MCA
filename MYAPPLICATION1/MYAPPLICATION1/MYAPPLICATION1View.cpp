
// MYAPPLICATION1View.cpp : CMYAPPLICATION1View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMYAPPLICATION1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMYAPPLICATION1View ����/����

CMYAPPLICATION1View::CMYAPPLICATION1View()
{
	// TODO: �ڴ˴���ӹ������

}

CMYAPPLICATION1View::~CMYAPPLICATION1View()
{
}

BOOL CMYAPPLICATION1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMYAPPLICATION1View ����

void CMYAPPLICATION1View::OnDraw(CDC* /*pDC*/)
{
	CMYAPPLICATION1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMYAPPLICATION1View ��ӡ


void CMYAPPLICATION1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMYAPPLICATION1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMYAPPLICATION1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMYAPPLICATION1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CMYAPPLICATION1View ���

#ifdef _DEBUG
void CMYAPPLICATION1View::AssertValid() const
{
	CView::AssertValid();
}

void CMYAPPLICATION1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMYAPPLICATION1Doc* CMYAPPLICATION1View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMYAPPLICATION1Doc)));
	return (CMYAPPLICATION1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMYAPPLICATION1View ��Ϣ�������

// ControlView.cpp : 实现文件
//

#include "stdafx.h"
#include<math.h>
#include "MCA.h"
#include "ControlView.h"
#include "MCADoc.h"
#include "MainFrm.h"


// CControlView

IMPLEMENT_DYNCREATE(CControlView, CFormView)

CControlView::CControlView()
	: CFormView(CControlView::IDD)
	, m_nHight(0)
	, m_nPeriod(0)
	, m_bCheckAuto(FALSE)
{

}

CControlView::~CControlView()
{
}

void CControlView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PERIOD, m_EditPeriod);
	DDX_Control(pDX, IDC_EDIT_HIGHT, m_EditHight);
	DDX_Text(pDX, IDC_EDIT_HIGHT, m_nHight);
	DDX_Text(pDX, IDC_EDIT_PERIOD, m_nPeriod);
	DDX_Control(pDX, IDC_BUTTON_PAINT, m_ButtonPaint);
	DDX_Control(pDX, IDC_BUTTON_CLEAR, m_ButtonClear);
	DDX_Check(pDX, IDC_CHECK_TIMER, m_bCheckAuto);
}

BEGIN_MESSAGE_MAP(CControlView, CFormView)
	//ON_BN_CLICKED(IDC_BUTTON1, &CControlView::OnBnClickedButton1)
	ON_BN_CLICKED(IDD_DIALOG_CONTROL, &CControlView::OnBnClickedDialogControl)
	//ON_EN_CHANGE(IDC_EDIT2, &CControlView::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON_PAINT, &CControlView::OnBnClickedButtonPaint)
	ON_COMMAND(ID_MENU_PAINT, &CControlView::OnMenuPaint)
	ON_COMMAND(ID_MENU_CLEAR, &CControlView::OnMenuClear)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CControlView::OnBnClickedButtonClear)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_TIMER, &CControlView::OnBnClickedCheckTimer)
END_MESSAGE_MAP()


// CControlView 诊断

#ifdef _DEBUG
void CControlView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CControlView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CControlView 消息处理程序


void CControlView::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CControlView::OnBnClickedDialogControl()
{
	// TODO: 在此添加控件通知处理程序代码
}


//void CControlView::OnEnChangeEdit2()
//{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CFormView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

//#1015

	// TODO:  在此添加控件通知处理程序代码
//}


void CControlView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	m_nHight = 10.0;
	m_nPeriod = 0.1;
	UpdateData(FALSE);
	m_ButtonClear.EnableWindow(FALSE);


	// TODO: 在此添加专用代码和/或调用基类
}


void CControlView::OnBnClickedButtonPaint()
{
	
	UpdateData(TRUE);//获取屏幕值至变量
	//设置按钮状态
	m_ButtonPaint.EnableWindow(FALSE);
	m_ButtonClear.EnableWindow(TRUE);
	//设置曲线值

	for (int i=0;i<512;i++) 
	{ ((CMCADoc*)m_pDocument)->m_Dot[i]=m_nHight*(1+sin(m_nPeriod*i)); } 
	((CMCADoc*)GetDocument())->UpdateAllViews(NULL); //重画曲线



	// TODO: 在此添加控件通知处理程序代码
}


void CControlView::OnMenuPaint()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedButtonPaint();
}


void CControlView::OnMenuClear()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedButtonClear();
}


void CControlView::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
		 //设置按钮状态
    m_ButtonPaint.EnableWindow(TRUE);
    m_ButtonClear.EnableWindow(FALSE);
     //设置曲线值
      for (int i=0;i<512;i++)  
      {
         ((CMCADoc*)m_pDocument)->m_Dot[i]=0;
        }
       //重画曲线
   ((CMainFrame *)AfxGetApp()->m_pMainWnd)->GetActiveDocument()->UpdateAllViews( NULL ) ;
}


void CControlView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//自动循环增加曲线幅度
	m_nHight ++; 
	if (m_nHight>30)  m_nHight=10.0;
	//重新画图
	UpdateData(FALSE);
	OnBnClickedButtonPaint();

	CFormView::OnTimer(nIDEvent);
}


void CControlView::OnBnClickedCheckTimer()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); //获取当前选中状态
if (m_bCheckAuto) 
{
	SetTimer(1,500,NULL);
	Invalidate( FALSE ); 
	//选中，设置自动更新 
}
else 
{ 
	KillTimer(1);
	//不选中，取消自动更新 
}

}

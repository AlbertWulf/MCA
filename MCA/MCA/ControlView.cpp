// ControlView.cpp : 实现文件
//

#include "stdafx.h"
#include<math.h>

#include <stdio.h>
#include <string>
#include <iostream>
#include "MCA.h"
#include "ControlView.h"
#include "MCADoc.h"
#include "MainFrm.h"
#include <fstream>
#include <time.h>

#include "DetailView.h"
#include "TotalView.h"
#include<windows.h>
#include <algorithm>
// CControlView

IMPLEMENT_DYNCREATE(CControlView, CFormView)

CControlView::CControlView()
	: CFormView(CControlView::IDD)
	, m_nHight(0)
	, m_nPeriod(0)
	, mul(1)
	, m_bCheckAuto(FALSE)
	, m_bwillpaint(FALSE)
	,runtime(0)
	,m_nprecount(1000000)
	,m_npretime(100)
	,pre_count(10000)
	,pre_time(100)

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
	DDX_Control(pDX, IDC_EDIT_DTCHID, ((CMCADoc*)m_pDocument)->m_EditChannel);
	DDX_Text(pDX, IDC_EDIT_DTCHID, ((CMCADoc*)m_pDocument)->m_nChannel);
	DDX_Control(pDX, IDC_EDIT_DTCOUNT, ((CMCADoc*)m_pDocument)->m_EditCount);
	DDX_Text(pDX, IDC_EDIT_DTCOUNT, ((CMCADoc*)m_pDocument)->m_nCount);
	DDX_Control(pDX, IDC_EDIT_DETAILSUM, ((CMCADoc*)m_pDocument)->m_EditDetailSum);
	DDX_Text(pDX, IDC_EDIT_DETAILSUM, ((CMCADoc*)m_pDocument)->m_nDetailSum);
	DDX_Control(pDX, IDC_EDIT_PRECOUNT, m_nEditprecount);
	DDX_Control(pDX, IDC_EDIT_PRETIME, m_nEditpretime);
	DDX_Text(pDX, IDC_EDIT_PRECOUNT, m_nprecount);
	DDX_Text(pDX, IDC_EDIT_PRETIME, m_npretime);
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
	ON_WM_MOUSEMOVE()
	ON_WM_CTLCOLOR()
	//ON_EN_CHANGE(IDC_EDIT_DETAILSUM, &CControlView::OnEnChangeEditDetailsum)
	
	ON_BN_CLICKED(IDC_BUTTON_EXPORT2TXT, &CControlView::OnBnClickedButtonExport2txt)
	ON_BN_CLICKED(IDC_BUTTON_IMPORTTXT, &CControlView::OnBnClickedButtonImporttxt)
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
	m_redcolor=RGB(255,51,93);                      // 红色
    m_bluecolor=RGB(255,209,71);                    // 蓝色
	m_greencolor = RGB(0,206,159);
    m_textcolor=RGB(255,255,255); 
	m_redbrush.CreateSolidBrush(m_redcolor);      // 红色背景色
    m_bluebrush.CreateSolidBrush(m_bluecolor);   
	m_greenbrush.CreateSolidBrush(m_greencolor);
	//draw background
	
	
	
	
	//END draw
	CFormView::OnInitialUpdate();
	//m_brush.CreateSolidBrush(RGB(255,0,0));
	m_nHight = 1.0;
	m_nPeriod = 0.1;
	UpdateData(FALSE);
	m_ButtonClear.EnableWindow(TRUE);
	FILE*f=fopen("D:\\mydevelopdata\\VSCODE\\MCA\\Cs137.txt","r");
	for(int i = 0;i<1024;i++){
		fscanf(f,"%d",&((CMCADoc*)m_pDocument)->Data[i]);
	}

	// TODO: 在此添加专用代码和/或调用基类
}


void CControlView::PAINTNEW()
{
	
	UpdateData(TRUE);//获取屏幕值至变量
	//设置按钮状态
	m_ButtonPaint.EnableWindow(TRUE);
	m_ButtonClear.EnableWindow(TRUE);
	//设置曲线值
	//
	
	//
	
	for (int i=0;i<1024;i++) 
		
	{ 
		//srand(time(NULL));
		//((CMCADoc*)m_pDocument)->m_Dot[i]=m_nHight*(1+cos(m_nPeriod*i));
		
		((CMCADoc*)m_pDocument)->m_Dot[i] = ((CMCADoc*)m_pDocument)->m_Dot[i]+0.001*((CMCADoc*)m_pDocument)->Data[i]+rand()%3;		
		//((CMCADoc*)m_pDocument)->Data[i]=1.02*(((CMCADoc*)m_pDocument)->Data[i])+1;
	} 
	((CMCADoc*)GetDocument())->UpdateAllViews(this); //重画曲线

}
void CControlView::OnBnClickedButtonPaint()
{
	
	


	((CMCADoc*)GetDocument())->UpdateAllViews(this); //重画曲线
	m_bwillpaint = !m_bwillpaint;
	UpdateData(TRUE); //获取当前选中状态
	//CDetailView*OnPaint();
	CString str_pc,str_pt;	
	GetDlgItem(IDC_EDIT_PRECOUNT)->GetWindowText(str_pc);
	GetDlgItem(IDC_EDIT_PRETIME)->GetWindowText(str_pt);
	pre_count = _wtoi(str_pc);
	pre_time = _wtoi(str_pt);

	
	if (m_bwillpaint) 
{
	SetTimer(1,1000,NULL);
	Invalidate( FALSE ); 
	//选中，设置自动更新 
}
else 
{ 
	KillTimer(1);
    runtime = 0;
	
	//不选中，取消自动更新 
}
	//UpdateData(TRUE);//获取屏幕值至变量
	//设置按钮状态
	//m_ButtonPaint.EnableWindow(FALSE);
	//m_ButtonClear.EnableWindow(TRUE);
	//设置曲线值
	
	
	//for (int i=0;i<512;i++) 
		
	//{ 
		//srand(time(NULL));
		//((CMCADoc*)m_pDocument)->m_Dot[i]=m_nHight*(1+cos(m_nPeriod*i));
		
		//((CMCADoc*)m_pDocument)->m_Dot[i] = ((CMCADoc*)m_pDocument)->m_Dot[i]+0.2*((CMCADoc*)m_pDocument)->Data[i]+rand()%3;		
		//((CMCADoc*)m_pDocument)->Data[i]=1.02*(((CMCADoc*)m_pDocument)->Data[i])+1;
	//} 
	//((CMCADoc*)GetDocument())->UpdateAllViews(NULL); //重画曲线



	// TODO: 在此添加控件通知处理程序代码
}


void CControlView::OnMenuPaint()
{
	// TODO: 在此添加命令处理程序代码
	PAINTNEW();
	//OnBnClickedButtonPaint();
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
    m_ButtonClear.EnableWindow(TRUE);
     //设置曲线值
	UpdateData(FALSE);
	CString have_run;
	m_nHight = 0;
	have_run.Format(_T("%d"),m_nHight);
	//str_Counts.Format(_T("%d"),channel);
	m_EditHight.SetWindowText(have_run);
	
      for (int i=0;i<1024;i++)  
      {
         ((CMCADoc*)m_pDocument)->m_Dot[i]=0;
        }
       //重画曲线
   ((CMainFrame *)AfxGetApp()->m_pMainWnd)->GetActiveDocument()->UpdateAllViews( this ) ;
}


void CControlView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//自动循环增加曲线幅度
	
	int temp_sum = 0;
	for(int k=0;k<1024;k++){
		temp_sum = temp_sum + ((CMCADoc*)m_pDocument)->m_Dot[k]*((CMCADoc*)m_pDocument)->mult;
	}
	if(pre_count<temp_sum){
		KillTimer(1);
		temp_sum = 0;
		m_bwillpaint = !m_bwillpaint;
		AfxMessageBox(_T("已到达预置计数！"));
	}

	if(pre_time<runtime){
		KillTimer(1);
		runtime = 0;
		m_bwillpaint = !m_bwillpaint;
		AfxMessageBox(_T("已达到预置时间！"));
	}
	
    
	m_nHight = m_nHight + 1;
	runtime = runtime + 1;
//((CMCADoc*)m_pDocument)->m_nChannel = ((CMCADoc*)m_pDocument) ->cha;
	//if(((CMCADoc*)m_pDocument)->m_nChannel<512){
		//((CMCADoc*)m_pDocument)->m_nCount =((CMCADoc*)m_pDocument) ->m_Dot[((CMCADoc*)m_pDocument)->m_nChannel];}
	//int max;
	//max = *max_element(((CMCADoc*)m_pDocument)->m_Dot,((CMCADoc*)m_pDocument)->m_Dot+1024);
	
	if (((CMCADoc*)m_pDocument)->m_Dot[24]>250){
		((CMCADoc*)m_pDocument)->mult = ((CMCADoc*)m_pDocument)->mult*2;
		mul  = mul*2;
		for(int i =0;i<1024;i++){
			((CMCADoc*)m_pDocument)->m_Dot[i]=(((CMCADoc*)m_pDocument)->m_Dot[i])/2;
		}
	}

		//(((CMCADoc*)m_pDocument)->m_Dot,((CMCADoc*)m_pDocument)->m_Dot+512);
	//if (m_nHight>3)  m_nHight=1.0;
	//重新画图
	//CString str_Counts;
	//((CMCADoc*)m_pDocument)->m_nCount = ((CMCADoc*)m_pDocument)->m_Dot[((CMCADoc*)m_pDocument)->m_nChannel];
	//str_Counts.Format(_T("%d"),((CMCADoc*)m_pDocument)->m_Dot[((CMCADoc*)m_pDocument)->m_nChannel]);
	//((CMCADoc*)m_pDocument)->m_EditCount.SetWindowText(str_Counts);
	
	UpdateData(FALSE);
	int gap = ((CMCADoc*)m_pDocument)->lbtn_end-((CMCADoc*)m_pDocument)->lbtn_beg;
	int chan = (int) ((CMCADoc*)m_pDocument)->lbtn_beg+((CMCADoc*)m_pDocument)->total_mouse_pos*gap/1024;
	CString str_Counts,str_sum;
	int channel;
	channel = (int) chan %1024;
	//((CMCADoc*)m_pDocument)->m_nCount = ((CMCADoc*)m_pDocument)->m_Dot[chan];
	str_Counts.Format(_T("%d"),((CMCADoc*)m_pDocument)->mult*((CMCADoc*)m_pDocument)->m_Dot[channel]);
	//str_Counts.Format(_T("%d"),channel);
	((CMCADoc*)m_pDocument)->m_EditCount.SetWindowText(str_Counts);
	//OnBnClickedButtonPaint();
	//
	int detail_sum=0;
	for(int i = ((CMCADoc*)m_pDocument)->lbtn_beg;i<=((CMCADoc*)m_pDocument)->lbtn_end;i++)
	{   int k = i%1024;
		detail_sum = detail_sum + ((CMCADoc*)m_pDocument)->m_Dot[k];
	}
	detail_sum  = detail_sum *((CMCADoc*)m_pDocument)->mult;
	str_sum.Format(_T("%d"),detail_sum);
	((CMCADoc*)m_pDocument)->m_EditDetailSum.SetWindowText(str_sum);
	
	//
	PAINTNEW();

	CFormView::OnTimer(nIDEvent);
}


void CControlView::OnBnClickedCheckTimer()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); //获取当前选中状态
if (m_bCheckAuto) 
{
	SetTimer(1,1000,NULL);
	Invalidate( FALSE ); 
	//选中，设置自动更新 
}
else 
{ 
	KillTimer(1);
	//不选中，取消自动更新 
}

}


void CControlView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//m_nChannel = ((CMCADoc*)m_pDocument) ->cha;

	CFormView::OnMouseMove(nFlags, point);
}


HBRUSH CControlView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	int id =::GetDlgCtrlID(pWnd->m_hWnd);//取得ID
    if(id == IDC_EDIT_DETAILSUM)
    {
        pDC->SetBkColor(m_bluecolor); 
		pDC->SetTextColor(m_textcolor); // change the text color
        hbr = (HBRUSH) m_bluebrush;  

		
    }
	else if(id ==IDC_EDIT_DTCOUNT)
	{
        pDC->SetBkColor(m_redcolor); 
		pDC->SetTextColor(m_textcolor); // change the text color
        hbr = (HBRUSH) m_redbrush;  
	}
	else if(id ==IDC_EDIT_DTCHID)
	{
		pDC->SetBkColor(m_greencolor); 
		pDC->SetTextColor(m_textcolor); // change the text color
        hbr = (HBRUSH) m_greenbrush;  
	}

	return hbr;
	
}






void CControlView::OnBnClickedButtonExport2txt()
{

	// TODO: 在此添加控件通知处理程序代码
	BOOL isOpen = FALSE;		//是否打开(否则为保存)	
	CString defaultDir = L"E:\\FileTest";	//默认打开的文件路径	
	CString fileName = L"";			//默认打开的文件名	
	CString filter = L"文件 (*.doc; *.ppt; *.xls; *.txt)|*.doc;*.ppt;*.xls;*.txt||";	//文件过虑的类型	
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY|OFN_READONLY, filter, NULL);	
	openFileDlg.GetOFN().lpstrInitialDir = L"E:\\FileTest\\test.doc";	
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaultDir + "\\" + fileName;
	if(result == IDOK) {		filePath = openFileDlg.GetPathName();	}

	try
	{
		CStdioFile export_file;
		export_file.Open(filePath,CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		for (int i = 0; i < 1024; i++)
		{
			CString datai;
			datai.Format(_T("%d    "),((CMCADoc*)m_pDocument)->mult*((CMCADoc*)m_pDocument)->m_Dot[i]);
			//datai.Format(_T("%d    "),i);
			export_file.WriteString(datai);
			export_file.WriteString(_T("\r\n"));


		}
		export_file.Close();


	}
	catch(CFileException* e)
	{
		e->ReportError();
		e->Delete();
	}

}


void CControlView::OnBnClickedButtonImporttxt()
{
	
	BOOL isOpen = TRUE;		//是否打开(否则为保存)	
	CString defaultDir = L"E:\\FileTest";	//默认打开的文件路径	
	CString fileName = L"";			//默认打开的文件名	
	CString filter = L"文件 (*.doc; *.ppt; *.xls; *.txt)|*.doc;*.ppt;*.xls;*.txt||";	//文件过虑的类型	
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY|OFN_READONLY, filter, NULL);	
	openFileDlg.GetOFN().lpstrInitialDir = L"E:\\FileTest\\test.doc";	
	INT_PTR result = openFileDlg.DoModal();	
	CString filePath = defaultDir + "\\test.doc";	
	if(result == IDOK) {		filePath = openFileDlg.GetPathName();	}
	USES_CONVERSION;
	char * pFileName = T2A(filePath);
	FILE*f=fopen(pFileName,"r");
	for(int i = 0;i<1024;i++){
		fscanf(f,"%d",&((CMCADoc*)m_pDocument)->Data[i]);
	}

}

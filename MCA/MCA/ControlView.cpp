// ControlView.cpp : ʵ���ļ�
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


// CControlView ���

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


// CControlView ��Ϣ�������


void CControlView::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CControlView::OnBnClickedDialogControl()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


//void CControlView::OnEnChangeEdit2()
//{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CFormView::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

//#1015

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}


void CControlView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	m_nHight = 10.0;
	m_nPeriod = 0.1;
	UpdateData(FALSE);
	m_ButtonClear.EnableWindow(FALSE);


	// TODO: �ڴ����ר�ô����/����û���
}


void CControlView::OnBnClickedButtonPaint()
{
	
	UpdateData(TRUE);//��ȡ��Ļֵ������
	//���ð�ť״̬
	m_ButtonPaint.EnableWindow(FALSE);
	m_ButtonClear.EnableWindow(TRUE);
	//��������ֵ

	for (int i=0;i<512;i++) 
	{ ((CMCADoc*)m_pDocument)->m_Dot[i]=m_nHight*(1+sin(m_nPeriod*i)); } 
	((CMCADoc*)GetDocument())->UpdateAllViews(NULL); //�ػ�����



	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CControlView::OnMenuPaint()
{
	// TODO: �ڴ���������������
	OnBnClickedButtonPaint();
}


void CControlView::OnMenuClear()
{
	// TODO: �ڴ���������������
	OnBnClickedButtonClear();
}


void CControlView::OnBnClickedButtonClear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		 //���ð�ť״̬
    m_ButtonPaint.EnableWindow(TRUE);
    m_ButtonClear.EnableWindow(FALSE);
     //��������ֵ
      for (int i=0;i<512;i++)  
      {
         ((CMCADoc*)m_pDocument)->m_Dot[i]=0;
        }
       //�ػ�����
   ((CMainFrame *)AfxGetApp()->m_pMainWnd)->GetActiveDocument()->UpdateAllViews( NULL ) ;
}


void CControlView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//�Զ�ѭ���������߷���
	m_nHight ++; 
	if (m_nHight>30)  m_nHight=10.0;
	//���»�ͼ
	UpdateData(FALSE);
	OnBnClickedButtonPaint();

	CFormView::OnTimer(nIDEvent);
}


void CControlView::OnBnClickedCheckTimer()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); //��ȡ��ǰѡ��״̬
if (m_bCheckAuto) 
{
	SetTimer(1,500,NULL);
	Invalidate( FALSE ); 
	//ѡ�У������Զ����� 
}
else 
{ 
	KillTimer(1);
	//��ѡ�У�ȡ���Զ����� 
}

}

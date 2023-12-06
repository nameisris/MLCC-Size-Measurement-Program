// Model_Info.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MainProgram.h"
#include "Model_Info.h"
#include "Model.h"
#include "afxdialogex.h"
#include "MainProgramDlg.h"


// Model_Info 대화 상자입니다.

IMPLEMENT_DYNAMIC(Model_Info, CDialog)

Model_Info::Model_Info(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_Model_Info, pParent)
	, m_Edit_Model_Info(_T(""))

{

}

Model_Info::~Model_Info()
{
}

void Model_Info::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_Model_Info, m_Edit_Model_Info);
	//  DDX_Text(pDX, IDC_EDIT_T1, m_Edit_L1_Info);
	
}


BEGIN_MESSAGE_MAP(Model_Info, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_Get_Info, &Model_Info::OnBnClickedButtonGetInfo)
	ON_BN_CLICKED(IDCANCEL, &Model_Info::OnBnClickedCancel)
	
END_MESSAGE_MAP()


// Model_Info 메시지 처리기입니다.


void Model_Info::OnBnClickedButtonGetInfo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	
}


void Model_Info::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	OnOK();
}


BOOL Model_Info::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_Model_Info = ((CMainProgramDlg*)GetParent())->m_Num_model;
	SetDlgItemInt(IDC_EDIT_Model_Info, m_Model_Info);


	if (m_Model_Info == 3216)
	{
		m_L1_Info = 32;
		m_T1_Info = 16;
		m_LBW_Info = 6;
		m_RBW_Info = 6;
		SetDlgItemInt(IDC_EDIT_L1, m_L1_Info);
		SetDlgItemInt(IDC_EDIT_T1, m_T1_Info);
		SetDlgItemInt(IDC_EDIT_LBW, m_LBW_Info);
		SetDlgItemInt(IDC_EDIT_RBW, m_RBW_Info);
	}

	if (m_Model_Info == 3225)
	{
		m_L1_Info = 32;
		m_T1_Info = 25;
		m_LBW_Info = 7;
		m_RBW_Info = 7;
		SetDlgItemInt(IDC_EDIT_L1, m_L1_Info);
		SetDlgItemInt(IDC_EDIT_T1, m_T1_Info);
		SetDlgItemInt(IDC_EDIT_LBW, m_LBW_Info);
		SetDlgItemInt(IDC_EDIT_RBW, m_RBW_Info);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


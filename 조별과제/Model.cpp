// Model.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MainProgram.h"
#include "Model.h"
#include "afxdialogex.h"
#include "Model_Info.h"
#include "MainProgramDlg.h"
// Model 대화 상자입니다.

IMPLEMENT_DYNAMIC(Model, CDialogEx)

Model::Model(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_Model, pParent)
	
	, m_Edit_Model(_T(""))
{

}

Model::~Model()
{
}

void Model::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT, m_Edit_Model);
}


BEGIN_MESSAGE_MAP(Model, CDialogEx)

	ON_BN_CLICKED(IDC_BUTTON_Exit, &Model::OnBnClickedButtonExit)

	ON_BN_CLICKED(IDC_BUTTON_3216, &Model::OnBnClickedButton3216)
	ON_BN_CLICKED(IDC_BUTTON_3225, &Model::OnBnClickedButton3225)
END_MESSAGE_MAP()


// Model 메시지 처리기입니다.





void Model::OnBnClickedButtonExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}



void Model::OnBnClickedButton3216()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	
	SetDlgItemInt(IDC_EDIT, m_3216);
	
	((CMainProgramDlg*)GetParent())->m_Num_model = m_3216;
	((CMainProgramDlg*)GetParent())->SetDlgItemInt(IDC_EDIT_Main_Model, m_3216);
	
	
	//((CMainProgramDlg*)GetParent())->m_Info->SetDlgItemInt(IDC_EDIT_Model_Info, m_3216);
	
	
	
}


void Model::OnBnClickedButton3225()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	SetDlgItemInt(IDC_EDIT, m_3225);

	((CMainProgramDlg*)GetParent())->m_Num_model = m_3225;
	((CMainProgramDlg*)GetParent())->SetDlgItemInt(IDC_EDIT_Main_Model, m_3225);
	//((CMainProgramDlg*)GetParent())->m_Info->SetDlgItemInt(IDC_EDIT_Model_Info, m_3225);

}


BOOL Model::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_3216 = 3216;
	m_3225 = 3225;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

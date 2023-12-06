// Model_Info.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MainProgram.h"
#include "Model_Info.h"
#include "Model.h"
#include "afxdialogex.h"
#include "MainProgramDlg.h"


// Model_Info ��ȭ �����Դϴ�.

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


// Model_Info �޽��� ó�����Դϴ�.


void Model_Info::OnBnClickedButtonGetInfo()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	
}


void Model_Info::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	OnOK();
}


BOOL Model_Info::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
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
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


// Setting.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MainProgram.h"
#include "Setting.h"
#include "afxdialogex.h"
#include "MainProgramDlg.h"


// Setting ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Setting, CDialog)

Setting::Setting(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_Setting, pParent)
	, m_iBright(0)
	
{

}

Setting::~Setting()
{
}

void Setting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);




	//DDX_Text(pDX, IDC_EDIT_BrightNum, m_BrightNum);
	//DDX_Control(pDX, IDC_SCR_HORI, m_scrHori);
	DDX_Control(pDX, IDC_SLIDER_L1_VALUE, m_slider_L1_value);
	DDX_Control(pDX, IDC_EDIT_L1_VALUE, m_edit_L1_value);
	DDX_Control(pDX, IDC_SLIDER_T1_VALUE, m_slider_T1_value);
	DDX_Control(pDX, IDC_EDIT_T1_VALUE, m_edit_T1_value);
	DDX_Control(pDX, IDC_SLIDER_LBW_VALUE, m_slider_LBW_value);
	DDX_Control(pDX, IDC_EDIT_LBW_VALUE, m_edit_LBW_value);
	DDX_Control(pDX, IDC_SLIDER_RBW_VALUE, m_slider_RBW_value);
	DDX_Control(pDX, IDC_EDIT_RBW_VALUE, m_edit_RBW_value);
}


BEGIN_MESSAGE_MAP(Setting, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_NewSet, &Setting::OnBnClickedButtonNewset)
//	ON_WM_HSCROLL()
	
//	ON_WM_HSCROLL()
ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_L1_VALUE, &Setting::OnNMCustomdrawSliderL1Value)
ON_EN_CHANGE(IDC_EDIT_L1_VALUE, &Setting::OnEnChangeEditL1Value)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_T1_VALUE, &Setting::OnNMCustomdrawSliderT1Value)
ON_EN_CHANGE(IDC_EDIT_T1_VALUE, &Setting::OnEnChangeEditT1Value)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_LBW_VALUE, &Setting::OnNMCustomdrawSliderLbwValue)
ON_EN_CHANGE(IDC_EDIT_LBW_VALUE, &Setting::OnEnChangeEditLbwValue)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_RBW_VALUE, &Setting::OnNMCustomdrawSliderRbwValue)
ON_EN_CHANGE(IDC_EDIT_RBW_VALUE, &Setting::OnEnChangeEditRbwValue)
ON_BN_CLICKED(IDC_BUTTON_STANDARD_VALUE, &Setting::OnBnClickedButtonStandardValue)
ON_BN_CLICKED(IDC_BUTTON_Exit, &Setting::OnBnClickedButtonExit)
END_MESSAGE_MAP()


// Setting �޽��� ó�����Դϴ�.


void Setting::OnBnClickedButtonNewset()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//���� �����ǵ���
	UpdateData(TRUE);
	
	((CMainProgramDlg*)GetParent())->m_L1_start_value = m_L1_pos;
	((CMainProgramDlg*)GetParent())->m_T1_start_value = m_T1_pos;
	((CMainProgramDlg*)GetParent())->m_LBW_start_value = m_LBW_pos;
	((CMainProgramDlg*)GetParent())->m_RBW_start_value = m_RBW_pos;
	
	MessageBox("���ŵǾ����ϴ�.");
	UpdateData(FALSE);


}


BOOL Setting::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_iBright = 0;
	//((CMainProgramDlg*)GetParent())->
	m_L1_pos = ((CMainProgramDlg*)GetParent())->m_L1_start_value;
	m_T1_pos = ((CMainProgramDlg*)GetParent())->m_T1_start_value;
	m_LBW_pos = ((CMainProgramDlg*)GetParent())->m_LBW_start_value;
	m_RBW_pos = ((CMainProgramDlg*)GetParent())->m_RBW_start_value;

	m_slider_L1_value.SetRange(0, 255);
	m_slider_L1_value.SetPos(m_L1_pos);

	m_slider_T1_value.SetRange(0, 255);
	m_slider_T1_value.SetPos(m_T1_pos);

	m_slider_LBW_value.SetRange(0, 255);
	m_slider_LBW_value.SetPos(m_LBW_pos);

	m_slider_RBW_value.SetRange(0, 255);
	m_slider_RBW_value.SetPos(m_RBW_pos);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}




//void Setting::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
//{
//	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
//	switch (nSBCode)
//	{
//	case SB_LINELEFT:
//		m_iBright--;
//		break;
//	case SB_LINERIGHT:
//		m_iBright++;
//		break;
//	case SB_PAGELEFT:
//		m_iBright--;
//		break;
//	case SB_PAGERIGHT:
//		m_iBright++;
//		break;
//	case SB_THUMBPOSITION:
//		m_iBright = nPos;
//		break;
//	}
//	m_BrightNum = m_scrHori.GetScrollPos();
//	m_scrHori.SetScrollPos(m_iBright);
//	Invalidate(FALSE);
//	UpdateData(FALSE);
//
//
//	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
//}


void Setting::OnNMCustomdrawSliderL1Value(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
	//int nPos;
	CString strPos;

	m_L1_pos = m_slider_L1_value.GetPos();		// get current position of slider
	strPos.Format(_T("%d"), m_L1_pos);				// convert position int to CString
	m_edit_L1_value.SetWindowTextA(strPos);	// set position to edit control
}


void Setting::OnEnChangeEditL1Value()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	//int nPos;
	CString strPos;

	m_edit_L1_value.SetSel(0, -1);	// select all words of edit box
	m_edit_L1_value.SetSel(-1, -1);	// set cursor position to end of word

	m_edit_L1_value.GetWindowTextA(strPos);	// get position CString value
	m_L1_pos = _ttoi(strPos);						// convert position CString to int
	m_slider_L1_value.SetPos(m_L1_pos);			// set position to slider control
}


void Setting::OnNMCustomdrawSliderT1Value(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	//int nPos;
	CString strPos;

	m_T1_pos = m_slider_T1_value.GetPos();		// get current position of slider
	strPos.Format(_T("%d"), m_T1_pos);				// convert position int to CString
	m_edit_T1_value.SetWindowTextA(strPos);	// set position to edit control
}


void Setting::OnEnChangeEditT1Value()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	//int nPos;
	CString strPos;

	m_edit_T1_value.SetSel(0, -1);	// select all words of edit box
	m_edit_T1_value.SetSel(-1, -1);	// set cursor position to end of word

	m_edit_T1_value.GetWindowTextA(strPos);	// get position CString value
	m_T1_pos = _ttoi(strPos);						// convert position CString to int
	m_slider_T1_value.SetPos(m_T1_pos);			// set position to slider control
}


void Setting::OnNMCustomdrawSliderLbwValue(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	//int nPos;
	CString strPos;

	m_LBW_pos = m_slider_LBW_value.GetPos();		// get current position of slider
	strPos.Format(_T("%d"), m_LBW_pos);				// convert position int to CString
	m_edit_LBW_value.SetWindowTextA(strPos);	// set position to edit control
}


void Setting::OnEnChangeEditLbwValue()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	//int nPos;
	CString strPos;

	m_edit_LBW_value.SetSel(0, -1);	// select all words of edit box
	m_edit_LBW_value.SetSel(-1, -1);	// set cursor position to end of word

	m_edit_LBW_value.GetWindowTextA(strPos);	// get position CString value
	m_LBW_pos = _ttoi(strPos);						// convert position CString to int
	m_slider_LBW_value.SetPos(m_LBW_pos);			// set position to slider control
}


void Setting::OnNMCustomdrawSliderRbwValue(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
	//int nPos;
	CString strPos;

	m_RBW_pos = m_slider_RBW_value.GetPos();		// get current position of slider
	strPos.Format(_T("%d"), m_RBW_pos);				// convert position int to CString
	m_edit_RBW_value.SetWindowTextA(strPos);	// set position to edit control
}


void Setting::OnEnChangeEditRbwValue()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//int nPos;
	CString strPos;

	m_edit_RBW_value.SetSel(0, -1);	// select all words of edit box
	m_edit_RBW_value.SetSel(-1, -1);	// set cursor position to end of word

	m_edit_RBW_value.GetWindowTextA(strPos);	// get position CString value
	m_RBW_pos = _ttoi(strPos);						// convert position CString to int
	m_slider_RBW_value.SetPos(m_RBW_pos);			// set position to slider control

}


void Setting::OnBnClickedButtonStandardValue()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	
	m_slider_L1_value.SetPos(80);


	m_slider_T1_value.SetPos(50);

	
	m_slider_LBW_value.SetPos(127);

	
	m_slider_RBW_value.SetPos(127);


}


void Setting::OnBnClickedButtonExit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnOK();
}

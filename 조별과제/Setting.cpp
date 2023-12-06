// Setting.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MainProgram.h"
#include "Setting.h"
#include "afxdialogex.h"
#include "MainProgramDlg.h"


// Setting 대화 상자입니다.

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


// Setting 메시지 처리기입니다.


void Setting::OnBnClickedButtonNewset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//변수 연동되도록
	UpdateData(TRUE);
	
	((CMainProgramDlg*)GetParent())->m_L1_start_value = m_L1_pos;
	((CMainProgramDlg*)GetParent())->m_T1_start_value = m_T1_pos;
	((CMainProgramDlg*)GetParent())->m_LBW_start_value = m_LBW_pos;
	((CMainProgramDlg*)GetParent())->m_RBW_start_value = m_RBW_pos;
	
	MessageBox("갱신되었습니다.");
	UpdateData(FALSE);


}


BOOL Setting::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
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
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}




//void Setting::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	//int nPos;
	CString strPos;

	m_L1_pos = m_slider_L1_value.GetPos();		// get current position of slider
	strPos.Format(_T("%d"), m_L1_pos);				// convert position int to CString
	m_edit_L1_value.SetWindowTextA(strPos);	// set position to edit control
}


void Setting::OnEnChangeEditL1Value()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	//int nPos;
	CString strPos;

	m_T1_pos = m_slider_T1_value.GetPos();		// get current position of slider
	strPos.Format(_T("%d"), m_T1_pos);				// convert position int to CString
	m_edit_T1_value.SetWindowTextA(strPos);	// set position to edit control
}


void Setting::OnEnChangeEditT1Value()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	//int nPos;
	CString strPos;

	m_LBW_pos = m_slider_LBW_value.GetPos();		// get current position of slider
	strPos.Format(_T("%d"), m_LBW_pos);				// convert position int to CString
	m_edit_LBW_value.SetWindowTextA(strPos);	// set position to edit control
}


void Setting::OnEnChangeEditLbwValue()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	//int nPos;
	CString strPos;

	m_RBW_pos = m_slider_RBW_value.GetPos();		// get current position of slider
	strPos.Format(_T("%d"), m_RBW_pos);				// convert position int to CString
	m_edit_RBW_value.SetWindowTextA(strPos);	// set position to edit control
}


void Setting::OnEnChangeEditRbwValue()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	
	m_slider_L1_value.SetPos(80);


	m_slider_T1_value.SetPos(50);

	
	m_slider_LBW_value.SetPos(127);

	
	m_slider_RBW_value.SetPos(127);


}


void Setting::OnBnClickedButtonExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}

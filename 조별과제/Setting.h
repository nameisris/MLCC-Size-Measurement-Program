#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// Setting 대화 상자입니다.

class Setting : public CDialog
{
	DECLARE_DYNAMIC(Setting)

public:
	Setting(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Setting();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Setting };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonNewset();

private:
	int m_iBright;

public:
	virtual BOOL OnInitDialog();
	
//	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl m_slider_L1_value;
	CEdit m_edit_L1_value;
	afx_msg void OnNMCustomdrawSliderL1Value(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditL1Value();
	CSliderCtrl m_slider_T1_value;
	CEdit m_edit_T1_value;
	afx_msg void OnNMCustomdrawSliderT1Value(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditT1Value();
	afx_msg void OnNMCustomdrawSliderLbwValue(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_slider_LBW_value;
	CEdit m_edit_LBW_value;
	afx_msg void OnEnChangeEditLbwValue();
	CSliderCtrl m_slider_RBW_value;
	CEdit m_edit_RBW_value;
	afx_msg void OnNMCustomdrawSliderRbwValue(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditRbwValue();
	afx_msg void OnBnClickedButtonStandardValue();
	afx_msg void OnBnClickedButtonExit();
	int m_L1_pos;
	int m_T1_pos;
	int m_LBW_pos;
	int m_RBW_pos;

};

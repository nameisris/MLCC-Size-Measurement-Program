#pragma once


// Model_Check 대화 상자입니다.

class Model_Check : public CDialog
{
	DECLARE_DYNAMIC(Model_Check)

public:
	Model_Check(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Model_Check();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Model_Check };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLbw();
	afx_msg void OnBnClickedButtonRbw();
	afx_msg void OnBnClickedButtonnewcheck();
};
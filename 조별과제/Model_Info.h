#pragma once


// Model_Info 대화 상자입니다.

class Model_Info : public CDialog
{
	DECLARE_DYNAMIC(Model_Info)

public:
	Model_Info(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Model_Info();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Model_Info };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonGetInfo();
	int m_Model_Info;
	afx_msg void OnBnClickedCancel();
	CString m_Edit_Model_Info;
	virtual BOOL OnInitDialog();
	int m_L1_Info;
	int m_T1_Info;
	int m_LBW_Info;
	int m_RBW_Info;

	CString m_Edit_T1_Info;
	CString m_Edit_L1_Info;
	CString m_Edit_LBW_Info;
	CString m_Edit_RBW_Info;
};

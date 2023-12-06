#pragma once


// Model 대화 상자입니다.

class Model : public CDialogEx
{
	DECLARE_DYNAMIC(Model)

public:
	Model(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Model();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Model };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_No_Model;
	
	int m_3216;
	int m_3225;

	


	afx_msg void OnBnClickedButtonExit();
	
	
	
	CString m_Edit_Model;
	afx_msg void OnBnClickedButton3216();
	afx_msg void OnBnClickedButton3225();
	virtual BOOL OnInitDialog();
};

#pragma once


// Model ��ȭ �����Դϴ�.

class Model : public CDialogEx
{
	DECLARE_DYNAMIC(Model)

public:
	Model(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Model();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Model };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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

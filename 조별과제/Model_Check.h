#pragma once


// Model_Check ��ȭ �����Դϴ�.

class Model_Check : public CDialog
{
	DECLARE_DYNAMIC(Model_Check)

public:
	Model_Check(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Model_Check();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Model_Check };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLbw();
	afx_msg void OnBnClickedButtonRbw();
	afx_msg void OnBnClickedButtonnewcheck();
};
#pragma once


// Lot ��ȭ �����Դϴ�.

class Lot : public CDialog
{
	DECLARE_DYNAMIC(Lot)

public:
	Lot(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Lot();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Lot };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strLot;
	afx_msg void OnBnClickedButtonNolot();
};

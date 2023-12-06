
// MainProgramDlg.h : ��� ����
//

#pragma once
#include "Model.h"
#include "Model_Info.h"
#include "Lot.h"
#include "Setting.h"
#include "Model_Check.h"
#include <opencv2/opencv.hpp>
#include "afxwin.h"
#include "afxcmn.h"
#include "ColorListCtrl.h"

using namespace cv;
using namespace std;

// CMainProgramDlg ��ȭ ����
class CMainProgramDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMainProgramDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

	BITMAPINFO *m_pBitmapInfo; // Bitmap ������ ��� ����ü
	Mat m_Original_Img; // ���� �̹���

	// �κк� ���� �̹���
	Mat m_L1_Img;
	Mat m_T1_Img;
	Mat m_LBW_Img;
	Mat m_RBW_Img;

	// �κк� ���� ������
	CString m_L1;
	CString m_T1;
	CString m_LBW;
	CString m_RBW;

	// ���
	CString path;

	// ���� �Լ�
	void CalculateL1();
	void CalculateT1();
	void CalculateLBW();
	void CalculateRBW();

	// ���� ���
	void CalculateSize(int row, CString model);

	void CreateBitmapInfo(int w, int h, int bpp); // Bitmap ������ �����ϴ� �Լ�
	void DrawImage(Mat img, int IDC); // �׸��� �Լ�

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

// �����Դϴ�.

protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonExit();
	CString m_EditDate;

	CString m_strModel;
	afx_msg void OnBnClickedButtonVideo();
	afx_msg void OnBnClickedButtonSelect();

	afx_msg void OnBnClickedButtonSetting();
	CRect m_MLCCImage;
	CRect m_Back;
	CImage m_Img;
	CImage m_Dlg;
	CString m_str;
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonModel();

	//Modeless
	Model *m_Model;
	Model_Info *m_Info;
	Setting *m_Set;
	Model_Check *m_Model_Check;
	//
	CImage m_Save;
	
	//���� ���� �� ��� ����
	int m_L1_start_value;
	int m_T1_start_value;
	int m_LBW_start_value;
	int m_RBW_start_value;

	//��
	int m_Num_model;
	
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonL1();
	afx_msg void OnBnClickedButtonT1();
	afx_msg void OnBnClickedButtonLbw();
	afx_msg void OnBnClickedButtonRbw();
	CColorListCtrl m_List;
	CString m_strLot;
	afx_msg void OnBnClickedButtonResultClear();
	CListBox m_ListBox;
	afx_msg void OnLbnDblclkFileList();
	afx_msg void OnBnClickedButtonFilelistClear();
	afx_msg void OnBnClickedButtonCheckAll();
	afx_msg void OnBnClickedButtonOriginal();
	afx_msg void OnNMDblclkResultList(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_MainModel;
};

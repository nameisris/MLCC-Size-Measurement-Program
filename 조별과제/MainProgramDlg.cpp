
// MainProgramDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MainProgram.h"
#include "MainProgramDlg.h"
#include "afxdialogex.h"
#include "Model.h"
#include "Setting.h"
#include "Model_Info.h"
#include "atlimage.h"
#include "XLEzAutomation.h"
#include "opencv2/imgcodecs.hpp"
#include <opencv2/videoio.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc.hpp"

#include "opencv2/highgui.hpp"
#include <iostream>
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//opencv
using namespace cv;
using namespace std;
RNG rng(12345);

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
	CFont newFont;
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMainProgramDlg ��ȭ ����



CMainProgramDlg::CMainProgramDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
	, m_EditDate(_T(""))
	, m_strModel(_T(""))

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainProgramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Date, m_EditDate);

	DDX_Control(pDX, IDC_RESULT_LIST, m_List);
	DDX_Control(pDX, IDC_FILE_LIST, m_ListBox);
	//  DDX_Text(pDX, IDC_EDIT_Main_Model, m_MainModel);
	DDX_Control(pDX, IDC_EDIT_Main_Model, m_MainModel);
}

BEGIN_MESSAGE_MAP(CMainProgramDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Exit, &CMainProgramDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_Video, &CMainProgramDlg::OnBnClickedButtonVideo)
	ON_BN_CLICKED(IDC_BUTTON_Select, &CMainProgramDlg::OnBnClickedButtonSelect)
	ON_BN_CLICKED(IDC_BUTTON_Setting, &CMainProgramDlg::OnBnClickedButtonSetting)
	ON_BN_CLICKED(IDC_BUTTON_Start, &CMainProgramDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_Model, &CMainProgramDlg::OnBnClickedButtonModel)
	ON_BN_CLICKED(IDC_BUTTON_Save, &CMainProgramDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_L1, &CMainProgramDlg::OnBnClickedButtonL1)
	ON_BN_CLICKED(IDC_BUTTON_T1, &CMainProgramDlg::OnBnClickedButtonT1)
	ON_BN_CLICKED(IDC_BUTTON_LBW, &CMainProgramDlg::OnBnClickedButtonLbw)
	ON_BN_CLICKED(IDC_BUTTON_RBW, &CMainProgramDlg::OnBnClickedButtonRbw)
	ON_BN_CLICKED(IDC_BUTTON_RESULT_CLEAR, &CMainProgramDlg::OnBnClickedButtonResultClear)
	ON_LBN_DBLCLK(IDC_FILE_LIST, &CMainProgramDlg::OnLbnDblclkFileList)
	ON_BN_CLICKED(IDC_BUTTON_FILELIST_CLEAR, &CMainProgramDlg::OnBnClickedButtonFilelistClear)
	ON_BN_CLICKED(IDC_BUTTON_CHECK_ALL, &CMainProgramDlg::OnBnClickedButtonCheckAll)
	ON_BN_CLICKED(IDC_BUTTON_ORIGINAL, &CMainProgramDlg::OnBnClickedButtonOriginal)
	ON_NOTIFY(NM_DBLCLK, IDC_RESULT_LIST, &CMainProgramDlg::OnNMDblclkResultList)
END_MESSAGE_MAP()


// CMainProgramDlg �޽��� ó����

BOOL CMainProgramDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.
	
	//Back Draw

	//���� �� ��¥, �ð� editcontrol�� ������ (��Ʈ, ���� ũ��, ��� ���� �ʿ�)
	SetTimer(1,100,NULL);
	char DateText[100];
	
	SYSTEMTIME sT;
	GetLocalTime(&sT);
	//��¥ (��-��-��)
	sprintf(DateText, "%d-%d-%d", sT.wYear, sT.wMonth, sT.wDay);
	m_EditDate = DateText;
	
	//�˻� ��(���� ����)
	//m_MainModel = m_strModel;

	UpdateData(FALSE);

	// �׸� ��ư �����
	GetDlgItem(IDC_BUTTON_ORIGINAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_L1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_T1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_LBW)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_RBW)->ShowWindow(SW_HIDE);

	// ����Ʈ ��Ʈ���� ũ�⸦ ���´�.
	CRect rect;
	m_List.GetClientRect(&rect);
	int width8 = rect.Width() / 8;

	m_List.InsertColumn(0, _T("����"), LVCFMT_LEFT, width8);
	m_List.InsertColumn(1, _T("Lot Num"), LVCFMT_LEFT, width8);
	m_List.InsertColumn(2, _T("L1"), LVCFMT_LEFT, width8);
	m_List.InsertColumn(3, _T("T1"), LVCFMT_LEFT, width8);
	m_List.InsertColumn(4, _T("LBW"), LVCFMT_LEFT, width8);
	m_List.InsertColumn(5, _T("RBW"), LVCFMT_LEFT, width8);
	m_List.InsertColumn(6, _T("File Name"), LVCFMT_LEFT, width8);
	m_List.InsertColumn(7, _T("Model"), LVCFMT_LEFT, width8);

	//m_List.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

	//���� ���̾�α�
	m_L1_start_value = 80;
	m_T1_start_value = 50;
	m_RBW_start_value = 127;
	m_LBW_start_value = 127;

	//model dialog
	
	//SetDlgItemInt(IDC_EDIT_Main_Model, m_Num_model);

	// BITMAPINFO �ʱ�ȭ
	m_pBitmapInfo = NULL;

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.

}

void CMainProgramDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMainProgramDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMainProgramDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMainProgramDlg::CreateBitmapInfo(int w, int h, int bpp)
{
	/*
	if (m_pBitmapInfo != NULL)
	{
		delete m_pBitmapInfo;
		m_pBitmapInfo = NULL;
	}
	*/

	if (bpp == 8)
		m_pBitmapInfo = (BITMAPINFO *) new BYTE[sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)];
	else // 24 or 32bit
		m_pBitmapInfo = (BITMAPINFO *) new BYTE[sizeof(BITMAPINFO)];

	m_pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBitmapInfo->bmiHeader.biPlanes = 1;
	m_pBitmapInfo->bmiHeader.biBitCount = bpp;
	m_pBitmapInfo->bmiHeader.biCompression = BI_RGB;
	m_pBitmapInfo->bmiHeader.biSizeImage = 0;
	m_pBitmapInfo->bmiHeader.biXPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biYPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biClrUsed = 0;
	m_pBitmapInfo->bmiHeader.biClrImportant = 0;

	if (bpp == 8)
	{
		for (int i = 0; i < 256; i++)
		{
			m_pBitmapInfo->bmiColors[i].rgbBlue = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbGreen = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbRed = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbReserved = 0;
		}
	}

	m_pBitmapInfo->bmiHeader.biWidth = w;
	m_pBitmapInfo->bmiHeader.biHeight = -h;
}


void CMainProgramDlg::DrawImage(Mat img, int IDC)
{
	CreateBitmapInfo(img.cols, img.rows, img.channels() * 8);

	CClientDC dc(GetDlgItem(IDC));

	CRect rect;
	GetDlgItem(IDC)->GetClientRect(&rect);

	SetStretchBltMode(dc.GetSafeHdc(), COLORONCOLOR);

	StretchDIBits(dc.GetSafeHdc(), 0, 0, img.cols, img.rows, 0, 0, img.cols, img.rows, img.data, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
}


void CMainProgramDlg::OnBnClickedButtonVideo()
{
	CString model;
	m_MainModel.GetWindowTextA(model);

	// �� ������ �ȵƴٸ�
	if (model == "") {
		MessageBox(_T("�� ������ �ȵǾ����ϴ�."), _T("�˸�"), MB_OK);
	}
	else {
		CString File, filem, strre;
		CString strFileList;
		int fileCnt;
		bool check = false;

		CFileDialog dlg(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT, "image file(*.jpg;*.bmp;*.png;*tif;)|*.jpg;*.bmp;*.png;*tif;|All Files(*.*)|*.*||", this);

		const int c_cMaxFiles = 20000 /*������ ���� ����*/;
		// �޸� ������������ Ȯ�� �����ָ� � ����
		const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
		dlg.GetOFN().lpstrFile = strFileList.GetBuffer(c_cbBuffSize);
		dlg.GetOFN().nMaxFile = c_cbBuffSize;

		if (dlg.DoModal() == IDOK)
		{
			path = dlg.GetPathName();
			for (POSITION pos = dlg.GetStartPosition(); pos != NULL;)
			{
				// ��ü������ ResetContent
				File = dlg.GetNextPathName(pos);

				filem = File.Right(File.GetLength() - File.ReverseFind(_T('\\')) - 1);
				// ��θ� ������ ���ϸ�       

				filem = filem.Left(filem.GetLength() - 4);
				// Ȯ���� ���� ( ex - .jpg )

				if (m_ListBox.GetCount() == 0)
				{
					m_ListBox.AddString(filem);
				}
				else {
					for (int i = 0; i < m_ListBox.GetCount(); i++)
					{
						CString cStr;
						m_ListBox.GetText(i, cStr); // ���� ���õ� ���� ���ڿ��� cStr�� �����Ѵ�.

						// ������ ���ϸ��� ����Ʈ�ڽ��� �̹� �����ϴ� ���� �ߺ��ȴٸ�
						if (cStr == filem)
							check = true;
					}
					if (check)
					{
						// AfxMessageBox("�ߺ� ������ ���ܵǾ����ϴ�.");
						check = false;
					}
					else
					{
						m_ListBox.AddString(filem);
					}
				}
			}
		}

		fileCnt = m_ListBox.GetCount();
		strre.Format(_T("�� %d���� �̹��� �ε� (�ߺ� �̹��� ����)"), fileCnt);
		AfxMessageBox(strre);
	}
}


void CMainProgramDlg::OnBnClickedButtonSelect()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_Model = new Model;
	
	m_Model->Create(IDD_DIALOG_Model);
	m_Model->ShowWindow(SW_SHOW);

}


void CMainProgramDlg::OnBnClickedButtonSetting()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	m_Set = new Setting;
	m_Set->Create(IDD_DIALOG_Setting);
	m_Set->m_L1_pos = m_L1_start_value;
	m_Set->m_T1_pos = m_T1_start_value;
	m_Set->m_LBW_pos = m_LBW_start_value;
	m_Set->m_RBW_pos = m_RBW_start_value;

	

	m_Set->ShowWindow(SW_SHOW);
}


void CMainProgramDlg::OnBnClickedButtonStart()
{
	CString model;
	m_MainModel.GetWindowTextA(model);

	// �� ������ �ȵƴٸ�
	if (model == "") {
		MessageBox(_T("�� ������ �ȵǾ����ϴ�."), _T("�˸�"), MB_OK);
	}
	// �̹��� �ε� ���̶��
	else if (m_pBitmapInfo == NULL) {
		MessageBox(_T("�̹����� �����ϴ�."), _T("�˸�"), MB_OK);
	}
	// �̹����� �ε� �ƴٸ�
	else {
		GetDlgItem(IDC_BUTTON_ORIGINAL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_L1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_T1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_LBW)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_RBW)->ShowWindow(SW_SHOW);

		// �˻� ���� (���)
		CalculateL1();
		CalculateT1();
		CalculateLBW();
		CalculateRBW();

		// �� ���� ��������
		int count;
		count = m_List.GetItemCount();

		// ��Ʈ��ȣ
		CString cntStr;
		cntStr.Format(_T("%d"), count + 1);

		m_List.InsertItem(count, cntStr);
		m_List.SetItemText(count, 1, m_EditDate + "-" + cntStr);
		m_List.SetItemText(count, 2, m_L1);
		m_List.SetItemText(count, 3, m_T1);
		m_List.SetItemText(count, 4, m_LBW);
		m_List.SetItemText(count, 5, m_RBW);
		m_List.SetItemText(count, 6, path.Right(9));
		m_List.SetItemText(count, 7, model);

		// ���� �˻�
		CalculateSize(count, model);

		SetDlgItemInt(IDC_EDIT_Count, count + 1);
	}
}


void CMainProgramDlg::OnBnClickedButtonModel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString model;
	m_MainModel.GetWindowTextA(model);

	// �� ������ �ȵƴٸ�
	if (model == "") {
		MessageBox(_T("�� ������ �ȵǾ����ϴ�."), _T("�˸�"), MB_OK);

	}
	else
	{
		m_Info = new Model_Info;
		m_Info->Create(IDD_Model_Info);
		m_Info->ShowWindow(SW_SHOW);
	}
}


void CMainProgramDlg::OnBnClickedButtonSave()
{
	if (m_List.GetItemCount() <= 0)
	{
		AfxMessageBox("��ȸ�� �����Ͱ� 0���̹Ƿ� ���� ���� �� �� �����ϴ�.");

		return;
	}

	CTime timeNow = CTime::GetCurrentTime();
	CString strDateTime;
	strDateTime = timeNow.Format(_T("%Y-%m-%d_%H%M%S"));
	CString strFileName;
	strFileName.Format("MLCC ���_%s", strDateTime);

	CFileDialog fdlg(FALSE, "xlsx", strFileName + ".xlsx", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR, "xlsx ���� (*.xlsx)|*.xlsx", NULL);

	if (fdlg.DoModal() != IDOK) return;

	CXLEzAutomation xls(FALSE);  // FALSE : ó�� ������ ȭ�鿡 ������ �ʴ´�.

	int rowOffset = 2;
	int colOffset = 0;

	int rowCount = m_List.GetItemCount();
	CHeaderCtrl* pHeaderCtrl = m_List.GetHeaderCtrl();
	int colCount = pHeaderCtrl->GetItemCount();
	CString strItemText;

	xls.SetCellValue(1, 1, "Lot Num");
	xls.SetCellValue(2, 1, "L1");
	xls.SetCellValue(3, 1, "T1");
	xls.SetCellValue(4, 1, "LBW");
	xls.SetCellValue(5, 1, "RBW");
	xls.SetCellValue(6, 1, "File Name");
	xls.SetCellValue(7, 1, "Model");

	for (int rowIdx = 0; rowIdx < rowCount; rowIdx++)
	{
		for (int colIdx = 0; colIdx < colCount; colIdx++)
		{
			strItemText = m_List.GetItemText(rowIdx, colIdx);

			// �÷� ������
			xls.SetCellValue(colIdx + colOffset, rowIdx + rowOffset, strItemText);
		}
	}

	xls.SaveFileAs(fdlg.GetPathName());
	xls.ReleaseExcel();
}


void CMainProgramDlg::OnBnClickedButtonExit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//Ŭ���� ��� �����ص� ��� ���� ������ ����
	OnOK();
}


void CMainProgramDlg::OnBnClickedButtonOriginal()
{
	// ���� �̹���
	DrawImage(m_Original_Img, IDC_ORIGINAL_VIEW);
}


void CMainProgramDlg::OnBnClickedButtonL1()
{
	// ���� ����
	CalculateL1();
	DrawImage(m_L1_Img, IDC_ORIGINAL_VIEW);
}


void CMainProgramDlg::OnBnClickedButtonT1()
{
	// ���� ����
	CalculateT1();
	DrawImage(m_T1_Img, IDC_ORIGINAL_VIEW);
}


void CMainProgramDlg::OnBnClickedButtonLbw()
{
	// �� ���� ����
	CalculateLBW();
	DrawImage(m_LBW_Img, IDC_ORIGINAL_VIEW);
}


void CMainProgramDlg::OnBnClickedButtonRbw()
{
	// �� ���� ����
	CalculateRBW();
	DrawImage(m_RBW_Img, IDC_ORIGINAL_VIEW);
}

void CMainProgramDlg::CalculateL1()
{
	// ���� ����
	Mat img_copy;
	m_Original_Img.copyTo(img_copy);

	// ��� ��ȯ
	Mat img_gray;
	cvtColor(m_Original_Img, img_gray, COLOR_BGR2GRAY);

	// ����ȭ
	Mat img_binary;
	threshold(img_gray, img_binary, m_L1_start_value, 255, THRESH_BINARY); // ��ü

	// �󺧸�
	Mat img_labels, stats, centroids;
	int numOfLabels = connectedComponentsWithStats(img_binary, img_labels, stats, centroids, 8, CV_32S);

	for (int j = 1; j < numOfLabels; j++)
	{
		// 1���� ��ü�� �ν��ϵ��� ����
		int area = stats.at<int>(j, CC_STAT_AREA);
		int left = stats.at<int>(j, CC_STAT_LEFT);
		int top = stats.at<int>(j, CC_STAT_TOP);
		int width = stats.at<int>(j, CC_STAT_WIDTH);
		int height = stats.at<int>(j, CC_STAT_HEIGHT);

		int x = centroids.at<double>(j, 0);	// �߽� x ��ǥ
		int y = centroids.at<double>(j, 1); // �߽� y ��ǥ

		// �ӽ� ���� (�� x ��ǥ)
		int tmp1, tmp2;
		int contrast = img_binary.at<uchar>(y, x); // x, y ��ǥ�� �ȼ���

		// ��� ���� ��
		while (true)
		{
			contrast = img_binary.at<uchar>(y, x);

			if (contrast == 0)
			{
				tmp1 = x;
				break;
			}
			x--;
		}

		x = centroids.at<double>(1, 0);	// �߽� x ��ǥ

		while (true)
		{
			contrast = img_binary.at<uchar>(y, x);

			if (contrast == 0)
			{
				tmp2 = x;
				break;
			}
			x++;
		}

		x = centroids.at<double>(1, 0);	// �߽� x ��ǥ

		if(area>1000)
		{
			// �׸��� �Լ�
			//circle(img_copy, Point(x, y), 5, Scalar(255, 0, 0), 1); // (��� �̹���, �߽���ǥ, ������, �׵θ� ��, �׵θ� ����)

			rectangle(img_copy, Point(left, top), Point(left + width, top + height), Scalar(0, 0, 255), 1); // (��� �̹���,���� ù x,y��ǥ,������ �Ʒ� �� x,y��ǥ, �׵θ� ��, �׵θ� ����)

			//putText(img_copy, to_string(1), Point(left + 20, top + 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2); // (��� �̹���, int j�� ���� ����, ���ʿ��� 20 ��ŭ ������ ���� ��ǥ, ��Ʈ, ��Ʈ ����, ����)

			line(img_copy, Point(left, y), Point(left + width, y), Scalar(0, 255, 0), 3, 8, 0);

			double a = 0.148971317023515;
			double result = (double)width*a;
			// ���� ����
			m_L1.Format(_T("%0.3f"), result);
		}
	}
	// ���� ���� �̹���
	m_L1_Img = img_copy;
}

void CMainProgramDlg::CalculateT1()
{
	// ���� ����

	Mat img_copy;
	m_Original_Img.copyTo(img_copy); // img�� img_copy�� ����

	// ��� ��ȯ
	Mat img_gray;
	cvtColor(m_Original_Img, img_gray, COLOR_BGR2GRAY);

	// ����ȭ
	Mat img_binary;
	threshold(img_gray, img_binary, m_T1_start_value, 255, THRESH_BINARY); // ��ü

	// ��� �̹��������� Canny Edge ���� (��輱 ����)
	Mat img_canny;
	Canny(img_binary, img_canny, 50, 100, 3); // �Է� �̹���, ���� �̹���, ���� �Ӱ谪, ���� �Ӱ谪
	// �ȼ��� ���� �Ӱ谪���� ū ���⸦ ������ �ȼ��� �����ڸ��� ����
	// ���� �Ӱ谪���� ���� ��� �����ڸ��� ������� ����

	// HoughTransform (Canny �̹��������� �����Ӽ��� �����ϸ� ���� lines�� ����)
	vector<Vec2f> houghLines;
	HoughLines(img_canny, houghLines, 1, CV_PI / 60, 55); // �Է� �̹���, �����Ӽ� ����(r, ��), r ���� ������, ȸ�����Ⱒ��, �ּ� �ȼ� ��
	// �ּ� �ȼ� ���� �ּ� ���� Ƚ��

	// img_hough �� img_lines�� ��輱 �����ֱ�
	for (size_t i = 0; i < houghLines.size(); i++)
	{
		float rho = houghLines[i][0], theta = houghLines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho; // x�� cos��Ÿ * x��ǥ, y�� sin��Ÿ * y��ǥ
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(img_copy, pt1, pt2, Scalar(0, 0, 255), 1, 8); // �Է� �̹���, ��ǥ��1, ��ǥ��2, ����, �β�, Ÿ��
	}

	// �ӽ�
	// �� ������ ������ �׸���
	Point pt1, pt2;

	// ù ��° ����
	float rho1 = houghLines[0][0], theta1 = houghLines[0][1];
	double a1 = cos(theta1), b1 = sin(theta1);
	double x1 = a1 * rho1, y1 = b1 * rho1; // x�� cos��Ÿ * x��ǥ, y�� sin��Ÿ * y��ǥ

	// �� ��° ����
	float rho2 = houghLines[1][0], theta2 = houghLines[1][1]; // x��ǥ, y��ǥ
	double a2 = cos(theta1), b2 = sin(theta2);
	double x2 = a2 * rho2, y2 = b2 * rho2; // x�� cos��Ÿ * x��ǥ, y�� sin��Ÿ * y��ǥ

	pt1.x = cvRound(x1 - 350 * (-b1));
	pt1.y = cvRound(y1 + 1000 * (a1));
	pt2.x = cvRound(x2 - 350 * (-b2));
	pt2.y = cvRound(y2 - 1000 * (a2));
	line(img_copy, pt1, pt2, Scalar(0, 255, 0), 3, 8); // �Է� �̹���, ��ǥ��1, ��ǥ��2, ����, �β�, Ÿ��

	double a = 0.15630746598014; //25mm = 0.15630746598014
	double result = (double)(abs(pt2.y - pt1.y))*a;
	// ���� ����
	m_T1.Format(_T("%0.3f"), result);

	// ���� ���� �̹���
	m_T1_Img = img_copy;
}

void CMainProgramDlg::CalculateLBW()
{
	Mat img_copy;
	m_Original_Img.copyTo(img_copy);

	Mat img_gray, img_binary;

	cvtColor(m_Original_Img, img_gray, COLOR_BGR2GRAY);
	threshold(img_gray, img_binary, m_LBW_start_value, 255, THRESH_BINARY); // (��� �̹���, ����ȭ �̹���, threshold ��, thresh_max��, thresh ����ȭ Ÿ��)
	// cvtColor(img_gray, img_copy, COLOR_GRAY2BGR);

	Mat img_labels, stats, centroids;
	int numOfLabels = connectedComponentsWithStats(img_binary, img_labels, stats, centroids, 8, CV_32S);

	// �󺧸� �� �̹����� ���� ���簢������ �ѷ��α�
	for (int j = 1; j < numOfLabels; j++)
	{
		int area = stats.at<int>(j, CC_STAT_AREA);
		int left = stats.at<int>(j, CC_STAT_LEFT);
		int top = stats.at<int>(j, CC_STAT_TOP);
		int width = stats.at<int>(j, CC_STAT_WIDTH);
		int height = stats.at<int>(j, CC_STAT_HEIGHT);

		int x = centroids.at<double>(j, 0);	// �߽���ǥ
		int y = centroids.at<double>(j, 1);

		if (area > 100)
		{
			if (x < 320) {
				// circle(img_copy, Point(x, y), 5, Scalar(255, 0, 0), 1); //(��� �̹���, �߽���ǥ,������, �׵θ� ��, �׵θ� ����)

				rectangle(img_copy, Point(left, top), Point(left + width, top + height), Scalar(0, 0, 255), 1); // (��� �̹���,���� ù x,y��ǥ,������ �Ʒ� �� x,y��ǥ, �׵θ� ��, �׵θ� ����)

				// putText(img_copy, to_string(j), Point(left + 20, top + 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2); //(��� �̹���, int j�� ���� ����, ���ʿ��� 20 ��ŭ ������ ���� ��ǥ, ��Ʈ, ��Ʈ ����, ����)

				line(img_copy, Point(left, y), Point(left + width, y), Scalar(0, 255, 0), 3, 8, 0);

				double a = 0.148971317023515;
				double result = (double)width * a;
				// �� ���� ����
				m_LBW.Format(_T("%0.3f"), result);
			}
		}
	}

	// �� ���� ���� �̹���
	
	m_LBW_Img = img_copy;
}

void CMainProgramDlg::CalculateRBW()
{
	Mat img_copy;
	m_Original_Img.copyTo(img_copy);

	Mat img_gray, img_binary;

	cvtColor(m_Original_Img, img_gray, COLOR_BGR2GRAY);
	threshold(img_gray, img_binary, m_RBW_start_value, 255, THRESH_BINARY); //(��� �̹���, ����ȭ �̹���, threshold ��, thresh_max��, thresh ����ȭ Ÿ��)
	// cvtColor(img_gray, img_copy, COLOR_GRAY2BGR);

	Mat img_labels, stats, centroids;
	int numOfLabels = connectedComponentsWithStats(img_binary, img_labels, stats, centroids, 8, CV_32S);

	// �󺧸� �� �̹����� ���� ���簢������ �ѷ��α�
	for (int j = 1; j < numOfLabels; j++)
	{
		int area = stats.at<int>(j, CC_STAT_AREA);
		int left = stats.at<int>(j, CC_STAT_LEFT);
		int top = stats.at<int>(j, CC_STAT_TOP);
		int width = stats.at<int>(j, CC_STAT_WIDTH);
		int height = stats.at<int>(j, CC_STAT_HEIGHT);

		int x = centroids.at<double>(j, 0);	// �߽���ǥ
		int y = centroids.at<double>(j, 1);

		if (area > 100)
		{
			if (x > 320) {
				// circle(img_copy, Point(x, y), 5, Scalar(255, 0, 0), 1); //(��� �̹���, �߽���ǥ,������, �׵θ� ��, �׵θ� ����)

				rectangle(img_copy, Point(left, top), Point(left + width, top + height), Scalar(0, 0, 255), 1); // (��� �̹���,���� ù x,y��ǥ,������ �Ʒ� �� x,y��ǥ, �׵θ� ��, �׵θ� ����)

				// putText(img_copy, to_string(j), Point(left + 20, top + 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2); //(��� �̹���, int j�� ���� ����, ���ʿ��� 20 ��ŭ ������ ���� ��ǥ, ��Ʈ, ��Ʈ ����, ����)

				line(img_copy, Point(left, y), Point(left + width, y), Scalar(0, 255, 0), 3, 8, 0);

				double a = 0.148971317023515;
				double result = (double)width * a;
				// �� ���� ����
				m_RBW.Format(_T("%0.3f"), result);
			}
		}
	}

	// �� ���� ���� �̹���
	m_RBW_Img = img_copy;
}

void CMainProgramDlg::OnBnClickedButtonResultClear()
{
	m_List.DeleteAllItems();
	SetDlgItemText(IDC_EDIT_Count, NULL);
	RedrawWindow();
}

void CMainProgramDlg::OnBnClickedButtonFilelistClear()
{
	m_ListBox.ResetContent();
		RedrawWindow();
}

void CMainProgramDlg::OnBnClickedButtonCheckAll()
{
	CString model;
	m_MainModel.GetWindowTextA(model);

	if (model == "") {
		MessageBox(_T("�� ������ �ȵǾ����ϴ�."), _T("�˸�"), MB_OK);
	}
	// �̹��� �ε� ���̶��
	else if (m_ListBox.GetCount() == 0) {
		MessageBox(_T("�̹����� �����ϴ�."), _T("�˸�"), MB_OK);
	}
	// �̹����� �ε� �ƴٸ�
	else {
		GetDlgItem(IDC_BUTTON_ORIGINAL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_L1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_T1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_LBW)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_RBW)->ShowWindow(SW_SHOW);

		for (int i = 0; i < m_ListBox.GetCount(); i++)
		{
			CString cStr;
			m_ListBox.GetText(i, cStr); // ���� ���õ� ���� ���ڿ��� cStr�� �����Ѵ�.

			if (path.Right(4) == ".tif")
			{
				TCHAR szTmp[256];
				StrCpy(szTmp, path);
				PathRemoveFileSpec(szTmp);
				path = szTmp;
			}

			path = path + "\\" + cStr + ".tif";

			CT2CA pszString(path);
			std::string strPath(pszString);

			m_Original_Img = imread(strPath);

			// �˻� ���� (���)
			CalculateL1();
			CalculateT1();
			CalculateLBW();
			CalculateRBW();

			// �� ���� ��������
			int count;
			count = m_List.GetItemCount();

			// ��Ʈ��ȣ
			CString cntStr;
			cntStr.Format(_T("%d"), count + 1);

			m_List.InsertItem(count, cntStr);
			m_List.SetItemText(count, 1, m_EditDate + "-" + cntStr);
			m_List.SetItemText(count, 2, m_L1);
			m_List.SetItemText(count, 3, m_T1);
			m_List.SetItemText(count, 4, m_LBW);
			m_List.SetItemText(count, 5, m_RBW);
			m_List.SetItemText(count, 6, path.Right(9));
			m_List.SetItemText(count, 7, model);

			// ���� �˻�
			CalculateSize(count, model);

			SetDlgItemInt(IDC_EDIT_Count, count + 1);
		}

		RedrawWindow();
	}
}

void CMainProgramDlg::OnLbnDblclkFileList()
{
	CString cStr;
	int index = m_ListBox.GetCurSel(); // ����Ʈ �ڽ����� ���� ���õ� ���� �ε����� �޾ƿ´�.
	m_ListBox.GetText(index, cStr); // ���� ���õ� ���� ���ڿ��� cStr�� �����Ѵ�.

	if (path.Right(4) == ".tif")
	{
		TCHAR szTmp[256];
		StrCpy(szTmp, path);
		PathRemoveFileSpec(szTmp);
		path = szTmp;
	}

	path = path + "\\" + cStr + ".tif";

	CT2CA pszString(path);
	std::string strPath(pszString);

	m_Original_Img = imread(strPath);

	RedrawWindow();

	DrawImage(m_Original_Img, IDC_ORIGINAL_VIEW);
}

void CMainProgramDlg::OnNMDblclkResultList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	if (pNMItemActivate->iItem != -1)
	{
		CString fileName = m_List.GetItemText(pNMItemActivate->iItem, 6);

		if (path.Right(4) == ".tif")
		{
			TCHAR szTmp[256];
			StrCpy(szTmp, path);
			PathRemoveFileSpec(szTmp);
			path = szTmp;
		}

		path = path + "\\" + fileName;

		CT2CA pszString(path);
		std::string strPath(pszString);

		m_Original_Img = imread(strPath);

		RedrawWindow();

		DrawImage(m_Original_Img, IDC_ORIGINAL_VIEW);
	}
}


void CMainProgramDlg::CalculateSize(int row, CString model)
{
	boolean error = false;

	// L1
	if (_ttof(m_L1) < 31 || _ttof(m_L1) > 33) {
		m_List.SetCellColor(RGB(255, 102, 102), row, 2);
		error = true;
	}
	else if (_ttof(m_L1) < 29 || _ttof(m_L1) > 35) {
		m_List.SetCellColor(RGB(255, 0, 0), row, 2);
		error = true;
	}

	// T1
	if (model == "3216") {
		if (_ttof(m_T1) < 15 || _ttof(m_T1) > 17) {
			m_List.SetCellColor(RGB(255, 102, 102), row, 3);
			error = true;
		}
		else if (_ttof(m_T1) < 13 || _ttof(m_T1) > 19) {
			m_List.SetCellColor(RGB(255, 0, 0), row, 3);
			error = true;
		}
	}
	else { // 3225
		if (_ttof(m_T1) < 24 || _ttof(m_T1) > 26) {
			m_List.SetCellColor(RGB(255, 102, 102), row, 3);
			error = true;
		}
		else if (_ttof(m_T1) < 22 || _ttof(m_T1) > 28) {
			m_List.SetCellColor(RGB(255, 0, 0), row, 3);
			error = true;
		}
	}

	// LBW
	if (model == "3216") {
		if (_ttof(m_LBW) < 5 || _ttof(m_LBW) > 7) {
			m_List.SetCellColor(RGB(255, 102, 102), row, 4);
			error = true;
		}
		else if (_ttof(m_LBW) < 3 || _ttof(m_LBW) > 9) {
			m_List.SetCellColor(RGB(255, 0, 0), row, 4);
			error = true;
		}
	}
	else { // 3225
		if (_ttof(m_LBW) < 6 || _ttof(m_LBW) > 8) {
			m_List.SetCellColor(RGB(255, 102, 102), row, 4);
			error = true;
		}
		else if (_ttof(m_LBW) < 3 || _ttof(m_LBW) > 9) {
			m_List.SetCellColor(RGB(255, 0, 0), row, 4);
			error = true;
		}
	}

	// RBW
	if (model == "3216") {
		if (_ttof(m_RBW) < 5 || _ttof(m_RBW) > 7) {
			m_List.SetCellColor(RGB(255, 102, 102), row, 5);
			error = true;
		}
		else if (_ttof(m_RBW) < 3 || _ttof(m_RBW) > 9) {
			m_List.SetCellColor(RGB(255, 0, 0), row, 5);
			error = true;
		}
	}
	else { // 3225
		if (_ttof(m_RBW) < 6 || _ttof(m_RBW) > 8) {
			m_List.SetCellColor(RGB(255, 102, 102), row, 5);
			error = true;
		}
		else if (_ttof(m_RBW) < 3 || _ttof(m_RBW) > 9) {
			m_List.SetCellColor(RGB(255, 0, 0), row, 5);
			error = true;
		}
	}

	if (error) {
		m_List.SetItemText(row, 1, m_List.GetItemText(row, 1) + "!");
	}
}
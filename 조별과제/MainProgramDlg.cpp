
// MainProgramDlg.cpp : 구현 파일
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

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CMainProgramDlg 대화 상자



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


// CMainProgramDlg 메시지 처리기

BOOL CMainProgramDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.
	
	//Back Draw

	//실행 시 날짜, 시간 editcontrol에 나오기 (폰트, 글자 크기, 배경 수정 필요)
	SetTimer(1,100,NULL);
	char DateText[100];
	
	SYSTEMTIME sT;
	GetLocalTime(&sT);
	//날짜 (년-월-일)
	sprintf(DateText, "%d-%d-%d", sT.wYear, sT.wMonth, sT.wDay);
	m_EditDate = DateText;
	
	//검사 모델(현재 오류)
	//m_MainModel = m_strModel;

	UpdateData(FALSE);

	// 항목 버튼 숨기기
	GetDlgItem(IDC_BUTTON_ORIGINAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_L1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_T1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_LBW)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_RBW)->ShowWindow(SW_HIDE);

	// 리스트 컨트롤의 크기를 얻어온다.
	CRect rect;
	m_List.GetClientRect(&rect);
	int width8 = rect.Width() / 8;

	m_List.InsertColumn(0, _T("순번"), LVCFMT_LEFT, width8);
	m_List.InsertColumn(1, _T("Lot Num"), LVCFMT_LEFT, width8);
	m_List.InsertColumn(2, _T("L1"), LVCFMT_LEFT, width8);
	m_List.InsertColumn(3, _T("T1"), LVCFMT_LEFT, width8);
	m_List.InsertColumn(4, _T("LBW"), LVCFMT_LEFT, width8);
	m_List.InsertColumn(5, _T("RBW"), LVCFMT_LEFT, width8);
	m_List.InsertColumn(6, _T("File Name"), LVCFMT_LEFT, width8);
	m_List.InsertColumn(7, _T("Model"), LVCFMT_LEFT, width8);

	//m_List.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

	//설정 다이얼로그
	m_L1_start_value = 80;
	m_T1_start_value = 50;
	m_RBW_start_value = 127;
	m_LBW_start_value = 127;

	//model dialog
	
	//SetDlgItemInt(IDC_EDIT_Main_Model, m_Num_model);

	// BITMAPINFO 초기화
	m_pBitmapInfo = NULL;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.

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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMainProgramDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
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

	// 모델 선택이 안됐다면
	if (model == "") {
		MessageBox(_T("모델 선택이 안되었습니다."), _T("알림"), MB_OK);
	}
	else {
		CString File, filem, strre;
		CString strFileList;
		int fileCnt;
		bool check = false;

		CFileDialog dlg(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT, "image file(*.jpg;*.bmp;*.png;*tif;)|*.jpg;*.bmp;*.png;*tif;|All Files(*.*)|*.*||", this);

		const int c_cMaxFiles = 20000 /*선택할 파일 숫자*/;
		// 메모리 부족현상으로 확장 안해주면 몇개 못씀
		const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
		dlg.GetOFN().lpstrFile = strFileList.GetBuffer(c_cbBuffSize);
		dlg.GetOFN().nMaxFile = c_cbBuffSize;

		if (dlg.DoModal() == IDOK)
		{
			path = dlg.GetPathName();
			for (POSITION pos = dlg.GetStartPosition(); pos != NULL;)
			{
				// 전체삭제는 ResetContent
				File = dlg.GetNextPathName(pos);

				filem = File.Right(File.GetLength() - File.ReverseFind(_T('\\')) - 1);
				// 경로를 제외한 파일명       

				filem = filem.Left(filem.GetLength() - 4);
				// 확장자 제거 ( ex - .jpg )

				if (m_ListBox.GetCount() == 0)
				{
					m_ListBox.AddString(filem);
				}
				else {
					for (int i = 0; i < m_ListBox.GetCount(); i++)
					{
						CString cStr;
						m_ListBox.GetText(i, cStr); // 현재 선택된 행의 문자열을 cStr에 저장한다.

						// 가져온 파일명이 리스트박스에 이미 존재하는 값과 중복된다면
						if (cStr == filem)
							check = true;
					}
					if (check)
					{
						// AfxMessageBox("중복 파일은 제외되었습니다.");
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
		strre.Format(_T("총 %d개의 이미지 로드 (중복 이미지 제외)"), fileCnt);
		AfxMessageBox(strre);
	}
}


void CMainProgramDlg::OnBnClickedButtonSelect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_Model = new Model;
	
	m_Model->Create(IDD_DIALOG_Model);
	m_Model->ShowWindow(SW_SHOW);

}


void CMainProgramDlg::OnBnClickedButtonSetting()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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

	// 모델 선택이 안됐다면
	if (model == "") {
		MessageBox(_T("모델 선택이 안되었습니다."), _T("알림"), MB_OK);
	}
	// 이미지 로드 전이라면
	else if (m_pBitmapInfo == NULL) {
		MessageBox(_T("이미지가 없습니다."), _T("알림"), MB_OK);
	}
	// 이미지가 로드 됐다면
	else {
		GetDlgItem(IDC_BUTTON_ORIGINAL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_L1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_T1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_LBW)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_RBW)->ShowWindow(SW_SHOW);

		// 검사 시작 (계산)
		CalculateL1();
		CalculateT1();
		CalculateLBW();
		CalculateRBW();

		// 열 개수 가져오기
		int count;
		count = m_List.GetItemCount();

		// 로트번호
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

		// 범위 검사
		CalculateSize(count, model);

		SetDlgItemInt(IDC_EDIT_Count, count + 1);
	}
}


void CMainProgramDlg::OnBnClickedButtonModel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString model;
	m_MainModel.GetWindowTextA(model);

	// 모델 선택이 안됐다면
	if (model == "") {
		MessageBox(_T("모델 선택이 안되었습니다."), _T("알림"), MB_OK);

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
		AfxMessageBox("조회된 데이터가 0건이므로 엑셀 저장 할 수 없습니다.");

		return;
	}

	CTime timeNow = CTime::GetCurrentTime();
	CString strDateTime;
	strDateTime = timeNow.Format(_T("%Y-%m-%d_%H%M%S"));
	CString strFileName;
	strFileName.Format("MLCC 기록_%s", strDateTime);

	CFileDialog fdlg(FALSE, "xlsx", strFileName + ".xlsx", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR, "xlsx 파일 (*.xlsx)|*.xlsx", NULL);

	if (fdlg.DoModal() != IDOK) return;

	CXLEzAutomation xls(FALSE);  // FALSE : 처리 과정을 화면에 보이지 않는다.

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

			// 컬럼 데이터
			xls.SetCellValue(colIdx + colOffset, rowIdx + rowOffset, strItemText);
		}
	}

	xls.SaveFileAs(fdlg.GetPathName());
	xls.ReleaseExcel();
}


void CMainProgramDlg::OnBnClickedButtonExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//클릭할 경우 기준해둔 밝기 설정 값으로 변동
	OnOK();
}


void CMainProgramDlg::OnBnClickedButtonOriginal()
{
	// 원본 이미지
	DrawImage(m_Original_Img, IDC_ORIGINAL_VIEW);
}


void CMainProgramDlg::OnBnClickedButtonL1()
{
	// 가로 길이
	CalculateL1();
	DrawImage(m_L1_Img, IDC_ORIGINAL_VIEW);
}


void CMainProgramDlg::OnBnClickedButtonT1()
{
	// 세로 길이
	CalculateT1();
	DrawImage(m_T1_Img, IDC_ORIGINAL_VIEW);
}


void CMainProgramDlg::OnBnClickedButtonLbw()
{
	// 좌 전극 길이
	CalculateLBW();
	DrawImage(m_LBW_Img, IDC_ORIGINAL_VIEW);
}


void CMainProgramDlg::OnBnClickedButtonRbw()
{
	// 우 전극 길이
	CalculateRBW();
	DrawImage(m_RBW_Img, IDC_ORIGINAL_VIEW);
}

void CMainProgramDlg::CalculateL1()
{
	// 가로 길이
	Mat img_copy;
	m_Original_Img.copyTo(img_copy);

	// 흑백 변환
	Mat img_gray;
	cvtColor(m_Original_Img, img_gray, COLOR_BGR2GRAY);

	// 이진화
	Mat img_binary;
	threshold(img_gray, img_binary, m_L1_start_value, 255, THRESH_BINARY); // 전체

	// 라벨링
	Mat img_labels, stats, centroids;
	int numOfLabels = connectedComponentsWithStats(img_binary, img_labels, stats, centroids, 8, CV_32S);

	for (int j = 1; j < numOfLabels; j++)
	{
		// 1개의 객체만 인식하도록 조정
		int area = stats.at<int>(j, CC_STAT_AREA);
		int left = stats.at<int>(j, CC_STAT_LEFT);
		int top = stats.at<int>(j, CC_STAT_TOP);
		int width = stats.at<int>(j, CC_STAT_WIDTH);
		int height = stats.at<int>(j, CC_STAT_HEIGHT);

		int x = centroids.at<double>(j, 0);	// 중심 x 좌표
		int y = centroids.at<double>(j, 1); // 중심 y 좌표

		// 임시 변수 (두 x 좌표)
		int tmp1, tmp2;
		int contrast = img_binary.at<uchar>(y, x); // x, y 좌표의 픽셀값

		// 명암 차이 비교
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

		x = centroids.at<double>(1, 0);	// 중심 x 좌표

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

		x = centroids.at<double>(1, 0);	// 중심 x 좌표

		if(area>1000)
		{
			// 그리기 함수
			//circle(img_copy, Point(x, y), 5, Scalar(255, 0, 0), 1); // (출력 이미지, 중심좌표, 반지름, 테두리 색, 테두리 굵기)

			rectangle(img_copy, Point(left, top), Point(left + width, top + height), Scalar(0, 0, 255), 1); // (출력 이미지,왼쪽 첫 x,y좌표,오른쪽 아래 끝 x,y좌표, 테두리 색, 테두리 굵기)

			//putText(img_copy, to_string(1), Point(left + 20, top + 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2); // (출력 이미지, int j의 숫자 저장, 왼쪽에서 20 만큼 떨어진 곳의 좌표, 폰트, 폰트 색깔, 굵기)

			line(img_copy, Point(left, y), Point(left + width, y), Scalar(0, 255, 0), 3, 8, 0);

			double a = 0.148971317023515;
			double result = (double)width*a;
			// 가로 길이
			m_L1.Format(_T("%0.3f"), result);
		}
	}
	// 가로 측정 이미지
	m_L1_Img = img_copy;
}

void CMainProgramDlg::CalculateT1()
{
	// 세로 길이

	Mat img_copy;
	m_Original_Img.copyTo(img_copy); // img를 img_copy에 복사

	// 흑백 변환
	Mat img_gray;
	cvtColor(m_Original_Img, img_gray, COLOR_BGR2GRAY);

	// 이진화
	Mat img_binary;
	threshold(img_gray, img_binary, m_T1_start_value, 255, THRESH_BINARY); // 전체

	// 흑백 이미지에서의 Canny Edge 검출 (경계선 검출)
	Mat img_canny;
	Canny(img_binary, img_canny, 50, 100, 3); // 입력 이미지, 저장 이미지, 낮은 임계값, 높은 임계값
	// 픽셀이 상위 임계값보다 큰 기울기를 가지면 픽셀을 가장자리로 간주
	// 하위 임계값보다 낮은 경우 가장자리로 고려하지 않음

	// HoughTransform (Canny 이미지에서의 직선속성을 검출하며 변수 lines에 저장)
	vector<Vec2f> houghLines;
	HoughLines(img_canny, houghLines, 1, CV_PI / 60, 55); // 입력 이미지, 직선속성 변수(r, θ), r 방향 변위값, 회전방향각도, 최소 픽셀 수
	// 최소 픽셀 수는 최소 교차 횟수

	// img_hough 및 img_lines에 경계선 더해주기
	for (size_t i = 0; i < houghLines.size(); i++)
	{
		float rho = houghLines[i][0], theta = houghLines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho; // x는 cos세타 * x좌표, y는 sin세타 * y좌표
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(img_copy, pt1, pt2, Scalar(0, 0, 255), 1, 8); // 입력 이미지, 좌표점1, 좌표점2, 색상, 두께, 타입
	}

	// 임시
	// 두 직선의 수직선 그리기
	Point pt1, pt2;

	// 첫 번째 직선
	float rho1 = houghLines[0][0], theta1 = houghLines[0][1];
	double a1 = cos(theta1), b1 = sin(theta1);
	double x1 = a1 * rho1, y1 = b1 * rho1; // x는 cos세타 * x좌표, y는 sin세타 * y좌표

	// 두 번째 직선
	float rho2 = houghLines[1][0], theta2 = houghLines[1][1]; // x좌표, y좌표
	double a2 = cos(theta1), b2 = sin(theta2);
	double x2 = a2 * rho2, y2 = b2 * rho2; // x는 cos세타 * x좌표, y는 sin세타 * y좌표

	pt1.x = cvRound(x1 - 350 * (-b1));
	pt1.y = cvRound(y1 + 1000 * (a1));
	pt2.x = cvRound(x2 - 350 * (-b2));
	pt2.y = cvRound(y2 - 1000 * (a2));
	line(img_copy, pt1, pt2, Scalar(0, 255, 0), 3, 8); // 입력 이미지, 좌표점1, 좌표점2, 색상, 두께, 타입

	double a = 0.15630746598014; //25mm = 0.15630746598014
	double result = (double)(abs(pt2.y - pt1.y))*a;
	// 세로 길이
	m_T1.Format(_T("%0.3f"), result);

	// 세로 측정 이미지
	m_T1_Img = img_copy;
}

void CMainProgramDlg::CalculateLBW()
{
	Mat img_copy;
	m_Original_Img.copyTo(img_copy);

	Mat img_gray, img_binary;

	cvtColor(m_Original_Img, img_gray, COLOR_BGR2GRAY);
	threshold(img_gray, img_binary, m_LBW_start_value, 255, THRESH_BINARY); // (흑백 이미지, 이진화 이미지, threshold 값, thresh_max값, thresh 이진화 타입)
	// cvtColor(img_gray, img_copy, COLOR_GRAY2BGR);

	Mat img_labels, stats, centroids;
	int numOfLabels = connectedComponentsWithStats(img_binary, img_labels, stats, centroids, 8, CV_32S);

	// 라벨링 된 이미지에 각각 직사각형으로 둘러싸기
	for (int j = 1; j < numOfLabels; j++)
	{
		int area = stats.at<int>(j, CC_STAT_AREA);
		int left = stats.at<int>(j, CC_STAT_LEFT);
		int top = stats.at<int>(j, CC_STAT_TOP);
		int width = stats.at<int>(j, CC_STAT_WIDTH);
		int height = stats.at<int>(j, CC_STAT_HEIGHT);

		int x = centroids.at<double>(j, 0);	// 중심좌표
		int y = centroids.at<double>(j, 1);

		if (area > 100)
		{
			if (x < 320) {
				// circle(img_copy, Point(x, y), 5, Scalar(255, 0, 0), 1); //(출력 이미지, 중심좌표,반지름, 테두리 색, 테두리 굵기)

				rectangle(img_copy, Point(left, top), Point(left + width, top + height), Scalar(0, 0, 255), 1); // (출력 이미지,왼쪽 첫 x,y좌표,오른쪽 아래 끝 x,y좌표, 테두리 색, 테두리 굵기)

				// putText(img_copy, to_string(j), Point(left + 20, top + 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2); //(출력 이미지, int j의 숫자 저장, 왼쪽에서 20 만큼 떨어진 곳의 좌표, 폰트, 폰트 색깔, 굵기)

				line(img_copy, Point(left, y), Point(left + width, y), Scalar(0, 255, 0), 3, 8, 0);

				double a = 0.148971317023515;
				double result = (double)width * a;
				// 좌 전극 길이
				m_LBW.Format(_T("%0.3f"), result);
			}
		}
	}

	// 좌 전극 측정 이미지
	
	m_LBW_Img = img_copy;
}

void CMainProgramDlg::CalculateRBW()
{
	Mat img_copy;
	m_Original_Img.copyTo(img_copy);

	Mat img_gray, img_binary;

	cvtColor(m_Original_Img, img_gray, COLOR_BGR2GRAY);
	threshold(img_gray, img_binary, m_RBW_start_value, 255, THRESH_BINARY); //(흑백 이미지, 이진화 이미지, threshold 값, thresh_max값, thresh 이진화 타입)
	// cvtColor(img_gray, img_copy, COLOR_GRAY2BGR);

	Mat img_labels, stats, centroids;
	int numOfLabels = connectedComponentsWithStats(img_binary, img_labels, stats, centroids, 8, CV_32S);

	// 라벨링 된 이미지에 각각 직사각형으로 둘러싸기
	for (int j = 1; j < numOfLabels; j++)
	{
		int area = stats.at<int>(j, CC_STAT_AREA);
		int left = stats.at<int>(j, CC_STAT_LEFT);
		int top = stats.at<int>(j, CC_STAT_TOP);
		int width = stats.at<int>(j, CC_STAT_WIDTH);
		int height = stats.at<int>(j, CC_STAT_HEIGHT);

		int x = centroids.at<double>(j, 0);	// 중심좌표
		int y = centroids.at<double>(j, 1);

		if (area > 100)
		{
			if (x > 320) {
				// circle(img_copy, Point(x, y), 5, Scalar(255, 0, 0), 1); //(출력 이미지, 중심좌표,반지름, 테두리 색, 테두리 굵기)

				rectangle(img_copy, Point(left, top), Point(left + width, top + height), Scalar(0, 0, 255), 1); // (출력 이미지,왼쪽 첫 x,y좌표,오른쪽 아래 끝 x,y좌표, 테두리 색, 테두리 굵기)

				// putText(img_copy, to_string(j), Point(left + 20, top + 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2); //(출력 이미지, int j의 숫자 저장, 왼쪽에서 20 만큼 떨어진 곳의 좌표, 폰트, 폰트 색깔, 굵기)

				line(img_copy, Point(left, y), Point(left + width, y), Scalar(0, 255, 0), 3, 8, 0);

				double a = 0.148971317023515;
				double result = (double)width * a;
				// 우 전극 길이
				m_RBW.Format(_T("%0.3f"), result);
			}
		}
	}

	// 우 전극 측정 이미지
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
		MessageBox(_T("모델 선택이 안되었습니다."), _T("알림"), MB_OK);
	}
	// 이미지 로드 전이라면
	else if (m_ListBox.GetCount() == 0) {
		MessageBox(_T("이미지가 없습니다."), _T("알림"), MB_OK);
	}
	// 이미지가 로드 됐다면
	else {
		GetDlgItem(IDC_BUTTON_ORIGINAL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_L1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_T1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_LBW)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_RBW)->ShowWindow(SW_SHOW);

		for (int i = 0; i < m_ListBox.GetCount(); i++)
		{
			CString cStr;
			m_ListBox.GetText(i, cStr); // 현재 선택된 행의 문자열을 cStr에 저장한다.

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

			// 검사 시작 (계산)
			CalculateL1();
			CalculateT1();
			CalculateLBW();
			CalculateRBW();

			// 열 개수 가져오기
			int count;
			count = m_List.GetItemCount();

			// 로트번호
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

			// 범위 검사
			CalculateSize(count, model);

			SetDlgItemInt(IDC_EDIT_Count, count + 1);
		}

		RedrawWindow();
	}
}

void CMainProgramDlg::OnLbnDblclkFileList()
{
	CString cStr;
	int index = m_ListBox.GetCurSel(); // 리스트 박스에서 현재 선택된 행의 인덱스를 받아온다.
	m_ListBox.GetText(index, cStr); // 현재 선택된 행의 문자열을 cStr에 저장한다.

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
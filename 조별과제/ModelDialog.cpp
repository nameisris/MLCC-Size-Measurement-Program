// ModelDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MainProgram.h"
#include "ModelDialog.h"
#include "afxdialogex.h"


// ModelDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(ModelDialog, CDialogEx)

ModelDialog::ModelDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_Model, pParent)
{

}

ModelDialog::~ModelDialog()
{
}

void ModelDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModelDialog, CDialogEx)
END_MESSAGE_MAP()


// ModelDialog 메시지 처리기입니다.

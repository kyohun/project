// ModifyMemInfoDialog.cpp: 구현 파일
//

#include "pch.h"
#include "도서 관리 프로그램.h"
#include "afxdialogex.h"
#include "ModifyMemInfoDialog.h"


// ModifyMemInfoDialog 대화 상자

IMPLEMENT_DYNAMIC(ModifyMemInfoDialog, CDialogEx)

ModifyMemInfoDialog::ModifyMemInfoDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MODMEMINFO, pParent)
{

}

ModifyMemInfoDialog::~ModifyMemInfoDialog()
{
}

void ModifyMemInfoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModifyMemInfoDialog, CDialogEx)
END_MESSAGE_MAP()


// ModifyMemInfoDialog 메시지 처리기

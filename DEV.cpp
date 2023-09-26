// DEV.cpp: 구현 파일
//

#include "pch.h"
#include "도서 관리 프로그램.h"
#include "afxdialogex.h"
#include "DEV.h"


// DEV 대화 상자

IMPLEMENT_DYNAMIC(DEV, CDialogEx)

DEV::DEV(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DEV, pParent)
{

}

DEV::~DEV()
{
}

void DEV::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DEV, CDialogEx)
END_MESSAGE_MAP()


// DEV 메시지 처리기

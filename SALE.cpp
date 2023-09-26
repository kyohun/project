// SALE.cpp: 구현 파일
//

#include "pch.h"
#include "도서 관리 프로그램.h"
#include "afxdialogex.h"
#include "SALE.h"


// SALE 대화 상자

IMPLEMENT_DYNAMIC(SALE, CDialogEx)

SALE::SALE(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SALE, pParent)
{

}

SALE::~SALE()
{
}

void SALE::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SALE, CDialogEx)
END_MESSAGE_MAP()


// SALE 메시지 처리기

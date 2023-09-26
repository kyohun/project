// SVCENTER.cpp: 구현 파일
//

#include "pch.h"
#include "도서 관리 프로그램.h"
#include "afxdialogex.h"
#include "SVCENTER.h"


// SVCENTER 대화 상자

IMPLEMENT_DYNAMIC(SVCENTER, CDialogEx)

SVCENTER::SVCENTER(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALO_SVCENTER, pParent)
{

}

SVCENTER::~SVCENTER()
{
}

void SVCENTER::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SVCENTER, CDialogEx)
END_MESSAGE_MAP()


// SVCENTER 메시지 처리기

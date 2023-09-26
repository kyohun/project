// CS.cpp: 구현 파일
//

#include "pch.h"
#include "도서 관리 프로그램.h"
#include "afxdialogex.h"
#include "CS.h"


// CS 대화 상자

IMPLEMENT_DYNAMIC(CS, CDialogEx)

CS::CS(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CS, pParent)
{

}

CS::~CS()
{
}

void CS::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CS, CDialogEx)
END_MESSAGE_MAP()


// CS 메시지 처리기

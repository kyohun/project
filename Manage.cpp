// Manage.cpp: 구현 파일
//

#include "pch.h"
#include "도서 관리 프로그램.h"
#include "afxdialogex.h"
#include "Manage.h"


// Manage 대화 상자

IMPLEMENT_DYNAMIC(Manage, CDialogEx)

Manage::Manage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MANAGE, pParent)
{

}

Manage::~Manage()
{
}

void Manage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Manage, CDialogEx)
END_MESSAGE_MAP()


// Manage 메시지 처리기

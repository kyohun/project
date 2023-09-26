// Product.cpp: 구현 파일
//

#include "pch.h"
#include "도서 관리 프로그램.h"
#include "afxdialogex.h"
#include "Product.h"


// Product 대화 상자

IMPLEMENT_DYNAMIC(Product, CDialogEx)

Product::Product(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PRODUCT, pParent)
{

}

Product::~Product()
{
}

void Product::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Product, CDialogEx)
END_MESSAGE_MAP()


// Product 메시지 처리기

// JobInfo.cpp: 구현 파일
//

#include "pch.h"
#include "도서 관리 프로그램.h"
#include "afxdialogex.h"
#include "JobInfo.h"
#include "DEV.h"
#include "Product.h"
#include "CS.h"
#include "SALE.h"
#include "Manage.h"


// JobInfo 대화 상자

IMPLEMENT_DYNAMIC(JobInfo, CDialogEx)

JobInfo::JobInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_JOB_INFO, pParent)
{

}

JobInfo::~JobInfo()
{
}

void JobInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(JobInfo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DEV, &JobInfo::OnBnClickedButtonDev)
	ON_BN_CLICKED(IDC_BUTTON_PRODUCT, &JobInfo::OnBnClickedButtonProduct)
	ON_BN_CLICKED(IDC_BUTTON_CS, &JobInfo::OnBnClickedButtonCs)
	ON_BN_CLICKED(IDC_BUTTON_SALE, &JobInfo::OnBnClickedButtonSale)
	ON_BN_CLICKED(IDC_BUTTON_MANAGE, &JobInfo::OnBnClickedButtonManage)
END_MESSAGE_MAP()


// JobInfo 메시지 처리기


void JobInfo::OnBnClickedButtonDev()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DEV* dv = new DEV();
	dv->Create(IDD_DIALOG_DEV);
	dv->ShowWindow(SW_SHOW);
}


void JobInfo::OnBnClickedButtonProduct()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Product* pr = new Product();
	pr->Create(IDD_DIALOG_PRODUCT);
	pr->ShowWindow(SW_SHOW);
}


void JobInfo::OnBnClickedButtonCs()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CS* cs = new CS();
	cs->Create(IDD_DIALOG_CS);
	cs->ShowWindow(SW_SHOW);
}


void JobInfo::OnBnClickedButtonSale()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SALE* sa = new SALE();
	sa->Create(IDD_DIALOG_SALE);
	sa->ShowWindow(SW_SHOW);
}


void JobInfo::OnBnClickedButtonManage()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Manage* mg = new Manage();
	mg->Create(IDD_DIALOG_MANAGE);
	mg->ShowWindow(SW_SHOW);
}

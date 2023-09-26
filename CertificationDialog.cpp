// CertificationDialog.cpp: 구현 파일
//


////////////////////////////////////////////////////////////////////

// CertificationDialog 메시지 처리기


#include "pch.h"
#include "도서 관리 프로그램.h"
#include "afxdialogex.h"
#include "CertificationDialog.h"
#include "BookManager.h"
#include <afxdb.h>
#include "DBControl.h"
#include "ModifyDialog.h"


// VerifyDilaog 대화 상자

IMPLEMENT_DYNAMIC(CertificationDialog, CDialogEx)

CertificationDialog::CertificationDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CERTIFICATION, pParent)

	, birth(_T(""))
{

}

CertificationDialog::~CertificationDialog()
{
}

void CertificationDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_BIRTH, birth);
	DDX_Control(pDX, IDC_COMBO_BNO, cbox_no);
}


BEGIN_MESSAGE_MAP(CertificationDialog, CDialogEx)
	
	ON_BN_CLICKED(BUTTON_CHECK, &CertificationDialog::OnBnClickedCheck)
	ON_CBN_SELCHANGE(IDC_COMBO_BNO, &CertificationDialog::OnCbnSelchangeComboBno)
END_MESSAGE_MAP()


// CertificationDialog 메시지 처리기


BOOL CertificationDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	DBControl* dbc = DBControl::GetInstance();


	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	BookManager& bm = BookManager::GetBookManager();
	bm.AddABEventHandler(this);//도서 추가하면 나한테 알려줘
	bm.AddRBEventHandler(this);//도서 삭제하면 나한테 알려줘
	NList* nlist = new NList();
	bm.GetBookNoList(nlist);
	NIter seek = nlist->begin();
	NIter end = nlist->end();
	wchar_t buf[256];
	for (; seek != end; ++seek)
	{
		wsprintf(buf, TEXT("%d"), (*seek));
		cbox_no.AddString(buf);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
void CertificationDialog::AddedBook(Book* book)
{
	wchar_t buf[256];
	wsprintf(buf, TEXT("%d"), book->GetNo());
	cbox_no.AddString(buf);

}

void CertificationDialog::OnCbnSelchangeComboBno()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = cbox_no.GetCurSel();
	if (index == -1)
	{
	//title = TEXT("");
	//	content = TEXT("");
	//	pubdate.SetDate(2023, 9, 20);
	}
	else
	{

		CString nos;
		cbox_no.GetLBText(index, nos);
		int bno = _wtoi(nos);
		BookManager& bm = BookManager::GetBookManager();
		Book* book = bm.GetBook(bno);
		if (book == 0)
		{
			throw "이런... 잘못 짰나봐. 빨리 버그 잡어라...";
		}
		//title = book->GetTitle();
		//content = book->GetContent();
		//pubdate = book->GetPubdate();
		/*CImage cimg;
		cimg.Load(book->GetImage());
		CDC* cdc = pbox_img.GetDC();
		RECT rt;
		pbox_img.GetClientRect(&rt);
		cimg.StretchBlt(*cdc, 0, 0, rt.right, rt.bottom, SRCCOPY);*/
	}
	UpdateData(0);//변수=>컨트롤

}


void CertificationDialog::RemovedBook(int bno)
{
	int cnt = cbox_no.GetCount();
	int bno2;
	CString nos;
	for (int i = 0; i < cnt; i++)
	{
		cbox_no.GetLBText(i, nos);
		bno2 = _wtoi(nos);
		if (bno == bno2)
		{
			cbox_no.DeleteString(i);
			return;
		}
	}

}

void CertificationDialog::OnBnClickedCheck()
{
	UpdateData(TRUE);

	int index = cbox_no.GetCurSel();
	CString nos;
	cbox_no.GetLBText(index, nos);
	int bno = _wtoi(nos);
	BookManager& bm = BookManager::GetBookManager();
	Book* book = bm.GetBook(bno);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (book->GetContent() == birth)
	{
		MessageBox(TEXT("본인인증을 성공하였습니다"));
		ModifyDialog* cd = new ModifyDialog();
		cd->Create(IDD_DIALOG_MODIFY);
		cd->ShowWindow(SW_SHOW);
	}
	else
	{
		MessageBox(TEXT("본인인증을 실패하였습니다"));
	}


}




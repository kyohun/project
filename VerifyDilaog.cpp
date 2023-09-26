// VerifyDilaog.cpp: 구현 파일
//

#include "pch.h"
#include "도서 관리 프로그램.h"
#include "afxdialogex.h"
#include "VerifyDilaog.h"
#include "BookManager.h"

// VerifyDilaog 대화 상자

IMPLEMENT_DYNAMIC(VerifyDilaog, CDialogEx)

VerifyDilaog::VerifyDilaog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CERTIFICATION, pParent)
	, title(_T(""))
	, content(_T(""))
	, pubdate(COleDateTime::GetCurrentTime())
	, paddr(_T(""))
{

}

VerifyDilaog::~VerifyDilaog()
{
}

void VerifyDilaog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_BNO, cbox_no);
	DDX_Text(pDX, IDC_EDIT_TITLE, title);
	DDX_Text(pDX, IDC_EDIT_CONTENT, content);
	DDX_Control(pDX, IDC_STATIC_IMG, pbox_img);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, pubdate);
	DDX_Text(pDX, IDC_EDIT_PADDR, paddr);
}


BEGIN_MESSAGE_MAP(VerifyDilaog, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_BNO, &VerifyDilaog::OnCbnSelchangeComboBno)
	
END_MESSAGE_MAP()


// VerifyDilaog 메시지 처리기


BOOL VerifyDilaog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	BookManager &bm = BookManager::GetBookManager();
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
void VerifyDilaog::AddedBook(Book* book)
{
	wchar_t buf[256];
	wsprintf(buf, TEXT("%d"), book->GetNo());
	cbox_no.AddString(buf);
}

void VerifyDilaog::OnCbnSelchangeComboBno()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = cbox_no.GetCurSel();
	if (index == -1)
	{
		title = TEXT("");
		content = TEXT("");
		pubdate.SetDate(2023, 9, 20);
	}
	else
	{
		CString nos;
		cbox_no.GetLBText(index, nos);
		int bno = _wtoi(nos);
		BookManager& bm = BookManager::GetBookManager();
		Book *book = bm.GetBook(bno);
		if (book == 0)
		{
			throw "이런... 잘못 짰나봐. 빨리 버그 잡어라...";
		}
		title = book->GetTitle();
		content = book->GetContent();
		paddr = book->GetPAddr();
		pubdate = book->GetPubdate();
		CImage cimg;
		cimg.Load(book->GetImage());
		CDC* cdc = pbox_img.GetDC();
		RECT rt;
		pbox_img.GetClientRect(&rt);
		cimg.StretchBlt(*cdc, 0, 0, rt.right, rt.bottom, SRCCOPY);
	}
	UpdateData(0);//변수=>컨트롤
}
void VerifyDilaog::RemovedBook(int bno)
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




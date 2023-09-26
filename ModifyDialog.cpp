// ModifyDialog.cpp: 구현 파일
//

#include "pch.h"
#include "도서 관리 프로그램.h"
#include "afxdialogex.h"
#include "ModifyDialog.h"
#include <afxdb.h>
#include "DBControl.h"


// ModifyDialog 대화 상자

IMPLEMENT_DYNAMIC(ModifyDialog, CDialogEx)

ModifyDialog::ModifyDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MODIFY, pParent)
	, pubdate(COleDateTime::GetCurrentTime())
	, content(_T(""))
	, paddr(_T(""))
{

}

ModifyDialog::~ModifyDialog()
{
}

void ModifyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_BOOK, list_book);
	DDX_Control(pDX, IDC_STATIC_IMG, pic_img);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, pubdate);
	DDX_Text(pDX, IDC_EDIT_CONTENT, content);
	//DDX_Text(pDX, IDC_EDIT_CONTENT, paddr);
	//DDX_Control(pDX, IDC_EDIT_PADDR, paddr);
	DDX_Text(pDX, IDC_EDIT_PADDR, paddr);
}


BEGIN_MESSAGE_MAP(ModifyDialog, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_BOOK, &ModifyDialog::OnLvnItemchangedListBook)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &ModifyDialog::OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_IMG, &ModifyDialog::OnBnClickedButtonImg)
	ON_BN_CLICKED(IDC_BUTTON_SUB, &ModifyDialog::OnBnClickedButtonSub)
END_MESSAGE_MAP()


// ModifyDialog 메시지 처리기
void ModifyDialog::AddedBook(Book* book)
{
	int bno = book->GetNo();
	CString title = book->GetTitle();
	wchar_t nbuf[256] = TEXT("");
	wsprintf(nbuf, TEXT("%d"), bno);
	int i = list_book.GetItemCount();
	list_book.InsertItem(i, nbuf);
	list_book.SetItemText(i, 1, title);
}
void ModifyDialog::RemovedBook(int bno)
{
	LVITEM li = { 0 };
	wchar_t buf[256] = TEXT("");
	int cnt = list_book.GetItemCount();
	for (int i = 0; i < cnt; i++)
	{
		li.iItem = i;
		li.iSubItem = 0;
		li.mask = LVIF_TEXT;
		li.pszText = buf;
		li.cchTextMax = 256;
		list_book.GetItem(&li);
		if (bno == _wtoi(buf))
		{
			list_book.DeleteItem(i);
			return;
		}
	}
}

BOOL ModifyDialog::OnInitDialog()
{
	__super::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	list_book.InsertColumn(0, TEXT("No"), 0, 50);
	list_book.InsertColumn(1, TEXT("성명"), 0, 80);
	list_book.InsertColumn(2, TEXT("생년월일"), 0, 80);
	BookManager& bm = BookManager::GetBookManager();
	//bm.AddABEventHandler(this);
	//bm.AddRBEventHandler(this);
	NList nlist;
	bm.GetBookNoList(&nlist);
	NIter seek = nlist.begin();
	NIter end = nlist.end();
	wchar_t nbuf[256]=TEXT("");
	Book* book = 0;
	for (int i=0; seek != end; ++seek,i++)
	{
		wsprintf(nbuf, TEXT("%d"), (*seek));
		list_book.InsertItem(i, nbuf);
		book = bm.GetBook(*seek);
		list_book.SetItemText(i, 1, book->GetTitle());
		list_book.SetItemText(i, 2, book->GetContent());
	}
	bm.AddABEventHandler(this);
	bm.AddRBEventHandler(this);
	//bm.AddMBEventHandler(this);//도서 변경하면 나한테 알려줘
	//bm.AddRegBEventHandler(this);//도서 등록하면 나한테 알려줘

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void ModifyDialog::OnLvnItemchangedListBook(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	OnBnClickedButtonCancel();
}


void ModifyDialog::OnBnClickedButtonCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos = list_book.GetFirstSelectedItemPosition();
	int index = list_book.GetNextSelectedItem(pos);
	if (index == -1)
	{
		return;
	}
	LVITEM li = { 0 };
	li.iItem = index;
	li.iSubItem = 0;
	wchar_t nbuf[256] = TEXT("");
	li.mask = LVIF_TEXT;
	li.pszText = nbuf;
	li.cchTextMax = 256;
	list_book.GetItem(&li);
	int no = _wtoi(nbuf);
	BookManager& bm = BookManager::GetBookManager();
	Book* book = bm.GetBook(no);
	//title = book->GetTitle();
	content = book->GetContent();//생년월일
	paddr = book->GetPAddr();//주소
	pubdate = book->GetPubdate();//제출일
	CImage cimg;
	image = book->GetImage();
	cimg.Load(image);
	CDC* cdc = pic_img.GetDC();
	RECT rt;
	pic_img.GetClientRect(&rt);
	cimg.StretchBlt(*cdc, 0, 0, rt.right, rt.bottom, SRCCOPY);
	UpdateData(0);
}


void ModifyDialog::OnBnClickedButtonImg()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog* fod = new CFileDialog(TRUE, 0);
	int re = fod->DoModal();
	if (re != IDOK)
	{
		return;
	}
	image = fod->GetPathName();
	CImage cimg;
	cimg.Load(image);

	CDC* cdc = pic_img.GetDC();
	RECT rt;
	pic_img.GetClientRect(&rt);
	cimg.StretchBlt(*cdc, 0, 0, rt.right, rt.bottom, SRCCOPY);
}


void ModifyDialog::OnBnClickedButtonSub()
{

	

	UpdateData();
	POSITION pos = list_book.GetFirstSelectedItemPosition();
	int index = list_book.GetNextSelectedItem(pos);
	if (index == -1)
	{
		return;
	}
	LVITEM li = { 0 };
	li.iItem = index;
	li.iSubItem = 0;
	wchar_t nbuf[256] = TEXT("");
	li.mask = LVIF_TEXT;
	li.pszText = nbuf;
	li.cchTextMax = 256;
	list_book.GetItem(&li);
	int no = _wtoi(nbuf);
	BookManager& bm = BookManager::GetBookManager();	
	bm.ModifyBook(no, content, paddr, image, pubdate);



}

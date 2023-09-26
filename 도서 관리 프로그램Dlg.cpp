
// 도서 관리 프로그램Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "도서 관리 프로그램.h"
#include "도서 관리 프로그램Dlg.h"
#include "afxdialogex.h"
#include <afxdb.h>
#include "DBControl.h"
#include "CertificationDialog.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

enum MY_W_MSG
{
	MWM_ENDED_REG = WM_APP + 1
};


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

//class CAboutDlg : public CDialogEx
//{
//public:
//	CAboutDlg();
//
//// 대화 상자 데이터입니다.
//#ifdef AFX_DESIGN_TIME
//	enum { IDD = IDD_ABOUTBOX };
//#endif
//
//	protected:
//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
//
//// 구현입니다.
//protected:
//	DECLARE_MESSAGE_MAP()
//};

//CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
//{
//}
//
//void CAboutDlg::DoDataExchange(CDataExchange* pDX)
//{
//	CDialogEx::DoDataExchange(pDX);
//}
//
//BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//END_MESSAGE_MAP()


// C도서관리프로그램Dlg 대화 상자



C도서관리프로그램Dlg::C도서관리프로그램Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MAIN, pParent)
	, pname(_T(""))
	, pprice(_T(""))
	, desc(_T(""))
	, pgender(_T(""))
	//, pphone(_T(""))
	//, peducation(_T(""))
	//, pintroduce(_T(""))
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C도서관리프로그램Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_BOOK, blist);
	DDX_Control(pDX, IDC_BUTTON_REMOVE, btn_remove);
	DDX_Control(pDX, IDC_BUTTON_MODIFY, btn_modify);
	DDX_Text(pDX, IDC_EDIT_PNAME, pname);
	DDX_Text(pDX, IDC_EDIT_PPRICE, pprice);
	DDX_Text(pDX, IDC_EDIT_DESC, desc);
	DDX_Text(pDX, IDC_EDIT_PGENDER, pgender);
	//DDX_Text(pDX, IDC_EDIT_PPHONE, pphone);
	//DDX_Text(pDX, IDC_EDIT_PEDUCATION, peducation);
	//DDX_Text(pDX, IDC_EDIT_PINTRODUCE, pintroduce);
}

BEGIN_MESSAGE_MAP(C도서관리프로그램Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_REG, &C도서관리프로그램Dlg::OnBnClickedButtonReg)
	ON_MESSAGE(MWM_ENDED_REG, &C도서관리프로그램Dlg::OnEndedReg)
	ON_BN_CLICKED(IDC_BUTTON_VERIFY, &C도서관리프로그램Dlg::OnBnClickedButtonVerify)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_BOOK, &C도서관리프로그램Dlg::OnLvnItemchangedListBook)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, &C도서관리프로그램Dlg::OnBnClickedButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &C도서관리프로그램Dlg::OnBnClickedButtonModify)

	ON_WM_DESTROY()
END_MESSAGE_MAP()


// C도서관리프로그램Dlg 메시지 처리기

BOOL C도서관리프로그램Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	//
	 //SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	//SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	DBControl *dbc = DBControl::GetInstance();
	///////////////////////////////////////////////////=>디비안불러와짐
	mrd = 0;
	BookManager& bm = BookManager::GetBookManager();
	//bm.AddABEventHandler(this);//도서 추가하면 나한테 알려줘
	//bm.AddMBEventHandler(this);//도서 변경하면 나한테 알려줘

	//LPWSTR texts[5] = { TEXT("번호"),TEXT("성명"),TEXT("생년월일"),TEXT("주소"),TEXT("성별") };
	//int widths[5] = { 50,80,80,80,80 };//{ 50,200,120 };
	//LV_COLUMN col;
	//col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	//col.fmt = LVCFMT_CENTER;
	//for (int i = 0; i < 5; i++)
	//{
	//	col.pszText = texts[i];
	//	col.iSubItem = i;
	//	col.cx = widths[i];
	//	blist.InsertColumn(i, col.pszText,0, col.cx);
	//}
	//bm.Load();
	//return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
	///////////////////////////////////////////////////

	////////////////////////////////////////////////////=>디비불러와짐
	blist.InsertColumn(0, TEXT("번호"), 0, 60);
	blist.InsertColumn(1, TEXT("성명"), 0, 80);//160
	blist.InsertColumn(2, TEXT("생년월일"), 0, 100);//120
	blist.InsertColumn(3, TEXT("주소"), 0, 100);//200
	blist.InsertColumn(4, TEXT("제출일"), 0, 80);//pgender


	//blist.InsertColumn(5, TEXT("휴대전화"), 0, 100);
	//blist.InsertColumn(6, TEXT("학력사항"), 0, 80);
	//blist.InsertColumn(7, TEXT("자기소개첨부"), 0, 80);
	

	//CDatabase db;
	//bool re = db.OpenEx(TEXT("DSN=Local;uid=scott;PWD=tiger"));
	//if (re == FALSE)
	//{
	//	return TRUE;
	//}


	CString pid;
	CRecordset *rs = dbc->Select();
	rs->Open(CRecordset::forwardOnly, TEXT("select*from Product"));
	int index = 0;
	while (!rs->IsEOF())
	{
		rs->GetFieldValue((short)0, pid);
		rs->GetFieldValue((short)1, pname);
		rs->GetFieldValue((short)2, pprice);
		rs->GetFieldValue((short)3, desc);
		rs->GetFieldValue((short)4, pgender);
		//rs->GetFieldValue((short)5, pphone);
		//rs->GetFieldValue((short)6, peducation);
		//rs->GetFieldValue((short)7, pintroduce);
		blist.InsertItem(index, pid);
		blist.SetItemText(index, 1, pname);
		blist.SetItemText(index, 2, pprice);
		blist.SetItemText(index, 3, desc);
		blist.SetItemText(index, 4, pgender);
		//blist.SetItemText(index, 5, pphone);
		//blist.SetItemText(index, 6, peducation);
		//blist.SetItemText(index, 7, pintroduce);

		rs->MoveNext();
		index++;
		//AddedBook
		//////////////////////////////////////////
		
	}
	bm.AddABEventHandler(this);//도서 추가하면 나한테 알려줘
	bm.AddMBEventHandler(this);//도서 변경하면 나한테 알려줘
	//bm.AddRegBEventHandler(this);//도서 등록하면 나한테 알려줘
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//mrd = 0;
	//BookManager& bm = BookManager::GetBookManager();
	//bm.AddABEventHandler(this);//도서 추가하면 나한테 알려줘
	//bm.AddMBEventHandler(this);//도서 변경하면 나한테 알려줘

	//LPWSTR texts[3] = { TEXT("No"),TEXT("제목"),TEXT("일자") };
	//int widths[3] = { 30,100,120 };//{ 50,200,120 };
	//LV_COLUMN col;
	//col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	//col.fmt = LVCFMT_CENTER;
	//for (int i = 0; i < 3; i++)
	//{
	//	col.pszText = texts[i];
	//	col.iSubItem = i;
	//	col.cx = widths[i];
	//	blist.InsertColumn(i, &col);
	//}
	//bm.Load();
	//return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

//void C도서관리프로그램Dlg::OnSysCommand(UINT nID, LPARAM lParam)
//{
//	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
//	{
//		CAboutDlg dlgAbout;
//		dlgAbout.DoModal();
//	}
//	else
//	{
//		CDialogEx::OnSysCommand(nID, lParam);
//	}
//}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

//void C도서관리프로그램Dlg::OnPaint()
//{
//	if (IsIconic())
//	{
//		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
//
//		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
//
//		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
//		int cxIcon = GetSystemMetrics(SM_CXICON);
//		int cyIcon = GetSystemMetrics(SM_CYICON);
//		CRect rect;
//		GetClientRect(&rect);
//		int x = (rect.Width() - cxIcon + 1) / 2;
//		int y = (rect.Height() - cyIcon + 1) / 2;
//
//		// 아이콘을 그립니다.
//		dc.DrawIcon(x, y, m_hIcon);
//	}
//	else
//	{
//		CDialogEx::OnPaint();
//	}
//}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
//HCURSOR C도서관리프로그램Dlg::OnQueryDragIcon()
//{
//	return static_cast<HCURSOR>(m_hIcon);
//}


void C도서관리프로그램Dlg::OnBnClickedButtonReg()
{// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//MessageBox(TEXT("제출이 완료되었습니다."));
	//UpdateData();
	//DBControl* dbc = DBControl::GetInstance();

	//CString pid;
	//wchar_t query_str[100] = TEXT("");
	//wsprintf(query_str, TEXT("insert into product values ('%s', %s,'%s','%s')"), pname, pprice, desc,pgender);
	//dbc->ExecuteQuery(query_str);

	//int index = blist.GetItemCount();

	//CRecordset* rs = dbc->Select();
	//rs->Open(CRecordset::forwardOnly, TEXT("select max(pid) from product"));
	//if (!rs->IsEOF())
	//{
	//	rs->GetFieldValue((short)0, pid);
	//	blist.InsertItem(index, pid);
	//	blist.SetItemText(index, 1, pname);
	//	blist.SetItemText(index, 2, pprice);
	//	blist.SetItemText(index, 3, desc);
	//	blist.SetItemText(index, 4, pgender);
	//	//blist.SetItemText(index, 5, pphone);
	//	//blist.SetItemText(index, 6, peducation);
	//	//blist.SetItemText(index, 7, pintroduce);
	//}
	//// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (mrd == 0)
	{
		mrd = new MyRegDialog();
		mrd->AddEndedEventHandler(this);//너 죽을 때 나한테 알려줘
		mrd->Create(IDD_DIALOG_REG, CWnd::GetDesktopWindow());
		mrd->ShowWindow(SW_SHOW);
	}

}
void C도서관리프로그램Dlg::EndedDialog()
{
	PostMessage(MWM_ENDED_REG, 0, 0);
}

LRESULT C도서관리프로그램Dlg::OnEndedReg(WPARAM, LPARAM)
{
	if (mrd == 0)
	{
		delete mrd;
	}
	mrd = 0;
	return 0;
}
//지원하기 화면 리스트에 등록하면 띄워지는 형태
void C도서관리프로그램Dlg::AddedBook(Book* book)
{
	int index = blist.GetItemCount();
	wchar_t nobuf[256];
	wsprintf(nobuf, TEXT("%d"), book->GetNo());
	blist.InsertItem(index, nobuf);

	blist.SetItemText(index, 1, book->GetTitle());
	blist.SetItemText(index, 2, book->GetContent());
	blist.SetItemText(index, 3, book->GetPAddr());
	
	COleDateTime dt = book->GetPubdate();
	wchar_t dtbuf[256];
	wsprintf(dtbuf, TEXT("%d%d%d"), dt.GetYear(), dt.GetMonth(), dt.GetDay());
	blist.SetItemText(index, 4, dtbuf);
	
}

void C도서관리프로그램Dlg::OnBnClickedButtonVerify()
{

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	VerifyDilaog* vd = new VerifyDilaog();
	//vd->DoModal();//모달 대화상자
	vd->Create(IDD_DIALOG_VERIFY);
	vd->ShowWindow(SW_SHOW);
}


void C도서관리프로그램Dlg::OnLvnItemchangedListBook(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	POSITION pos = blist.GetFirstSelectedItemPosition();
	int index = blist.GetNextSelectedItem(pos);
	bool flag = (index != -1);
	btn_remove.EnableWindow(flag);
	btn_modify.EnableWindow(flag);
	if (index == -1)
	{
		pname = TEXT("");
		pprice = TEXT("");
		desc = TEXT("");
		pgender = TEXT("");
		//pphone = TEXT("");
		//peducation = TEXT("");
		//pintroduce = TEXT("");
	}
	pname = blist.GetItemText(index, 1);
	pprice = blist.GetItemText(index, 2);
	desc = blist.GetItemText(index, 3);
	pgender = blist.GetItemText(index, 4);
	//pphone = blist.GetItemText(index, 5);
	//peducation = blist.GetItemText(index, 6);
	//pintroduce = blist.GetItemText(index, 7);
	UpdateData(0);
	if (blist.GetSelectedCount())
	{
		btn_remove.EnableWindow(TRUE);
	}
	else
	{
		btn_remove.EnableWindow(FALSE);
	}
}


void C도서관리프로그램Dlg::OnBnClickedButtonRemove()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DBControl* dbc = DBControl::GetInstance();

	//CDatabase db;
	//bool re = db.OpenEx(TEXT("DSN=Local;uid=scott;PWD=tiger"));
	//if (re == FALSE)
	//{
	//	return;
	//}
	POSITION pos = blist.GetFirstSelectedItemPosition();
	int index = blist.GetNextSelectedItem(pos);
	/*if (re == -1)
	{
		return;
	}*/
	CString pid = blist.GetItemText(index, 0);
	//CString pid;
	wchar_t query_str[100] = TEXT("");
	wsprintf(query_str, TEXT("delete from product where pid='%s'"), pid);
	//db.ExecuteSQL(query_str);
	dbc->ExecuteQuery(query_str);

	blist.DeleteItem(index);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BookManager& bm = BookManager::GetBookManager();
	/*POSITION pos = blist.GetFirstSelectedItemPosition();
	int index = blist.GetNextSelectedItem(pos);*/
	if (index == -1)
	{
		return;
	}
	LVITEM li = { 0 };
	li.iItem = index;
	li.iSubItem = 0;
	wchar_t buf[256] = TEXT("");
	li.mask = LVIF_TEXT;
	li.pszText = buf;
	li.cchTextMax = 256;//버퍼 크기
	blist.GetItem(&li);
	int bno = _wtoi(buf);
	if (bm.RemoveBook(bno))
	{
		blist.DeleteItem(index);
	}


}


void C도서관리프로그램Dlg::OnBnClickedButtonModify()
{
	CertificationDialog* cd = new CertificationDialog();
	cd->Create(IDD_DIALOG_CERTIFICATION);
	cd->ShowWindow(SW_SHOW);
	//CertificationDialog* cd = new CertificationDialog();
	//cd->Create(IDD_DIALOG_CERTIFICATION);
	//cd->ShowWindow(SW_SHOW);


//////////////////////////////////////////////////////////////////////////////////////////
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	DBControl* dbc = DBControl::GetInstance();


	//CDatabase db;
	//bool re = db.OpenEx(TEXT("DSN=Local;uid=scott;PWD=tiger"));
	//if (re == FALSE)
	//{
	//	return;
	//}
	POSITION pos = blist.GetFirstSelectedItemPosition();
	int index = blist.GetNextSelectedItem(pos);
	//if (re == -1)
	//{
	//	return;
	//}
	


	CString pid = blist.GetItemText(index, 0);
	wchar_t query_str[100] = TEXT("");
	wsprintf(query_str, TEXT("update product set pname='%s', pprice='%s',description='%s',pgender='%s' where pid='%s'"), pname, pprice, desc,pgender, pid);
	////db.ExecuteSQL(query_str);
	dbc->ExecuteQuery(query_str);

	blist.SetItemText(index, 1, pname);
	blist.SetItemText(index, 2, pprice);
	blist.SetItemText(index, 3, desc);
	blist.SetItemText(index, 4, pgender);
	 
	//////////////////////////////////////////////////////////////////////////
	//blist.SetItemText(index, 5, pphone);
	//blist.SetItemText(index, 6, peducation);
	//blist.SetItemText(index, 7, pintroduce);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	
	//ModifyDialog* md = new ModifyDialog();
	//md->Create(IDD_DIALOG_MODIFY);
	//md->ShowWindow(SW_SHOW);



	//====================================================================
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//UpdateData();

	//DBControl* dbc = DBControl::GetInstance();
	////CDatabase db;
	////bool re = db.OpenEx(TEXT("DSN=Local;uid=scott;PWD=tiger"));
	////if (re == FALSE)
	////{
	////	return;
	////}
	//POSITION pos = blist.GetFirstSelectedItemPosition();
	//int index = blist.GetNextSelectedItem(pos);
	////if (re == -1)
	////{
	////	return;
	////}
	////CString pid = blist.GetItemText(index, 0);
	//CString pid;
	//wchar_t query_str[100] = TEXT("");
	//wsprintf(query_str, TEXT("update product set pname='%s', pprice=%s,description='%s' where pid='%s'"), pname, pprice, desc, pid);
	//dbc->ExecuteQuery(query_str);
	////db.ExecuteSQL(query_str);
	//blist.SetItemText(index, 1, pname);
	//blist.SetItemText(index, 2, pprice);
	//blist.SetItemText(index, 3, desc);
	//// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//ModifyDialog* md = new ModifyDialog();
	//md->Create(IDD_DIALOG_MODIFY);
	//md->ShowWindow(SW_SHOW);

	///*FindInfoDialog* fd = new FindInfoDialog();
	//fd->Create(IDD_FINDINFO);
	//fd->ShowWindow(SW_SHOW);*/
}

void C도서관리프로그램Dlg::ModifiedBook(Book* book)
{

	//DBControl* dbc = DBControl::GetInstance();
	/////////////////////////////////////////////////////=>디비안불러와짐

	/*BookManager& bm = BookManager::GetBookManager();*/
	int bno = book->GetNo();
	LVITEM li = { 0 };
	wchar_t buf[256] = TEXT("");
	int cnt = blist.GetItemCount();
	COleDateTime dt;
	wchar_t dtbuf[256] = TEXT("");
	for (int i = 0; i < cnt; i++)
	{
		li.iItem = i;
		li.iSubItem = 0;
		li.mask = LVIF_TEXT;
		li.pszText = buf;
		li.cchTextMax = 256;
		blist.GetItem(&li);
		if (bno == _wtoi(buf))
		{
			blist.SetItemText(i, 1, book->GetTitle());//성명
			blist.SetItemText(i, 2, book->GetContent());//생년월일
			blist.SetItemText(i, 3, book->GetPAddr());//주소
			dt = book->GetPubdate();//제출일
			wsprintf(dtbuf, TEXT("%d%d%d"), dt.GetYear(), dt.GetMonth(), dt.GetDay());
			blist.SetItemText(i, 4, dtbuf);
			//bm.AddABEventHandler(this);//도서 추가하면 나한테 알려줘
			//bm.AddMBEventHandler(this);//도서 변경하면 나한테 알려줘
			//bm.AddRegBEventHandler(this);//도서 등록하면 나한테 알려줘
			/*return TRUE;  */// 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
			return;
		}
	}
}

BOOL C도서관리프로그램Dlg::DestroyWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	BookManager& bm = BookManager::GetBookManager();
	bm.Save();
	return __super::DestroyWindow();
}



void C도서관리프로그램Dlg::OnDestroy()
{
	__super::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	DBControl* dbc = DBControl::GetInstance();
	dbc->Close();

}

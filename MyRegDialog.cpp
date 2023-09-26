// MyRegDialog.cpp: 구현 파일
//

#include "pch.h"
#include "도서 관리 프로그램.h"

#include "afxdialogex.h"
#include "MyRegDialog.h"
#include "BookManager.h"
#include <afxdb.h>
#include "DBControl.h"

// MyRegDialog 대화 상자

IMPLEMENT_DYNAMIC(MyRegDialog, CDialogEx)

MyRegDialog::MyRegDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_REG, pParent)	
	, title(_T(""))
	, content(_T(""))
	, bno(0)
	, date1(COleDateTime::GetCurrentTime())
	, date2(COleDateTime::GetCurrentTime())
	, paddr(_T(""))
{
	eeh = 0;
}

MyRegDialog::~MyRegDialog()
{
}

void MyRegDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, dtp);
	DDX_Control(pDX, IDC_MONTHCALENDAR1, mc);
	DDX_Text(pDX, IDC_EDIT_TITLE, title);
	DDX_Text(pDX, IDC_EDIT_CONTENT, content);
	DDX_Text(pDX, IDC_STATIC_BNO, bno);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, date1);
	DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR1, date2);
	DDX_Control(pDX, IDC_STATIC_IMG, pic_con);
	DDX_Text(pDX, IDC_EDIT_PADDR, paddr);
}


BEGIN_MESSAGE_MAP(MyRegDialog, CDialogEx)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &MyRegDialog::OnDtnDatetimechangeDatetimepicker1)
	ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR1, &MyRegDialog::OnMcnSelchangeMonthcalendar1)
	ON_BN_CLICKED(IDC_BUTTON_IMG, &MyRegDialog::OnBnClickedButtonImg)
	ON_BN_CLICKED(IDC_BUTTON_SUB, &MyRegDialog::OnBnClickedButtonSub)
	//ON_EN_CHANGE(IDC_EDIT_CONTENT, &MyRegDialog::OnEnChangeEditContent)
	
END_MESSAGE_MAP()


// MyRegDialog 메시지 처리기
void MyRegDialog::AddEndedEventHandler(EndDialogEventHandler* eeh)
{
	this->eeh = eeh;
}

void MyRegDialog::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (eeh)
	{
		eeh->EndedDialog();//나 죽음을 통보한다.
	}
	CDialogEx::OnCancel();
}


void MyRegDialog::OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	UpdateData();
	mc.SetCurSel(date1);
}


void MyRegDialog::OnMcnSelchangeMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	UpdateData();
	dtp.SetTime(date2);
}


void MyRegDialog::OnBnClickedButtonImg()
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
	
	CDC *cdc = pic_con.GetDC();
	RECT rt;
	pic_con.GetClientRect(&rt);
	cimg.StretchBlt(*cdc, 0, 0, rt.right, rt.bottom, SRCCOPY);
}


void MyRegDialog::OnBnClickedButtonSub()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		//MessageBox(TEXT("제출이 완료되었습니다."));
		UpdateData();
		DBControl* dbc = DBControl::GetInstance();

		CString pid;
		wchar_t query_str[100] = TEXT("");
		//지원하기 화면 리스트에 디비에 저장되는 형태
	
		wsprintf(query_str, TEXT("insert into product values ('%s', '%s','%s','%s')"), title, content, paddr, date1);
		dbc->ExecuteQuery(query_str);

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
		//if (mrd == 0)
		//{
		//	mrd = new MyRegDialog();
		//	mrd->AddEndedEventHandler(this);//너 죽을 때 나한테 알려줘
		//	mrd->Create(IDD_DIALOG_REG, CWnd::GetDesktopWindow());
		//	mrd->ShowWindow(SW_SHOW);
		//}

	



	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();//컨트롤=>변수
	if (image == TEXT(""))
	{
		image = TEXT("noimage.bmp");
	}
	BookManager& bm = BookManager::GetBookManager();
	if (bm.AddBook(title, content,paddr, image, date1) == FALSE)
	{
		MessageBox(TEXT("추가 실패"));	
	}

	
	InitControls();
}
void MyRegDialog::InitControls()
{
	title = TEXT("");
	content = TEXT("");
	paddr = TEXT("");
	image = TEXT("");
	UpdateData(FALSE);//변수=>컨트롤
	BookManager& bm = BookManager::GetBookManager();
	int bno = bm.GetNextBookNo();
	SetDlgItemInt(IDC_STATIC_BNO, bno, FALSE);
	////////////////////////////////////////////////////



}

BOOL MyRegDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	BookManager& bm = BookManager::GetBookManager();
	int bno = bm.GetNextBookNo();
	SetDlgItemInt(IDC_STATIC_BNO, bno, FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


//void MyRegDialog::OnEnChangeEditContent()
//{
//	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
//	// CDialogEx::OnInitDialog() 함수를 재지정 
//	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
//	// 이 알림 메시지를 보내지 않습니다.
//
//	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
//}



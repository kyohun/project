// LoginPageDialog.cpp: 구현 파일
//

#include "pch.h"
#include "도서 관리 프로그램.h"
#include "afxdialogex.h"
#include "LoginPageDialog.h"
#include <afxdb.h>

enum MY_W_MSG
{
	MWM_ENDED_REG = WM_APP + 1
};

// LoginPageDialog 대화 상자

IMPLEMENT_DYNAMIC(LoginPageDialog, CDialogEx)

LoginPageDialog::LoginPageDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOGINPAGE, pParent)
	, loginpage_message(_T(""))
{

}

LoginPageDialog::~LoginPageDialog()
{
}

void LoginPageDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MEMINFO, mem_list);
	DDX_Control(pDX, IDC_BUTTON_MODMEMINFO, mod_button);
	DDX_Control(pDX, IDC_BUTTON_DELMEMINFO, del_button);
	DDX_Control(pDX, IDC_BUTTON_SIGNIN, signin_button);
	DDX_Text(pDX, IDC_STATIC_LOGINPAGE, loginpage_message);
	DDX_Control(pDX, IDC_BUTTON_SIGNOUT, signout_button);
}


BEGIN_MESSAGE_MAP(LoginPageDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SIGNIN, &LoginPageDialog::OnBnClickedButtonSignin)
	ON_MESSAGE(MWM_ENDED_REG, &LoginPageDialog::OnEndedSignin)
	ON_BN_CLICKED(IDC_BUTTON_SIGNUP, &LoginPageDialog::OnBnClickedButtonSignup)
	ON_BN_CLICKED(IDC_BUTTON_MODMEMINFO, &LoginPageDialog::OnBnClickedButtonModmeminfo)
	ON_BN_CLICKED(IDC_BUTTON_DELMEMINFO, &LoginPageDialog::OnBnClickedButtonDelmeminfo)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_MEMINFO, &LoginPageDialog::OnLvnItemchangedListMeminfo)
	ON_BN_CLICKED(IDC_BUTTON_SIGNOUT, &LoginPageDialog::OnBnClickedButtonSignout)
END_MESSAGE_MAP()


// LoginPageDialog 메시지 처리기

BOOL LoginPageDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	sid = 0;
	AccountManager& am = AccountManager::GetAccountManager();
	am.AddABEventHandler(this);//계정 추가하면 나한테 알려주세요.
	am.AddMBEventHandler(this);//계정 변경하면 나한테 알려주세요.
	am.AddRBEventHandler(this);//계정 삭제하면 나한테 알려주세요.

	LPWSTR texts[4] = { TEXT("EMAIL"),TEXT("이름"),TEXT("생년월일"),TEXT("전화번호") };
	int widths[4] = { 200,50,100,100 };
	LV_COLUMN col;
	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_CENTER;
	for (int i = 0; i < 4; i++)
	{
		col.pszText = texts[i];
		col.iSubItem = i;
		col.cx = widths[i];
		mem_list.InsertColumn(i, &col);
	}
	if (am.GetAccount(0) == 0)
	{
		SetDlgItemText(IDC_STATIC_LOGINPAGE, TEXT("로그인해주세요"));
		GetDlgItem(IDC_LIST_MEMINFO)->ShowWindow(0);//0은 안보이게 1은 보이게
		GetDlgItem(IDC_BUTTON_SIGNOUT)->ShowWindow(0);//0은 안보이게 1은 보이게
	}
	else
	{
		Account* account = am.GetAccount(0);
		CString strText;
		strText.Format(_T("%s님 안녕하세요"), account->GetAccName());
		SetDlgItemText(IDC_STATIC_LOGINPAGE, strText);
		mem_list.InsertItem(0, account->GetAccEmail());
		mem_list.SetItemText(0, 1, account->GetAccName());
		COleDateTime dt = account->GetAccBirthdate();
		wchar_t dtbuf[256];
		wsprintf(dtbuf, TEXT("%d년 %d월 %d일"), dt.GetYear(), dt.GetMonth(), dt.GetDay());
		mem_list.SetItemText(0, 2, dtbuf);
		mem_list.SetItemText(0, 3, account->GetAccPhone());
		//리스트 보이게
		GetDlgItem(IDC_LIST_MEMINFO)->ShowWindow(1);//0은 안보이게 1은 보이게
		//로그인 버튼 보이게
		GetDlgItem(IDC_BUTTON_SIGNOUT)->ShowWindow(1);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//버튼 눌러서 다른 다이얼로그로
void LoginPageDialog::OnBnClickedButtonSignin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (sid == 0)
	{
		sid = new SignInDialog();
		sid->AddEndedEventHandler(this);//너 죽을 때 나한테 알려줘
		sid->Create(IDD_DIALOG_SIGNIN, CWnd::GetDesktopWindow());
		sid->ShowWindow(SW_SHOW);
	}
}
void LoginPageDialog::OnBnClickedButtonSignup()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SignUpDialog* sud = new SignUpDialog();

	sud->Create(IDD_DIALOG_SIGNUP);
	sud->ShowWindow(SW_SHOW);
}
void LoginPageDialog::OnBnClickedButtonModmeminfo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ModifyMemInfoDialog* mid = new ModifyMemInfoDialog();

	mid->Create(IDD_DIALOG_MODMEMINFO);
	mid->ShowWindow(SW_SHOW);
}

void LoginPageDialog::OnBnClickedButtonDelmeminfo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDatabase db;
	bool re = db.OpenEx(TEXT("DSN=LocalSQL;uid=scott;PWD=tiger"));
	if (re == FALSE)
	{
		return;
	}
	POSITION pos = mem_list.GetFirstSelectedItemPosition();
	int index = mem_list.GetNextSelectedItem(pos);
	if (index == -1)
	{
		return;
	}

	CString myemail = mem_list.GetItemText(0, 0);
	wchar_t query_str[100] = TEXT("");
	wsprintf(query_str, TEXT("delete from accounttest where acc_email='%s'"), myemail);
	db.ExecuteSQL(query_str);
	mem_list.DeleteItem(0);

	OnInitDialog();
}
LRESULT LoginPageDialog::OnEndedSignin(WPARAM, LPARAM)
{
	if (sid == 0)
	{
		delete sid;
	}
	sid = 0;
	return 0;
}

void LoginPageDialog::AddedAccount(Account* account)
{
	/*wchar_t emailbuf[256];
	wsprintf(emailbuf, TEXT("%s"), account->GetAccEmail());*/
	mem_list.InsertItem(0, account->GetAccEmail());
	mem_list.SetItemText(0, 1, account->GetAccName());
	COleDateTime dt = account->GetAccBirthdate();
	wchar_t dtbuf[256];
	wsprintf(dtbuf, TEXT("%d년 %d월 %d일"), dt.GetYear(), dt.GetMonth(), dt.GetDay());
	mem_list.SetItemText(0, 2, dtbuf);
	mem_list.SetItemText(0, 3, account->GetAccPhone());
	//리스트 보이게
	GetDlgItem(IDC_LIST_MEMINFO)->ShowWindow(1);//0은 안보이게 1은 보이게
	//로그인 버튼 보이게
	GetDlgItem(IDC_BUTTON_SIGNOUT)->ShowWindow(1);
	///
	CString strText;
	strText.Format(_T("%s님 안녕하세요"), account->GetAccName());
	SetDlgItemText(IDC_STATIC_LOGINPAGE, strText);

}
void LoginPageDialog::ModifiedAccount(Account* account)
{
	mem_list.InsertItem(0, account->GetAccEmail());
	mem_list.SetItemText(0, 1, account->GetAccName());
	COleDateTime dt = account->GetAccBirthdate();
	wchar_t dtbuf[256];
	wsprintf(dtbuf, TEXT("%d년 %d월 %d일"), dt.GetYear(), dt.GetMonth(), dt.GetDay());
	mem_list.SetItemText(0, 2, dtbuf);
	mem_list.SetItemText(0, 3, account->GetAccPhone());
}
void  LoginPageDialog::RemovedAccount(int bno)
{
	POSITION pos = mem_list.GetFirstSelectedItemPosition();
	int index = mem_list.GetNextSelectedItem(pos);
	if (index == -1)
	{
		return;
	}

	CString myemail = mem_list.GetItemText(0, 0);

	mem_list.DeleteItem(0);

	signin_button.EnableWindow(TRUE);
}

void LoginPageDialog::EndedDialog()
{
	PostMessage(MWM_ENDED_REG, 0, 0);
}
void LoginPageDialog::OnLvnItemchangedListMeminfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	if (mem_list.GetSelectedCount())
	{
		del_button.EnableWindow(TRUE);
		mod_button.EnableWindow(TRUE);
		signout_button.EnableWindow(TRUE);

	}
	else
	{
		del_button.EnableWindow(FALSE);
		mod_button.EnableWindow(FALSE);
		signout_button.EnableWindow(FALSE);
	}
}


void LoginPageDialog::OnBnClickedButtonSignout()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	AccountManager& am = AccountManager::GetAccountManager();
	if (am.RemoveAccount(0) == TRUE)
	{
		MessageBox(TEXT("로그아웃 성공"));
		OnInitDialog();
	}
	else
	{
		MessageBox(TEXT("로그아웃 실패"));
	}
}

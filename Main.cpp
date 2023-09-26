// Main.cpp: 구현 파일
//

#include "pch.h"
#include "도서 관리 프로그램.h"
#include "afxdialogex.h"
#include "Main.h"
#include "framework.h"
#include "도서 관리 프로그램Dlg.h"
#include "JobInfo.h"
#include "SVCENTER.h"
#include "LoginPageDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

enum MY_W_MSG
{
	MWM_ENDED_REG = WM_APP + 1
};


// Main 대화 상자

//IMPLEMENT_DYNAMIC(Main, CDialogEx)
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	//virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void Main::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

//


Main::Main(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAIN, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	mrr = nullptr;
}

BEGIN_MESSAGE_MAP(Main, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_BUTTON_JOB_APPLICATION, &Main::OnBnClickedButtonJobApplication)
	ON_BN_CLICKED(IDC_BUTTON_JOB_INFO, &Main::OnBnClickedButtonJobInfo)
	ON_BN_CLICKED(IDC_BUTTON_MEMBERSHIP, &Main::OnBnClickedButtonMembership)
	ON_BN_CLICKED(IDC_BUTTON_LOGINPAGE, &Main::OnBnClickedButtonLoginpage)
END_MESSAGE_MAP()



// Main 메시지 처리기

BOOL Main::OnInitDialog()
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
	mrr = 0;
	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void Main::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}
void Main::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR Main::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void Main::OnBnClickedButtonJobApplication()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

		mrr = new C도서관리프로그램Dlg(this);
		//mrr->AddEndedEventHandler(this);//너 죽을 때 나한테 알려줘
		mrr->Create(IDD_DIALOG_MAIN, this);
		mrr->ShowWindow(SW_SHOW);

}
void Main::EndedDialog()
{
	PostMessage(MWM_ENDED_REG, 0, 0);
}



void Main::OnBnClickedButtonJobInfo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	JobInfo* jb = new JobInfo();
	//vd->DoModal();//모달 대화상자
	jb->Create(IDD_DIALOG_JOB_INFO);
	jb->ShowWindow(SW_SHOW);
}
BOOL Main::DestroyWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	BookManager& bm = BookManager::GetBookManager();
	bm.Save();
	return __super::DestroyWindow();
}
void Main::OnLButtonDown(UINT nFlags, CPoint point)
{
	// IDC_STATIC으로 정의된 Picture Control을 가져옵니다.
	CWnd* pStatic = GetDlgItem(IDC_STATIC_JS);
	if (pStatic)
	{
		CRect rect;
		pStatic->GetClientRect(&rect);

		// 클릭한 좌표가 Picture Control의 영역 내에 있는지 확인합니다.
		if (rect.PtInRect(point))
		{
			// 클릭한 경우 원하는 링크로 이동합니다.
			ShellExecute(NULL, _T("open"), _T("http://www.jseng.com"), NULL, NULL, SW_SHOWNORMAL);
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

void Main::OnBnClickedButtonMembership()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SVCENTER* sv = new SVCENTER();
	//vd->DoModal();//모달 대화상자
	sv->Create(IDD_DIALO_SVCENTER);
	sv->ShowWindow(SW_SHOW);
}


void Main::OnBnClickedButtonLoginpage()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	LoginPageDialog* LPD = new LoginPageDialog();
	LPD->Create(IDD_DIALOG_LOGINPAGE);
	LPD->ShowWindow(SW_SHOW);
}

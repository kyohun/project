// Main.h
#pragma once
#include "afxdialogex.h"
#include "EndDialogEventHandler.h"
#include "도서 관리 프로그램Dlg.h"

// Main 대화 상자

class Main : public CDialogEx,
	public EndDialogEventHandler
{
	C도서관리프로그램Dlg* mrr;
	//DECLARE_DYNAMIC(Main)

public:
	Main(CWnd* pParent = nullptr);   // 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN };
#endif

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	//afx_msg void OnBnClickedButtonReg();
	virtual void EndedDialog();
	//afx_msg LRESULT OnEndedReg(WPARAM, LPARAM);
	//CListCtrl blist;
	//virtual void AddedBook(Book* book);
	//afx_msg void OnBnClickedButtonVerify();
	//afx_msg void OnLvnItemchangedListBook(NMHDR* pNMHDR, LRESULT* pResult);
	//CButton btn_remove;
	//afx_msg void OnBnClickedButtonRemove();
	//afx_msg void OnBnClickedButtonModify();
	//virtual void ModifiedBook(Book* book);
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedButtonJobApplication();
	afx_msg void OnBnClickedButtonJobInfo();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonMembership();
	afx_msg void OnBnClickedButtonLoginpage();
};

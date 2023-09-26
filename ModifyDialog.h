#pragma once
#include "afxdialogex.h"
#include "AddBookEventHandler.h"
#include "BookManager.h"
// ModifyDialog 대화 상자

class ModifyDialog : public CDialogEx,
	public AddBookEventHandler,
	public RemoveBookEventHandler
{
	DECLARE_DYNAMIC(ModifyDialog)

public:
	ModifyDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ModifyDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MODIFY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl list_book;
	CStatic pic_img;
	COleDateTime pubdate;
	CString content;
	CString image;
	virtual void AddedBook(Book* book);
	virtual void RemovedBook(int bno);
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedListBook(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedButtonImg();
	afx_msg void OnBnClickedButtonSub();

	
	CString paddr;
};

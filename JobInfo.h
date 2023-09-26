#pragma once
#include "afxdialogex.h"


// JobInfo 대화 상자

class JobInfo : public CDialogEx
{
	DECLARE_DYNAMIC(JobInfo)

public:
	JobInfo(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~JobInfo();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_JOB_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDev();
	afx_msg void OnBnClickedButtonProduct();
	afx_msg void OnBnClickedButtonCs();
	afx_msg void OnBnClickedButtonSale();
	afx_msg void OnBnClickedButtonManage();
};

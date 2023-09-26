//AccountManager.h
#pragma once
#include "Account.h"
#include "AddAccountEventHandler.h"
#include <map>
#include <list>
using std::list;

typedef list<int> NList;
typedef NList::iterator NIter;
using std::map;
typedef map<int, Account*> AMap;
typedef AMap::iterator AIter;
typedef list<AddAccountEventHandler*> AAHLIST;
typedef AAHLIST::iterator AAIter;
typedef list<RemoveAccountEventHandler*> RAHLIST;
typedef RAHLIST::iterator RAIter;
typedef list<ModifyAccountEventHandler*> MAHLIST;
typedef MAHLIST::iterator MAIter;

class AccountManager
{
	AMap Account_map;
	int last_bno;//가장 최근에 부여한 도서 번호
	AAHLIST abhandlers;
	RAHLIST rbhandlers;
	MAHLIST mbhandlers;
	static AccountManager am;//단일체 개체
public:
	static AccountManager& GetAccountManager();//단일체 개체를 반환
	//int GetNextAccountNo();
	bool AddAccount(int acc_no, CString acc_email, CString acc_password, CString acc_name, COleDateTime acc_birthdate, CString acc_phone, CString acc_image);
	//void GetAccountNoList(NList* bno_list);
	Account* GetAccount(int no);
	bool ModifyAccount(int acc_no, CString acc_email, CString acc_password, CString acc_name, COleDateTime acc_birthdate, CString acc_phone, CString acc_image);
	bool RemoveAccount(int bno);
	void AddABEventHandler(AddAccountEventHandler* abeh);//계정 추가하면 나한테 알려주세요.
	void AddRBEventHandler(RemoveAccountEventHandler* rbeh);//계정 삭제하면 나한테 알려주세요.
	void AddMBEventHandler(ModifyAccountEventHandler* mbeh);//계정 변경하면 나한테 알려주세요.
private:
	AccountManager();
};
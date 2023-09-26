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
	int last_bno;//���� �ֱٿ� �ο��� ���� ��ȣ
	AAHLIST abhandlers;
	RAHLIST rbhandlers;
	MAHLIST mbhandlers;
	static AccountManager am;//����ü ��ü
public:
	static AccountManager& GetAccountManager();//����ü ��ü�� ��ȯ
	//int GetNextAccountNo();
	bool AddAccount(int acc_no, CString acc_email, CString acc_password, CString acc_name, COleDateTime acc_birthdate, CString acc_phone, CString acc_image);
	//void GetAccountNoList(NList* bno_list);
	Account* GetAccount(int no);
	bool ModifyAccount(int acc_no, CString acc_email, CString acc_password, CString acc_name, COleDateTime acc_birthdate, CString acc_phone, CString acc_image);
	bool RemoveAccount(int bno);
	void AddABEventHandler(AddAccountEventHandler* abeh);//���� �߰��ϸ� ������ �˷��ּ���.
	void AddRBEventHandler(RemoveAccountEventHandler* rbeh);//���� �����ϸ� ������ �˷��ּ���.
	void AddMBEventHandler(ModifyAccountEventHandler* mbeh);//���� �����ϸ� ������ �˷��ּ���.
private:
	AccountManager();
};
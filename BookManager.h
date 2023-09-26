#pragma once
#include "Book.h"
#include "AddBookEventHandler.h"
#include <map>
#include <list>
using std::list;

typedef list<int> NList;
typedef NList::iterator NIter;
using std::map;
typedef map<int, Book*> BMap;
typedef BMap::iterator BIter;
typedef list<AddBookEventHandler*> ABHList;
typedef ABHList::iterator ABIter;
typedef list<RemoveBookEventHandler*> RBHList;
typedef RBHList::iterator RBIter;
typedef list<ModifyBookEventHandler*> MBHList;
typedef MBHList::iterator MBIter;
typedef list<RegisterBookEventHandler*> RegBHList;
typedef RegBHList::iterator RegBIter;

class BookManager
{
	BMap book_map;
	int last_bno;//���� �ֱٿ� �ο��� ���� ��ȣ
	ABHList abhandlers;
	RBHList rbhandlers;
	MBHList mbhandlers;
	RegBHList regbhandlers;
	static BookManager bm;//����ü ��ü
public:
	static BookManager& GetBookManager();//����ü ��ü�� ��ȯ
	int GetNextBookNo();
	bool AddBook(CString title, CString content, CString paddr,CString image, COleDateTime pubdate);
	void GetBookNoList(NList* bno_list);
	Book* GetBook(int no);
	bool ModifyBook(int bno, CString content, CString paddr, CString image, COleDateTime pubdate);
	bool RemoveBook(int bno);
	void AddABEventHandler(AddBookEventHandler* abeh);//���� �߰��ϸ� ������ �˷��ּ���.
	void AddRBEventHandler(RemoveBookEventHandler* rbeh);//���� �����ϸ� ������ �˷��ּ���.
	void AddMBEventHandler(ModifyBookEventHandler* mbeh);//���� �����ϸ� ������ �˷��ּ���.
	void AddRegBEventHandler(RegisterBookEventHandler* regbeh);//���� �����ϸ� ������ �˷��ּ���.
	void Save();
	void Load();
private:	
	BookManager();
};




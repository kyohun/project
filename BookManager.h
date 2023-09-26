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
	int last_bno;//가장 최근에 부여한 도서 번호
	ABHList abhandlers;
	RBHList rbhandlers;
	MBHList mbhandlers;
	RegBHList regbhandlers;
	static BookManager bm;//단일체 개체
public:
	static BookManager& GetBookManager();//단일체 개체를 반환
	int GetNextBookNo();
	bool AddBook(CString title, CString content, CString paddr,CString image, COleDateTime pubdate);
	void GetBookNoList(NList* bno_list);
	Book* GetBook(int no);
	bool ModifyBook(int bno, CString content, CString paddr, CString image, COleDateTime pubdate);
	bool RemoveBook(int bno);
	void AddABEventHandler(AddBookEventHandler* abeh);//도서 추가하면 나한테 알려주세요.
	void AddRBEventHandler(RemoveBookEventHandler* rbeh);//도서 삭제하면 나한테 알려주세요.
	void AddMBEventHandler(ModifyBookEventHandler* mbeh);//도서 삭제하면 나한테 알려주세요.
	void AddRegBEventHandler(RegisterBookEventHandler* regbeh);//도서 삭제하면 나한테 알려주세요.
	void Save();
	void Load();
private:	
	BookManager();
};




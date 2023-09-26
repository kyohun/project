///AccountManager.cpp
#include "pch.h"
#include "AccountManager.h"
AccountManager AccountManager::am;
AccountManager& AccountManager::GetAccountManager()
{
    return am;
}
AccountManager::AccountManager()
{
    last_bno = 0;
}
//int AccountManager::GetNextAccountNo()
//{
//   return last_bno + 1;
//}
bool AccountManager::AddAccount(int acc_no, CString acc_email, CString acc_password, CString acc_name, COleDateTime acc_birthdate, CString acc_phone, CString acc_image)
{
    //last_bno++;
    Account* account = new Account(acc_no, acc_email, acc_password, acc_name, acc_birthdate, acc_phone, acc_image);
    Account_map[0] = account;
    /*
    * 도서 추가한 정보를 알고자 하는 이들에게 통보하는 코드가 필요할 듯
    */
    AAIter seek = abhandlers.begin();
    AAIter end = abhandlers.end();
    for (; seek != end; ++seek)
    {
        (*seek)->AddedAccount(account);//도서 추가 사실을 통보한다.
    }
    return true;
}
//void AccountManager::GetAccountNoList(NList* bno_list)
//{
//   Account* Account = 0;
//   BIter seek = Account_map.begin();
//   BIter end = Account_map.end();
//   for (; seek != end; ++seek)
//   {
//      Account = (*seek).second;//값
//      if (Account)//값이 유효하다면
//      {
//         bno_list->push_back((*seek).first);//Account->GetNo()
//      }
//   }
//}
Account* AccountManager::GetAccount(int no)
{
    return Account_map[no];
}
bool AccountManager::ModifyAccount(int acc_no, CString acc_email, CString acc_password, CString acc_name, COleDateTime acc_birthdate, CString acc_phone, CString acc_image)
{
    Account* account = Account_map[0];
    if (account)
    {
        account->SetAccEmail(acc_email);
        account->SetAccPassword(acc_password);
        account->SetAccName(acc_name);
        account->SetAccBirthdate(acc_birthdate);
        account->SetAccPhone(acc_phone);
        account->SetAccImage(acc_image);
        MAIter seek = mbhandlers.begin();
        MAIter end = mbhandlers.end();
        for (; seek != end; ++seek)
        {
            (*seek)->ModifiedAccount(account);
        }
        return true;
    }
    return false;
}
bool AccountManager::RemoveAccount(int bno)
{
    Account* account = Account_map[bno];
    if (account)
    {
        delete account;
        Account_map[bno] = 0;
        RAIter seek = rbhandlers.begin();
        RAIter end = rbhandlers.end();
        for (; seek != end; ++seek)
        {
            (*seek)->RemovedAccount(bno);
        }
        return true;
    }
    return false;
}
void AccountManager::AddABEventHandler(AddAccountEventHandler* abeh)
{
    abhandlers.push_back(abeh);
}
void AccountManager::AddRBEventHandler(RemoveAccountEventHandler* rbeh)
{
    rbhandlers.push_back(rbeh);
}
void AccountManager::AddMBEventHandler(ModifyAccountEventHandler* mbeh)
{
    mbhandlers.push_back(mbeh);
}
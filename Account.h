#pragma once
class Account
{
	int acc_no;
	CString acc_email;
	CString acc_password;
	CString acc_name;
	COleDateTime acc_birthdate;
	CString acc_phone;
	CString acc_image;
public:
	Account(int acc_no, CString acc_email, CString acc_password, CString acc_name, COleDateTime acc_birthdate, CString acc_phone, CString acc_image);
	int GetAccNo();
	CString GetAccEmail();
	CString GetAccPassword();
	CString GetAccName();
	COleDateTime GetAccBirthdate();
	CString GetAccPhone();
	CString GetAccImage();
	void SetAccEmail(CString acc_email);
	void SetAccPassword(CString acc_password);
	void SetAccName(CString acc_name);
	void SetAccBirthdate(COleDateTime acc_birthdate);
	void SetAccPhone(CString acc_phone);
	void SetAccImage(CString acc_image);

};


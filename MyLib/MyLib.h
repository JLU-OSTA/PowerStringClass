#ifndef MYLIB_API
	#ifdef MYLIB_EXPORTS
		#define MYLIB_API __declspec( dllexport )
	#else	
		#define MYLIB_API __declspec( dllimport )
	#endif
#endif


#include <iostream>
#include <string>
#include <stdio.h>

//using namespace std;

class MYLIB_API MyStr
{
public:
	MyStr();
	MyStr(const char* src);
	MyStr(const MyStr& src);
	operator char*(){return m_pData;}
	void Clear();
	void ExtendSize(int size);
	int	GetLength() const{return strlen(m_pData);}	//多用const
	char* GetData() const{return m_pData;}
	char GetAt(int pos) const{return m_pData[pos];}
	void SetAt(char tmp,int pos){m_pData[pos]=tmp;}
	int Compare(const char* tmp) const{return strcmp(tmp,m_pData);}
	int FindChar(const char tmp) const;	//常变量
	int FindString(const char* tmp) const;
	//int FindString(char* tmp);	My method
	MyStr& ToUpper();
	MyStr& ToLower();
	MyStr& Append(const char* tmp);
	MyStr& Insert(int pos,const char tmp);
	MyStr& Insert(int pos,const char* tmp);
	MyStr& Delete(int pos,int count=1);
	MyStr& TrimLeft(const char tmp=' ');
	MyStr& TrimRight(const char tmp=' ');
	MyStr& FillLeft(int len,char tmp=' ');
	MyStr& Replace(const MyStr& oldVal,const MyStr& newVal);

	MYLIB_API friend bool operator==(const MyStr& tmp1,const MyStr& tmp2);
	MYLIB_API friend bool operator!=(const MyStr& tmp1,const MyStr& tmp2);
	MYLIB_API friend bool operator>(const MyStr& tmp1,const MyStr& tmp2);
	MYLIB_API friend bool operator>=(const MyStr& tmp1,const MyStr& tmp2);
	MYLIB_API friend bool operator<(const MyStr& tmp1,const MyStr& tmp2);
	MYLIB_API friend bool operator<=(const MyStr& tmp1,const MyStr& tmp2);

	MyStr& operator=(const MyStr& tmp);
	MyStr& operator+=(const MyStr& tmp);
	MYLIB_API friend MyStr operator+(const MyStr& tmp1,const MyStr& tmp2);

	char& operator[](int pos);

	MYLIB_API friend std::ostream& operator<<(std::ostream& tmp,const MyStr& src);
	MYLIB_API friend std::istream& operator>>(std::istream& tmp,const MyStr& src);
private:
	char* m_pData;
	int m_iSize;
};
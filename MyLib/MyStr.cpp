#include "stdafx.h"
#include <iostream>
#include "MyLib.h"

//using namespace std;

MyStr::MyStr()
{
	m_pData=NULL;
	m_iSize=0;
}

MyStr::MyStr(const char* src):m_pData(NULL),m_iSize(0)
{
	if(src==NULL) return;	//判断src是否为空
	m_iSize=(strlen(src)+1)*256;	//内存对齐,256的倍数可以使运算更快
	m_pData=new char[m_iSize];
	strcpy(m_pData,src);
}

MyStr::MyStr(const MyStr& src)
{
	m_iSize=src.m_iSize;
	m_pData=new char[m_iSize];
	strcpy(m_pData,src.m_pData);
}

void MyStr::Clear()
{
	delete m_pData;
	m_iSize=0;
}

void MyStr::ExtendSize(int size)
{
	if(size>=0)
	{
		char* backup=new char[m_iSize];
		strcpy(backup,m_pData);
		delete m_pData;
		m_iSize=(m_iSize/256+size)*256;
		m_pData=new char[m_iSize];
		strcpy(m_pData,backup);
		delete backup;
	}
	else throw "Extend out of size!!!";
}

int MyStr::FindChar(const char tmp) const
{
	for(unsigned int i=0;GetLength();i++)	//用unsigned int代替int
		if(m_pData[i]==tmp) return i;
	return -1;
}

int MyStr::FindString(const char* tmp) const
{
	char* result=strstr(m_pData,tmp);	//strstr返回首次出现子串的地址
	if(result==NULL) return -1;
	else return result-m_pData;
}

/*int MyStr::FindString(const char* tmp)
{
	for(unsigned int i=0;i<GetLength();i++)
	{
		if(m_pData[i]==tmp[0])
		{
			bool tag=1;
			for(unsigned int j=1,k=i+1;j<strlen(tmp);j++,k++)
				if(m_pData[k]!=tmp[j]) tag=0;
			if(tag) return i;
		}
	}
}*/

MyStr& MyStr::ToUpper()
{
	for(unsigned int i=0;i<GetLength();i++)
		if(m_pData[i]>='a'&&m_pData[i]<='z')	//判断是否为小写
			m_pData[i]-='a'-'A';
	return *this;
}

MyStr& MyStr::ToLower()
{
	for(unsigned int i=0;i<GetLength();i++)
		if(m_pData[i]>='A'&&m_pData[i]<='Z')
			m_pData[i]+='a'-'A';
	return *this;
}

MyStr& MyStr::Append(const char* tmp)
{
	//Trash Code!!!
	/*char* backup=new char[m_iSize];
	strcpy(backup,m_pData);
	delete m_pData;
	m_iSize+=strlen(tmp);
	m_pData=new char[m_iSize];
	strcpy(m_pData,backup);
	delete backup;*/
	ExtendSize(strlen(tmp));
	strcat(m_pData,tmp);	//追加内容
	return *this;
}

MyStr& MyStr::Insert(int pos,const char tmp)
{
	ExtendSize(1);
	for(int i=GetLength()-1;i>=pos;i--)
		m_pData[i+1]=m_pData[i];
	m_pData[pos]=tmp;
	/*char c=tmp;	//待插入字符
	for(int i=pos;i<=GetLength();i++)
	{
		//从pos开始，所有字符往后串一个字节
		char cNext=m_pData[i]; //下一个待插入字符
		m_pData[i]=c;	//插入
		c=cNext;	//下一个待插入字符
	}*/
	return *this;
}

MyStr& MyStr::Insert(int pos,const char* tmp)
{
	ExtendSize(strlen(tmp));
	char* backup=new char[m_iSize];
	strcpy(backup,m_pData+pos);	//备份pos之后的内容
	strcpy(m_pData+pos,tmp);	//将tmp拷贝到pos之后
	strcat(m_pData,backup);	//将备份追加到字符数组
	return *this;
}

MyStr& MyStr::Delete(int pos,int count)
{
	strcpy(m_pData+pos,m_pData+pos+count);	//Check it
	return *this;
}

MyStr& MyStr::TrimLeft(const char tmp)
{
	unsigned int i;
	for(i=0;m_pData[i]==tmp&&i<GetLength();i++);
	Delete(0,i);
	return *this;
}

MyStr& MyStr::TrimRight(const char tmp)
{
	unsigned int i;
	for(i=GetLength()-1;m_pData[i]==tmp&&i>=0;i--);	//i=GetLength()-1
	m_pData[i+1]='\0';	//Check
	return *this;
}

MyStr& MyStr::FillLeft(int len,char tmp)
{
	int length=len-GetLength();
	ExtendSize(len-GetLength());
	char* backup=new char[m_iSize];
	strcpy(backup,m_pData);
	delete m_pData;
	char* m_pData=new char[m_iSize];
	for(unsigned int i=0;i<length;i++)
		m_pData[i]=tmp;
	strcat(m_pData,backup);
	return *this;
}

MyStr& MyStr::Replace(const MyStr& oldVal,const MyStr& newVal)
{
	unsigned int pos=FindString(oldVal.GetData());
	Delete(pos,oldVal.GetLength());
	Insert(pos,newVal.GetData());
	return *this;
}

bool operator==(const MyStr& tmp1,const MyStr& tmp2){return strcmp(tmp1.GetData(),tmp2.GetData())==0;}

bool operator!=(const MyStr& tmp1,const MyStr& tmp2){return strcmp(tmp1.GetData(),tmp2.GetData())!=0;}

bool operator>(const MyStr& tmp1,const MyStr& tmp2){return strcmp(tmp1.GetData(),tmp2.GetData())>0;}

bool operator>=(const MyStr& tmp1,const MyStr& tmp2){return strcmp(tmp1.GetData(),tmp2.GetData())>=0;}

bool operator<(const MyStr& tmp1,const MyStr& tmp2){return strcmp(tmp1.GetData(),tmp2.GetData())<=0;}

bool operator<=(const MyStr& tmp1,const MyStr& tmp2){return strcmp(tmp1.GetData(),tmp2.GetData())<=0;}

MyStr& MyStr::operator=(const MyStr& tmp)
{
	if(this==&tmp) return *this; 
	if(m_pData!=NULL) delete[] m_pData;
	m_iSize=tmp.m_iSize;
	m_pData=new char[m_iSize];
	strcpy(m_pData,tmp.m_pData);
	return *this;
}
	

MyStr& MyStr::operator+=(const MyStr& tmp)
{
	ExtendSize(tmp.GetLength());
	strcat(m_pData,tmp.GetData());
	return *this;
}

MyStr operator+(const MyStr& tmp1,const MyStr& tmp2)
{
	MyStr str(tmp1);
	str.Append(tmp2.GetData());
	return str;
}

char& MyStr::operator[](int pos){return m_pData[pos];}

std::ostream& operator<<(std::ostream& tmp,const MyStr& src){return tmp<<src.GetData();}

std::istream& operator>>(std::istream& tmp,MyStr& src)
{
	char* in;
	tmp>>in;
	src.Clear();
	src=MyStr(in);
	return tmp;
}

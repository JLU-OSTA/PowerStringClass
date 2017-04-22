// MyLibDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MyLib.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	MyStr a("hehe");
	cout<<"a: "<<a<<endl;
	a+="HAHA";
	cout<<a<<endl;
	MyStr b=a;
	cout<<"a: "<<a<<endl<<"b: "<<b<<endl;
	cout<<"a=b?  "<<(a==b)<<endl;
	b.Delete(1,3);
	cout<<"b deleted: "<<b<<endl;
	cout<<"a>b?  "<<(a>b)<<endl;
	cout<<"a<=b?  "<<(a<=b)<<endl;
	b=b+a;
	cout<<"b=b+a: "<<b<<endl;
	cout<<"b[5]: "<<b.GetAt(5)<<endl;
	cout<<"b to upper: "<<b.ToUpper()<<endl;
	cout<<"b to lower: "<<b.ToLower()<<endl;
	cout<<"b append: "<<b.Append("OSTA")<<endl;
	cout<<"b insert: "<<b.Insert(2,"Kingrealer")<<endl;
	cout<<"b insert: "<<b.Insert(0,"    ")<<endl;
	cout<<"b insert: "<<b.Insert(b.GetLength(),"kkkk")<<endl;
	cout<<"b trimleft: "<<b.TrimLeft()<<endl;
	cout<<"b trimright: "<<b.TrimRight('k')<<endl;
	//cout<<"b fillleft: "<<b.FillLeft(b.GetLength()+3,'i')<<endl;
	cout<<"b find str: "<<b.FindString("Kingrealer")<<endl;
	cout<<"b replace: "<<b.Replace("OSTA","Tech")<<endl;
	cout<<"cin: "<<endl;
	//cin>>b;
	cout<<"cin: "<<b<<endl;
	return 0;
}

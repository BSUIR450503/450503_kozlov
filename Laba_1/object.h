#ifdef _WIN32
//#include "stdafx.h"
#include "windows.h"
#include <string>
#include <iostream>
#include <atlconv.h>
using namespace std;
class Process
{
    public:
	PROCESS_INFORMATION p;
    Process(string name,string parametr,bool waitfor,int & status)
	{
        parametr=name+' '+parametr;
		STARTUPINFO a;
		ZeroMemory( &a, sizeof(a));
		a.cb = sizeof(a);
		ZeroMemory( &p, sizeof(p) );
		wchar_t * t=new wchar_t[100];
		mbstowcs(t,parametr.c_str(),100);
		if(!CreateProcess(NULL, t ,NULL,NULL,FALSE,0,NULL,NULL,&a,&p))
			cout<<"Процесс не создан"<<endl;
       if (waitfor)
			WaitForSingleObject(p.hProcess,INFINITE);
            DWORD code;
			GetExitCodeProcess(p.hProcess, &code);
            status=code;
	}
	~Process()
	{
		CloseHandle(p.hProcess);
	}
};
#endif

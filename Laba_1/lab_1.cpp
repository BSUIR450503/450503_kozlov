
#include "object.h"
#ifdef _WIN32
#define FNAME "spovm_lab1.exe"

#include <fstream>
using namespace std;
int main(int argc, char * argv[])
{
	
	string name,parametr;
	int result;
    name= FNAME;
	cout << "Input number:" <<endl;
	cin>>parametr;
    Process pr(name,parametr,1,result);
    cout<<"Result:"<<result<<endl;
	system("pause");
	return 0;
}


#elif linux
#include <stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
	int result=9;
  pid_t pid;
  int a;
  switch(pid=fork()) {
  case -1:
          perror("fork"); /* произошла ошибка */
          exit(1); /*выход из родительского процесса*/
  case 0:
         result*=result;
		 printf("%d",result);
		 exit(result);
  default:
         
          wait(&a);
          WEXITSTATUS(a);
          
  }
}
#endif

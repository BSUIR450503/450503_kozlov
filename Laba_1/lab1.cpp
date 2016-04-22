#include <stdio.h>
//#ifdef _WIN32
#include <windows.h>


//#ifdef __linux__
//#include <unistd.h>
//#include <stdlib.h>

//#endif

int main(int argc, wchar_t *argv[])
{
	#ifdef WIN32
	
		int  result = _wtoi(argv[1]);
		result*=result;
        printf("%d\n", result);
		return result;
   
 
    
//	#endif

//	#ifdef linux


//	sleep(10);
//	#endif
	return 0;
}
#endif
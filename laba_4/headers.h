#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <process.h>

#define PLATFORM_WIN 1 
#define PLATFORM_UNIX 2 

#if defined(_WIN32) || defined(_WIN64) 
	#include <windows.h> 
	#include <conio.h> 
	#define PLATFORM PLATFORM_WIN 
#else 
	#include <sys/sem.h>
	#include <sys/types.h>
	#include <sys/wait.h>
	#include <errno.h>
	#include <unistd.h>
	#include <termios.h>
	#define PLATFORM PLATFORM_UNIX 

	char _getch();
#endif 

struct Data
{
#if PLATFORM == PLATFORM_WIN
	HANDLE threadInfo;
	HANDLE hStdOut;
	HANDLE hMutex;
#else

#endif
	int number;
};

struct REC_D
{
#if PLATFORM == PLATFORM_WIN
	struct Data *data;
	struct Stack *stack;
#else

#endif
};

#include "stack.h"

struct Data initData(struct Data);
struct Stack * CreateNewThread(int, struct Data *, struct Stack *);
struct Stack * CloseLastThread(struct Stack *, struct Data *);
struct Stack * CloseAllThreads(struct Stack *, struct Data *);
void PrintThreads(void *);
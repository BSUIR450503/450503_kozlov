#include "headers.h"

void PrintThreads(void *p)
{
	struct REC_D *pdata = (struct REC_D *)p;
	CONST HANDLE hMutex = (CONST HANDLE)(pdata->data->hMutex);

	int num = pdata->data->number;

	while (1)
	{
		WaitForSingleObject(hMutex, INFINITE);
		printf("Index: %d \n", num);
		ReleaseMutex(hMutex);
		Sleep(100);
	}
	
	_endthread();
}
struct Stack * CreateNewThread(int number, struct Data *data, struct Stack *stack)
{
	data->number = number;
	struct REC_D *rec = (struct REC_D *)malloc(sizeof(struct REC_D));

	rec->data = *&data;
	data->threadInfo = (HANDLE)_beginthread(PrintThreads, 0, (void *)rec);
	
	stack = push(stack, *data);
	rec->stack = stack;

	return stack;
}
struct Stack * CloseLastThread(struct Stack *stack, struct Data *data)
{
	WaitForSingleObject(data->hMutex, INFINITE);
	TerminateThread(stack->threadInfo, 0);
	stack = pop(stack);
	int c = data->number;
	data->number = --c;
	ReleaseMutex(data->hMutex);

	return stack;
}
struct Stack * CloseAllThreads(struct Stack *stack, struct Data *data)
{
	while (size(stack) != 0)
	{
		WaitForSingleObject(data->hMutex, INFINITE);
		TerminateThread(stack->threadInfo, 0);
		
		stack = pop(stack);
		int c = data->number;
		data->number = --c;
		ReleaseMutex(data->hMutex);
	}

	return stack;
}
struct Data initData(struct Data data)
{
	data.hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	data.hMutex = CreateMutex(NULL, FALSE, NULL);
	data.number = 0;
	if (NULL == data.hMutex) {
		printf("Failed to create mutex.\n");
		ExitProcess(0);
	}
	
	return data;
}

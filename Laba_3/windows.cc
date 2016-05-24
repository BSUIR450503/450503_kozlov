// lab3 windows. Using canals.

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

void Server(){

	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	PROCESS_INFORMATION childProcessInfo;
	ZeroMemory(&childProcessInfo, sizeof(childProcessInfo));

	HANDLE hMyPipe;
	HANDLE Semaphores[3];
	TCHAR Line[] = TEXT("Child.exe");

	char buffer[100];

	Semaphores[0] = CreateSemaphore(NULL, 0, 1, TEXT("sem_ready"));
	Semaphores[1] = CreateSemaphore(NULL, 0, 1, TEXT("sem_end"));
	Semaphores[2] = CreateSemaphore(NULL, 0, 1, TEXT("sem_exit"));

	hMyPipe = CreateNamedPipe(
		TEXT("\\\\.\\pipe\\Mypipe"),
		PIPE_ACCESS_OUTBOUND,
		PIPE_TYPE_MESSAGE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		0,
		0,
		INFINITE,
		(LPSECURITY_ATTRIBUTES)NULL
		);
	if (hMyPipe == INVALID_HANDLE_VALUE){
		printf("Error with creation pipe!!!!\n\n");
		exit(0);
	}

	if (!CreateProcess(NULL,
		Line,
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&si,
		&childProcessInfo)){
		printf("Create Process Error");
		exit(0);
	}

	if (!ConnectNamedPipe(hMyPipe, (LPOVERLAPPED)NULL))
		printf("Connection failure\n");

	while (1)
	{
		
		DWORD NumberOfBytesWritten;

		printf("\nEnter message:\n");
		fflush(stdin);
		gets(buffer);

		if (!strcmp(buffer, "quit")){
			ReleaseSemaphore(Semaphores[2], 1, NULL);  
			WaitForSingleObject(childProcessInfo.hProcess, INFINITE);
			break;
		}

		ReleaseSemaphore(Semaphores[0], 1, NULL);  

		int size = strlen(buffer);
		WriteFile(hMyPipe, &size, sizeof(size), &NumberOfBytesWritten, (LPOVERLAPPED)NULL);

		if (!WriteFile(hMyPipe, buffer, strlen(buffer), &NumberOfBytesWritten, (LPOVERLAPPED)NULL))
			printf("Write Error\n");

		WaitForSingleObject(Semaphores[1], INFINITE); 
	}

	CloseHandle(hMyPipe);
	CloseHandle(Semaphores[0]);
	CloseHandle(Semaphores[1]);
	printf("\n\n");
	return;
}

int main(){
	Server();
}
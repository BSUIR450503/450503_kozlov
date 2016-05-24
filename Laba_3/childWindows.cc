//Дочерний процесс, или по-другому "клиент"

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>


void client(){

	HANDLE hMyPipe; 
	HANDLE Semaphores[3]; 

	char buffer[20];

	int successFlag;

	Semaphores[0] = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, TEXT("sem_ready")); 
	Semaphores[1] = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, TEXT("sem_end"));
	Semaphores[2] = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, TEXT("sem_exit"));

	printf("Child process\n\n");

	hMyPipe = CreateFile(
		TEXT("\\\\.\\pipe\\MyPipe"),
		GENERIC_READ,
		FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL); 


	while (1)
	{
		successFlag = 1;

		DWORD NumberOfBytesRead;

		char s[] = "";
		strcpy(buffer, s);

		int index = WaitForMultipleObjects(3, Semaphores, FALSE, INFINITE) - WAIT_OBJECT_0; 
		
		if (index == 2){ 
			printf("Closing child process\n");
			break;
		}

		int size;
		if (!ReadFile(hMyPipe, &size, sizeof(size), &NumberOfBytesRead, NULL)) break;

			successFlag = ReadFile(hMyPipe, buffer, size, &NumberOfBytesRead, NULL);
			if (!successFlag) break;

		for (int i = 0; i < size; i++)
		{
			printf("%c", buffer[i]);
			Sleep(100);
		}
		printf("\n");

		ReleaseSemaphore(Semaphores[1], 1, NULL);	
	}
	CloseHandle(hMyPipe);
	CloseHandle(Semaphores[0]);
	CloseHandle(Semaphores[1]);
	return;
}



int main(){
	client();
}
#include "headers.h"

int main()
{
	struct Data data;
	struct Stack *stack = NULL;

	data = initData(data);

	while (1)
	{
		switch (_getch())
		{
		case '+':
			stack = CreateNewThread(++(data.number), &data, stack);
			break;
		case '-':
			if (size(stack) != 0)
				stack = CloseLastThread(stack, &data);
			break;
		case 'q':
			stack = CloseAllThreads(stack, &data);
			return 0;
			break;
		}
	}

	return 0;
}
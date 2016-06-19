struct Stack {
#if PLATFORM == PLATFORM_WIN
	HANDLE threadInfo;
#else
	pid_t pid;
#endif
	struct Stack *next;
	int index;
};

int size(const struct Stack *);
struct Stack * push(struct Stack *, struct Data);
struct Stack * pop(struct Stack *);
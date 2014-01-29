#include <stdio.h>
#include <stdlib.h>

#define STACK_GOAL 0xBFFF0000U
#define MAX_PAD 0xFFFF

int main(int argc, char *argv[], char *envp[])
{
	// Advance the stack pointer to a position that's invariant of
	// the size of the environment and the program arguments.
	char *esp = alloca(0);
	if ((esp < (char *)STACK_GOAL) || (esp - (char *)STACK_GOAL > MAX_PAD)) {
		fprintf(stderr, "Can't normalize stack position: %p\n", esp);
		return 1;
	}
	alloca(esp - (char *)STACK_GOAL);
#ifdef COOKIE
	alloca(COOKIE);
#endif
	return _main(argc, argv, envp);
}

#include <sys/syscall.h>
#include <unistd.h>

void my_write()
{
	syscall(SYS_write, 1, "Hello word\n", 11);
}

int main()
{
	my_write();
	return 0;
}

#include <stdio.h>

#include <dlfcn.h>

int main()
{
	void *session;
	void (*func)();

	session = dlopen("./librntime.so",RTLD_LAZY);
	if (!session)
	{
		printf("failed to open\n");
		return 0;
	}

	func = dlsym(session, "hello_from_dyn_runtime_lib");

    func();

	dlclose(session);

	return 0;
}
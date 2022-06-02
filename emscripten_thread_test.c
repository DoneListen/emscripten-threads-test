
#include <assert.h>
#include <emscripten/emscripten.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <emscripten/threading.h>
#include <emscripten/fetch.h>
void Sleep(double msecs)
{
	double t1 = emscripten_get_now();
	emscripten_thread_sleep(msecs);
	double t2 = emscripten_get_now();
	printf("emscripten_thread_sleep() slept for %f msecs.\n", t2 - t1);

	assert(t2 - t1 >= 0.9 * msecs); // Should have slept ~ the requested time.
}

void *thread_main(void *arg)
{
	while (1)
	{
		char* strURL = "https://webst03.is.autonavi.com/appmaptile?style=6&x=1637&y=815&z=11";
		emscripten_fetch_attr_t attr;
		emscripten_fetch_attr_init(&attr);
		strcpy(attr.requestMethod, "GET");
		attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY | EMSCRIPTEN_FETCH_SYNCHRONOUS/* | EMSCRIPTEN_FETCH_REPLACE*/;
		emscripten_fetch_t* fetch = emscripten_fetch(&attr, strURL); // Blocks here until the operation is complete.
		if (fetch->status == 200)
		{
			//eErrorType = 1;
		}
		else
		{
			//eErrorType = 0;
		}
		emscripten_fetch_close(fetch);
	}
	emscripten_force_exit(0);
	return NULL;
}

int main()
{
	pthread_t thread;
	pthread_create(&thread, NULL, thread_main, NULL);
	emscripten_exit_with_live_runtime();
	__builtin_trap();
}

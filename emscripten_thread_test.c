// Copyright 2019 The Emscripten Authors.  All rights reserved.
// Emscripten is available under two separate licenses, the MIT license and the
// University of Illinois/NCSA Open Source License.  Both these licenses can be
// found in the LICENSE file.

#include <pthread.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <emscripten.h>
#include <emscripten/fetch.h>
#include <stdio.h>
#include <string.h>

static void *thread_start(void *arg)
{
	for (int i = 0; i < 10000; i++)
	{
		//printf("thread_start\n");
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
	printf("thread_start\n");

	//emscripten_force_exit(0);
	/*char* buffer = (char*)malloc(64 * 1024 * 1024);
	assert(buffer);
	*buffer = 42;
	pthread_exit((void*)buffer);*/
}

int main()
{
  printf("prep\n");
  pthread_t thr;

  printf("start\n");

  printf("create\n");
  int s = pthread_create(&thr, NULL, thread_start, (void*)NULL);
  assert(s == 0);
  void* result = NULL;
  printf("join\n");
  s = pthread_join(thr, &result);
  return 0;
}


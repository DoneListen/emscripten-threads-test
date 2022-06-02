# emscripten-threads-test
A demo of the use of emscripten threads.

Version of emscripten/emsdk: v3.1.0.

Compile command：
emcc emscripten_thread_test.c -s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=2 -s ALLOW_MEMORY_GROWTH=1 -s FETCH -o testThread.html

Access Web service deployment, You can see that browser memory keeps growing.

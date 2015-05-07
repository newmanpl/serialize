ifeq (,$(tg))
  tg=test1
endif

CC = gcc
CXX = g++
CFLAGS = `pkg-config --cflags --libs gtk+-2.0`

ifeq ($(tg),test1)
main: main.cc
#thread: thread_example.c
#thread:: nonblocking_thread.cc
#thread: thread_cplusplus.cc
#thread: thread_join.cc
#thread: thread_detach.cc
	$(CXX) -std=c++11 -o $@ $^ $(CFLAGS)
	@echo "build thread"
endif
.PHONY: clean
clean:
#	-rm *.o test
	-rm thread

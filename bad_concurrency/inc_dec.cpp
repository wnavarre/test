#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstddef>
#include <pthread.h>
#include <stdlib.h>


#ifndef _POSIX_THREAD_PROCESS_SHARED
#error This system does not support process shared mutex
#endif

int main(int argc, char *argv[]) {
	int fd = open("file.txt", O_RDWR);
	void * mapped = mmap(nullptr, 60, PROT_READ | PROT_WRITE, MAP_SHARED,
											 fd, 0);
	int64_t * numbers = (int64_t *)mapped;
  pthread_mutex_t * mutex_loc = (pthread_mutex_t *) &numbers[2];

	bool plus = true;
	bool minus = true;
	bool use_mutex = false;
	
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
	if (argc > 1) {
		char sym = *argv[1];
		if (sym == '+') {
			minus = false;
		}
		if (sym == '-') {
			plus = false;
		}
		if (sym == 'i') {
			numbers[1] = 0;
			pthread_mutex_init(mutex_loc, &attr);
			munmap(mapped, 16);
			close(fd);
			return 0;
		}
	}
	if (argc > 2) {
		char sym = *argv[2];
		if (sym == 'm') {
			use_mutex = true;
		}
	}
	if (plus) {
		if (use_mutex) {
					pthread_mutex_lock(mutex_loc);
		}
		numbers[1]++;
		if (use_mutex) {
			pthread_mutex_unlock(mutex_loc);
		}
	}
	if (minus) {
		if (use_mutex) {
			pthread_mutex_lock(mutex_loc);
		}
		numbers[1]--;
		if (use_mutex) {
			pthread_mutex_unlock(mutex_loc);
		}
	}
	munmap(mapped, 16);
	close(fd);
}

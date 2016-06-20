#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstddef>
#include <iostream>

int main() {
	int fd = open("file.txt", O_RDONLY);
	void * mapped = mmap(nullptr, 16, PROT_READ, MAP_SHARED,
											 fd, 0);
	int64_t * numbers = (int64_t *)(mapped);
	std::cout << numbers[1] << '\n';
	munmap(mapped, 16);
	close(fd);
}

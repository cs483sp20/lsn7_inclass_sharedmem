#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>

/*
 * Note: In order for CMake to properly link this program, we need to add the following
 * to the end of CMakeLists.txt:
 *
 * target_link_libraries([your target name...whatever you have inside add_executable()] "-lrt")
 *
 * This will include the required libraries for shared memory functionality
 */

int main() {
    const int SIZE = 4096;
    const char *name = "/OS2";
    int shm_fd;
    void *ptr;

    /* open the shared memory segment */
    shm_fd = shm_open(name, O_RDWR, 0666);

    if (shm_fd == -1) {
        printf("Shared memory failed.\n");
        exit(-1);
    }

    /* now map the shared memory segment in the address space of the process */
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        printf("Map failed.\n");
        return -1;
    }

    /* Now read from the shared memory region */
    printf("%s\n", (char *)ptr);

    /* remove the shared memory segment */
    if (shm_unlink(name) == -1) {
        printf("Error removing %s\n", name);
        exit(-1);
    }
    return 0;
}
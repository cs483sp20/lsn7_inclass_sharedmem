#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

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
    const char *message0 = "Studying ";
    const char *message1 = "Operating Systems ";
    const char *message2 = "is fun!";
    int shm_fd;
    void *ptr;

    /* Create the shared memory segment */
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    /* Configure size of shared memory segment */
    ftruncate(shm_fd, SIZE);

    /* now map the shared memory segment in the address space of the process */
    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        printf("Map failed.\n");
        return -1;
    }

    /* Now write to the shared memory region. Note we must increment
     * the value of ptr after each write */
    sprintf(ptr, "%s", message0);
    ptr += strlen(message0);
    sprintf(ptr, "%s", message1);
    ptr += strlen(message1);
    sprintf(ptr, "%s", message2);
    ptr += strlen(message2);

    return 0;
}
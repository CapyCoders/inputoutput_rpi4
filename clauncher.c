#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
// GPIO base offsets
#define GPIO_LEN 0xB4   // Length of GPIO register block
extern void run_alarm(uint64_t gpio_base); // ARM64 assembly function
int main() {
   int fd;
   void *gpio_map;
   // Open /dev/gpiomem
   fd = open("/dev/gpiomem", O_RDWR | O_SYNC);
   if (fd < 0) {
       perror("Failed to open /dev/gpiomem");
       return 1;
   }
   // Map GPIO registers into virtual memory
   gpio_map = mmap(NULL, GPIO_LEN, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
   if (gpio_map == MAP_FAILED) {
       perror("mmap failed");
       return 1;
   }
   // Call ARM64 assembly alarm, passing pointer to mapped GPIO
   run_alarm((uint64_t)gpio_map);
   // Cleanup
   munmap(gpio_map, GPIO_LEN);
   close(fd);
   return 0;
}

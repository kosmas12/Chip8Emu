#include "memory.h"
#include "cpu.h"


int main() {
  cpu_reset();
  memory_init(4000);
  memory_deinit(memory);
  return 0;
}

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

int read_le32_stdio(int fd, uint32_t *out)
{
	uint8_t buf[4];
	assert(out != NULL);
	if (read(fd, buf, 4) == 4) {
		*out = 0;
		*out |= buf[3] << 24;
		*out |= buf[2] << 16;
		*out |= buf[1] << 8;
		*out |= buf[0];
		return 0;
	}
	return 1;
}

const uint32_t tt_addr_mask[4] = {0, 0xFFFFFC00, 0xFFF00000, 0xFFFFF000};
const char *tt_type_string[4]  = {"Not present", "Coarse table", "Section", "Fine page table"},
           *tt_perm_string[4]  = {"None / None", "RW / None", "RW / RO", "RW / RW"},
           *tt_cache_string[4] = {"None", "Buffered", "Writethrough + buffered", "Writeback + buffered"};

int main(int argc, char *argv[])
{
	uint32_t va, tt;
	unsigned int tte_type, tte_addr, tte_dom, tte_perm, tte_cache;

	while (read_le32_stdio(STDIN_FILENO, &tt) == 0) {
		tte_type = tt & 3;

		tte_addr = tt & tt_addr_mask[tte_type];
		tte_dom  = (tt >> 5) & 3;

		if (tte_type == 2) {
			tte_perm  = (tt >> 10) & 3;
			tte_cache = (tt >> 2)  & 3;
		}

		printf("[%08X] -> ", va);

		if (tte_type == 0)
			printf("NA");
		else
			printf("[%08X]", tte_addr);

		if (tte_type == 2)
			printf(", permissions: %s, cache: %s", tt_perm_string[tte_type], tt_cache_string[tte_type]);

		printf(" (%s)\n", tt_type_string[tte_type]);
		va += 0x100000;
	}
	return EXIT_SUCCESS;
}

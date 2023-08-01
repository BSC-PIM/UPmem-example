#include <defs.h> //give data about stack (wram)
#include <mram.h>
#include <vmutex.h> // virtual mutex which has no limitation on number 
		    // (harware mutex can not exceed 56 for a single dpu)
#include <stdio.h>

#define BUFFER_SIZE (1024 * 1024)
#define NR_ELEMENTS_HIST (1 << 8)
#define NR_ELEMETNS_PER_TASKLET (BUFFER_SIZE / NR_TASKLETS)

__mram_noinit uint8_t input_table[BUFFER_SIZE];
__mram uint64_t histogram[NR_ELEMENTS_HIST];

/**
 * create a virtual mutex to protect each elements of the histogram.
 * only one hardware mutex is used
**/
VMUTEX_INIT(my_vmutex, NR_ELEMENTS_HIST, 1); // the my_vmutex is the name of the virtual mutex
					     // the NR_ELEMNTS_HIST is the number of vmutex which must be initialized
					     // the last element (1 here) is the number of mutex which are responsible to handle these virtual mutexes

int main() {
	printf("i : %d\n", me());
	for (unsigned i = me() * NR_ELEMETNS_PER_TASKLET; i < (me() + 1) * NR_ELEMETNS_PER_TASKLET; ++i) {
		/**	
	       	* Lock the virtual mutex with id 'elem'
		**/
		uint64_t elem = input_table[i];
		vmutex_lock(&my_vmutex, elem);
		histogram[elem]++;
		vmutex_unlock(&my_vmutex, elem);
	}

	return 0;
}

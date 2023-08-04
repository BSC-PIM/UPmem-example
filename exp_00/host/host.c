#include <dpu.h>
#include <dpu_log.h>
#include <stdio.h>


#ifndef DPU_BINARY
#define DPU_BINARY "build/exp00_dpu"
#endif

int main(void) {
    struct dpu_set_t set, dpu;
    // dpu_set_t is the main structure to group the DPUs
    // the second variable is usually used as a loop iterator.


    // allocate 1 DPU with no profile parameter and group them in a set
    DPU_ASSERT(dpu_alloc(1, NULL, &set));

    // load the binary file which must be executed by DPUs
    DPU_ASSERT(dpu_load(set, DPU_BINARY, NULL));

    // run all the DPUs in set variable (they all execute the DPU_BINARY)
    // the DPU_SYNCHRONOUS works like a barrier. i.e., all the DPUs must finish their jobs and
    // return. after that, the program will awake its process
    DPU_ASSERT(dpu_launch(set, DPU_SYNCHRONOUS));

    // loop over the DPUs of Set
    // in each iteration, dpu variable contains single dpu info
    DPU_FOREACH(set, dpu) {
        // read the logs (print sys calls of DPUs) and print them in host stdout
        DPU_ASSERT(dpu_log_read(dpu, stdout));
    }

    // free the sets
    DPU_ASSERT(dpu_free(set));

    return 0;
}
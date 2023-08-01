dpu-upmem-dpurte-clang -DNR_TASKLETS=3 -DSTACK_SIZE_DEFAULT=256 -DSTACK_SIZE_TASKLET_1=2048 -O2 -o tasklet_stack_check tasklet_stack_check.c
dpu-lldb

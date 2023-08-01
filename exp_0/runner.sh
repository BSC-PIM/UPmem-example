# source the upmem environment (change the address based on your env)
source ~/lab/CAfPP/UPmem/upmem-2023.2.0-Linux-x86_64/upmem_env.sh simulator

# compile the helloworld.c with upmem compiler
dpu-upmem-dpurte-clang helloworld.c -o helloworld

# compile the host
gcc --std=c99 host.c -o host $(dpu-pkg-config --cflags --libs dpu)

# run the host
./host

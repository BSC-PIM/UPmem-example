DPU_DIR := dpu
HOST_DIR := host

BUILDDIR ?= build
NR_TASKLETS ?= 1
NR_DPUS ?= 1

SHELL:=/bin/bash

define conf_filename
	${BUILDDIR}/.NR_DPUS_$(1)_NR_TASKLETS_$(2).conf
endef

CONF := $(call conf_filename,${NR_DPUS},${NR_TASKLETS})

HOST_TARGET := ${BUILDDIR}/exp00_host
DPU_TARGET := ${BUILDDIR}/exp00_dpu

HOST_SOURCES := $(wildcard ${HOST_DIR}/*.c)
DPU_SOURCES := $(wildcard ${DPU_DIR}/*.c)

.PHONY: all clean test

__dirs := $(shell mkdir -p ${BUILDDIR})

COMMON_INCLUDES := common
COMMON_FLAGS := -Wall -Wextra -Werror -g -I${COMMON_INCLUDES}
DPU_FLAGS := ${COMMON_FLAGS} -O2 -DNR_TASKLETS=${NR_TASKLETS}
HOST_FLAGS := ${COMMON_FLAGS} -std=c11 -O3 `dpu-pkg-config --cflags --libs dpu`  -DNR_TASKLETS=${NR_TASKLETS} -DNR_DPUS=${NR_DPUS}

all: ${HOST_TARGET} ${DPU_TARGET}

${CONF}:
	$(RM) $(call conf_filename,*,*)
	touch ${CONF}


${DPU_TARGET}: ${CONF} ${DPU_SOURCES}
	dpu-upmem-dpurte-clang ${DPU_FLAGS} -o $@ ${DPU_SOURCES}


${HOST_TARGET}: ${CONF} ${HOST_SOURCES}
	 $(CC) -o $@ ${HOST_SOURCES} ${HOST_FLAGS}

clean:
	$(RM) -r $(BUILDDIR)


test: ${HOST_TARGET} ${DPU_TARGET}
	./${HOST_TARGET}

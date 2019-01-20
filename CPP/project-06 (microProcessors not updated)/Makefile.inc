#*****************************************************************************
#
# Copyright 2013,2014 Altera Corporation. All Rights Reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
# 1. Redistributions of source code must retain the above copyright notice,
# this list of conditions and the following disclaimer.
# 
# 2. Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
# 
# 3. Neither the name of the copyright holder nor the names of its contributors
# may be used to endorse or promote products derived from this software without
# specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
# 
#*****************************************************************************

#
# $Id: //acds/rel/16.0/embedded/examples/software/Altera-SoCFPGA-HardwareLib-Timer-CV-GNU/Makefile.inc#2 $
#
ALT_DEVICE ?= CYCLONEV

OBJ_DIR ?= objs_$(COMPILER)_$(ALT_DEVICE)
OBJ     := $(patsubst %.c,$(OBJ_DIR)/%.o,$(C_SRC))
SPL_CV  := u-boot-spl.axf
SPL_A10 := u-boot
DTB_A10 := devicetree.dtb
SOF_A10 := ghrd_10as066n2.sof

SOCEDS_ROOT ?= $(SOCEDS_DEST_ROOT)

ifeq ($(ALT_DEVICE),CYCLONEV)
 ALT_DEVICE_FAMILY ?= soc_cv_av
 SPL := $(SPL_CV)
 SPL_SRC := $(SOCEDS_ROOT)/examples/hardware/cv_soc_devkit_ghrd/software/preloader/uboot-socfpga/spl/u-boot-spl
 ALT_DEV_SHORT := cv
else ifeq ($(ALT_DEVICE),ARRIAV)
 ALT_DEVICE_FAMILY ?= soc_cv_av
 SPL := $(SPL_CV)
 SPL_SRC := $(SOCEDS_ROOT)/examples/hardware/av_soc_devkit_ghrd/software/preloader/uboot-socfpga/spl/u-boot-spl
 ALT_DEV_SHORT := av
else
 ALT_DEVICE_FAMILY ?= soc_a10
 UBOOT_DIR := $(SOCEDS_ROOT)/examples/hardware/a10_soc_devkit_ghrd/software/bootloader_ext_cfg
 SOF_DIR   := $(SOCEDS_ROOT)/examples/hardware/a10_soc_devkit_ghrd/output_files
 SOF       := $(SOF_A10)
 SOF_SRC   := $(SOF_DIR)/$(SOF)
 SPL       := $(SPL_A10)
 SPL_SRC   := $(UBOOT_DIR)/uboot-socfpga/$(SPL)
 DTB       := $(DTB_A10)
 DTB_SRC   := $(UBOOT_DIR)/$(DTB)
 ALT_DEV_SHORT := a10
endif

HWLIBS_ROOT = $(SOCEDS_ROOT)/ip/altera/hps/altera_hps/hwlib

INCLUDE_DIRS := $(BASE_INCLUDES) \
                -I$(HWLIBS_ROOT)/include \
                -I$(HWLIBS_ROOT)/include/$(ALT_DEVICE_FAMILY) \
                -I$(HWLIBS_ROOT)/include/$(ALT_DEVICE_FAMILY)/socal

#VPATH is similar to an include path, but for source files
VPATH = $(HWLIBS_ROOT)/src/hwmgr/:$(HWLIBS_ROOT)/src/hwmgr/$(ALT_DEVICE_FAMILY):$(HWLIBS_ROOT)/src/utils

ifeq ($(COMPILER), GNU)
 CROSS_COMPILE := arm-altera-eabi-
 CC := $(CROSS_COMPILE)gcc
 LD := $(CROSS_COMPILE)g++
 NM := $(CROSS_COMPILE)nm
 OD := $(CROSS_COMPILE)objdump
 OC := $(CROSS_COMPILE)objcopy
 ifeq ($(ALT_DEVICE_FAMILY),soc_cv_av)
  LINKER_SCRIPT := cycloneV-dk-ram-hosted.ld
 else
  LINKER_SCRIPT := linkerscripts/arria10-dk-oc-ram-hosted.ld
 endif
 MULTILIBFLAGS := -mcpu=cortex-a9 -mfloat-abi=softfp -mfpu=neon
 CFLAGS  := -g -O0 -Wall $(MULTILIBFLAGS) $(INCLUDE_DIRS) -D$(ALT_DEVICE_FAMILY) -D$(ALT_DEVICE)
 LDFLAGS := -T$(LINKER_SCRIPT) $(MULTILIBFLAGS) 
 ODFLAGS := -DS
 OCFLAGS := -O binary #Note - This line MUST end with a space
else
 CC := armcc
 AS := armasm
 LD := armlink
 AR := armar
 OD := fromelf
 OC := fromelf
 LINKER_SCRIPT := linkerscripts/$(ALT_DEVICE_FAMILY)-scatter.scat
 MULTILIBFLAGS := --diag_error=warning --diag_suppress=9931 --cpu=Cortex-A9 --no_unaligned_access
 CFLAGS   := -g -O0 --strict $(MULTILIBFLAGS) $(INCLUDE_DIRS) -D$(ALT_DEVICE_FAMILY) -D$(ALT_DEVICE)
 ASMFLAGS := -g $(MULTILIBFLAGS)
 LDFLAGS  := --strict $(MULTILIBFLAGS) --entry=alt_interrupt_vector --scatter=$(LINKER_SCRIPT)
 OBJ      := $(OBJ_DIR)/alt_interrupt_armcc.o $(OBJ)
 ODFLAGS  := --text -c -s -d
 OCFLAGS  := --bin --output=
endif

ifeq ($(or $(COMSPEC),$(ComSpec)),)
 RM := rm -rf
else
 RM := cs-rm -rf
endif
CP := cp -f

.PHONY: all
all: $(ELF) $(SPL) $(DTB) debug-hosted.ds

.PHONY: clean
clean:
	$(RM) $(OBJ_DIR) $(ELF) *.objdump *.map $(SPL_CV) $(SPL_A10) $(DTB_A10)

.PHONY: help
help:
	@echo "make ALT_DEVICE=(CYCLONEV/ARRIAV/ARRIA10) COMPILER=(ARMCC/GNU)"

$(OBJ_DIR) :
	mkdir $@

$(OBJ_DIR)/%.o: %.c $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/alt_interrupt_armcc.o: alt_interrupt_armcc.s $(OBJ_DIR)
	$(AS) $(ASMFLAGS) $< -o $@

$(ELF): $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $@
	$(OD) $(ODFLAGS) $@ > $@.objdump

$(SPL): $(SPL_SRC)
	$(CP) $< $@

$(DTB_A10): $(DTB_SRC)
	$(CP) $< $@

$(SOF_A10): $(SOF_SRC)
	$(CP) $< $@

debug-hosted.ds: debug-$(ALT_DEV_SHORT).ds
	$(CP) $< $@

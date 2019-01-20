#include "tie_ui_connection.h"

void tie_ui_connection_init(){
	#define ALT_RSTMGR_BASE_ADDR  0xffd05000
	#define ALT_RSTMGR_BRGMODRST_OFFSET 0x0000001c
	#define ALT_RSTMGR_BRGMODRST_ADDR (ALT_RSTMGR_BASE_ADDR+ALT_RSTMGR_BRGMODRST_OFFSET)
	#define ALT_RSTMGR_BRGMODRST_LWH2F_SET_MSK 0x00000002

	#define ALT_L3REGS_BASE_ADDR 0xFF800000
	#define ALT_L3REGS_REMAP_OFFSET 0x00000000
	#define ALT_L3REGS_REMAP_ADDR (ALT_L3REGS_BASE_ADDR+ALT_L3REGS_REMAP_OFFSET)

	// initialize HPS2FPGA lightweight bridge

	// set LW to reset
	*((volatile unsigned int*)ALT_RSTMGR_BRGMODRST_ADDR) = *((volatile unsigned int*)ALT_RSTMGR_BRGMODRST_ADDR) | ALT_RSTMGR_BRGMODRST_LWH2F_SET_MSK;

	// L4 MP clock should be checked here, but we cannot really do anything about it, so we will anycase fail

	// release LW from reset
	*((volatile unsigned int*)ALT_RSTMGR_BRGMODRST_ADDR) = *((volatile unsigned int*)ALT_RSTMGR_BRGMODRST_ADDR) & ~(ALT_RSTMGR_BRGMODRST_LWH2F_SET_MSK);

	// bit[0] = 0 set Boot ROM to address 0x0 for the MPU L3 master
	// bit[1] = 1 set On-chip RAM to address 0x0 for the non-MPU L3 masters
	// bit[2] = 0 N/A
	// bit[3] = 1 set HPS2FPGA AXI bridge visible
	// bit[4] = 1 set LW HPS2FPGA AXI bridge visible
	// -> 0x1A (0b00011010)
	*((volatile unsigned int*)ALT_L3REGS_REMAP_ADDR) = 0x0000001A;
}

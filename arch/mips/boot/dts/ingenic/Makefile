# SPDX-License-Identifier: GPL-2.0
dtb-$(CONFIG_JZ4740_QI_LB60)	+= qi_lb60.dtb
dtb-$(CONFIG_JZ4740_RS90)	+= rs90.dtb
dtb-$(CONFIG_JZ4770_GCW0)	+= gcw0.dtb
dtb-$(CONFIG_JZ4780_CI20)	+= ci20.dtb
dtb-$(CONFIG_X1000_CU1000_NEO)	+= cu1000-neo.dtb
dtb-$(CONFIG_X1830_CU1830_NEO)	+= cu1830-neo.dtb
dtb-$(CONFIG_DT_T40_SHARK)	+= shark.dtb
dtb-$(CONFIG_DT_T31_SWAN)	+= swan.dtb
dtb-$(CONFIG_DT_T31_ZRT)	+= zrt.dtb
dtb-$(CONFIG_DT_HALLEY2_V20)	+= halley2v20.dtb
dtb-$(CONFIG_DT_SEAL)		+= seal.dtb
dtb-$(CONFIG_DT_X2000_V12_FPGA)	+= x2000_v12_fpga.dtb
dtb-$(CONFIG_DT_T41_FPGA)	+= t41_fpga.dtb

ifdef CONFIG_FAST_BOOT
dtb-$(CONFIG_DT_T40_SHARK)	+= shark_fast.dtb
else
dtb-$(CONFIG_DT_T40_SHARK)	+= shark.dtb
endif

dtb-$(CONFIG_DT_T41_MARMOT)	+= marmot.dtb
obj-y				+= $(patsubst %.dtb, %.dtb.o, $(dtb-y))


obj-$(CONFIG_BUILTIN_DTB)	+= $(addsuffix .o, $(dtb-y))

# SPDX-License-Identifier: (GPL-2.0-or-later OR BSD-3-Clause)
#
# Copyright (C) 2022-2023 SudoMaker
# Author: Reimu NotMoe <reimu@sudomaker.com>
#

cflags-y			+= -I$(srctree)/include/linux/
cflags-y			+= -I$(srctree)/arch/mips/ingenic/include/


# SMP support
obj-$(CONFIG_SMP) += smp.o
obj-$(CONFIG_SMP) += smp-entry.o

obj-$(CONFIG_MACH_INGENIC)		+= board-ingenic.o early_printk.o
obj-$(CONFIG_MACH_X1000)		+= regs_save_restore.o pm_x1000.o
#cflags-y						+= -I$(srctree)/arch/mips/ingenic/include/
#LINUXINCLUDE	+=  -include $(srctree)/arch/mips/ingenic/include/nanoprintf.h
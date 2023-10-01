// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#include <linux/clk.h>
#include <linux/clocksource.h>
#include <linux/init.h>
#include <linux/irqchip.h>
#include <linux/of_clk.h>
#include <linux/of_fdt.h>

#include <asm/bootinfo.h>
#include <asm/fw/fw.h>
#include <asm/irq_cpu.h>
#include <asm/machine.h>
#include <asm/mips-cps.h>
#include <asm/prom.h>
#include <asm/smp-ops.h>
#include <asm/time.h>

#include <linux/moduleparam.h>
#include <linux/serial_reg.h>
#include <asm/setup.h>
#include <asm/io.h>

extern void super_early_printk(char *str);

/*** Super early printk code 

#define	UART0_IOBASE	0x10030000
#define	UART1_IOBASE	0x10031000
#define	UART2_IOBASE	0x10032000
#define UART_OFF	(0x1000)

static void check_uart(char c);

static volatile u32 *uart_base;
typedef void (*putchar_f_t)(char);

static putchar_f_t putchar_f = check_uart;

static void putchar(char ch)
{
	int timeout = 10000;
	volatile u32 *base = uart_base;

	// Wait for fifo to shift out some bytes 
	while ((base[UART_LSR] & (UART_LSR_THRE | UART_LSR_TEMT))
	       != (UART_LSR_THRE | UART_LSR_TEMT) && timeout--)
		;
	base[UART_TX] = (u8)ch;
}

static void putchar_dummy(char ch)
{
	return;
}

static void check_uart(char c)
{
	// We Couldn't use ioremap() here
	volatile u32 *base = (volatile u32*)CKSEG1ADDR(UART1_IOBASE);
	int i;
	for(i=0; i < 3; i++) {
		if(base[UART_LCR])
			break;
		base += (UART_OFF/sizeof(u32));
	}

	if(i < 3) {
		uart_base = base;
		putchar_f = putchar;
		putchar_f(c);
	} else {
		putchar_f = putchar_dummy;
	}
}

void super_early_printk(char *str)
{
	int i;
	for(i=0; str[0] != 0; i++)
	{
		check_uart(str[i]);
	}
}

Super early printk code end ***/

static __initconst const void *fdt;
static __initconst const struct mips_machine *mach;
static __initconst const void *mach_match_data;

void __init prom_init(void)
{
	super_early_printk("Ingenic SoC Hello from Kernel 6.4-rc3\n");

	plat_get_fdt();
	BUG_ON(!fdt);
}

void __init *plat_get_fdt(void)
{
	const struct mips_machine *check_mach;
	const struct of_device_id *match;

	super_early_printk("plat_get_fdt()\n");

	if (fdt)
		/* Already set up */
		return (void *)fdt;

	fdt = (void *)get_fdt();
	if (fdt && !fdt_check_header(fdt)) {
		/*
		 * We have been provided with the appropriate device tree for
		 * the board. Make use of it & search for any machine struct
		 * based upon the root compatible string.
		 */
		for_each_mips_machine(check_mach) {
			match = mips_machine_is_compatible(check_mach, fdt);
			if (match) {
				mach = check_mach;
				mach_match_data = match->data;
				break;
			}
		}
	} else if (IS_ENABLED(CONFIG_LEGACY_BOARDS)) {
		/*
		 * We weren't booted using the UHI boot protocol, but do
		 * support some number of boards with legacy boot protocols.
		 * Attempt to find the right one.
		 */
		for_each_mips_machine(check_mach) {
			if (!check_mach->detect)
				continue;

			if (!check_mach->detect())
				continue;

			mach = check_mach;
		}

		/*
		 * If we don't recognise the machine then we can't continue, so
		 * die here.
		 */
		BUG_ON(!mach);

		/* Retrieve the machine's FDT */
		fdt = mach->fdt;
	}
	return (void *)fdt;
}

#ifdef CONFIG_RELOCATABLE

void __init plat_fdt_relocated(void *new_location)
{

	super_early_printk("plat_fdt_relocated()\n");
	/*
	 * reset fdt as the cached value would point to the location
	 * before relocations happened and update the location argument
	 * if it was passed using UHI
	 */
	fdt = NULL;

	if (fw_arg0 == -2)
		fw_arg1 = (unsigned long)new_location;
}

#endif /* CONFIG_RELOCATABLE */

void __init plat_mem_setup(void)
{
	super_early_printk("plat_mem_setup()\n");

	if (mach && mach->fixup_fdt)
		fdt = mach->fixup_fdt(fdt, mach_match_data);

	fw_init_cmdline();
	__dt_setup_arch((void *)fdt);
}

void __init device_tree_init(void)
{
	super_early_printk("device_tree_init()\n");

	unflatten_and_copy_device_tree();
	mips_cpc_probe();

	if (!register_cps_smp_ops())
		return;
	if (!register_vsmp_smp_ops())
		return;

	register_up_smp_ops();
}

int __init apply_mips_fdt_fixups(void *fdt_out, size_t fdt_out_size,
				 const void *fdt_in,
				 const struct mips_fdt_fixup *fixups)
{
	int err;

	super_early_printk("apply_mips_fdt_fixups()\n");

	err = fdt_open_into(fdt_in, fdt_out, fdt_out_size);
	if (err) {
		pr_err("Failed to open FDT\n");
		return err;
	}

	for (; fixups->apply; fixups++) {
		err = fixups->apply(fdt_out);
		if (err) {
			pr_err("Failed to apply FDT fixup \"%s\"\n",
			       fixups->description);
			return err;
		}
	}

	err = fdt_pack(fdt_out);
	if (err)
		pr_err("Failed to pack FDT\n");
	return err;
}

void __init plat_time_init(void)
{
	struct device_node *np;
	struct clk *clk;

	super_early_printk("plat_time_init()\n");

	of_clk_init(NULL);

	if (!cpu_has_counter) {
		mips_hpt_frequency = 0;
	} else if (mach && mach->measure_hpt_freq) {
		mips_hpt_frequency = mach->measure_hpt_freq();
	} else {
		np = of_get_cpu_node(0, NULL);
		if (!np) {
			pr_err("Failed to get CPU node\n");
			return;
		}

		clk = of_clk_get(np, 0);
		if (IS_ERR(clk)) {
			pr_err("Failed to get CPU clock: %ld\n", PTR_ERR(clk));
			return;
		}

		mips_hpt_frequency = clk_get_rate(clk);
		clk_put(clk);

		switch (boot_cpu_type()) {
		case CPU_20KC:
		case CPU_25KF:
			/* The counter runs at the CPU clock rate */
			break;
		default:
			/* The counter runs at half the CPU clock rate */
			mips_hpt_frequency /= 2;
			break;
		}
	}

	timer_probe();
}

void __init arch_init_irq(void)
{
	struct device_node *intc_node;

	super_early_printk("arch_init_irq()\n");

	intc_node = of_find_compatible_node(NULL, NULL,
					    "mti,cpu-interrupt-controller");
	if (!cpu_has_veic && !intc_node)
		mips_cpu_irq_init();
	of_node_put(intc_node);

	irqchip_init();
}

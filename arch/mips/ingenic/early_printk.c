// SPDX-License-Identifier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2023
 */

#include <linux/cpu.h>
#include <linux/serial_reg.h>
#include <asm/setup.h>

#define	UART0_IOBASE	0x10030000
//#define	UART1_IOBASE	0x10031000
//#define	UART2_IOBASE	0x10032000
#define UART_OFF	(0x1000)

static void check_uart(char c);

static volatile u32 *uart_base;
typedef void (*putchar_f_t)(char);

static putchar_f_t putchar_f = check_uart;

static void putchar(char ch)
{
	int timeout = 10000;
	volatile u32 *base = uart_base;

	/* Wait for fifo to shift out some bytes */
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
	/* We Couldn't use ioremap() here */
	volatile u32 *base = (volatile u32*)CKSEG1ADDR(UART0_IOBASE);
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

void prom_putchar(char c)
{
	putchar_f(c);
}

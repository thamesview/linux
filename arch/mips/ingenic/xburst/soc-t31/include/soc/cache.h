#ifndef __CHIP_CACHE_H__
#define __CHIP_CACHE_H__
#include <asm/cacheops.h>
#include <asm/r4kcache.h>

#define Index_Prefetch_I        0x1c


#define cache_prefetch(label,size)					\
do{									\
	unsigned long addr,end;						\
	/* Prefetch codes from label */					\
	addr = (unsigned long)(&&label) & ~(32 - 1);			\
	end = (unsigned long)(&&label + size) & ~(32 - 1);		\
	end += 32;							\
	for (; addr < end; addr += 32) {				\
		__asm__ volatile (					\
				".set push       \n\t"			\
				".set mips32     \n\t"			\
				" cache %0, 0(%1)\n\t"			\
				".set pop        \n\t"			\
				:					\
				: "I" (Index_Prefetch_I), "r"(addr));	\
	}								\
}									\
while(0)

#define K0BASE			KSEG0
#define CFG_DCACHE_SIZE		32768
#define CFG_ICACHE_SIZE		32768
#define CFG_CACHELINE_SIZE	32

static inline void __jz_flush_cache_all(void)
{
	register unsigned long addr;
	/* Clear CP0 TagLo */
	asm volatile ("mtc0 $0, $28\n\t");
	for (addr = K0BASE; addr < (K0BASE + CFG_DCACHE_SIZE); addr += CFG_CACHELINE_SIZE) {
		asm volatile (".set mips32\n\t"
					  " cache %0, 0(%1)\n\t"
					  ".set mips32\n\t"
					  :
					  : "I" (Index_Writeback_Inv_D), "r"(addr));
	}

	for (addr = K0BASE; addr < (K0BASE + CFG_ICACHE_SIZE); addr += CFG_CACHELINE_SIZE) {
		asm volatile (".set mips32\n\t"
					  " cache %0, 0(%1)\n\t"
					  ".set mips32\n\t"
					  :
					  : "I" (Index_Invalidate_I), "r"(addr));
	}

	/* invalidate BTB */
	asm volatile (
			".set mips32\n\t"
			" mfc0 $26, $16, 7\n\t"
			" nop\n\t"
			" ori $26, 2\n\t"
			" mtc0 $26, $16, 7\n\t"
			" nop\n\t"
			".set mips32\n\t"
		     );
	asm volatile ("sync\n\t"
				  "lw $0,0(%0)"
				  ::"r" (0xa0000000));
}

static inline void __jz_cache_init(void)
{
	register unsigned long addr;
	asm volatile ("mtc0 $0, $28\n\t"::);

	for (addr = K0BASE; addr < (K0BASE + CFG_DCACHE_SIZE); addr += CFG_CACHELINE_SIZE) {
		asm volatile (".set mips32\n\t"
				" cache %0, 0(%1)\n\t"
				".set mips32\n\t"
				:
				: "I" (Index_Store_Tag_D), "r"(addr));
	}
	for (addr = K0BASE; addr < (K0BASE + CFG_ICACHE_SIZE); addr += CFG_CACHELINE_SIZE) {
		asm volatile (".set mips32\n\t"
				" cache %0, 0(%1)\n\t"
				".set mips32\n\t"
				:
				: "I" (Index_Store_Tag_I), "r"(addr));
	}
	/* invalidate BTB */
	asm volatile (  ".set mips32\n\t"
			" mfc0 $26, $16, 7\n\t"
			" nop\n\t"
			" ori $26, 2\n\t"
			" mtc0 $26, $16, 7\n\t"
			" nop\n\t"
			"nop\n\t"
			".set mips32\n\t"
		    );
}


#endif /* __CHIP_CACHE_H__ */

#ifndef _DDR_H_
#define _DDR_H_

#define DDRC_BASE   0xb34f0000
#define DDR_PHY_OFFSET  (-0x4e0000 + 0x1000)
#define DDRC_APB_OFFSET (-0x4e0000 + 0x2000)

#define DDRC_STATUS         0x0
#define DDRC_CFG            0x8
#define DDRC_CTRL           0x10
#define DDRC_LMR            0x18
#define DDRC_DLP            0x20
#define DDRC_AUTOSR_EN      0x28
#define DDRC_AUTOSR_CNT     0x30
#define DDRC_REFCNT         0x38
#define DDRC_TIMING(n)      (0x40 + 8 * (n - 1))
#define DDRC_MMAP0          0x78
#define DDRC_MMAP1          0x80
#define DDRC_BWCFG          0x88
#define DDRC_BWSTP          0x90
#define DDRC_BWP0WR         0x98
#define DDRC_BWP1WR         0xa8
#define DDRC_BWP2WR         0xb8
#define DDRC_BWP3WR         0xc8
#define DDRC_HREGPRO        0xd8
#define DDRC_DBGEN          0xE0
#define DDRC_DBGINFO        0xE8
#define DDRC_DWCFG          (DDRC_APB_OFFSET + 0x00)

#define DDRP_PIR_INIT		(1 << 0)
#define DDRP_PIR_DLLSRST	(1 << 1)
#define DDRP_PIR_DLLLOCK	(1 << 2)
#define DDRP_PIR_ZCAL   	(1 << 3)
#define DDRP_PIR_ITMSRST   	(1 << 4)
#define DDRP_PIR_DRAMRST   	(1 << 5)
#define DDRP_PIR_DRAMINT   	(1 << 6)
#define DDRP_PIR_QSTRN   	(1 << 7)
#define DDRP_PIR_EYETRN   	(1 << 8)
#define DDRP_PIR_DLLBYP   	(1 << 17)
#define DDRP_PIR_LOCKBYP   	(1 << 29)
#define DDRP_PGSR_IDONE		(1 << 0)
#define DDRP_PGSR_DLDONE	(1 << 1)
#define DDRP_PGSR_ZCDONE	(1 << 2)
#define DDRP_PGSR_DIDONE	(1 << 3)
#define DDRP_PGSR_DTDONE	(1 << 4)
#define DDRP_PGSR_DTERR 	(1 << 5)
#define DDRP_PGSR_DTIERR 	(1 << 6)
#define DDRP_PGSR_DFTEERR 	(1 << 7)
#define DDRC_AUTOSR_ENABLE	(1 << 0)


#define DDRP_PIR	(DDR_PHY_OFFSET + 0x4) /* PHY Initialization Register */
#define DDRP_PGCR   (DDR_PHY_OFFSET + 0x8) /* PHY General Configuration Register*/
#define DDRP_PGSR	(DDR_PHY_OFFSET + 0xc) /* PHY General Status Register*/
#define DDRP_DLLGCR (DDR_PHY_OFFSET + 0x10) /* DLL General Control Register*/
#define DDRP_ACDLLCR    (DDR_PHY_OFFSET + 0x14) /* AC DLL Control Register*/
#define DDRP_PTR0   (DDR_PHY_OFFSET + 0x18) /* PHY Timing Register 0 */
#define DDRP_PTR1   (DDR_PHY_OFFSET + 0x1c) /* PHY Timing Register 1 */
#define DDRP_PTR2   (DDR_PHY_OFFSET + 0x20) /* PHY Timing Register 2 */
#define DDRP_ACIOCR (DDR_PHY_OFFSET + 0x24) /* AC I/O Configuration Register */
#define DDRP_DXCCR  (DDR_PHY_OFFSET + 0x28) /* DATX8 Common Configuration Register */
#define DDRP_DSGCR  (DDR_PHY_OFFSET + 0x2c) /* DDR System General Configuration Register */
#define DDRP_DCR    (DDR_PHY_OFFSET + 0x30) /* DRAM Configuration Register*/

#define DDRP_DTPR0  (DDR_PHY_OFFSET + 0x34) /* DRAM Timing Parameters Register 0 */
#define DDRP_DTPR1  (DDR_PHY_OFFSET + 0x38) /* DRAM Timing Parameters Register 1 */
#define DDRP_DTPR2  (DDR_PHY_OFFSET + 0x3c) /* DRAM Timing Parameters Register 2 */
#define DDRP_MR0    (DDR_PHY_OFFSET + 0x40) /* Mode Register 0 */
#define DDRP_MR1    (DDR_PHY_OFFSET + 0x44) /* Mode Register 1 */
#define DDRP_MR2    (DDR_PHY_OFFSET + 0x48) /* Mode Register 2 */
#define DDRP_MR3    (DDR_PHY_OFFSET + 0x4c) /* Mode Register 3 */
#define DDRP_ODTCR  (DDR_PHY_OFFSET + 0x50) /* ODT Configure Register */
#define DDRP_DTAR   (DDR_PHY_OFFSET + 0x54) /* Data Training Address Register */
#define DDRP_DTDR0  (DDR_PHY_OFFSET + 0x58) /* Data Training Data Register 0 */
#define DDRP_DTDR1  (DDR_PHY_OFFSET + 0x5c) /* Data Training Data Register 1 */

#define DDRP_DCUAR  (DDR_PHY_OFFSET + 0xc0) /* DCU Address Register */
#define DDRP_DCUDR  (DDR_PHY_OFFSET + 0xc4) /* DCU Data Register */
#define DDRP_DCURR  (DDR_PHY_OFFSET + 0xc8) /* DCU Run Register */
#define DDRP_DCULR  (DDR_PHY_OFFSET + 0xcc) /* DCU Loop Register */
#define DDRP_DCUGCR (DDR_PHY_OFFSET + 0xd0) /* DCU Gerneral Configuration Register */
#define DDRP_DCUTPR (DDR_PHY_OFFSET + 0xd4) /* DCU Timing Parameters Register */
#define DDRP_DCUSR0 (DDR_PHY_OFFSET + 0xd8) /* DCU Status Register 0 */
#define DDRP_DCUSR1 (DDR_PHY_OFFSET + 0xdc) /* DCU Status Register 1 */

#define DDRP_DXGCR(n)   (DDR_PHY_OFFSET + 0x1c0 + n * 0x40) /* DATX8 n General Configuration Register */
#define DDRP_DXGSR0(n)  (DDR_PHY_OFFSET + 0x1c4 + n * 0x40) /* DATX8 n General Status Register */
#define DDRP_DXGSR1(n)  (DDR_PHY_OFFSET + 0x1c8 + n * 0x40) /* DATX8 n General Status Register */
#define DDRP_DXDLLCR(n) (DDR_PHY_OFFSET + 0x1cc + n * 0x40) /* DATX8 n General Status Register */
#define DDRP_DXDQSTR(n) (DDR_PHY_OFFSET + 0x1d4 + n * 0x40) /* DATX8 n DQS Timing Register */
#define DDRP_ZQXCR0(n)  (DDR_PHY_OFFSET + 0x180 + n * 0x10) /* ZQ impedance Control Register 0 */
#define DDRP_ZQXCR1(n)  (DDR_PHY_OFFSET + 0x184 + n * 0x10) /* ZQ impedance Control Register 1 */
#define DDRP_ZQXSR0(n)  (DDR_PHY_OFFSET + 0x188 + n * 0x10) /* ZQ impedance Status Register 0 */
#define DDRP_ZQXSR1(n)  (DDR_PHY_OFFSET + 0x18c + n * 0x10) /* ZQ impedance Status Register 1 */


#define DDRP_INNOPHY_PLL_CTRL       (DDR_PHY_OFFSET + 0x14c)
#define DDRP_DX0GSR     (DDR_PHY_OFFSET + 0x71 * 4)

#define DDRC_STATUS			0x0
#define DDRC_CFG			0x8
#define DDRC_CTRL			0x10
#define DDRC_STRB			0x34
#define DDRC_REMAP(n)           (0x9c + 4 * (n - 1))


#define DDRP_DXnDQSTR(n)     (DDR_PHY_OFFSET + (0x10 * n + 0x75) * 4)
#define DDRP_DXnDQTR(n)      (DDR_PHY_OFFSET + (0x10 * n + 0x74) * 4)

#ifndef REG32
#define REG32(x) *(volatile unsigned int *)(x)
#endif

#define ddr_writel(value, reg)	REG32(DDRC_BASE + reg) = (value)
#define ddr_readl(reg)		REG32(DDRC_BASE + reg)



#endif /* _DDR_H_ */

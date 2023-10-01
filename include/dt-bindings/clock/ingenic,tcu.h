/* SPDX-License-Identifier: GPL-2.0 */
/*
 * This header provides clock numbers for the ingenic,tcu DT binding.
 */

#ifndef __DT_BINDINGS_CLOCK_INGENIC_TCU_H__
#define __DT_BINDINGS_CLOCK_INGENIC_TCU_H__

#define TCU_CLK_TIMER0	0
#define TCU_CLK_TIMER1	1
#define TCU_CLK_TIMER2	2
#define TCU_CLK_TIMER3	3
#define TCU_CLK_TIMER4	4
#define TCU_CLK_TIMER5	5
#define TCU_CLK_TIMER6	6
#define TCU_CLK_TIMER7	7
#define TCU_CLK_WDT	8
#define TCU_CLK_OST	9

#define TCU_MODE1				1
#define TCU_MODE2				2

#define PWM_FUNC				1
#define TRACKBALL_FUNC				2
#define PWM_AND_TRACKBALL_FUNC		(PWM_FUNC | TRACKBALL_FUNC)

#define NO_PWM_IN			0
#define PWM_IN				1


#define CHANNEL_BASE_OFF 4
#define CHANNEL_ID_OFF 0
#define CHANNEL_MODE_OFF (CHANNEL_ID_OFF + CHANNEL_BASE_OFF*2)
#define CHANNEL_FUNC_OFF (CHANNEL_MODE_OFF + CHANNEL_BASE_OFF)
#define CHANNEL_IN_OFF (CHANNEL_FUNC_OFF + CHANNEL_BASE_OFF)

#define CHANNEL_INFO(ID, MODE, FUNC, IN)			\
	((ID << CHANNEL_ID_OFF)|(MODE << CHANNEL_MODE_OFF)	\
	 |(FUNC << CHANNEL_FUNC_OFF)|(IN << CHANNEL_IN_OFF))

#endif /* __DT_BINDINGS_CLOCK_INGENIC_TCU_H__ */

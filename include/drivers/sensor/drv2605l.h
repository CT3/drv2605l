/*
 * Copyright (c) 2022 Circuit Dojo LLC
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_DRIVERS_RTC_DRV2605L_DRV2605L_H_
#define ZEPHYR_DRIVERS_RTC_DRV2605L_DRV2605L_H_

#include <zephyr/kernel.h>
#include <zephyr/drivers/i2c.h>
#include <time.h>

#define DRV2605L_BCD_UPPER_SHIFT 4
#define DRV2605L_BCD_LOWER_MASK 0x0f
#define DRV2605L_BCD_UPPER_MASK 0xf0
#define DRV2605L_BCD_UPPER_MASK_SEC 0x70

#define DRV2605L_CTRL1 0x00
#define DRV2605L_CTRL1_EXT_TEST BIT(7)
#define DRV2605L_CTRL1_STOP BIT(5)
#define DRV2605L_CTRL1_SR BIT(4)
#define DRV2605L_CTRL1_CIE BIT(2)
#define DRV2605L_CTRL1_12_24 BIT(1)
#define DRV2605L_CTRL1_CAP_SEL BIT(0)

#define DRV2605L_CTRL2 0x01
#define DRV2605L_CTRL2_AIE BIT(7)
#define DRV2605L_CTRL2_AF BIT(6)
#define DRV2605L_CTRL2_MI BIT(5)
#define DRV2605L_CTRL2_HMI BIT(4)
#define DRV2605L_CTRL2_TF BIT(3)

/* CLKOUT frequency selection */
#define DRV2605L_CTRL2_COF_32K 0x0
#define DRV2605L_CTRL2_COF_16K 0x1
#define DRV2605L_CTRL2_COF_8K 0x2
#define DRV2605L_CTRL2_COF_4K 0x3
#define DRV2605L_CTRL2_COF_2K 0x4
#define DRV2605L_CTRL2_COF_1K 0x5
#define DRV2605L_CTRL2_COF_1 0x6
#define DRV2605L_CTRL2_COF_LOW 0x7

/* Offset register related */
#define DRV2605L_OFFSET 0x02
#define DRV2605L_OFFSET_MODE BIT(7)
#define DRV2605L_OFFSET_VALUE_MASK 0x7f
#define DRV2605L_OFFSET_MODE_NORMAL 0
#define DRV2605L_OFFSET_MODE_COURSE 1

#define DRV2605L_RAM_BYTE 0x03
#define DRV2605L_TENS_SHIFT 4

/* Time related */
#define DRV2605L_SECONDS 0x04
#define DRV2605L_SECONDS_OS BIT(7)
#define DRV2605L_SECONDS_MASK 0x7f

#define DRV2605L_MINUTES 0x05
#define DRV2605L_MINUTES_MASK 0x7f

#define DRV2605L_HOURS 0x06
#define DRV2605L_HOURS_AM_PM BIT(5)
#define DRV2605L_HOURS_MASK 0x3f

#define DRV2605L_DAYS 0x07
#define DRV2605L_DAYS_MASK 0x3f

#define DRV2605L_WEEKDAYS 0x08
#define DRV2605L_WEEKDAYS_MASK 0x7
#define DRV2605L_WEEKDAYS_SUN 0x0
#define DRV2605L_WEEKDAYS_MON 0x1
#define DRV2605L_WEEKDAYS_TUE 0x2
#define DRV2605L_WEEKDAYS_WED 0x3
#define DRV2605L_WEEKDAYS_THU 0x4
#define DRV2605L_WEEKDAYS_FRI 0x5
#define DRV2605L_WEEKDAYS_SAT 0x6

#define DRV2605L_MONTHS 0x09
#define DRV2605L_MONTHS_MASK 0x1f
#define DRV2605L_MONTHS_JAN 0x1
#define DRV2605L_MONTHS_FEB 0x2
#define DRV2605L_MONTHS_MAR 0x3
#define DRV2605L_MONTHS_APR 0x4
#define DRV2605L_MONTHS_MAY 0x5
#define DRV2605L_MONTHS_JUN 0x6
#define DRV2605L_MONTHS_JUL 0x7
#define DRV2605L_MONTHS_AUG 0x8
#define DRV2605L_MONTHS_SEP 0x9
#define DRV2605L_MONTHS_OCT 0x10
#define DRV2605L_MONTHS_NOV 0x11
#define DRV2605L_MONTHS_DEC 0x12

#define DRV2605L_YEARS 0x0a

/* Alarm related */
#define DRV2605L_SECOND_ALARM 0x0b
#define DRV2605L_SECOND_ALARM_EN BIT(7)

#define DRV2605L_MINUTE_ALARM 0x0c
#define DRV2605L_MINUTE_ALARM_EN BIT(7)

#define DRV2605L_HOUR_ALARM 0x0d
#define DRV2605L_HOUR_ALARM_EN BIT(7)
#define DRV2605L_HOUR_ALARM_AM_PM BIT(5)

#define DRV2605L_DAY_ALARM 0x0e
#define DRV2605L_DAY_ALARM_EN BIT_MASK(7)

#define DRV2605L_WEEKDAY_ALARM 0x0f
#define DRV2605L_WEEKDAY_ALARM_EN BIT(7)

/* Timer registers */
#define DRV2605L_TIMER_VALUE 0x10
#define DRV2605L_TIMER_MODE 0x11
#define DRV2605L_TIMER_MODE_FREQ_MASK BIT(4) | BIT(3)
#define DRV2605L_TIMER_MODE_FREQ_SHIFT 3
#define DRV2605L_TIMER_MODE_FREQ_4K 0x0
#define DRV2605L_TIMER_MODE_FREQ_64 0x1
#define DRV2605L_TIMER_MODE_FREQ_1 0x2
#define DRV2605L_TIMER_MODE_FREQ_1_60 0x3
#define DRV2605L_TIMER_MODE_EN BIT(2)
#define DRV2605L_TIMER_MODE_INT_EN BIT(1)
#define DRV2605L_TIMER_MODE_INT_TI_TP BIT(0)

/* Capacitor values */
#define DRV2605L_CAP_VALUE_7PF	0
#define DRV2605L_CAP_VALUE_12_5PF	1

struct drv2605l_data
{
	const struct i2c_dt_spec i2c;
};

int drv2605l_init(const struct device *dev);

/*
 * Future
 *
 * int drv2605l_osc_en(bool enabled);
 * int drv2605l_set_timer(uint8_t seconds);
 * int drv2605l_timer_en(bool enabled);
 */

int drv2605l_set_cap_sel(const struct device *dev, uint8_t cap_value);
int drv2605l_set_offset_mode(const struct device *dev, uint8_t offset_mode_value);
int drv2605l_set_offset_value(const struct device *dev, uint8_t offset_value);
int drv2605l_set_time(const struct device *dev, const struct tm *time);
int drv2605l_get_time(const struct device *dev, struct tm *time);

#endif /* ZEPHYR_DRIVERS_RTC_DRV2605L_DRV2605L_H_ */

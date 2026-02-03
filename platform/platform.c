/*
 * platform.c
 *
 *  Created on: Jan 30, 2026
 *      Author: manhhai
 */

#include "platform.h"

char platform_init ()
{
	platform_system_init();
	platform_spi_init();
	platform_i2c_init();
	return 0;
}

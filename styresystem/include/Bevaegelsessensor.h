#ifndef BEVAEGELSESSENSOR_H_
#define BEVAEGELSESSENSOR_H_

#include <stdint.h>

extern volatile uint8_t g_bevaegelse_set_flag;

extern "C" {
	void init_bevaegelsessensor(void);
}

#endif
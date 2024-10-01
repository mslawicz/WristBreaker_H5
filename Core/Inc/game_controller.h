#ifndef __GAME_CONTROLLER_H
#define __GAME_CONTROLLER_H

#include "main.h"

#ifdef __cplusplus
 extern "C" {
#endif

#define GAME_CTRL_EVENT_TIMER_TRIG  ((uint32_t)(1 << 0))

void gameController(void);


#ifdef __cplusplus
}
#endif
#endif /* __GAME_CONTROLLER_H__ */
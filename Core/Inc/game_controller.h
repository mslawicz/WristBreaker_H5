#ifndef __GAME_CONTROLLER_H
#define __GAME_CONTROLLER_H

#include "main.h"
#include "ux_api.h"

#ifdef __cplusplus
 extern "C" {
#endif

#define GAME_CTRL_EVENT_TIMER_TRIG  ((uint32_t)(1 << 0))
#define GAME_CTRL_EVENT_GEN_INP  ((uint32_t)(2 << 0))

extern TX_EVENT_FLAGS_GROUP gameControllerEvents;
extern TIM_HandleTypeDef* pMotor_X_Timer;

void gameController(void);


#ifdef __cplusplus
}
#endif
#endif /* __GAME_CONTROLLER_H__ */
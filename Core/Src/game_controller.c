#include "game_controller.h"
#include "logger.h"
#include "ux_device_class_hid.h"
#include "ux_device_descriptors.h"
#include "ux_device_customhid.h"

typedef struct __attribute__((__packed__))
{
  int16_t X;
  int16_t Y;
  int16_t Z;
  int16_t Rx;
  int16_t Ry;
  int16_t Rz;
  int16_t slider;
  int16_t dial;
  uint8_t hat;
  uint32_t buttons;
} JoyReport_t;

UX_SLAVE_CLASS_HID_EVENT hidEvent;
UX_SLAVE_CLASS_HID* pHid;
JoyReport_t joyReport;
TX_TIMER gameControllerTimer; //XXX temporary triggering timer
TX_EVENT_FLAGS_GROUP gameControllerEvents;
TIM_HandleTypeDef* pMotor_X_Timer =NULL;

void sendJoyReport(void);
void sendBufReport(void);  //XXX test
void gameControllerTrigger(ULONG arg);  //XXX temp

/**
  * @brief  Function implementing the Game Controller entry thread.
  * @param  thread_input: Hardcoded to 0.
  * @retval None
  */
void gameController(void)
{
  static uint32_t loopCounter = 0;
  ULONG actualFlags;
  LOG_INFO("gameController entry");
  tx_timer_create(&gameControllerTimer, "game controller timer", gameControllerTrigger, 0, 100, 1, TX_AUTO_ACTIVATE); //XXX temp
  tx_event_flags_create(&gameControllerEvents, "game controller events");

  /* XXX test of motor pwm signals */
  HAL_TIM_PWM_Start(pMotor_X_Timer, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(pMotor_X_Timer, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(pMotor_X_Timer, TIM_CHANNEL_3);
  __HAL_TIM_SET_COMPARE(pMotor_X_Timer, TIM_CHANNEL_1, 10 * PWM_PERIOD / 100);
  __HAL_TIM_SET_COMPARE(pMotor_X_Timer, TIM_CHANNEL_2, 25 * PWM_PERIOD / 100);
  __HAL_TIM_SET_COMPARE(pMotor_X_Timer, TIM_CHANNEL_3, 50 * PWM_PERIOD / 100);

  /* Infinite loop */
  while (1)
  {
    tx_event_flags_get(&gameControllerEvents, GAME_CTRL_EVENT_TIMER_TRIG | GAME_CTRL_EVENT_GEN_INP, TX_OR_CLEAR, &actualFlags, TX_WAIT_FOREVER);
    HAL_GPIO_WritePin(TEST_1_GPIO_Port, TEST_1_Pin, GPIO_PIN_RESET); //XXX test

    /* check game controller event flags */

    if(actualFlags & GAME_CTRL_EVENT_TIMER_TRIG)
    {
      /* loop triggered by game controller timer */
      if(loopCounter %100 == 0)
      {
        sendBufReport();
      }
      sendJoyReport();

      if((loopCounter++ % (TX_TIMER_TICKS_PER_SECOND >> 1)) == 0) //true every half a second
      {
        HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin);
      }    
    }

    if(actualFlags & GAME_CTRL_EVENT_GEN_INP)
    {
      /* loop triggered by generic data received */
      LOG_DEBUG("generic input buffer: %u,%u,%u,%u", genericInpBuf[0], genericInpBuf[1], genericInpBuf[2], genericInpBuf[3]);
    }    
  }
}

void sendJoyReport(void)
{
  UX_SLAVE_DEVICE* pDevice;
  UX_SLAVE_INTERFACE* pInterface;

  //HAL_GPIO_WritePin(TEST_2_GPIO_Port, TEST_2_Pin, GPIO_PIN_SET); //XXX test
  /* get USB device */
  pDevice = &_ux_system_slave->ux_system_slave_device;
  /* get the interface */
  pInterface = pDevice->ux_slave_device_first_interface;
  /* get the HID instance */
  pHid = pInterface->ux_slave_interface_class_instance;
  ux_utility_memory_set(&hidEvent, 0, sizeof(UX_SLAVE_CLASS_HID_EVENT));

  /* check if USB device has been configured */
  if((pDevice == TX_NULL) ||
    (pDevice->ux_slave_device_state != UX_DEVICE_CONFIGURED) ||
    (pInterface == TX_NULL) ||
    (pHid == TX_NULL))
  {
    return;
  }

  // XXX test of joystick report
  static uint32_t cnt = 0;
  int16_t i16val = -32767 + (cnt % 100) * 655;
  joyReport.X = i16val;
  joyReport.Y = i16val;
  joyReport.Z = i16val;
  joyReport.Rx = i16val;
  joyReport.Ry = i16val;
  joyReport.Rz = i16val;
  joyReport.slider = i16val;
  joyReport.dial = (int16_t)cnt;
  joyReport.hat = ((cnt >> 5) % 8) + 1;
  joyReport.buttons = 1 << ((cnt >> 5) % 32);
  cnt++;
  // XXX end of test

  memcpy(hidEvent.ux_device_class_hid_event_buffer, &joyReport, sizeof(joyReport));
  hidEvent.ux_device_class_hid_event_report_id = REPORT_ID_JOY;
  hidEvent.ux_device_class_hid_event_length = sizeof(JoyReport_t);
  ux_device_class_hid_event_set(pHid, &hidEvent);
  //HAL_GPIO_WritePin(TEST_2_GPIO_Port, TEST_2_Pin, GPIO_PIN_RESET);
}

void gameControllerTrigger(ULONG arg) //XXX temp
{
  TX_PARAMETER_NOT_USED(arg);
  HAL_GPIO_WritePin(TEST_1_GPIO_Port, TEST_1_Pin, GPIO_PIN_SET);
  tx_event_flags_set(&gameControllerEvents, GAME_CTRL_EVENT_TIMER_TRIG, TX_OR);
}

void sendBufReport(void)  //XXX test
{
  UX_SLAVE_DEVICE* pDevice;
  UX_SLAVE_INTERFACE* pInterface;

  HAL_GPIO_WritePin(TEST_2_GPIO_Port, TEST_2_Pin, GPIO_PIN_SET); //XXX test
  HAL_GPIO_TogglePin(TEST_2_GPIO_Port, TEST_2_Pin);
  HAL_GPIO_TogglePin(TEST_2_GPIO_Port, TEST_2_Pin);
  /* get USB device */
  pDevice = &_ux_system_slave->ux_system_slave_device;
  /* get the interface */
  pInterface = pDevice->ux_slave_device_first_interface;
  /* get the HID instance */
  pHid = pInterface->ux_slave_interface_class_instance;
  ux_utility_memory_set(&hidEvent, 0, sizeof(UX_SLAVE_CLASS_HID_EVENT));

  /* check if USB device has been configured */
  if((pDevice == TX_NULL) ||
    (pDevice->ux_slave_device_state != UX_DEVICE_CONFIGURED) ||
    (pInterface == TX_NULL) ||
    (pHid == TX_NULL))
  {
    return;
  }

  static uint32_t cnt = 0;
  memcpy(hidEvent.ux_device_class_hid_event_buffer, &cnt, 4);
  cnt++;

  hidEvent.ux_device_class_hid_event_report_id = REPORT_ID_GEN;
  hidEvent.ux_device_class_hid_event_length = 4;
  ux_device_class_hid_event_set(pHid, &hidEvent);
  HAL_GPIO_WritePin(TEST_2_GPIO_Port, TEST_2_Pin, GPIO_PIN_RESET);
}
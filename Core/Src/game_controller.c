#include "game_controller.h"
#include "logger.h"
#include "ux_api.h"
#include "ux_device_class_hid.h"
#include "ux_device_descriptors.h"

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

void sendJoyReport(void);
void gameControllerTrigger(ULONG arg);  //XXX temp

/**
  * @brief  Function implementing the Game Controller entry thread.
  * @param  thread_input: Hardcoded to 0.
  * @retval None
  */
void gameController(void)
{
  ULONG actualFlags;
  LOG_INFO("gameController entry");
  tx_timer_create(&gameControllerTimer, "game controller timer", gameControllerTrigger, 0, 100, 1, TX_AUTO_ACTIVATE); //XXX temp
  tx_event_flags_create(&gameControllerEvents, "game controller events");

  /* Infinite loop */
  while (1)
  {
    tx_event_flags_get(&gameControllerEvents, GAME_CTRL_EVENT_TIMER_TRIG, TX_OR_CLEAR, &actualFlags, TX_WAIT_FOREVER);
    HAL_GPIO_WritePin(TEST_1_GPIO_Port, TEST_1_Pin, GPIO_PIN_RESET); //XXX test

    // HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET);
    // tx_thread_sleep(UX_MS_TO_TICK_NON_ZERO(50));
    // HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET);
    // tx_thread_sleep(UX_MS_TO_TICK_NON_ZERO(100));
    // HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET);
    // tx_thread_sleep(UX_MS_TO_TICK_NON_ZERO(50));
    // HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET);
    // tx_thread_sleep(UX_MS_TO_TICK_NON_ZERO(800));

    sendJoyReport();       
  }
}

void sendJoyReport(void)
{
  UX_SLAVE_DEVICE* pDevice;
  UX_SLAVE_INTERFACE* pInterface;

  /* get USB device */
  pDevice = &_ux_system_slave->ux_system_slave_device;
  /* get the interface */
  pInterface = pDevice->ux_slave_device_first_interface;
  /* get the HID instance */
  pHid = pInterface->ux_slave_interface_class_instance;
  ux_utility_memory_set(&hidEvent, 0, sizeof(UX_SLAVE_CLASS_HID_EVENT));

  /* check if USB device has been configured */
  if((pDevice->ux_slave_device_state != UX_DEVICE_CONFIGURED) || (pHid == TX_NULL))
  {
    return;
  }



  // XXX test of joystick report
  HAL_GPIO_TogglePin(TEST_2_GPIO_Port, TEST_2_Pin);
  static uint32_t cnt = 0;
  int16_t i16val = -32767 + (cnt % 10) * 6553;
  joyReport.X = i16val;
  joyReport.Y = i16val;
  joyReport.Z = i16val;
  joyReport.Rx = i16val;
  joyReport.Ry = i16val;
  joyReport.Rz = i16val;
  joyReport.slider = i16val;
  joyReport.dial = i16val;
  joyReport.hat = (cnt % 8) + 1;
  joyReport.buttons = 1 << (cnt % 32);
  cnt++;
  // XXX end of test

  memcpy(hidEvent.ux_device_class_hid_event_buffer, &joyReport, sizeof(joyReport));
  hidEvent.ux_device_class_hid_event_report_id = REPORT_ID_JOY;
  hidEvent.ux_device_class_hid_event_length = sizeof(JoyReport_t);
  ux_device_class_hid_event_set(pHid, &hidEvent);
}

void gameControllerTrigger(ULONG arg) //XXX temp
{
  TX_PARAMETER_NOT_USED(arg);
  HAL_GPIO_WritePin(TEST_1_GPIO_Port, TEST_1_Pin, GPIO_PIN_SET);
  tx_event_flags_set(&gameControllerEvents, GAME_CTRL_EVENT_TIMER_TRIG, TX_OR);
}
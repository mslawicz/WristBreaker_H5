#include "game_controller.h"
#include "logger.h"
#include "ux_api.h"
#include "ux_device_class_hid.h"
#include "ux_device_descriptors.h"

#define JOY_REPORT_SIZE (8*2 + 1 + 4)

uint8_t joyReport[JOY_REPORT_SIZE];
UX_SLAVE_CLASS_HID_EVENT hidEvent;
UX_SLAVE_CLASS_HID* pHid;

void sendJoyReport(void);

/**
  * @brief  Function implementing the Game Controller entry thread.
  * @param  thread_input: Hardcoded to 0.
  * @retval None
  */
void gameController(void)
{
  LOG_INFO("gameController entry");

  /* Infinite loop */
  while (1)
  {
    HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET);
    tx_thread_sleep(UX_MS_TO_TICK_NON_ZERO(50));
    HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET);
    tx_thread_sleep(UX_MS_TO_TICK_NON_ZERO(100));
    HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET);
    tx_thread_sleep(UX_MS_TO_TICK_NON_ZERO(50));
    HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET);
    tx_thread_sleep(UX_MS_TO_TICK_NON_ZERO(800));     

    sendJoyReport();       
  }
}

void sendJoyReport(void)
{
  UX_SLAVE_DEVICE* pDevice;
  UX_SLAVE_INTERFACE* pInterface;

  pDevice = &_ux_system_slave->ux_system_slave_device;
  ux_utility_memory_set(&hidEvent, 0, sizeof(UX_SLAVE_CLASS_HID_EVENT));

  /* check if USB device has been configured */
  if(pDevice->ux_slave_device_state != UX_DEVICE_CONFIGURED)
  {
    return;
  }

  /* get the interface */
  pInterface = pDevice->ux_slave_device_first_interface;
  /* get the HID instance */
  pHid = pInterface->ux_slave_interface_class_instance;


  static uint32_t cnt = 0;
  int16_t i16val = -32767 + (cnt % 10) * 6553; 
  hidEvent.ux_device_class_hid_event_report_id = REPORT_ID_JOY;
  hidEvent.ux_device_class_hid_event_length = JOY_REPORT_SIZE;
  *(int16_t*)(hidEvent.ux_device_class_hid_event_buffer + 0) = i16val;
  *(int16_t*)(hidEvent.ux_device_class_hid_event_buffer + 2) = i16val;
  *(int16_t*)(hidEvent.ux_device_class_hid_event_buffer + 4) = i16val;
  *(int16_t*)(hidEvent.ux_device_class_hid_event_buffer + 6) = i16val;
  *(int16_t*)(hidEvent.ux_device_class_hid_event_buffer + 8) = i16val;
  *(int16_t*)(hidEvent.ux_device_class_hid_event_buffer + 10) = i16val;
  *(int16_t*)(hidEvent.ux_device_class_hid_event_buffer + 12) = i16val;
  *(int16_t*)(hidEvent.ux_device_class_hid_event_buffer + 14) = i16val;
  hidEvent.ux_device_class_hid_event_buffer[16] = (cnt % 8) + 1;
  *(uint32_t*)(hidEvent.ux_device_class_hid_event_buffer + 17) = 1 << (cnt % 32);
  cnt++;

  ux_device_class_hid_event_set(pHid, &hidEvent);
}
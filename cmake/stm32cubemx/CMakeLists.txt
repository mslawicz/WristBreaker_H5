cmake_minimum_required(VERSION 3.22)

project(stm32cubemx)
add_library(stm32cubemx INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

target_compile_definitions(stm32cubemx INTERFACE 
	TX_INCLUDE_USER_DEFINE_FILE 
	TX_SINGLE_MODE_NON_SECURE=1 
	UX_INCLUDE_USER_DEFINE_FILE 
	USE_HAL_DRIVER 
	STM32H563xx
    $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories(stm32cubemx INTERFACE
    ../../Core/Inc
    ../../AZURE_RTOS/App
    ../../USBX/App
    ../../USBX/Target
    ../../Drivers/STM32H5xx_HAL_Driver/Inc
    ../../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy
    ../../Middlewares/ST/threadx/common/inc
    ../../Drivers/CMSIS/Device/ST/STM32H5xx/Include
    ../../Middlewares/ST/threadx/ports/cortex_m33/gnu/inc
    ../../Middlewares/ST/usbx/common/core/inc
    ../../Middlewares/ST/usbx/ports/generic/inc
    ../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers
    ../../Middlewares/ST/usbx/common/usbx_device_classes/inc
    ../../Drivers/CMSIS/Include
)

target_sources(stm32cubemx INTERFACE
    ../../Core/Src/main.c
    ../../Core/Src/app_threadx.c
    ../../Core/Src/stm32h5xx_it.c
    ../../Core/Src/stm32h5xx_hal_msp.c
    ../../Core/Src/stm32h5xx_hal_timebase_tim.c
    ../../USBX/App/ux_device_descriptors.c
    ../../USBX/App/app_usbx_device.c
    ../../USBX/App/ux_device_customhid.c
    ../../AZURE_RTOS/App/app_azure_rtos.c
    ../../Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_cortex.c
    ../../Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_icache.c
    ../../Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_rcc.c
    ../../Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_rcc_ex.c
    ../../Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_flash.c
    ../../Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_flash_ex.c
    ../../Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_gpio.c
    ../../Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_dma.c
    ../../Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_dma_ex.c
    ../../Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_pwr.c
    ../../Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_pwr_ex.c
    ../../Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal.c
    ../../Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_exti.c
    ../../Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_tim.c
    ../../Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_tim_ex.c
    ../../Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_uart.c
    ../../Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_uart_ex.c
    ../../Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_pcd.c
    ../../Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_pcd_ex.c
    ../../Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_ll_usb.c
    ../../Core/Src/system_stm32h5xx.c
    ../../Middlewares/ST/threadx/common/src/tx_initialize_high_level.c
    ../../Middlewares/ST/threadx/common/src/tx_initialize_kernel_enter.c
    ../../Middlewares/ST/threadx/common/src/tx_initialize_kernel_setup.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_stack_error_handler.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_stack_error_notify.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_system_resume.c
    ../../Middlewares/ST/threadx/common/src/tx_block_allocate.c
    ../../Middlewares/ST/threadx/common/src/tx_block_pool_cleanup.c
    ../../Middlewares/ST/threadx/common/src/tx_block_pool_create.c
    ../../Middlewares/ST/threadx/common/src/tx_block_pool_delete.c
    ../../Middlewares/ST/threadx/common/src/tx_block_pool_info_get.c
    ../../Middlewares/ST/threadx/common/src/tx_block_pool_initialize.c
    ../../Middlewares/ST/threadx/common/src/tx_block_pool_prioritize.c
    ../../Middlewares/ST/threadx/common/src/tx_block_release.c
    ../../Middlewares/ST/threadx/common/src/tx_byte_allocate.c
    ../../Middlewares/ST/threadx/common/src/tx_byte_pool_cleanup.c
    ../../Middlewares/ST/threadx/common/src/tx_byte_pool_create.c
    ../../Middlewares/ST/threadx/common/src/tx_byte_pool_delete.c
    ../../Middlewares/ST/threadx/common/src/tx_byte_pool_info_get.c
    ../../Middlewares/ST/threadx/common/src/tx_byte_pool_initialize.c
    ../../Middlewares/ST/threadx/common/src/tx_byte_pool_prioritize.c
    ../../Middlewares/ST/threadx/common/src/tx_byte_pool_search.c
    ../../Middlewares/ST/threadx/common/src/tx_byte_release.c
    ../../Middlewares/ST/threadx/common/src/tx_event_flags_cleanup.c
    ../../Middlewares/ST/threadx/common/src/tx_event_flags_create.c
    ../../Middlewares/ST/threadx/common/src/tx_event_flags_delete.c
    ../../Middlewares/ST/threadx/common/src/tx_event_flags_get.c
    ../../Middlewares/ST/threadx/common/src/tx_event_flags_info_get.c
    ../../Middlewares/ST/threadx/common/src/tx_event_flags_initialize.c
    ../../Middlewares/ST/threadx/common/src/tx_event_flags_set.c
    ../../Middlewares/ST/threadx/common/src/tx_event_flags_set_notify.c
    ../../Middlewares/ST/threadx/common/src/tx_mutex_cleanup.c
    ../../Middlewares/ST/threadx/common/src/tx_mutex_create.c
    ../../Middlewares/ST/threadx/common/src/tx_mutex_delete.c
    ../../Middlewares/ST/threadx/common/src/tx_mutex_get.c
    ../../Middlewares/ST/threadx/common/src/tx_mutex_info_get.c
    ../../Middlewares/ST/threadx/common/src/tx_mutex_initialize.c
    ../../Middlewares/ST/threadx/common/src/tx_mutex_prioritize.c
    ../../Middlewares/ST/threadx/common/src/tx_mutex_priority_change.c
    ../../Middlewares/ST/threadx/common/src/tx_mutex_put.c
    ../../Middlewares/ST/threadx/common/src/tx_queue_cleanup.c
    ../../Middlewares/ST/threadx/common/src/tx_queue_create.c
    ../../Middlewares/ST/threadx/common/src/tx_queue_delete.c
    ../../Middlewares/ST/threadx/common/src/tx_queue_flush.c
    ../../Middlewares/ST/threadx/common/src/tx_queue_front_send.c
    ../../Middlewares/ST/threadx/common/src/tx_queue_info_get.c
    ../../Middlewares/ST/threadx/common/src/tx_queue_initialize.c
    ../../Middlewares/ST/threadx/common/src/tx_queue_prioritize.c
    ../../Middlewares/ST/threadx/common/src/tx_queue_receive.c
    ../../Middlewares/ST/threadx/common/src/tx_queue_send.c
    ../../Middlewares/ST/threadx/common/src/tx_queue_send_notify.c
    ../../Middlewares/ST/threadx/common/src/tx_semaphore_ceiling_put.c
    ../../Middlewares/ST/threadx/common/src/tx_semaphore_cleanup.c
    ../../Middlewares/ST/threadx/common/src/tx_semaphore_create.c
    ../../Middlewares/ST/threadx/common/src/tx_semaphore_delete.c
    ../../Middlewares/ST/threadx/common/src/tx_semaphore_get.c
    ../../Middlewares/ST/threadx/common/src/tx_semaphore_info_get.c
    ../../Middlewares/ST/threadx/common/src/tx_semaphore_initialize.c
    ../../Middlewares/ST/threadx/common/src/tx_semaphore_prioritize.c
    ../../Middlewares/ST/threadx/common/src/tx_semaphore_put.c
    ../../Middlewares/ST/threadx/common/src/tx_semaphore_put_notify.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_create.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_delete.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_entry_exit_notify.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_identify.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_info_get.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_initialize.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_preemption_change.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_priority_change.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_relinquish.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_reset.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_resume.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_shell_entry.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_sleep.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_stack_analyze.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_suspend.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_system_preempt_check.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_system_suspend.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_terminate.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_time_slice.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_time_slice_change.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_timeout.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_wait_abort.c
    ../../Middlewares/ST/threadx/common/src/tx_time_get.c
    ../../Middlewares/ST/threadx/common/src/tx_time_set.c
    ../../Middlewares/ST/threadx/common/src/txe_block_allocate.c
    ../../Middlewares/ST/threadx/common/src/txe_block_pool_create.c
    ../../Middlewares/ST/threadx/common/src/txe_block_pool_delete.c
    ../../Middlewares/ST/threadx/common/src/txe_block_pool_info_get.c
    ../../Middlewares/ST/threadx/common/src/txe_block_pool_prioritize.c
    ../../Middlewares/ST/threadx/common/src/txe_block_release.c
    ../../Middlewares/ST/threadx/common/src/txe_byte_allocate.c
    ../../Middlewares/ST/threadx/common/src/txe_byte_pool_create.c
    ../../Middlewares/ST/threadx/common/src/txe_byte_pool_delete.c
    ../../Middlewares/ST/threadx/common/src/txe_byte_pool_info_get.c
    ../../Middlewares/ST/threadx/common/src/txe_byte_pool_prioritize.c
    ../../Middlewares/ST/threadx/common/src/txe_byte_release.c
    ../../Middlewares/ST/threadx/common/src/txe_event_flags_create.c
    ../../Middlewares/ST/threadx/common/src/txe_event_flags_delete.c
    ../../Middlewares/ST/threadx/common/src/txe_event_flags_get.c
    ../../Middlewares/ST/threadx/common/src/txe_event_flags_info_get.c
    ../../Middlewares/ST/threadx/common/src/txe_event_flags_set.c
    ../../Middlewares/ST/threadx/common/src/txe_event_flags_set_notify.c
    ../../Middlewares/ST/threadx/common/src/txe_mutex_create.c
    ../../Middlewares/ST/threadx/common/src/txe_mutex_delete.c
    ../../Middlewares/ST/threadx/common/src/txe_mutex_get.c
    ../../Middlewares/ST/threadx/common/src/txe_mutex_info_get.c
    ../../Middlewares/ST/threadx/common/src/txe_mutex_prioritize.c
    ../../Middlewares/ST/threadx/common/src/txe_mutex_put.c
    ../../Middlewares/ST/threadx/common/src/txe_queue_create.c
    ../../Middlewares/ST/threadx/common/src/txe_queue_delete.c
    ../../Middlewares/ST/threadx/common/src/txe_queue_flush.c
    ../../Middlewares/ST/threadx/common/src/txe_queue_front_send.c
    ../../Middlewares/ST/threadx/common/src/txe_queue_info_get.c
    ../../Middlewares/ST/threadx/common/src/txe_queue_prioritize.c
    ../../Middlewares/ST/threadx/common/src/txe_queue_receive.c
    ../../Middlewares/ST/threadx/common/src/txe_queue_send.c
    ../../Middlewares/ST/threadx/common/src/txe_queue_send_notify.c
    ../../Middlewares/ST/threadx/common/src/txe_semaphore_ceiling_put.c
    ../../Middlewares/ST/threadx/common/src/txe_semaphore_create.c
    ../../Middlewares/ST/threadx/common/src/txe_semaphore_delete.c
    ../../Middlewares/ST/threadx/common/src/txe_semaphore_get.c
    ../../Middlewares/ST/threadx/common/src/txe_semaphore_info_get.c
    ../../Middlewares/ST/threadx/common/src/txe_semaphore_prioritize.c
    ../../Middlewares/ST/threadx/common/src/txe_semaphore_put.c
    ../../Middlewares/ST/threadx/common/src/txe_semaphore_put_notify.c
    ../../Middlewares/ST/threadx/common/src/txe_thread_create.c
    ../../Middlewares/ST/threadx/common/src/txe_thread_delete.c
    ../../Middlewares/ST/threadx/common/src/txe_thread_entry_exit_notify.c
    ../../Middlewares/ST/threadx/common/src/txe_thread_info_get.c
    ../../Middlewares/ST/threadx/common/src/txe_thread_preemption_change.c
    ../../Middlewares/ST/threadx/common/src/txe_thread_priority_change.c
    ../../Middlewares/ST/threadx/common/src/txe_thread_relinquish.c
    ../../Middlewares/ST/threadx/common/src/txe_thread_reset.c
    ../../Middlewares/ST/threadx/common/src/txe_thread_resume.c
    ../../Middlewares/ST/threadx/common/src/txe_thread_suspend.c
    ../../Middlewares/ST/threadx/common/src/txe_thread_terminate.c
    ../../Middlewares/ST/threadx/common/src/txe_thread_time_slice_change.c
    ../../Middlewares/ST/threadx/common/src/txe_thread_wait_abort.c
    ../../Middlewares/ST/threadx/common/src/tx_timer_activate.c
    ../../Middlewares/ST/threadx/common/src/tx_timer_change.c
    ../../Middlewares/ST/threadx/common/src/tx_timer_create.c
    ../../Middlewares/ST/threadx/common/src/tx_timer_deactivate.c
    ../../Middlewares/ST/threadx/common/src/tx_timer_delete.c
    ../../Middlewares/ST/threadx/common/src/tx_timer_expiration_process.c
    ../../Middlewares/ST/threadx/common/src/tx_timer_info_get.c
    ../../Middlewares/ST/threadx/common/src/tx_timer_initialize.c
    ../../Middlewares/ST/threadx/common/src/tx_timer_system_activate.c
    ../../Middlewares/ST/threadx/common/src/tx_timer_system_deactivate.c
    ../../Middlewares/ST/threadx/common/src/tx_timer_thread_entry.c
    ../../Middlewares/ST/threadx/common/src/txe_timer_activate.c
    ../../Middlewares/ST/threadx/common/src/txe_timer_change.c
    ../../Middlewares/ST/threadx/common/src/txe_timer_create.c
    ../../Middlewares/ST/threadx/common/src/txe_timer_deactivate.c
    ../../Middlewares/ST/threadx/common/src/txe_timer_delete.c
    ../../Middlewares/ST/threadx/common/src/txe_timer_info_get.c
    ../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_callback.c
    ../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_endpoint_create.c
    ../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_endpoint_destroy.c
    ../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_endpoint_reset.c
    ../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_endpoint_stall.c
    ../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_endpoint_status.c
    ../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_frame_number_get.c
    ../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_function.c
    ../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_initialize.c
    ../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_initialize_complete.c
    ../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_interrupt_handler.c
    ../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_transfer_abort.c
    ../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_transfer_request.c
    ../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_uninitialize.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_debug_callback_register.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_debug_log.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_delay_ms.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_descriptor_pack.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_descriptor_parse.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_error_callback_register.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_event_flags_create.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_event_flags_delete.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_event_flags_get.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_event_flags_set.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_long_get.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_long_get_big_endian.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_long_put.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_long_put_big_endian.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_memory_allocate.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_memory_allocate_add_safe.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_memory_allocate_mulc_safe.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_memory_allocate_mulv_safe.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_memory_compare.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_memory_copy.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_memory_free.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_memory_free_block_best_get.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_memory_set.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_mutex_create.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_mutex_delete.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_mutex_off.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_mutex_on.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_pci_class_scan.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_pci_read.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_pci_write.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_physical_address.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_semaphore_create.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_semaphore_delete.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_semaphore_get.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_semaphore_put.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_set_interrupt_handler.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_short_get.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_short_get_big_endian.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_short_put.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_short_put_big_endian.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_string_length_check.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_string_length_get.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_string_to_unicode.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_thread_create.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_thread_delete.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_thread_identify.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_thread_relinquish.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_thread_resume.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_thread_schedule_other.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_thread_sleep.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_thread_suspend.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_timer_create.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_timer_delete.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_unicode_to_string.c
    ../../Middlewares/ST/usbx/common/core/src/ux_utility_virtual_address.c
    ../../Middlewares/ST/usbx/common/core/src/ux_system_error_handler.c
    ../../Middlewares/ST/usbx/common/core/src/ux_system_initialize.c
    ../../Middlewares/ST/usbx/common/core/src/ux_system_uninitialize.c
    ../../Middlewares/ST/usbx/common/usbx_device_classes/src/ux_device_class_hid_activate.c
    ../../Middlewares/ST/usbx/common/usbx_device_classes/src/ux_device_class_hid_control_request.c
    ../../Middlewares/ST/usbx/common/usbx_device_classes/src/ux_device_class_hid_deactivate.c
    ../../Middlewares/ST/usbx/common/usbx_device_classes/src/ux_device_class_hid_descriptor_send.c
    ../../Middlewares/ST/usbx/common/usbx_device_classes/src/ux_device_class_hid_entry.c
    ../../Middlewares/ST/usbx/common/usbx_device_classes/src/ux_device_class_hid_event_get.c
    ../../Middlewares/ST/usbx/common/usbx_device_classes/src/ux_device_class_hid_event_set.c
    ../../Middlewares/ST/usbx/common/usbx_device_classes/src/ux_device_class_hid_initialize.c
    ../../Middlewares/ST/usbx/common/usbx_device_classes/src/ux_device_class_hid_interrupt_thread.c
    ../../Middlewares/ST/usbx/common/usbx_device_classes/src/ux_device_class_hid_read.c
    ../../Middlewares/ST/usbx/common/usbx_device_classes/src/ux_device_class_hid_receiver_event_free.c
    ../../Middlewares/ST/usbx/common/usbx_device_classes/src/ux_device_class_hid_receiver_event_get.c
    ../../Middlewares/ST/usbx/common/usbx_device_classes/src/ux_device_class_hid_receiver_initialize.c
    ../../Middlewares/ST/usbx/common/usbx_device_classes/src/ux_device_class_hid_receiver_thread.c
    ../../Middlewares/ST/usbx/common/usbx_device_classes/src/ux_device_class_hid_receiver_uninitialize.c
    ../../Middlewares/ST/usbx/common/usbx_device_classes/src/ux_device_class_hid_report_get.c
    ../../Middlewares/ST/usbx/common/usbx_device_classes/src/ux_device_class_hid_report_set.c
    ../../Middlewares/ST/usbx/common/usbx_device_classes/src/ux_device_class_hid_uninitialize.c
    ../../Middlewares/ST/usbx/common/core/src/ux_device_stack_alternate_setting_get.c
    ../../Middlewares/ST/usbx/common/core/src/ux_device_stack_alternate_setting_set.c
    ../../Middlewares/ST/usbx/common/core/src/ux_device_stack_class_register.c
    ../../Middlewares/ST/usbx/common/core/src/ux_device_stack_class_unregister.c
    ../../Middlewares/ST/usbx/common/core/src/ux_device_stack_clear_feature.c
    ../../Middlewares/ST/usbx/common/core/src/ux_device_stack_configuration_get.c
    ../../Middlewares/ST/usbx/common/core/src/ux_device_stack_configuration_set.c
    ../../Middlewares/ST/usbx/common/core/src/ux_device_stack_control_request_process.c
    ../../Middlewares/ST/usbx/common/core/src/ux_device_stack_descriptor_send.c
    ../../Middlewares/ST/usbx/common/core/src/ux_device_stack_disconnect.c
    ../../Middlewares/ST/usbx/common/core/src/ux_device_stack_endpoint_stall.c
    ../../Middlewares/ST/usbx/common/core/src/ux_device_stack_get_status.c
    ../../Middlewares/ST/usbx/common/core/src/ux_device_stack_host_wakeup.c
    ../../Middlewares/ST/usbx/common/core/src/ux_device_stack_initialize.c
    ../../Middlewares/ST/usbx/common/core/src/ux_device_stack_interface_delete.c
    ../../Middlewares/ST/usbx/common/core/src/ux_device_stack_interface_get.c
    ../../Middlewares/ST/usbx/common/core/src/ux_device_stack_interface_set.c
    ../../Middlewares/ST/usbx/common/core/src/ux_device_stack_interface_start.c
    ../../Middlewares/ST/usbx/common/core/src/ux_device_stack_microsoft_extension_register.c
    ../../Middlewares/ST/usbx/common/core/src/ux_device_stack_set_feature.c
    ../../Middlewares/ST/usbx/common/core/src/ux_device_stack_transfer_abort.c
    ../../Middlewares/ST/usbx/common/core/src/ux_device_stack_transfer_all_request_abort.c
    ../../Middlewares/ST/usbx/common/core/src/ux_device_stack_transfer_request.c
    ../../Middlewares/ST/usbx/common/core/src/ux_device_stack_uninitialize.c
    ../../Core/Src/sysmem.c
    ../../Core/Src/syscalls.c
    ../../startup_stm32h563xx.s
    ../../Core/Src/tx_initialize_low_level.S
    ../../Middlewares/ST/threadx/ports/cortex_m33/gnu/src/tx_thread_context_restore.S
    ../../Middlewares/ST/threadx/ports/cortex_m33/gnu/src/tx_thread_context_save.S
    ../../Middlewares/ST/threadx/ports/cortex_m33/gnu/src/tx_thread_interrupt_control.S
    ../../Middlewares/ST/threadx/ports/cortex_m33/gnu/src/tx_thread_interrupt_disable.S
    ../../Middlewares/ST/threadx/ports/cortex_m33/gnu/src/tx_thread_interrupt_restore.S
    ../../Middlewares/ST/threadx/ports/cortex_m33/gnu/src/tx_thread_schedule.S
    ../../Middlewares/ST/threadx/ports/cortex_m33/gnu/src/tx_thread_stack_build.S
    ../../Middlewares/ST/threadx/ports/cortex_m33/gnu/src/tx_thread_system_return.S
    ../../Middlewares/ST/threadx/ports/cortex_m33/gnu/src/tx_timer_interrupt.S
)

target_link_directories(stm32cubemx INTERFACE
)

target_link_libraries(stm32cubemx INTERFACE
)

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()



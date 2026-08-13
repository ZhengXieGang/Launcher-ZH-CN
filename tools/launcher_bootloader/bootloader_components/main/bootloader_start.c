/*
 * SPDX-FileCopyrightText: 2015-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdbool.h>
#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_rom_sys.h"
#include "esp_rom_caps.h"
#include "bootloader_init.h"
#include "bootloader_utility.h"
#include "bootloader_common.h"

void bootloader_before_init(void) __attribute__((weak));
void bootloader_after_init(void) __attribute__((weak));

static const char *TAG = "boot";

static int select_partition_number(bootloader_state_t *bs);
static int selected_boot_partition(const bootloader_state_t *bs);
static bool should_boot_launcher(int reset_reason);

void __attribute__((noreturn)) call_start_cpu0(void)
{
    if (bootloader_before_init) {
        bootloader_before_init();
    }

    if (bootloader_init() != ESP_OK) {
        bootloader_reset();
    }

    if (bootloader_after_init) {
        bootloader_after_init();
    }

#ifdef CONFIG_BOOTLOADER_SKIP_VALIDATE_IN_DEEP_SLEEP
    bootloader_utility_load_boot_image_from_deep_sleep();
#endif

    bootloader_state_t bs = {0};
    int boot_index = select_partition_number(&bs);
    if (boot_index == INVALID_INDEX) {
        bootloader_reset();
    }

#if CONFIG_SECURE_ENABLE_TEE
    bootloader_utility_load_tee_image(&bs);
#endif

    bootloader_utility_load_boot_image(&bs, boot_index);
}

static int select_partition_number(bootloader_state_t *bs)
{
    if (!bootloader_utility_load_partition_table(bs)) {
        ESP_LOGE(TAG, "load partition table error!");
        return INVALID_INDEX;
    }

    return selected_boot_partition(bs);
}

static int selected_boot_partition(const bootloader_state_t *bs)
{
    int boot_index = bootloader_utility_get_selected_boot_partition(bs);
    if (boot_index == INVALID_INDEX) {
        return boot_index;
    }

    const int reset_reason = esp_rom_get_reset_reason(0);
    if (should_boot_launcher(reset_reason)) {
        if (bs->test.offset != 0) {
            return TEST_APP_INDEX;
        }
        if (bs->factory.offset != 0) {
            return FACTORY_INDEX;
        }
    }

    return boot_index;
}

static bool should_boot_launcher(int reset_reason)
{
    if (reset_reason == RESET_REASON_CHIP_POWER_ON || reset_reason == RESET_REASON_CORE_DEEP_SLEEP) {
        return true;
    }
#if defined(CONFIG_IDF_TARGET_ESP32P4)
    if (reset_reason == RESET_REASON_CORE_MWDT) {
        return true;
    }
#endif

    return false;
}

#if CONFIG_LIBC_NEWLIB
struct _reent *__getreent(void)
{
    return _GLOBAL_REENT;
}
#endif

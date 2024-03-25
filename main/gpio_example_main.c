/* GPIO Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

/**
 * Brief:
 * This test code shows how to configure gpio and how to use gpio interrupt.
 *
 * GPIO status:
 * GPIO18: output (ESP32C2/ESP32H2 uses GPIO8 as the second output pin)
 * GPIO19: output (ESP32C2/ESP32H2 uses GPIO9 as the second output pin)
 * GPIO4:  input, pulled up, interrupt from rising edge and falling edge
 * GPIO5:  input, pulled up, interrupt from rising edge.
 *
 * Note. These are the default GPIO pins to be used in the example. You can
 * change IO pins in menuconfig.
 *
 * Test:
 * Connect GPIO18(8) with GPIO4
 * Connect GPIO19(9) with GPIO5
 * Generate pulses on GPIO18(8)/19(9), that triggers interrupt on GPIO4/5
 *
 */
// #define GPIO_OUTPUT_IO_0    CONFIG_GPIO_OUTPUT_0
// #define GPIO_OUTPUT_IO_1    CONFIG_GPIO_OUTPUT_1
// #define GPIO_OUTPUT_PIN_SEL  ((1ULL<<GPIO_OUTPUT_IO_0) | (1ULL<<GPIO_OUTPUT_IO_1))

#define GPIO_RED_PIN 16
#define GPIO_GREEN_PIN 17
#define GPIO_BLUE_PIN 18
#define GPIO_5V_PIN 19

#define GPIO_OUTPUT_PIN_SEL ((1ULL<<GPIO_RED_PIN) | (1ULL<<GPIO_GREEN_PIN) | (1ULL<<GPIO_BLUE_PIN) | (1ULL<<GPIO_5V_PIN))

/*
 * Let's say, GPIO_OUTPUT_IO_0=18, GPIO_OUTPUT_IO_1=19
 * In binary representation,
 * 1ULL<<GPIO_OUTPUT_IO_0 is equal to 0000000000000000000001000000000000000000 and
 * 1ULL<<GPIO_OUTPUT_IO_1 is equal to 0000000000000000000010000000000000000000
 * GPIO_OUTPUT_PIN_SEL                0000000000000000000011000000000000000000
 * */
// #define GPIO_INPUT_IO_0     CONFIG_GPIO_INPUT_0
// #define GPIO_INPUT_IO_1     CONFIG_GPIO_INPUT_1
// #define GPIO_INPUT_PIN_SEL  ((1ULL<<GPIO_INPUT_IO_0) | (1ULL<<GPIO_INPUT_IO_1))

/*
 * Let's say, GPIO_INPUT_IO_0=4, GPIO_INPUT_IO_1=5
 * In binary representation,
 * 1ULL<<GPIO_INPUT_IO_0 is equal to 0000000000000000000000000000000000010000 and
 * 1ULL<<GPIO_INPUT_IO_1 is equal to 0000000000000000000000000000000000100000
 * GPIO_INPUT_PIN_SEL                0000000000000000000000000000000000110000
 * */
//#define ESP_INTR_FLAG_DEFAULT 0

//static QueueHandle_t gpio_evt_queue = NULL;

/* Define color control macros (active low) */
#define RED_ON gpio_set_level(GPIO_RED_PIN, 0)
#define RED_OFF gpio_set_level(GPIO_RED_PIN, 1)
#define GREEN_ON gpio_set_level(GPIO_GREEN_PIN, 0)
#define GREEN_OFF gpio_set_level(GPIO_GREEN_PIN, 1)
#define BLUE_ON gpio_set_level(GPIO_BLUE_PIN, 0)
#define BLUE_OFF gpio_set_level(GPIO_BLUE_PIN, 1)
#define VOLTAGE_ON gpio_set_level(GPIO_5V_PIN, 1)
#define VOLTAGE_OFF gpio_set_level(GPIO_5V_PIN, 0)


// static void IRAM_ATTR gpio_isr_handler(void* arg)
// {
//     uint32_t gpio_num = (uint32_t) arg;
//     xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
// }

// static void gpio_task_example(void* arg)
// {
//     uint32_t io_num;
//     for (;;) {
//         if (xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)) {
//             printf("GPIO[%"PRIu32"] intr, val: %d\n", io_num, gpio_get_level(io_num));
//         }
//     }
// }

void app_main(void)
{
    // //zero-initialize the config structure.
    // gpio_config_t io_conf = {};
    // //disable interrupt
    // io_conf.intr_type = GPIO_INTR_DISABLE;
    // //set as output mode
    // io_conf.mode = GPIO_MODE_OUTPUT;
    // //bit mask of the pins that you want to set,e.g.GPIO18/19
    // io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    // //disable pull-down mode
    // io_conf.pull_down_en = 0;
    // //disable pull-up mode
    // io_conf.pull_up_en = 0;
    // //configure GPIO with the given settings
    // gpio_config(&io_conf);

    // //interrupt of rising edge
    // io_conf.intr_type = GPIO_INTR_POSEDGE;
    // //bit mask of the pins, use GPIO4/5 here
    // io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
    // //set as input mode
    // io_conf.mode = GPIO_MODE_INPUT;
    // //enable pull-up mode
    // io_conf.pull_up_en = 1;
    // gpio_config(&io_conf);

    // //change gpio interrupt type for one pin
    // gpio_set_intr_type(GPIO_INPUT_IO_0, GPIO_INTR_ANYEDGE);

    // //create a queue to handle gpio event from isr
    // gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
    // //start gpio task
    // xTaskCreate(gpio_task_example, "gpio_task_example", 2048, NULL, 10, NULL);

    // //install gpio isr service
    // gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    // //hook isr handler for specific gpio pin
    // gpio_isr_handler_add(GPIO_INPUT_IO_0, gpio_isr_handler, (void*) GPIO_INPUT_IO_0);
    // //hook isr handler for specific gpio pin
    // gpio_isr_handler_add(GPIO_INPUT_IO_1, gpio_isr_handler, (void*) GPIO_INPUT_IO_1);

    // //remove isr handler for gpio number.
    // gpio_isr_handler_remove(GPIO_INPUT_IO_0);
    // //hook isr handler for specific gpio pin again
    // gpio_isr_handler_add(GPIO_INPUT_IO_0, gpio_isr_handler, (void*) GPIO_INPUT_IO_0);

    // printf("Minimum free heap size: %"PRIu32" bytes\n", esp_get_minimum_free_heap_size());

    // int cnt = 0;
    // while (1) {
    //     printf("cnt: %d\n", cnt++);
    //     vTaskDelay(1000 / portTICK_PERIOD_MS);
    //     gpio_set_level(GPIO_OUTPUT_IO_0, cnt % 2);
    //     gpio_set_level(GPIO_OUTPUT_IO_1, cnt % 2);
    // }

    /* Configure GPIO */
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = GPIO_OUTPUT_PIN_SEL,
        .pull_down_en = 0,
        .pull_up_en = 0
    };
    gpio_config(&io_conf);

    /* Initialize LED Display */
    VOLTAGE_ON; // Turn on voltage for display

    // while(1) {
    //     /* Activate colors (active low) */
    //     RED_ON;
    //     GREEN_ON;
    //     BLUE_OFF;
    //     vTaskDelay(1000 / portTICK_PERIOD_MS); //Delay for red color
        
    //     // gpio_set_level(GPIO_RED_PIN, 0);
    //     // gpio_set_level(GPIO_GREEN_PIN, 1);
    //     // gpio_set_level(GPIO_BLUE_PIN, 1);
    //     //vTaskDelay(1000 / portTICK_PERIOD_MS); //Delay for red color

    //     RED_OFF;
    //     GREEN_ON;
    //     BLUE_ON;
    //     vTaskDelay(1000 / portTICK_PERIOD_MS); //Delay for green color

    //     RED_OFF;
    //     GREEN_OFF;
    //     BLUE_ON;
    //     vTaskDelay(1000 / portTICK_PERIOD_MS);  // Delay for blue color
    // }

    while(1) {
        /* Display Hex Color: #F1452F */
        // Extract RGB values from the hex color
        uint32_t hex_color = 0x8F5A1B;
        uint8_t red = (hex_color >> 16) & 0xFF;
        uint8_t green = (hex_color >> 8) & 0xFF;
        uint8_t blue = hex_color & 0xFF;

        // Set the colors of the LEDs
        if (red > 0) {
            RED_ON;
        } else {
            RED_OFF;
        }

        if (green > 0) {
            GREEN_ON;
        } else {
            GREEN_OFF;
        }

        if (blue > 0) {
            BLUE_ON;
        } else {
            BLUE_OFF;
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for color display
    }
}

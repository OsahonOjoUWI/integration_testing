// Osahon Ojo - 816005001
// ECNG 3006 Lab #3

/* I2C example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "esp_log.h"
#include "esp_system.h"
#include "esp_err.h"

#include "driver/i2c.h"


static const char *TAG = "main";
volatile uint16_t adc_result;
volatile uint16_t v_in_whole;
volatile uint16_t v_in_frac;
volatile uint16_t exp_whole;
volatile uint16_t exp_frac;
// volatile char* v_in_dec;

/**
 * CODE BRIEF
 *
 * This code will create a task to run unit tests on two functions: adcResToVoltageWhole and adcResToVoltageFrac.
 *
 **/

/* ADC result to voltage conversion formula:
 * Vin = ( (ADC_result / 2^N)*(Vthres_+ - Vthres_-) ) + Vthres_-
 * Vin = ADC_result (4.096 / 65536)
 * Vin = ADC_result / 16000      */

//This fxn calculates whole number part of voltage value
static void adcResToVoltageWhole(volatile uint16_t* res_adc, volatile uint16_t* res_whole)
{
    (*res_whole) = (*res_adc) / 16000;
}

/* This fxn calculates the fractional part of the voltage value */
static void adcResToVoltageFrac(volatile uint16_t* res_adc, volatile uint16_t* res_frac)
{
    (*res_frac) = (*res_adc) % 16000;
}

//This fxn converts the ADC result to a voltage
static void adcResToVoltage(volatile uint16_t* res_adc, volatile uint16_t* res_whole, volatile uint16_t* res_frac)
{
    adcResToVoltageWhole(res_adc, res_whole);
    adcResToVoltageFrac(res_adc, res_frac);

    /* uint16_t dec = ((*res_frac) * 10000) / 16000;
    sprintf(res_dec, "0%i", (int)dec); */
}

static void integration_test_task(void* arg)
{
    static int i = 1;

    ESP_LOGI(TAG, "Integration testing task\n");
    ESP_LOGI(TAG, "UUT: adcResToVoltage()\n");
    ESP_LOGI(TAG, "adcResToVoltage() determines both the whole and fractional part of voltage value corresponding to ADC result\n\n");

    while (1) {
        //init variables
        adc_result = 0;

        // test cases
        if (i == 1)
        {
            adc_result = 0x0;     // 0
            exp_whole = 0;
            exp_frac = 0;
        }
        else if (i == 2)
        {
            adc_result = 0xa;     // 10
            exp_whole = 0;
            exp_frac = 10;
        }
        else if (i == 3)
        {
            adc_result = 0x5e1f;  // 24095
            exp_whole = 1;
            exp_frac = 8095;
        }
        else if (i == 4)
        {
            adc_result = 0x6c1f;  // 27679
            exp_whole = 1;
            exp_frac = 11679;
        }
        else if (i == 5)
        {
            adc_result = 0xffff;  // 65535
            exp_whole = 4;
            exp_frac = 1535;
        }

        ESP_LOGI(TAG, "Test case %i: ADC result: 0x%x [%i]\n", i, adc_result, (int)adc_result);
        ESP_LOGI(TAG, "Expected output > Whole: %i, Fraction: %i / 16000\n", (int)exp_whole, (int)exp_frac);
        adcResToVoltage(&adc_result, &v_in_whole, &v_in_frac);
        ESP_LOGI(TAG, "Output > Whole: %i, Fraction: %i / 16000\n\n", (int)v_in_whole, (int)v_in_frac);

        if (i >= 5)
            i = 1;
        else
            i++;

        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

void app_main(void)
{
    printf("Inside app_main\n");

    // v_in_dec = malloc(4);

    //start unit test task
    xTaskCreate(integration_test_task, "integration_test_task", 2048, NULL, 10, NULL);

}

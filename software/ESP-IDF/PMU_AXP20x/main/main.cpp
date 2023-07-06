/////////////////////////////////////////////////////////////////
/*
MIT License

Copyright (c) 2020 lewis he

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

main.cpp - AXP202X_Library idf Programming example
Created by Lewis he on July 29, 2020.
github:https://github.com/lewisxhe/ESP_IDF_AXP20x_Library
*/
/////////////////////////////////////////////////////////////////
//! 请注意外设最大支持电压，调压可能会损坏外设器件
//IIC部分官方文档：https://docs.espressif.com/projects/esp-idf/en/release-v4.4/esp32c3/api-reference/peripherals/i2c.html

extern "C" {

#include "i2c_port.h"

}

#include "axp20x.hpp"

static const char *TAG = "AXP20x";

// //! ESP32C3只有I2C_NUM_0一个I2C通道

AXP20X_Class axp;


static QueueHandle_t gpio_evt_queue = NULL;

static void IRAM_ATTR axp_isr_handler(void *arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

static void axp_irq_init()
{

    static gpio_config_t io_conf;
    //enable interrupt
    io_conf.intr_type = GPIO_INTR_NEGEDGE;
    //set as input mode
    io_conf.mode = GPIO_MODE_INPUT;
    //bit mask of the pins that you want to set
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
    //disable pull-down mode
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    //enable pull-up mode
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    //configure GPIO with the given settings
    gpio_config(&io_conf);
    //change gpio intrrupt type for one pin
    gpio_set_intr_type(AXP_ISR_GPIO, GPIO_INTR_NEGEDGE);
    //install gpio isr service
    gpio_install_isr_service(0);
    //hook isr handler for specific gpio pin
    gpio_isr_handler_add(AXP_ISR_GPIO, axp_isr_handler, (void *) AXP_ISR_GPIO);
    //create a queue to handle gpio event from isr
    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
}

extern "C" void app_main(void)
{
    ESP_ERROR_CHECK(i2c_master_init());

    axp_irq_init();

    if (axp.begin(twi_read, twi_write, AXP202_SLAVE_ADDRESS)) {
        ESP_LOGE(TAG, "Error init axp20x !!!");
        while (1);
    }
    ESP_LOGI(TAG, "Success init axp20x !!!");

    axp.setPowerOutPut(AXP202_DCDC3, AXP202_ON);
    axp.setPowerOutPut(AXP202_EXTEN, AXP202_ON);
    axp.setPowerOutPut(AXP202_LDO2, AXP202_ON);
    axp.setPowerOutPut(AXP202_LDO4, AXP202_ON);
    axp.setPowerOutPut(AXP202_DCDC2, AXP202_ON);
    axp.setLDO4Voltage(AXP202_LDO4_3300MV);
    axp.setLDO3Voltage(3500);
    axp.setPowerOutPut(AXP202_LDO3, AXP202_ON);

    if ( axp.isDCDC2Enable()) {
        ESP_LOGI(TAG, "DC2: %u mV", axp.getDCDC2Voltage());
    } else {
        ESP_LOGI(TAG, "DC2: DISABLE");
    }

    if (axp.isDCDC3Enable()) {
        ESP_LOGI(TAG, "DC3: %u mV", axp.getDCDC3Voltage());
    } else {
        ESP_LOGI(TAG, "DC3: DISABLE");
    }

    if (axp.isLDO2Enable()) {
        ESP_LOGI(TAG, "LDO2: %u mV", axp.getLDO2Voltage());
    } else {
        ESP_LOGI(TAG, "LDO2: DISABLE");
    }

    if (axp.isLDO3Enable()) {
        ESP_LOGI(TAG, "LDO3: %u mV", axp.getLDO3Voltage());
    } else {
        ESP_LOGI(TAG, "LDO3: DISABLE");
    }

    if (axp.isLDO4Enable()) {
        ESP_LOGI(TAG, "LDO4: %u mV", axp.getLDO4Voltage());
    } else {
        ESP_LOGI(TAG, "LDO4: DISABLE");
    }

    if (axp.isExtenEnable()) {
        ESP_LOGI(TAG, "Exten: ENABLE");
    } else {
        ESP_LOGI(TAG, "Exten: DISABLE");
    }

    //When the chip is axp192 / 173, the allowed values are 0 ~ 15,
    //corresponding to the axp1xx_charge_current_t enumeration
    // axp.setChargeControlCur(AXP1XX_CHARGE_CUR_550MA);

    //axp202 allows maximum charging current of 1800mA, minimum 300mA
    axp.setChargeControlCur(300);

    ESP_LOGI(TAG, "setChargeControlCur:%u", axp.getChargeControlCur());

    axp.setGPIOMode(AXP_GPIO_0, AXP_IO_OUTPUT_HIGH_MODE);
    axp.gpioWrite(AXP_GPIO_0, 1);

    //! Enable all irq channel
    axp.enableIRQ(AXP202_ALL_IRQ, true);

    axp.clearIRQ();

    uint32_t io_num;
    for (;;) {

        if (xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)) {
            if (io_num == AXP_ISR_GPIO) {
                axp.readIRQ();
                if (axp.isPEKShortPressIRQ()) {
                    ESP_LOGI(TAG, "AXP202 PEK key Click");
                }
                axp.clearIRQ();
            }
        }
    }
}

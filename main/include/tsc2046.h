#ifndef TSC2046_H
#define TSC2046_H

#include <stdint.h>
#include <stdbool.h>
#include "driver/spi_master.h"

#define TSC2046_PIN_NUM_MISO 2
#define TSC2046_PIN_NUM_MOSI 41
#define TSC2046_PIN_NUM_CLK  39
#define TSC2046_PIN_NUM_CS   40
#define TSC2046_PIN_NUM_IRQ  1
#define TSC2046_PIN_NUM_BUSY 42

#define TSC2046_SPI_HOST            SPI2_HOST
#define TSC2046_SPI_CLK_SPEED_HZ    (5*100*1000) // 500 kHz

#define TSC2046_NVS_NAMESPACE "tsc2046"
#define TSC2046_NVS_KEY_CAL_DATA "cal_data"


enum tsc2046_state_e {
    TSC2046_STATE_RELEASED,
    TSC2046_STATE_PRESSED,
};

typedef struct {
    uint16_t x;
    uint16_t y;
    enum tsc2046_state_e state;
} tsc2046_data_t;

typedef struct {
    uint16_t x_raw; // Raw x coordinate from the touch screen
    uint16_t y_raw; // Raw y coordinate from the touch screen
    uint16_t x_cal; // Target x coordinate
    uint16_t y_cal; // Target y coordinate
} tsc2046_cal_data_point_t;

// Function prototypes
esp_err_t tsc2046_init(void);
tsc2046_data_t tsc2046_read(bool raw);
esp_err_t tsc2046_calibrate(const tsc2046_cal_data_point_t points[], size_t num_points);
esp_err_t tsc2046_store_cal_data(void);
bool tsc2046_is_calibrated(void);


#endif //TSC2046_H

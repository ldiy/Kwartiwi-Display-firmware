/**
 * @file tsc2046.c
 * @brief TSC2046 touch screen controller driver
 */

#include "esp_system.h"
#include "esp_log.h"
#include "driver/spi_master.h"
#include "nvs.h"
#include "tsc2046.h"

// TSC2046 commands/control bytes (differential mode, 12-bit resolution, PD1=1, PD0=1)
#define CMD_Y_READ  0b10010011
#define CMD_X_READ  0b11010011
#define CMD_Z1_READ 0b10110011
#define CMD_Z2_READ 0b11000011

#define BUFFER_SIZE 5   // 2 * 2 * 1 = 2 measurements * 2 bytes/measurement + 1 (first(rx) or last(tx) byte is a 0 byte)
#define Z_THRESHOLD 100 // Minimum z value to be considered a valid touch
#define SAMPLE_COUNT 4   // Number of samples to average

static char *TAG = "tsc2046";
static spi_device_handle_t tsc2046_spi_dev;

/**
 * Calibration data
 * X = cal_data[0] * x_raw + cal_data[1] * y_raw + cal_data[2]
 * Y = cal_data[3] * x_raw + cal_data[4] * y_raw + cal_data[5]
 */
float cal_data[6];
size_t cal_data_size = sizeof(cal_data);

/**
 * @brief Initialize the TSC2046 touch screen controller
 *
 * This function will setup the SPI bus and device, and read the calibration data from NVS.
 */
void tsc2046_init(void) {
    nvs_handle_t nvs_handle;
    esp_err_t err;

    ESP_LOGI(TAG, "Initializing TSC2046 touch screen controller");

    // Initialize the SPI bus
    spi_bus_config_t bus_cfg = {
        .miso_io_num = TSC2046_PIN_NUM_MISO,
        .mosi_io_num = TSC2046_PIN_NUM_MOSI,
        .sclk_io_num = TSC2046_PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .data4_io_num = -1,
        .data5_io_num = -1,
        .data6_io_num = -1,
        .data7_io_num = -1,
        .max_transfer_sz = 0,
        .flags = 0,
        .intr_flags = 0,
    };
    ESP_ERROR_CHECK(spi_bus_initialize(TSC2046_SPI_HOST, &bus_cfg, SPI_DMA_CH_AUTO));

    // Initialize the SPI device
    spi_device_interface_config_t dev_cfg = {
            .spics_io_num = TSC2046_PIN_NUM_CS,
            .clock_speed_hz = TSC2046_SPI_CLK_SPEED_HZ,
            .mode = 0,
            .flags = 0,
            .queue_size = 1,
            .pre_cb = NULL,
            .post_cb = NULL,
            .command_bits = 0,
            .address_bits = 0,
            .dummy_bits = 0,
    };
    ESP_ERROR_CHECK(spi_bus_add_device(SPI2_HOST, &dev_cfg, &tsc2046_spi_dev));

    // Read cal data from NVS
    ESP_ERROR_CHECK(nvs_open(TSC2046_NVS_NAMESPACE, NVS_READONLY, &nvs_handle));
    err = nvs_get_blob(nvs_handle, TSC2046_NVS_KEY_CAL_DATA, cal_data, &cal_data_size);
    if (err == ESP_ERR_NVS_NOT_FOUND) {
        // Use the raw X and Y values (the other factors are already 0)
        cal_data[0] = 1;
        cal_data[4] = 1;
        ESP_LOGI(TAG, "Calibration data NOT found, using raw data");
    }
    else if(err != ESP_OK) {
        ESP_LOGE(TAG, "Error reading cal data from NVS: %d", err);
        abort();
    }
    else {
        ESP_LOGI(TAG, "Calibration data found: %f, %f, %f, %f, %f, %f", cal_data[0], cal_data[1], cal_data[2], cal_data[3], cal_data[4], cal_data[5]);
    }
    nvs_close(nvs_handle);
}

/**
 * @brief Read the touch screen controller
 *
 * This function will read the touch screen controller.
 * If a valid touch is detected, it will return the X and Y coordinates.
 * If no touch is detected, it will return 0 for X and Y.
 * SAMPLE_COUNT samples will be taken and averaged.
 *
 * @warning This function is not thread safe. It should only be called from one task.
 * @param[in] raw If true, return raw X and Y values. If false, return calibrated X and Y values.
 * @return The touchscreen status (x and y coordinates and pressed or not)
 */
tsc2046_data_t tsc2046_read(bool raw) {
    tsc2046_data_t result;
    const uint8_t tx_data_z[BUFFER_SIZE] =  {CMD_Z1_READ, 0, CMD_Z2_READ, 0, 0};
    const uint8_t tx_data_xy[BUFFER_SIZE] = {CMD_X_READ, 0, CMD_Y_READ, 0, 0};
    uint8_t rx_data[5];
    uint16_t z1;
    uint16_t z2;

    spi_transaction_t spi_tran = {
            .length = BUFFER_SIZE * 8,
            .rxlength = 0,
            .tx_buffer = tx_data_z,
            .rx_buffer = rx_data,
    };

    ESP_ERROR_CHECK(spi_device_polling_transmit(tsc2046_spi_dev, &spi_tran));
    z1 = ((rx_data[1] << 8) + rx_data[2]) >> 3;
    z2 = ((rx_data[3] << 8) + rx_data[4]) >> 3;

    result.x = 0;
    result.y = 0;
    result.state = TSC2046_STATE_RELEASED;

    // If the touch screen is not pressed, return
    if (z1 < Z_THRESHOLD || z2 > 4095 - Z_THRESHOLD) {
        return result;
    }

    // The touch screen is pressed, sample the x and y coordinates, and average the result
    result.state = TSC2046_STATE_PRESSED;
    spi_tran.tx_buffer = tx_data_xy;
    spi_tran.rx_buffer = rx_data;
    for (uint8_t i = 0; i < SAMPLE_COUNT; i++) {
        ESP_ERROR_CHECK(spi_device_polling_transmit(tsc2046_spi_dev, &spi_tran));
        result.x += ((rx_data[1] << 8) + rx_data[2]) >> 3;
        result.y += ((rx_data[3] << 8) + rx_data[4]) >> 3;
    }
    result.x /= SAMPLE_COUNT;
    result.y /= SAMPLE_COUNT;

    // Correct for orientation
    result.x = 4095 - result.x;
    result.y = 4095 - result.y;

    // Apply calibration data if not in raw mode
    if (!raw) {
        result.x = (uint16_t)(cal_data[0] * (float)result.x + cal_data[1] * (float)result.y + cal_data[2]);
        result.y = (uint16_t)(cal_data[3] * (float)result.x + cal_data[4] * (float)result.y + cal_data[5]);
    }

    ESP_LOGD(TAG, "Pressed: x: %d, y: %d", result.x, result.y);

    return result;
}

void tsc2046_calibrate(tsc2046_cal_data_point_t points[], size_t size) {
    // TODO: Implement calibration
}
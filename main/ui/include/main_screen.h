#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_H

#include <time.h>
#include "data_manager.h"

#define SIMULATOR 0

extern lv_obj_t * main_screen;

// Function prototypes
void main_screen_init(void);
void set_power_consumption(uint16_t value);
void set_time(time_t time);
void set_max_peak_line(uint16_t value);
void set_new_max_peak_demand(uint16_t value);
void reset_peak_demand_chart_data(void);
void add_peak_demand_data_point(time_t time, uint16_t value);
void set_predicted_peak(uint16_t value);
void set_wifi_status(bool connected);
void set_connected_status(bool connected);


/**
 * @brief Get the power consumption
 *
 * @return The current power consumption in Watts
 */
static inline uint16_t get_power_consumption(void)
{
#if SIMULATOR
    return lv_rand(0, 5000);
#else
    float current_power_usage;
    data_manager_get_field(DM_DF_CURRENT_POWER_USAGE, &current_power_usage);
    return (uint16_t)(current_power_usage*1000);
#endif
}

/**
 * @brief Get the current time
 *
 * @return The current time
 */
static inline time_t get_time(void)
{
#if SIMULATOR
    return time(NULL);
#else
    time_t timestamp;
    data_manager_get_field(DM_DF_P1_TIMESTAMP, &timestamp);
    return timestamp;
#endif
}

/**
 * @brief Get the max peak of the month
 *
 * @return The max peak in Watts
 */
static inline uint16_t get_max_peak_month(void)
{
#if SIMULATOR
    return lv_rand(1000, 5000) ;
#else
    data_manager_demand_data_point_t max_demand_month;
    data_manager_get_field(DM_DF_MAX_DEMAND_MONTH, &max_demand_month);
    if (max_demand_month.timestamp == 0 || max_demand_month.demand == 0)
    {
        return 2500;
    }
    return (uint16_t)(max_demand_month.demand*1000);
#endif
}

/**
 * @brief Get the predicted peak
 *
 * @return The predicted peak in Watts at the end of the current quarter hour
 */
static inline uint16_t get_predicted_peak(void)
{
#if SIMULATOR
    return lv_rand(1000, 5000) ;
#else
    data_manager_demand_data_point_t predicted_demand;
    data_manager_get_field(DM_DF_PREDICTED_PEAK, &predicted_demand);
    return (uint16_t)(predicted_demand.demand*1000);
#endif
}


#endif //MAIN_SCREEN_H

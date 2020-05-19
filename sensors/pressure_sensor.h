/**************************************************************************/
/*!
    @file     pressure_sensor.h

    @brief 	  Pressure sensor module

    @author   Tworks

	@defgroup VentilatorModule

    Pressure sensor module - allows clients to get sensor readings
	Sensor data is updated to local data structure in a timer
	in frequent intervals
	The same readings can be read or reset using utility APIs
	@{
*/
/**************************************************************************/
#ifndef __PRESSURE_SENSOR_H__
#define __PRESSURE_SENSOR_H__

#include "sensors.h"

/**************************************************************************/
/*!
    @brief  Class to handle Pressure sensor, inherits base sensor class
*/
/**************************************************************************/
class pressure_sensor : public sensor {
	protected:
		int m_dp;					/*!< Flag to store whether the object is pressure sensor or differential pressure sensor */
		int m_adc_channel;			/*!< adc channel where the sensor is connected to */
		Adafruit_ADS1115 *m_ads;	/*!< ADS board where the sensor is connected to */
	protected:
		/**
		 *   @brief  Utility function to read the pressure from MPX5010 sensor
		 *   @return returns the pressure read from the sensor
		 **/
		float get_pressure_MPX5010();
		/**
		 *   @brief  Utility function to read the differential pressure from MPXV7002 sensor
		 *   @return returns the differential pressure read from the sensor
		 **/
		float get_pressure_MPXV7002DP(float vout);
		/**
		 *   @brief  Utility function to read volume of air from spyro for specific sensor
		 *   @return returns the spyro volume 
		 **/
		float get_spyro_volume_MPX7002DP();
		/**
		 *   @brief  Utility function to read volume of air from spyro
		 *   @return returns the spyro volume 
		 **/
		float get_flowrate_spyro(float pressure);
		/**
		 *   @brief  Calibrates pressure sensor during boot
		 *   @return returns 0 on success and -1 on failure
		 **/
		int sensor_zero_calibration();
	public:
		/**
		 *   @brief  Constructor for pressure sensors
		 *           Initializes pressure sensor variables
		 **/
		pressure_sensor(Adafruit_ADS1115 *ads, int adc_channel) : sensor() {
			m_dp = 0; 
			m_ads = ads;
			m_adc_channel = adc_channel;
		}
       /**
		 *   @brief  Function to initialize the O2 sensor
		 *   @return 0 on success and -1 on error
		 **/
		int init();
        /**
		 *   @brief  Function to read sensor data
		 *   @return Returns the readings from sensor
		 **/
		float read_sensor_data();
        /**
		 *   @brief  Function to reset sensor data
		 *   @return None
		 **/
		void reset_sensor_data();
        /**
		 *   @brief  Function to read and update sensor data in local data structures (called in timer interrupt)
		 *   @return None
		 **/
		void update_sensor_data();
};

/**************************************************************************/
/*!
    @brief  Class to handle Differential pressure sensor, inherits base pressure sensor class
*/
/**************************************************************************/
class dpressure_sensor : public pressure_sensor {
	public:
		/**
		 *   @brief  Constructor for differential pressure sensors
		 *           Initializes all variables
		 **/
		dpressure_sensor(Adafruit_ADS1115 *ads, int adc_channel) : pressure_sensor(ads, adc_channel) {
			m_dp = 1;
		}
};

#endif /*__PRESSURE_SENSOR_H__*/
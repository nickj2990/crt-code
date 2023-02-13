/** altimiter.hpp gathers relevant data from the altimiter and updates
 * settings to get more accurate data
*/

/*Libraries*/
#include <movingAvg.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_10DOF.h>


/*Global Variables*/


/*Moving Averages*/
movingAvg baro_alt_avg(50); 
movingAvg baro_vs_avg(1);
movingAvg baro_vavg(5);
movingAvg pressure_avg(1); 
movingAvg press_percent_avg(50); 

/*Sensor objects on 10DOF board*/

Adafruit_10DOF                dof   = Adafruit_10DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_BMP085_Unified       bmp   = Adafruit_BMP085_Unified(18001);

/* flight variables */

double baro_set  = 1000.0; 
float alt_baro      = 0;
float pressure_baro = 0; 
float prev_alt_baro = 0; 
float baro_vspeed   = 0; 
float baro_count    = 0; 
float loop_number = 0;
float loop_speed = 0;
bool new_baro       = false;
bool stable_descent = false; 

/* Timers*/

unsigned long alt_timer_a     = 0; 
unsigned long alt_timer_b     = 0; 
unsigned long baro_blk  = 0;
unsigned long baro_clb  = 0;
unsigned long loop_time = 0;


/** altInit() initializes altimiter and moving averages*/
void altInit() {

}


/**
 * alt_set() calculates vertical speed by change in time and altitude and 
 * sets global variable*/

void alt_set(){

}

void alt_update(){

}

/**
 * vSpeedAlt() calculates vertical speed by change in time and altitude and 
 * sets global variable*/

void alt_vspeed(){

}

void alt_get(){

}

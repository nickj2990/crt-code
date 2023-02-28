/** gps.hpp contains all relevant functions for gps data*/

/** Libraries */
#include <TinyGPS++.h>
#include <movingAvg.h>
#include <SoftwareSerial.h>

/** Moving Averages*/
movingAvg gps_vs_avg(1); 
movingAvg gps_vavg(10); 

/** Global Variables*/
TinyGPSPlus gps;
TinyGPSCustom fix_type(gps, "GNGSA", 2);
static const int GRXPin = 2, GTXPin = 3;
static const uint32_t GPSBaud = 9600;
SoftwareSerial Gss(GRXPin, GTXPin);
float prev_alt_gps = 0; 
float gps_vspeed   = 0; 
unsigned long gpsB = 0;
float prev_cog     = 0; 
bool new_gps = false;
bool new_cog = false;
bool gps_ok = false; 
bool cog_ok = false; 

/** gpsSetup() initializes gps*/
void gpsSetup(){

}

/**
 * gpsHealth() gets relevant data about data health and 
 * updates global variables.
 * 
 * Test Location age, Fix Type, Course updated, Altitude updated*/

void gpsHealth(){

}

/** 
 * vSpeed_GPS() computes speed given time and distance*/
 void gpsVspeed(){

 }


/** gpsData() gathers all relevant data and returns it as a string*/
String gpsData(){

}

/* gpsCourseToHome() takes position arguments lat, lon, homelat, homelon 
and returns the course to home*/
float gpsCourseToHome(){

}

/** gpsAngle(ci,cf) computes the difference in angle between current course 
 * and course to home returns an angle in (-180,180)*/

Float gpsAngle(ci,cf){

}
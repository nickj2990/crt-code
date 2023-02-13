/** Merged Position Uses the data from gps and altimiter to weight 
 * positional values and their derivatives.
*/
// Fusion of altitude from GPS and barometer
float merged_alt = 0; 
// Fused vertical speed from GPS and barometer
float merged_vspeed = 0; 
// Altitude weight from barometer
float baro_alt_weight = 1;
// Altitude weight from GPS
float gps_alt_weight = 1; 


// Vertical speed weight from barometer
float baro_vspeed_weight = 1;
// Vertical speed weight from GPS
float gps_vspeed_weight = 1; 
// Altitude of launch point
float ground_altitude = 0;
// stability timer
unsigned long tstab = 0; 

// stability factor for gps 
float gps_stab_factor = 0; 

// stability factor for barometer
float baro_stab_factor = 0; 

bool new_baro_fusion = false;
bool new_gps_fusion = false; 

//Moving averages for gps, barometer, and pressure percentage
movingAvg gps_v(GPS_SAFE_AVG); 
movingAvg baro_v(BARO_SAFE_AVG);
movingAvg ps_p(PRE_PE_AVG);  

//Pressure percentage
double pressure_percentage;
// Begins position moving averages
// Initializes the global variables
void position_setup() {
}

// computes fused altitudes and sets glopbal variables
// 1) computes altitude weights
// 2) computes vertical speed weights
//3) computes fused altitude
// 2) computes fusedvertical speed
void cmpt_fusion() {
}

// Sets global boolean variables for new barometer and reading
void cmpt_vertical_state() {
}


// Computes the pressure square root ratio for altitude
// for tranalting pressure reading to altitude
float pressure_sqrt_ratio() {
}

// Forms a string of the relevant position data
String pos_text() {
}


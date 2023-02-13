/** gps.hpp contains all relevant functions for gps data*/

/** Libraries */
#include <TinyGPS++/TinyGPS++.h>
#include <movingAvg.h>
#include <SoftwareSerial.h>
#include <string>

/** Moving Averages*/
movingAvg gps_vs_avg(1); 
movingAvg gps_vavg(10); 

/** Global Variables*/
TinyGPSPlus gps;
TinyGPSCustom fix_type(gps, "GNGSA", 2);
static const int GRXPin = 2, GTXPin = 3;
static const uint32_t GPSBaud = 9600;
SoftwareSerial Gss(GRXPin, GTXPin);
double prev_alt = 0; 
int prev_time = 0;
//double alt_gps = 0;
//uint32_t cur_time = 0;
//float gps_vspeed   = 0; 
//unsigned long gpsB = 0;
//float prev_cog     = 0; 
//bool new_gps = false;
//bool new_cog = false;
bool gps_ok = false; 
//bool cog_ok = false;

static const double HOME_LAT = 51.508131, HOME_LON = -0.128002;

/** gpsSetup() initializes gps*/
void gpsSetup(){
    prev_alt = gps.altitude.meters();
    prev_alt_time = gps.time.value();
    // Debug: if we haven't seen lots of data in 5 seconds, something's wrong.
    if (millis() > 5000 && gps.charsProcessed() < 10) // uh oh
    { 
        gps_ok = false;
    }
    else{
        gps_ok = true;
    }
}

/** gpsData() gathers all relevant data and returns it as a string printing out 
 * latitude, longitude, hdop, speed, altitude, course, satellites, date, time. */
String gpsData(){
    string gpsData;
    if(gps.location.isUpdated()){
        string loc = "LOCATION      Fix Age=";
        loc += to_string(gps.location.age());
        loc += " Lat=";
        loc += (gps.location.rawLat().negative ? "-" : "+");
        loc += to_string(gps.location.rawLat().deg);
        loc += "[+";
        loc += to_string(gps.location.rawLat().billionths);
        loc += " billionths],  Long=";
        loc += (gps.location.rawLng().negative ? "-" : "+");
        loc += to_string(gps.location.rawLng().deg);
        loc +=.print("[+");
        loc += to_string(gps.location.rawLng().billionths);
        loc += " billionths],  Lat="; //maybe remove later (cuz not in deg)
        loc += to_string(gps.location.lat(), 6);
        loc += " Long=";
        loc += to_string(gps.location.lng(), 6);
        loc += " HDOP=";
        loc += to_string(gps.hdop.value());
        loc += " hdop age=";
        loc += to_string(gps.hdop.age());
    }

    if(gps.speed.isUpdated()){
        string speed = "SPEED       Fix Age=";
        speed += to_string(gps.speed.age());
        speed += " m/s=";
        speed += to_string(gps.speed.mps());
    }

    if(gps.altitude.isUpdated()){
        string vert = "ALTITUDE     Fix Age=";
        vert += to_string(gps.altitude.age());
        vert += " Meters=";
        vert += to_string(gps.altitude.meters());
        vert += " VDOP=";
        vert += to_string(gps.vdop.value());
        vert += " vdop age=";
        vert += to_string(gps.vdop.age());
    }

    if(gps.course.isUpdated()){
        string course = "COURSE     Fix Age=";
        course += to_string(gps.course.age());
        course += " Deg =";
        course += to_string(gps.course.deg());
    }

    if(gps.satellites.isUpdated()){
        string sat = "SATTELLITES   Fix Age=";
        sat += to_string(gps.satellites.age());
        sat += " Num=";
        sat += to_string(gos.sattellites.value());
    }

    if(gps.date.isUpdated()){
        string date = "DATE     Fix Age=";
        date += to_string(gps.date.age());
        date += "ms Raw=";
        date += to_string(gps.date.value());
    }

    if(gps.time.isUpdated()){
        string gpsTime = "TIME     Fix Age=";
        gpsTime += to_string(gps.time.age());
        gpsTime + "ms Raw=";
        gpsTime += to_string(gps.time.value());
    }

    gpsData = loc + speed + vert + course + sat + date + gpsTime;
    Serial.println(loc);
    Serial.println(speed);
    Serial.println(vert);
    Serial.println(course);
    Serial.println(sat);
    Serial.println(date);
    Serial.println(gpsTime);
    return gpsData;
}

/* gpsCourseToHome() takes position arguments lat, lon, homelat, homelon 
and returns the course to home*/
double gpsCourseToHome(){ 
    double courseToHome = TinyGGPSPlus::courseTo(
        gps.location.lat(), 
        gps.location.lng(), 
        HOME_LAT, 
        HOME_LON);
    courseToHome = TinyGPSPlus::cardinal(courseToHome); // don't know return type of cardinal
    return courseToHome;
}

/* gpsDistToHome() takes position arguments lat, lon, homelat, homelon 
and returns the distance to home in meters*/
double gpsDistToHome(){
    double distToHome = TinyGPSPlus::distanceBetween(
        gps.location.lat(), 
        gps.location.lng(), 
        HOME_LAT, 
        HOME_LON);
    return distToHome/1000;
}

/* ishorzHealthy returns true if the location and hdop has been updated recently and if the hdop < 2, otherwise false.  */
bool hIsHealthy(){
    if(gps.location.isValid() && gps.location.isUpdated() && gps.location.age() <= 1000){
        if(gps.hdop.isUpdated() && gps.hdop.age()<= 1000 && gps.hdop.value() <= 2){
            return true;
        }   
    }
    return false;
}

/* isVertHealthy returns true if the location and hdop has been updated recently and if the hdop < 2, otherwise false.  */
bool vIsHealthy(){
     if(gps.altitude.isValid() && gps.altitude.isUpdated() && gps.altitude.age() <= 1000){
        if(gps.vdop.isUpdated() && gps.vdop.age()<= 1000 && gps.vdop.value() <= 2){
            return true;
        }   
    }
    return false;
}

/* returns the vertical speed in meter per second and updates prev_alt, prev_alt_time */
double gpsVSpeed(){
    vSpeed = 0;
    if(vIsHealthy()){
        vSpeed = (gps.altitude.meters() - prev_alt_gps)/timeSince(gps.time.value(), prev_alt_time);
        prev_alt = gps.altitude.meters(); 
        prev_alt_time  = gps.time.value(); // maybe have to account for age?? - don't think so.
    }
    return vSpeed;
}

/* Returns the difference between two times formatted HHMMSSCC in seconds*/
double timeSince(int cur, int prev){
    cur = cur % 1000;
    prev = prev % 1000;
    double timeDiff = 0.0;
    if( cur < prev){
        cur += 6000;
        timeDiff = cur - prev;
    }
    else{
        timeDiff = cur - prev;
    }
    return timeDif/100;
}



// /** gpsAngle(ci,cf) computes the difference in angle between current course 
//  * and course to home returns an angle in (-180,180)*/

// Float gpsAngle(ci,cf){
// }

// String gpsData2(){
//     String spacer = ", ";
//     String rawLat =  (gps.location.rawLat().negative ? "-" : "+");
//     std::string lat = gps.location.lat();
//     String rawLng =  (gps.location.rawLng().negative ? "-" : "+");
//     std::string lng = gps.location.lng();
//     std::string alt = std::to_string(gps.altitude.meters());
//     std::string date = std::to_string(gps.date.value());
//     std::string time = std::to_string(gps.time.value());
//     std::string vspeed = std::to_string(gps_vspeed);
//     std::string satellites = std::to_string(gps.satellites.value());
    
//     String data = rawLat + spacer + lat + spacer +
//     rawLng + spacer + Lng + spacer +
//     alt + spcacer + date + spacer + time + spacer + vspeed + spacer + satellites;

//     String data = ("Lat: %s%s\n Lng: %s%s\n Altitude: %s\n Date: %s\n Time: %s\n Vspeed: %s\n Satellites: %s\n", 
//     rawLat, lat, rawLng, Lng, alt, date, time, vspeed, satellites);
    
//     return data;
// }

// String gpsDat3(){
//     String gpsdata = gps.hdop.value() + ", " + 
//     (gps.location.rawLat().negative ? "-" : "+") + ", " +
//     gps.location.lat() + ", " + 
//     (gps.location.rawLng().negative ? "-" : "+") + ", " +
//     gps.location.lng() + ", " + 
//     gps.altitude.meters() + ", " +
//     gps.date.value() + ", " +
//     gps.time.value() + ", " +
//     gps_vspeed + ", " +
//     gps.satellites.value();

//     Serial.println(gpsdata);

//     return gpsdata;
// }

// /** 
//  * vSpeed_GPS() computes speed given time and distance*/
//  void gpsVspeed(){
//     if(new_gps){
//         gps_vspeed = (alt_gps - prev_alt_gps)/(time);
//         time = 0;
//         prev_alt_gps = alt_gps;
//     }
//  }

// /**
//  * gpsHealth() gets relevant data about data health and 
//  * updates global variables.
//  * 
//  * Test Location age, Fix Type, Course updated, Altitude updated*/
// //
// void gpsHealth(){
//     if(gps.location.age() < age && gps.altitude.isUpdated() && gps.course.isUpdated()){
//         time += gps.altitude.age();
//         cur_altitude = gps.altitude.meters();
//         new_gps = true;
//         gpsVspeed();
//         new_gps = false;
//     }
//     else{
//         new_gps = false;
//     }
// }



//NOTES
// Validity, Update status, and Age
// You can examine an object’s value at any time, but unless TinyGPS++ has recently been fed from the GPS, 
// it should not be considered valid and up-to-date. The isValid() method will tell you whether the object 
// contains any valid data and is safe to query.

// Similarly, isUpdated() indicates whether the object’s value has been updated (not necessarily changed) 
// since the last time you queried it.

// Lastly, if you want to know how stale an object’s data is, call its age() method, which returns the number of 
// milliseconds since its last update. If this returns a value greater than 1500 or so, it may be a sign of a 
// problem like a lost fix

//need to investigate what course returns (aka course not course to home)
//perhaps don't need isUpdated() in getData
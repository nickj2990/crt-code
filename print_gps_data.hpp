
/** gps.hpp contains all relevant functions for gps data*/

/** Libraries */
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
//#include <movingAvg.h>
#include <SD.h>
 
File myFile;


/** Global Variables*/
TinyGPSPlus gps;
double prev_alt = 0; 
int prev_time = 0;

int locAge;
bool isLatNeg;
double latitude;
float latDeg;
bool isLonNeg;
float lonDeg;
double longitude;
int hdop;
float velocity;
float altitude;
double course;
char cardinalCourse;
int satNum;
String date;
String time;
double courseToHome;
unsigned long distanceToHome;
char cardinalHome;
String gpsData;
int maxloops = 100;

static const double HOME_LAT = 51.508131, HOME_LON = -0.128002;
int loopah = 0;

 
void setup()
{
  Serial.begin(115200);
  Serial1.begin(9600);
  Serial1.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
   pinMode(53, OUTPUT);
 
  if (!SD.begin(53)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
 
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.

  myFile = SD.open("test.txt", FILE_WRITE);
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println(getGPSData());
	// close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  
  Serial.println(F("An extensive example of many interesting TinyGPSPlus features"));
  Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println();
  Serial.println(F("Sats HDOP  Latitude   Longitude   Fix  Date       Time     Date Alt    Course Speed Card  Distance Course Card  Chars Sentences Checksum"));
  Serial.println(F("           (deg)      (deg)       Age                      Age  (m)    --- from GPS ----  ---- to London  ----  RX    RX        Fail"));
  Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------------"));
}
 


void loop(){
while (loopah<=maxloops) {
{
  loopah+=1;
  myFile = SD.open("test.txt", FILE_WRITE);
 
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println(getGPSData());
	// close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
  
  static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;
  satNum = gps.satellites.value();
  printInt(satNum, gps.satellites.isValid(), 5);
  hdop = gps.hdop.hdop();
  printFloat(hdop, gps.hdop.isValid(), 6, 1);
  latitude = gps.location.lat();
  printFloat(latitude, gps.location.isValid(), 11, 6);
  longitude = gps.location.lng();
  printFloat(longitude, gps.location.isValid(), 12, 6);
  locAge = gps.location.age();
  printInt(locAge, gps.location.isValid(), 5);
  printDateTime(gps.date, gps.time);
  altitude = gps.altitude.meters();
  printFloat(altitude, gps.altitude.isValid(), 7, 2);
  course = gps.course.deg();
  printFloat(course, gps.course.isValid(), 7, 2);
  velocity = gps.speed.mps();
  printFloat(velocity, gps.speed.isValid(), 6, 2);
  const char *cardinalCourseToHome = TinyGPSPlus::cardinal(course);
  cardinalCourse = *cardinalCourseToHome;
  printStr(gps.course.isValid() ? TinyGPSPlus::cardinal(course) : "*** ", 6);

  unsigned long distanceToHome =
    (unsigned long)TinyGPSPlus::distanceBetween(
      gps.location.lat(),
      gps.location.lng(),
      LONDON_LAT, 
      LONDON_LON) / 1000;
  printInt(distanceToHome, gps.location.isValid(), 9);

  double courseToHome =
    TinyGPSPlus::courseTo(
      gps.location.lat(),
      gps.location.lng(),
      LONDON_LAT, 
      LONDON_LON);
      
  printFloat(courseToHome, gps.location.isValid(), 7, 2);

  const char *cardinalToHome = TinyGPSPlus::cardinal(courseToHome);
  cardinalHome = *cardinalToHome;

  printStr(gps.location.isValid() ? cardinalToHome : "*** ", 6);

  printInt(gps.charsProcessed(), true, 6);
  printInt(gps.sentencesWithFix(), true, 10);
  printInt(gps.failedChecksum(), true, 9);
  gpsData = "Sat Num: " + String(satNum) + "  HDOP: " + String(hdop) + "  Lat: " + String(latitude, 6) + "  Long: " + 
            String(longitude, 6) + "  loc age: " + 
            String(locAge) + "  Date:" + String(date) + "  Time: " + String(time) + "  Altitude: " + 
            String(altitude) + "  Course: " + 
            String(course) + "  Velocity(m/s): " + String(velocity) + "  Cardinal Course: " + cardinalCourse + "  Course to Home: " + String(courseToHome) + ' ' + 
            String(distanceToHome) + "  Dist. Home (km): " + "  Cardinal Home: " + cardinalHome;
  Serial.println();
  Serial.println(gpsData);
  
  smartDelay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
}
}

// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (Serial1.available())
      gps.encode(Serial1.read());
  } while (millis() - start < ms);
}

static void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len)
{
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartDelay(0);
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{
  if (!d.isValid())
  {
    Serial.print(F("********** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    date = String(sz);
    Serial.print(sz);
  }
  
  if (!t.isValid())
  {
    Serial.print(F("******** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    time = String(sz);
    Serial.print(sz);
  }

  printInt(d.age(), d.isValid(), 5);
  smartDelay(0);
}

static void printStr(const char *str, int len)
{
  int slen = strlen(str);
  for (int i=0; i<len; ++i)
    Serial.print(i<slen ? str[i] : ' ');
  smartDelay(0);
}

/** Returns course to home in degrees */
float getCourseToHome(){
    return courseToHome;
}

/** Returns cardinal direction course to home*/
char getCardinalCourseToHome(){
  return cardinalCourse;
}

/** Returns distance to home in kilometers. */
double getDistToHome(){
    return distanceToHome;
}

double getLatitude(){
    return latitude;
}

double getLongitude(){
    return longitude;
}

/** Returns horizontal dilution of precision
--------input which values are generally good/bad ------*/
int getHDOP(){ 
    return hdop;
}

/** Returns horizontal velocity in meters/second. */
double getVelocity(){
    return velocity;
}

/** Returns altitude in meter. s*/
double getAltitude(){
    return altitude;
}

/** Returns course in degrees*/
double getCourseOverGround(){
    return course;
}

/** Returns the cardinal direction of the current course */
char getCardinalCourseOverGround(){
  return cardinalCourse;
}

int getNumSatellites(){
    return satNum;
}

String getDate(){
    return date;
}

/** Returns String with all GPS data: Number Satellites, HDOP,
 *  latitude(deg), longitude(deg), date, time, altitude (meters), 
 *  course (deg), velocity (meters), cardinal course, distance to home (km),
 *  course to home (deg), cardinal course to home. */
String getGPSData(){
  return gpsData;
}


/* ishorzHealthy returns true if the location and hdop has been updated recently and if the hdop < 2, otherwise false.  */
bool ishorzHealthy(){
    if(gps.location.isValid() && gps.location.isUpdated() && gps.location.age() <= 1000){
        if(gps.hdop.isUpdated() && gps.hdop.age()<= 1000 && gps.hdop.value() <= 2){
            return true;
        }   
    }
    return false;
}

/* isVertHealthy returns true if the location and hdop has been updated recently and if the hdop < 2, otherwise false.  */
bool isVertHealthy(){
     if(gps.altitude.isValid() && gps.altitude.isUpdated() && gps.altitude.age() <= 1000){
        if(gps.hdop.isUpdated() && gps.hdop.age()<= 1000 && gps.hdop.value() <= 2){
            return true;
        }   
    }
    return false;
}

/* returns the vertical speed in meter per second and updates prev_alt, prev_alt_time */
// double gpsVSpeed(){
//     vSpeed = 0;
//     if(vIsHealthy()){
//         vSpeed = (gps.altitude.meters() - prev_alt_gps)/timeSince(gps.time.value(), prev_alt_time);
//         prev_alt = gps.altitude.meters(); 
//         prev_alt_time  = gps.time.value(); // maybe have to account for age?? - don't think so.
//     }
//     return vSpeed;
// }

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
    return timeDiff/100;
}




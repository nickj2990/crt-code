/** flight_phase.hpp moves through the stages of flight to 
 * decide when to take action
*/

// Phase of flight to dictate action
int flight_mode   = 0; 

// Altitudes of deployment 
int dep_altitude  = 0; 

// Last flight mode
int prev_flight_mode = 0; 

// Has the flight been intialized?
bool initialised  = false;

// Has the flight started?
bool flight_started = false;

// Has the payload been deployed?
bool deployed     = false; 

// Has the parachute opened to gliding 
bool wing_opened  = false; 

// Is it spiraling?
bool spiral = false;

// Has the payload been separated?
bool separation = false;

//How long has the payload been spiraling?
unsigned long spiral_time = 0; 

// How long has it been since initialization?
unsigned long init_time = 0; 


/**
 * fsInit() checks that the gps is ok and initializes sensors/ moving averages 
 * then goes to flight stage 1*/
void fsInit(){

}

/**
 * fsLaunchMode() 
 * 1) if GPS has no fix -> fsInit 
 * 2) if vSpeed is positive and above threshhold -> fsBooster()
 * 3) if vSpeed is negative beyond threshhold -> fsDrogue() */
void fsLaunchMode(){

}

/**
 * fsBooster() 
 * 1) if GPS has no fix -> fsInit ()
 * 2) if vSpeed is positive and above threshhold -> fsBooster()
 * 3) if vSpeed is negative beyond threshhold -> fsDrogue() */
void fsBooster(){

}

/** fsDrogue() - Descent before parachute deployment
* 1) Checks for ascent -> fsBooster()
* 2) Checks for parafoil deployment -> Flight mode */
void fsDrogue(){

}

/** fsMain() - Navigation flight phase
 * 1) Checks for spiral -> fsSpiral()
 * 2) Checks for landing -> fsLanded()
* 3) Checks for glide -> navigates -> fsMain()*/
void fsMain(){

}

/**fsSpiral() - spiraling flight phase
 * 1) Checks for glide -> fsMain()*/
void fsSpiral(){
} 

 /** fsLanded() - landed function 
* 1) Checks for landing -> fsLanded()
* 2) Checks for glide -> navigates -> fsMain()*/
void fsLanded(){

}

/** fsSwitch cycles through flight stages*/

void fs_Switch() {
  if (flight_mode!=prev_flight_mode and prev_flight_mode !=0) {
      prev_flight_mode = flight_mode; 
  }
  switch(flight_mode) { 
    case 0: 
      fsInit(); 
    break;

    case 1: 
      fsLaunchMode(); 
    break;

    case 2: 
      fsBooster(); 
    break;

    case 3: 
      fsDrogue();
    break;

    case 4: 
      fsMain(); 
    break;

    case 5: 
      fsSpiral();
    break;

    case 6: 
      fsLanded(); 
    break; 
  }
}
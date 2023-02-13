/** servos.hpp contains all functions interacting with servos*/
#include <PWMServo.h>
//Servos
PWMServo steer;
PWMServo left; 
PWMServo right; 

int servo_left  = 0;
int servo_right = 0;
int servo_aux   = 0; 
unsigned long pwm_timer = 0; 

struct servo_cmd {
  float left = 1500;
  float right = 1500; 
  };



//Servos
void servo_setup() {
  left.attach(9, 1000, 2000);  
  right.attach(10, 1000, 2000); 

}


servo_cmd calc_servo(int autopilot, int flight_mode, bool deployed, bool cog_ok, bool spiral, bool separation){

}

void update_servo_cmd(servo_cmd steering_apply, unsigned int a) {
   
  if ((millis()-pwm_timer)>=(1000/a)) {  
    pwm_timer = millis(); 
    left.write(map(steering_apply.left, 1000, 2000, 0, 180));
    right.write(map(steering_apply.right, 1000, 2000, 0, 180)); 
   // if(DEBUG){
         // Serial.println("servo command updated");
         // Serial.println(steering_apply.left);
         // Serial.println(steering_apply.right);
       // }
    
    
  }
 
}
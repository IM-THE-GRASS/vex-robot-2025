#include "main.h"

void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "we're cooked");
}

//runs when robot disabled b4 match
void disabled() {}

//runs b4 autonomous but after initialize
void competition_initialize() {}

//runs during autonomous
void autonomous() {

}

//runs during the driver control period
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::MotorGroup left_mg({-6, 8, -7});  
	pros::MotorGroup right_mg({-1, -3, -5});  
	pros::Motor intake_motor(9); 
	pros::ADIDigitalOut claw_pneumatic = pros::ADIDigitalOut('B'); 
	while (true) {
		int turn = master.get_analog(ANALOG_LEFT_X);
		int dir = master.get_analog(ANALOG_RIGHT_Y); 
		left_mg.move(dir - turn);
		right_mg.move(dir + turn);
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			intake_motor.move(127);
		}
		else {
			if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			intake_motor.move(-127);
			}
			else {
				intake_motor.move(0);
			}
		} 
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
			claw_pneumatic.set_value(true); 
		}
		else{
			if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
				claw_pneumatic.set_value(false); 
			}
		}
		pros::delay(20);
	}
}
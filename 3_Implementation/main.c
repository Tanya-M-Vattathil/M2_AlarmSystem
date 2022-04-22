//MOTOR_A
#define EN_A       DDB3		 //PWM Enable Motor 1				-- Pin 11 / OCOA
#define IN1_DDR    DDC4		 //DATA DIRECTION REGISTER~~~Control direction  of Motor 1	-- Pin A4
#define IN2_DDR    DDC5		 //DATA DIRECTION REGISTER~~~Control direction of Motor 1    -- Pin A5
#define IN1_PORT   PORTC4    //PORT~~~Control direction of Motor 1	-- Pin A4
#define IN2_PORT   PORTC5    //PORT~~~Control direction of Motor 1    -- Pin A5

//MOTOR_B
#define EN_B		   DDD3      //PWM Enable Motor 2				-- Pin 3 / OCOB
#define IN3_DDR    DDC3      //DATA DIRECTION REGISTER~~~Control direction of Motor 2	-- Pin A3
#define IN4_DDR    DDC2      //DATA DIRECTION REGISTER~~~Control direction of Motor 2    -- Pin A2
#define IN3_PORT   PORTC3    //PORT~~~Control direction of Motor 1	-- Pin A3
#define IN4_PORT   PORTC2    //PORT~~~Control direction of Motor 1    -- Pin A2

//SERVO
#define SERVO	   DDB1		//SERVO SIGNAL	pin 9

//ULTRASONIC SENSOR
#define echoPin 7
#define trigPin 8

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void setup();

void setup()
{
	
	DDRB |= (1<<DDB5); //Led output
	
	DDRB |= (1<<SERVO);
	
	// motor A
	DDRB |= (1<<EN_A); //pin 6 output PWM
	DDRC = (1<<IN1_DDR) | (1<<IN2_DDR); // A4,A5 pins for controlling the direction of motor
	
	//motor B
	DDRD |= (1<<EN_B); //pin 5 output PWM
	DDRC = (1<<IN3_DDR) | (1<<IN4_DDR); //2,4 pins for controlling the direction of motor B
	
	TCCR2A = (1<<COM2A1) | (1<<COM2B1) | (1<<WGM21) | (1<<WGM20); //clear pin on compare match, update pin on BOTTOM, TOPT= 0xFF
	TCCR1A = (1<<COM1A1) | (1<<COM1A0) | (1<<WGM11); // inverting mode fast pwm with icr1 reg as top
	
	
	TIMSK2 = (1<<TOIE2); // interupt on overflow
	
	
	OCR2A = (dutyA/100) *255;
	OCR2B = (dutyB/100) *255;
	ICR1 = 39999; 
	
	sei();
	
	TCCR2B = (1<<CS22) | (1<<CS21) | (1<<CS20); //clk source, prescalar 1024
	TCCR1B  = (1<<WGM13) |(1<<WGM12)|(1<<CS11); //Prescalar = 8
	
	delay(3000);
}

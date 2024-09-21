/**********************************************************************************************

                                PMW Motor Control System

To create a motor control system using C programming, we will simulate controlling a simple DC motor by adjusting its speed
and direction using Pulse Width Modulation (PWM). This approach is commonly used in embedded systems for motor control, 
where the PWM signal controls the power supplied to the motor. Below are the components and the setup required for this basic
motor system.

Components:
Motor Speed Control: Controlled by varying the duty cycle of the PWM signal.
Motor Direction Control: Controlled by setting GPIO pins to HIGH or LOW.
Here’s the basic structure of a C program to control the motor:

Setup:
PWM Signal: Generate a PWM signal to control motor speed.
GPIO Control: Control motor direction using GPIO pins (assuming embedded system hardware like Arduino, STM32, etc.).


*****************************************************************************/

#include <stdio.h>
#include <unistd.h> // For sleep function (to simulate delays)

// Simulate GPIO pins for motor direction
#define GPIO_PIN_MOTOR_FORWARD 1
#define GPIO_PIN_MOTOR_BACKWARD 0

// Simulate PWM signal
void setMotorSpeed(int dutyCycle) {
    if (dutyCycle >= 0 && dutyCycle <= 100) {
        printf("PWM Signal: Motor running at %d%% speed\n", dutyCycle);
    } else {
        printf("Error: Invalid duty cycle. Must be between 0 and 100.\n");
    }
}

// Function to control motor direction
void setMotorDirection(int direction) {
    if (direction == GPIO_PIN_MOTOR_FORWARD) {
        printf("Motor Direction: Forward\n");
    } else if (direction == GPIO_PIN_MOTOR_BACKWARD) {
        printf("Motor Direction: Backward\n");
    } else {
        printf("Error: Invalid direction\n");
    }
}

// Function to stop the motor
void stopMotor() {
    printf("Motor stopped\n");
}

int main() {
    int speed = 0;
    int direction = GPIO_PIN_MOTOR_FORWARD;
    
    printf("Motor Control System\n");

    // Set motor direction to forward
    setMotorDirection(direction);
    
    // Simulate increasing speed
    for (speed = 0; speed <= 100; speed += 10) {
        setMotorSpeed(speed);
        sleep(1); // Delay to simulate the motor ramping up
    }
    
    // Change motor direction to backward
    direction = GPIO_PIN_MOTOR_BACKWARD;
    setMotorDirection(direction);
    
    // Simulate decreasing speed
    for (speed = 100; speed >= 0; speed -= 10) {
        setMotorSpeed(speed);
        sleep(1); // Delay to simulate the motor ramping down
    }
    
    // Stop the motor
    stopMotor();

    return 0;
}

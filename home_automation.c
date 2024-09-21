/**********************************************************************************************

                            Raspberry Pi Home Automation System

Creating a home automation system using C programming typically involves interfacing with hardware components such as sensors, 
actuators (like lights and fans), and communication modules (like Wi-Fi or Bluetooth). 
For this example, we will provide a simple home automation system that can:

Control Lights: Turn lights on and off.
Control a Fan: Adjust fan speed.
Monitor Temperature: Read temperature from a sensor and take actions based on the temperature.
In this project we use Raspberry Pi, as it's a popular platform for home automation and supports C programming for GPIO manipulation. 

Components Required:

1.Raspberry Pi 
2. LEDs or Lights 
3. DC Fan with a Motor Driver 
4. Temperature Sensor 
5. Resistors, Breadboard, and Jumper Wires
6. Power Supply for the fan and sensors
7.C Compiler installed on the Raspberry Pi

Setup Overview

Connect LEDs/Lights: Use GPIO pins to control the LEDs representing lights.
Connect Fan: Use a motor driver to control the fan's speed via PWM.
Connect Temperature Sensor: Interface the temperature sensor with the GPIO pins to read temperature data.

*****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <unistd.h>

// Define GPIO pins using WiringPi numbering
#define LIGHT_PIN 0         // GPIO17
#define MOTOR_PIN1 1        // GPIO18
#define MOTOR_PIN2 2        // GPIO27
#define FAN_PWM_PIN 3       // GPIO22
#define TEMP_SENSOR_PIN 4   // ADC Channel (Assuming MCP3008 setup)

// Temperature threshold in Celsius
#define TEMP_THRESHOLD 30

// Function to initialize GPIO pins
void setupGPIO() {
    if (wiringPiSetup() == -1) {
        printf("WiringPi setup failed!\n");
        exit(1);
    }

    // Set pin modes
    pinMode(LIGHT_PIN, OUTPUT);
    pinMode(MOTOR_PIN1, OUTPUT);
    pinMode(MOTOR_PIN2, OUTPUT);
    pinMode(FAN_PWM_PIN, OUTPUT);

    // Initialize PWM for fan speed control
    if (softPwmCreate(FAN_PWM_PIN, 0, 100) != 0) {
        printf("PWM initialization failed!\n");
        exit(1);
    }

    // Initialize Light and Fan to OFF
    digitalWrite(LIGHT_PIN, LOW);
    digitalWrite(MOTOR_PIN1, LOW);
    digitalWrite(MOTOR_PIN2, LOW);
    softPwmWrite(FAN_PWM_PIN, 0);
}

// Function to read temperature from ADC (Mock function)
float readTemperature() {
    // In a real scenario, read from MCP3008 or another ADC
    // Here, we'll simulate temperature for demonstration
    // Replace this with actual ADC reading code
    // Example for MCP3008 would involve SPI communication
    // For simplicity, return a fixed value or random

    // Simulate temperature
    return 25.0 + (rand() % 100) / 10.0; // 25.0 to 35.0 Celsius
}

// Function to turn light ON
void lightOn() {
    digitalWrite(LIGHT_PIN, HIGH);
    printf("Light turned ON.\n");
}

// Function to turn light OFF
void lightOff() {
    digitalWrite(LIGHT_PIN, LOW);
    printf("Light turned OFF.\n");
}

// Function to set fan speed (0 to 100)
void setFanSpeed(int speed) {
    if (speed < 0) speed = 0;
    if (speed > 100) speed = 100;
    softPwmWrite(FAN_PWM_PIN, speed);
    printf("Fan speed set to %d%%.\n", speed);
}

// Function to stop the fan
void stopFan() {
    setFanSpeed(0);
    // Also stop motor direction
    digitalWrite(MOTOR_PIN1, LOW);
    digitalWrite(MOTOR_PIN2, LOW);
    printf("Fan stopped.\n");
}

// Function to start the fan in forward direction
void startFanForward(int speed) {
    digitalWrite(MOTOR_PIN1, HIGH);
    digitalWrite(MOTOR_PIN2, LOW);
    setFanSpeed(speed);
    printf("Fan started in forward direction.\n");
}

// Function to start the fan in backward direction
void startFanBackward(int speed) {
    digitalWrite(MOTOR_PIN1, LOW);
    digitalWrite(MOTOR_PIN2, HIGH);
    setFanSpeed(speed);
    printf("Fan started in backward direction.\n");
}

int main() {
    int choice;
    int speed;
    float temperature;

    // Seed random number generator for temperature simulation
    srand(time(NULL));

    setupGPIO();

    printf("=== Home Automation System ===\n");

    while (1) {
        printf("\nSelect an option:\n");
        printf("1. Turn Light ON\n");
        printf("2. Turn Light OFF\n");
        printf("3. Set Fan Speed\n");
        printf("4. Read Temperature\n");
        printf("5. Automatic Fan Control based on Temperature\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                lightOn();
                break;
            case 2:
                lightOff();
                break;
            case 3:
                printf("Enter fan speed (0-100): ");
                scanf("%d", &speed);
                setFanSpeed(speed);
                break;
            case 4:
                temperature = readTemperature();
                printf("Current Temperature: %.2f°C\n", temperature);
                break;
            case 5:
                temperature = readTemperature();
                printf("Current Temperature: %.2f°C\n", temperature);
                if (temperature > TEMP_THRESHOLD) {
                    printf("Temperature exceeds threshold! Turning fan ON.\n");
                    startFanForward(75); // Set fan speed to 75%
                } else {
                    printf("Temperature is below threshold. Turning fan OFF.\n");
                    stopFan();
                }
                break;
            case 6:
                printf("Exiting...\n");
                stopFan();
                lightOff();
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

        // Small delay
        delay(500);
    }

    return 0;
}

#include "TurtleController.h"

#include <Arduino.h>
#include <ezButton.h>
//#include <math.h>

const int ADC_MAX = 4095;

#pragma region constructors
Joystick::Joystick() : xPin(0), yPin(0), zButton(ezButton(0)){
    setup();
}

Joystick::~Joystick(){}

/*Joystick::Joystick(const Joystick& other): xPin(other.xPin), yPin(other.yPin), maxVoltage(other.maxVoltage), zButton(ezButton(other.zButton.)){
   setup();
}*/

Joystick::Joystick(int xPin, int yPin, int zPin): xPin(xPin), yPin(yPin), zButton(ezButton(zPin)){
    setup();
}

/*Joystick& Joystick::operator=(const Joystick& other){
    xPin = other.xPin; // grab other's pin numbers
    yPin = other.yPin;
    zPin = other.zPin;
    maxVoltage = other.maxVoltage;
    zButton = ezButton(other.zPin);
    
}*/
#pragma endregion constructors



float Joystick::getX(float deadzone = 0){
    u_int16_t adcReadout = analogRead(xPin); // get output 
    float output = (adcReadout - (ADC_MAX/2.0f)) / (ADC_MAX/2.0f); // normalize to range of -1 to 1
    if(abs(output) < deadzone){
        return 0;
    }
    else{
        return output;
    }
    
}

float Joystick::getY(float deadzone = 0){
    u_int16_t adcReadout = analogRead(yPin); // get output 
    float output = (adcReadout - (ADC_MAX/2.0f)) / (ADC_MAX/2.0f); // normalize to range of -1 to 1
    if(abs(output) < deadzone){
        return 0;
    }
    else{
        return output;
    }
}

bool Joystick::getZ(){
    return zButton.isPressed(); 
}




void Joystick::joystickUpdate(){
    zButton.loop(); // update button stuff for debouncing and stuff, make sure to run every loop
}


void Joystick::setup(){
    pinMode(xPin, INPUT); // set all pins connected to joystick to receive inputs
    pinMode(yPin, INPUT);

    zButton.setDebounceTime(50); // setup debouncing on pushning the stick down
    zButton.loop();
}



// controller methods

Controller::Controller(): joy1(Joystick()), joy2(Joystick()), butA(ezButton(0)), butB(ezButton(0)), butX(ezButton(0)), butY(ezButton(0)){
    setup();
}

Controller::Controller(int j1x, int j1y, int j1z, int j2x, int j2y, int j2z, int butAPin, int butBPin, int butXPin, int butYPin):
joy1(Joystick(j1x, j1y, j1z)), joy2(Joystick(j2x, j2y, j2z)), butA(ezButton(butAPin)),
butB(ezButton(butBPin)), butX(ezButton(butXPin)), butY(ezButton(butYPin)){
    setup();
}

Controller::~Controller(){}

// joy 1

float Controller::getJoy1X(float deadzone ){
    return joy1.getX(deadzone);
}

float Controller::getJoy1Y(float deadzone ){
    return joy1.getY(deadzone);
}

bool Controller::getJoy1Z(){
    return joy1.getZ();
}

// joy 2

float Controller::getJoy2X(float deadzone ){
    return joy2.getX(deadzone);
}

float Controller::getJoy2Y(float deadzone ){
    return joy2.getY(deadzone);
}

bool Controller::getJoy2Z(){
    return joy2.getZ();
}

// buttons

bool Controller::getA(){
    return butA.isPressed();
}

bool Controller::getB(){
    return butB.isPressed();
}

bool Controller::getX(){
    return butX.isPressed();
}

bool Controller::getY(){
    return butY.isPressed();
}




void Controller::controllerUpdate(){
    butA.loop();
    butB.loop();
    butX.loop();
    butY.loop();

    joy1.joystickUpdate();
    joy2.joystickUpdate();
}




void Controller::setup(){
    butA.setDebounceTime(50);
    butB.setDebounceTime(50);
    butX.setDebounceTime(50);
    butY.setDebounceTime(50);

    butA.loop();
    butB.loop();
    butX.loop();
    butY.loop();
}


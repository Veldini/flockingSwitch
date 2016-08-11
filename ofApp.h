#pragma once

#ifndef _TEST_APP
#define _TEST_APP
#include "ofMain.h"
#include "boid.h"


#define BOIDS 150

class ofApp : public ofBaseApp {
private:
	boid *boids[BOIDS];
	ofArduino	arduino;

	void setupArduino(const int & version);
	void digitalPinChanged(const int & pinNum);
	void analogPinChanged(const int & pinNum);

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void mouseDragged(int x, int y, int button);


	int potMeter;
	int knop;

	ofColor color;
};
#endif

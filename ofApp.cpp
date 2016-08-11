#include "ofApp.h"
#define PIN_BUTTON 2
#define PIN_POTMETER 0
//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(25);
	ofBackground(255);
	
	ofEnableAlphaBlending();

	ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);
	// connect to the Arduino
	// use the same device name used in the Arduino IDE
	arduino.connect("COM3");
	arduino.sendFirmwareVersionRequest();

	color.set(ofRandom(255), ofRandom(255), ofRandom(255));
	for (int i = 0; i < BOIDS; i++) {
		boids[i] = new boid(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()), ofRandom(-10, 10), ofRandom(-10, 10), boids, BOIDS);
	}
	//ofSetFrameRate(25);



}

//--------------------------------------------------------------
void ofApp::update() {
	for (int i = 0; i < BOIDS; i++) {
		boids[i]->update();
	}
	if (potMeter < 300) {
		for (int i = 0; i < BOIDS; i++) {
			boids[i]->attract();
		}
	}

	arduino.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(255, 255, 255);
	for (int i = 0; i < BOIDS; i++) {
		boids[i]->draw();
	}
	ofDrawCircle(ofGetMouseX(), ofGetMouseY(), potMeter);
}

//--------------------------------------------------------------
void ofApp::setupArduino(const int& version) {
	// remove listener because we don't need it anymore
	ofRemoveListener(arduino.EInitialized, this, &ofApp::setupArduino);

	// print firmware name and version to the console
	ofLogNotice() << "Arduino firmware found: " << arduino.getFirmwareName()
		<< " v" << arduino.getMajorFirmwareVersion() << "." << arduino.getMinorFirmwareVersion();

	
	arduino.sendDigitalPinMode(PIN_BUTTON, ARD_INPUT);
	arduino.sendAnalogPinReporting(PIN_POTMETER, ARD_ANALOG);

	// set listeners for pin events
	ofAddListener(arduino.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
	ofAddListener(arduino.EAnalogPinChanged, this, &ofApp::analogPinChanged);

}

void ofApp::digitalPinChanged(const int& pinNum) {
	// get value with arduino.getDigital(pinNum)
	ofLogNotice() << "Digital Pin " << pinNum << " value: " << arduino.getDigital(pinNum) << endl;
	knop = arduino.getDigital(pinNum);
	if (knop == 1) {
		for (int i = 0; i < BOIDS; i++) {
			boids[i]->attract();
		}

	}

}

void ofApp::analogPinChanged(const int& pinNum) {
	// get value with arduino.getAnalog(pinNum));
	//	ofLogNotice() << "Analog Pin " << pinNum << " value: " << arduino.getAnalog(pinNum) << endl;
	potMeter = arduino.getAnalog(pinNum);
}


void ofApp::keyPressed(int key) {

}


void ofApp::mouseDragged(int x, int y, int button) {
	for (int i = 0; i < BOIDS; i++) {
		boids[i]->repel();

	}
}


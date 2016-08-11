#include "boid.h"
#include "ofMain.h"
float sq(float a) {
	return a * a;
}

boid::boid(float x, float y, float vx, float vy, boid* others[], int num_others) {
	this->r1 = 40;
	this->r2 = 80;
	this->r3 = 160;

	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	this->others = others;
	this->num_others = num_others;

}
void boid::setup() {
	
	

}

void boid::update() {
	sep();
	align();


	float l = sqrt(sq(vx) + sq(vy));
	if (l > 4) {
		vx = 0.9 * vx;
		vy = 0.9 * vy;
	}

	x += vx;
	y += vy;

	//houd boid binnen window
	if (x > ofGetWidth() - 30) { vx -= 2; }
	if (x < 30) { vx += 2; }
	if (y > ofGetHeight() - 30) { vy -= 2; }
	if (y < 30) { vy += 2; }

}


void boid::sep() { // zorgt dat de onderdelen van de klusters wat van elkaar blijven en niet overlappen en een blob worden
	int count = 0;
	float sx = 0;
	float sy = 0;

	for (int i = 0; i < num_others; i++) {

		float d = sqrt(sq(x - others[i]->x) + sq(y - others[i]->y));
		if (d < r1 && this != others[i]) {
			count++;
			sx += others[i]->x;
			sy += others[i]->y;
		}
	}

	if (count  > 0) {
		sx = x - sx / count;
		sy = y - sy / count;

		float l = sqrt(sq(sx) + sq(sy));
		sx = 1.2 * sx / l;
		sy = 1.2 * sy / l;
	}
	vx += sx;
	vy += sy;

}

void boid::align() { // functie die zorgt dat de boids gaan klusteren
	int count = 0;
	float dx = 0;
	float dy = 0;

	for (int i = 0; i < num_others; i++) {

		float d = sqrt(sq(x - others[i]->x) + sq(y - others[i]->y));
		if (d < r2 && this != others[i]) {
			count++;
			dx += others[i]->vx;
			dy += others[i]->vy;
		}
	}
	if (count  > 0) {
		dx = dx / count;
		dy = dy / count;
		float l = sqrt(sq(dx) + sq(dy));
		dx = dx / l;
		dy = dy / l;
	}
	vx += dx;
	vy += dy;

}

void boid::attract() { //maakt dat de zwerm naar de muis komt
	int count = 0;
	float sx = 0;
	float sy = 0;

	for (int i = 0; i < num_others; i++) {

		float d = sqrt(sq(x - others[i]->x) + sq(y - others[i]->y));
		if (d < r3  && d > r1 && this != others[i]) {
			count++;
			sx += ofGetMouseX();
			sy += ofGetMouseY();
		}
	}

	if (count  > 0) {
		sx = x - sx / count;
		sy = y - sy / count;

		float l = sqrt(sq(sx) + sq(sy));
		sx = sx / l;
		sy = sy / l;

	}

	vx -= sx;
	vy -= sy;



}
void boid::repel() { // zorgt dat de onderdelen wegkaatsen wanneer ze binnen een een radius van 40 bij de muis in de buurt zijn
	float distance = ofDist(ofGetMouseX(), ofGetMouseY(), x, y);
	if (distance < 40) {
		vx -= ofRandom(-20, 20);
		vy -= ofRandom(-20, 20);
		ofSetColor(ofRandom(0), ofRandom(0), ofRandom(150, 255));

	}
}


void boid::draw() {

	float r = 0;
	glPushMatrix();
	glTranslatef(x, y, 0);
	float alpha = atan(vy / vx) + (vx < 0 ? PI : 0); //waarde berekenen voor rotatie

	glRotatef(alpha * 180 / PI, 0, 0, 1); // zorgt voor het roteren

	ofFill();
	ofSetColor(0, 0, ofRandom(128, 255), 150);
	
	ofBeginShape();  // driehoekjes
	ofVertex(r-15, r-5);
	ofVertex(r-15, r+5);
	ofVertex(r+15, r-5);
	ofEndShape(true);

	glPopMatrix();

}

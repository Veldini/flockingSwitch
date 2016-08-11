#pragma once
#ifndef _BOID
#define _BOID

class boid {
private:
	float r1;
	float r2;
	float r3;

	float x, y;
	float vx, vy;
	boid** others;
	int num_others;
	
	

public:
	boid(float x, float y, float vx, float vy, boid* others[], int num_others);
	void update();
	void draw();
	void setup();

	

	void sep();
	void align();
	void attract();
	void repel();
	float r;

};


#endif
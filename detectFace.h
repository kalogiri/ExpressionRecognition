#pragma once

#include "ofMain.h"
#include "ofxFaceTracker.h"
#include "ofEvents.h"

class detectFace : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void expressionCheck();
	void keyPressed(int key);
	
	ofVideoGrabber cam;
	ofxFaceTracker tracker;
	ExpressionClassifier classifier;

	//Expression Feedback
	bool _smiling, _frowning, _neutral;
	bool _startProg;
	int expressionCount;//A counter for whatever expression is being shown.
	void expressionDisplay(); //This function displays the expression that  which exp...

	int imageOriginX, imageOriginY;

	//Prototype 1 Feedback [Smiley]
	//Variables
	ofImage smileExpr, frownExpr, neutralExpr;

	//Prototype 2 Feedback [Flower] 

	ofImage deadFlower, dyingFlower, fullyBloomedFlower, neutralFlower, bud;

	//Prototype 3 Feedback [Sound]
	
	//Variables
	ofSoundPlayer smile, frown;

	 
	/////////////////////////////////////////////////////////////////////////////////////
	//Arduino Stuff
	//Serial Communication
	ofSerial serial;
};

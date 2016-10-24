#include "detectFace.h"

using namespace ofxCv;
using namespace cv;

void detectFace::setup() {
	ofBackground(0);
	//Standard expression variables...
	_smiling = false;
	_frowning = false;
	_neutral = false;
	_startProg = false;
	expressionCount = 0;

	//Prototype 1 Images [Smiley]
	smileExpr.loadImage("images/Smile_use.jpg");
	frownExpr.loadImage("images/Sad_use.jpg");
	neutralExpr.loadImage("images/Neutral_use.jpg");

	//Prototype 2 Images [Flower]
	bud.loadImage("images/Bud.jpg");
	neutralFlower.loadImage("images/Neutral.jpg");
	fullyBloomedFlower.loadImage("images/Fully_Bloomed.jpg");
	dyingFlower.loadImage("images/Dying.jpg");
	deadFlower.loadImage("images/Dead.jpg");

	//Prototype 3 Sound [Correct/Incorrect]
	smile.loadSound("audio/correct.mp3");
	frown.loadSound("audio/wrong.mp3");

	//Serial Communication
	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();

	int baud = 9600;
	serial.setup(0,baud);

	//Face Tracker Stuff
	ofSetVerticalSync(true);
	cam.initGrabber(640, 480);
	
	tracker.setup();
	tracker.setRescale(.5);


}

void detectFace::update() {
	//Face Tracker...
	cam.update();
	if(cam.isFrameNew()) {
		if(tracker.update(toCv(cam))) {
			classifier.classify(tracker);
		}		
	}
}
void detectFace::draw() {
	
	ofSetColor(255);
	
	cam.draw(0, 0);

	//Face Tracker...

	//This draws the white outline of what the face tracker grabs
	//Disable this for actual tests
	tracker.draw();
	expressionDisplay();
	int w = 100, h = 12;
	ofPushStyle();
	ofPushMatrix();
	ofTranslate(5, 10);
	int n = classifier.size();
	int primary = classifier.getPrimaryExpression();
  for(int i = 0; i < n; i++){
	  
		ofSetColor(i == primary ? ofColor::red : ofColor::black);
		ofRect(0, 0, w * classifier.getProbability(i) + .5, h);
		ofSetColor(255);
		ofDrawBitmapString(classifier.getDescription(i), 5, 9);
		ofTranslate(0, h + 5);
		
 }
	ofPopMatrix();
	ofPopStyle();
	
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), ofGetWidth() - 20, ofGetHeight() - 10);
	drawHighlightString(
		string() +
		"r - reset\n" +
		"e - add expression\n" +
		"a - add sample\n" +
		"s - save expressions\n"
		"l - load expressions",
		14, ofGetHeight() - 7 * 12);

	expressionCheck();
	
}

void detectFace::keyPressed(int key) {
	if(key == 'r') {
		tracker.reset();
		classifier.reset();
	}
	if(key == 'e') {
		classifier.addExpression();
	}
	if(key == 'a') {
		classifier.addSample(tracker);
	}
	if(key == 's') {
		classifier.save("expressions");
	}
	if(key == 'l') {
		classifier.load("expressions");
	}

	if(key == ' ' ) {
		_startProg = true;
	}
}

void detectFace::expressionCheck() {
	switch (classifier.getPrimaryExpression()) {
		case 0:
			cout << "neutral" << endl;
			_smiling = false;
			_frowning = false;
			_neutral = true;
			break;

		case 1:
			cout << "smiling" << endl;
			_neutral = false;
			_frowning = false;
			_smiling = true;
			break;

		case 2:
			cout << "frowning" << endl;
			_neutral = false;
			_frowning = true;
			_smiling = false;
			break;
	}
}

void detectFace::expressionDisplay() {

	if(_smiling == false && _frowning == false && _neutral == false) {
		bud.draw(imageOriginX,imageOriginY,600,480);
	}

	if(_neutral == true) {
		expressionCount = 1;
	}

	if(_smiling == true) {
		expressionCount++;
	}

	if(_frowning == true) {
		expressionCount--;
	}

	
	if(expressionCount < -5 && expressionCounte < 5) {
		
		neutralFlower.draw(imageOriginX,imageOriginY,600,480);
	}

	if(expressionCount >=5) {
		fullyBloomedFlower.draw(imageOriginX,imageOriginY,600,480);
	}

	if(expressionCount <= -5 && expressionCount > -10 ) {
		dying.draw(imageOriginX,imageOriginY,600,480);
	}

	if(expressionCount <= -10 && expressionCount > -15 ) {
		dying.draw(imageOriginX,imageOriginY,600,480);
	}

	if(_smiling == false && _frowning == false) {
		expressionCount = 1;
	}

}
#include "polygonShape.h"

PolygonShape::PolygonShape(){
}


PolygonShape::~PolygonShape(){
}


void PolygonShape::setup(){

	_currentPos = ofVec3f(0.0, 0.0, 0.0);

	_moveDir = ofVec3f(
		ofRandom(-1.0, 1.0),
		ofRandom(-1.0, 1.0),
		ofRandom(-1.0, 1.0)
	).normalize();

	_distance = ofRandom(1, 10);
	_angle    = 0.0;

	_actionFrame  = static_cast<int>(ofRandom(5, 180));
	_frameCounter = 0;


}


void PolygonShape::update(){

	if(_frameCounter > _actionFrame){

		this->updateMoveDir();
		this->updateDistance();
		
		_actionFrame  = static_cast<int>(ofRandom(5, 180));
		_frameCounter = 0;

	
	}else{

		_frameCounter++;
	
	}

	this->updateCurrentPos();
	this->updateAngle();

	/*
	std::cout << "X : " << _currentPos.x << std::endl;
	std::cout << "Y : " << _currentPos.y << std::endl;
	std::cout << "Z : " << _currentPos.z << std::endl;
	*/

}



void PolygonShape::draw(){

	ofPushMatrix();
	{
		ofRotate(_angle, _currentPos.x, _currentPos.y, _currentPos.z);
		ofSetSphereResolution(8);
		ofDrawSphere(_currentPos, 20.0);
	}
	ofPopMatrix();
}


void PolygonShape::updateMoveDir(){

	_moveDir = ofVec3f(
		ofRandom(-1.0, 1.0),
		ofRandom(-1.0, 1.0),
		ofRandom(-1.0, 1.0)
	).normalize();
	
}

void PolygonShape::updateDistance(){

	_distance = ofRandom(1, 10);

}

void PolygonShape::updateCurrentPos(){

	_currentPos += _moveDir.getScaled(_distance);
	
}

void PolygonShape::updateAngle(){

	if(_angle >= 360.0){
		_angle -= 360.0;
	}

	_angle += 2.0;

}


ofVec3f PolygonShape::getCurrentPos(){

	return _currentPos;

}
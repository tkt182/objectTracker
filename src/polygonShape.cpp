#include "polygonShape.h"

PolygonShape::PolygonShape(){
}


PolygonShape::~PolygonShape(){
}


void PolygonShape::setup(){

	_currentPos = ofVec3f(0.0, 0.0, 0.0);
	_pathLines.addVertex(_currentPos);

	_moveDir = ofVec3f(
		ofRandom(-1.0, 1.0),
		ofRandom(-1.0, 1.0),
		ofRandom(-1.0, 1.0)
	).normalize();

	_distance     = ofRandom(1.0, 5.0);
	_velocitySize = ofRandom(1.0, 5.0);
	_frictionSize = 10.0;
	_angle        = 0.0;

	_moveStep     = 25;
	_stepCounter  = 0;
	_actionFrame  = 0;
	_frameCounter = 0;


	_ambient  = ofFloatColor(0.1, 0.4, 0.1, 1.0);
	_diffuse  = ofFloatColor(0.2, 0.7, 0.2, 1.0);
	_specular = ofFloatColor(1.0, 1.0, 1.0, 1.0);
	_shininess  = 100.0;

	_material.setAmbientColor(_ambient);
	_material.setDiffuseColor(_diffuse);
	_material.setSpecularColor(_specular);
	_material.setShininess(_shininess);



}


void PolygonShape::update(){

	if(_frameCounter > _actionFrame){

		this->updateMoveDir();
		this->updateDistination();
		this->updateFriction();
		this->updateVelocity();

		_actionFrame  = static_cast<int>(ofRandom(10, 50));
		_frameCounter = 0;

	
	}else{

		_frameCounter++;
	
	}

	this->updateCurrentPos();
	this->updateAngle();

	_pathLines.addVertex(_currentPos);
	_vbo.setMesh(_pathLines, GL_DYNAMIC_DRAW);



}



void PolygonShape::draw(){

	ofPushMatrix();
	{
		ofRotate(_angle, _currentPos.x, _currentPos.y, _currentPos.z);
		
		_material.begin();

		ofSetSphereResolution(4);
		ofDrawSphere(_currentPos, 5.0);

		_material.end();
	
	}
	ofPopMatrix();

	ofSetLineWidth(1.0);
	_vbo.draw(GL_LINE_STRIP, 0, _pathLines.getNumVertices());


}



void PolygonShape::updateMoveDir(){

	_moveDir = ofVec3f(
		ofRandom(-1.0, 1.0),
		ofRandom(-1.0, 1.0),
		ofRandom(-1.0, 1.0)
	).normalize();
	
}

void PolygonShape::updateDistination(){

	_distance    = ofRandom(20.0, 50.0);
	_distination = _moveDir.getScaled(_distance);
	

}


void PolygonShape::updateVelocity(){

	_velocity = (_distination - _currentPos) / _moveStep;

}

void PolygonShape::updateFriction(){

	_friction     = _moveDir.getScaled(_frictionSize);

}


void PolygonShape::updateCurrentPos(){


	float distance = _velocity.length() - _friction.length();
	//std::cout << "DISTANCE : " << distance << std::endl;

	if(_stepCounter > _moveStep){

		_stepCounter = 0;
	
	}else{
	
		_stepCounter++;
	}

	ofVec3f diff     = _distination - _currentPos;
	float   diffSize = diff.length();



	if(diffSize >= 10.0){
		_currentPos += _velocity;
	}
	
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

ofVec3f PolygonShape::getDistination(){

	return _distination;

}

float PolygonShape::getStepCounter(){

	return _stepCounter;
}

float PolygonShape::getMoveStep(){

	return _moveStep;

}
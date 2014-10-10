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

	_distance = ofRandom(1, 10);
	_angle    = 0.0;

	_actionFrame  = static_cast<int>(ofRandom(5, 180));
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
		this->updateDistance();
		
		_actionFrame  = static_cast<int>(ofRandom(5, 180));
		_frameCounter = 0;

	
	}else{

		_frameCounter++;
	
	}

	this->updateCurrentPos();
	this->updateAngle();

	_pathLines.addVertex(_currentPos);
	_vbo.setMesh(_pathLines, GL_DYNAMIC_DRAW);

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
		
		_material.begin();

		ofSetSphereResolution(4);
		ofDrawSphere(_currentPos, 20.0);

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
#include "polygonShapeSound.h"

PolygonShapeSound::PolygonShapeSound(){
}

PolygonShapeSound::~PolygonShapeSound(){
}

void PolygonShapeSound::setup(){


	_prevTime = ofGetElapsedTimef();

	_currentPos = ofVec3f(0.0, 0.0, 0.0);
	_pathLines.addVertex(_currentPos);


	_moveDir = ofVec3f(
		ofRandom(-1.0, 1.0),
		ofRandom(-1.0, 1.0),
		ofRandom(-1.0, 1.0)
	).normalize();


	_powerLevel = 0.001;
	_power      = 0.0;
	
	_frictionSize = 0.0;
	_angle        = 0.0;


	this->setMoveDir();
	this->setFriction();
	this->setVelocity();


	// ライティングの設定
	_ambient  = ofFloatColor(0.1, 0.4, 0.1, 1.0);
	_diffuse  = ofFloatColor(0.2, 0.7, 0.2, 1.0);
	_specular = ofFloatColor(1.0, 1.0, 1.0, 1.0);
	_shininess  = 100.0;

	_material.setAmbientColor(_ambient);
	_material.setDiffuseColor(_diffuse);
	_material.setSpecularColor(_specular);
	_material.setShininess(_shininess);


}


void PolygonShapeSound::update(){

	this->updateTimeStep();

	if(_power > _powerLevel){
		
		this->setMoveDir();
		this->setFrictionSize();
		this->setFriction();
		this->setVelocity();

	}
	
	this->updateCurrentPos();
	this->updateAngle();

	_pathLines.addVertex(_currentPos);
	_vbo.setMesh(_pathLines, GL_DYNAMIC_DRAW);


}

void PolygonShapeSound::setPower(const float power){
	_power = power;
}


void PolygonShapeSound::setVelocity(){

	_velocitySize = _power * 10.0;
	_velocity     = _moveDir.getScaled(_velocitySize);

	//std::cout << _velocitySize << std::endl;
}


void PolygonShapeSound::setFrictionSize(){

	_frictionSize = _power * 0.005;

}
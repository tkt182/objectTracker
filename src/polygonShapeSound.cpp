#include "polygonShapeSound.h"

PolygonShapeSound::PolygonShapeSound(const int type) : PolygonShape(type){
}

PolygonShapeSound::~PolygonShapeSound(){
}

void PolygonShapeSound::setup(){


	_prevTime = ofGetElapsedTimef();
	_vboIndex = 0;

	// _pathLines‚Ì‰Šú‰»
	ofMesh mesh;
	_pathLines.push_back(mesh);
	_pathLines[_vboIndex].addVertex(_currentPos);

	// _vbos‚Ì‰Šú‰»
	ofVbo vbo;
	_vbos.push_back(vbo);


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

	// ––”ö‚Ì—v‘f‚É’¸“_î•ñ‚ğ’Ç‰Á‚·‚é
	_pathLines[_vboIndex].addVertex(_currentPos);
	
	_vbos[_vboIndex].setMesh(_pathLines[_vboIndex], GL_DYNAMIC_DRAW);

}

void PolygonShapeSound::setPower(const float power){
	_power = power;
}


void PolygonShapeSound::setVelocity(){

	_velocitySize = _power * 5.0;
	_velocity     = _moveDir.getScaled(_velocitySize);

}


void PolygonShapeSound::setFrictionSize(){

	_frictionSize = _power * 0.005;

}
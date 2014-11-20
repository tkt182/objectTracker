#include "polygonShapeSound.h"

PolygonShapeSound::PolygonShapeSound(const int type) : PolygonShape(type){
}

PolygonShapeSound::~PolygonShapeSound(){
}

void PolygonShapeSound::setup(){


	_prevTime = ofGetElapsedTimef();
	_vboIndex = 0;

	_currentPos = _initalPos;


	// _pathLines�̏�����
	ofMesh mesh;
	_pathLines.push_back(mesh);
	_pathLines[_vboIndex].addVertex(_currentPos);

	// _vbos�̏�����
	ofVbo vbo;
	_vbos.push_back(vbo);


	_moveDir = ofVec3f(
		ofRandom(-1.0, 1.0),
		ofRandom(-1.0, 1.0),
		ofRandom(-1.0, 1.0)
	).normalize();


	_enableAutoMove     = false;


	_magnitudeThresHold = 0.1;    // �I�u�W�F�N�g�𓮂���臒l��ݒ�(�}�W�b�N�i���o�[!)
	_magnitude          = 0.0;
	
	_frictionSize       = 5.0;
	_angle              = 0.0;

	_actionFrame  = 0;
	_frameCount   = 0;


	this->setMoveDir();
	this->setFriction();
	this->setVelocity();


	_material.setAmbientColor(_ambient);
	_material.setDiffuseColor(_diffuse);
	_material.setSpecularColor(_specular);
	_material.setShininess(_shininess);


}


void PolygonShapeSound::update(){


	if(_enableAutoMove){

		// soundstream�̓��͂𗘗p���Ȃ��ꍇ�́A�e�N���X�̃��\�b�h�����̂܂܎g�p
		PolygonShape::update();

	}else{

		this->updateTimeStep();

		if(_magnitude > _magnitudeThresHold){

			this->setMoveDir();
			this->setVelocity();
			this->setFriction();

		}
	

		this->updateCurrentPos();
		this->updateAngle();

		// �����̗v�f�ɒ��_����ǉ�����
		_pathLines[_vboIndex].addVertex(_currentPos);
	
		_vbos[_vboIndex].setMesh(_pathLines[_vboIndex], GL_DYNAMIC_DRAW);
	
	}

}



void PolygonShapeSound::setMagnitude(const float magnitude){
	_magnitude = magnitude;

}

void PolygonShapeSound::changeMoveMode(){
	_enableAutoMove = !_enableAutoMove;
}


void PolygonShapeSound::setVelocity(){

	// �N�����v�͈̔͂́A�������Ă݂Ē��x�悩�����͈�(�}�W�b�N�i���o�[!)
	_velocitySize = this->clampf(_magnitude, 2.0, 3.0);
	_velocity     = _moveDir.getScaled(_velocitySize);

}


float PolygonShapeSound::clampf(float value, float min, float max){

    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;

}
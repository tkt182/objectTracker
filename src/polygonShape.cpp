#include "polygonShape.h"

/**
 * �I�u�W�F�N�g�̐���������
 */
PolygonShape::PolygonShape(const int type){

	_objectType = type;

	switch(_objectType){

	case 0:

		srand(static_cast<unsigned int>(time(NULL)));
		
		_initalPos = ofVec3f(0.0, 0.0, 0.0);
	
		_ambient  = ofFloatColor(0.3, 0.3, 0.3, 0.9);
		_diffuse  = ofFloatColor(0.1, 0.8, 0.3, 0.9);
		_specular = ofFloatColor(0.8, 0.8, 0.8, 0.9);
		_shininess  = 100.0;
	
		break;
	
	case 1:

		srand(static_cast<unsigned int>(time(NULL) + time(NULL)));

		_initalPos = ofVec3f(0.0, 0.0, 50.0);
	
		_ambient  = ofFloatColor(0.3, 0.3, 0.3, 0.9);
		_diffuse  = ofFloatColor(0.3, 0.6, 0.9, 0.9);
		_specular = ofFloatColor(0.8, 0.8, 0.8, 0.9);
		_shininess  = 100.0;
	
		break;

	case 2:

		srand(static_cast<unsigned int>(time(NULL) + time(NULL) + time(NULL)));
		
		_initalPos = ofVec3f(0.0, 0.0, -50.0);

		_ambient  = ofFloatColor(0.3, 0.3, 0.3, 0.9);
		_diffuse  = ofFloatColor(0.4, 0.9, 0.6, 0.9);
		_specular = ofFloatColor(0.8, 0.8, 0.8, 0.9);
		_shininess  = 100.0;

		break;

	}


}


PolygonShape::~PolygonShape(){
}


void PolygonShape::setup(){


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


	// �o�ߎ��Ԃ��|���Ďg���̂ŁA�傫�߂̒l��ݒ肷��
	// �� 1�t���[���̕`��ɂ�����o�ߎ���(�b)�͏��������߁B
	_frictionSize = 5.0;
	_velocitySize = ofRandom(1.0, 2.0);

	_angle        = 0.0;

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


void PolygonShape::update(){

	this->updateTimeStep();

	if(_frameCount > _actionFrame){

		this->setMoveDir();
		this->setVelocity();
		this->setFriction();


		_actionFrame  = static_cast<int>(ofRandom(10, 40));
		_frameCount = 0;
	
	}else{

		_frameCount++;
	
	}


	this->updateCurrentPos();
	this->updateAngle();


	// �����̗v�f�ɒ��_����ǉ�����
	_pathLines[_vboIndex].addVertex(_currentPos);
	
	_vbos[_vboIndex].setMesh(_pathLines[_vboIndex], GL_DYNAMIC_DRAW);



}


void PolygonShape::draw(){

	ofPushMatrix();
	{
		ofRotate(_angle, _currentPos.x, _currentPos.y, _currentPos.z);

		_material.begin();

		ofSetIcoSphereResolution(1);
		ofDrawIcoSphere(_currentPos, 5.0);

		_material.end();
	
	}
	ofPopMatrix();


	ofSetLineWidth(1.0);

	for(int i = 0; i < _pathLines.size(); i++){
		_vbos[i].draw(GL_LINE_STRIP, 0, _pathLines[i].getNumVertices());
	}



}


void PolygonShape::updateTimeStep(){

	_currentTime = ofGetElapsedTimef();
	_timeDiff    = _currentTime - _prevTime;
	_prevTime    = _currentTime;

}


void PolygonShape::setMoveDir(){


	// �ǂ̎��̕����ɓ�����������
	// 0 : X������(+)
	// 1 : X������(-)
	// 2 : Y������(+)
	// 3 : Y������(-)
	// 4 : Z������(+)
	// 5 : Z������(-)
	// ofRandom��float���̒l���A���Ă��邽�߁Arand�֐����g�p����



	int dir = rand() % 6;


	switch(dir){
	
		case 0:
			_moveDir =
				ofVec3f(ofRandom(5.0, 10.0), ofRandom(-0.5, 0.5), ofRandom(-0.5, 0.5)).normalize();
			break;

		case 1:
			_moveDir =
				ofVec3f(ofRandom(-5.0, -10.0), ofRandom(-0.5, 0.5), ofRandom(-0.5, 0.5)).normalize();
			break;

		case 2:
			_moveDir =
				ofVec3f(ofRandom(-0.5, 0.5), ofRandom(5.0, 10.0), ofRandom(-0.5, 0.5)).normalize();
			break;

		case 3:
			_moveDir =
				ofVec3f(ofRandom(-0.5, 0.5), ofRandom(-5.0, -10.0), ofRandom(-0.5, 0.5)).normalize();
			break;

		case 4:
			_moveDir =
				ofVec3f(ofRandom(-0.5, 0.5), ofRandom(-0.5, 0.5), ofRandom(5.0, 10.0)).normalize();
			break;

		case 5:
			_moveDir =
				ofVec3f(ofRandom(-0.5, 0.5), ofRandom(-0.5, 0.5), ofRandom(-5.0, -10.0)).normalize();
			break;


		default:

			_moveDir =
				ofVec3f(ofRandom(-1.0, 1.0), ofRandom(-1.0, 1.0), ofRandom(-1.0, 1.0)).normalize();
			break;
		
	}

	
}


void PolygonShape::setVelocity(){

	_velocitySize = ofRandom(1.0, 2.0);
	_velocity     = _moveDir.getScaled(_velocitySize);

}

void PolygonShape::setFriction(){

	_friction    = -_moveDir.getScaled(_frictionSize);

}


void PolygonShape::updateCurrentPos(){

	_velocity += _friction * _timeDiff;

	// ���x�x�N�g���̑傫����1.0�ȏ�̏ꍇ�́A
	// �܂��I�u�W�F�N�g�������Ă���Ƃ���
	if(_velocity.length() > 1.0){
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

void PolygonShape::resetCurrentPos(){


	// �I�u�W�F�N�g�������ʒu�ɖ߂�
	_currentPos = ofVec3f(0.0, 0.0, 0.0);

	// �V����mesh�Avbo��ǉ�����
	ofMesh mesh;
	_vboIndex++;
	_pathLines.push_back(mesh);
	_pathLines[_vboIndex].addVertex(_currentPos);

	ofVbo vbo;
	_vbos.push_back(vbo);

}
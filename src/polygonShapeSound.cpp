#include "polygonShapeSound.h"

PolygonShapeSound::PolygonShapeSound(){
}

PolygonShapeSound::~PolygonShapeSound(){
}

void PolygonShapeSound::setup(){


	_prevTime = ofGetElapsedTimef();
	_vboIndex = 0;

	// _pathLinesの初期化
	ofMesh mesh;
	_pathLines.push_back(mesh);
	_pathLines[_vboIndex].addVertex(_currentPos);

	// _vbosの初期化
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

	// 末尾の要素に頂点情報を追加する
	_pathLines[_vboIndex].addVertex(_currentPos);
	
	_vbos[_vboIndex].setMesh(_pathLines[_vboIndex], GL_DYNAMIC_DRAW);

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
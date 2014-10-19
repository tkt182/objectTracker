#include "polygonShape.h"

PolygonShape::PolygonShape(){
}


PolygonShape::~PolygonShape(){
}


void PolygonShape::setup(){


	_prevTime = ofGetElapsedTimef();

	_currentPos = ofVec3f(0.0, 0.0, 0.0);
	_pathLines.addVertex(_currentPos);


	_moveDir = ofVec3f(
		ofRandom(-1.0, 1.0),
		ofRandom(-1.0, 1.0),
		ofRandom(-1.0, 1.0)
	).normalize();

	_velocitySize = ofRandom(1.0, 5.0);

	// 経過時間を掛けて使うので、大きめの値を設定する
	// ※ 1フレームの描画にかかる経過時間(秒)は小さいため。
	_frictionSize = 25;
	_angle        = 0.0;

	_actionFrame  = 0;
	_frameCount = 0;


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


void PolygonShape::update(){


	this->updateTimeStep();

	if(_frameCount > _actionFrame){

		this->setMoveDir();
		this->setFriction();
		this->setVelocity();

		_actionFrame  = static_cast<int>(ofRandom(10, 30));
		_frameCount = 0;

	
	}else{

		_frameCount++;
	
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

		ofSetSphereResolution(3);
		ofDrawSphere(_currentPos, 5.0);

		_material.end();
	
	}
	ofPopMatrix();

	ofSetLineWidth(1.0);
	_vbo.draw(GL_LINE_STRIP, 0, _pathLines.getNumVertices());


}


void PolygonShape::updateTimeStep(){

	_currentTime = ofGetElapsedTimef();
	_timeDiff    = _currentTime - _prevTime;
	_prevTime    = _currentTime;

}


void PolygonShape::setMoveDir(){

	_moveDir = ofVec3f(
		ofRandom(-1.0, 1.0),
		ofRandom(-1.0, 1.0),
		ofRandom(-1.0, 1.0)
	).normalize();
	
}


void PolygonShape::setVelocity(){

	_velocitySize = ofRandom(5.0, 10.0);
	_velocity     = _moveDir.getScaled(_velocitySize);

}

void PolygonShape::setFriction(){

	_friction    = -_moveDir.getScaled(_frictionSize);

}


void PolygonShape::updateCurrentPos(){

	_velocity += _friction * _timeDiff;


	// 速度ベクトルの大きさが5.0以上の場合は、
	// まだオブジェクトが動いているとする
	if(_velocity.length() > 5.0){
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
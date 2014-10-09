#include "stars.h"


Stars::Stars(int num, float radius){

	_num    = num;
	_pos    = new ofVec3f[_num];
	_radius = radius;

	_limit  = 5000.0;
	

}

Stars::~Stars(){
	
	delete[] _pos;

}

void Stars::setup(){

	for(int i = 0; i < _num; i++){
	
		_pos[i].set(
			ofRandom(-_limit, _limit), 
			ofRandom(-_limit, _limit), 
			ofRandom(-_limit, _limit)
		);
	
	}

}

void Stars::draw(){

	for(int i = 0; i < _num; i++){
	
		ofSetSphereResolution(4);
		ofDrawSphere(_pos[i], _radius);
	
	}

}
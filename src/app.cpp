#include "app.h"


/**
* �R���X�g���N�^
*/
App::App(){


}

/**
* �f�X�g���N�^
*/
App::~App(){
}


//--------------------------------------------------------------
void App::setup(){

	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofEnableDepthTest();
	ofSetSmoothLighting(false);
	//ofSetFullscreen(true);
	//ofHideCursor();

	ofBackground(0, 0, 0);

	_light.setDirectional();
	_light.setAmbientColor(ofFloatColor(0.1, 0.4, 0.1, 1.0));
	_light.setDiffuseColor(ofFloatColor(0.2, 0.7, 0.2, 1.0));
	_light.setSpecularColor(ofFloatColor(0.2, 0.8, 0.2, 1.0));


	_dampen = 0.4;

	_polygonShape = new PolygonShape();
	_polygonShape->setup();

	_stars = new Stars(2000);
	_stars->setup();


}

//--------------------------------------------------------------
void App::update(){

	_polygonShape->update();


}

//--------------------------------------------------------------
void App::draw(){



	ofVec3f targetPos = _polygonShape->getCurrentPos();
	ofVec3f lightPos  = targetPos + 10.0;

	_ccam.begin();

	/////// �J�����֘A�̐ݒ� ///////

	// �J�����̊�{�ʒu�ƒ����_������
	_ccam.setCamPos(targetPos);
	_ccam.setTargetPos(targetPos);
	

	// �}�E�X����ɂ���]�̍��W�ϊ����J�����ɉ�����
	_ccam.execRotate();

	// ���W�ϊ����ꂽ�J�����̈ʒu���A�I�u�W�F�N�g������̋�����ۂĂ�ʒu�ɕύX����
	_ccam.keepADistance();


	// �X�V���ꂽ���_���W�n�̍��W�����v�Z����
	_ccam.calcCamAxis();


	// �ŏI�I�ȃJ�����̈ʒu�ƒ����_�̍��W��K�p����
	_ccam.setPosition();
	_ccam.lookAt();



	/////// �\������I�u�W�F�N�g�̐ݒ�E�`�� ///////
	
	// �}�E�X����ɂ���]�̍��W�ϊ���K�p
	float angle;
	ofVec3f axis;
	_ccam.getRotation(angle, axis);

	ofRotate(angle, axis.x, axis.y, axis.z);
	
	
	ofPushMatrix();
	{

		_stars->draw();

		_light.enable();
		_light.setPosition(lightPos);
		//_light.setSpotlight();


		_polygonShape->draw();

		//_light.end();
		_light.disable();

	}
	ofPopMatrix();

	_ccam.end();

}

void App::exit(){

	delete _polygonShape;
	delete _stars;
	
}



//--------------------------------------------------------------
void App::keyPressed(int key){

	if(key == 'a'){
		_ccam.updateDistance(50.0);
	}

	if(key == 's'){
		_ccam.updateDistance(-50.0);
	}	


}

//--------------------------------------------------------------
void App::keyReleased(int key){
}

//--------------------------------------------------------------
void App::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void App::mouseDragged(int x, int y, int button){

	
    ofVec2f mouse(x,y);  

	ofVec3f xAxis = _ccam.getCamXAxis();
	ofVec3f yAxis = _ccam.getCamYAxis();

	ofQuaternion yRot((x-_lastMouse.x)*_dampen, yAxis);  
    ofQuaternion xRot((y-_lastMouse.y)*_dampen, xAxis);


	_ccam.setRotation(yRot*xRot);
	_lastMouse = mouse;


}

//--------------------------------------------------------------
void App::mousePressed(int x, int y, int button){

	//store the last mouse point when it's first pressed to prevent popping
	_lastMouse = ofVec2f(x,y);

}

//--------------------------------------------------------------
void App::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void App::windowResized(int w, int h){

}

//--------------------------------------------------------------
void App::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void App::dragEvent(ofDragInfo dragInfo){ 

}
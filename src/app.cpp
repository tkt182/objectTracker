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

	delete _polygonShape;
	delete _stars;


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

#ifdef SOUND_DEVICE_ENABLE

	_soundStream.listDevices();
	//_soundStream.setDeviceID(1);
	_soundStream.setup(this, 0, 2, 44100, BUFFER_SIZE, 4);

	_left     = new float[BUFFER_SIZE];
	_maxPower = 0.0;


	// ���C���I�u�W�F�N�g�̐ݒ�
	_polygonShape = new PolygonShapeSound();
	_polygonShape->setup();

#else

	// ���C���I�u�W�F�N�g�̐ݒ�
	_polygonShape = new PolygonShape();
	_polygonShape->setup();

#endif

	// �J�����֘A�̐ݒ�
	_moveStep       = 15;  // �ݒ�ɂ���ẮA�ڕW�ʒu�܂œ��B���Ȃ��ꍇ������
	_waitFrameNum   = 10;
	_frameCounter   = 0;

	_camPos         = _polygonShape->getCurrentPos();
	_camDistination = _polygonShape->getCurrentPos();
	_camVelocity    = (_camDistination - _camPos) / _moveStep; 


	// �w�i�I�u�W�F�N�g�̐ݒ�
	_stars = new Stars(2000);
	_stars->setup();


}

//--------------------------------------------------------------
void App::update(){

#ifdef SOUND_DEVICE_ENABLE
	_polygonShape->setPower(_maxPower);
#endif

	_polygonShape->update();


	// �w�肳�ꂽ�t���[�������ƂɃJ�����̈ړ��x�N�g����ύX����
	if(_frameCounter == _waitFrameNum){

		_camDistination = _polygonShape->getCurrentPos();
		_camVelocity = (_camDistination - _camPos) * 0.1;

		_frameCounter = 0;
	
	}


}

//--------------------------------------------------------------
void App::draw(){


	_camPos += _camVelocity;


	ofVec3f lightPos  = _camPos + 10.0;

	_ccam.begin();


	/////// �J�����֘A�̐ݒ� ///////

	// �J�����̊�{�ʒu�ƒ����_������.
	// ������x�I�u�W�F�N�g�𒆐S���炸�炷���߁A
	// �����_�̓I�u�W�F�N�g�̈ʒu�ł͂Ȃ��A�J�����̈ʒu�ƂȂ�.
	// �� �ŏI�I�ɂ́A�J�����ʒu�𒍎��X����y�������ɕ��s�ړ�������
	_ccam.setCamPos(_camPos);
	_ccam.setTargetPos(_camPos);
	

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


	_frameCounter++;

}


void App::exit(){

#ifdef SOUND_DEVICE_ENABLE
	_soundStream.close();
	delete[] _left;
#endif

}

#ifdef SOUND_DEVICE_ENABLE

void App::audioIn(float* input, int bufferSize, int nChannels){

	// ���[�U���w�肵���o�b�t�@�ƁA���ۂɃh���C�o���m�ۂ���o�b�t�@�̃T�C�Y��
	// ��r���A�����������̗p����.�����傫���l���g���ƁASoundStream�����ۂɃG���[����������
	int minBufferSize = min(BUFFER_SIZE, bufferSize);

	_maxPower = 0.0;

	for(int i = 0; i < minBufferSize; i++){
		
		_left[i] = input[i * 2];
		if(_left[i] > _maxPower) _maxPower = _left[i];

	}

}
#endif



//--------------------------------------------------------------
void App::keyPressed(int key){

	// ���L�[
	if(key == 357){
		_ccam.updateDistance(-20.0);
	}	

	// ���L�[
	if(key == 359){
		_ccam.updateDistance(20.0);
	}

	if(key == 'r'){
		_polygonShape->resetCurrentPos();
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
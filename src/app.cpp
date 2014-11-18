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

	delete[] _polygonShapes;
	delete _stars;

#ifdef SOUND_DEVICE_ENABLE
	delete[] _left;
#endif

}


//--------------------------------------------------------------
void App::setup(){

	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	

	
	// �����I�u�W�F�N�g�ɂ��邽�߁ADepthTest�͗L���ɂ��Ȃ�
	//ofEnableDepthTest();
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);


	ofSetSmoothLighting(false);

	//ofSetFullscreen(true);
	//ofHideCursor();

	ofBackground(0, 0, 0);

	_light.setPointLight();
	_light.setAmbientColor(ofFloatColor(0.2, 0.2, 0.2, 1.0));
	_light.setDiffuseColor(ofFloatColor(1.0, 1.0, 1.0, 1.0));
	_light.setSpecularColor(ofFloatColor(0.4, 0.4, 0.4, 1.0));


	_objectNum    = 3;
	_activeObject = 0;


#ifdef SOUND_DEVICE_ENABLE

	_soundStream.listDevices();
	_soundStream.setDeviceID(1);
	_soundStream.setup(this, 0, 2, 44100, BUFFER_SIZE, 4);

	_left     = new float[BUFFER_SIZE];
	_maxPower = 0.0;


	// ���C���I�u�W�F�N�g�̐ݒ�
	_polygonShapes = new PolygonShapeSound[_objectNum];
	for(int i = 0; i < _objectNum; i++){
		new(_polygonShapes + i) PolygonShapeSound(i);
		_polygonShapes[i].setup();
	}

#else

	// ���C���I�u�W�F�N�g�̐ݒ�
	_polygonShapes = new PolygonShape[_objectNum];
	for(int i = 0; i < _objectNum; i++){
		new(_polygonShapes + i) PolygonShape(i);
		_polygonShapes[i].setup();
		
		_lights.push_back(ofLight());
	
	}



#endif

	// �J�����֘A�̐ݒ�
	_waitFrameNum   = 3;
	_frameCounter   = 0;
	_camMoveEnable  = true;


	// �f�t�H���g��0�Ԗڂ̃I�u�W�F�N�g
	_targetPos      = _polygonShapes[_activeObject].getCurrentPos();
	_camBasePos     = _targetPos;
	_camDistination = _targetPos;
	_camVelocity    = _camBasePos;
	_camStayPos     = _camBasePos;



	// �w�i�I�u�W�F�N�g�̐ݒ�
	_stars = new Stars(2000);
	_stars->setup();


	// �}�E�X�h���b�O���̈ړ����������p�����[�^
	_dampen = 0.4;

}

//--------------------------------------------------------------
void App::update(){

#ifdef SOUND_DEVICE_ENABLE

	for(int i = 0; i < _objectNum; i++){
		_polygonShapes[i].setPower(_maxPower);
	}

#endif

	for(int i = 0; i < _objectNum; i++){
		_polygonShapes[i].update();
	}

	_targetPos = _polygonShapes[_activeObject].getCurrentPos();


	// �w�肳�ꂽ�t���[�������ƂɃJ�����̈ړ��x�N�g����ύX����
	if(_frameCounter == _waitFrameNum){

		_camDistination = _targetPos;
		_camVelocity    = (_camDistination - _camBasePos) * 0.1;

		_frameCounter = 0;
	
	}





}

//--------------------------------------------------------------
void App::draw(){



	_camBasePos += _camVelocity;

	_ccam.begin();


	/////// �J�����֘A�̐ݒ� ///////

	if(_camMoveEnable){

		/////// �J�������I�u�W�F�N�g�ɉ����ē������ꍇ ///////

		// �J�����̊�{�ʒu�ƒ����_������B
		// ������x�I�u�W�F�N�g�𒆐S���炸�炷���߁A
		// �����_�̓I�u�W�F�N�g���̂��̂̈ʒu�ł͂Ȃ��A�J�����̊�{�ʒu�ƂȂ�B
		// �� �ŏI�I�ɂ́A�J�����ʒu�𒍎��X����y�������ɕ��s�ړ�������B
		_ccam.setCamBasePos(_camBasePos);
		_ccam.setTargetPos(_camBasePos);

	}else{

		/////// �J�����̈ʒu���Œ肵�A�I�u�W�F�N�g�̕����݂̂������ꍇ ///////

		// �J�����̊�{�ʒu���Œ肵�A�����_������B
		// �����_�̓J�����𓮂����ꍇ�Ɠ��l�ɁA�J�����̊�{�ʒu�Ƃ���B
		// �� �J�����̊�{�ʒu��_camVelocity��������`�ŏ��X�Ɉړ����邽�߁A
		//    �J�����̓��������炩�ɂȂ�
		_ccam.setCamBasePos(_camStayPos);
		_ccam.setTargetPos(_camBasePos);

	}

	// �}�E�X����ɂ���]�̍��W�ϊ����J�����ɉ�����
	_ccam.execRotate();
		
	// ���W�ϊ����ꂽ�J�����̈ʒu���A�I�u�W�F�N�g������̋�����ۂĂ�ʒu�ɕύX����
	_ccam.keepADistance();


	// �X�V���ꂽ���_���W�n�̍��W�����v�Z����
	_ccam.calcCamAxis();


	// �ŏI�I�ȃJ�����̈ʒu�ƒ����_�̍��W��K�p����
	_ccam.setPosition();
	_ccam.lookAt();

	// ���C�g�̈ʒu���J�����̈ʒu�Ɠ����ɂ���
	ofVec3f lightPos = _ccam.getPosition();
	_light.setPosition(lightPos);


	// ���C�g��L���ɂ������_�ŁA�ʒu���X�V�����
	// �� ��]�s���������O�ɗL���ɂ���K�v������
	_light.enable();


	/////// �\������I�u�W�F�N�g�̐ݒ�E�`�� ///////
	
	// �}�E�X����ɂ���]�̍��W�ϊ���K�p
	float angle;
	ofVec3f axis;
	_ccam.getRotation(angle, axis);


	ofRotate(angle, axis.x, axis.y, axis.z);
	


	
	ofPushMatrix();
	{

		_stars->draw();

		// Light��ON�ɂ����GL_COLOR_MATERIAL���L���ɂȂ�悤��.
		// 0.8.0�̃o�O??
		glDisable(GL_COLOR_MATERIAL);

		for(int i = 0; i < _objectNum; i++){
			_polygonShapes[i].draw();
		}


	}
	ofPopMatrix();

	_light.disable();
	_ccam.end();


	_frameCounter++;


}


void App::exit(){

#ifdef SOUND_DEVICE_ENABLE
	_soundStream.close();
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
	// �J�����ƃI�u�W�F�N�g�̋������߂Â���(-�̏ꍇ�͉�������)
	if(key == 357){
		_ccam.updateDistance(-20.0);
	}	

	// ���L�[
	// �J�����ƃI�u�W�F�N�g�̋�������������(-�̏ꍇ�͋߂Â���)
	if(key == 359){
		_ccam.updateDistance(20.0);
	}

	// �I�u�W�F�N�g�̈ʒu���f�t�H���g�ɖ߂�
	if(key == 'r'){
		_polygonShapes[_activeObject].resetCurrentPos();
	}

	// �J�������I�u�W�F�N�g�ɉ����ē��������ǂ��������߂�
	if(key == 'm'){
		_camMoveEnable = !_camMoveEnable;
		_camStayPos    = _camBasePos;
	}

	// �g���b�N����I�u�W�F�N�g��ύX
	if(key == 's'){

		_activeObject++;

		if(_objectNum == _activeObject) _activeObject = 0;

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
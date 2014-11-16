#include "app.h"


/**
* コンストラクタ
*/
App::App(){


}

/**
* デストラクタ
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
	

	
	// 透明オブジェクトにするため、DepthTestは有効にしない
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


	// メインオブジェクトの設定
	_polygonShapes = new PolygonShapeSound[_objectNum];
	for(int i = 0; i < _objectNum; i++){
		new(_polygonShapes + i) PolygonShapeSound(i);
		_polygonShapes[i].setup();
	}

#else

	// メインオブジェクトの設定
	_polygonShapes = new PolygonShape[_objectNum];
	for(int i = 0; i < _objectNum; i++){
		new(_polygonShapes + i) PolygonShape(i);
		_polygonShapes[i].setup();
		
		_lights.push_back(ofLight());
	
	}



#endif

	// カメラ関連の設定
	_waitFrameNum   = 3;
	_frameCounter   = 0;
	_camMoveEnable  = true;


	// デフォルトは0番目のオブジェクト
	_targetPos      = _polygonShapes[_activeObject].getCurrentPos();
	_camBasePos     = _targetPos;
	_camDistination = _targetPos;
	_camVelocity    = _camBasePos;
	_camStayPos     = _camBasePos;



	// 背景オブジェクトの設定
	_stars = new Stars(2000);
	_stars->setup();


	// マウスドラッグ時の移動距離調整パラメータ
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


	// 指定されたフレーム数ごとにカメラの移動ベクトルを変更する
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


	/////// カメラ関連の設定 ///////

	if(_camMoveEnable){

		/////// カメラをオブジェクトに沿って動かす場合 ///////

		// カメラの基本位置と注視点を決定。
		// ある程度オブジェクトを中心からずらすため、
		// 注視点はオブジェクトそのものの位置ではなく、カメラの基本位置となる。
		// ※ 最終的には、カメラ位置を注視店からy軸方向に平行移動させる。
		_ccam.setCamBasePos(_camBasePos);
		_ccam.setTargetPos(_camBasePos);

	}else{

		/////// カメラの位置を固定し、オブジェクトの方向のみを向く場合 ///////

		// カメラの基本位置を固定し、注視点を決定。
		// 注視点はカメラを動かす場合と同様に、カメラの基本位置とする。
		// ※ カメラの基本位置は_camVelocityを加える形で徐々に移動するため、
		//    カメラの動きが滑らかになる
		_ccam.setCamBasePos(_camStayPos);
		_ccam.setTargetPos(_camBasePos);

	}

	// マウス操作による回転の座標変換をカメラに加える
	_ccam.execRotate();
		
	// 座標変換されたカメラの位置を、オブジェクトから一定の距離を保てる位置に変更する
	_ccam.keepADistance();


	// 更新された視点座標系の座標軸を計算する
	_ccam.calcCamAxis();


	// 最終的なカメラの位置と注視点の座標を適用する
	_ccam.setPosition();
	_ccam.lookAt();

	// ライトの位置をカメラの位置と同じにする
	ofVec3f lightPos = _ccam.getPosition();
	_light.setPosition(lightPos);


	// ライトを有効にした時点で、位置が更新される
	// ※ 回転行列をかける前に有効にする必要がある
	_light.enable();


	/////// 表示するオブジェクトの設定・描画 ///////
	
	// マウス操作による回転の座標変換を適用
	float angle;
	ofVec3f axis;
	_ccam.getRotation(angle, axis);


	ofRotate(angle, axis.x, axis.y, axis.z);
	


	
	ofPushMatrix();
	{

		_stars->draw();

		// LightをONにするとGL_COLOR_MATERIALが有効になるようだ.
		// 0.8.0のバグ??
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

	// ユーザが指定したバッファと、実際にドライバが確保するバッファのサイズを
	// 比較し、小さい方を採用する.もし大きい値を使うと、SoundStreamを閉じる際にエラーが発生する
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

	// ↑キー
	// カメラとオブジェクトの距離を近づける(-の場合は遠ざける)
	if(key == 357){
		_ccam.updateDistance(-20.0);
	}	

	// ↓キー
	// カメラとオブジェクトの距離を遠ざける(-の場合は近づける)
	if(key == 359){
		_ccam.updateDistance(20.0);
	}

	// オブジェクトの位置をデフォルトに戻す
	if(key == 'r'){
		_polygonShapes[_activeObject].resetCurrentPos();
	}

	// カメラをオブジェクトに沿って動かすかどうかを決める
	if(key == 'm'){
		_camMoveEnable = !_camMoveEnable;
		_camStayPos    = _camBasePos;
	}

	// トラックするオブジェクトを変更
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
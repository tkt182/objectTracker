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

	// メインオブジェクトの設定
	_polygonShape = new PolygonShape();
	_polygonShape->setup();


	// カメラ関連の設定
	_moveStep       = 15;  // 設定によっては、目標位置まで到達しない場合もある
	_waitFrameNum   = 10;
	_frameCounter   = 0;

	_camPos         = _polygonShape->getCurrentPos();
	_camDistination = _polygonShape->getCurrentPos();
	_camVelocity    = (_camDistination - _camPos) / _moveStep; 


	// 背景オブジェクトの設定
	_stars = new Stars(2000);
	_stars->setup();


}

//--------------------------------------------------------------
void App::update(){

	_polygonShape->update();


	// 指定されたフレーム数ごとにカメラの移動ベクトルを変更する
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


	/////// カメラ関連の設定 ///////

	// カメラの基本位置と注視点を決定.
	// ある程度オブジェクトを中心からずらすため、
	// 注視点はオブジェクトの位置ではなく、カメラの位置となる.
	// ※ 最終的には、カメラ位置を注視店からy軸方向に平行移動させる
	_ccam.setCamPos(_camPos);
	_ccam.setTargetPos(_camPos);
	

	// マウス操作による回転の座標変換をカメラに加える
	_ccam.execRotate();

	// 座標変換されたカメラの位置を、オブジェクトから一定の距離を保てる位置に変更する
	_ccam.keepADistance();


	// 更新された視点座標系の座標軸を計算する
	_ccam.calcCamAxis();


	// 最終的なカメラの位置と注視点の座標を適用する
	_ccam.setPosition();
	_ccam.lookAt();



	/////// 表示するオブジェクトの設定・描画 ///////
	
	// マウス操作による回転の座標変換を適用
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

}



//--------------------------------------------------------------
void App::keyPressed(int key){

	// ↑キー
	if(key == 357){
		_ccam.updateDistance(-50.0);
	}	

	// ↓キー
	if(key == 359){
		_ccam.updateDistance(50.0);
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
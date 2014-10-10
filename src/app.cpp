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
}


//--------------------------------------------------------------
void App::setup(){

	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofEnableDepthTest();
	//ofSetFullscreen(true);
	//ofHideCursor();

	ofBackground(0, 0, 0);

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


	ofColor cyan = ofColor::fromHex(0x00abec);
	ofColor magenta = ofColor::fromHex(0xec008c);
	ofColor yellow = ofColor::fromHex(0xffee00);
	ofColor white  = ofColor::fromHex(0xffffff);


	ofVec3f target = _polygonShape->getCurrentPos();


	_ccam.begin();

	/////// カメラ関連の設定 ///////

	// カメラの基本位置と注視点を決定
	_ccam.setCamPos(target);
	_ccam.setTargetPos(target);
	

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

		ofSetColor(white);

		_stars->draw();


		// translate and rotate to the current position and orientation
		ofPushMatrix();
		{

			ofSetColor(255);
			_polygonShape->draw();


		}
		ofPopMatrix();


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
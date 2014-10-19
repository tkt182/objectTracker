#ifndef __POLYGON_SHAPE_H_
#define __POLYGON_SHAPE_H_

#include <iostream>
#include <deque>
#include "ofMain.h"

class PolygonShape{

public:

	PolygonShape();
	virtual ~PolygonShape();

	void setup();
	void update();
	void draw();

	ofVec3f getCurrentPos();         // 現在の座標を取得する

private:

	ofVec3f        _currentPos;      // 中心座標
	ofVec3f        _moveDir;         // オブジェクトの進行方向
	ofVec3f        _velocity;        // 速度ベクトル
	ofVec3f        _friction;        // 摩擦(もどき)として働く速度ベクトル

	float          _prevTime, _currentTime, _timeDiff;
	float          _velocitySize;    // 移動する速度(スカラー値)
	float          _frictionSize;    // 摩擦(もどき)の大きさ(スカラー値)
	float          _angle;           // オブジェクトの時点角度


	deque<ofVec3f> _pathVertices;    // 移動履歴の頂点情報
	ofMesh         _pathLines;       // 移動履歴のメッシュ
	ofVbo          _vbo;

	int            _actionFrame;     // 次に速度ベクトルを変更するフレーム
	int            _frameCount;      // フレーム数のカウント


	ofFloatColor   _ambient;
	ofFloatColor   _diffuse;         
	ofFloatColor   _specular;
	float          _shininess;

	ofMaterial     _material;        // オブジェクトのマテリアル


	void updateTimeStep();
	void setMoveDir();
	void setVelocity();
	void setFriction();
	void updateCurrentPos();
	void updateAngle();


	

};


#endif /* __POLYGON_SHAPE_H_ */
#ifndef __POLYGON_SHAPE_H_
#define __POLYGON_SHAPE_H_

#include <iostream>
#include <deque>
#include "ofMain.h"

class PolygonShape{

public:

	PolygonShape();
	~PolygonShape();

	void setup();
	void update();
	void draw();

	ofVec3f getCurrentPos();         // 現在の座標を取得する

private:

	ofVec3f        _currentPos;      // 中心座標
	ofVec3f        _moveDir;         // オブジェクトの進行方向

	float          _distance;        // 移動する距離
	float          _angle;

	deque<ofVec3f> _pathVertices;    // 移動履歴の頂点情報
	ofMesh         _pathLines;       // 移動履歴のメッシュ
	ofVbo          _vbo;


	int            _actionFrame;     // 次に中心座標を変更するフレーム 
	int            _frameCounter;

	ofFloatColor   _ambient;
	ofFloatColor   _diffuse;         
	ofFloatColor   _specular;
	float          _shininess;

	ofMaterial     _material;        // オブジェクトのマテリアル



	void updateMoveDir();
	void updateDistance();
	void updateCurrentPos();
	void updateAngle();


	

};


#endif /* __POLYGON_SHAPE_H_ */
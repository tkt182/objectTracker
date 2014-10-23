#ifndef __POLYGON_SHAPE_H_
#define __POLYGON_SHAPE_H_

#include <iostream>
#include <vector>
#include <deque>
#include "ofMain.h"


class PolygonShape{

public:

	PolygonShape();
	virtual ~PolygonShape();

	virtual void setup();
	virtual void update();
	virtual void draw();

	ofVec3f getCurrentPos();         // 現在の座標を取得する
	void    resetCurrentPos();


protected:

	ofVec3f        _currentPos;         // 中心座標
	ofVec3f        _moveDir;            // オブジェクトの進行方向
	ofVec3f        _velocity;           // 速度ベクトル
	ofVec3f        _friction;           // 摩擦(もどき)として働く速度ベクトル

	float          _prevTime, _currentTime, _timeDiff;
	float          _velocitySize;       // 速さ(スカラー値)
	float          _velocitySizeLimit;  // 速さのリミット
	float          _frictionSize;       // 摩擦(もどき)の大きさ(スカラー値)
	float          _angle;              // オブジェクトの時点角度


	int                 _vboIndex;      // 中心座標のリセット毎に追加するvboのインデックス
	std::vector<ofMesh> _pathLines;     // 移動履歴の頂点情報
	std::vector<ofVbo> _vbos;

	int                _actionFrame;    // 次に速度ベクトルを変更するフレーム
	int                _frameCount;     // フレーム数のカウント


	ofFloatColor   _ambient;
	ofFloatColor   _diffuse;         
	ofFloatColor   _specular;
	float          _shininess;

	ofMaterial     _material;           // オブジェクトのマテリアル

	
	void updateTimeStep();
	void setMoveDir();
	void setFriction();
	void updateCurrentPos();
	void updateAngle();


	virtual void setVelocity();
	

};


#endif /* __POLYGON_SHAPE_H_ */
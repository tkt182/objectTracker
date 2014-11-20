#ifndef __POLYGON_SHAPE_SOUND_H_
#define __POLYGON_SHAPE_SOUND_H_


#include "polygonShape.h"

class PolygonShapeSound : public PolygonShape {

public:

	PolygonShapeSound(const int type = 0);
	virtual ~PolygonShapeSound();

	virtual void setup();
	virtual void update();

	void         setMagnitude(const float magnitude);
	void         changeMoveMode();

private:

	bool   _enableAutoMove;         // オブジェクトを自動で動かすか、音声入力を利用するか

	float  _magnitudeThresHold;     // 入力の閾値(速度ベクトルを更新する際に利用)
	float  _magnitude;              // 入力の大きさ

	virtual void setVelocity();


	float clampf(float value, float min, float max);

};


#endif /* __POLYGON_SHAPE_SOUND_H_ */
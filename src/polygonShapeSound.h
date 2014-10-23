#ifndef __POLYGON_SHAPE_SOUND_H_
#define __POLYGON_SHAPE_SOUND_H_


#include "polygonShape.h"

class PolygonShapeSound : public PolygonShape {

public:

	PolygonShapeSound();
	virtual ~PolygonShapeSound();

	virtual void setup();
	virtual void update();

	void setPower(const float power);


private:

	float  _powerLevel;     // 速度ベクトルを更新する際の閾値
	float  _power;

	virtual void setVelocity();
	void setFrictionSize();


};


#endif /* __POLYGON_SHAPE_SOUND_H_ */
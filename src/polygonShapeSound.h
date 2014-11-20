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

	bool   _enableAutoMove;         // �I�u�W�F�N�g�������œ��������A�������͂𗘗p���邩

	float  _magnitudeThresHold;     // ���͂�臒l(���x�x�N�g�����X�V����ۂɗ��p)
	float  _magnitude;              // ���͂̑傫��

	virtual void setVelocity();


	float clampf(float value, float min, float max);

};


#endif /* __POLYGON_SHAPE_SOUND_H_ */
#ifndef __STARS_H_
#define __STARS_H_

#include "ofMain.h"

class Stars{

public:

	Stars(int num = 1000, float radius = 4.0);
	virtual ~Stars();

	void setup();
	void draw();


private:

	int      _num;      // 表示する球の数
	float    _radius;   // 球の半径
	float    _limit;    // 球の座標を生成する際のMAX値
	ofVec3f* _pos;      // 球の中心座標

	ofFloatColor  _color;    // 球の色


};


#endif /* __STARS_H_ */
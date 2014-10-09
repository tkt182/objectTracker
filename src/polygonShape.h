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

	ofVec3f getCurrentPos();         // ���݂̍��W���擾����

private:

	ofVec3f        _currentPos;      // ���S���W
	ofVec3f        _moveDir;         // �I�u�W�F�N�g�̐i�s����
	ofVec3f        _velocity;
	float          _distance;        // �ړ����鋗��
	float          _angle;

	deque<ofVec3f> _pathVertices;    // �ړ������̒��_���
	ofMesh         _pathLines;       // �ړ������̃��b�V��

	int            _actionFrame;     // ���ɒ��S���W��ύX����t���[�� 
	int            _frameCounter;

	
	void updateMoveDir();
	void updateDistance();
	void updateCurrentPos();
	void updateAngle();


	

};


#endif /* __POLYGON_SHAPE_H_ */
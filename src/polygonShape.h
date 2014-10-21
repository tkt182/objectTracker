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

	ofVec3f getCurrentPos();         // ���݂̍��W���擾����

private:

	ofVec3f        _currentPos;      // ���S���W
	ofVec3f        _moveDir;         // �I�u�W�F�N�g�̐i�s����
	ofVec3f        _velocity;        // ���x�x�N�g��
	ofVec3f        _friction;        // ���C(���ǂ�)�Ƃ��ē������x�x�N�g��

	float          _prevTime, _currentTime, _timeDiff;
	float          _velocitySize;    // �ړ����鑬�x(�X�J���[�l)
	float          _frictionSize;    // ���C(���ǂ�)�̑傫��(�X�J���[�l)
	float          _angle;           // �I�u�W�F�N�g�̎��_�p�x


	deque<ofVec3f> _pathVertices;    // �ړ������̒��_���
	ofMesh         _pathLines;       // �ړ������̃��b�V��
	ofVbo          _vbo;

	int            _actionFrame;     // ���ɑ��x�x�N�g����ύX����t���[��
	int            _frameCount;      // �t���[�����̃J�E���g


	ofFloatColor   _ambient;
	ofFloatColor   _diffuse;         
	ofFloatColor   _specular;
	float          _shininess;

	ofMaterial     _material;        // �I�u�W�F�N�g�̃}�e���A��


	void updateTimeStep();
	void setMoveDir();
	void setVelocity();
	void setFriction();
	void updateCurrentPos();
	void updateAngle();


	

};


#endif /* __POLYGON_SHAPE_H_ */
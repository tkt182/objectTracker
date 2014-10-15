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
	ofVec3f        _distination;     // �ړ��ڕW�ƂȂ���W
	ofVec3f        _moveDir;         // �I�u�W�F�N�g�̐i�s����
	ofVec3f        _velocity;        // ���x�x�N�g��
	ofVec3f        _friction;        // ���C�x�N�g��


	float          _distance;         
	float          _velocitySize;    // �ړ����鑬�x(�X�J���[�l)
	float          _frictionSize;    // ���C�̑傫��(�X�J���[�l)
	float          _angle;

	deque<ofVec3f> _pathVertices;    // �ړ������̒��_���
	ofMesh         _pathLines;       // �ړ������̃��b�V��
	ofVbo          _vbo;

	int            _moveStep;        // �ڕW�ʒu�ɓ��B����܂ł̃X�e�b�v(�`���)
	int            _stepCounter;
	int            _actionFrame;     // ���ɒ��S���W��ύX����t���[�� 
	int            _frameCounter;


	ofFloatColor   _ambient;
	ofFloatColor   _diffuse;         
	ofFloatColor   _specular;
	float          _shininess;

	ofMaterial     _material;        // �I�u�W�F�N�g�̃}�e���A��


	void updateMoveDir();
	void updateDistination();
	void updateVelocity();
	void updateFriction();
	void updateCurrentPos();
	void updateAngle();


	

};


#endif /* __POLYGON_SHAPE_H_ */
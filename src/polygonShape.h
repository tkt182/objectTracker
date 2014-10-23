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

	ofVec3f getCurrentPos();         // ���݂̍��W���擾����
	void    resetCurrentPos();


protected:

	ofVec3f        _currentPos;         // ���S���W
	ofVec3f        _moveDir;            // �I�u�W�F�N�g�̐i�s����
	ofVec3f        _velocity;           // ���x�x�N�g��
	ofVec3f        _friction;           // ���C(���ǂ�)�Ƃ��ē������x�x�N�g��

	float          _prevTime, _currentTime, _timeDiff;
	float          _velocitySize;       // ����(�X�J���[�l)
	float          _velocitySizeLimit;  // �����̃��~�b�g
	float          _frictionSize;       // ���C(���ǂ�)�̑傫��(�X�J���[�l)
	float          _angle;              // �I�u�W�F�N�g�̎��_�p�x


	int                 _vboIndex;      // ���S���W�̃��Z�b�g���ɒǉ�����vbo�̃C���f�b�N�X
	std::vector<ofMesh> _pathLines;     // �ړ������̒��_���
	std::vector<ofVbo> _vbos;

	int                _actionFrame;    // ���ɑ��x�x�N�g����ύX����t���[��
	int                _frameCount;     // �t���[�����̃J�E���g


	ofFloatColor   _ambient;
	ofFloatColor   _diffuse;         
	ofFloatColor   _specular;
	float          _shininess;

	ofMaterial     _material;           // �I�u�W�F�N�g�̃}�e���A��

	
	void updateTimeStep();
	void setMoveDir();
	void setFriction();
	void updateCurrentPos();
	void updateAngle();


	virtual void setVelocity();
	

};


#endif /* __POLYGON_SHAPE_H_ */
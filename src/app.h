#include <vector>
#include <new>
#include <cstdio>
#include <ctime>

#include "ofMain.h"
#include "customCam.h"
#include "polygonShape.h"

#include "stars.h"


#define SOUND_DEVICE_ENABLE

#ifdef  SOUND_DEVICE_ENABLE
#include "polygonShapeSound.h"
#include "fft.h"
#define BUFFER_SIZE 32
#endif


class App : public ofBaseApp{


	public:

		App();
		virtual ~App();

		void setup();
		void update();
		void draw();
		void exit();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);


	private:
	
		CustomCam _ccam;                  // �J����
		ofLight   _light;                 // ���C�g
		
		ofVec3f   _camBasePos;            // ���݂̃J������"��{"�ʒu
		ofVec3f   _camDistination;        // �J�����̈ړ��ڕW(�I�u�W�F�N�g�̈ʒu)
		ofVec3f   _camVelocity;           // �J�����̑��x�x�N�g��

		ofVec3f   _targetPos;             // ���݂̃I�u�W�F�N�g�̈ʒu

		bool      _camMoveEnable;         // �J�����̈ʒu�𓮂������A�ʒu���Œ肷�邩�̃t���O
		ofVec3f   _camStayPos;            // �J�����Œ莞�̈ʒu

		float     _waitFrameNum;          // �J�����̑��x�x�N�g����ύX����t���[���Ԋu
		float     _frameCount;            // �t���[�����̃J�E���^�[
 
		ofVec2f   _lastMouse;             // 1�t���[���O�̃}�E�X�ʒu
		float     _dampen;                // �}�E�X����̒���
		

		int       _objectNum;             // �I�u�W�F�N�g�̐�
		int       _activeObject;          // �^�[�Q�b�g�ƂȂ��Ă���I�u�W�F�N�g�̔ԍ� 


#ifdef SOUND_DEVICE_ENABLE

		ofSoundStream      _soundStream;
		float*             _left;
		float              _magnitude[BUFFER_SIZE];
		float              _phase[BUFFER_SIZE];
		float              _power[BUFFER_SIZE];

		float              _maxPower;
		void audioIn(float* input, int bufferSize, int nChannels);

		Fft*               _fft;

		PolygonShapeSound* _polygonShapes;   // �^�[�Q�b�g�I�u�W�F�N�g(�I�[�f�B�I���͂���)

#else

		PolygonShape* _polygonShapes;        // �^�[�Q�b�g�I�u�W�F�N�g

#endif
		// �w�i�ɕ\�����鋅
		Stars* _stars;


};

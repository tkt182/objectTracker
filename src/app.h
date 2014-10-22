#include <vector>
#include <deque>
#include <cstdio>
#include <ctime>

#include "ofMain.h"
#include "customCam.h"
#include "polygonShape.h"
#include "polygonShapeSound.h"
#include "stars.h"


//#define SOUND_DEVICE_ENABLE

#ifdef  SOUND_DEVICE_ENABLE
#define BUFFER_SIZE 256
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
	
		ofVec3f _camPos;                // ���݂̃J�����ʒu
		ofVec3f _camDistination;        // �J�����̈ړ��ڕW(�I�u�W�F�N�g�̈ʒu)
		ofVec3f _camVelocity;           // �J�����̑��x�x�N�g��

		float   _waitFrameNum;          // �J�����̑��x�x�N�g����ύX����t���[���Ԋu
		float   _moveStep;              // �J�������ڕW�ʒu�܂ňړ�����̂ɕK�v�ȃX�e�b�v(�t���[��)��
		float   _frameCounter;          // �t���[�����̃J�E���^�[


		//a place to store the mouse position so we can measure incremental change  
		ofVec2f _lastMouse;
	
		// slows down the rotation 1 = 1 degree per pixel
		float _dampen;


		CustomCam _ccam;                // �J����
		ofLight   _light;               // ���C�g


#ifdef SOUND_DEVICE_ENABLE

		ofSoundStream      _soundStream;
		float*             _left;
		float              _maxPower;
		void audioIn(float* input, int bufferSize, int nChannels);

		PolygonShapeSound* _polygonShape;    // �^�[�Q�b�g�I�u�W�F�N�g(�I�[�f�B�I���͂���)


#else

		PolygonShape* _polygonShape;         // �^�[�Q�b�g�I�u�W�F�N�g

#endif
		// �w�i�ɕ\�����鋅
		Stars* _stars;


};

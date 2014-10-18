#include <vector>
#include <deque>
#include "ofMain.h"
#include "customCam.h"
#include "polygonShape.h"
#include "stars.h"



class App : public ofBaseApp{


	public:

		App();
		~App();

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

		// �J����
		CustomCam _ccam;

		// ���C�g
		ofLight   _light;

		// �^�[�Q�b�g�I�u�W�F�N�g
		PolygonShape* _polygonShape;

		// �w�i�ɕ\�����鋅
		Stars* _stars;


};

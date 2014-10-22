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
	
		ofVec3f _camPos;                // 現在のカメラ位置
		ofVec3f _camDistination;        // カメラの移動目標(オブジェクトの位置)
		ofVec3f _camVelocity;           // カメラの速度ベクトル

		float   _waitFrameNum;          // カメラの速度ベクトルを変更するフレーム間隔
		float   _moveStep;              // カメラが目標位置まで移動するのに必要なステップ(フレーム)数
		float   _frameCounter;          // フレーム数のカウンター


		//a place to store the mouse position so we can measure incremental change  
		ofVec2f _lastMouse;
	
		// slows down the rotation 1 = 1 degree per pixel
		float _dampen;


		CustomCam _ccam;                // カメラ
		ofLight   _light;               // ライト


#ifdef SOUND_DEVICE_ENABLE

		ofSoundStream      _soundStream;
		float*             _left;
		float              _maxPower;
		void audioIn(float* input, int bufferSize, int nChannels);

		PolygonShapeSound* _polygonShape;    // ターゲットオブジェクト(オーディオ入力あり)


#else

		PolygonShape* _polygonShape;         // ターゲットオブジェクト

#endif
		// 背景に表示する球
		Stars* _stars;


};

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
	
		CustomCam _ccam;                  // カメラ
		ofLight   _light;                 // ライト
		
		ofVec3f   _camBasePos;            // 現在のカメラの"基本"位置
		ofVec3f   _camDistination;        // カメラの移動目標(オブジェクトの位置)
		ofVec3f   _camVelocity;           // カメラの速度ベクトル

		ofVec3f   _targetPos;             // 現在のオブジェクトの位置

		bool      _camMoveEnable;         // カメラの位置を動かすか、位置を固定するかのフラグ
		ofVec3f   _camStayPos;            // カメラ固定時の位置

		float     _waitFrameNum;          // カメラの速度ベクトルを変更するフレーム間隔
		float     _frameCount;            // フレーム数のカウンター
 
		ofVec2f   _lastMouse;             // 1フレーム前のマウス位置
		float     _dampen;                // マウス動作の調節
		

		int       _objectNum;             // オブジェクトの数
		int       _activeObject;          // ターゲットとなっているオブジェクトの番号 


#ifdef SOUND_DEVICE_ENABLE

		ofSoundStream      _soundStream;
		float*             _left;
		float              _magnitude[BUFFER_SIZE];
		float              _phase[BUFFER_SIZE];
		float              _power[BUFFER_SIZE];

		float              _maxPower;
		void audioIn(float* input, int bufferSize, int nChannels);

		Fft*               _fft;

		PolygonShapeSound* _polygonShapes;   // ターゲットオブジェクト(オーディオ入力あり)

#else

		PolygonShape* _polygonShapes;        // ターゲットオブジェクト

#endif
		// 背景に表示する球
		Stars* _stars;


};

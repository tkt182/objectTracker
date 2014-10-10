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
	

		//a place to store the mouse position so we can measure incremental change  
		ofVec2f _lastMouse;
	
		// slows down the rotation 1 = 1 degree per pixel
		float _dampen;

		// カメラ
		CustomCam _ccam;

		// ターゲットオブジェクト
		PolygonShape* _polygonShape;


		// 背景に表示する球
		Stars* _stars;


};

#pragma once
#define FISH_NUM 15 

#include "ofMain.h"
#include "spring.h"
#include "particle.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxAutoControlPanel.h"
#include "foam.h"
#include "ofxOsc.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);	
    void audioIn(float * input, int bufferSize, int nChannels);
	
    
    
    //sound part
    
    vector <float> left;
    vector <float> volHistory;    
    int 	bufferCounter;
    int 	drawCounter;
    float smoothedVol;
    float scaledVol;
    float scaledVol1;
    ofSoundStream soundStream;
    float soundthreshold,soundamount;
    
    
    
    int number;    
    float radius;
    float xoffset; 
    float yoffset;
    float x;
    float y;
    float orin;
    float threshold; 
    float amount;
    
    int dragx, dragy, pressx, pressy;
    int press;
    

    
	ofxKinect kinect;
	ofxAutoControlPanel panel;    
    ofBlendMode blendMode;
    

  
    int buttontoggle,  shelftoggle, linetoggle;


    
    ofImage image, imageInk,  imageMask;
    ofImage result;
    ofxCvGrayscaleImage		resultAsCvImage;
    ofxCvGrayscaleImage		videoPrevFrameImage;
    ofxCvGrayscaleImage		videoDiffImage;
    ofxCvGrayscaleImage		videoDiffMHI, videoDiffMHI2;
    
    //float cvspeed;
    
    
    
    ofVideoPlayer           vidPlayer;
    ofxCvColorImage			videoColorCvImage;
    ofxCvGrayscaleImage		videoGrayscaleCvImage;
    
    // foam
    //vector < foam > foams;
    
    float mousealphaX, mousealphaY ;
    
    float noisevalue, noisetime;
    
    int posx, posy, sclx, scly;
    
        bool vidtoggle;
    float inkvalue[640*480];
    
    
    ofxCvContourFinder		contourFinder;
    
    ofxCvBlob blob1,blob2;
    
    
    ////////springs///////////////
     particle particleA;
    particle particleB;
    particle particleC;
    spring connector;
    spring connector2;
    vector<ofVec3f> points;
    
    
    int alphaToggle, blurToggle;

    float mouseblur;
    
    
    ofxOscReceiver receiver;
    float oscBlur, oscAlpha, oscFar;
    
    float maskX,maskY,maskSclX, maskSclY;
    
    int maskToggle;
};

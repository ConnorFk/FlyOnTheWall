#pragma once

#include "ofMain.h"

#import "ofxSpacebrew.h"

class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    
    // create your spacebrew object
    Spacebrew::Connection spacebrew;
    int cLR, cUD; // Camera Left and Right, camera Up and Down
    
    // Listen to spaceBrew messages
    void onMessage( Spacebrew::Message & m);
    
    
    void keyPressed(int key);
    void keyReleased(int key);
    
    
    //interface
    int red1,red2, red3,red4 ;
    ofVec2f c1, c2, t1, t2;
    ofVec2f rcc1, rcc2, rcc3, rcc4;
    float angleLR, angleUD;
    
    int ForB;
    int LorR;
    
    
    //strings
    bool bFirst;
    string typeStr;
    
    ofTrueTypeFont	verdana20;
    
    //sound
    int dir, acc,start, speed1,speed2,acc1,acc2;
    ofSoundPlayer ss,sad,sw,sca;
    
    
};


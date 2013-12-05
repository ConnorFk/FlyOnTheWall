#pragma once

#include "ofMain.h"
#import "ofxSpacebrew.h"

class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    // Creating spacebrew project
    Spacebrew::Connection spacebrew;
    
    // Listen to spaceBrew messages
    void onMessage( Spacebrew::Message & m);
    
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    int dir, acc,start;

    
};
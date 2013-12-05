#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
//    string host = Spacebrew::SPACEBREW_CLOUD; // "localhost";
    string host = Spacebrew::SPACEBREW_CLOUD; // "localhost";
    string name = "RC Car";
    string description = "Publisher Fly on the Wall";
    
    spacebrew.addPublish("Camera Left and Right", "range");
    spacebrew.addPublish("Camera Up and Down", "range");
    spacebrew.addPublish("Forward or Backward(or Stop)", "range");
    spacebrew.addPublish("Left or Right(or Stright)", "range");

    spacebrew.connect( host, name, description );

    
    ofBackground(0);
    ofSetCircleResolution(100);
    cLR = 90;
    cUD = 90;
    
    angleLR = PI * 0.5;
    angleUD = PI * 0.5;
    
    c1 = ofVec2f(ofGetWindowWidth()* 1/4, ofGetWindowHeight()*3/4);
    c2 = ofVec2f(ofGetWindowWidth()* 3/4, ofGetWindowHeight()*3/4);
    
    //RC Car
    rcc1 = ofVec2f(ofGetWindowWidth()* 1/5, ofGetWindowHeight()/4);
    rcc2 = ofVec2f(ofGetWindowWidth()* 2/5, ofGetWindowHeight()/4);
    rcc3 = ofVec2f(ofGetWindowWidth()* 3/5, ofGetWindowHeight()/4);
    rcc4 = ofVec2f(ofGetWindowWidth()* 4/5, ofGetWindowHeight()/4);
    
    //button
    red1 = 0;
    red2 = 0;
    red3 = 0;
    red4 = 0;
    
    //fonts
    verdana20.loadFont("verdana.ttf", 20, true, true);
	verdana20.setLineHeight(34.0f);
	verdana20.setLetterSpacing(1.035);
    


}

//--------------------------------------------------------------
void testApp::update(){
    
    if (cLR > 180) {cLR = 180;}
    if (cLR < 0) {cLR = 0;}
    if (cUD > 180) {cUD = 180;}
    if (cUD < 0) {cUD = 0;}

    if ( spacebrew.isConnected() ){
        spacebrew.sendRange("Camera Left or Right", (cLR) );
        spacebrew.sendRange("Camera Up or down", (cUD) );
        spacebrew.sendRange("Forward or Backward(or Stop)", ForB);
        spacebrew.sendRange("Left or Right(or Stright)", LorR);
    }
    
    //for interface
    angleLR = ofMap(cLR, 0, 180, PI * 7/6, PI * 11/6);
    angleUD = ofMap(cUD, 0, 180, - PI * 2/6, PI * 2/6);
    t1 = ofVec2f(c1.x + 100 * cos(angleLR), c1.y + 100 * sin(angleLR) );
    t2 = ofVec2f(c2.x + 100 * cos(angleUD), c2.y + 100 * sin(angleUD) );

}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(100,0,0);
    ofCircle(c1.x, c1.y, 80);
    ofSetColor(0,255,225);
    verdana20.drawString("camera", c1.x,c1.y + 40);
    verdana20.drawString("L or R", c1.x,c1.y + 70);
    
    
    ofSetColor(0,0,100);
    ofCircle(c2.x, c2.y, 80);
    ofSetColor(0,255,225);
    verdana20.drawString("camera", c2.x,c2.y + 40);
    verdana20.drawString("Up or Down", c2.x,c2.y + 70);
    
    
    ofSetColor(red1, 255, 0);
    ofCircle(rcc1.x, rcc1.y, 70);
    ofSetColor(0,255,225);
    verdana20.drawString("Forward", rcc1.x,rcc1.y + 90);
    
    ofSetColor(red2, 255, 0);
    ofCircle(rcc2.x, rcc2.y, 70);
    ofSetColor(0,255,225);
    verdana20.drawString("Backward", rcc2.x,rcc2.y + 90);
    
    ofSetColor(red3, 0, 255);
    ofCircle(rcc3.x, rcc3.y, 70);
    ofSetColor(0,255,225);
    verdana20.drawString("Left", rcc3.x,rcc3.y + 90);
    
    ofSetColor(red4, 0, 255);
    ofCircle(rcc4.x, rcc4.y, 70);
    ofSetColor(0,255,225);
    verdana20.drawString("Right", rcc4.x,rcc4.y + 90);
    
    
    ofSetLineWidth(5);
    ofSetColor(255, 0, 0);
    ofLine(c1, t1);
    ofSetColor(0, 0, 255);
    ofLine(c2, t2);
    

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    //camera angle
    if (key == 'r') {
        cLR += 15;
    }
    
    if (key == 'l') {
        cLR -= 15;
    }
    
    if (key == 'd') {
        cUD += 15;
    }
    
    if (key == 'u') {
        cUD -= 15;
    }
    
    //RC car
    if (key == 'f') {
        red1 = 255;
        ForB = 1;
    }
    
    if (key == 'b') {
        red2 = 255;
        ForB = 2;
        
    }
    
    if (key == 'w') {
        red3 = 255;
        LorR = 1;
    }
    
    if (key == 'e') {
        red4 = 255;
        LorR = 2;
        
    }


}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    red1 = 0;
    red2 = 0;
    red3 = 0;
    red4 = 0;

}
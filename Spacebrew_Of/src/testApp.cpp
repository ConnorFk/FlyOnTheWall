#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    dir = 0;
    acc = 0;
    start = 0;
    
    string host = Spacebrew::SPACEBREW_CLOUD;
    string name = "Car reciever";
    string description = "Recieving car dir/acc";
    
    // What I am listenning
    spacebrew.addSubscribe("dir", Spacebrew::TYPE_RANGE);
    spacebrew.addSubscribe("acc", Spacebrew::TYPE_RANGE);
    spacebrew.addSubscribe("start", Spacebrew::TYPE_RANGE);
    
    spacebrew.connect( host, name, description );
    
    // Listen to spacebrew events
    Spacebrew::addListener(this, spacebrew);

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(255);
    ofRect(100, 100, 100, 100);
    ofSetColor(250, 255, 255);
    if (start == 1 && dir == 1){
        ofSetColor(255, 255, 255);
    }
    if (start == 1 && dir == 2){
        ofSetColor(0, 100, 255);
    }
    if (start == 1 && dir == 0){
        ofSetColor(100, 0, 50);
    }
    if (start == 0){
        ofSetColor(100, 0, 50);
    }
    
    ofRect(500, 100, 100, 100);
    ofSetColor(0, 0, 255);
    if (start == 1 && acc == 1){
        ofSetColor(0, 0, 200);
    }
    if (start == 1 && acc == 2){
        ofSetColor(70, 70, 70);
    }
    if (start == 1 && acc == 0){
        ofSetColor(0, 0, 250);
    }
    if (start == 0){
        ofSetColor(0, 0, 250);
    }


}

//-------------------------------------------------------------------
void testApp::onMessage(Spacebrew::Message & m){
    if (m.name == "dir"){
        dir = m.valueRange();        
    }
    if (m.name == "acc"){
        acc = m.valueRange();
    }
    if (m.name == "start"){
        start = m.valueRange();
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
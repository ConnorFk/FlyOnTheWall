#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    dir = 0;
    acc = 0;
    start = 0;//the car stopped

    
    // spacebrew setup
    string host = Spacebrew::SPACEBREW_CLOUD;
    string name = "Car controller";
    string description = "Sending the car acc/dir/start";
    
    // what I am sending
    spacebrew.addPublish("dir", Spacebrew::TYPE_RANGE);
    spacebrew.addPublish("acc", Spacebrew::TYPE_RANGE);
    spacebrew.addPublish("start", Spacebrew::TYPE_RANGE);
    
    spacebrew.connect( host, name, description );


}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key=='f'){
        start = 1;
        spacebrew.sendRange("start",start);
    }
    
    if(key=='g'){
        start = 0;
        spacebrew.sendRange("start",start);
    }
    
//--------------------------------------------------------------start
    if(key=='w' && key=='s'){
        acc=0;
        spacebrew.sendRange("acc",acc);
    }
    if(key=='w'){
        acc=1;
        spacebrew.sendRange("acc",acc);
    }    
    if(key=='s'){
        acc=2;
        spacebrew.sendRange("acc",acc);
    }    
    if(key=='a' && key=='d'){
        dir=0;
        spacebrew.sendRange("dir",dir);
    }    
    if(key=='a'){
        dir=2;
        spacebrew.sendRange("dir",dir);
    }    
    if(key=='d'){
        dir=1;
        spacebrew.sendRange("dir",dir);
    }    
    if(key=='a' && key=='w'){
        dir=2;
        acc=1;
        spacebrew.sendRange("dir",dir);
        spacebrew.sendRange("acc",acc);
    }    
    if(key=='d' && key=='w'){
        dir=1;
        acc=1;
        spacebrew.sendRange("dir",dir);
        spacebrew.sendRange("acc",acc);
    }    
    if(key=='a' && key=='s'){
        dir=2;
        acc=-1;
        spacebrew.sendRange("acc",acc);
        spacebrew.sendRange("dir",dir);
    }    
    if(key=='d' && key=='s'){
        dir=1;
        acc=2;
        spacebrew.sendRange("dir",dir);
        spacebrew.sendRange("acc",acc);
    }
    

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    acc = 0;
    dir = 0;
    spacebrew.sendRange("dir",dir);
    spacebrew.sendRange("acc",acc);

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
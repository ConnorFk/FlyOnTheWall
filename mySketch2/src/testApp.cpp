#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0);
    ofEnableSmoothing();
    ofSetCircleResolution(100);
    ofEnableAlphaBlending();
    bg.loadImage("bg.jpg");
    time=0.1;
    time1=0.006;
    pressed=false;
    
    dir = 0;
    acc = 0;
    speed = 0;
    direction = 0;
    circle.x= 720;
    circle.y=80;
}

//--------------------------------------------------------------
void testApp::update(){
    pos.x = (1-time) * pos.x + (time) * circle.x;
    pos.y = (1-time) * pos.y + (time) * circle.y;
    prepos=pos;
    dis = (1-time1) * dis + (time1) * circle.x;
    //pos1.y = (1-time1) * pos1.y + (time1) * mouseY;
    predis=dis;
    
    
    speed+=acc;
    cout<<speed<<endl;
    
    direction+=dir;//the value about the rotation, but I am not clear what value to start so I just type 0
    cout<<direction<<endl;

    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255, 255, 255, 200);
    bg.draw(0,0, 1440, 300);
    
    ofSetColor(255, 370-pos.y-ofClamp(speed, 0, 30)*10, 250-pos.y-ofClamp(speed, 0, 30)*10, 100+pos.y/50);
    ofCircle(ofClamp(pos.x, 520, 920),ofClamp(pos.y, 0, 160), 60);
        for (int i=0; i<40; i++) {
    
        float step=12;
       

        float sinOfTime=sin(ofGetElapsedTimef());
        float sinOfTimeMapped=ofMap( sinOfTime, -1, 1, i*5, 100+i*step);
      //  float ah=ofMap(sinOfTimeMapped,50,255,
        ofSetColor(255, 255, 255, sinOfTimeMapped);
                ofCircle(720-(720-ofClamp(dis,670,770))/i*2, i*step, 2);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key=='w' && key=='s'){
        acc=0;
        circle.x= 720;
        circle.y= 80;
    }
    if(key=='w'){
        acc=1;
        circle.x= 720;
        circle.y= 20;
    }
    if(key=='s'){
        acc=-1;
        circle.x= 720;
        circle.y= 120;
    }
    
    if(key=='a' && key=='d'){
        dir=0;
        circle.x= 720;
        circle.y= 80;
    }
    
    if(key=='a'){
        dir=-1;
        circle.x= 520;
        circle.y= 80;
    }
    
    if(key=='d'){
        dir=1;
        circle.x= 900;
        circle.y= 80;
    }
    
    if(key=='a' && key=='w'){
        dir=-1;
        acc=1;
        circle.x= 520;
        circle.y=20;
    }
    
    if(key=='d' && key=='w'){
        dir=1;
        acc=1;
        circle.x= 820;
        circle.y=20;
    }
    
    if(key=='a' && key=='s'){
        dir=-1;
        acc=-1;
        circle.x= 620;
        circle.y=120;
    }
    
    if(key=='d' && key=='s'){
        dir=1;
        acc=-1;
        circle.x= 820;
        circle.y=120;
    }

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

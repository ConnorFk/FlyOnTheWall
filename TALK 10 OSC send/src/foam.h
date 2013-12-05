

#pragma once


#include "ofMain.h"
#include "ofxCvMain.h"

class foam {

	public: 
	ofPoint pos,  dotpos;
	float energy, energy2;
	void setup();
	//void update();
	void draw(float vol,  int posx,  int posy ,  int sclx,  int scly, int shelftoggle,int linetoggle, float volumn);
	
	void checkImage( ofxCvGrayscaleImage & myImage , int linetoggle ,float noisevalue, int xoffsetL, int xoffsetR ,int yoffsetL, int yoffsetR );

    
    void audioIn(float * input, int bufferSize, int nChannels); 
    
    
    float currentpix, dotCurrentpix, previouspix, differpix , shake;
    
    float damping;
    
    int alpha, orinalpha;

    
    float linewidth, swing, time;
    
    ofPoint vel, orinvel, accel;
    
     bool collision;
    
    int size,orinsize, dotsize, dotorinsize, rotate;
    
    int dotoffsetX2 , dotoffsetX1, dotoffsetY;
    
    ofImage stroke1;
    
    float noise, noiseoffset;

};
#include "testApp.h"


const int width = 1280;
const int height = 800;

//--------------------------------------------------------------
void testApp::setup() {
	
    
    receiver.setup(8000);
    
    ofBackground(0);
    ofSetRectMode(OF_RECTMODE_CORNER); 
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
	kinect.init(false, false);  // disable infrared/rgb video iamge (faster fps)
	kinect.open();
	panel.setup(280, 750);
	panel.addPanel("Settings");
	panel.addSlider("nearThreshold", 2377, 1500, 3500);
	panel.addSlider("farThreshold", 2722, 1500, 3500);
    panel.addSlider("offsetX", 58.3, -500, 1000);
    panel.addSlider("offsetY", 130.6, 500, -200);
    panel.addSlider("scaleX",  67.8, -6000, 2600);
    panel.addSlider("scaleY",  153.3, -600, 600);
    panel.addSlider("contourBlur", 0, 0, 60);  
    panel.addSlider("angle", 2.7, -30, 30); 
    panel.addSlider("maskX", -44.4, -500, 500); 
    panel.addSlider("maskY", -156.7, -300, 300); 
    panel.addSlider("maskSclX", 38.9, -500, 500); 
    panel.addSlider("maskSclY", 500, -500, 1000); 
    
    panel.addToggle("nearWhite", false);
	panel.addToggle("threshold", false);
	
	result.allocate(kinect.getWidth(), kinect.getHeight(), OF_IMAGE_GRAYSCALE);
    resultAsCvImage.allocate(result.width, result.height);
    
    videoPrevFrameImage.allocate(result.width, result.height);
    videoDiffImage.allocate(result.width, result.height);
    videoDiffMHI.allocate(result.width, result.height);
    videoDiffMHI2.allocate(result.width, result.height);

    



    //Sound input//////////////////////////
	soundStream.listDevices();
	int bufferSize = 256;
	left.assign(bufferSize, 0.0);
	volHistory.assign(400, 0.0);
	
	bufferCounter	= 0;
	drawCounter		= 0;
	smoothedVol     = 0.0;
	scaledVol		= 0.0;
    scaledVol1  =0.0; 
	soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
    soundthreshold=10;
    soundamount=0;
    
   ///////////////////////////////////
    
    
   
        //particleA.pos.set(100,100);
    
    
    
    
    
    
    // foam setup ////////////////////
//    for (int i = 0; i <3000; i++){
//		foam temp;
//		temp.setup();
//		foams.push_back(temp);
//	}
    
    
 
    
    /////////////////////////////////
    
//    noisevalue=0; 
//    noisetime=0;
    
    
    blendMode = OF_BLENDMODE_MULTIPLY;
    

    
    //image.loadImage("white.jpg");
    
    imageMask.loadImage("BlackMask.png");

    
    
    buttontoggle=0;
    linetoggle=0;
    //mousealphaX=mousealphaY=0;


        dragx=0;
        dragy=0;
        press=1;
    
    
    shelftoggle=0;
    
    vidtoggle=0;
    
    vidPlayer.loadMovie("background.jpg");
    
     imageInk.allocate(640, 480, OF_IMAGE_COLOR_ALPHA);
    
    
    
   /////////////////////////////////////// ////////spring stroke setup////////////////
    particleA.bFixed = true;
    
    particleA.pos.set(100,100);
    particleB.pos.set(100,100);
    particleC.pos.set(100,100);
    
    connector.springiness = 0.15;
    connector.distance = 0;
    connector.particleA = &particleA;
    connector.particleB = &particleB;
    
    connector2.springiness = 0.05;
    connector2.distance = 0;
    connector2.particleA = &particleB;
    connector2.particleB = &particleC;
   
    
    
    
      alphaToggle=1; 
      blurToggle=2;
      maskToggle=2;
    
    oscBlur=0;
    oscAlpha=0;
    oscFar=0;
}





//--------------------------------------------------------------

void testApp::update() {
	kinect.update();
	if(kinect.isFrameNew()) {
		float* distancePixels = kinect.getDistancePixels(); // distance in millimeters
		unsigned char* resultPixels = result.getPixels();
		int n = kinect.getWidth() * kinect.getHeight();
		float nearThreshold = panel.getValueF("nearThreshold")+oscFar*5;
		float farThreshold = panel.getValueF("farThreshold")+oscFar*5;
		int nearTarget, farTarget;
		bool threshold = panel.getValueB("threshold");
		int thresholdLevel = (nearTarget + farTarget) / 2;
		bool nearWhite = panel.getValueB("nearWhite");
		
        
        if(nearWhite) {
			nearTarget = 255;
			farTarget = 0;
		} else {
			nearTarget = 0;
			farTarget = 255;
		}
		if(nearThreshold != farThreshold) {
			for(int i = 0; i < n; i++) {
				float cur = distancePixels[i];
                float precur;
				if(cur != 0) { // only remap nonzeros
				
					// this code will threshold data to white or black
					if(threshold) {
						if(cur > thresholdLevel) {
							if(nearWhite) {
								cur = 0;
							} else {
								cur = 255;
							}
						} else {
							if(nearWhite) {
								cur = 255;
							} else {
								cur = 0;
							}
						}
					}
					
					// alternatively, just remap between 0 and 255
					else {
						cur = ofMap(cur, nearThreshold, farThreshold, nearTarget, farTarget, true);
					}
				}
                
                
				resultPixels[i] = cur;
			}
		}
    
		result.update();
	
    
        
        posx=panel.getValueF("offsetX"); 
        posy=panel.getValueF("offsetY"); 
        sclx=panel.getValueF("scaleX"); 
        scly=panel.getValueF("scaleY"); 
        
        maskX= panel.getValueF("maskX");
        maskY=panel.getValueF("maskY");
        maskSclX=panel.getValueF("maskSclX");
        maskSclY=panel.getValueF("maskSclY");
        
        
	//	videoGrayscaleCvImage = videoColorCvImage; 
        	
        
        

     resultAsCvImage.setFromPixels(result.getPixels(),result.width, result.height);
        
        

        
      //Blurness 
        
        
       // resultAsCvImage.blur(panel.getValueF("contourBlur")+ofMap(mousealphaY, 0, ofGetHeight(),0,250)); 
        
        
        resultAsCvImage.blur(panel.getValueF("contourBlur")+oscBlur*100);   
        
        
//        if(blurToggle%2==0){
//            
//          resultAsCvImage.blur(panel.getValueF("contourBlur")+ofMap(mousealphaY, 0, ofGetHeight(),0,200));  
//            
//        }else{
//            
//          resultAsCvImage.blur(panel.getValueF("contourBlur")+oscBlur*100);   
//        }
        
    
        resultAsCvImage.mirror(0,1);

    
        
        

        
        
        //cv for difference////////////
       // int thresholdcv			= panel.getValueI("thresholdcv");
        videoDiffImage.absDiff(resultAsCvImage, videoPrevFrameImage);
        //videoDiffImage.threshold(thresholdcv);
        videoPrevFrameImage = resultAsCvImage;      
        //cvspeed= ofMap(videoDiffImage.countNonZeroInRegion(0, 0, 640, 480), 0,5000, 0, 5);
    
        
        
        
        

        videoDiffMHI += videoDiffImage;
        videoDiffMHI -= 20;
        videoDiffMHI.blur(9);

        
        contourFinder.findContours(videoDiffImage, 7000, 1000000, 1, false, true);

    } 
    //// end of kinect frame new    
        
        
        
        
        
    //////////////////////////// sound threshold
        
        if (soundthreshold==1){
            soundamount+=0.3;
            soundthreshold++;
        };
        
        
        if ( soundthreshold==-1) {
            
            soundamount -=.3;
            soundthreshold++;
        };
                
        scaledVol1 = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
        scaledVol= scaledVol1* (1.0+soundamount);   
        
        //int thresholdvolumn	= panel.getValueI("thresholdvolumn");
        
        
        
        
        
        
   //particle//////////////////////////////
                
//        int ofxLeft=posx+dragx;
//        int ofxRight=resultAsCvImage.width+sclx;
//    int ofyLeft=posy+dragy;
//    int ofyRight=resultAsCvImage.height+scly;
//    
//        for (int i = 0; i < foams.size(); i++){
//
//          //  noisevalue=ofNoise(noisetime+i/10)*(ofRandom(100,200));   
//        
//        foams[i].checkImage(resultAsCvImage, linetoggle, noisevalue, ofxLeft, ofxRight, ofyLeft, ofyRight );
//          
//        }
 
    
    
     
   
    
    
    
    
    // end of  kinect.isFrameNew
    // kinect rotate Angle
    kinect.setCameraTiltAngle(panel.getValueF("angle"));
    
    
//    mousealphaY =  ofMap(mouseY, 0, 1024, 0, 255) ;
//    mousealphaX =  ofMap(mouseX, 0, 767, 255, 0) ;

     
    
    vidPlayer.idleMovie();
    
    
    
    
    
    
    
    
    ///////////////contour finder////////////
    
     if(contourFinder.nBlobs>0) {
         
      blob1 = contourFinder.blobs[0];
     
     if(contourFinder.nBlobs>1) {    
     blob2 = contourFinder.blobs[1];
     }    
    }
    
    
    
    
    
///////////////////////////OSC////////////////////////////////////////////    
    
    // check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
		// check for mouse moved message


        if(m.getAddress() == "/1/fader1"){
			oscAlpha = m.getArgAsFloat(0);
		}
        
        
        if(m.getAddress() == "/1/fader2"){
			oscBlur = m.getArgAsFloat(0);
		}
        
        
        
        if(m.getAddress() == "/1/fader3"){
			oscFar = m.getArgAsFloat(0);
		}
        
        
        
	}
  
    
    
    
    

    
   
}





//--------------------------------------------------------------



void testApp::draw() {
    

//    ofSetColor(255);
//    vidPlayer.draw(posx+dragx, posy+dragy,width+sclx,height+scly);
//    vidPlayer.play();
    
    
    // draw the white image  press "b"    
    if (buttontoggle==2){

        ofSetColor(255, 255, 255);
        image.draw(posx+dragx, posy+dragy,width+sclx,height+scly);
     
    } 


    
    if (vidtoggle==1){
        ofSetColor(255);
        vidPlayer.draw(0, 0, ofGetWidth(), ofGetHeight());
        vidPlayer.play();
        
    }
    
    
    
    
    
    float CvWidth=resultAsCvImage.width;
    float CvHeight=resultAsCvImage.height;




/////////////////
 
    
     if (buttontoggle==2){
    
        ofSetColor(255);
        resultAsCvImage.draw(posx+dragx,posy+dragy,CvWidth+sclx, CvHeight+scly);
     }

    


    
    if (shelftoggle==1){
    
        
        ofSetColor(255,255);
     // ofRect(0,0, ofGetWidth(), ofGetHeight());
       resultAsCvImage.draw(posx+dragx,posy+dragy,CvWidth+sclx, CvHeight+scly);
        
        
        
/////////////////////////////////////draw shadows///////////////////////////////////////////  
       unsigned char * pixels2 = resultAsCvImage.getPixels(); 
	   unsigned char * pixels = videoDiffMHI.getPixels();
        
        unsigned char * imgPixels = imageInk.getPixels();
        
        //float pct = ofMap(mouseX, 0, ofGetWidth(), 0, 1, true);     // get the mouse as a pct across the screen
        
        

      noisetime+=0.01; 
        
        
	  for (int i = 0; i < resultAsCvImage.width; i+=1){
		for (int j = 0; j < resultAsCvImage.height; j+=1){
			
            int value = pixels[j * resultAsCvImage.width + i];
            int value2 = pixels2[j * resultAsCvImage.width + i];
			
            float circleX=posx+dragx+ i*((CvWidth+sclx)/CvWidth);
            float circleY=posy+dragy+j*((CvHeight+scly)/CvHeight);
            
            // draw feedback shadow  
            if(value >5 && value2>100){
                ofSetColor(0, ofClamp(value/10,0,255));
                ofCircle(circleX, circleY , 5);
            }  
            
            
            
      ///////// popup human layer///////////

//            float noiseX = ofMap(i, 0,CvWidth, 0,2);
//            float noiseY = ofMap(j, 0,CvHeight, 0,2);
//            noisevalue=ofNoise(noiseX+noisetime,noiseY)*25;
//        
//            if(value2<200){
//                imgPixels[(j * resultAsCvImage.width + i)*4+3]= 255-value2;   //Alpha
//                imgPixels[(j * resultAsCvImage.width + i)*4]= value2;    //R
//                 imgPixels[(j * resultAsCvImage.width + i)*4+1]= value2;    //G
//                 imgPixels[(j * resultAsCvImage.width + i)*4+2]= value2;    //B
//            } else {                 
//                imgPixels[(j * resultAsCvImage.width + i)*4+3]=0;
//            }
            
            
            
 
        
          }
	    
        }
//
    //    ofSetColor(255);
//        imageInk.update(); 
//        imageInk.draw(posx+dragx,posy+dragy,CvWidth+sclx, CvHeight+scly);
        

        
        
        

    }
    
 ////////////end of shelf toggle//////////////////////////////////////////////////   /////////////////////////////////////////////////////////////////
 
    
    
    
    
    
    
    /////////////////////////////////////////////////   /////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////   /////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////   /////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////   /////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////   /////////////////////////////////////////////////////////////////
  
    
    if(shelftoggle==2){
        
        
        ofSetColor(255,255);
       ofRect(0,0, ofGetWidth(), ofGetHeight());
        
        
        
        
        ///////////////SPRING START///////////////////////////////
    
        
        
        /////////////////////////////////////// ////////spring stroke update////////////////  
        
        particleA.pos.set(mouseX, mouseY);
        
        
        particleB.resetForce();
        connector.update();
        particleB.addDampingForce();
        particleB.update();
        
        particleC.resetForce();
        connector2.update();
        particleC.addDampingForce();
        particleC.update();
        
        points.push_back(particleC.pos);
        
        
        ///////////////////////////////////spring stroke draw//////////////////////////////
        
        if (points.size() > 90){
            points.erase(points.begin());
        }
        
        ofMesh mesh;
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        
        for (int i = 0; i < points.size(); i++){
            
            //float pct = ofMap(i, 0, points.size()-1, 0,1);
            
            ofVec2f thisPoint = points[i];
            ofVec2f nextPoint = points[i+1];
            ofVec2f direction = (nextPoint - thisPoint);
            float distance = direction.length();
            ofVec2f unitDirection = direction.normalized();
            ofVec2f toTheLeft = unitDirection.getRotated(-90, ofVec3f(0,0,1));
            ofVec2f toTheRight = unitDirection.getRotated(90, ofVec3f(0,0,1));
            float thickness = ofMap(distance, 0, 50, 38, 2, true);
            ofVec2f leftPoint = thisPoint+toTheLeft*thickness;
            ofVec2f rightPoint = thisPoint+toTheRight*thickness;
            
            mesh.addVertex(ofVec2f(leftPoint.x, leftPoint.y));
            mesh.addVertex(ofVec2f(rightPoint.x, rightPoint.y));
            
        }
        
        ofSetColor(0,100+scaledVol*100);        
        mesh.draw();
        
        
        ///////////////SPRING END////////////////////////// 
        
   
    }
    
    
    
    
    
    
    /////////////////////////////////////////////////   /////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////   /////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////   /////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////   /////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////   /////////////////////////////////////////////////////////////////
    
    
    
    
    
    
    
    
    /// draw particle
   

//    for (int i = 0; i < foams.size(); i++){
//        foams[i].draw(i/100, posx, posy, sclx, scly, shelftoggle, linetoggle, scaledVol);
//       }       
//    
        
    
    
   
    
    
    
 

    
    //ofSetColor(0, 0, 0, mousealphaX);
    ofSetColor(0, 0, 0, oscAlpha*255);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());   
    

    
    
    
    ///////the mask
   
    if(maskToggle%2==0){
    ofSetColor(255);
    imageMask.draw(maskX,maskY,ofGetWidth()+maskSclX, ofGetHeight()+maskSclY);
    }
     

}





//--------------------------------------------------------------
void testApp::exit() {
	kinect.close();
}





//--------------------------------------------------------------
void testApp::audioIn(float * input, int bufferSize, int nChannels){	
	
	float curVol = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;	
    
	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume	
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2]*0.5;
        
		curVol += left[i] * left[i];
		numCounted+=2;
	}
	
	//this is how we get the mean of rms :) 
	curVol /= (float)numCounted;
	
	// this is how we get the root of rms :) 
	curVol = sqrt( curVol );
	
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;
	
	bufferCounter++;
	
}



//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
    
    switch (key) {
 
                                
        case ' ':
            shelftoggle=0;
            linetoggle=0; 
            vidtoggle=0;
            buttontoggle=0;
            vidPlayer.loadMovie("background.jpg");
            vidPlayer.stop();
             image.loadImage("background.jpg");
            break; 
            
        case 'b':
            shelftoggle=0;
            vidtoggle=0;
            buttontoggle=2;
            image.loadImage("white.jpg");
            break; 
            
            
 
        case 'm':
            CGDisplayHideCursor(kCGDirectMainDisplay);          
            break; 
            
                   
        case '1':
            shelftoggle=1; 
            break; 
            
            
            
//        case 'q':
//            shelftoggle=0; 
//            vidtoggle=11;
////            vidPlayer.loadMovie("brushExport1.mov");
////            vidPlayer.firstFrame();
////            vidPlayer.play();
//            break;
            
            
            
            
        case '2':
            shelftoggle=2;         
            break; 
            
        case '3':
            shelftoggle=3;         
            break; 
            
        case '4':
            shelftoggle=4;   

            break; 
            
        case '5':
            shelftoggle=5;         
            break; 
            
            
        case '6':
            shelftoggle=6;         
            break; 
            

        
        case '0':
            maskToggle+=1;
            break; 
    
            
        case '=':
            soundthreshold=1;
            break;          
        case '-':
            soundthreshold=-1;
            break; 
            
            
        case 'z':
            press+=1;
            break; 
            
        case 'a':
            vidtoggle=1;
            vidPlayer.loadMovie("Comp 1.mp4");
            vidPlayer.firstFrame();
            vidPlayer.play();
            break;   
            
        case 's':
            vidtoggle=1;
            vidPlayer.loadMovie("Comp 2.mp4");
            vidPlayer.firstFrame();
            vidPlayer.play();
            break;   
            
        case 'd':
            vidtoggle=1;
            vidPlayer.loadMovie("Comp 3.mp4");
            vidPlayer.firstFrame();
            vidPlayer.play();
            break;   
            
        case 'f':
            vidtoggle=1;
            vidPlayer.loadMovie("Comp 4.mp4");
            vidPlayer.firstFrame();
            vidPlayer.play();
            break;   
            
        case 'g':
            vidtoggle=1;
            vidPlayer.loadMovie("Comp 5.mp4");
            vidPlayer.firstFrame();
            vidPlayer.play();
            break;   
            
            
            
//        case 'p':
//            alphaToggle+=1;
//            break; 
//            
//            
//        case 'o':
//            blurToggle+=1;          
//            break; 
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
  
    if(press%2==0){  
    dragx=x-pressx;
    dragy=y-pressy;
      }
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
   
    if(press%2==0){
    pressx=x-dragx;
    pressy=y-dragy;
   }
    
   
//    for (int i = 0; i < particleBounces.size(); i++){
//		particleBounces[i].setInitialCondition(x,y,ofRandom(-10,10), ofRandom(-10,10));
//	}
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

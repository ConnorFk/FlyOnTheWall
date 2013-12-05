

#include "foam.h"


void foam::setup(){
	pos.x = ofRandom(0,ofGetWidth());
	pos.y = ofRandom(0,ofGetHeight());
    
    dotpos.x = ofRandom(0,ofGetWidth());
	dotpos.y =ofRandom(0,ofGetHeight());
    
	energy = 0;
    energy2=0;
    shake=0;
    orinalpha=ofRandom(20,150);
    alpha=orinalpha;
    
    linewidth=ofRandom(1,4);
    
    swing=ofRandom(-6,6);
    
    
    time=ofRandom(10);
    
    //orinvel=ofRandom(12,16);
    
    vel.set(ofRandom(-1,1),ofRandom(-1,1));

    
    //accel.set(-0.1,-0.1);
    
    orinsize=ofRandom(10,50);
    size=orinsize;
    
    dotorinsize=ofRandom(2,10);
    dotsize=dotorinsize;
    
    rotate=ofRandom(0,90);

    collision=0;
    
    
    stroke1.loadImage("spot.png");
    

    
}






void foam::checkImage( ofxCvGrayscaleImage & myImage,  int linetoggle,  float noisevalue, int xoffsetL, int xoffsetR ,int yoffsetL, int yoffsetR ){
	
        dotoffsetX1=xoffsetL;
 
    
    
  //////////////////////position//////////////////////
    
         float pctx = (pos.x-xoffsetL) / (float)(xoffsetR);
         pctx = ofClamp(pctx, 0,1);
         float pcty = (pos.y) / (float)(ofGetHeight());
         pcty = ofClamp(pcty, 0,1);
         
         int pixXinImage = myImage.width * pctx;
         int pixYinImage = myImage.height * pcty;
         
         unsigned char * pixels = myImage.getPixels();
         

         
         //pixel difference//////
         
         currentpix = pixels[pixYinImage * myImage.width + pixXinImage];    
    
    differpix = currentpix - previouspix ;
    previouspix= currentpix;
    
    if (currentpix < 10){
        
        energy = 0.10f * energy + 0.90f * 1.0f;
        
    } else { 
        
        if (energy>0) {
            energy = energy-0.085;
        }else {
            energy=0;
        }
    }
    
    
    
    
    //////////////////////dot position//////////////////////
    
    if(linetoggle==1){ 
        

        
        float dotpctx = (dotpos.x-xoffsetL) / (float)(xoffsetR);
        dotpctx = ofClamp(dotpctx, 0,1);
        float dotpcty = (dotpos.y-yoffsetL) / (float)(yoffsetR);
        dotpcty = ofClamp(dotpcty, 0,1);
        
        int dotpixXinImage = myImage.width * dotpctx;
        int dotpixYinImage = myImage.height * dotpcty;
        
        //unsigned char * dotpixels = myImage.getPixels();
        
        unsigned char * pixels2 = myImage.getPixels();
        
        dotCurrentpix = pixels2[dotpixYinImage * myImage.width + dotpixXinImage];
        
        
        
        
        ///speed control////////////////
        
        dotpos+=vel;
          
        
        if (dotCurrentpix < 10){
                
                vel*=-1;
                accel*=-1;

            dotpos.x+=vel.x*3;
            dotpos.y+=vel.y*3;
        }
        
        
        
        
        
        
        if (dotpos.x>xoffsetL+xoffsetR) {
            dotpos.x=xoffsetL;
        }
        
        if (dotpos.x<xoffsetL) {
            dotpos.x=xoffsetL+xoffsetR;
        }
        
        if (dotpos.y>yoffsetL+yoffsetR) {
            dotpos.y=yoffsetL;
        }
        
        if (dotpos.y<yoffsetL) {
            dotpos.y=yoffsetL+yoffsetR;
        }
        
    }
    
    
    


    
}



void foam::draw(float vol,  int posx,  int posy ,  int sclx,  int scly,  int shelftoggle, int linetoggle, float volumn ){
	
    //ofEnableAlphaBlending();

   
    


       
  
     

    
    if(shelftoggle==3){
        ofSetColor(255, orinalpha);
       ofCircle(pos.x, pos.y, orinsize *0.5 * energy+differpix/20);
           }
    
    if(shelftoggle==4){
        ofSetColor(255, 100+orinalpha);
        stroke1.draw(pos.x,pos.y,80 *energy+differpix/20, 80 * energy+differpix/20);
    }
    
    
    if(shelftoggle==5){
        
        ofSetColor(255, orinalpha);
        ofRect(pos.x, pos.y, orinsize *energy, (orinsize+10) * energy+differpix/20);
    }
    
    if(shelftoggle==6){

        ofSetColor(255, 255);
        ofCircle(pos.x, pos.y, differpix/30);
    }
    
    
    
    /////////////draw particles////////////
//    if(linetoggle==1){
//    
//        if(dotCurrentpix>100){ 
//        ofSetColor(0,100+orinalpha);
//        ofCircle(dotpos.x, dotpos.y, linewidth);
//      }
//    }
    


}

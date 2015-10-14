#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){	 

    
    ofSetFrameRate(60);
    ofBackground(0);
    
    mainOffSetXPos = (ofGetWidth() - (baseArch.fassadeCorner[0].x + baseArch.fassadeCorner[1].x)) * 0.5;
    mainOffSetYPos = (ofGetHeight() - (baseArch.fassadeCorner[0].y + baseArch.fassadeCorner[3].y)) * 0.5;
    baseArch.mainOffSetXPos = mainOffSetXPos;
    baseArch.mainOffSetYPos = mainOffSetYPos;

    
	nBandsToGet = 32 * 2;
    
    fft.fft.stream.setDeviceID(3);
    fft.setup();
    fft.fft.setup(16384);
    fft.setNumFFTBins(nBandsToGet);
    fft.setFFTpercentage(0.9);
    
    calligraphy.inputBaseArch( baseArch );
    calligraphy.inputFFTP( fft );
    
}




//--------------------------------------------------------------
void ofApp::update(){
	
    fft.update();
    calligraphy.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofPushMatrix();
    
    ofTranslate( mainOffSetXPos, mainOffSetYPos );
    
//    baseArch.guideLines();
//    baseArch.guidePoints();
    
    baseArch.guideFrames( ofColor(255, 0, 0) );
    
    calligraphy.draw();

    baseArch.drawEdgeCover( ofColor(0) );
    
    ofPopMatrix();
    
    
}


//--------------------------------------------------------------
void ofApp::exit(){
    
}



//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}
 
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

    mainOffSetXPos = (ofGetWidth() - (baseArch.fassadeCorner[0].x + baseArch.fassadeCorner[1].x)) * 0.5;
    mainOffSetYPos = (ofGetHeight() - (baseArch.fassadeCorner[0].y + baseArch.fassadeCorner[3].y)) * 0.5;
    baseArch.mainOffSetXPos = mainOffSetXPos;
    baseArch.mainOffSetYPos = mainOffSetYPos;

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


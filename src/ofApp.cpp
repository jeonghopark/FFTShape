#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){	 

    
    ofSetFrameRate(60);
    ofBackground(0);
    
    mainOffSetXPos = (ofGetWidth() - (baseArch.fassadeCorner[0].x + baseArch.fassadeCorner[1].x)) * 0.5;
    mainOffSetYPos = (ofGetHeight() - (baseArch.fassadeCorner[0].y + baseArch.fassadeCorner[3].y)) * 0.5;
    baseArch.mainOffSetXPos = mainOffSetXPos;
    baseArch.mainOffSetYPos = mainOffSetYPos;

    
	
	fftSmoothed = new float[8192];
	for (int i = 0; i < 8192; i++){
		fftSmoothed[i] = 0;
	}
	
	nBandsToGet = 32 * 2;
    
    for(int i=0; i<10; i++) {
        int _index = round(ofRandom(360));
        captureFFTIndex.push_back( _index );
        captureFFTSmoothed.push_back( fftSmoothed[_index] );
    }
    
    
    
    xPosition = 150;
    
    calliYShift = 0;
    calliIndex = -1;
    
    fft.fft.stream.setDeviceID(2);
    fft.setup();
    fft.fft.setup(16384 * 0.5);
    fft.setNumFFTBins(nBandsToGet);
    fft.setFFTpercentage(0.9);

}




//--------------------------------------------------------------
void ofApp::update(){
	
    fft.update();
    
    captureTimer = 9;

    if(ofGetFrameNum()%captureTimer==0) {
        calligraphy.inputFftSmoothed(fft.getSpectrum());
    }
    
    
//    if(ofGetFrameNum()%captureTimer==0) {
//        Calligraphy _eCalligraphy;
//        _eCalligraphy.inputFftSmoothed(fft.getSpectrum());
//        
//
//        calligraphies.push_back(_eCalligraphy);
//        calliIndex++;
//        
//        if (calligraphies.size()>0) {
//            
//            float _changedX = calliIndex % 3;
//            float _changedY = calliYShift;
//
//            if ((calliIndex%3==0)&&bClliXPosChange==false) {
//                calliYShift++;
//                bClliXPosChange = true;
//            }
//            
//            if (calliIndex%3==2){
//                bClliXPosChange = false;
//            }
//
//            calliPos.push_back( ofVec3f(_changedX, _changedY, 0) );
//            
//        }
//
//        if (calliIndex>21) {
//            calligraphies.erase(calligraphies.begin());
//            calliPos.erase(calliPos.begin());
//            calliYShift = 0;
//            calliIndex = 0;
//        }
//        
//
//    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofPushMatrix();
    
    ofTranslate( mainOffSetXPos, mainOffSetYPos );
    
    baseArch.guideFrames();
    baseArch.drawEdgeCover();
    baseArch.guideLines();
    baseArch.guidePoints();
    
    ofPopMatrix();
    
    
    ofPushMatrix();

    ofTranslate( mainOffSetXPos, mainOffSetYPos );

    normalFFT();
    lineCircleFFT();
    lineCircleCaptureFFT();
    
    
    calligraphy.draw( baseArch.framesCenter[11][5].x, baseArch.framesCenter[11][5].y );

//    for (int i=0; i<calligraphies.size(); i++) {
//        calligraphies[i].draw( calliPos[i].x, calliPos[i].y );
//    }
    
    
    ofPopMatrix();
    


    
    
    
}


//--------------------------------------------------------------
void ofApp::exit(){
    
}


//--------------------------------------------------------------
void ofApp::normalFFT(){
    
    ofPushMatrix();
    
    ofPushStyle();
    
    ofSetColor(255);

    ofNoFill();
    
    float _heightRatio = 1;
    float _width = (baseArch.fassadeCorner[1].x - baseArch.fassadeCorner[0].x) / nBandsToGet;

    for (int i = 0; i<nBandsToGet; i++){
        
        float _w = _width;
        float _h = -fft.getSpectrum()[i] * _heightRatio;
        float _x = baseArch.fassadeCorner[0].x + i * _w;
        float _y = baseArch.fassadeCorner[3].y;

        ofDrawRectangle( _x, _y, _w, _h );
    }
    
    ofPopStyle();
    
    ofPopMatrix();

}


//--------------------------------------------------------------
void ofApp::lineCircleFFT(float _yPos){
    
    
    ofPushMatrix();
    
    ofPushStyle();
    
    ofSetColor(255);
    
    float _heightRatio = 1;
    float _width = (baseArch.fassadeCorner[1].x - baseArch.fassadeCorner[0].x) / nBandsToGet;

    for (int i = 0;i < nBandsToGet-1; i++){
        float _w = _width;
        
        float _fftFactor1 = fft.getSpectrum()[i];
        float _fftFactor2 = fft.getSpectrum()[i+1];
        
        float _y1 = baseArch.fassadeCorner[3].y - _yPos - _fftFactor1;
        float _y2 = baseArch.fassadeCorner[3].y - _yPos - _fftFactor2;
        float _x1 = baseArch.fassadeCorner[0].x + i * _w;
        float _x2 = baseArch.fassadeCorner[0].x + (i +1) * _w;
        
        ofDrawLine( _x1, _y1, _x2, _y2 );
    }
    
    ofPopStyle();
    

    
    ofPushStyle();
    
    ofSetColor(255);

    ofNoFill();
    
    for (int i = 0;i < nBandsToGet; i++){
        float _w = _width;
        
        float _fftFactor1 = fft.getSpectrum()[i];
        
        float _y1 = baseArch.fassadeCorner[3].y - _yPos - _fftFactor1;
        float _x1 = baseArch.fassadeCorner[0].x + i * _w;
        float _size = _fftFactor1;

        ofDrawCircle( _x1, _y1, _size );
        
        if (fft.getSpectrum()[i] > 0.25){
            float _length = ofMap( _size, 0, 200, 0, 800 );
            ofDrawLine( _x1, _y1, _length + _x1, _y1 );
        }
        
    }
    
    ofPopStyle();
    
    ofPopMatrix();
    

}


//--------------------------------------------------------------
void ofApp::lineCircleCaptureFFT(float _yPos){
    
    ofPushStyle();
    
    ofNoFill();

    int _index = 20;
    
    float _heightRatio = 1;
    float _width = (baseArch.fassadeCorner[1].x - baseArch.fassadeCorner[0].x) / _index;

    
    if(ofGetFrameNum()%captureTimer==0) {
        
        captureFFTSmoothed.clear();
        captureFFTIndex.clear();
        
        for(int i=0; i<_index; i++) {
            int _index = round(ofRandom(127));
            captureFFTIndex.push_back( _index );
            captureFFTSmoothed.push_back( fft.getSpectrum()[_index] );
        }
        
    } else {
        
        ofSetColor(255);
        
        for (int i = 0;i < _index-1; i++){
            float _w = _width;
            
            float _fftFactor1 = captureFFTSmoothed[ i ] * _heightRatio;
            float _fftFactor2 = captureFFTSmoothed[ i + 1 ] * _heightRatio;
            
            float _y1 = baseArch.fassadeCorner[3].y - _yPos - _fftFactor1;
            float _y2 = baseArch.fassadeCorner[3].y - _yPos - _fftFactor2;
            float _x1 = baseArch.fassadeCorner[0].x + i * _w;
            float _x2 = baseArch.fassadeCorner[0].x + (i +1) * _w;

            ofDrawLine( _x1, _y1, _x2, _y2 );
            
        }

        
        for (int i = 0;i < _index; i++){
            float _w = _width;
            
            float _fftFactor1 = captureFFTSmoothed[ i ] * _heightRatio;
            
            float _y1 = baseArch.fassadeCorner[3].y - _yPos - _fftFactor1;
            float _x1 = baseArch.fassadeCorner[0].x + i * _w;
            ofDrawCircle( _x1, _y1, 20 );


        }
        
        for (int i = 0;i < _index; i++){
            float _w = _width;
            float _fftFactor1 = captureFFTSmoothed[ i ] * _heightRatio;

            float _x1 = baseArch.fassadeCorner[0].x + i * _w;
            float _y1 = baseArch.fassadeCorner[3].y - _yPos - _fftFactor1;
            ofDrawBitmapString(captureFFTIndex[i], _x1, _y1);

            char _fqString = (char)( captureFFTIndex[i] );
            ofDrawBitmapString(_fqString, _x1, _y1);
        }
        
        
    }
    ofPopStyle();


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


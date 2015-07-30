#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){	 

    ofSetDataPathRoot("../Resources/data/");

    
    glassscherben.load("musics/glassscherben.mp3");
    spacefunk.load("musics/spacefunk.mp3");
    glassscherben.setLoop(true);
    spacefunk.setLoop(true);
    
    ofBackground( 10 );
    ofSetFrameRate( 60 );
    ofSetBackgroundAuto( false );
    
	
	fftSmoothed = new float[8192];
	for (int i = 0; i < 8192; i++){
		fftSmoothed[i] = 0;
	}
	
	nBandsToGet = 32;
    
    for(int i=0; i<10; i++) {
        int _index = round(ofRandom(127));
        captureFFTIndex.push_back( _index );
        captureFFTSmoothed.push_back( fftSmoothed[_index] );
    }
    
    
    gui.setup();
    gui.add(captureTimer.setup("Capture Frame", 50, 1, 120));
    gui.add(musicChange.setup("Music Change", false));

    
    musicChange.addListener(this, &ofApp::musicChangePressed);
    musicChangeIndex = 1;
    
    spacefunk.play();
    
    xPosition = 150;
    
    calliYShift = 0;
    calliIndex = -1;

}


//--------------------------------------------------------------
void ofApp::musicChangePressed(){
    
    musicChangeIndex++;
    musicChangeIndex = musicChangeIndex % 2;

    switch (musicChangeIndex) {
        case 0:
            glassscherben.play();
            spacefunk.stop();
            captureTimer = 9;
            break;

        case 1:
            glassscherben.stop();
            spacefunk.play();
            captureTimer = 15;
            break;

        default:
            break;
    }
    

}


//--------------------------------------------------------------
void ofApp::update(){
	
	ofSoundUpdate();
	
	float * val = ofSoundGetSpectrum(nBandsToGet);		// request 128 values for fft
	for (int i = 0;i < nBandsToGet; i++){
		fftSmoothed[i] *= 0.9f;
		if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
	}

    if(ofGetFrameNum()%captureTimer==0) {
        Calligraphy _eCalligraphy;
        _eCalligraphy.inputFftSmoothed(fftSmoothed);
        
        calligraphy.inputFftSmoothed(fftSmoothed);

        calligraphies.push_back(_eCalligraphy);
        calliIndex++;
        
        if (calligraphies.size()>0) {
            
            
            float _changedX = (calliIndex%3) * 100 + 950;
            float _changedY = calliYShift * 100 + 50;

            if ((calliIndex%3==0)&&bClliXPosChange==false) {
                calliYShift++;
                bClliXPosChange = true;
            }
            
            if (calliIndex%3==2){
                bClliXPosChange = false;
            }

            calliPos.push_back( ofVec3f(_changedX, _changedY, 0) );
            
        }

        if (calliIndex>21) {
            calligraphies.erase(calligraphies.begin());
            calliPos.erase(calliPos.begin());
            calliYShift = 0;
            calliIndex = 0;
        }
        

    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(0, 50);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    
    ofPushMatrix();
    ofTranslate(xPosition, 0);

    normalFFT();
    lineCircleFFT();
    
    lineCircleCaptureFFT();
    ofPopMatrix();
    

    
    for (int i=0; i<calligraphies.size(); i++) {
        calligraphies[i].drawCali( calliPos[i].x, calliPos[i].y );
    }
    
    
    calligraphy.drawCali(800, 300);
    
    gui.draw();
    
}


//--------------------------------------------------------------
void ofApp::exit(){
    
    ofSoundShutdown();
    
    glassscherben.unload();
    spacefunk.unload();
    fftSmoothed = NULL;
    
}


//--------------------------------------------------------------
void ofApp::normalFFT(float _yPos){
    
    ofPushStyle();
    ofSetColor(255, 120);
    ofNoFill();
    
    float _height = 100;
    float _widthStep = 20;
    
    for (int i = 0; i<nBandsToGet; i++){
        float _w = (float)(_widthStep * nBandsToGet) / nBandsToGet;
        float _h = -(fftSmoothed[i] * _height);
        float _x = 100 + i * _w;
        float _y = ofGetHeight() - _yPos;
        ofDrawRectangle( _x, _y, _w, _h );
    }
    
    ofPopStyle();

}


//--------------------------------------------------------------
void ofApp::lineCircleFFT(float _yPos){
    
    ofPushStyle();
    ofSetColor(255, 120);
    
    float _height = 100;
    float _xPos = 100;
    float _widthStep = 20;

    float _scaleUp = 5;

    for (int i = 0;i < nBandsToGet-1; i++){
        float _w = (float)(_widthStep * nBandsToGet) / nBandsToGet;
        
        float _fftFactor1 = fftSmoothed[i] * ofMap( i, 0, nBandsToGet-1, 1, _scaleUp );
        float _fftFactor2 = fftSmoothed[i+1] * ofMap( i+1, 0, nBandsToGet-1, 1, _scaleUp );
        
        float _h1 = ofGetHeight() - _yPos - (_fftFactor1 * _height);
        float _h2 = ofGetHeight() - _yPos - (_fftFactor2 * _height);
        float _x1 = _xPos + i * _w;
        float _x2 = _xPos + (i +1) * _w;
        ofDrawLine( _x1, _h1, _x2, _h2 );
    }
    
    ofPopStyle();
    
    ofPushStyle();
    ofSetColor(255, 120);

    ofNoFill();
    for (int i = 0;i < nBandsToGet; i++){
        float _w = (float)(_widthStep * nBandsToGet) / nBandsToGet;
        
        float _fftFactor1 = fftSmoothed[i] * ofMap( i, 0, nBandsToGet-1, 1, _scaleUp );
        
        float _h1 = ofGetHeight() - _yPos - (_fftFactor1 * _height);
        float _x1 = 100 + i * _w;
        float _size = _fftFactor1 * 50;
        ofDrawCircle( _x1, _h1, _size );
        
        if(fftSmoothed[i] > 0.25){
            float _length = ofMap( _size, 0, 200, 0, 800 );
            ofDrawLine( _x1, _h1, _length + _x1, _h1 );
        }
        
    }
    
    ofPopStyle();
    

}


//--------------------------------------------------------------
void ofApp::lineCircleCaptureFFT(float _yPos){
    
    
    ofPushStyle();
    
    ofNoFill();

    int _index = 10;

    float _height = 100;
    float _widthStep = 40;
    
    float _scaleUp = 0.3;

    if(ofGetFrameNum()%captureTimer==0) {
        captureFFTSmoothed.clear();
        captureFFTIndex.clear();
        for(int i=0; i<_index; i++) {
            int _index = round(ofRandom(127));
            captureFFTIndex.push_back( _index );
            captureFFTSmoothed.push_back( fftSmoothed[_index] );
        }
    } else {
        
        ofSetColor(255, 120);
        
        for (int i = 0;i < _index-1; i++){
            float _w = (float)(_widthStep * _index) / _index;
            
            float _fftFactor1 = pow(captureFFTSmoothed[ i ], _scaleUp);
            float _fftFactor2 = pow(captureFFTSmoothed[ i + 1 ], _scaleUp);
            
            float _h1 = ofGetHeight() -  _yPos - (_fftFactor1 * _height);
            float _h2 = ofGetHeight() -  _yPos - (_fftFactor2 * _height);
            
            float _x1 = 100 + i * _w;
            float _x2 = 100 + (i + 1) * _w;
            ofDrawLine( _x1, _h1, _x2, _h2 );
            
        }

        
        for (int i = 0;i < _index; i++){
            float _w = (float)(_widthStep * _index) / _index;
            
            float _fftFactor1 = pow(captureFFTSmoothed[ i ], _scaleUp);
            
            float _h1 = ofGetHeight() -  _yPos - (_fftFactor1 * _height);
            float _x1 = 100 + i * _w;
            float _size = _fftFactor1 * 20;
            ofDrawCircle( _x1, _h1, 20 );


        }
        
        for (int i = 0;i < _index; i++){
            float _w = (float)(_widthStep * _index) / _index;
            float _x1 = 100 + i * _w;
            ofDrawBitmapString(captureFFTIndex[i], _x1, ofGetHeight() - _yPos + 35);

            char _fqString = (char)( captureFFTIndex[i] );
            ofDrawBitmapString(_fqString, _x1, ofGetHeight() - _yPos + 50);
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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


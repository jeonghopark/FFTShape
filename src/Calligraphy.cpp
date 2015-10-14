//
//  Calligraphy.cpp
//  MusicFFT_score
//
//  Created by JeongHo Park on 09/07/15.
//
//

#include "Calligraphy.h"


//--------------------------------------------------------------
Calligraphy::Calligraphy(){
 
    calliSize = 20;
    calliYShift = -1;
    calliIndex = -1;
 
}



//--------------------------------------------------------------
Calligraphy::~Calligraphy(){
    
}


//--------------------------------------------------------------
void Calligraphy::setup(){
    
}


//--------------------------------------------------------------
void Calligraphy::inputFFTP(ProcessFFT & _processFFT){
    
    processFFT = & _processFFT;
    
}



//--------------------------------------------------------------
void Calligraphy::inputBaseArch(BaseArch & _baseArch){
    
    baseArch = & _baseArch;

}


//--------------------------------------------------------------
void Calligraphy::update(){

    if(ofGetFrameNum()%10==0) {
        inputFftSmoothed( processFFT->getSpectrum() );
    }
    
    
    if(ofGetFrameNum()%10==0) {
        
        Calligraphy _eCalligraphy;
        _eCalligraphy.inputFftSmoothed( processFFT->getSpectrum() );
        
        
        calligraphies.push_back(_eCalligraphy);
        
        if (calliIndex%22==0) calliYShift++;
        
        
        if (calligraphies.size()>0) {
            
            int _indexX = calliIndex % 22;
            int _indexY = calliYShift % 5;
            
            ofVec2f _changedPos = baseArch->windowsOriginCenter[_indexX][_indexY];
            calliPos.push_back( _changedPos );
            
        }
        
        if ((calliIndex!=0)&&(calliIndex%110==0)) {
            calliIndex = -1;
            calliYShift = -1;
        }
        
        if (calligraphies.size()>110) {
            calligraphies.erase(calligraphies.begin());
            calliPos.erase(calliPos.begin());
        }
        
        
        calliIndex++;
        
    }

}




//--------------------------------------------------------------
void Calligraphy::inputFftSmoothed(vector<float> _fft){
        
    captureFFTSmoothed.clear();
    captureFFTIndex.clear();

    captureFFTSmoothed.resize(calliSize);
    captureFFTIndex.resize(calliSize);
    
    for(int i=0; i<calliSize; i++) {

        int _index = round( ofRandom(60) );
        captureFFTIndex[i] = _index;
        captureFFTSmoothed[i] = _fft[_index];
    }
    
}


//--------------------------------------------------------------
void Calligraphy::drawElement(float _xPos, float _yPos, int _h){
    
    ofPushStyle();
    
    ofNoFill();
    
    ofBeginShape();
    
    for (int i=0; i<calliSize; i++){

        ofSetColor( 255 );
        ofSetColor( ofColor::fromHsb( _h, 255, 255) );

        
        float _fftFactor1 = ofMap(captureFFTSmoothed[i], 0, 1, 0, 25);
        float _x1 = captureFFTIndex[i];
        
        float _xCircle = cos( captureFFTIndex[i] * 36 / 127.0 ) * _fftFactor1;
        float _yCircle = sin( captureFFTIndex[i] * 36 / 127.0 ) * _fftFactor1;
        
        ofCurveVertex(_xCircle + _xPos, _yCircle + _yPos);
        
    }
    
    ofEndShape();
    
    
    
    ofPopStyle();
    
}


//--------------------------------------------------------------
void Calligraphy::draw(){
    
    drawElement( baseArch->framesCenter[11][5].x, baseArch->framesCenter[11][5].y, 255 );

    for (int i=0; i<calligraphies.size(); i++) {
        int _h = ofMap(i, 0, 110, 0, 255);

        calligraphies[i].drawElement( calliPos[i].x, calliPos[i].y, _h );
    }
    
}




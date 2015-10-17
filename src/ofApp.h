#pragma once

#include "ofMain.h"
#include "GuiApp.h"
#include "BaseArch.h"

#include "ofxGui.h"
#include "ofxProcessFFT.h"

#include "Calligraphy.h"


class ofApp : public ofBaseApp{
    
public:
    
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
    shared_ptr<GuiApp> gui;
    BaseArch baseArch;
    
    
    int nBandsToGet;
    
    vector<float> captureFFTSmoothed;
    vector<int> captureFFTIndex;

    Calligraphy calligraphy;

    ProcessFFT fft;
    
    float mainOffSetXPos, mainOffSetYPos;
    
};


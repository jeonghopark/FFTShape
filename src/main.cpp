#include "ofMain.h"
#include "ofApp.h"
#include "GuiApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
    
    
    ofGLFWWindowSettings settings;
    
    settings.width = 700;
    settings.height = 800;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = false;
    shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);
    
    settings.width = 1280;  // 1920
    settings.height = 720;  // 1080
    settings.resizable = true;
    settings.setPosition( ofVec2f(settings.width, 0 ));
    //    settings.windowMode = OF_FULLSCREEN;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    
    shared_ptr<GuiApp> guiApp(new GuiApp);
    shared_ptr<ofApp> mainApp(new ofApp);
    mainApp->gui = guiApp;
    
    ofRunApp(mainWindow, mainApp);
    ofRunApp(guiWindow, guiApp);
    ofRunMainLoop();
    
    
}

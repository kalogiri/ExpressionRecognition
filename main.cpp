#include "testApp.h"
#include "ofAppGlutWindow.h"

int main() {
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 600, 480, OF_WINDOW);
	ofRunApp(new testApp());
}

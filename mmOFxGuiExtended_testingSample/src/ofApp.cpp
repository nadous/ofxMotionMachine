/**
 *
 *  @file ofApp.cpp
 *  @brief MotionMachine source file for empty example
 *  @copyright Numediart Institute, UMONS (c) 2015
 *
 */

#include "ofApp.h"
#include "mmGeometry.h"

using namespace std;
using namespace arma;
using namespace MoMa;

void ofApp::setup(void)
{
    //Some noisy example (flat text file from kinect data)
    myTrack.load(getAbsoluteResPath() + "kinect2.nodes"); //load corresponding nodelist (it must have the same number of
                                                          //markers (or nodes) as in the raw data text file)
                                                          //Same as:
                                                          //myTrack.load(getAppPath() + "../../ExampleData/kinect2.nodes");

    myTrack.load(getAbsoluteResPath() + "kinect2.bones"); //load corresponding bonelist, describing the links between nodes,
    // i.e. the skeleton structure, used for drawing, and for local coordinate representation

    myTrack.load(getAbsoluteResPath() + "kinect2.txt"); //load raw data from a flat text file (one line = a frame; one
    //line has 3 x m values, 3 for x,y,z directions, and m for m markers (or nodes) )

    myTrack.setFrameRate(30); //This file is recorded from a kinect has thus a framerate around 30fps

    setFrameRate(myTrack.frameRate()); // Set the framerate of the application to the framerate of the track, so that it is played at the real speed
    setPlayerSize(myTrack.nOfFrames());
}

void ofApp::update(void)
{
    //---- We can also extract the current frame (at the current time of the application) to display it in the
    //3D scene (which is generally more useful...)

    myFrame = myTrack[getAppTime()];
}

void ofApp::scene3d(void)
{
    //in the 3D scene of the application


    //---- We translate the coordinate system of oF of 3m on x-axis
    ofPushMatrix();
    ofTranslate(3000, 0, 500);
    //"ofPushMatrix()" and "ofPopMatrix()" are beacons between with we can locally modify the coordinate system
    //with "ofTranslate(x,y,z)". This translation have no more effect on the code following "ofPopMatrix()".

    ofSetColor(0, 255, 0); //Set drawing color to green
    draw(myFrame);         //Draw myFrame, i.e. the frame at the running time of the application

    //---- We can also draw any openframeworks-like stuff. For instance, let's draw a line linking the pelvis and
    //the right hand

    // Node LHand = myTrack("RightHand")[getAppTime()]; //position data of the right hand at the current time of the
    // //application

    // Node Pelvis = myTrack("Pelvis")[getAppTime()]; //position data of the pelvis at the current time of the
    // //application

    // vec LHandPositionVector = LHand.position;
    // vec PelvisPositionVector = Pelvis.position;
    // ofSetColor(255, 0, 0);                                               //Set drawing color to red
    // ofLine(toVec3f(LHandPositionVector), toVec3f(PelvisPositionVector)); //draw a line between two points

    ofPopMatrix(); //End of the local coordinate system effect
}

void ofApp::scene2d(void)
{
    draw(COM);
}

void ofApp::annotate(void)
{
}

void ofApp::keyPressed(int key)
{
}

void ofApp::keyReleased(int key)
{
}

void ofApp::mousePressed(int x, int y, int button)
{
}

void ofApp::mouseReleased(int x, int y, int button)
{
}

void ofApp::mouseDragged(int x, int y, int button)
{
}

void ofApp::mouseMoved(int x, int y)
{
}

void ofApp::windowResized(int w, int h)
{
}

void ofApp::dragEvent(ofDragInfo dragInfo)
{
    COM = Geometry::centerOfMassTrace(myTrack);
}

void ofApp::gotMessage(ofMessage msg)
{
}

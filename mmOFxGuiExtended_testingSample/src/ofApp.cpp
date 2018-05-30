/**
 *
 *  @file ofApp.cpp
 *  @brief MotionMachine source file for empty example
 *  @copyright Numediart Institute, UMONS (c) 2015
 *
 */

#include "ofApp.h"

#include "mmGeometry.h"    //enables some geometry techniques (such as translation)
#include "mmKinematics.h"  //enables some kinematics techniques (such as speed computation)
#include "mmSignal.h"      //enables some signal processing techniques (such as filtering)

using namespace std;
using namespace arma;
using namespace MoMa;

void ofApp::setup(void) {
  //Some noisy example (flat text file from kinect data)
  myTrack.load(getAbsoluteResPath() + "kinect2.nodes");  //load corresponding nodelist (it must have the same number of
                                                         //markers (or nodes) as in the raw data text file)
                                                         //Same as:
                                                         //myTrack.load(getAppPath() + "../../ExampleData/kinect2.nodes");

  myTrack.load(getAbsoluteResPath() + "kinect2.bones");  //load corresponding bonelist, describing the links between nodes,
  // i.e. the skeleton structure, used for drawing, and for local coordinate representation

  myTrack.load(getAbsoluteResPath() + "kinect2.txt");  //load raw data from a flat text file (one line = a frame; one
  //line has 3 x m values, 3 for x,y,z directions, and m for m markers (or nodes) )

  myTrack.setFrameRate(30);  //This file is recorded from a kinect has thus a framerate around 30fps

  myFilteredTrack = meanfilter(myTrack, 5);  //a mean filter with a window of 5 frames (signal processing
  //functions are available if you include "mmSignal.h", see beginning oe the file)

  //------------------ Translate the tracks ------------------------------

  Geometry::translate(myTrack, 3000, -500, 700);  //Translate the track of 3000mm on x-axis, -500mm on y-axis,
  // and 700mm on z-axis(supposing the unit of the track data is mm)

  Geometry::translate(myFilteredTrack, 3000, 500, 700);  //Translate the track of 3000mm on x-axis, 500mm on y-axis,
  // and 700mm on z-axis(supposing the unit of the track data is mm)

  //-------------------------- Compute some features --------------------------------------

  mySpeed = normSpeed(myTrack("RightHand"));
  myFilteredSpeed = normSpeed(myFilteredTrack("RightHand"));
  //Note: by default, a five-point derivative is used for the speed computation

  //------------------------- Initialize 2D scene figures -----------------------------

  //We want to display three features separately, so we need three figures
  setNumOfFigures(2);

  setFrameRate(myTrack.frameRate());  // Set the framerate of the application to the framerate of the track, so that it is played at the real speed
  setPlayerSize(myTrack.nOfFrames());

  // register mouse event with a list of labels;
  registerMouseEvent(myLabels);
}

void ofApp::update(void) {
  //---- We can also extract the current frame (at the current time of the application) to display it in the
  //3D scene (which is generally more useful...)

  myFrame = myTrack[getAppTime()];
  myFilteredFrame = myFilteredTrack[getAppTime()];
  COM = Geometry::centerOfMassTrace(myTrack);
}

void ofApp::scene3d(void) {
  //in the 3D scene of the application

  //---- We translate the coordinate system of oF of 3m on x-axis
  //"ofPushMatrix()" and "ofPopMatrix()" are beacons between with we can locally modify the coordinate system
  //with "ofTranslate(x,y,z)". This translation have no more effect on the code following "ofPopMatrix()".

  ofSetColor(Green);
  draw(myFrame);
  ofSetColor(Blue);
  draw(myFilteredFrame);

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
}

void ofApp::scene2d(void) {
  draw(COM);  //Draw myFrame, i.e. the frame at the running time of the application

  figure(0);  //Activate the first figure for drawings
  draw(mySpeed, "Speed of unfiltered right hand");
  figure(1);  //Activate the second figure for drawings
  draw(myFilteredSpeed, "Speed of filtered right hand");
}

void ofApp::annotate(void) {
  draw(myLabels);
}

void ofApp::keyPressed(int key) {
}

void ofApp::keyReleased(int key) {
}

void ofApp::mousePressed(int x, int y, int button) {
}

void ofApp::mouseReleased(int x, int y, int button) {
}

void ofApp::mouseDragged(int x, int y, int button) {
}

void ofApp::mouseMoved(int x, int y) {
}

void ofApp::windowResized(int w, int h) {
}

void ofApp::dragEvent(ofDragInfo dragInfo) {
  COM = Geometry::centerOfMassTrace(myTrack);
}

void ofApp::gotMessage(ofMessage msg) {
}

/** PlayBar class
*
* Created by Micka�l Tits on 20/08/2015
*
*/

#ifndef __mmPlayBar__
#define __mmPlayBar__

/*namespace MoMa { 

    class PlayBar;
    //class Canvas;
}*/

#include "mmCanvas.h"

namespace MoMa {

//class SceneApp;
//class Canvas;

class PlayBar : public MoMa::Canvas {
 public:
  PlayBar(SceneApp* app,
          MoMa::Position position = DEFAULT,
          MoMa::Position alignment = MoMa::BOTTOM,
          MoMa::Canvas* parentUI = NULL,
          int group = 1,
          bool minified = false);

  void update();
  // void canvasEvent( ofxUIEventArgs &e );
  void initCanvas();
  void pause();

 protected:
  void play();
  void stop();
  void next();
  void prev();
  void speedUp();
  void speedDown();

  void scrub(bool& value);
  void reverse(bool& value);

  void timeChange(string& value);
  void timeSliderChange(float& value);

  void timeSpeedChange(float& value);

  ofParameter<float> timeSpeedParam, timeSliderParam;
  ofParameter<string> timeParam;
  ofParameter<bool> scrubParam;

  ofxGuiButton* playButton;
  ofxGuiToggle* reverseButton;
//   ofxGuiFloatSlider* timSlider;
  //ofxUIImageToggle *bt_play, *bt_pause;
  //   ofxUIImageToggle* bt_scrub;
  //   ofxUIImageButton *bt_play, *bt_stop, *bt_nextFrame, *bt_prevFrame, *bt_nextSpeed, *bt_prevSpeed;
  bool playingState, enteringFrame, enteringSpeed;
  //   ofxUITextArea *txt_index, *txt_time, *textarea;
  //   ofxUILabel* textlabel;
  //   ofxUITextInput *timeinput, *speedinput;
  //   ofxUIMinimalSlider* timeslider;  // , *frslider;
  //   string libPath;
  bool enteringSpeed;
  bool isNext, isPrev, nextspeed, prevspeed;
  double mywidth;
};
}  // namespace MoMa

#endif
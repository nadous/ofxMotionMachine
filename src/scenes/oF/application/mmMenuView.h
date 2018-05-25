/** FiguresView class
*
* Created by Micka�l Tits on 28/07/2015
*
*/

#ifndef __mmMenuView__
#define __mmMenuView__

/*namespace MoMa { 

    class MenuView;
    //class Canvas;
}*/

#include "mmCanvas.h"

namespace MoMa {

//class SceneApp;
//class Canvas;

class MenuView : public MoMa::Canvas {
 public:
  MenuView(SceneApp* app,
           MoMa::Position position = DEFAULT,
           MoMa::Position alignment = MoMa::DEFAULT,
           MoMa::Canvas* parentUI = NULL,
           bool minified = false);

  void update();
  void canvasEvent(ofEventArgs& e);
  void reopenOtherCanvas();
  void closeOtherCanvas();

 protected:
  ofParameterGroup focusModeGroup;
  unsigned short activeFocusMode = 0;
  void modeToggle(bool& value);
  void modeChange(const string& name);

  ofParameterGroup viewOptionsGroup;
  void viewOptionsChange(bool& value);

  //   ofParameter<bool> playbarParam;
  //   ofxGuiToggle* playBar;

  //   ofParameter<bool> viewOptionsParam;
  //   ofxGuiToggle* viewOptions;

  //   ofParameter<bool> hideAllParam;
  //   ofxGuiToggle* hideAll;
};
}  // namespace MoMa

#endif
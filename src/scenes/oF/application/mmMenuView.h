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
  void focusModeToggle(bool& value);
  void focusModeChange(const string& name);

  ofParameterGroup uiOptionsGroup;
  void uiVisibilityChange(bool& value);
};
}  // namespace MoMa

#endif
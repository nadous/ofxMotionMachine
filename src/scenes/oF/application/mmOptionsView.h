/** OptionsView class
*
* Created by Micka�l Tits on 02/09/2015
*
*/

#ifndef __mmOptionsView__
#define __mmOptionsView__

/*namespace MoMa { 

    class Options;
    //class Canvas;
}*/

#include "mmCanvas.h"

namespace MoMa {

//class SceneApp;
//class Canvas;

class Options : public MoMa::Canvas {
 public:
  Options(SceneApp* app, MoMa::Position position = DEFAULT, MoMa::Position alignment = MoMa::DEFAULT, MoMa::Canvas* parentUI = NULL, int group = 0, bool minified = false);

  void update();
//   void canvasEvent(ofxUIEventArgs& e);
  //void initCanvas();

 protected:
  ofParameterGroup viewOptionsGroup;
  void viewOptionsChange(bool& value);
  ofxGuiToggle *toggle3DScene, *toggleGround, *toggleNodeNames, *toggleAnnotations, *toggleFigure, *toggleCaption, *toggleTimeline, *toggleShortcuts;
};
}  // namespace MoMa

#endif
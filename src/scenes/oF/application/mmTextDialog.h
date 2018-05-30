/** PlayBar class
*
* Created by Micka�l Tits on 20/08/2015
*
*/

#ifndef __mmTextDialog__
#define __mmTextDialog__

#include "mmCanvas.h"

namespace MoMa {

class TextDialog : public MoMa::Canvas {
 public:
  TextDialog(SceneApp* app);

  // void canvasEvent(ofEventArgs& e);
  void initCanvas();
  ofParameter<string> txtInput;

 protected:
  void inputConfirm();
  void inputCancel();
  // ofxTextField* txtInput;
};

}  // namespace MoMa
#endif
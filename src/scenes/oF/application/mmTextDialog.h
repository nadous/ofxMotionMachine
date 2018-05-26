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
  std::string getText();
  void set(std::string& value);
  void setOff();
  void initCanvas();

 protected:
  std::string* text;
  std::string oldtext;
  bool isTextEntered;

  ofParameter<string> txtInput;

  void inputChange(std::string& value);

  void inputConfirm();
  void inputCancel();
  // ofxTextField* txtInput;
};

}  // namespace MoMa
#endif
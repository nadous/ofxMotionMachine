/** Canvas : Basic UI canvas specific to the MoMa.
*    Canvas heritates from ofxUISuperCanvas.
*    Specific functionnalities :
*        - automatically handle MoMa views management
*        - handle canvas positions (automatically and manually)
*        - automatically manage children canvas
*        - adapted parameters relative to the MoMa.
*    Constructor :
*           MoMa::SceneApp *app : pointer to the current scene application, used to interact with it
*           std::string title = "" : title of the ofxUISuperCanvas
*       Optional options (positioning and parent/children hierarchy) :
*           Position position = DEFAULT : position of the canvas, relative to another canvas (the relative), or to the main ofWindow (if relative = NULL)
*           Position alignment = DEFAULT : alignment of the canvas with the relative (defines which edges of the rectangles are aligned)
*           Canvas *relative = NULL : relative canvas (for position)
*           Canvas *parent = NULL : parent canvas (the parent can open/close its children canvas)
*           int group = 1 : (begins at 1) a parent may have several groups of children. group defines in which group add the child 
*           bool minified = false : minify or not the canvas at its construction
*
* Created by Micka�l Tits on 03/07/2015
* @file mmCanvas.h
* @brief MotionMachine header file for Canvas class.
* @copyright Numediart Institute, UMONS (c) 2014-2015
*
*/

#ifndef __mmCanvas__
#define __mmCanvas__

/*namespace MoMa { 

    class Canvas;
}*/

#include "mmSceneApp.h"
#include "ofMain.h"
#include "ofxGuiExtended.h"

namespace MoMa {

enum Position {
  DEFAULT,
  LEFT,
  RIGHT,
  ABOVE,
  BELOW,
  LEFTSIDE,
  RIGHTSIDE,
  TOP,
  BOTTOM
};

//class SceneApp;

class Canvas {
  ofEvent<string> radioChange;

 public:
  enum Type { Container,
              Group,
              Panel };

  Canvas(SceneApp* app,
         const std::string& title,
         const Type& type,
         Position position = DEFAULT,
         Position alignment = DEFAULT,
         Canvas* relative = NULL,
         Canvas* parent = NULL,
         int group = 1,
         bool minified = false);

  Canvas(SceneApp* app,
         const std::string& title,
         const Type& type,
         Canvas* parent,
         int group = 1,
         bool minified = false);

  ~Canvas();

  /** setPos : set position of the canvas relative to another */
  void setPos(Position position, Position alignment, Canvas* relative = NULL);
  void remove();

  /** resetPositions (static) : reset positions of the main canvas */
  static void resetPositions();

  /** deleteCanvas (static) : delete all canvas */
  static void deleteCanvas();

  static void openMainCanvas();
  static bool canvasOpened();
  std::vector<Canvas*>& getAllCanvas();
  std::vector<std::vector<Canvas*>>& getChildren();
  static void closeMainCanvas();
  static void closeAllCanvas();
  static void reopenCanvas();

  void setMinified(bool value);
  void setVisible(bool value);
  bool isVisible();

  /** ofxGui updates. **/
  ofxGui gui;
  ofxGuiContainer* _container;

 protected:
  /** _app : pointer to the application, needed to interact with it */
  SceneApp* _app;

  /** virtual methods of ofxUISuperCanvas */
  virtual void update();

  /** Canvas parameters (position and alignment relative to the parent, index in the vector of Canvass, and is the canvas minified at initialization) */
  Canvas *_relative, *_parent;
  Position _position, _alignment;
  static std::vector<MoMa::Canvas*> closedCanvas;

  const Type _type;

  int _index, _group, _allIndex;
  bool _minified;

  /** setupCanvas : setup the canvas */
  void setupCanvas(const std::string& title);

  /** initCanvas : initialize the canvas (size, position and minified) */
  virtual void initCanvas();

  /** methods to open and close canvas */
  void openChildren(int group = 0);
  void openChild(int index, int group = 0);
  void closeChildren(void);
  void closeChildren(int groupe);
  bool childrenOpened(int group = 0);

  /** close all canvas exept main canvas */
  static void mainView();

 private:
  /** Static vector storing addresses of main canvas */
  static std::vector<Canvas*> mainCanvas;

  /** Static vector storing addresses of all canvas */
  static std::vector<Canvas*> allCanvas;

  /** vector of vector storing addresses of children canvas (one vector for each group) */
  std::vector<std::vector<Canvas*>> childrenCanvas;

  bool _isInitialized, _isShortCutDisabled;
  static int _limit;
  int savedMode;
};
}  // namespace MoMa

#endif

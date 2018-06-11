#include "mmOptionsView.h"

using namespace MoMa;

Options::Options(SceneApp* app,
                 MoMa::Position position,
                 MoMa::Position alignment,
                 MoMa::Canvas* parentUI,
                 int group,
                 bool minified) : Canvas(app, "Options", MoMa::Canvas::Type::Group, position, alignment, NULL, parentUI, group, minified) {
  optionsGroup.setName("UI visibility");
  optionsGroup.add(_app->is3dScene);
  optionsGroup.add(_app->isGround);
  optionsGroup.add(_app->isNodeNames);
  optionsGroup.add(_app->isAnnotation);
  optionsGroup.add(_app->isFigure);
  optionsGroup.add(_app->isCaptions);
  optionsGroup.add(_app->isTimeline);
  optionsGroup.add(_app->shortcutDisplayed);

  _container->add(optionsGroup);

  setVisible(false);
  initCanvas();
}

void Options::update() {
  optionsGroup.getBool("Show 3D Scene").set(_app->is3dScene);
  optionsGroup.getBool("Show 3D Ground").set(_app->isGround);
  optionsGroup.getBool("Show Node Names").set(_app->isNodeNames);
  optionsGroup.getBool("Show Annotations").set(_app->isAnnotation);
  optionsGroup.getBool("Show 2D Figures").set(_app->isFigure);
  optionsGroup.getBool("Show Captions").set(_app->isCaptions);
  optionsGroup.getBool("Show Timeline").set(_app->isTimeline);
  optionsGroup.getBool("Show Shortcuts").set(_app->shortcutDisplayed);
}
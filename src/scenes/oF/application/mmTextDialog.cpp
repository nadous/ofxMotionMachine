#include "mmTextDialog.h"

using namespace MoMa;
using namespace std;

TextDialog::TextDialog(SceneApp* app) : Canvas(app, "Text Dialog", MoMa::Canvas::Type::Container, NULL) {
  gui.setupFlexBoxLayout();
  container->addSpacer(0, 10);

  ofxGuiGroup* root = container->addGroup("root", ofJson({{"width", "100%"},
                                                          {"show-header", false}}));

  ofxGuiGroup* header = root->addGroup("header", ofJson({{"flex-direction", "row"},
                                                         {"width", "100%"},
                                                         {"show-header", false}}));
  ofParameter<string> txtInput;
  txtInput.set("text");
  txtInput.addListener(this, &TextDialog::inputChange);
  header->add<ofxGuiTextField>(txtInput, ofJson({{"width", "100%"}}));

  ofxGuiGroup* form = root->addGroup("form", ofJson({{"flex-direction", "row"},
                                                     {"width", "50%"},
                                                     {"padding", 0},
                                                     {"align-self", "flex-end"},
                                                     {"background-color", "transparent"},
                                                     {"show-header", false}}));

  ofJson submitStyle = ofJson({{"type", "fullsize"},
                               {"text-align", "right"},
                               {"padding", "5 10 5 8"}});

  ofParameter<void> okParam, cancelParam;
  form->add<ofxGuiButton>(okParam.set("OK"), submitStyle);
  okParam.addListener(this, &TextDialog::inputConfirm);

  form->add<ofxGuiButton>(cancelParam.set("cancel"), submitStyle);
  cancelParam.addListener(this, &TextDialog::inputCancel);

  // txtInput = addTextInput("Text Input", "", OFX_UI_FONT_SMALL);

  // addButton("OK", false);
  // addButton("Cancel", false);
  // setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);

  text = NULL;

  initCanvas();
}

void TextDialog::initCanvas() {
  // autoSizeToFitWidgets();
  setVisible(false);
  setMinified(false);
  container->setPosition(round(ofGetWidth() * .5f - container->getWidth() * .5f),
                         round(ofGetHeight() * .5f - container->getHeight() * .5f));
}

string TextDialog::getText() {
  return txtInput;
}

void TextDialog::set(string& value) {
  setVisible(true);
  text = &value;
  oldtext = *text;
  *text = "";
  txtInput.set(*text);
  // txtInput->setTextString(*text);
  // txtInput->setFocus(true);
}

void TextDialog::setOff() {
  setVisible(false);
  text = NULL;
}

void TextDialog::inputChange(std::string& value) { *text = value; }

void TextDialog::inputConfirm() { setOff(); }
void TextDialog::inputCancel() {
  isTextEntered = false;
  *text = oldtext;
  setOff();
}
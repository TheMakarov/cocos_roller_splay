#ifndef INTRO_H_
#define INTRO_H_
#include "cocos2d.h"
#include "ui/UIButton.h"

class Intro_scene : public cocos2d::Scene
{
public:
  cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
  cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
  static Scene* createScene();
  virtual bool init();
  CREATE_FUNC(Intro_scene);
};


#endif // MENU_H_

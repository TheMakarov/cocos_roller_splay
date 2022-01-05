#ifndef MENU_H_
#define MENU_H_
#include "cocos2d.h"
#include"Scene1.h"
#include "ui/UIButton.h"

class Menu_scene : public cocos2d::Scene
{
public:
  cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
  cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
  static Scene* createScene();
  virtual bool init();
  CREATE_FUNC(Menu_scene);
};


#endif // MENU_H_

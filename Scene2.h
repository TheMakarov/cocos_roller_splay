#ifndef SCENE_2_H_
#define SCENE_2_H_
#include "cocos2d.h"
#include "Scene3.h"
#include "Menu_scene.h"
#include "ui/UIButton.h"
#include <vector>


class Scene2 : public cocos2d::Scene
{
public:
  // members
  std::vector <cocos2d::Sprite* > floor;

  cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
  cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

  bool done = true;
  // Methods

  static Scene* createScene();

  void move_sound();

  virtual bool init();

  void CheckGoals(float x, float y);

  void make_path();

  void  return_floor(int, int );

  void draw_succes();


  bool legalMove_scene(float, float);

  int moveto_scene(int );

  void checkGoals();

  CREATE_FUNC(Scene2);
};


#endif // SCENE3_H_

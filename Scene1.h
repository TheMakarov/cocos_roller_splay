#ifndef SCENE_1_H_
#define SCENE_1_H_
#include "ui/UIButton.h"
#include "cocos2d.h"
#include "Scene2.h"
#include <vector>


class Scene1 : public cocos2d::Scene
{
public:
  // members <------ -------->
  // tarjectory map
  std::vector <cocos2d::Sprite* > floor;

  // testing purposes

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

  CREATE_FUNC(Scene1);
};


#endif // SCENE3_H_

#ifndef SCENE_H
#define SCENE_H

typedef struct t_Scene {
  unsigned int id;
  void (*init)();
  void (*destroy)();
  void (*enter)();
  void (*exit)();
  void (*update)(float dt);
  void (*render)();
} Scene;

typedef struct t_SceneStackNode {
  unsigned int id;
  Scene* scene;
  struct t_SceneStackNode* next;
} SceneStackNode;

typedef struct t_SceneStack {
  SceneStackNode* top;
  int numScenes;
} SceneStack;

extern SceneStack* sceneStackPtr;

extern void scene_stack_init();
extern void scene_stack_destroy();
extern void scene_stack_push(Scene* scene);
extern Scene* scene_stack_pop();
extern Scene* scene_stack_top();

extern void scene_stack_update(float dt);
extern void scene_stack_render();

#endif

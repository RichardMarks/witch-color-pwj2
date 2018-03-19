#ifndef SCENES_H
#define SCENES_H

#include "scene.h"

extern void init_title_scene();
extern void destroy_title_scene();
extern void enter_title_scene();
extern void exit_title_scene();
extern void update_title_scene(float dt);
extern void render_title_scene();

extern void init_play_scene();
extern void destroy_play_scene();
extern void enter_play_scene();
extern void exit_play_scene();
extern void update_play_scene(float dt);
extern void render_play_scene();

extern void init_credits_scene();
extern void destroy_credits_scene();
extern void enter_credits_scene();
extern void exit_credits_scene();
extern void update_credits_scene(float dt);
extern void render_credits_scene();

extern Scene* currentScenePtr;

#endif

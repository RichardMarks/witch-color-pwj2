#ifndef SPRITE_H
#define SPRITE_H

#define SPRITE_VISIBLE 0x00
#define SPRITE_HIDDEN 0xFF

typedef struct t_Sprite {
  float x;
  float y;
  float xv;
  float yv;
  void* data;
  int state;
  SDL_Texture* texture;
  SDL_Texture* texture2;
  SDL_Rect src;
  unsigned char visible;
  int layer;
  int frame;
} Sprite;

extern Sprite* Sprite__init(Sprite* sprite, SDL_Texture* texture, SDL_Rect* src, int layer);
extern void Sprite__render(Sprite* sprite);
extern int Sprite__collides_with_point(Sprite* sprite, int x, int y);
extern void Sprite__change_texture(Sprite* sprite, SDL_Texture* texture, SDL_Rect* src);

#endif

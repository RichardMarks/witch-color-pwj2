#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

typedef struct t_Text {
  // render properties
  char* text;
  unsigned int color;
  // properties
  TTF_Font* font;
  SDL_Texture* texture;

  int width;
  int height;

  float pivotX;
  float pivotY;
  float scaleX;
  float scaleY;

  SDL_Rect src;
  SDL_Rect pvt;
  SDL_Rect dst;
  // TextRenderProperties* renderProperties;
  // TextProperties* properties;
  int x;
  int y;
  void* allocation;
} Text;

extern Text* Text__create(TTF_Font* font, unsigned int color);
extern Text* Text__init(Text* ptr, TTF_Font* font, unsigned int color);
extern void Text__destroy(Text* ptr);
extern void Text__set_text(Text* ptr, char* text);
extern void Text__set_color(Text* ptr, unsigned int color);
extern void Text__set_pivot(Text* ptr, float x, float y);
extern void Text__set_scale(Text* ptr, float x, float y);
extern void Text__set_scale_x(Text* ptr, float scale);
extern void Text__set_scale_y(Text* ptr, float scale);
extern void Text__render(Text* ptr);
extern int Text__contains_point(Text* ptr, int x, int y);
extern int Text__get_width(Text* ptr);
extern int Text__get_height(Text* ptr);
extern char* Text__get_text(Text* ptr);
extern unsigned int Text__get_color(Text* ptr);
extern void Text__get_pivot(Text* ptr, float* x, float* y);
extern void Text__get_scale(Text* ptr, float* x, float* y);
extern float Text__get_scale_x(Text* ptr);
extern float Text__get_scale_y(Text* ptr);

#endif

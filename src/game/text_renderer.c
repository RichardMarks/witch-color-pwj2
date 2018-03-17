#include "game.h"
#include "text_renderer.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

void PRIVATE__Text__update_pivot(Text* ptr);
void PRIVATE__Text__render_text(Text* ptr);
void PRIVATE__Text__release_cached_texture(Text* ptr);

Text* Text__create(TTF_Font* font, unsigned int color) {
  Text* ptr = malloc(sizeof(Text));
  ptr->renderProperties = malloc(sizeof(TextRenderProperties));
  ptr->properties = malloc(sizeof(TextProperties));

  memset(ptr, 0, sizeof(Text));
  memset(ptr->renderProperties, 0, sizeof(TextRenderProperties));
  memset(ptr->properties, 0, sizeof(TextProperties));

  Text__init(ptr, font, color);

  ptr->allocation = ptr;

  return ptr;
}

void Text__destroy(Text* ptr) {
  if (ptr && ptr->allocation) {
    if (ptr->properties->texture) {
      SDL_DestroyTexture(ptr->properties->texture);
    }
    free(ptr->properties);
    free(ptr->renderProperties);
    free(ptr);
    ptr = 0;
  }
}

void Text__init(Text* ptr, TTF_Font* font, unsigned int color) {
  if (ptr) {
    ptr->properties->font = font;
    ptr->renderProperties->color = color;

    ptr->properties->src.x = 0;
    ptr->properties->src.y = 0;

    ptr->x = 0;
    ptr->y = 0;

    ptr->properties->scaleX = 1.0f;
    ptr->properties->scaleY = 1.0f;

    ptr->properties->pivotX = 0.5f;
    ptr->properties->pivotY = 0.5f;
  }
}

void Text__set_text(Text* ptr, char* text) {
  if (strcmp(text, ptr->renderProperties->text) != 0) {
    PRIVATE__Text__release_cached_texture(ptr);
    ptr->renderProperties->text = text;
    PRIVATE__Text__render_text(ptr);
  }
}

void Text__set_color(Text* ptr, unsigned int color) {
  if (color != ptr->renderProperties->color) {
    PRIVATE__Text__release_cached_texture(ptr);
    ptr->renderProperties->color = color;
    PRIVATE__Text__render_text(ptr);
  }
}

void Text__set_pivot(Text* ptr, float x, float y) {
  if (
    (int)(x * 10) != (int)(ptr->properties->pivotX * 10) ||
    (int)(y * 10) != (int)(ptr->properties->pivotY * 10)) {
    ptr->properties->pivotX = x;
    ptr->properties->pivotY = y;
    PRIVATE__Text__update_pivot(ptr);
  }
}

void Text__set_scale(Text* ptr, float x, float y) {
  if (
    (int)(x * 10) != (int)(ptr->properties->scaleX * 10) ||
    (int)(y * 10) != (int)(ptr->properties->scaleY * 10)) {
    ptr->properties->scaleX = x;
    ptr->properties->scaleY = y;
    PRIVATE__Text__update_pivot(ptr);
  }
}

void Text__set_scale_x(Text* ptr, float scale) {
  if (
    (int)(scale * 10) != (int)(ptr->properties->scaleX * 10)) {
    ptr->properties->scaleX = scale;
    PRIVATE__Text__update_pivot(ptr);
  }
}

void Text__set_scale_y(Text* ptr, float scale) {
  if (
    (int)(scale * 10) != (int)(ptr->properties->scaleY * 10)) {
    ptr->properties->scaleY = scale;
    PRIVATE__Text__update_pivot(ptr);
  }
}

void Text__render(Text* ptr) {
  SDL_Texture* texture = ptr->properties->texture;

  if (texture && (ptr->renderProperties->color >> 24 & 255) > 0) {
    SDL_Rect* src = &ptr->properties->src;
    SDL_Rect* dst = &ptr->properties->dst;
    SDL_Rect* pvt = &ptr->properties->pvt;

    dst->x = ptr->x + pvt->x;
    dst->y = ptr->y + pvt->y;

    SDL_RenderCopy(mainRendererPtr, texture, src, dst);
  }
}

int Text__contains_point(Text* ptr, int x, int y) {
  SDL_Rect* dst = &ptr->properties->dst;
  if (x >= dst->x && x <= dst->x + dst->w && y >= dst->y && y <= dst->y + dst->h) {
    return 1;
  }
  return 0;
}

int Text__get_width(Text* ptr) {
  return ptr->properties->dst.w;
}

int Text__get_height(Text* ptr) {
  return ptr->properties->dst.h;
}

char* Text__get_text(Text* ptr) {
  return ptr->renderProperties->text;
}

unsigned int Text__get_color(Text* ptr) {
  return ptr->renderProperties->color;
}

void Text__get_pivot(Text* ptr, float* x, float* y) {
  *x = ptr->properties->pivotX;
  *y = ptr->properties->pivotY;
}

void Text__get_scale(Text* ptr, float* x, float* y) {
  *x = ptr->properties->scaleX;
  *y = ptr->properties->scaleY;
}

float Text__get_scale_x(Text* ptr) {
  return ptr->properties->scaleX;
}

float Text__get_scale_y(Text* ptr) {
  return ptr->properties->scaleY;
}

void PRIVATE__Text__update_pivot(Text* ptr) {
  if (ptr) {
    ptr->properties->pvt.w = ptr->properties->width;
    ptr->properties->pvt.h = ptr->properties->height;

    float textWidth = (float)ptr->properties->width * ptr->properties->scaleX;
    float textHeight = (float)ptr->properties->height * ptr->properties->scaleY;

    ptr->properties->pvt.x = (int)(ptr->properties->pivotX * -textWidth);
    ptr->properties->pvt.y = (int)(ptr->properties->pivotY * -textHeight);

    ptr->properties->dst.w = (int)textWidth;
    ptr->properties->dst.h = (int)textHeight;
  }
}

SDL_Color privateRenderTextColor;
void PRIVATE__Text__render_text(Text* ptr) {
  if (ptr) {
    TTF_Font* font = ptr->properties->font;
    char* text = ptr->renderProperties->text;
    unsigned int color32 = ptr->renderProperties->color;

    privateRenderTextColor.r = color32 >> 16 & 255;
    privateRenderTextColor.g = color32 >> 8 & 255;
    privateRenderTextColor.b = color32 & 255;
    privateRenderTextColor.a = color32 >> 24 & 255;

    SDL_Surface* temporarySurface = TTF_RenderUTF8_Blended(font, text, privateRenderTextColor);

    SDL_SetSurfaceAlphaMod(temporarySurface, privateRenderTextColor.a);

    ptr->properties->width = temporarySurface->w;
    ptr->properties->height = temporarySurface->h;
    ptr->properties->src.w = temporarySurface->w;
    ptr->properties->src.h = temporarySurface->h;

    ptr->properties->texture = SDL_CreateTextureFromSurface(mainRendererPtr, temporarySurface);

    SDL_FreeSurface(temporarySurface);

    if (
      ptr->properties->pvt.w != ptr->properties->width ||
      ptr->properties->pvt.h != ptr->properties->height) {
      PRIVATE__Text__update_pivot(ptr);
    }
  }
}

void PRIVATE__Text__release_cached_texture(Text* ptr) {
  if (ptr) {
    if (ptr->properties->texture) {
      SDL_DestroyTexture(ptr->properties->texture);
      ptr->properties->texture = 0;
    }
  }
}

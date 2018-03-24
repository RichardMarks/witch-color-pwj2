#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "game.h"
#include "text_renderer.h"

void PRIVATE__Text__update_pivot(Text* ptr);
void PRIVATE__Text__render_text(Text* ptr);
void PRIVATE__Text__release_cached_texture(Text* ptr);

Text* Text__create(TTF_Font* font, unsigned int color) {
  // printf("malloc ptr\n");
  Text* ptr = (Text*)malloc(sizeof(*ptr));
  if (!ptr) {
    // printf("unable to malloc ptr!\n");
    return 0;
  }

  // printf("memset ptr\n");
  memset(ptr, 0, sizeof(*(ptr)));

  // printf("init ptr\n");
  Text__init(ptr, font, color);

  ptr->allocation = ptr;

  return ptr;
}

void Text__destroy(Text* ptr) {
  if (ptr && ptr->allocation) {
    if (ptr->texture) {
      SDL_DestroyTexture(ptr->texture);
    }
    if (ptr->text) {
      free(ptr->text);
    }
    free(ptr);
    ptr = 0;
  }
}

Text* Text__init(Text* ptr, TTF_Font* font, unsigned int color) {
  if (ptr) {
    // printf("setting font\n");
    ptr->font = font;
    // printf("setting color\n");
    ptr->color = color;

    // printf("setting src xy\n");
    ptr->src.x = 0;
    ptr->src.y = 0;

    // printf("setting pos xy\n");
    ptr->x = 0;
    ptr->y = 0;

    // printf("setting scale xy\n");
    ptr->scaleX = 1.0f;
    ptr->scaleY = 1.0f;

    // printf("setting pivot xy\n");
    ptr->pivotX = 0.5f;
    ptr->pivotY = 0.5f;

    ptr->text = (char*)malloc(sizeof(char) * 1);
    ptr->text[0] = '\0';
  }
  return ptr;
}

void Text__set_text(Text* ptr, char* text) {
  // printf("setting text to \"%s\"\n", text);
  PRIVATE__Text__release_cached_texture(ptr);
  int len = 0; char* s = text; while (*s) { s += 1; len += 1; }
  if (len == 0) {
    // text is an empty string
    if (ptr->text) {
      free(ptr->text);
      ptr->text = 0;
    }
  } else {
    // have a string to set
    if (ptr->text) {
      if (strcmp(ptr->text, text) != 0) {
        // new text
        // same length?
        int len2 = 0; char* s2 = ptr->text; while (*s2) { s2 += 1; len2 += 1; }
        if (len2 == len) {
          // enough space, so just copy over
          s2 = ptr->text;
          for (int i = 0; i < len2 - 1; i += 1) {
            ptr->text[i] = 32;
          }
          ptr->text[len2] = '\0';
          strcpy(ptr->text, text);
        } else {
          // not enough space, so realloc enough space and copy
          ptr->text = (char*)realloc(ptr->text, sizeof(char) * (1 + len));
          strcpy(ptr->text, text);
        }
      } else {
        // same text do nothing
      }
    } else {
      // no current text
      ptr->text = (char*)malloc(sizeof(char) * (1 + len));
      strcpy(ptr->text, text);
    }
  }
  PRIVATE__Text__render_text(ptr);
}

void Text__set_color(Text* ptr, unsigned int color) {
  if (color != ptr->color) {
    PRIVATE__Text__release_cached_texture(ptr);
    ptr->color = color;
    PRIVATE__Text__render_text(ptr);
  }
}

void Text__set_pivot(Text* ptr, float x, float y) {
  if (
    (int)(x * 10) != (int)(ptr->pivotX * 10) ||
    (int)(y * 10) != (int)(ptr->pivotY * 10)) {
    ptr->pivotX = x;
    ptr->pivotY = y;
    PRIVATE__Text__update_pivot(ptr);
  }
}

void Text__set_scale(Text* ptr, float x, float y) {
  if (
    (int)(x * 10) != (int)(ptr->scaleX * 10) ||
    (int)(y * 10) != (int)(ptr->scaleY * 10)) {
    ptr->scaleX = x;
    ptr->scaleY = y;
    PRIVATE__Text__update_pivot(ptr);
  }
}

void Text__set_scale_x(Text* ptr, float scale) {
  if (
    (int)(scale * 10) != (int)(ptr->scaleX * 10)) {
    ptr->scaleX = scale;
    PRIVATE__Text__update_pivot(ptr);
  }
}

void Text__set_scale_y(Text* ptr, float scale) {
  if (
    (int)(scale * 10) != (int)(ptr->scaleY * 10)) {
    ptr->scaleY = scale;
    PRIVATE__Text__update_pivot(ptr);
  }
}

void Text__render(Text* ptr) {
  SDL_Texture* texture = ptr->texture;

  if (texture && (ptr->color >> 24 & 255) > 0) {
    SDL_Rect* src = &ptr->src;
    SDL_Rect* dst = &ptr->dst;
    SDL_Rect* pvt = &ptr->pvt;

    dst->x = ptr->x + pvt->x;
    dst->y = ptr->y + pvt->y;

    SDL_RenderCopy(mainRendererPtr, texture, src, dst);
  }
}

int Text__contains_point(Text* ptr, int x, int y) {
  SDL_Rect* dst = &ptr->dst;
  if (x >= dst->x && x <= dst->x + dst->w && y >= dst->y && y <= dst->y + dst->h) {
    return 1;
  }
  return 0;
}

int Text__get_width(Text* ptr) {
  return ptr->dst.w;
}

int Text__get_height(Text* ptr) {
  return ptr->dst.h;
}

char* Text__get_text(Text* ptr) {
  return ptr->text;
}

unsigned int Text__get_color(Text* ptr) {
  return ptr->color;
}

void Text__get_pivot(Text* ptr, float* x, float* y) {
  *x = ptr->pivotX;
  *y = ptr->pivotY;
}

void Text__get_scale(Text* ptr, float* x, float* y) {
  *x = ptr->scaleX;
  *y = ptr->scaleY;
}

float Text__get_scale_x(Text* ptr) {
  return ptr->scaleX;
}

float Text__get_scale_y(Text* ptr) {
  return ptr->scaleY;
}

void PRIVATE__Text__update_pivot(Text* ptr) {
  if (ptr) {
    ptr->pvt.w = ptr->width;
    ptr->pvt.h = ptr->height;

    float textWidth = (float)ptr->width * ptr->scaleX;
    float textHeight = (float)ptr->height * ptr->scaleY;

    ptr->pvt.x = (int)(ptr->pivotX * -textWidth);
    ptr->pvt.y = (int)(ptr->pivotY * -textHeight);

    ptr->dst.w = (int)textWidth;
    ptr->dst.h = (int)textHeight;
  }
}

SDL_Color privateRenderTextColor;
void PRIVATE__Text__render_text(Text* ptr) {
  if (ptr && ptr->text) {
    TTF_Font* font = ptr->font;
    char* text = ptr->text;
    unsigned int color32 = ptr->color;

    privateRenderTextColor.r = color32 >> 16 & 255;
    privateRenderTextColor.g = color32 >> 8 & 255;
    privateRenderTextColor.b = color32 & 255;
    privateRenderTextColor.a = color32 >> 24 & 255;

    SDL_Surface* temporarySurface = TTF_RenderUTF8_Solid(font, text, privateRenderTextColor);

    SDL_SetSurfaceAlphaMod(temporarySurface, privateRenderTextColor.a);

    ptr->width = temporarySurface->w;
    ptr->height = temporarySurface->h;
    ptr->src.w = temporarySurface->w;
    ptr->src.h = temporarySurface->h;

    ptr->texture = SDL_CreateTextureFromSurface(mainRendererPtr, temporarySurface);

    SDL_FreeSurface(temporarySurface);

    if (
      ptr->pvt.w != ptr->width ||
      ptr->pvt.h != ptr->height) {
      PRIVATE__Text__update_pivot(ptr);
    }
  }
}

void PRIVATE__Text__release_cached_texture(Text* ptr) {
  if (ptr) {
    // printf("releasing cached texture\n");
    if (ptr->texture) {
      // printf("destroying texture\n");
      SDL_DestroyTexture(ptr->texture);
      ptr->texture = 0;
    }
  }
}

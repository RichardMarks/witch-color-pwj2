#ifndef DIMMER_H
#define DIMMER_H

extern void init_dimmer(unsigned int color);
extern void destroy_dimmer();
extern void show_dimmer(float opacity);
extern void hide_dimmer();
extern void render_dimmer();

#endif

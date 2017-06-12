#ifndef FW_H_INCLUDED
#define FW_H_INCLUDED
#include <allegro5/allegro.h>
#include "defines.h"

extern ALLEGRO_EVENT_QUEUE *event_queue;

extern int init_fw(); // inisyalize je a
extern void lancer_fw(); // lanse je a
extern void arreter_fw(); // kite li

#endif // FW_H_INCLUDED

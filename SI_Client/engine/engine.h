#include "screen.h"

typedef enum {RUNNING, SHUTDOWN} E_State;
E_State state;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;
E_Screen current_screen;

int E_Init();
int E_HandleEvent(SDL_Event* event);
int E_Update();
int E_Render();
int E_Shutdown();

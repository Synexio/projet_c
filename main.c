#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
//#include <SDL2/SDL_mixer.h>

#include <fmod.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
void SDL_ExitWithError(char* message);

int main(int argc, char** argv)
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_Surface *imagebg = NULL;
    SDL_Texture *texturebg = NULL;

    FMOD_SYSTEM *system;
    FMOD_SOUND *bgmusic = NULL;
    FMOD_CHANNEL *channel;


    //Mix_Music *musicbg = NULL;

    //Initialisation SDL et vérif
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_ExitWithError("Initialisation SDL");
    }

    //Init audio

    FMOD_System_Create(&system);
    FMOD_System_Init(system, 10, FMOD_INIT_NORMAL  , NULL);
    FMOD_System_GetChannel(system,0,&channel);
    FMOD_System_CreateSound(system, "ressources/sg_gos.mp3", FMOD_CREATESAMPLE, 0, &bgmusic);
    FMOD_System_PlaySound(system, bgmusic, 0, 0, &channel);

    //Creation fenetre et verif
    window = SDL_CreateWindow("Touhou 0.1 by AH & JF",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH,WINDOW_HEIGHT,0);
    if (window == NULL){
        SDL_ExitWithError("Creation fenetre");
    }

    // Creation du rendu pour la fenetre
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_SOFTWARE);
    if (renderer == NULL){
        SDL_ExitWithError("Creation rendu");
    }

    /*-------------------------------------------------------------------------*/

//Execution du programme
    SDL_bool program_launched = SDL_TRUE;

    while(program_launched){
        SDL_Event event;

        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_MOUSEMOTION:
                    printf("%d / %d \n",event.motion.x,event.motion.y);
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_UP:
                            printf("UP");
                            break;

                        default:
                            break;

                    }
                    break;
                case SDL_KEYUP:
                    switch(event.key.keysym.sym){
                        case SDLK_UP:
                            printf("UP");
                            break;

                        default:
                            break;

                    }
                    break;
                case SDL_QUIT:
                    program_launched = SDL_FALSE;
                    break;
                default:
                    break;
            }
        }







    imagebg = SDL_LoadBMP("ressources/ckdo.bmp");
    if (imagebg == NULL){

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Creation image");
    }

    texturebg = SDL_CreateTextureFromSurface(renderer,imagebg);
    SDL_FreeSurface(imagebg);
    if (texturebg == NULL){

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Creation texture");
    }
    SDL_Rect rectangle;

    if (SDL_QueryTexture(texturebg,NULL,NULL,&rectangle.w,&rectangle.h) != 0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Chargement texture");
    }

    rectangle.x = (WINDOW_WIDTH-rectangle.w)/2;
    rectangle.y = (WINDOW_HEIGHT-rectangle.h)/2;

    if (SDL_RenderCopy(renderer,texturebg,NULL,&rectangle) != 0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Affichage texture");
    }

    //Affiche le rendu
    SDL_RenderPresent(renderer);

    /*
    //Efface le rendu
    if(SDL_RenderClear(renderer) != 0){
        SDL_ExitWithError("Effacement rendu");
    }
    */

    }






    /*-------------------------------------------------------------------------*/
    //Quitter SDL
    FMOD_System_Release(system);
    SDL_DestroyTexture(texturebg);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return EXIT_SUCCESS;
}

void SDL_ExitWithError(char* message){
    SDL_Log("Erreur : %s > %s \n",message,SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

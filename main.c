#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
//#include <SDL2/SDL_mixer.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
void SDL_ExitWithError(char* message);

int main(int argc, char** argv)
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_Surface *imagebg = NULL;
    SDL_Texture *texturebg = NULL;

    //Mix_Music *musicbg = NULL;

    //Initialisation SDL et vérif
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_ExitWithError("Initialisation SDL");
    }

    //Init audio et vérif
    /*if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
    {
        SDL_Log("Erreur initialisation SDL_mixer : %s", Mix_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    music = Mix_LoadMUS("ressources/sg_gos.mp3");
    if (music == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur chargement de la musique : %s", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }*/

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
    //Mix_CloseAudio();
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

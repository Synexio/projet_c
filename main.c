#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
//#include <SDL2/SDL_mixer.h>

#include <fmod.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
void SDL_ExitWithError(char* message);

typedef struct Point
{
    int x;
    int y;
}Point;

typedef struct Player
{
    int lives;
    int isShooting;
    int x;
    int y;
}Player;

typedef struct Bullet
{
    int speed;
    int x;
    int y;
}Bullet;

Point pollclick(){
    SDL_Event event;
    Point p;

    while(SDL_PollEvent(&event)){
        if(event.type == SDL_MOUSEBUTTONDOWN){
            p.x = event.motion.x;
            p.y = event.motion.y;
        }
    }

    return p;
}

int pollpress(){
    SDL_Event event;

    while(SDL_PollEvent(&event)){
        if(event.type == SDL_KEYDOWN){
            return event.key.keysym.sym;

        }
    }
}

void drawImage(SDL_Window *window, SDL_Surface *image, SDL_Renderer *renderer, int x, int y){

    SDL_Texture *texture;
    SDL_Rect rectangle;

    if (image == NULL){

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Creation image");
    }

    texture = SDL_CreateTextureFromSurface(renderer,image);
    SDL_FreeSurface(image);
    if (texture == NULL){

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Creation texture");
    }


    if (SDL_QueryTexture(texture,NULL,NULL,&rectangle.w,&rectangle.h) != 0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Chargement texture");
    }

    rectangle.x = x;
    rectangle.y = y;

    if (SDL_RenderCopy(renderer,texture,NULL,&rectangle) != 0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Affichage texture");
    }

    //Affiche le rendu
    //SDL_RenderPresent(renderer);

    //printf("Image affichee");

}

int main(int argc, char** argv)
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_Surface *imagebg = NULL;
    //SDL_Texture *texturebg = NULL;

    FMOD_SYSTEM *system;
    FMOD_SOUND *bgmusic = NULL;
    FMOD_SOUND *theme = NULL;
    FMOD_CHANNEL *channel0;
    FMOD_CHANNEL *channel1;


    //Mix_Music *musicbg = NULL;

    //Initialisation SDL et vérif
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_ExitWithError("Initialisation SDL");
    }

    //Init audio

    FMOD_System_Create(&system);
    FMOD_System_Init(system, 10, FMOD_INIT_NORMAL  , NULL);
    FMOD_System_GetChannel(system,0,&channel0);
    FMOD_System_GetChannel(system,1,&channel1);
    FMOD_System_CreateSound(system, "ressources/sg_gos.mp3", FMOD_CREATESAMPLE, 0, &bgmusic);
    FMOD_System_CreateSound(system, "ressources/main_theme.mp3", FMOD_CREATESAMPLE, 0, &theme);
    FMOD_System_PlaySound(system, bgmusic, 0, 0, &channel0);

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
    SDL_bool game = SDL_FALSE;
    SDL_Surface *reimu = NULL;
    int menu = 0;

    while(program_launched){
        SDL_Event event;
        Point click;
        int buttonpress = 0;



        if(menu==0){

            while(SDL_PollEvent(&event)){
                if (event.type == SDL_QUIT){
                    program_launched = SDL_FALSE;
                    printf("QUIT\n");
                    break;
                }
            }

            imagebg = SDL_LoadBMP("ressources/ckdo.bmp");
            drawImage(window,imagebg,renderer,0,0);
            SDL_RenderPresent(renderer);
            click = pollclick();
            buttonpress = pollpress();

            if( ( click.x > 275 ) && ( click.x < 530 ) && ( click.y > 225 ) && ( click.y < 310 ) ){
                printf("\nIN\n");
                menu = 1;
            }

            if( ( click.x > 275 ) && ( click.x < 530 ) && ( click.y > 475 ) && ( click.y < 555 ) ){
                program_launched = SDL_FALSE;
            }



        }

        if(menu==1){

            FMOD_Channel_SetPaused(channel0,1);
            FMOD_System_PlaySound(system, theme, 0, 0, &channel1);

            int reimu_x = 390;
            int reimu_y = 552;

            while(program_launched)
            {

                imagebg = SDL_LoadBMP("ressources/ckdo2.bmp");
                reimu = SDL_LoadBMP("ressources/reimu.bmp");

                while(SDL_PollEvent(&event)){
                    if (event.type == SDL_KEYDOWN){
                        if(event.key.keysym.sym == SDLK_LEFT && reimu_x >=10){
                            printf("%d\n",reimu_x);
                            reimu_x-=10;
                        }
                        if(event.key.keysym.sym == SDLK_RIGHT && reimu_x <=750){
                            printf("RIGHT\n");
                            reimu_x+=10;
                        }
                    }
                    if (event.type == SDL_QUIT){
                        program_launched = SDL_FALSE;
                        printf("QUIT\n");
                        break;
                    }
                }

                drawImage(window,imagebg,renderer,0,0);
                drawImage(window,reimu,renderer,reimu_x,reimu_y);
                SDL_RenderPresent(renderer);




            }
        }


    /*
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

    rectangle.x = 0;
    rectangle.y = 0;

    if (SDL_RenderCopy(renderer,texturebg,NULL,&rectangle) != 0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Affichage texture");
    }

    //Affiche le rendu
    SDL_RenderPresent(renderer);


    //Efface le rendu
    if(SDL_RenderClear(renderer) != 0){
        SDL_ExitWithError("Effacement rendu");
    }
    */

    }






    /*-------------------------------------------------------------------------*/
    //Quitter SDL
    FMOD_System_Release(system);
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

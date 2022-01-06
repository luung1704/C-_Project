#include "Game.h"
Game::Game(){
    object=NULL;
    rect.x=0;
    rect.y=0;
    rect.h=0;
    rect.w=0;
}
Game::~Game(){
    Free();
}
bool Game::LoadImg(std::string path, SDL_Renderer* screen){
    SDL_Texture* new_texture = NULL;
    SDL_Surface* load_surface = IMG_Load(path.c_str());
    if (load_surface != NULL){
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format,COLOR_KEY_R,COLOR_KEY_G,COLOR_KEY_B));
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if (new_texture != NULL){
            rect.w = load_surface->w;
            rect.h = load_surface->h;
        }
        SDL_FreeSurface(load_surface);
    }
    object = new_texture;
    return object != NULL;
}
void Game::Render(SDL_Renderer* des,const SDL_Rect* clip){
    SDL_RenderCopy(des,object,clip,&rect);
}
void Game::RenderFlip(SDL_Renderer* des,const SDL_Rect* clip){
    SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL ;
    SDL_RenderCopyEx(des, object, NULL, &rect, NULL, NULL, flip);
    //SDL_RenderCopy(des,object,clip,&rect);
}
void Game::Free(){
    if (object) {
        SDL_DestroyTexture(object);
        object = NULL;
        rect.w=0;
        rect.h=0;
    }
}

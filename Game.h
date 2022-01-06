#ifndef GAME_H
#define GAME_H
#include "Common.h"
class Game{
public:
    Game();
    ~Game();
    void SetRect(const int& x, const int& y , const int& w, const int& h){rect.x = x, rect.y = y,rect.w=w, rect.h=h;}
    SDL_Rect SetRect() const {return rect;}
    SDL_Texture* SetObject() const {return object;}
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Render(SDL_Renderer* des, const SDL_Rect* clip=NULL);
    void RenderFlip(SDL_Renderer* des, const SDL_Rect* clip=NULL);
    void Free();
private:
    SDL_Texture* object;
    SDL_Rect rect;
};
#endif // GAME_H

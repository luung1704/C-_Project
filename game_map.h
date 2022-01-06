#ifndef GAME_MAP_H
#define GAME_MAP_H
#include "Common.h"
#include "Game.h"
#define MAX_TILES 20
class TileMat : public Game{
public:
    TileMat();
    ~TileMat();
};
class Gamemap{
public:
    Gamemap();
    ~Gamemap();
    void LoadMap(char* name);
    void LoadTiles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
private:
    Map map_;
    TileMat tile_mat[MAX_TILES];

};
#endif // GAME_MAP_H

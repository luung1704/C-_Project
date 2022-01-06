#ifndef MAINOBJECT_H
#define MAINOBJECT_H
#include "Common.h"
#include "Game.h"

#define GRAVITY_SPEED 1.0
#define MAX_FALL_SPEED 13
#define PLAYER_JUMP_VAL 19
class MainTile : public Game{
public:
    MainTile();
    ~MainTile();
};
class MainObject : public Game {
public:
    MainObject();
    ~MainObject();
    enum WalkType{
        WALK_RIGHT = 0,
        WALK_LEFT = 1,
    };
    float get_attack_status() const {return attack_status;}
    int get_attack_dame () const { int res = rand() % (attack_dame_max - attack_dame_min + 1) + attack_dame_min; return res;}
    float get_x_pos() const { return x_pos;}
    float get_y_pos() const { return y_pos;}
    float getfullhp() const { return fullhp;}
    float getnowhp() const { return nowhp;}
    bool get_left_status() const {return left_status;}
    void setnowhp(int a) {nowhp-=a;}
    void set_attack_status()  {attack_status=0;}
    bool IsAttack() const { return input_type.attack;}
    bool LoadImg(std::string ath, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void LoadTiles(SDL_Renderer* screen);
    void HandelInputAction(SDL_Event events, SDL_Renderer* screen);
    void DoPlayer(Map& map_data);
    void CheckToMap(Map& map_data);
    void SetMapXY(const int map_x, const int map_y){map_x_ = map_x ; map_y_ = map_y;}
    void CenterEnityOnMap(Map& map_data);
private:
    bool attack_status;
    int attack_dame_max;
    int attack_dame_min;
    float fullhp;
    float nowhp;
    float x_val;
    float y_val;
    float x_pos;
    float y_pos;
    float width_frame;
    float height_frame;
    Input input_type;
    int frame;
    int status;
    int prev;
    int frame_jump;
    int frame_fall;
    int frame_attack;
    int frame_idle;
    //SDL_Rect rect;
    MainTile idleTile[8];
    MainTile runTile[10];
    MainTile jumpTile[3];
    MainTile fallTile[4];
    MainTile attack1Tile[6];
    MainTile attack2Tile[6];
    MainTile attack3Tile[8];
    int attack;
    bool on_ground;
    int map_x_;
    int map_y_;
    int come_back_time;
    bool left_status;
};
#endif // MAINOBJECT_H

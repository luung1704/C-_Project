#ifndef THREATSOBJECT_H
#define THREATSOBJECT_H
#include "Common.h"
#include "Game.h"
#define THREAT_FRAME_NUM 8

class ThreatsObject : public Game {
public:
    ThreatsObject();
    ~ThreatsObject();
    float getfullhp() const { return fullhp;}
    float getnowhp() const { return nowhp;}
    int get_attack_status () const {return attack_status;}
    void set_attack_status1 ()  {attack_status1=1;}
    int get_attack_status1 ()  const {return attack_status1;}
    bool get_dead_attack() const {return dead_attack;}
    int get_dead() const {return dead;}
    void set_x_val (const float& xVal) { x_val = xVal;}
    void set_y_val (const float& yVal) {y_val = yVal;}
    void set_x_pos (const float& xp) { x_pos = xp;}
    void set_y_pos (const float& yp) { y_pos = yp;}
    void set_dead () { dead_attack=1;}
    void set_attack (){attack++;}
    void set_hp (int attack_dame) {nowhp-=attack_dame;}
    float get_x_pos() const { return x_pos;}
    float get_y_pos() const { return y_pos;}
    void SetMapXY(const int& mp_x, const int& mp_y) { map_x = mp_x ; map_y = mp_y;}
    void Show(Game runThreat[18],Game deadThreat[15],Game idleThreat[12],Game hurtThreat[12], Game attackThreat[12], SDL_Renderer* des);
    int get_width_frame() const { return width_frame;}
    int get_height_frame() const { return height_frame;}
    void DoPlayer(Map& map_data,int player_x_pos,int player_y_pos);
    void CheckToMap(Map& map_data);
private:
    float attack;
    float fullhp;
    float nowhp;
    int dead;
    int map_x;
    int map_y;
    float y_val;
    float x_val;
    float y_pos;
    float x_pos;
    bool on_ground;
    int width_frame;
    int height_frame;
    int frame;
    int frame_hurt;
    int dead_attack ;
    int frame_run;
    int run_status;
    int idle_status;
    int attack_status;
    int frame_attack;
    int attack_status1;
    int count;
};
#endif // THREATSOBJECT_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Common.h"
#include "Game.h"
#include "Gamemap.h"
#include "MainObject.h"
#include "ThreatsObject.h"
Game background;
//-----------------------------------------------------------------------------------------------
void RenderHPBar(int x, int y, int w, int h, float Percent,SDL_Renderer* Renderer) {
   Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : Percent;
   SDL_Color old;
   SDL_GetRenderDrawColor(Renderer, &old.r, &old.g, &old.g, &old.a);
   SDL_Rect bgrect = { x, y, w, h };
   SDL_SetRenderDrawColor(Renderer, 90, 90, 90, 100);
   SDL_RenderFillRect(Renderer, &bgrect);
   SDL_SetRenderDrawColor(Renderer, 0, 255, 0, 200);

   int pw = (int)((float)w * Percent);
   int px = x + (w - pw);
   SDL_Rect fgrect = { px, y, pw, h };
   SDL_RenderFillRect(Renderer, &fgrect);
   SDL_SetRenderDrawColor(Renderer, old.r, old.g, old.b, old.a);
}
//-----------------------------------------------------------------------------------------------
bool InitData(){
    bool status = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0 )
        return false;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");

    window = SDL_CreateWindow("Knight game",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if (window == NULL){
        status = false;
    }
    else{
        screen = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
        if (screen == NULL)
            status = false;
        else{
            SDL_SetRenderDrawColor(screen,RENDER_DRAW_COLOR ,RENDER_DRAW_COLOR ,RENDER_DRAW_COLOR ,RENDER_DRAW_COLOR );
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                status = false;
        }
    }
    return status;
}

bool LoadBackground(){
    bool ret = background.LoadImg("map//bg2.png",screen);
    if (ret == false)
        return false;
    return true;
}
Game runEnemy[18],deadEnemy[15],idleEnemy[12],hurtEnemy[12],attackEnemy[12];
bool LoadEnemy(){
    char file_img[50];
    FILE* fp = NULL;
    for (int i = 0 ; i < 18; i ++)
    {   if (i < 10)
            sprintf_s(file_img, "Enemy//Walking//Minotaur_01_Walking_00%d.PNG",i);
        else
             sprintf_s(file_img, "Enemy//Walking//Minotaur_01_Walking_0%d.PNG",i);
        runEnemy[i].LoadImg(file_img,screen);

    }
    for (int i = 0 ; i < 15; i ++)
    {   if (i < 10)
            sprintf_s(file_img, "Enemy//Dying//Minotaur_01_Dying_00%d.PNG",i);
        else
             sprintf_s(file_img, "Enemy//Dying//Minotaur_01_Dying_0%d.PNG",i);
        deadEnemy[i].LoadImg(file_img,screen);
    }
    for (int i = 0 ; i < 12; i ++)
    {   if (i < 10)
            sprintf_s(file_img, "Enemy//Idle//Minotaur_01_Idle_00%d.PNG",i);
        else
             sprintf_s(file_img, "Enemy//Idle//Minotaur_01_Idle_0%d.PNG",i);
        idleEnemy[i].LoadImg(file_img,screen);
    }
    for (int i = 0 ; i < 12; i ++)
    {   if (i < 10)
            sprintf_s(file_img, "Enemy//Hurt//Minotaur_01_Hurt_00%d.PNG",i);
        else
             sprintf_s(file_img, "Enemy//Hurt//Minotaur_01_Hurt_0%d.PNG",i);
        hurtEnemy[i].LoadImg(file_img,screen);
    }
    for (int i = 0 ; i < 12; i ++)
    {   if (i < 10)
            sprintf_s(file_img, "Enemy//Attacking//Minotaur_01_Attacking_00%d.PNG",i);
        else
             sprintf_s(file_img, "Enemy//Attacking//Minotaur_01_Attacking_0%d.PNG",i);
        attackEnemy[i].LoadImg(file_img,screen);
    }
    return true;
}
void close(){
    background.Free();
    SDL_DestroyRenderer(screen);
    screen= NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    IMG_Quit();
    SDL_Quit();
}
int main(int argc, char* argv[])
{
    srand(time(NULL));
    if (InitData() == false)
        return -1;
    if (LoadBackground() == false)
        return -1;
    Gamemap gamemap_;
    gamemap_.LoadMap("map//map01.dat");
    gamemap_.LoadTiles(screen);
    LoadEnemy();
    MainObject player;
    player.LoadTiles(screen);
    ThreatsObject threat[30];
    const int FPS = 30;
    const int frameDelay = 1000/FPS;
    int32_t frameStart;
    int frameTime=0;
    for(int i = 0 ; i < 30; i++){
        threat[i].set_x_pos(i*300);
        //threat[i].set_y_pos(0);
    }
    bool is_quit = false;
    while (!is_quit) {
        //SDL_Delay(40);
        frameStart = SDL_GetTicks();
        while (SDL_PollEvent(&event) != 0) {
            if (event.type ==SDL_QUIT)
                is_quit = true;
                player.HandelInputAction(event,screen);

        }

        SDL_SetRenderDrawColor(screen,0 ,RENDER_DRAW_COLOR ,RENDER_DRAW_COLOR ,0 );
        SDL_RenderClear(screen);

        background.SetRect(0,0,1280,640);
        background.Render(screen);

        //gamemap_.DrawMap(screen);
        //mainT[6].Render(screen);
        Map ga_map = gamemap_.getMap();
        player.SetMapXY(ga_map.start_x,ga_map.start_y);
        player.DoPlayer(ga_map);
        int x=player.get_x_pos();
        int y=player.get_y_pos();
        if (x > 640) x=640;
        x+=60;
        //if (y > 320) y = 320;
        RenderHPBar(x,y,40,7,player.getnowhp()/player.getfullhp(),screen);
        for(int i = 0 ; i < 30; i ++){
            threat[i].SetMapXY(ga_map.start_x,ga_map.start_y);
            threat[i].DoPlayer(ga_map,player.get_x_pos(),player.get_y_pos());
            if (threat[i].getnowhp() < threat[i].getfullhp() && !threat[i].get_dead() && !threat[i].get_dead_attack())
            RenderHPBar(std::min(threat[i].get_x_pos()+15,640+(threat[i].get_x_pos()+15-player.get_x_pos())),threat[i].get_y_pos(),30,7,threat[i].getnowhp()/threat[i].getfullhp(),screen);
            threat[i].Show(runEnemy, deadEnemy, idleEnemy, hurtEnemy, attackEnemy, screen);
            if (threat[i].get_attack_status()==0 && threat[i].get_attack_status1()==0) {
                player.setnowhp(5);
                threat[i].set_attack_status1();
            }
        }
        player.Show(screen);
        bool kt=0;
        if (player.IsAttack()) {
            for(int i = 0 ; i< 30 ; i++){
                if (!player.get_left_status()){
                    if (threat[i].get_x_pos() < player.get_x_pos()+140 && threat[i].get_x_pos() > player.get_x_pos() && !threat[i].get_dead() && player.get_attack_status()&& !threat[i].get_dead_attack() && threat[i].get_y_pos() > player.get_y_pos() && threat[i].get_y_pos() < player.get_y_pos()+64 ){

                        //threat[i].set_dead();
                        threat[i].set_attack();
                        x=player.get_attack_dame();
                        threat[i].set_hp(x);
                        std::cout<<x<<"\n";
                        //std::cout<<threat[i].get_x_pos() <<" "<< player.get_x_pos()+140<<" "<<i<<"\n";
                        kt =1;
                    }
                }
                else{
                        if (threat[i].get_x_pos() > player.get_x_pos()-40 && threat[i].get_x_pos() < player.get_x_pos()+50 && !threat[i].get_dead() && player.get_attack_status()&& !threat[i].get_dead_attack()&& threat[i].get_y_pos() > player.get_y_pos() && threat[i].get_y_pos() < player.get_y_pos()+64){
                            //threat[i].set_dead();
                            threat[i].set_attack();
                            x=player.get_attack_dame();
                            threat[i].set_hp(x);
                            std::cout<<x<<"\n";
                            //std::cout<<threat[i].get_x_pos() <<" "<< player.get_x_pos()+140<<" "<<i<<"\n";
                            kt =1;
                    }
                }

            }
        }
        if (kt)
            player.set_attack_status();
        gamemap_.setMap(ga_map);
        gamemap_.DrawMap(screen);
        SDL_RenderPresent(screen);

        frameTime = SDL_GetTicks()-frameStart;
        if (frameDelay > frameTime){

            SDL_Delay(frameDelay - frameTime);
        }
        if (player.getnowhp() <=0 ){
            MessageBox(NULL, "GAME OVER", "Info", MB_OK | MB_ICONSTOP);
            close();
            SDL_Quit();
        return 0;
        }

    }
    close();
    return 0;
}

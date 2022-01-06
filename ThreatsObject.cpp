#include "ThreatsObject.h"

ThreatsObject::ThreatsObject(){
    width_frame = 64;
    height_frame = 64;
    x_val = 0;
    y_val = 0;
    x_pos = 0;
    y_pos = 0;
    on_ground = 0;
    frame = -1;
    dead=0;
    dead_attack = 0;
    count=0;
    nowhp=30;
    fullhp=30;
    attack=0;
    frame_hurt=-1;
    run_status=0;
    frame_run=0;
    idle_status=1;
    attack_status=-1;
    frame_attack=-1;
    attack_status1=0;

}
ThreatsObject::~ThreatsObject(){

}
void ThreatsObject::Show(Game runThreat[18],Game deadThreat[15],Game idleThreat[12],Game hurtThreat[12], Game attackThreat[12], SDL_Renderer* des){
    if (dead==1) return;
    if (nowhp <=0) dead_attack=1;
    if (dead_attack){
        run_status=0;
        count++;
        if (count==100) { frame = 0; dead= 1 ; return ;}
        frame++;
        if (frame >28) {frame =28; }
        deadThreat[frame/2].SetRect(x_pos-map_x,y_pos-map_y, 64,64);

        if (idle_status==1)
            deadThreat[frame/2].Render(des);
        else
            deadThreat[frame/2].RenderFlip(des);
        return;
    }
    if (attack_status==0) {

        frame_attack++;
        if (frame_attack >11) {frame_attack=-1;attack_status++;}
        //std::cout<<frame_attack<<"\n";
        attackThreat[frame_attack].SetRect(x_pos-map_x,y_pos-map_y, 64,64);
        if (idle_status==1)
            attackThreat[frame_attack].Render(des);
        else
            attackThreat[frame_attack].RenderFlip(des);
        return;
    }
    if (attack==1) {
        frame_hurt++;
        attack=0;
        frame=0;
        frame_run=0;
        run_status=0;
    }

    if (frame_hurt>-1){
        //std::cout<<frame_hurt<<"\n";
        run_status=0;
        frame_hurt++;
        if (frame_hurt >11) {frame_hurt=-1;attack=0;}
        hurtThreat[frame_hurt].SetRect(x_pos-map_x,y_pos-map_y, 64,64);
        if (idle_status==1)
            hurtThreat[frame_hurt].Render(des);
        else
            hurtThreat[frame_hurt].RenderFlip(des);
        return;
    }

    if (run_status){

        frame_hurt=-1;

        frame_run++;

        if (frame_run > 34) frame_run=0;
        runThreat[frame_run/2].SetRect(x_pos-map_x,y_pos-map_y, 64,64);
        if (run_status==1)
            runThreat[frame_run/2].Render(des);
        else
            runThreat[frame_run/2].RenderFlip(des);
        return;
    }
    frame++;
    frame_run=0;
    frame_hurt=-1;
    //std::cout<<idle_status<<"\n";
    if (frame > 22) frame = 0;
    idleThreat[frame/2].SetRect(x_pos-map_x,y_pos-map_y, 64,64);
    if (idle_status==1)
        idleThreat[frame/2].Render(des);
    else
        idleThreat[frame/2].RenderFlip(des);

}
void ThreatsObject::DoPlayer(Map& map_data,int player_x_pos,int player_y_pos){
    if (dead == 1 ) return;
    x_val = 0;
    y_val +=10;
    if (y_val>=10) {
        y_val=10;
    }
    if (on_ground&&!dead_attack){
        int gg=abs(x_pos - player_x_pos);
        if (gg <= 640 && gg >= 30) {

            //std::cout<<gg<<"\n";

            if (x_pos > player_x_pos){
                x_val-=5;
                run_status=2;
            }
            else{
                run_status=1;
                x_val+=5;

            }
        }
        else{
            if (x_pos > player_x_pos){
                idle_status=2;
            }
            else{
                idle_status=1;
            }
            run_status=0;
            if (gg < 30 && attack_status<0&&y_pos > player_y_pos && y_pos < player_y_pos+64)
                attack_status++;
        }

    }
    CheckToMap(map_data);
}
void ThreatsObject::CheckToMap(Map& map_data){
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;
    int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;

    x1 = (x_pos+x_val) / TILE_SIZE ;
    x2 = (x_pos + x_val +width_frame-1)/TILE_SIZE;
    y1 = (y_pos-20) / TILE_SIZE;
    y2 = (y_pos + height_min -20) / TILE_SIZE;
    //std::cout<<y_pos<<" ";
    //std::cout<<y2<<" "<<y1<<"\n";
    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y){
        if (x_val > 0) {
            if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2]!= BLANK_TILE)
            {
                 //std::cout<<"co van de x_pos > 0\n";

                x_pos = (x2)*TILE_SIZE;
                x_pos -= width_frame+1;
                x_val = 0;
            }
        }
        else if (x_val < 0) {
            if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1]!= BLANK_TILE){
                //std::cout<<"co van de x_pos > 0\n";
                x_pos = (x1+1)*TILE_SIZE;
                x_val = 0;
            }
        }
    }

    int width_min = width_frame < TILE_SIZE ? width_frame :TILE_SIZE;
    x1 = (x_pos) / TILE_SIZE;
    x2 = (x_pos + width_min) / TILE_SIZE;

    y1 = (y_pos + y_val) / TILE_SIZE;
    y2 = (y_pos + y_val +height_frame -1 ) / TILE_SIZE;
    if ( x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
        if (y_val > 0) {

            if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE) {
                y_pos = y2*TILE_SIZE+5;
                y_pos -= height_frame +1;
                y_val =0;
                on_ground = true;
            }
        }
        else if (y_val < 0 ) {
           if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE) {
                y_pos = (y1 + 1)*TILE_SIZE+1;
                y_val = 0;
            }
        }
    }
    x_pos+=x_val;
    y_pos+=y_val;
    if (x_pos < 0){
       x_pos =0;
    }
    if (x_pos+height_frame > map_data.max_x){
        x_pos = map_data.max_x + width_frame -1;
    }
    if (y_pos > map_data.max_y){
        dead=1;
    }
}
//bool Thread

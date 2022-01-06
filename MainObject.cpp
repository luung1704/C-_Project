#include "MainObject.h"
MainTile::MainTile(){
}
MainTile::~MainTile(){
}
MainObject::MainObject(){
    attack_status=0;
    nowhp=90;
    fullhp=100;
    attack_dame_min=8;
    attack_dame_max=15;
    frame_attack = -1;
    frame_fall = -1;
    frame_jump = -1;
    frame = -1;
    frame_idle=-1;
    x_pos = 0;
    y_pos = 0;
    x_val = 0;
    y_val = 0;
    width_frame = 64;
    height_frame = 80;
    status = -1;
    prev=1;
    on_ground = false;
    map_x_ = 0;
    map_y_ = 0;
    come_back_time = 0;
    input_type.attack=0;
    attack = 1;
    left_status=0;
}

MainObject::~MainObject(){
}
bool MainObject::LoadImg(std::string path, SDL_Renderer* screen){
}
void MainObject::LoadTiles(SDL_Renderer* screen){
    char file_img[50];
    FILE* fp = NULL;
    for (int i = 0 ; i < 8; i ++)
    {
        sprintf_s(file_img, "hero//Idle//HeroKnight_Idle_%d.png",i);
        idleTile[i].LoadImg(file_img,screen);
    }
    for (int i = 0 ; i < 10; i ++)
    {
        sprintf_s(file_img, "hero//Run//HeroKnight_Run_%d.png",i);
        runTile[i].LoadImg(file_img,screen);
    }
        for (int i = 0 ; i < 3; i ++)
    {
        sprintf_s(file_img, "hero//Jump//HeroKnight_Jump_%d.png",i);
        //std::cout<<file_img<<"\n";
        jumpTile[i].LoadImg(file_img,screen);
    }
        for (int i = 0 ; i < 4; i ++)
    {
        sprintf_s(file_img, "hero//Fall//HeroKnight_Fall_%d.png",i);
        //std::cout<<file_img<<"\n";
        fallTile[i].LoadImg(file_img,screen);
    }
            for (int i = 0 ; i < 6; i ++)
    {
        sprintf_s(file_img, "hero//Attack1//HeroKnight_Attack1_%d.png",i);
        //std::cout<<file_img<<"\n";
        attack1Tile[i].LoadImg(file_img,screen);
    }
            for (int i = 0 ; i < 6; i ++)
    {
        sprintf_s(file_img, "hero//Attack2//HeroKnight_Attack2_%d.png",i);
        //std::cout<<file_img<<"\n";
        attack2Tile[i].LoadImg(file_img,screen);
    }
            for (int i = 0 ; i < 8; i ++)
    {
        sprintf_s(file_img, "hero//Attack3//HeroKnight_Attack3_%d.png",i);
        //std::cout<<file_img<<"\n";
        attack3Tile[i].LoadImg(file_img,screen);
    }


}
void MainObject::Show(SDL_Renderer* des){
    if (!on_ground) {
            input_type.attack=0;
            bool kt = 0;
        if (y_val <=0){
            frame_jump++;
            if (frame_jump > 2)
                frame_jump = 2;
            jumpTile[frame_jump].SetRect(x_pos-map_x_,y_pos-map_y_, 150,82.5);
            if (input_type.left == 1) {
                jumpTile[frame_jump].RenderFlip(des);
                kt = 1;
                prev=0;
            }
            if (input_type.right == 1) {
                jumpTile[frame_jump].Render(des);
                kt = 1;
                prev=1;
            }
            if (kt == 0){
                if (prev == 0)
                    jumpTile[frame_jump].RenderFlip(des);
                else
                    jumpTile[frame_jump].Render(des);
            }
        }
        if (y_val > 0) {
            kt = 0;
            frame_fall++;
            if (frame_fall > 3)
                frame_fall =0;
            fallTile[frame_fall].SetRect(x_pos-map_x_,y_pos-map_y_, 150,82.5);
            if (input_type.left == 1) {
                fallTile[frame_fall].RenderFlip(des);
                left_status=1;
                kt =1;
                prev = 0;
            }
            if (input_type.right == 1) {
                fallTile[frame_fall].Render(des);

                kt =1;
                prev=1;
            }
            if (kt == 0){
                if (prev == 0){
                    fallTile[frame_fall].RenderFlip(des);
                    left_status=1;
                }
                else{
                    fallTile[frame_fall].Render(des);
                }
            }
        }
    }
    if (on_ground){
        frame_fall = 0;
        frame_jump = 0;
        if(input_type.attack == 1) {
            if (!frame_attack)
            attack_status=1;
            frame_attack++;
            if (frame_attack > 5 && (attack == 1 || attack ==2)) {attack_status=0;frame_attack = 0;input_type.attack=0;attack++;}
            if (frame_attack > 7 && attack == 3) { attack_status=0;frame_attack = 0; input_type.attack = 0; attack = 1;}
            if (input_type.right){
            if (attack == 1) {
                attack1Tile[frame_attack].SetRect(x_pos-map_x_,y_pos-map_y_, 150,82.5);
                attack1Tile[frame_attack].Render(des);
                left_status=0;
            }
            if (attack == 2) {
                attack2Tile[frame_attack].SetRect(x_pos-map_x_,y_pos-map_y_, 150,82.5);
                attack2Tile[frame_attack].Render(des);
                left_status=0;
            }
            if (attack == 3) {
                attack3Tile[frame_attack].SetRect(x_pos-map_x_,y_pos-map_y_, 150,82.5);
                attack3Tile[frame_attack].Render(des);
                left_status=0;
            }
            prev=1;
            return;
            }

            if (input_type.left){
            if (attack == 1) {
                attack1Tile[frame_attack].SetRect(x_pos-map_x_,y_pos-map_y_, 150,82.5);
                attack1Tile[frame_attack].RenderFlip(des);
                left_status=1;
            }
            if (attack == 2) {
                attack2Tile[frame_attack].SetRect(x_pos-map_x_,y_pos-map_y_, 150,82.5);
                attack2Tile[frame_attack].RenderFlip(des);
                left_status=1;
            }
            if (attack == 3) {
                attack3Tile[frame_attack].SetRect(x_pos-map_x_,y_pos-map_y_, 150,82.5);
                attack3Tile[frame_attack].RenderFlip(des);
                left_status=1;
            }
            prev=0;
            return;
            }
            if (prev == 0 ){
                if (attack == 1) {
                    attack1Tile[frame_attack].SetRect(x_pos-map_x_,y_pos-map_y_, 150,82.5);
                    attack1Tile[frame_attack].RenderFlip(des);
                    left_status=1;
                }
                if (attack == 2) {
                    attack2Tile[frame_attack].SetRect(x_pos-map_x_,y_pos-map_y_, 150,82.5);
                    attack2Tile[frame_attack].RenderFlip(des);
                    left_status=1;
                }
                if (attack == 3) {
                    attack3Tile[frame_attack].SetRect(x_pos-map_x_,y_pos-map_y_, 150,82.5);
                    attack3Tile[frame_attack].RenderFlip(des);
                    left_status=1;
                }
            }
            else{
                if (attack == 1) {
                    attack1Tile[frame_attack].SetRect(x_pos-map_x_,y_pos-map_y_, 150,82.5);
                    attack1Tile[frame_attack].Render(des);
                    left_status=0;
                }
                if (attack == 2) {
                    attack2Tile[frame_attack].SetRect(x_pos-map_x_,y_pos-map_y_, 150,82.5);
                    attack2Tile[frame_attack].Render(des);
                    left_status=0;
                }
                if (attack == 3) {
                    attack3Tile[frame_attack].SetRect(x_pos-map_x_,y_pos-map_y_, 150,82.5);
                    attack3Tile[frame_attack].Render(des);
                    left_status=0;
                }
            }

            return;

        }


    if (input_type.left == 1 || input_type.right == 1){
        frame++;
    }
    else{ frame = -1;
    }
    if (frame >= 9) frame = 0;
    runTile[frame].SetRect(x_pos-map_x_,y_pos-map_y_, 150,82.5);
    if (input_type.left == 1){
        runTile[frame].RenderFlip(des);
        prev=0;
        return;

    }
    if (input_type.right == 1){
        runTile[frame].Render(des);
        prev=1;
        return;
    }
    //std::cout<<frame_idle/3<<"\n";
    frame_idle++;
    if (frame_idle>= 23) frame_idle = 0;
    idleTile[frame_idle/3].SetRect(x_pos-map_x_,y_pos-map_y_, 150,82.5);
    if (prev==0){
        idleTile[frame_idle/3].RenderFlip(des);
        return;
    }
    if (prev==1){
        idleTile[frame_idle/3].Render(des);
        return;
    }
    }


    //std::cout<<frame<<"\n";



}
void MainObject::HandelInputAction(SDL_Event events, SDL_Renderer* screen) {
if (events.type == SDL_KEYDOWN) {
    switch (events.key.keysym.sym){
    case SDLK_d:{
        status =WALK_RIGHT;
        input_type.right=1;
        input_type.left = 0;
        //std::cout<<"right\n";
    }
    break;
        case SDLK_a:{
        status =WALK_LEFT;
        input_type.left=1;
        input_type.right = 0;
        //std::cout<<"left\n";
    }
    break;
        default:
            break;
    }
}
else if (events.type == SDL_KEYUP){
    switch (events.key.keysym.sym) {
        case SDLK_d:{
            input_type.right = 0;
        }
        break;
        case SDLK_a:{
            input_type.left = 0;
        }
        break;
        default:
            break;
    }
}
if (events.type == SDL_KEYDOWN) {
    if (events.key.keysym.sym == SDLK_w) {
        input_type.jump = 1;
    }
}
if (events.type == SDL_KEYDOWN) {
    if (events.key.keysym.sym == SDLK_SPACE) {
        input_type.attack = 1;
    }
}
}
void MainObject::DoPlayer(Map& map_data){
    if (come_back_time == 0) {
    x_val = 0;
    y_val += 1.2;
    if (y_val >= MAX_FALL_SPEED){
        y_val = MAX_FALL_SPEED;
    }
    if (input_type.left == 1){
        x_val -=SPEED;
    }
    else
    if (input_type.right == 1){
        x_val +=SPEED;
    }
    if (input_type.jump == 1) {
        if (on_ground == true){
            y_val = -PLAYER_JUMP_VAL;
            on_ground = false;
        }
        input_type.jump = 0;
    }
    CheckToMap(map_data);
    CenterEnityOnMap(map_data);
    }
    if (come_back_time > 0) {
        come_back_time--;
        if ( come_back_time == 0){
            y_pos = 0;
            x_val = 0;
            y_val = 0;
            //x_pos = 0;
        }
    }
}
void MainObject::CenterEnityOnMap(Map& map_data){
    map_data.start_x = x_pos - (SCREEN_WIDTH/2);
    if (map_data.start_x < 0 ){
        map_data.start_x = 0;
    }
    else if (map_data.start_x + SCREEN_WIDTH >= map_data.max_x){
        map_data.start_x = map_data.max_x - SCREEN_WIDTH;
    }
    map_data.start_y = y_pos - (SCREEN_HEIGHT / 2);
    if (map_data.start_y < 0) {
        map_data.start_y = 0;
    }
    else if (map_data.start_y + SCREEN_HEIGHT >= map_data.max_y) {
        map_data.start_y = map_data.max_y - SCREEN_HEIGHT;
    }
}
void MainObject::CheckToMap(Map& map_data){
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;

    int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;
    x1 = (x_pos+x_val+55) / TILE_SIZE ;
    x2 = (x_pos + x_val +width_frame-1+30)/TILE_SIZE;
    y1 = (y_pos) / TILE_SIZE;
    y2 = (y_pos + height_min - 1) / TILE_SIZE;
    //std::cout<<"nhan vat"<<" "<<y_pos<<" "<<y2<<" "<<y1<<"\n";
    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y){
        if (x_val > 0) {
            if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2]){
                //std::cout<<"co van de x_val > 0\n";
                x_pos = x2*TILE_SIZE-30;
                x_pos -= width_frame+1;
                x_val = 0;
            }
        }
        else if (x_val < 0) {
            if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1]){
                //std::cout<<"co van de x_val < 0\n";
                x_pos = (x1+1)*TILE_SIZE-55;
                x_val = 0;
            }
        }
    }

    int width_min = width_frame < TILE_SIZE ? width_frame :TILE_SIZE;
    x1 = (x_pos+55) / TILE_SIZE;
    x2 = (x_pos + width_min+30) / TILE_SIZE;

    y1 = (y_pos + y_val) / TILE_SIZE;
    y2 = (y_pos + y_val +height_frame  ) / TILE_SIZE;
    if ( x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
        if (y_val > 0) {

            if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE) {
                //std::cout<<"co van de\n";
                y_pos = y2*TILE_SIZE;
                y_pos -= height_frame +1;
                y_val =0;
                on_ground = true;
            }
        }
        else if (y_val < 0 ) {
           if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE) {
                //std::cout<<"co van de"<<y_pos<<" "<<y1<<" ";
                y_pos = (y1 + 1)*TILE_SIZE+1;
                //std::cout<<y_pos<<"\n";
                y_val = 0;
            }
        }
    }
    x_pos+=x_val;
    y_pos+=y_val;
    if (x_pos < -50){
       x_pos =-50;
    }
    if (x_pos+height_frame > map_data.max_x){
        x_pos = map_data.max_x + width_frame -1;
    }
    if (y_pos > map_data.max_y){
        nowhp=0;
        come_back_time = 60;
    }
}

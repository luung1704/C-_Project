
#include "Gamemap.h"
void Gamemap::LoadMap(char* name){
    FILE* fp = NULL;
    fopen_s(&fp, name, "rb");
    if (fp == NULL){
        return;
    }
    map_.max_x = 0;
    map_.max_y = 0;
    for(int i = 0 ; i< MAX_MAP_Y ; i ++){
    for(int j = 0 ; j < MAX_MAP_X ; j ++){
        fscanf(fp,"%d",&map_.tile[i][j]);
        //std::cout<<map_.tile[i][j]<<std::endl;
        int val = map_.tile[i][j];
        if (val > 0){
            if ( j > map_.max_x) {
                map_.max_x = j;
            }
            if ( i > map_.max_y) {
                map_.max_y = i;
            }
        }
    }
    }
    map_.max_x= (map_.max_x+1) * TILE_SIZE;
    map_.max_y= (map_.max_y+1) * TILE_SIZE;
    map_.start_x = 0;
    map_.start_y = 0;
    map_.file_name = name;
    fclose(fp);
}
void Gamemap::LoadTiles(SDL_Renderer* screen){
    char file_img[30];
    FILE* fp = NULL;
    for (int i = 0 ; i < MAX_TILES; i ++)
    {
        sprintf_s(file_img, "map//%d.png",i);
        fopen_s(&fp,file_img,"rb");
        if (fp == NULL){
            //std::cout<<"hello";
            continue;
        }
        fclose(fp);
        tile_mat[i].LoadImg(file_img,screen);
    }
}
void Gamemap::DrawMap(SDL_Renderer* screen){
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;
    int map_x = 0;
    int map_y = 0;
    map_x = map_.start_x/TILE_SIZE;
    x1 = (map_.start_x%TILE_SIZE)*-1;
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);
    map_y = map_.start_y/TILE_SIZE;
    y1 = (map_.start_y%TILE_SIZE)*-1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    for (int i = y1 ; i < y2 ; i+= TILE_SIZE){
        map_x = map_.start_x/TILE_SIZE;
        for(int j = x1 ; j< x2 ; j += TILE_SIZE){
            int val = map_.tile[map_y][map_x];
            if (val > 0) {

                tile_mat[val].SetRect(j,i,64,64);
                tile_mat[val].Render(screen);
            }
            map_x++;
        }
        map_y++;
    }
}


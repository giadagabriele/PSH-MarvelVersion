#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Map.h"
#include "Player.h"
#include "Enemy.h"

class GameManager
{
    private:
        Map map;
        Player* player=NULL;
        vector <Enemy> enemies;
        bool destroy;
        int xBarrel;
        int yBarrel;
        int directionBarrel;
        
    public:
        GameManager();
        void movePlayer(int);
        void moveEnemy();
        bool moveBarrel(int, int, int, int);
        
        void update(Creature&, int, int, int, int, int, int);
       
        bool takeBarrel(int);
        bool dropBarrel(int);
        
        void respawn(int,int,int);
        void collisionEnemy(int,int);
        void collisionPlayer(int, int);
        
        void collisionP(Enemy&, int, int, int, int, int, int);
        int gameOver();
        int newLevel();
        void createMap(int);
        
        //SET E GET
        Player getPlayer() const {return *player;}
        Enemy getEnemy(int i) const {return enemies[i];}
        Map getMap() const {return map;}
        int getDirectionBarrel() const {return directionBarrel;}
        bool getDestroy() const {return destroy;}
        
        void setDirectionBarrel(int dir) {directionBarrel=dir;}
        void setBarrel(int x, int y); 
        
};

#endif
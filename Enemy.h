#ifndef ENEMY_H
#define ENEMY_H
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "Creature.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

//      La classe Enemy carica le immagini di ogni Enemy (tra cui il Corsaro) presente sulla mappa

class Enemy : public Creature
{
	private:
	    int value;
		int speed;
		ALLEGRO_BITMAP *enemy;
	public:
		Enemy(int v,int x,int y) : Creature(x, y), speed(1) 
		{
		    value = v;
		    if(value == 3)
		    {
		        enemy=al_load_bitmap("Immagini/enemy.png");
		    }
	        else
	        {
	            enemy=al_load_bitmap("Immagini/corsair.png");
	        }
		}		
		int getSpeed() const {return speed;}
		int getValue() const {return value;}
		void draw(int i, int j)
		{
		    al_draw_bitmap(enemy,j,i,0);
		}
};

#endif

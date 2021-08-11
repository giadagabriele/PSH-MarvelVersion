#ifndef CREATURE_H
#define CREATURE_H

#include "Map.h"

//      La classe Creature setta le coordinate di tutto ciò che è 
//      in movimento sulla mappa, ovvero il Giocatore e i nemici
//      Il metodo move prende in input un intero che serve ad aggiornare
//      la direzione dell'oggetto: 0 verso l'alto, 1 verso sinistra,
//      2 verso il basso e 3 verso destra

class Creature
{
    protected:
        int x;
        int y;
        int value;
        int direction;
        
    public:
        Creature(int x,int y)
        {
            this->x=x;
            this->y=y;
        }
        Creature(int value, int x, int y)
        {
            this->value = value;
            this->x = x;
            this->y = y;
        }
        void move(int direction)
        {
            if(direction==0)   //UP
	            x--;
            if(direction==1)   //LEFT
	            y--;
	        if(direction==2)   //DOWN
	            x++;
	        if(direction==3)   //RIGHT
	            y++;
        } 
        
        //SET E GET
        int getX() const {return x;}
        int getY() const {return y;}
        int getValue() const { return value; }
        int getDirection() const {return direction;}
        
        void setX(int x1) {x=x1;}
        void setY(int y1) {y=y1;}
        void setDirection(int d) {direction=d;}
        void setValue(int v) {value = v;}
};

#endif





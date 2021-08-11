#ifndef MAP_H
#define MAP_H

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
using namespace std;

// Il costruttore di Map serve a creare una mappa di dimensione 
// 14x17 e un cont = 1 per tenere traccia del livello corrente

// Il metodo LoadLevel carica nell'attributo map il livello corrente da file di testo
// che contiene tutti gli oggetti della mappa (Enemy, Player, barili)

// Il metodo printMap stampa su terminale il contenuto di map

// Il metodo setValue prende come parametri un valore e le 
// posizioni i,j e setta il valore sulle coordinate passate

//cont tiene traccia del livello corrente
class Map
{
    private:
		int **map;
		int rows;
		int columns;
		int cont;
		int levelMax;
	public:
	    Map();
		int **getMap() const {return map;}
		void loadLevel();
		void printMap();
		
		//SET E GET
		int getCont() {return cont;}
		int getRows() const {return rows;}
		int getColumns() const {return columns;}
		int getValue(int i, int j) const {return map[i][j];}
		int getLevelMax() const {return levelMax;}
		
		void setValue(int value, int i, int j){map[i][j]=value;}
		void setCont(int c) {cont=c;}
		
};

#endif

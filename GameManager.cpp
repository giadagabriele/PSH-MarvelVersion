#include "GameManager.h"

//  Il costruttore carica la mappa e crea gli oggetti Player e un vector di enemies

GameManager::GameManager()
{
    destroy=true;
    map.loadLevel();
    createMap(5);
}

// setta le posizioni iniziali del barilie, che coincidono con quelle del player

void GameManager::setBarrel(int x, int y)
{
   xBarrel = x;
   yBarrel = y;
}

// prende in input un intero che rappresenta le vite iniziali del player
// legge la matrice e crea gli oggetti Player con le coordinati iniziali e 
// un vector di enemies che oltre alle coordinate indica il tipo di nemico:
// 3 semplice nemico, 4 corsaro

void GameManager::createMap(int lifes)
{
    enemies.clear();
    for(int i=0;i<map.getRows();i++)
    {
        for(int j=0;j<map.getColumns();j++)
        {
            if(map.getValue(i,j)==2){
                player=new Player(i,j,lifes);
            }
            if(map.getValue(i,j)==3)
            {
                Enemy e(3,i,j);
                enemies.push_back(e);
            }
            if(map.getValue(i,j)==4)
            {
                Enemy e(4,i,j);
                enemies.push_back(e);
            }
        }
    }
}

//  Il metodo movePlayer permette di far muovere il player in  
//  ogni posizione vuota della mappa senza uscire dai bordi.
//  Aggiorna le coordinate del player mediante il metodo move 
//  e sulla mappa con il setValue  

void GameManager::movePlayer(int direction)
{
    int x = player->getX();
    int y = player->getY();
    if(direction==0 && map.getValue(x-1,y)==0)      //UP
    {
        player->setDirection(0);
        update(*player, 0, 2, x, y, x-1, y);
    }
    if(direction==1 && map.getValue(x,y-1)==0)      //LEFT
    {
        player->setDirection(1);
        update(*player, 1, 2, x, y, x, y-1);
    }
    if(direction==2 && map.getValue(x+1,y)==0)      //DOWN
    {
        player->setDirection(2);
        update(*player, 2, 2, x, y, x+1, y);
    }
    if(direction==3 && map.getValue(x,y+1)==0)      //RIGHT
    {
        player->setDirection(3);
        update(*player, 3, 2, x, y, x, y+1);
    }
}

//Prende in input un oggetto Creature che può essere o il player o un nemico,
//d indica la direzione, value indica il valore da mettere sulla mappa in i,j
//x,y le coordinate precedenti sul quale mettere 0
//Fa un semplice aggiornamento sul movimento

void GameManager::update(Creature& e, int d, int value, int x, int y, int i, int j)
{
    map.setValue(value,i,j);
    map.setValue(0,x,y);
    e.move(d);
}

// Il metodo moveEnemy scorre il vector di enemies e per ognuno di loro effettua un random sulla direzione (da 0 a 3)
// se la posizione successiva è libera vengono aggiornate le coordinate sia sull'oggetto map che sul singolo enemy

void GameManager::moveEnemy()
{ 
    int x, y;
    int direction=0;
    int value = 0;
    srand(time(NULL));
    for(int i=0;i<enemies.size();i++)
    {
        x=enemies[i].getX();
        y=enemies[i].getY();
        direction=rand()%4;
        if(map.getValue(x,y)==3)
            value = 3;
        if(map.getValue(x,y)==4)
            value = 4;
        
        if(direction==0 && map.getValue(x-1,y)==0)      //UP
            update(enemies[i], 0, value, x, y, x-1, y);
        if(direction==0 && map.getValue(x-1,y)==2)      
        {
            collisionPlayer(x-1,y);
            update(enemies[i], 0, value, x, y, x-1, y);
        }
        
        if(direction==1 && map.getValue(x,y-1)==0)      //LEFT
            update(enemies[i], 1, value, x, y, x, y-1);

        if(direction==1 && map.getValue(x,y-1)==2)      
        {
            collisionPlayer(x,y-1);
            update(enemies[i], 1, value, x, y, x, y-1);
        }
        
        if(direction==2 && map.getValue(x+1,y)==0)      //DOWN
            update(enemies[i], 2, value, x, y, x+1, y);
        if(direction==2 && map.getValue(x+1,y)==2)     
        {
            collisionPlayer(x+1,y);
            update(enemies[i],2,value,x,y,x+1,y);
        }
        
        if(direction==3 && map.getValue(x,y+1)==0)      //RIGHT
            update(enemies[i], 3, value, x, y, x, y+1);
        if(direction==3 && map.getValue(x,y+1)==2)      
        {
            collisionPlayer(x,y+1);
            update(enemies[i],3,value,x,y,x,y+1);
        }
    }
}



//  Il metodo takeBarrel restituisce true se il player prende il barile, false altrimenti. 
//  Controlla che la posizione successiva al Player sia un 1 o un 5, ovvero un barile, 
//  se così fosse, in quella posizione verrà messo uno 0

bool GameManager::takeBarrel(int direction)
{
    int x = player->getX();
    int y = player->getY();
    if(direction==0 && map.getValue(x-1,y)==1 || map.getValue(x-1,y)==5)      //UP
    {
        if(map.getValue(x-1,y)==1)
            destroy=true;
        if(map.getValue(x-1,y)==5)
            destroy=false;
        map.setValue(0,x-1,y);
        return true;
    }
    else if(direction==1 && map.getValue(x,y-1)==1 ||  map.getValue(x,y-1)==5)      //LEFT
    {
        if(map.getValue(x,y-1)==1)
            destroy = true;
        if(map.getValue(x,y-1)==5)
            destroy=false;
        map.setValue(0,x,y-1);
        return true;
    }
    else if(direction==2 && map.getValue(x+1,y)==1 || map.getValue(x+1,y)==5)      //DOWN
    {
        if(map.getValue(x+1,y)==1)
            destroy = true;
        else
            destroy=false;
        map.setValue(0,x+1,y);
        return true;
    }
    else if(direction==3 && map.getValue(x,y+1)==1 || map.getValue(x,y+1)==5)      //RIGHT
    {
        if(map.getValue(x,y+1)==1)
            destroy=true;
        else
            destroy=false;
        map.setValue(0,x,y+1);
        return true;
    }
    return false;
}

// vengono passati in input le coordinate x,y (successive) e i,j (correnti)
// controlla che la posizione successiva sia libera (== 0) e aggiorna il 
// movimento del barile che è stato lanciato
// altrimenti controlla se il barile deve essere distrutto o meno ed 
// eventualmente lo distrugge

bool GameManager::moveBarrel(int x, int y, int i, int j)
{
    if(map.getValue(x, y)==0)
    {
        if(map.getValue(xBarrel, yBarrel)!=2)
            map.setValue(0,xBarrel, yBarrel);
        xBarrel+=i;
        yBarrel+=j;
        if(destroy)
            map.setValue(1,xBarrel,yBarrel);
        else{
            map.setValue(5,xBarrel,yBarrel);
        }
        return true;
    }
    else
    {   
        if(destroy)
        {
            if(map.getValue(xBarrel, yBarrel)!=2)
                map.setValue(0,xBarrel,yBarrel);
        }
        return false;
    }
       
}

//  Il metodo dropBarrel restituisce true se il barile è stato lanciato, false altrimenti.
//  Controlla che la posizione successiva sia uno 0 e se così fosse, la posizione corrente, 
//      se != 2 viene posta a 0, quella successiva a 1 o 5 

bool GameManager::dropBarrel(int direction)
{   
    if(direction==0)    //UP
    {
        collisionEnemy(xBarrel-1, yBarrel);
        return moveBarrel(xBarrel-1,yBarrel,-1,0);
    }
    
    if(direction==1)    //LEFT
    {
        collisionEnemy(xBarrel, yBarrel-1);
        //se non è DISTRUGGIBILE NON FAI NIENT'ALTRO
        return moveBarrel(xBarrel,yBarrel-1,0,-1);
    }
    
    if(direction==2)    //DOWN
    {
        collisionEnemy(xBarrel+1, yBarrel);
        return moveBarrel(xBarrel+1,yBarrel,1,0);
    }
    
    if(direction==3)    //RIGHT
    {   
        collisionEnemy(xBarrel, yBarrel+1);
        return moveBarrel(xBarrel,yBarrel+1,0,1);
    }
}


// vengono passati in input le coordinate successive al barile
// se è un nemico viene ucciso. se è un corsaro viene fatto
// un respawn sulla mappa

void GameManager::collisionEnemy(int x, int y)
{
    if(map.getValue(x,y) == 3 || map.getValue(x,y) == 4)
    {
       for (int i=0; i<enemies.size(); i++)
            if(enemies[i].getX() == x && enemies[i].getY() == y)
            {
                enemies.erase(enemies.begin()+i);
                break;
            }
                
         if(map.getValue(x,y) == 4)
            respawn(4,x,y); 
         map.setValue(0,x,y);  
    }      
}

// vengono passati in input le coordinate successive rispetto al nemico
// se è il player e ha ancora vite, viene fatto un respawn sulla mappa e
// aggiornata la vita del player con una in meno 

void GameManager::collisionPlayer(int x, int y)
{
    if(player->getLife()>0)
    {
        respawn(2,x,y);
        player->setLife(player->getLife()-1);
    }
}

// prende in input il valore da settare sulla mappa e le coordinate x,y
// da settare a 0. Viene fatto un random sulle coordinate i e j  
// finchè la posizione non risulta libera. In base al valore viene 
// rimesso su mappa o il player o il corsaro

void GameManager::respawn(int value, int x, int y)
{
    map.setValue(0,x,y);
    srand(time(NULL));
    int i=rand()%map.getRows();
    int j=rand()%map.getColumns();
    while(map.getValue(i,j)!=0)
    {
        i=rand()%map.getRows();
        j=rand()%map.getColumns();
    }
    map.setValue(value,i,j);
    if(value == 2)
    {
        player->setX(i);
        player->setY(j);
    }
    if(value == 4)
    {
        Enemy e(4,i,j);
        enemies.push_back(e);
    }
}

// controlla se ci sono altri nemici sulla mappa (return 0)
// se posso caricare altri livelli return 2 
// se non altri livelli da caricare return 1

int GameManager::newLevel()
{
    for(int i=0; i<enemies.size(); i++)
    {
        if(enemies[i].getValue() == 3)
            return 0;
    }
    
    if(map.getCont() < map.getLevelMax())
        map.setCont(map.getCont()+1);
    else 
        return 1;
    enemies.clear();
    map.loadLevel();
    createMap(player->getLife());
    return 2; 
    
}

//controlla se sono in una situazione di gameOver (==0) o ho vinto la partita (==1)
//restituisce 2 se posso continuare a giocare

int GameManager::gameOver()
{
    if(player->getLife()==0)
        return 0;
    else if(player->getLife()>0 && newLevel() == 1)
        return 1;
    return 2;            
}

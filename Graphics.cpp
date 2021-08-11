#include "Graphics.h"

Graphics::Graphics()
{
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		exit(1);
	}

	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize keyboard!\n");
		exit(1);
	}
  
    if(!al_init_image_addon())
    {
        fprintf(stderr, "failed to initialize image addon!\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_event_queue(event_queue);
        exit(-1);
    }
    
    if(!al_init_font_addon()){
        fprintf(stderr, "failed to initialize font!\n");
        exit(1);
    }
    
    if(!al_init_ttf_addon()){
        fprintf(stderr, "failed to initialize ttf!\n");
        exit(1);
    }
	redraw=false;
	doExit=false;

	for(int i=0; i<5; i++)
	  key[i]=false;
	  
	FPS = 60;
	speed = 10.0;

	timer = al_create_timer(7.0 / FPS);
	enemyTimer = al_create_timer(speed / FPS);

	if(!timer) 
	{
		fprintf(stderr, "failed to create timer!\n");
		exit(1);
	}
	if(!enemyTimer)
	{
		fprintf(stderr, "failed to create enemyTimer!\n");
		exit(1);
	}

	al_get_display_mode(0, &disp_data);

	/**** FUNZIONE TRANSFORM ***/
	int width = disp_data.width*100/100; 
	int height = disp_data.height*150/100;
	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	display = al_create_display(width, height);   
	int h = 1080;
	int w = 1024;

	float res_x = width / (float) w;
	float res_y = height / (float) h;
	al_set_window_position(display,width, height);  //Posiziona la finestra nel centro

	al_identity_transform(&resize);
	al_scale_transform(&resize, res_x,res_y);
	al_use_transform(&resize);

	/**** FINE TRANSFORM ****/

	al_set_window_title(display,"PIRATE SHIP HIGEMARU");

	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		exit(1);
	}

	event_queue = al_create_event_queue();

	if(!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        exit(1);
    }
    
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(enemyTimer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(timer);
    al_start_timer(enemyTimer);  
}

void Graphics::Game()
{
	Load();
	Check();
    al_draw_bitmap(start, 0,0,0);
    al_flip_display();
    while(!Start()){}

    int direction=0;
    bool barrel=false;
    bool drop=false;
    while(!doExit)
    {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
      if(ev.type == ALLEGRO_EVENT_TIMER) 
      {
        if(ev.timer.source == timer)
        {              
            if(key[KEY_UP])
            {
               gameManager.movePlayer(0);
               direction=0;
              }   

            if(key[KEY_LEFT])
            {
               gameManager.movePlayer(1);
               direction=1;
            }
            if(key[KEY_DOWN])
            {
               gameManager.movePlayer(2);
               direction=2;
            }
                      
            if(key[KEY_RIGHT])
            {
               gameManager.movePlayer(3);
               direction=3;
            }
            if(key[KEY_A] && !barrel && !drop)
            {
                barrel=gameManager.takeBarrel(direction);
            }
            if(key[KEY_S] && barrel && !drop)
            {
                gameManager.setBarrel(gameManager.getPlayer().getX(),gameManager.getPlayer().getY());  
                gameManager.setDirectionBarrel(direction);
                drop = gameManager.dropBarrel(gameManager.getDirectionBarrel());  
                al_clear_to_color(al_map_rgb(0,0,0));
				Draw();
				al_flip_display();
            }
            if(drop)
            {
                drop = gameManager.dropBarrel(gameManager.getDirectionBarrel());
                if(!drop)
                  barrel=false;
            }
        }
            
     if(ev.type == ALLEGRO_EVENT_TIMER)
            if(ev.timer.source == enemyTimer)
                gameManager.moveEnemy();
        redraw = true;
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        break;
      
       else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
           switch(ev.keyboard.keycode) {
              case ALLEGRO_KEY_UP:
                 key[KEY_UP] = true;
                 break;

              case ALLEGRO_KEY_DOWN:
                 key[KEY_DOWN] = true;
                 break;

              case ALLEGRO_KEY_LEFT: 
                 key[KEY_LEFT] = true;
                 break;

              case ALLEGRO_KEY_RIGHT:
                 key[KEY_RIGHT] = true;
                 break;
               
              case ALLEGRO_KEY_A:
                  key[KEY_A] = true;
                  break;  
                  
              case ALLEGRO_KEY_S:
                  key[KEY_S] = true;
                  break;
           }
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
           switch(ev.keyboard.keycode) {
              case ALLEGRO_KEY_S:
                  key[KEY_S] = false;
                  break;
              
              case ALLEGRO_KEY_A:
                  key[KEY_A] = false;
                  break;
                                  
              case ALLEGRO_KEY_UP:
                 key[KEY_UP] = false;
                 break;

              case ALLEGRO_KEY_DOWN:
                 key[KEY_DOWN] = false;
                 break;

              case ALLEGRO_KEY_LEFT: 
                 key[KEY_LEFT] = false;
                 break;

              case ALLEGRO_KEY_RIGHT:
                 key[KEY_RIGHT] = false;
                 break;

              case ALLEGRO_KEY_ESCAPE:
                 doExit = true;
                 break;
           }
        }

      if(redraw && al_is_event_queue_empty(event_queue)) 
      {
        al_clear_to_color(al_map_rgb(0,0,0));
        if(gameManager.newLevel() == 2)
        {  
            speed -= 3.0;
            al_set_timer_speed(enemyTimer, speed / FPS);
        }
        Draw();
        al_flip_display();
        redraw = false;
      }
      
    }
  }


// il metodo load carica tutte le immagini del gioco
void Graphics::Load()
{
    //caricamento immagini
    start=al_load_bitmap("Immagini/start2.jpg");
    wall=al_load_bitmap("Immagini/wall.png");
    barrel=al_load_bitmap("Immagini/barile.png");
    barrelND=al_load_bitmap("Immagini/barrelND.png");
    lose=al_load_bitmap("Immagini/lose.jpg");
    win=al_load_bitmap("Immagini/win.jpg");

    //caricamento font
    text = al_load_ttf_font("Immagini/life.ttf",25,0);
    if(!text)
    {
        cout << "non carico il font";
        exit(2);
    }
}

// disegna tutte le immagini del gioco
void Graphics::Draw()
{
    if(gameManager.gameOver()==0)
        al_draw_bitmap(lose,0,0,0);
    else if(gameManager.gameOver()==1)
        al_draw_bitmap(win,0,0,0);
    else
    {    
        int size = disp_data.width*50/100;
        int pos = size / 1024;
        int resize = 50;
        
        Map map = gameManager.getMap();
        for (int i=0;i<map.getRows();i++)
        {
            for (int j=0; j<map.getColumns(); j++)
            {
                if(map.getValue(i,j)==1)
                  al_draw_bitmap(barrel,(j+pos)*resize,i*resize+resize/2,0);
                if(map.getValue(i,j)==8)
                  al_draw_bitmap(wall,(j+pos)*resize,i*resize+resize/2,0);
                if(map.getValue(i,j)==2)
                {
                    Player p(i,j);
                    p.draw(gameManager.getPlayer().getDirection(),i*resize+resize/2, (j+pos)*resize);
                }
                if(map.getValue(i,j)==3)
                {
                    Enemy e(3,i,j);
                    e.draw(i*resize+resize/2, (j+pos)*resize);
                }
                if(map.getValue(i,j)==4)
                {
                    Enemy e(4,i,j);
                    e.draw(i*resize+resize/2, (j+pos)*resize);
                }
                if(map.getValue(i,j)==5)
                    al_draw_bitmap(barrelND,(j+pos)*resize,i*resize+resize/2,0);
                
                if(j==3)
                {
                    al_draw_text(text, al_map_rgb(255,255,255),(pos+map.getColumns())*resize+resize,(j+pos)*resize,ALLEGRO_ALIGN_CENTRE, "Lifes: ");
                    al_draw_textf(text, al_map_rgb(255,255,255), (pos+map.getColumns())*resize+resize+resize, (j+pos)*resize, ALLEGRO_ALIGN_CENTRE, "%d",gameManager.getPlayer().getLife());
                }
                if(j==5)
                {
                    al_draw_text(text, al_map_rgb(255,255,255),(pos+map.getColumns())*resize+resize, (j+pos)*resize ,ALLEGRO_ALIGN_CENTRE, "Level: ");
                    al_draw_textf(text, al_map_rgb(255,255,255), (pos+map.getColumns())*resize+resize+resize, (j+pos)*resize, ALLEGRO_ALIGN_CENTRE, "%d",gameManager.getMap().getCont());
                }
            }
        }
    }
}


// se premo Enter avvia il gioco altrimenti rimane in attesa

bool Graphics::Start()
{
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);
    
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        if(ev.keyboard.keycode == ALLEGRO_KEY_ENTER) 
        {
            key[KEY_ENTER] = true;
            key[KEY_ENTER] = false;
            return true;
        }
        return false;
    }
}          

void Graphics::Check()
{
    if(!start)
	{
		fprintf(stderr, "failed to load start!\n");
		exit(1);
	}
	if(!wall)
	{
		fprintf(stderr, "failed to load wall!\n");
		exit(1);
	}
	if(!barrel)
	{
		fprintf(stderr, "failed to load barrel!\n");
		exit(1);
	}
	if(!barrelND)
	{
		fprintf(stderr, "failed to load barrelND!\n");
		exit(1);
	}
	if(!lose)
	{
		fprintf(stderr, "failed to load lose!\n");
		exit(1);
	}
	if(!win)
	{
		fprintf(stderr, "failed to load win!\n");
		exit(1);
	}
}

Graphics::~Graphics()
{
  al_destroy_timer(timer);
  al_destroy_timer(enemyTimer);

  al_destroy_display(display);
  al_destroy_event_queue(event_queue);
}
#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <allegro.h>
#include <stdlib.h>
#include <time.h>
#include "allegroElements.h"
#include "diseno.h"
#include "personajes.h"
#include "disparos.h"

using namespace std;

#define ANCHO 600
#define ALTO  600

BITMAP *buffer		= NULL;
BITMAP *portada		= NULL;
BITMAP *fondo		= NULL;
BITMAP *img_muros	= NULL;
NAVE N;
NAVE E[60];



//---------------------------------------------------
bool limites(struct NAVE E[], int& dir)
{
	for(int i = 0; i < 55; i++)
	{
		if((E[i].x > 520 || E[i].x < 50) && E[i].vida)
		{
			dir *= -1;
			return true;
		}
	}
	return false;
}

void mover_enemigos(struct NAVE E[], int& mov, int& dir)
{
	for(int i = 0; i < 55; i++)
		E[i].x += dir;
	if(++mov == 2)
		mov = 0;
	if(limites(E, dir))
	{
		for(int j = 0; j < 55; j++)
		{
			E[j].y += 10;
		}
	}
}

void cargar_imagenes()
{
	//Cargando imagenes
	printf("Cargando imagenes...\n");
	buffer = create_bitmap(ANCHO, ALTO);
	portada = load_bitmap("img/portada.bmp", NULL);
	fondo = load_bitmap("img/fondo.bmp", NULL);
	img_muros = load_bitmap("img/escudos.bmp", NULL);
}

void finalizarAllegro()
{
	printf("Finalizando todos los recursos icializados.\n");
	remove_timer();
}

void * hilo_nave(void * arg)
{
	while(true)
	{
		N.mueve();
		rest(20);
	}
}

void * hilo_explosionNave(void *arg)
{
	explocion2(N, buffer, fondo);
	pthread_cancel(pthread_self());
}

//---------------------------------------------------

main()
{
	//NAVE N;
	//NAVE E[60];
	pthread_t h_nave;
	pthread_t h_explosion;
	int enem_azar = rand() % 55;
	int mov = 0;
	int dir = -5;
	int vel_juego = 5;

	srand(time(NULL));
	inicia_allegro(ANCHO,ALTO, "SPACE INVADERS");
	cargar_imagenes();

	despliega_menu(portada);

	//------------------------------
	// Empezando con el juego

	//Inicializando la Nave
	N.inicia("img/nave.bmp" , "img/Bala2.bmp", 6, 12, 30, 20, ANCHO / 2, ALTO - 70, -20, 0, 3);
	Balas disparos[N.max_disp];

	//Inicializando y acomodando a los enemigos
	acomoda_enemigos(E);
	Balas disp_E[E[0].max_disp];


	pthread_create(&h_nave, NULL, hilo_nave, NULL);

	while(!key[KEY_ESC])
	{
		clear_to_color(buffer,0x000000);

		if(E[0].temporizador(vel_juego))
			mover_enemigos(E, mov, dir);
		

		N.pinta(buffer, 0, 0);

		if(key[KEY_SPACE] && N.temporizador(10))
			crear_bala(N.n_disp , N.max_disp , disparos , N.x , N.y, N.dir_bala);
		N.dispara(disparos, buffer);


		for(int i = 0; i < 55; i++)
		{
			if(elimina_bala_objeto(N, E[i], disparos))
				explocion1(E[i], buffer);
		}


		pintar_enemigos(E, buffer, mov);
		if(E[enem_azar].n_disp == 0)
		{
			enem_azar = rand() % 55;
			while(E[enem_azar].vida == 0)
				enem_azar = rand() % 55;
		}
		E[enem_azar].dispara(disp_E, buffer);
		


		if(elimina_bala_objeto(E[enem_azar], N, disp_E))
		{
			//Creando hilo para la explosion de la nave (para que no se trabe)
			pthread_create(&h_explosion, NULL, hilo_explosionNave, NULL);
		}

		imprimir_fondo(fondo, buffer);

		blit(buffer, screen , 0,0 ,0,0 ,ANCHO, ALTO);
		rest(20);
	}

	pthread_cancel(h_nave);

	return 0;
}
END_OF_MAIN();


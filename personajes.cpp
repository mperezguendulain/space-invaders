#include <stdio.h>
#include "personajes.h"
#include "disparos.h"
#include "diseno.h"
#include <allegro.h>

#define ANCHO 600
#define ALTO  600


void NAVE::inicia(	const char* ruta_nave , const char* ruta_bala, int _ancho_b,
					int _alto_b, int _ancho_p, int _alto_p, int _x, int _y, 
					int _dir_bala, int _tipo, int _vida)
{
	 x = _x; y = _y;
	 n_disp = 0; max_disp = 4;
	 img_nav = load_bitmap(ruta_nave,NULL);
	 img_bala = load_bitmap(ruta_bala,NULL);
	 tick = 0;
	 ancho_b = _ancho_b;
	 alto_b = _alto_b;
	 ancho_p = _ancho_p;
	 alto_p = _alto_p;
	 dir_bala = _dir_bala;
	 tipo = _tipo;
	 vida = _vida;
	 exp_enem = load_bitmap("img/pum_enemigo.bmp", NULL);
}

bool NAVE::temporizador(int tiempo){
	 tick++;
	 if(tick == tiempo){
		 tick = 0;
		 return true;
	 }
	 return false;

}

void NAVE::pinta(BITMAP* buffer, int ix, int iy){
	masked_blit(img_nav,buffer, ix * ancho_p, iy * alto_p,x,y,ancho_p,alto_p);
}

void NAVE::mueve(){
	 if(key[KEY_LEFT]) x -= 5;
	 if(key[KEY_RIGHT]) x += 5;

}

void NAVE::dispara(struct Balas disparos[], BITMAP* buffer)
{
	if(tipo)
		crear_bala(n_disp , max_disp , disparos , x , y, dir_bala);
	pintar_bala(n_disp , max_disp , disparos , buffer , img_bala, ancho_b, alto_b);
	elimina_bala(n_disp , max_disp , disparos , ANCHO , ALTO);
}

void acomoda_enemigos(struct NAVE E[])
{
	int indice = -1;
	int _tipo = 0;
	for(int i = 0; i < 5; i++)
	{
		_tipo++;
		if(_tipo == 4)
			_tipo = 1;
		for(int j = 0; j < 11; j++)
		{
			indice++;
			E[indice].inicia("img/enemigos.bmp" , "img/Bala_enem.bmp", 6, 12, 25, 20,
							j * 30 + 140, i * 24 + 130, 1, _tipo, 1);
		}
	}
}


void pintar_enemigos(struct NAVE E[], BITMAP* buffer, int mov)
{
	int indice = -1;
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 11; j++)
		{
			indice++;
			if(E[indice].vida > 0)
				E[indice].pinta(buffer, mov, E[indice].tipo - 1);
		}
	}
}

void explocion1(struct NAVE E, BITMAP* buffer)
{
	BITMAP* parche = create_bitmap(25, 20);
	clear_to_color(parche, 0x000000);
	blit(parche, buffer, 0, 0, E.x, E.y, 25, 20);
	masked_blit(E.exp_enem, buffer, 0, 0, E.x - 10, E.y, 41, 34);
	rest(50);
}

void explocion2(struct NAVE N, BITMAP* buffer, BITMAP* fondo)
{
	BITMAP* parche = create_bitmap(30, 20);
	clear_to_color(parche, 0x000000);
	for(int j = 0; j < 10; j++)
	{
		for(int i = 1; i <= 2; i++)
		{
			blit(parche, buffer, 0, 0, N.x, N.y, 30, 20);
			masked_blit(N.img_nav, buffer, i * 30, 0, N.x, N.y, 30, 20);
			imprimir_fondo(fondo, buffer);
			blit(buffer, screen, 0, 0, 0, 0, ANCHO, ALTO);
			rest(50);
		}
	}
}
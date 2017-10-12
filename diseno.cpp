#include "diseno.h"
#include <stdio.h>
#include <allegro.h>

void despliega_menu(BITMAP* p)
{
	printf("Entro a dibujar el menu\n");
	int parpadeo = 0;
	int y = 0;
	int cont = 0;
	bool salida = false;
	bool carga = false;

	while(!salida)
	{
		if(parpadeo < 400)
			blit(p, screen, 0, y, 0, 100, 600, 400);
		else
			blit(p, screen, 600, y, 0, 100, 600, 400);
		
		if(key[KEY_ENTER])
		{
			y = 400;
			carga = true;
		}
		if(carga)
			cont++;
		if(cont > 500)
			salida = true;
		rest(5);
		if(++parpadeo == 800)
			parpadeo = 0;
	}
	clear_to_color(screen, 0x000000);
}

void imprimir_fondo(BITMAP* fondo, BITMAP* buffer)
{
	masked_blit(fondo, buffer, 0, 0, 0, 0, 600, 600);
}
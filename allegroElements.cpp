#include "allegroElements.h"
#include <allegro.h>


void inicia_allegro(int ANCHO_ , int ALTO_, const char * titulo)
{
	allegro_init();
	install_keyboard();
	install_timer();

	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, ANCHO_, ALTO_, 0, 0);
	set_window_title(titulo);
}

int inicia_audio(int izquierda, int derecha)
{
	if(install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0)
	{
		allegro_message("Error: inicializando sistema de sonido\n%s\n", allegro_error);
		return 1;
	}
	set_volume(izquierda, derecha);
}
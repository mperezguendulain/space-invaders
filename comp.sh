#!/bin/bash
# -*- ENCODING: UTF-8 -*-

rm space_invaders

echo "Compilando Poryecto: Space Invaders"

gcc -c allegroElements.cpp -o allegroElements `pkg-config --cflags --libs allegro`

gcc -c diseno.cpp -o diseno `pkg-config --cflags --libs allegro`

gcc -c personajes.cpp -o personajes `pkg-config --cflags --libs allegro`

gcc -c disparos.cpp -o disparos `pkg-config --cflags --libs allegro`


#Compilacion Final
g++ main.cpp -o space_invaders `pkg-config --cflags --libs allegro` allegroElements diseno personajes disparos -lpthread

./space_invaders

exit

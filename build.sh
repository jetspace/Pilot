gcc -std=c99 src-gtk/main.c `pkg-config --libs --cflags gtk+-3.0` -o pilot-gtk -Wall

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 21:16:51 by fwisp             #+#    #+#             */
/*   Updated: 2020/07/16 14:58:23 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <stdbool.h>

void				manage_processes(t_sdl sdl, int argc, char **argv)
{
	int				i;
	t_scene			scene;
	SDL_Event		event;
	
	// sdl.cl_inst = initcl();
	// SDL_PollEvent(&event);
	if (!construct_scene(argv[1], &scene))
		ft_draw(sdl, scene);
	if (argc > 2)
	{
		i = 1;
		while (++i < argc)
		{
			SDL_PollEvent(&event);
			sleep(1);
			if (!construct_scene(argv[i], &scene))
				ft_draw(sdl, scene);
		}
	}
	// controls(sdl, scene);
	SDL_FreeSurface(sdl.screen);
	SDL_DestroyWindow(sdl.window);
}

gboolean	manage_events_gtk(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
    if (event->keyval == GDK_KEY_Escape){
        gtk_main_quit();
        return TRUE;
    }
    return FALSE;
}

int					main(int argc, char **argv)
{
	t_sdl			sdl;
	GtkWindow *gtk_window;
	GtkWidget *gtk_da;
	void *gdk_window;
	void *window_id;

	gtk_init(&argc, &argv);
    gtk_window = (GtkWindow*)gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(gtk_window, "RT");

    gtk_da = gtk_drawing_area_new();
	gtk_widget_set_size_request (gtk_da, C_W, C_H);
	gtk_widget_add_events(gtk_da, GDK_KEY_PRESS_MASK);
    gtk_container_add(GTK_CONTAINER(gtk_window), gtk_da);
    gtk_widget_show_all(GTK_WIDGET(gtk_window));

    gdk_window = gtk_widget_get_window(GTK_WIDGET(gtk_da));
    window_id = (void*)(intptr_t)GDK_WINDOW_XID(gdk_window);

	SDL_Init(SDL_INIT_VIDEO);
	// SDL_CreateWindowAndRenderer(C_W, C_H, 0, &(sdl.window), &(sdl.renderer));
	sdl.window = SDL_CreateWindowFrom(window_id);
	SDL_SetWindowSize(sdl.window, C_W, C_H);
	sdl.renderer = SDL_CreateRenderer(sdl.window, -1, 0);
	sdl.screen = SDL_CreateRGBSurface(0, C_W, C_H, 32, 0x00FF0000, \
							0x0000FF00, 0x000000FF, 0xFF000000);
	sdl.texture = SDL_CreateTexture(sdl.renderer, SDL_PIXELFORMAT_ARGB8888, \
								SDL_TEXTUREACCESS_STREAMING, C_W, C_H);
	if (argc < 2)
		return (0);
	g_signal_connect (G_OBJECT (gtk_window), "delete_event", G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect (G_OBJECT (gtk_window), "destroy", G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect (G_OBJECT (gtk_window), "key_press_event", G_CALLBACK (manage_events_gtk), NULL);
	manage_processes(sdl, argc, argv);
	gtk_main();
	
	
	SDL_Quit();
	return (0);
}

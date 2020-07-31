/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 21:16:51 by fwisp             #+#    #+#             */
/*   Updated: 2020/07/31 16:12:19 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

// void	manage_events_gtk(GtkWidget *widget, GdkEventKey *event, t_controls *ctrl)
// {	
// 	t_scene	scene;
// 	t_sdl	sdl;

// 	scene = ctrl->scene;
// 	sdl = ctrl->sdl;
// 	controls2(sdl, &scene, event);
//     return ;
// }

void				run_gui(t_sdl *sdl)//, GObject	**gtk_window, GtkBuilder **builder)
{
	// GObject		*gdk_window;
	// void		*window_id;

	// SDL_Init(SDL_INIT_VIDEO);
	// gtk_init(NULL, NULL);
	// *builder = gtk_builder_new();
  	// gtk_builder_add_from_file(*builder, "src/RTui.glade", NULL);
  	// *gtk_window = gtk_builder_get_object (*builder, "window");
    // gdk_window = gtk_widget_get_window(GTK_WIDGET(\
	// 					gtk_builder_get_object(*builder, "gdkda")));
    // window_id = (void*)(intptr_t)GDK_WINDOW_XID(gdk_window);
	// sdl->window = SDL_CreateWindowFrom(window_id);
	// SDL_SetWindowSize(sdl->window, C_W, C_H);
	// sdl->renderer = SDL_CreateRenderer(sdl->window, -1, 0);
	SDL_CreateWindowAndRenderer(C_W, C_H, 0, &(sdl->window), &(sdl->renderer));
	sdl->screen = SDL_CreateRGBSurface(0, C_W, C_H, 32, 0x00FF0000,\
							0x0000FF00, 0x000000FF, 0xFF000000);
	sdl->texture = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_ARGB8888,\
								SDL_TEXTUREACCESS_STREAMING, C_W, C_H);
	// g_signal_connect(G_OBJECT (*gtk_window), "delete_event", \
	// 									G_CALLBACK(gtk_main_quit), NULL);
	// g_signal_connect(G_OBJECT (*gtk_window), "destroy", \
	// 									G_CALLBACK(gtk_main_quit), NULL);
	sdl->cl_inst = initcl();
}

void				quit_sdl(t_sdl *sdl)
{
	SDL_FreeSurface(sdl->screen);
	SDL_DestroyWindow(sdl->window);
	SDL_Quit();
}

int					main(int argc, char **argv)
{
	t_sdl		sdl;
	t_scene		scene;
	// GtkBuilder	*builder;
  	// GObject		*gtk_window;
	t_controls	ctrl;


	if (argc < 2)
		return (0);
	run_gui(&sdl);//, &gtk_window, &builder);
	if (!construct_scene(argv[1], &scene))
		ft_draw(sdl, scene);
	ctrl.scene = scene;
	ctrl.sdl = sdl;
	// g_signal_connect(G_OBJECT (gtk_window), "key_press_event", \
	// 									G_CALLBACK(manage_events_gtk), (gpointer)&ctrl);
	controls(sdl, scene);
	// gtk_main();
	releasecl(&(sdl.cl_inst));
	quit_sdl(&sdl);
	return (0);
}

/*
static void
print_hello (GtkWidget *widget,
             gpointer   data)
{
  g_print ("Hello World\n");
}

int
main (int   argc,
      char *argv[])
{
  GtkBuilder *builder;
  GObject *window;
  GObject *button;
  GError *error = NULL;

  gtk_init (&argc, &argv);

  builder = gtk_builder_new();
  if (gtk_builder_add_from_file (builder, "src/interface.ui", &error) == 0)
    {
      g_printerr ("Error loading file: %s\n", error->message);
      g_clear_error (&error);
      return 1;
    }

  window = gtk_builder_get_object (builder, "window");
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  button = gtk_builder_get_object (builder, "button1");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);

  button = gtk_builder_get_object (builder, "button2");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);

  button = gtk_builder_get_object (builder, "quit");
  g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);

  gtk_main ();

  return 0;
}
*/
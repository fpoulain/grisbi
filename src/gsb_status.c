/* ************************************************************************** */
/*                                                                            */
/*     Copyright (C)    2005-2008 Benjamin Drieu (bdrieu@april.org)           */
/*          http://www.grisbi.org                                             */
/*                                                                            */
/*  This program is free software; you can redistribute it and/or modify      */
/*  it under the terms of the GNU General Public License as published by      */
/*  the Free Software Foundation; either version 2 of the License, or         */
/*  (at your option) any later version.                                       */
/*                                                                            */
/*  This program is distributed in the hope that it will be useful,           */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/*  GNU General Public License for more details.                              */
/*                                                                            */
/*  You should have received a copy of the GNU General Public License         */
/*  along with this program; if not, write to the Free Software               */
/*  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */
/*                                                                            */
/* ************************************************************************** */


/**
 * \file gsb_status.c
 * Various routines that implement the status bar.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "include.h"

/*START_INCLUDE*/
#include "gsb_status.h"
#include "structures.h"
#include "utils.h"
/*END_INCLUDE*/

/*START_STATIC*/
/*END_STATIC*/

/*START_EXTERN*/
/*END_EXTERN*/

/** Status bar displayed in the bottom of Grisbi window.  */
static GtkWidget *main_statusbar = NULL;

/** Context ID from the GtkStatusBar. */
static guint context_id;

/** Message ID from the GtkStatusBar.  */
static guint message_id = -1;

/** Optional progress bar in main status bar.  */
/*
static GtkWidget * progress_bar = NULL;
*/

/** Timer ID of the timeout responsible for updating the
 * GtkProgressBar.  */
/*
static gint timer_id;
*/

/** Window under cursor at the time the cursor animation changed. */
static GdkWindow * tracked_window;

/**
 * Display a message in the status bar.
 *
 * \param message	Message to display.
 */
void gsb_status_message ( gchar * message )
{
    if ( ! main_statusbar || ! GTK_IS_STATUSBAR ( main_statusbar ) )
	return;

    gsb_status_clear ();
    message_id = gtk_statusbar_push ( GTK_STATUSBAR (main_statusbar), context_id, message );

    /* force status message to be displayed NOW */
    update_gui ( );
}



/**
 * Clear any message in the status bar.
 */
void gsb_status_clear (  )
{
    if ( ! main_statusbar || ! GTK_IS_STATUSBAR ( main_statusbar ) )
	return;

    if ( message_id >= 0 )
    {
	gtk_statusbar_remove ( GTK_STATUSBAR (main_statusbar), context_id, message_id );
	message_id = -1;
    }

    /* force status message to be displayed NOW */
    update_gui ( );
}


/**
 * Change current cursor to a animated watch (if animation supported
 * by environment).
 *
 * \param force_update		Call a gtk iteration to ensure cursor
 *				is updated.  May cause trouble if
 *				called from some signal handlers.
 */
void gsb_status_wait ( gboolean force_update )
{
    GdkDeviceManager *device_manager;
    GdkDisplay *display;
    GdkDevice *device;
    GdkWindow *current_window;
    GdkWindow *run_window;

    run_window = gtk_widget_get_window (GTK_WIDGET (run.window));
    display = display = gdk_window_get_display (run_window);
    device_manager = gdk_display_get_device_manager (display);
    device = gdk_device_manager_get_client_pointer (device_manager);

    gdk_window_set_cursor (run_window, gdk_cursor_new_for_display (display, GDK_WATCH));

    current_window = gdk_device_get_window_at_position (device, NULL, NULL);

    if ( current_window && GDK_IS_WINDOW ( current_window )
     &&
     current_window != run_window )
    {
	GdkWindow * parent = gdk_window_get_toplevel ( current_window );

	if ( parent && parent != current_window )
	{
	    current_window = parent;
	}

	gdk_window_set_cursor ( current_window,
				gdk_cursor_new_for_display ( gdk_display_get_default ( ),
							     GDK_WATCH ) );

	tracked_window = current_window;
    }

    if ( force_update )
	update_gui ( );
}


/**
 * Change current cursor to default cursor.
 *
 * \param force_update		Call a gtk iteration to ensure cursor
 *				is updated.  May cause trouble if
 *				called from some signal handlers.
 */
void gsb_status_stop_wait ( gboolean force_update )
{
    if ( ! run.window )
	return;

    gdk_window_set_cursor ( gtk_widget_get_window ( GTK_WIDGET ( run.window ) ), NULL );

    if ( tracked_window && gdk_window_is_visible ( tracked_window ) )
    {
	gdk_window_set_cursor ( tracked_window, NULL );
	tracked_window = NULL;
    }

    if ( force_update )
	update_gui ( );
}


/**
 *
 *
 * \param
 *
 * \return
 * */
GtkWidget *gsb_status_get_status_bar ( void )
{
    return main_statusbar;
}

void gsb_status_set_status_bar (GtkWidget *status_bar)
{
    main_statusbar = status_bar;
}

/**
 *
 *
 * \param
 *
 * \return
 * */
/* Local Variables: */
/* c-basic-offset: 4 */
/* End: */

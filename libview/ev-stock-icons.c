/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* Stock icons for Atril
 *
 * Copyright (C) 2003 Martin Kretzschmar
 *
 * Author:
 *   Martin Kretzschmar <Martin.Kretzschmar@inf.tu-dresden.de>
 *
 * Atril is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Atril is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
 * USA.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "ev-stock-icons.h"

#include <gtk/gtk.h>

typedef struct {
  char *stock_id;
  char *icon;
} EvStockIcon;

/* Atril stock icons */
static const EvStockIcon stock_icons[] = {
    {EV_STOCK_ZOOM, "zoom"},
    {EV_STOCK_ZOOM_PAGE, "zoom-fit-height"},
    {EV_STOCK_ZOOM_WIDTH, "zoom-fit-width"},
    {EV_STOCK_VIEW_DUAL, "view-page-facing"},
    {EV_STOCK_VIEW_CONTINUOUS, "view-page-continuous"},
    {EV_STOCK_ROTATE_LEFT, "object-rotate-left"},
    {EV_STOCK_ROTATE_RIGHT, "object-rotate-right"},
    {EV_STOCK_RUN_PRESENTATION, "x-office-presentation"},
    {EV_STOCK_VISIBLE, "eye"},
    {EV_STOCK_RESIZE_SE, "resize-se"},
    {EV_STOCK_RESIZE_SW, "resize-sw"},
    {EV_STOCK_CLOSE, "close"},
    {EV_STOCK_INVERTED_COLORS, "stock_filters-invert"},
    {EV_STOCK_ATTACHMENT, "mail-attachment"},
    {EV_STOCK_SEND_TO, "document-send"},
};

#define EV_ICONS_PATH ATRILDATADIR "/icons"

static void ev_stock_icons_add_icons_path_for_screen(GdkScreen *screen) {
  GtkIconTheme *icon_theme;

  icon_theme = screen ? gtk_icon_theme_get_for_screen(screen)
                      : gtk_icon_theme_get_default();
  if (icon_theme) {
    gchar **path = NULL;
    gint n_paths;
    gint i;

    /* GtkIconTheme will then look in Atril custom hicolor dir
     * for icons as well as the standard search paths
     */
    gtk_icon_theme_get_search_path(icon_theme, &path, &n_paths);
    for (i = n_paths - 1; i >= 0; i--) {
      if (g_ascii_strcasecmp(EV_ICONS_PATH, path[i]) == 0) break;
    }

    if (i < 0) gtk_icon_theme_append_search_path(icon_theme, EV_ICONS_PATH);

    g_strfreev(path);
  }
}

/**
 * ev_stock_icons_init:
 *
 * Creates a new icon factory, adding the base stock icons to it.
 */
void ev_stock_icons_init(void) {
  GtkIconFactory *factory;
  GtkIconSource *source;
  gint i;

  factory = gtk_icon_factory_new();
  gtk_icon_factory_add_default(factory);

  source = gtk_icon_source_new();

  for (i = 0; i < G_N_ELEMENTS(stock_icons); i++) {
    GtkIconSet *set;

    gtk_icon_source_set_icon_name(source, stock_icons[i].icon);

    set = gtk_icon_set_new();
    gtk_icon_set_add_source(set, source);

    gtk_icon_factory_add(factory, stock_icons[i].stock_id, set);
    gtk_icon_set_unref(set);
  }

  gtk_icon_source_free(source);

  g_object_unref(G_OBJECT(factory));

  ev_stock_icons_add_icons_path_for_screen(gdk_screen_get_default());
}

void ev_stock_icons_set_screen(GdkScreen *screen) {
  g_return_if_fail(GDK_IS_SCREEN(screen));

  ev_stock_icons_add_icons_path_for_screen(screen);
}

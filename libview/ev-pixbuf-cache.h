/* this file is part of atril, a mate document viewer
 *
 *  Copyright (C) 2005 Red Hat, Inc
 *
 * Atril is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Atril is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
 * USA.
 */

/* This File is basically an extention of EvView, and is out here just to keep
 * ev-view.c from exploding.
 */

#if !defined(__EV_ATRIL_VIEW_H_INSIDE__) && !defined(ATRIL_COMPILATION)
#error "Only <atril-view.h> can be included directly."
#endif

#ifndef __EV_PIXBUF_CACHE_H__
#define __EV_PIXBUF_CACHE_H__

#include <atril-document.h>
#include <atril-view.h>
#include <glib-object.h>
#include <glib.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define EV_TYPE_PIXBUF_CACHE (ev_pixbuf_cache_get_type())
#define EV_PIXBUF_CACHE(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), EV_TYPE_PIXBUF_CACHE, EvPixbufCache))
#define EV_IS_PIXBUF_CACHE(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), EV_TYPE_PIXBUF_CACHE))

/* The coordinates in the rect here are at scale == 1.0, so that we can ignore
 * resizings.  There is one per page, maximum.
 */
typedef struct {
  int page;
  EvRectangle rect;
  cairo_region_t *covered_region;
  EvSelectionStyle style;
} EvViewSelection;

typedef struct _EvPixbufCache EvPixbufCache;
typedef struct _EvPixbufCacheClass EvPixbufCacheClass;

GType ev_pixbuf_cache_get_type(void) G_GNUC_CONST;
EvPixbufCache *ev_pixbuf_cache_new(GtkWidget *view, EvDocumentModel *model,
                                   gsize max_size);
void ev_pixbuf_cache_set_max_size(EvPixbufCache *pixbuf_cache, gsize max_size);
void ev_pixbuf_cache_set_page_range(EvPixbufCache *pixbuf_cache,
                                    gint start_page, gint end_page,
                                    GList *selection_list);
cairo_surface_t *ev_pixbuf_cache_get_surface(EvPixbufCache *pixbuf_cache,
                                             gint page);
void ev_pixbuf_cache_clear(EvPixbufCache *pixbuf_cache);
void ev_pixbuf_cache_style_changed(EvPixbufCache *pixbuf_cache);
void ev_pixbuf_cache_reload_page(EvPixbufCache *pixbuf_cache,
                                 cairo_region_t *region, gint page,
                                 gint rotation, gdouble scale);
void ev_pixbuf_cache_set_inverted_colors(EvPixbufCache *pixbuf_cache,
                                         gboolean inverted_colors);
/* Selection */
cairo_surface_t *ev_pixbuf_cache_get_selection_surface(
    EvPixbufCache *pixbuf_cache, gint page, gfloat scale);
cairo_region_t *ev_pixbuf_cache_get_selection_region(
    EvPixbufCache *pixbuf_cache, gint page, gfloat scale);
void ev_pixbuf_cache_set_selection_list(EvPixbufCache *pixbuf_cache,
                                        GList *selection_list);
GList *ev_pixbuf_cache_get_selection_list(EvPixbufCache *pixbuf_cache);

G_END_DECLS

#endif /* __EV_PIXBUF_CACHE_H__ */

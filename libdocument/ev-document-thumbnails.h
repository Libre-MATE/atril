/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8;
 * c-indent-level: 8 -*- */
/*
 *  Copyright (C) 2004 Anders Carlsson
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
 * USA.
 *
 */

#if !defined(__EV_ATRIL_DOCUMENT_H_INSIDE__) && !defined(ATRIL_COMPILATION)
#error "Only <atril-document.h> can be included directly."
#endif

#ifndef EV_DOCUMENT_THUMBNAILS_H
#define EV_DOCUMENT_THUMBNAILS_H

#include <gdk-pixbuf/gdk-pixbuf.h>
#include <glib-object.h>
#include <glib.h>

#include "ev-render-context.h"

G_BEGIN_DECLS

#define EV_TYPE_DOCUMENT_THUMBNAILS (ev_document_thumbnails_get_type())
G_DECLARE_INTERFACE(EvDocumentThumbnails, ev_document_thumbnails, EV,
                    DOCUMENT_THUMBNAILS, GObject);

struct _EvDocumentThumbnailsInterface {
  GTypeInterface base_iface;

  /* Methods  */
  GdkPixbuf *(*get_thumbnail)(EvDocumentThumbnails *document,
                              EvRenderContext *rc, gboolean border);
  void (*get_dimensions)(EvDocumentThumbnails *document, EvRenderContext *rc,
                         gint *width, gint *height);
};

GdkPixbuf *ev_document_thumbnails_get_thumbnail(EvDocumentThumbnails *document,
                                                EvRenderContext *rc,
                                                gboolean border);
void ev_document_thumbnails_get_dimensions(EvDocumentThumbnails *document,
                                           EvRenderContext *rc, gint *width,
                                           gint *height);
G_END_DECLS

#endif /* EV_DOCUMENT_THUMBNAILS_H */

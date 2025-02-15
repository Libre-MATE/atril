/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8;
 * c-indent-level: 8 -*- */
/*
 *  Copyright (C) 2004 Red Hat, Inc.
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
 *  $Id$
 */

#if !defined(__EV_ATRIL_DOCUMENT_H_INSIDE__) && !defined(ATRIL_COMPILATION)
#error "Only <atril-document.h> can be included directly."
#endif

#ifndef EV_DOCUMENT_FIND_H
#define EV_DOCUMENT_FIND_H

#include <glib-object.h>
#include <glib.h>

#include "ev-document.h"

G_BEGIN_DECLS

#define EV_TYPE_DOCUMENT_FIND (ev_document_find_get_type())
G_DECLARE_INTERFACE(EvDocumentFind, ev_document_find, EV, DOCUMENT_FIND,
                    GObject);

struct _EvDocumentFindInterface {
  GTypeInterface base_iface;

  /* Methods */
  GList *(*find_text)(EvDocumentFind *document_find, EvPage *page,
                      const gchar *text, gboolean case_sensitive);

  guint (*check_for_hits)(EvDocumentFind *document_find, EvPage *page,
                          const gchar *text, gboolean case_sensitive);
};

GList *ev_document_find_find_text(EvDocumentFind *document_find, EvPage *page,
                                  const gchar *text, gboolean case_sensitive);

guint ev_document_find_check_for_hits(EvDocumentFind *document_find,
                                      EvPage *page, const gchar *text,
                                      gboolean case_sensitive);
G_END_DECLS

#endif /* EV_DOCUMENT_FIND_H */

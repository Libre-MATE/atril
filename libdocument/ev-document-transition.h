/* ev-document-transition.h
 *  this file is part of atril, a mate document viewer
 *
 * Copyright (C) 2006 Carlos Garcia Campos <carlosgc@gnome.org>
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

#if !defined(__EV_ATRIL_DOCUMENT_H_INSIDE__) && !defined(ATRIL_COMPILATION)
#error "Only <atril-document.h> can be included directly."
#endif

#ifndef EV_DOCUMENT_TRANSITION_H
#define EV_DOCUMENT_TRANSITION_H

#include <glib-object.h>
#include <glib.h>

#include "ev-document.h"
#include "ev-transition-effect.h"

G_BEGIN_DECLS

#define EV_TYPE_DOCUMENT_TRANSITION (ev_document_transition_get_type())
G_DECLARE_INTERFACE(EvDocumentTransition, ev_document_transition, EV,
                    DOCUMENT_TRANSITION, GObject);

struct _EvDocumentTransitionInterface {
  GTypeInterface base_iface;

  /* Methods  */
  gdouble (*get_page_duration)(EvDocumentTransition *document_trans, gint page);
  EvTransitionEffect *(*get_effect)(EvDocumentTransition *document_trans,
                                    gint page);
};

gdouble ev_document_transition_get_page_duration(
    EvDocumentTransition *document_trans, gint page);
EvTransitionEffect *ev_document_transition_get_effect(
    EvDocumentTransition *document_trans, gint page);

G_END_DECLS

#endif /* EV_DOCUMENT_TRANSITION_H */

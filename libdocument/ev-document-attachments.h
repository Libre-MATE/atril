/* ev-document-attachments.h
 *  this file is part of atril, a mate document viewer
 *
 * Copyright (C) 2009 Carlos Garcia Campos  <carlosgc@gnome.org>
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

#ifndef EV_DOCUMENT_ATTACHMENTS_H
#define EV_DOCUMENT_ATTACHMENTS_H

#include <glib-object.h>
#include <glib.h>

G_BEGIN_DECLS

#define EV_TYPE_DOCUMENT_ATTACHMENTS (ev_document_attachments_get_type())
G_DECLARE_INTERFACE(EvDocumentAttachments, ev_document_attachments, EV,
                    DOCUMENT_ATTACHMENTS, GObject);

struct _EvDocumentAttachmentsInterface {
  GTypeInterface base_iface;

  /* Methods  */
  gboolean (*has_attachments)(EvDocumentAttachments *document_attachments);
  GList *(*get_attachments)(EvDocumentAttachments *document_attachments);
};

gboolean ev_document_attachments_has_attachments(
    EvDocumentAttachments *document_attachments);
GList *ev_document_attachments_get_attachments(
    EvDocumentAttachments *document_attachments);

G_END_DECLS

#endif /* EV_DOCUMENT_ATTACHMENTS_H */

/* ev-document-security.h
 *  this file is part of atril, a mate pdf viewer
 *
 * Copyright (C) 2005 Red Hat, Inc.
 *
 * Author:
 *   Jonathan Blandford <jrb@alum.mit.edu>
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

#ifndef EV_DOCUMENT_SECURITY_H
#define EV_DOCUMENT_SECURITY_H

#include <glib-object.h>
#include <glib.h>

#include "ev-document.h"

G_BEGIN_DECLS

#define EV_TYPE_DOCUMENT_SECURITY (ev_document_security_get_type())
G_DECLARE_INTERFACE(EvDocumentSecurity, ev_document_security, EV,
                    DOCUMENT_SECURITY, GObject);

struct _EvDocumentSecurityInterface {
  GTypeInterface base_iface;

  /* Methods  */
  gboolean (*has_document_security)(EvDocumentSecurity *document_security);
  void (*set_password)(EvDocumentSecurity *document_security,
                       const char *password);
};

gboolean ev_document_security_has_document_security(
    EvDocumentSecurity *document_security);
void ev_document_security_set_password(EvDocumentSecurity *document_security,
                                       const char *password);

G_END_DECLS

#endif /* EV_DOCUMENT_SECURITY_H */

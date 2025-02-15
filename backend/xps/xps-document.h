/* this file is part of atril, a mate document viewer
 *
 * Copyright (C) 2010 Carlos Garcia Campos <carlosgc@gnome.org>
 *               2012 Leandro Vital <leandro.vital@yahoo.com.br>
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

#ifndef __XPS_DOCUMENT_H__
#define __XPS_DOCUMENT_H__

#include <glib-object.h>
#include <glib.h>

#include "ev-document.h"

G_BEGIN_DECLS

#define XPS_TYPE_DOCUMENT (xps_document_get_type())
#define XPS_DOCUMENT(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), XPS_TYPE_DOCUMENT, XPSDocument))
#define XPS_DOCUMENT_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass), XPS_TYPE_DOCUMENT, XPSDocumentClass))
#define XPS_IS_DOCUMENT(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), XPS_TYPE_DOCUMENT))
#define XPS_DOCUMENT_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS((obj), XPS_TYPE_DOCUMENT, XPSDocumentClass))

typedef struct _XPSDocument XPSDocument;
typedef struct _XPSDocumentClass XPSDocumentClass;

GType xps_document_get_type(void) G_GNUC_CONST;

G_MODULE_EXPORT GType register_atril_backend(GTypeModule *module);

G_END_DECLS

#endif /* __XPS_DOCUMENT_H__ */

/* ev-document-print.h
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef EV_DOCUMENT_PRINT_H
#define EV_DOCUMENT_PRINT_H

#include <glib-object.h>
#include <cairo.h>

#include "ev-page.h"

G_BEGIN_DECLS

#define EV_TYPE_DOCUMENT_PRINT (ev_document_print_get_type ())
G_DECLARE_INTERFACE (EvDocumentPrint, ev_document_print, EV, DOCUMENT_PRINT, GObject);
struct _EvDocumentPrintInterface
{
	GTypeInterface base_iface;

	/* Methods  */
	void (* print_page) (EvDocumentPrint *document_print,
			     EvPage          *page,
			     cairo_t         *cr);
};

void  ev_document_print_print_page (EvDocumentPrint *document_print,
				    EvPage          *page,
				    cairo_t         *cr);

G_END_DECLS

#endif /* EV_DOCUMENT_PRINT_H */

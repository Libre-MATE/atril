/* ev-document-fonts.h
 *  this file is part of atril, a mate document_fonts viewer
 *
 * Copyright (C) 2004 Red Hat, Inc.
 *
 * Author:
 *   Marco Pesenti Gritti <mpg@redhat.com>
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "ev-document-fonts.h"

G_DEFINE_INTERFACE(EvDocumentFonts, ev_document_fonts, 0)

static void ev_document_fonts_default_init(EvDocumentFontsInterface *klass) {}

double ev_document_fonts_get_progress(EvDocumentFonts *document_fonts) {
  EvDocumentFontsInterface *iface = EV_DOCUMENT_FONTS_GET_IFACE(document_fonts);

  return iface->get_progress(document_fonts);
}

gboolean ev_document_fonts_scan(EvDocumentFonts *document_fonts, int n_pages) {
  EvDocumentFontsInterface *iface = EV_DOCUMENT_FONTS_GET_IFACE(document_fonts);

  return iface->scan(document_fonts, n_pages);
}

void ev_document_fonts_fill_model(EvDocumentFonts *document_fonts,
                                  GtkTreeModel *model) {
  EvDocumentFontsInterface *iface = EV_DOCUMENT_FONTS_GET_IFACE(document_fonts);

  iface->fill_model(document_fonts, model);
}

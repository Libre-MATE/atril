/* this file is part of atril, a mate document viewer
 *
 *  Copyright (C) 2004 Martin Kretzschmar
 *
 *  Author:
 *    Martin Kretzschmar <martink@gnome.org>
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

#ifndef EV_FILE_EXPORTER_H
#define EV_FILE_EXPORTER_H

#include <glib-object.h>
#include <glib.h>

#include "ev-render-context.h"

G_BEGIN_DECLS

typedef enum {
  EV_FILE_FORMAT_UNKNOWN,
  EV_FILE_FORMAT_PS,
  EV_FILE_FORMAT_PDF
} EvFileExporterFormat;

typedef enum {
  EV_FILE_EXPORTER_CAN_PAGE_SET = 1 << 0,
  EV_FILE_EXPORTER_CAN_COPIES = 1 << 1,
  EV_FILE_EXPORTER_CAN_COLLATE = 1 << 2,
  EV_FILE_EXPORTER_CAN_REVERSE = 1 << 3,
  EV_FILE_EXPORTER_CAN_SCALE = 1 << 4,
  EV_FILE_EXPORTER_CAN_GENERATE_PDF = 1 << 5,
  EV_FILE_EXPORTER_CAN_GENERATE_PS = 1 << 6,
  EV_FILE_EXPORTER_CAN_PREVIEW = 1 << 7,
  EV_FILE_EXPORTER_CAN_NUMBER_UP = 1 << 8
} EvFileExporterCapabilities;

typedef struct {
  EvFileExporterFormat format;
  const gchar *filename;
  gint first_page;
  gint last_page;
  gdouble paper_width;
  gdouble paper_height;
  gboolean duplex;
  gint pages_per_sheet;
} EvFileExporterContext;

#define EV_TYPE_FILE_EXPORTER (ev_file_exporter_get_type())
G_DECLARE_INTERFACE(EvFileExporter, ev_file_exporter, EV, FILE_EXPORTER,
                    GObject);

struct _EvFileExporterInterface {
  GTypeInterface base_iface;

  /* Methods  */
  void (*begin)(EvFileExporter *exporter, EvFileExporterContext *fc);
  void (*begin_page)(EvFileExporter *exporter);
  void (*do_page)(EvFileExporter *exporter, EvRenderContext *rc);
  void (*end_page)(EvFileExporter *exporter);
  void (*end)(EvFileExporter *exporter);
  EvFileExporterCapabilities (*get_capabilities)(EvFileExporter *exporter);
};

void ev_file_exporter_begin(EvFileExporter *exporter,
                            EvFileExporterContext *fc);
void ev_file_exporter_begin_page(EvFileExporter *exporter);
void ev_file_exporter_do_page(EvFileExporter *exporter, EvRenderContext *rc);
void ev_file_exporter_end_page(EvFileExporter *exporter);
void ev_file_exporter_end(EvFileExporter *exporter);
EvFileExporterCapabilities ev_file_exporter_get_capabilities(
    EvFileExporter *exporter);

G_END_DECLS

#endif

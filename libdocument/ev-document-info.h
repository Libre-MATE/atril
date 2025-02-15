/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8;
 * c-indent-level: 8 -*- */
/*
 *  Copyright (C) 2000-2003 Marco Pesenti Gritti
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

#ifndef EV_DOCUMENT_INFO_H
#define EV_DOCUMENT_INFO_H

#include <glib-object.h>
#include <glib.h>

G_BEGIN_DECLS

typedef struct _EvDocumentInfo EvDocumentInfo;
typedef struct _EvDocumentLicense EvDocumentLicense;

#define EV_TYPE_DOCUMENT_INFO (ev_document_info_get_type())

typedef enum {
  EV_DOCUMENT_LAYOUT_SINGLE_PAGE,
  EV_DOCUMENT_LAYOUT_ONE_COLUMN,
  EV_DOCUMENT_LAYOUT_TWO_COLUMN_LEFT,
  EV_DOCUMENT_LAYOUT_TWO_COLUMN_RIGHT,
  EV_DOCUMENT_LAYOUT_TWO_PAGE_LEFT,
  EV_DOCUMENT_LAYOUT_TWO_PAGE_RIGHT
} EvDocumentLayout;

typedef enum {
  EV_DOCUMENT_MODE_NONE,
  EV_DOCUMENT_MODE_USE_OC,
  EV_DOCUMENT_MODE_USE_THUMBS,
  EV_DOCUMENT_MODE_FULL_SCREEN,
  EV_DOCUMENT_MODE_USE_ATTACHMENTS,
  EV_DOCUMENT_MODE_PRESENTATION =
      EV_DOCUMENT_MODE_FULL_SCREEN /* Will these be different? */
} EvDocumentMode;

typedef enum {
  EV_DOCUMENT_UI_HINT_HIDE_TOOLBAR = 1 << 0,
  EV_DOCUMENT_UI_HINT_HIDE_MENUBAR = 1 << 1,
  EV_DOCUMENT_UI_HINT_HIDE_WINDOWUI = 1 << 2,
  EV_DOCUMENT_UI_HINT_FIT_WINDOW = 1 << 3,
  EV_DOCUMENT_UI_HINT_CENTER_WINDOW = 1 << 4,
  EV_DOCUMENT_UI_HINT_DISPLAY_DOC_TITLE = 1 << 5,
  EV_DOCUMENT_UI_HINT_DIRECTION_RTL = 1 << 6
} EvDocumentUIHints;

/* This define is needed because glib-mkenums chokes with multiple lines */
#define PERMISSIONS_FULL                                                       \
  (EV_DOCUMENT_PERMISSIONS_OK_TO_PRINT |                                       \
   EV_DOCUMENT_PERMISSIONS_OK_TO_MODIFY | EV_DOCUMENT_PERMISSIONS_OK_TO_COPY | \
   EV_DOCUMENT_PERMISSIONS_OK_TO_ADD_NOTES)

typedef enum {
  EV_DOCUMENT_PERMISSIONS_OK_TO_PRINT = 1 << 0,
  EV_DOCUMENT_PERMISSIONS_OK_TO_MODIFY = 1 << 1,
  EV_DOCUMENT_PERMISSIONS_OK_TO_COPY = 1 << 2,
  EV_DOCUMENT_PERMISSIONS_OK_TO_ADD_NOTES = 1 << 3,
  EV_DOCUMENT_PERMISSIONS_FULL = PERMISSIONS_FULL
} EvDocumentPermissions;

typedef enum {
  EV_DOCUMENT_INFO_TITLE = 1 << 0,
  EV_DOCUMENT_INFO_FORMAT = 1 << 1,
  EV_DOCUMENT_INFO_AUTHOR = 1 << 2,
  EV_DOCUMENT_INFO_SUBJECT = 1 << 3,
  EV_DOCUMENT_INFO_KEYWORDS = 1 << 4,
  EV_DOCUMENT_INFO_LAYOUT = 1 << 5,
  EV_DOCUMENT_INFO_CREATOR = 1 << 6,
  EV_DOCUMENT_INFO_PRODUCER = 1 << 7,
  EV_DOCUMENT_INFO_CREATION_DATE = 1 << 8,
  EV_DOCUMENT_INFO_MOD_DATE = 1 << 9,
  EV_DOCUMENT_INFO_LINEARIZED = 1 << 10,
  EV_DOCUMENT_INFO_START_MODE = 1 << 11,
  EV_DOCUMENT_INFO_UI_HINTS = 1 << 12,
  EV_DOCUMENT_INFO_PERMISSIONS = 1 << 13,
  EV_DOCUMENT_INFO_N_PAGES = 1 << 14,
  EV_DOCUMENT_INFO_SECURITY = 1 << 15,
  EV_DOCUMENT_INFO_PAPER_SIZE = 1 << 16,
  EV_DOCUMENT_INFO_LICENSE = 1 << 17,

} EvDocumentInfoFields;

struct _EvDocumentInfo {
  char *title;
  char *format; /* eg, "pdf-1.5" */
  char *author;
  char *subject;
  char *keywords;
  char *creator;
  char *producer;
  char *linearized;
  char *security;
  gint64 creation_date;
  gint64 modified_date;
  EvDocumentLayout layout;
  EvDocumentMode mode;
  guint ui_hints;
  guint permissions;
  int n_pages;
  double paper_height;
  double paper_width;
  EvDocumentLicense *license;

  /* Mask of all the valid fields */
  guint fields_mask;
};

GType ev_document_info_get_type(void) G_GNUC_CONST;
EvDocumentInfo *ev_document_info_copy(EvDocumentInfo *info);
void ev_document_info_free(EvDocumentInfo *info);

/* EvDocumentLicense */
#define EV_TYPE_DOCUMENT_LICENSE (ev_document_license_get_type())
struct _EvDocumentLicense {
  gchar *text;
  gchar *uri;
  gchar *web_statement;
};
GType ev_document_license_get_type(void) G_GNUC_CONST;
EvDocumentLicense *ev_document_license_new(void);
EvDocumentLicense *ev_document_license_copy(EvDocumentLicense *license);
void ev_document_license_free(EvDocumentLicense *license);
const gchar *ev_document_license_get_text(EvDocumentLicense *license);
const gchar *ev_document_license_get_uri(EvDocumentLicense *license);
const gchar *ev_document_license_get_web_statement(EvDocumentLicense *license);

G_END_DECLS

#endif /* EV_DOCUMENT_INFO_H */

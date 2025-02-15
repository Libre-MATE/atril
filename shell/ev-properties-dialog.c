/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8;
 * c-indent-level: 8 -*- */
/* this file is part of atril, a mate document viewer
 *
 *  Copyright (C) 2005 Red Hat, Inc
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

#include <glib/gi18n.h>
#include <gtk/gtk.h>

#include "ev-document-fonts.h"
#include "ev-properties-dialog.h"
#include "ev-properties-fonts.h"
#include "ev-properties-license.h"
#include "ev-properties-view.h"

struct _EvPropertiesDialog {
  GtkDialog base_instance;

  EvDocument *document;
  GtkWidget *notebook;
  GtkWidget *general_page;
  GtkWidget *fonts_page;
  GtkWidget *license_page;
};

struct _EvPropertiesDialogClass {
  GtkDialogClass base_class;
};

G_DEFINE_TYPE(EvPropertiesDialog, ev_properties_dialog, GTK_TYPE_DIALOG)

static void ev_properties_dialog_class_init(
    EvPropertiesDialogClass *properties_class) {}

static gboolean on_notebook_scroll_event(GtkWidget *widget,
                                         GdkEventScroll *event) {
  GtkNotebook *notebook = GTK_NOTEBOOK(widget);
  GtkWidget *child, *event_widget, *action_widget;

  child = gtk_notebook_get_nth_page(notebook,
                                    gtk_notebook_get_current_page(notebook));
  if (child == NULL) return FALSE;

  event_widget = gtk_get_event_widget((GdkEvent *)event);

  /* Ignore scroll events from the content of the page */
  if (event_widget == NULL || event_widget == child ||
      gtk_widget_is_ancestor(event_widget, child))
    return FALSE;

  /* And also from the action widgets */
  action_widget = gtk_notebook_get_action_widget(notebook, GTK_PACK_START);
  if (event_widget == action_widget ||
      (action_widget != NULL &&
       gtk_widget_is_ancestor(event_widget, action_widget)))
    return FALSE;

  action_widget = gtk_notebook_get_action_widget(notebook, GTK_PACK_END);
  if (event_widget == action_widget ||
      (action_widget != NULL &&
       gtk_widget_is_ancestor(event_widget, action_widget)))
    return FALSE;

  switch (event->direction) {
    case GDK_SCROLL_RIGHT:
    case GDK_SCROLL_DOWN:
      gtk_notebook_next_page(notebook);
      break;
    case GDK_SCROLL_LEFT:
    case GDK_SCROLL_UP:
      gtk_notebook_prev_page(notebook);
      break;
    case GDK_SCROLL_SMOOTH:
      switch (gtk_notebook_get_tab_pos(notebook)) {
        case GTK_POS_LEFT:
        case GTK_POS_RIGHT:
          if (event->delta_y > 0)
            gtk_notebook_next_page(notebook);
          else if (event->delta_y < 0)
            gtk_notebook_prev_page(notebook);
          break;
        case GTK_POS_TOP:
        case GTK_POS_BOTTOM:
          if (event->delta_x > 0)
            gtk_notebook_next_page(notebook);
          else if (event->delta_x < 0)
            gtk_notebook_prev_page(notebook);
          break;
      }
      break;
  }

  return TRUE;
}

static void ev_properties_dialog_init(EvPropertiesDialog *properties) {
  GtkBox *content_area;

  content_area = GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(properties)));

  gtk_window_set_title(GTK_WINDOW(properties), _("Properties"));
  gtk_window_set_destroy_with_parent(GTK_WINDOW(properties), TRUE);
  gtk_container_set_border_width(GTK_CONTAINER(properties), 5);
  gtk_box_set_spacing(content_area, 2);

  gtk_dialog_add_button(GTK_DIALOG(properties), "gtk-close",
                        GTK_RESPONSE_CANCEL);
  gtk_dialog_set_default_response(GTK_DIALOG(properties), GTK_RESPONSE_CANCEL);

  properties->notebook = gtk_notebook_new();
  gtk_widget_add_events(properties->notebook, GDK_SCROLL_MASK);
  g_signal_connect(properties->notebook, "scroll-event",
                   G_CALLBACK(on_notebook_scroll_event), NULL);

  gtk_container_set_border_width(GTK_CONTAINER(properties->notebook), 5);
  gtk_box_pack_start(content_area, properties->notebook, TRUE, TRUE, 0);
  gtk_widget_show(properties->notebook);

  g_signal_connect(properties, "response", G_CALLBACK(gtk_widget_destroy),
                   NULL);
}

void ev_properties_dialog_set_document(EvPropertiesDialog *properties,
                                       const gchar *uri, EvDocument *document) {
  GtkWidget *label;
  const EvDocumentInfo *info;

  properties->document = document;

  info = ev_document_get_info(document);

  if (properties->general_page == NULL) {
    label = gtk_label_new(_("General"));
    properties->general_page = ev_properties_view_new(uri);
    gtk_notebook_append_page(GTK_NOTEBOOK(properties->notebook),
                             properties->general_page, label);
    gtk_widget_show(properties->general_page);
  }
  ev_properties_view_set_info(EV_PROPERTIES_VIEW(properties->general_page),
                              info);

  if (EV_IS_DOCUMENT_FONTS(document)) {
    if (properties->fonts_page == NULL) {
      label = gtk_label_new(_("Fonts"));
      properties->fonts_page = ev_properties_fonts_new();
      gtk_notebook_append_page(GTK_NOTEBOOK(properties->notebook),
                               properties->fonts_page, label);
      gtk_widget_show(properties->fonts_page);
    }

    ev_properties_fonts_set_document(
        EV_PROPERTIES_FONTS(properties->fonts_page), document);
  }

  if (info->fields_mask & EV_DOCUMENT_INFO_LICENSE && info->license) {
    if (properties->license_page == NULL) {
      label = gtk_label_new(_("Document License"));
      properties->license_page = ev_properties_license_new();
      gtk_notebook_append_page(GTK_NOTEBOOK(properties->notebook),
                               properties->license_page, label);
      gtk_widget_show(properties->license_page);
    }

    ev_properties_license_set_license(
        EV_PROPERTIES_LICENSE(properties->license_page), info->license);
  }
}

GtkWidget *ev_properties_dialog_new() {
  EvPropertiesDialog *properties;

  properties = g_object_new(EV_TYPE_PROPERTIES_DIALOG, NULL);

  return GTK_WIDGET(properties);
}

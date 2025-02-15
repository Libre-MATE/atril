/* ev-message-area.c
 *  this file is part of atril, a mate document viewer
 *
 * Copyright (C) 2007 Carlos Garcia Campos
 *
 * Author:
 *   Carlos Garcia Campos <carlosgc@gnome.org>
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

#include "ev-message-area.h"

struct _EvMessageAreaPrivate {
  GtkWidget *main_box;
  GtkWidget *image;
  GtkWidget *label;
  GtkWidget *secondary_label;

  guint message_type : 3;
};

enum { PROP_0, PROP_TEXT, PROP_SECONDARY_TEXT, PROP_IMAGE };

static void ev_message_area_set_property(GObject *object, guint prop_id,
                                         const GValue *value,
                                         GParamSpec *pspec);
static void ev_message_area_get_property(GObject *object, guint prop_id,
                                         GValue *value, GParamSpec *pspec);

G_DEFINE_TYPE_WITH_PRIVATE(EvMessageArea, ev_message_area, GTK_TYPE_INFO_BAR)

static void ev_message_area_class_init(EvMessageAreaClass *class) {
  GObjectClass *gobject_class = G_OBJECT_CLASS(class);

  gobject_class->set_property = ev_message_area_set_property;
  gobject_class->get_property = ev_message_area_get_property;

  g_object_class_install_property(
      gobject_class, PROP_TEXT,
      g_param_spec_string("text", "Text",
                          "The primary text of the message dialog", NULL,
                          G_PARAM_READWRITE));
  g_object_class_install_property(
      gobject_class, PROP_SECONDARY_TEXT,
      g_param_spec_string("secondary-text", "Secondary Text",
                          "The secondary text of the message dialog", NULL,
                          G_PARAM_READWRITE));
  g_object_class_install_property(
      gobject_class, PROP_IMAGE,
      g_param_spec_object("image", "Image", "The image", GTK_TYPE_WIDGET,
                          G_PARAM_READWRITE));
}

static void ev_message_area_init(EvMessageArea *area) {
  GtkWidget *hbox, *vbox;
  GtkWidget *content_area;

  area->priv = ev_message_area_get_instance_private(area);

  area->priv->main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 12);

  hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 12);
  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 12);

  area->priv->label = gtk_label_new(NULL);
  gtk_label_set_use_markup(GTK_LABEL(area->priv->label), TRUE);
  gtk_label_set_line_wrap(GTK_LABEL(area->priv->label), TRUE);
  gtk_label_set_selectable(GTK_LABEL(area->priv->label), TRUE);
  gtk_label_set_xalign(GTK_LABEL(area->priv->label), 0.0);
  gtk_widget_set_can_focus(area->priv->label, TRUE);
  gtk_box_pack_start(GTK_BOX(vbox), area->priv->label, TRUE, TRUE, 0);
  gtk_widget_show(area->priv->label);

  area->priv->secondary_label = gtk_label_new(NULL);
  gtk_label_set_use_markup(GTK_LABEL(area->priv->secondary_label), TRUE);
  gtk_label_set_line_wrap(GTK_LABEL(area->priv->secondary_label), TRUE);
  gtk_label_set_selectable(GTK_LABEL(area->priv->secondary_label), TRUE);
  gtk_label_set_xalign(GTK_LABEL(area->priv->secondary_label), 0.0);
  gtk_widget_set_can_focus(area->priv->secondary_label, TRUE);
  gtk_box_pack_start(GTK_BOX(vbox), area->priv->secondary_label, TRUE, TRUE, 0);

  area->priv->image = gtk_image_new_from_icon_name(NULL, GTK_ICON_SIZE_DIALOG);
  gtk_widget_set_halign(area->priv->image, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(area->priv->image, GTK_ALIGN_START);
  gtk_box_pack_start(GTK_BOX(hbox), area->priv->image, FALSE, FALSE, 0);
  gtk_widget_show(area->priv->image);

  gtk_box_pack_start(GTK_BOX(hbox), vbox, TRUE, TRUE, 0);
  gtk_widget_show(vbox);

  gtk_box_pack_start(GTK_BOX(area->priv->main_box), hbox, TRUE, TRUE, 0);
  gtk_widget_show(hbox);

  content_area = gtk_info_bar_get_content_area(GTK_INFO_BAR(area));
  gtk_container_add(GTK_CONTAINER(content_area), area->priv->main_box);
  gtk_widget_show(area->priv->main_box);
}

static void ev_message_area_set_image_for_type(EvMessageArea *area,
                                               GtkMessageType type) {
  const gchar *icon_name = NULL;
  AtkObject *atk_obj;

  switch (type) {
    case GTK_MESSAGE_INFO:
      icon_name = "dialog-information";
      break;
    case GTK_MESSAGE_QUESTION:
      icon_name = "dialog-question";
      break;
    case GTK_MESSAGE_WARNING:
      icon_name = "dialog-warning";
      break;
    case GTK_MESSAGE_ERROR:
      icon_name = "dialog-error";
      break;
    case GTK_MESSAGE_OTHER:
      break;
    default:
      g_warning("Unknown GtkMessageType %u", type);
      break;
  }

  if (icon_name)
    gtk_image_set_from_icon_name(GTK_IMAGE(area->priv->image), icon_name,
                                 GTK_ICON_SIZE_DIALOG);

  atk_obj = gtk_widget_get_accessible(GTK_WIDGET(area));
  if (GTK_IS_ACCESSIBLE(atk_obj)) {
    atk_object_set_role(atk_obj, ATK_ROLE_ALERT);
    if (icon_name) {
      atk_object_set_name(atk_obj, icon_name);
    }
  }
}

static void ev_message_area_set_property(GObject *object, guint prop_id,
                                         const GValue *value,
                                         GParamSpec *pspec) {
  EvMessageArea *area = EV_MESSAGE_AREA(object);

  switch (prop_id) {
    case PROP_TEXT:
      ev_message_area_set_text(area, g_value_get_string(value));
      break;
    case PROP_SECONDARY_TEXT:
      ev_message_area_set_secondary_text(area, g_value_get_string(value));
      break;
    case PROP_IMAGE:
      ev_message_area_set_image(area, (GtkWidget *)g_value_get_object(value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
      break;
  }
}

static void ev_message_area_get_property(GObject *object, guint prop_id,
                                         GValue *value, GParamSpec *pspec) {
  EvMessageArea *area = EV_MESSAGE_AREA(object);

  switch (prop_id) {
    case PROP_TEXT:
      g_value_set_string(value,
                         gtk_label_get_label(GTK_LABEL(area->priv->label)));
      break;
    case PROP_SECONDARY_TEXT:
      g_value_set_string(
          value, gtk_label_get_label(GTK_LABEL(area->priv->secondary_label)));
      break;
    case PROP_IMAGE:
      g_value_set_object(value, area->priv->image);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
      break;
  }
}

void _ev_message_area_add_buttons_valist(EvMessageArea *area,
                                         const gchar *first_button_text,
                                         va_list args) {
  const gchar *text;
  gint response_id;

  if (first_button_text == NULL) return;

  text = first_button_text;
  response_id = va_arg(args, gint);

  while (text != NULL) {
    gtk_info_bar_add_button(GTK_INFO_BAR(area), text, response_id);

    text = va_arg(args, gchar *);
    if (text == NULL) break;

    response_id = va_arg(args, int);
  }
}

GtkWidget *_ev_message_area_get_main_box(EvMessageArea *area) {
  return area->priv->main_box;
}

GtkWidget *ev_message_area_new(GtkMessageType type, const gchar *text,
                               const gchar *first_button_text, ...) {
  GtkWidget *widget;

  widget = g_object_new(EV_TYPE_MESSAGE_AREA, "message-type", type, "text",
                        text, NULL);
  ev_message_area_set_image_for_type(EV_MESSAGE_AREA(widget), type);
  if (first_button_text) {
    va_list args;

    va_start(args, first_button_text);
    _ev_message_area_add_buttons_valist(EV_MESSAGE_AREA(widget),
                                        first_button_text, args);
    va_end(args);
  }

  return widget;
}

void ev_message_area_set_image(EvMessageArea *area, GtkWidget *image) {
  GtkWidget *parent;

  g_return_if_fail(EV_IS_MESSAGE_AREA(area));

  area->priv->message_type = GTK_MESSAGE_OTHER;

  parent = gtk_widget_get_parent(area->priv->image);
  gtk_container_add(GTK_CONTAINER(parent), image);
  gtk_container_remove(GTK_CONTAINER(parent), area->priv->image);
  gtk_box_reorder_child(GTK_BOX(parent), image, 0);

  area->priv->image = image;

  g_object_notify(G_OBJECT(area), "image");
}

void ev_message_area_set_image_from_stock(EvMessageArea *area,
                                          const gchar *icon_name) {
  g_return_if_fail(EV_IS_MESSAGE_AREA(area));
  g_return_if_fail(icon_name != NULL);

  gtk_image_set_from_icon_name(GTK_IMAGE(area->priv->image), icon_name,
                               GTK_ICON_SIZE_DIALOG);
}

void ev_message_area_set_text(EvMessageArea *area, const gchar *str) {
  g_return_if_fail(EV_IS_MESSAGE_AREA(area));

  if (str) {
    gchar *msg;

    msg = g_strdup_printf("<b>%s</b>", str);
    gtk_label_set_markup(GTK_LABEL(area->priv->label), msg);
    g_free(msg);
  } else {
    gtk_label_set_markup(GTK_LABEL(area->priv->label), NULL);
  }

  g_object_notify(G_OBJECT(area), "text");
}

void ev_message_area_set_secondary_text(EvMessageArea *area, const gchar *str) {
  g_return_if_fail(EV_IS_MESSAGE_AREA(area));

  if (str) {
    gchar *msg;

    msg = g_strdup_printf("<small>%s</small>", str);
    gtk_label_set_markup(GTK_LABEL(area->priv->secondary_label), msg);
    g_free(msg);
    gtk_widget_show(area->priv->secondary_label);
  } else {
    gtk_label_set_markup(GTK_LABEL(area->priv->secondary_label), NULL);
    gtk_widget_hide(area->priv->secondary_label);
  }

  g_object_notify(G_OBJECT(area), "secondary-text");
}

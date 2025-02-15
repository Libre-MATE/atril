/* ev-loading-message.h
 *  this file is part of atril, a mate document viewer
 *
 * Copyright (C) 2010, 2012 Carlos Garcia Campos <carlosgc@gnome.org>
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

#ifndef EV_LOADING_MESSAGE_H
#define EV_LOADING_MESSAGE_H

#include <glib-object.h>
#include <glib.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

typedef struct _EvLoadingMessage EvLoadingMessage;
typedef struct _EvLoadingMessageClass EvLoadingMessageClass;

#define EV_TYPE_LOADING_MESSAGE (ev_loading_message_get_type())
#define EV_LOADING_MESSAGE(object)                               \
  (G_TYPE_CHECK_INSTANCE_CAST((object), EV_TYPE_LOADING_MESSAGE, \
                              EvLoadingMessage))
#define EV_IS_LOADING_MESSAGE(object) \
  (G_TYPE_CHECK_INSTANCE_TYPE((object), EV_TYPE_LOADING_MESSAGE))
#define EV_LOADING_MESSAGE_CLASS(klass)                      \
  (G_TYPE_CHECK_CLASS_CAST((klass), EV_TYPE_LOADING_MESSAGE, \
                           EvLoadingMessageClass))
#define EV_IS_LOADING_MESSAGE_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass), EV_TYPE_LOADING_MESSAGE))
#define EV_LOADING_MESSAGE_GET_CLASS(object)                    \
  (G_TYPE_INSTANCE_GET_CLASS((object), EV_TYPE_LOADING_MESSAGE, \
                             EvLoadingMessageClass))

GType ev_loading_message_get_type(void) G_GNUC_CONST;

GtkWidget *ev_loading_message_new(void);

G_END_DECLS

#endif /* EV_LOADING_MESSAGE_H */

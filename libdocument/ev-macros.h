/*
 * Copyright © 2012 Christian Persch
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2.1 of the License, or (at your
 * option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef EV_MACROS_H
#define EV_MACROS_H

#if defined(EV_DISABLE_DEPRECATION_WARNINGS) || defined(EVINCE_COMPILATION)
#define EV_DEPRECATED
#define EV_DEPRECATED_FOR(f)
#define EV_UNAVAILABLE(maj, min)
#else
#define EV_DEPRECATED G_DEPRECATED
#define EV_DEPRECATED_FOR(f) G_DEPRECATED_FOR(f)
#define EV_UNAVAILABLE(maj, min) G_UNAVAILABLE(maj, min)
#endif

#endif /* #ifndef EV_MACROS_H */

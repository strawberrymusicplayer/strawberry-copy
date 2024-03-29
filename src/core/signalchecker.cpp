/*
 * Strawberry Music Player
 * This file was part of Clementine.
 * Copyright 2010, David Sansome <me@davidsansome.com>
 * Copyright 2012, 2014, John Maguire <john.maguire@gmail.com>
 * Copyright 2014, Krzysztof Sobiecki <sobkas@gmail.com>
 *
 * Strawberry is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Strawberry is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Strawberry.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "config.h"

#include <glib-object.h>

#include <QtGlobal>

#include "signalchecker.h"

gulong CheckedGConnect(gpointer source, const char *signal, GCallback callback, gpointer data, const int callback_param_count) {

  guint signal_id = 0;
  GQuark detail = 0;

  if (!g_signal_parse_name(signal, G_OBJECT_TYPE(source), &signal_id, &detail, false)) {
    qFatal("Connecting to invalid signal: %s", signal);
  }

  GSignalQuery query;
  g_signal_query(signal_id, &query);
  // The signature for a signal callback is always: return_type callback(gpointer data1, params..., gpointer data2);
  int signal_params = static_cast<int>(query.n_params) + 2;
  if (signal_params != callback_param_count) {
    qFatal("Connecting callback to signal with different parameters counts");
  }

  return g_signal_connect(source, signal, G_CALLBACK(callback), data);

}

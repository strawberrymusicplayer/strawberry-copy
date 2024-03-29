/*
 * Strawberry Music Player
 * This file was part of Clementine.
 * Copyright 2010, David Sansome <me@davidsansome.com>
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

#ifndef POTRANSLATOR_H
#define POTRANSLATOR_H

#include <QTranslator>

// We convert from .po files to .qm files, which loses context information.
// This translator tries loading strings with an empty context if it can't find any others.

class PoTranslator : public QTranslator {
  Q_OBJECT

 public:
  PoTranslator(QObject *parent = nullptr) : QTranslator(parent) {}
  QString translate(const char *context, const char *source_text, const char *disambiguation = nullptr, int n = -1) const override {
    QString ret = QTranslator::translate(context, source_text, disambiguation, n);
    if (!ret.isEmpty()) return ret;
    return QTranslator::translate(nullptr, source_text, disambiguation, n);
  }
};

#endif  // POTRANSLATOR_H

/***************************************************************************
  bioitem.h
  -------------------
  Copyright (C) 2013-2018, LI-COR Biosciences
  Author: Antonio Forgione

  This file is part of EddyPro (R).

  EddyPro (R) is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  EddyPro (R) is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with EddyPro (R). If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#ifndef BIOMITEM_H
#define BIOMITEM_H

#include <QString>

struct BiomItem
{
    BiomItem(QString type, QString id, int col)
        : type_(std::move(type)),
          id_(std::move(id)),
          col_(col)
    {
    }

    QString type_;
    QString id_;
    int col_;
};

#endif // BIOMITEM_H

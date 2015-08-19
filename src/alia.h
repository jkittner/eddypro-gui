/***************************************************************************
  alia.h
  -------------------
  Copyright (C) 2007-2011, Eco2s team, Antonio Forgione
  Copyright (C) 2011-2015, LI-COR Biosciences
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

// TODO: move relevant functions to widget_utils

#ifndef ALIA_H
#define ALIA_H

#include <QtGlobal>
#include <QVariant>
#include <QCoreApplication>

////////////////////////////////////////////////////////////////////////////////
/// \file src/alia.h
/// \brief
/// \version
/// \date
/// \author      Antonio Forgione
/// \note
/// \sa
/// \bug
/// \deprecated
/// \test
/// \todo
////////////////////////////////////////////////////////////////////////////////

class QCalendarWidget;
class QCheckBox;
class QComboBox;
class QLabel;
class QLineEdit;
class QGlobalColor;
class QString;
class QStringList;
class QUrl;

/// \class Alia
/// \brief Container class with helper functions for common use
namespace Alia
{
    bool isOnline_2();
} // Alia

#endif // ALIA_H

/***************************************************************************
  wheeleventfilter.cpp
  --------------------
  Copyright © 2013-2019, LI-COR Biosciences, Inc. All Rights Reserved.
  Author: Antonio Forgione

  This file is part of EddyPro®.

  NON-COMMERCIAL RESEARCH PURPOSES ONLY - EDDYPRO® is licensed for
  non-commercial academic and government research purposes only,
  as provided in the EDDYPRO® End User License Agreement.
  EDDYPRO® may only be used as provided in the End User License Agreement
  and may not be used or accessed for any commercial purposes.
  You may view a copy of the End User License Agreement in the file
  EULA_NON_COMMERCIAL.rtf.

  Commercial companies that are LI-COR flux system customers are
  encouraged to contact LI-COR directly for our commercial EDDYPRO®
  End User License Agreement.

  EDDYPRO® contains Open Source Components (as defined in the
  End User License Agreement). The licenses and/or notices for the
  Open Source Components can be found in the file LIBRARIES.txt.

  EddyPro® is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "wheeleventfilter.h"

#include <QAbstractSpinBox>
#include <QComboBox>
#include <QDebug>
#include <QEvent>

// NOTE: workaround to avoid setting StrongFocus on each combo or spin
// in order to avoid accidental changes using the mouse wheel

WheelEventFilter::WheelEventFilter(QObject *parent) :
    QObject(parent)
{
}

bool WheelEventFilter::eventFilter(QObject *o, QEvent *e)
{
    if (e->type() == QEvent::Wheel)
    {
        if (qobject_cast<QAbstractSpinBox*>(o))
        {
            if (qobject_cast<QAbstractSpinBox*>(o)->focusPolicy() & Qt::WheelFocus)
            {
                e->ignore();
                return true;
            }
            e->accept();
            return false;
        }
        if (qobject_cast<QComboBox*>(o))
        {
            if (qobject_cast<QComboBox*>(o)->focusPolicy() & Qt::WheelFocus)
            {
                e->ignore();
                return true;
            }
            e->accept();
            return false;
        }
    }
    return QObject::eventFilter(o, e);
}

/***************************************************************************
 * This file is part of the TTK qmmp plugin project
 * Copyright (C) 2015 - 2022 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#ifndef REGULARWRAPPER_H
#define REGULARWRAPPER_H

#include "qmmp_export.h"
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
#  include <QRegularExpression>
#else
#  include <QRegExp>
#endif

/*! @brief The class of the regular wrapper.
 * @author Greedysky <greedysky@163.com>
 */
class QMMP_EXPORT RegularWrapper
{
public:
    RegularWrapper();
    explicit RegularWrapper(const QString &pattern);
    ~RegularWrapper();

    bool hasMatch(const QString &str);
    QString value(int index) const;

    static QString escape(const QString &str);

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
    operator QRegularExpression () const;
private:
    QRegularExpression m_regular;
    QRegularExpressionMatch m_match;
#else
    operator QRegExp () const;
private:
    QRegExp m_regular;
#endif

};

#endif

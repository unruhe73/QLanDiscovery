/***************************************************************************
 *   Copyright (C) 2012-2023 by Giovanni Venturi                           *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Steet, Fifth Floor, Boston, MA  02110-1301, USA.          *
 ***************************************************************************/

#ifndef QLANDISCOVERYSETTINGS_H
#define QLANDISCOVERYSETTINGS_H

#include <QtCore/QSettings>
#include <QtCore/QString>


class QLanDiscoverySettings : public QSettings
{
    Q_OBJECT

  public:
    QLanDiscoverySettings();
    ~QLanDiscoverySettings();

    QString startAddress();
    void setStartAddress( const QString ip );

    QString endAddress();
    void setEndAddress( const QString ip );

    void setRangeAddress( const QString ip1, const QString ip2 );

  private:
    QString ipStartAddress;
    QString ipEndAddress;

  signals:

  public slots:

};

#endif // QLANDISCOVERYSETTINGS_H

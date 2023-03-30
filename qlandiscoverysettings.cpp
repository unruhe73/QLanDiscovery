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

#include "qlandiscoverysettings.h"

//#include <QtCore/QtDebug>

QLanDiscoverySettings::QLanDiscoverySettings() :
    QSettings("GV", "QLanDiscovery")
{
  ipStartAddress = value( "IP/Begin" ).toByteArray();
  ipEndAddress = value( "IP/End" ).toByteArray();
}

QLanDiscoverySettings::~QLanDiscoverySettings()
{
  setValue( "IP/Begin", ipStartAddress );
  setValue( "IP/End", ipEndAddress );
}

QString QLanDiscoverySettings::startAddress()
{
  return ipStartAddress;
}

void QLanDiscoverySettings::setStartAddress( const QString ip )
{
  ipStartAddress = ip;
}

QString QLanDiscoverySettings::endAddress()
{
  return ipEndAddress;
}

void QLanDiscoverySettings::setEndAddress(const QString ip)
{
  ipEndAddress = ip;
}

void QLanDiscoverySettings::setRangeAddress(const QString ip1, const QString ip2)
{
  ipStartAddress = ip1;
  ipEndAddress = ip2;
}

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

#ifndef NMAPPROCESS_H
#define NMAPPROCESS_H

#include <QtCore/QProcess>

#include <security/pam_appl.h>
#include <security/pam_misc.h>

class NmapProcess : public QProcess
{
    Q_OBJECT

  public:
    explicit NmapProcess(QObject *parent = 0);

    void exec(const QString& address);

  signals:
    
  public slots:
    
  private:
    bool m_authenticated;
};

int misc_conv(int n, const struct pam_message **msg,
    void *data);

#endif // NMAPPROCESS_H

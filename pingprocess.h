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

#ifndef PINGPROCESS_H
#define PINGPROCESS_H

#include <QtCore/QProcess>

class PingProcess : public QProcess
{
    Q_OBJECT

  public:
    explicit PingProcess(const QString &address, QObject *parent = 0);
    void run();

    const QString address();
    bool reachable();

  signals:
    void executed(bool);

  private slots:
    void done(int state, QProcess::ExitStatus exitState);
    void gotError(QProcess::ProcessError error);

  private:
    QString m_address;
    bool m_pingable;
};

#endif // PINGPROCESS_H

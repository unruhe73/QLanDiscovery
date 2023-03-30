/***************************************************************************
 *   Copyright (C) 2012-2013 by Giovanni Venturi                           *
 *   giovanni@ksniffer.org                                                 *
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

#ifndef HOSTQUEUE_H
#define HOSTQUEUE_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QMap>
#include <QtCore/QQueue>

#define MAX_COUNT 25
#define ERROR_WRONG_RANGE 10
#define NO_ERROR 0

class PingProcess;

class HostQueue : public QObject
{
    Q_OBJECT

  public:
    HostQueue();
    ~HostQueue();

    static bool isIPv4(const QString &address);
    void add(const QString &address);
    void add(const QString &fromAddress, const QString &toAddress);
    int error();

  private slots:
    void checked(bool reachable);

  signals:
    void executed(QString, bool);
    void completed();

  private:
    QMap<QString, PingProcess*> m_pingProcessQueue;
    QQueue<QString> m_waitQueue;
    int m_count;
    int m_error;
};

#endif // HOSTQUEUE_H

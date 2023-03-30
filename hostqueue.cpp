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

#include <QtCore/QStringList>
#include <QtCore/QProcess>
#include <QtCore/QDebug>
#include <QtNetwork/QHostAddress>

#include "hostqueue.h"
#include "pingprocess.h"

HostQueue::HostQueue()
{
  m_count = 0;
  m_error = NO_ERROR;
}


HostQueue::~HostQueue()
{
  QStringList keys = m_pingProcessQueue.keys();
  for (int i = 0; i < keys.size(); i++)
  {
    m_pingProcessQueue[keys.at(i)]->kill();
    delete m_pingProcessQueue[keys.at(i)];
  }

  m_waitQueue.clear();
}


bool HostQueue::isIPv4(const QString &address)
{
  QStringList list = address.split(".");
  if (list.size() != 4)
    return false;

  /*
  // validator yet do the following job:
  book ok;
  short dec;
  short count = 0;
  for (short i = 0; i < 4; i++)
  {
    dec = list[i].toShort(&ok, 10);
    if ((0 <= dec) and (dec <= 255))
      cout++;
  }
  if (count != 4)
    return false;
  */

  return true;
}


void HostQueue::add(const QString &address)
{
  if (m_count < MAX_COUNT)
  {
    PingProcess *pingProcess = new PingProcess(address);
    m_pingProcessQueue[address] = pingProcess;
    connect(pingProcess, SIGNAL(executed(bool)), this, SLOT(checked(bool)));
    pingProcess->run();
    m_count++;
  }
  else
  {
    // queue exceeded list: we can't exceed the opened files used by QProcess
    m_waitQueue.append(address);
  }
}


void HostQueue::add(const QString &fromAddress, const QString &toAddress)
{
  QHostAddress from(fromAddress);
  QHostAddress to(toAddress);
  QHostAddress i;
  if (from.toIPv4Address() <= to.toIPv4Address())
  {
    //qDebug() << "range is ok, from:" << fromAddress << "to:" << toAddress;
    for (quint32 addr = from.toIPv4Address(); addr <= to.toIPv4Address(); addr++)
    {
      i.setAddress(addr);
      add(i.toString());
      m_error = NO_ERROR;
    }
  }
  else
  {
    //qDebug() << "range is WRONG no scanning STARTED";
    m_error = ERROR_WRONG_RANGE;
    emit completed();
  }
}

int HostQueue::error()
{
  return m_error;
}


/* SLOTS */
void HostQueue::checked(bool reachable)
{
  emit executed(((PingProcess*)sender())->address(), reachable);
  m_count--;
  if (m_waitQueue.count() > 0)
  {
    add(m_waitQueue.dequeue());
  }
  if ((m_count == 0) and (m_waitQueue.count() == 0))
    emit completed();
/*  else
  {
    QStringList key = m_pingProcessQueue.keys();
    for (int i = 0; i < key.size(); i++)
      qDebug() << m_pingProcessQueue[key.at(i)]->address() << ":" << m_pingProcessQueue[key.at(i)]->reachable();
  }*/
}

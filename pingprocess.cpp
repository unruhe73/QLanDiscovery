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

#include "pingprocess.h"

#include <QtCore/QDebug>

PingProcess::PingProcess(const QString &address, QObject *parent) :
    QProcess(parent), m_address(address)
{
  m_pingable = false;

  connect(this, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(done(int, QProcess::ExitStatus)));
  connect(this, SIGNAL(error(QProcess::ProcessError)), this, SLOT(gotError(QProcess::ProcessError)));
}


void PingProcess::run()
{
  QString app = "ping";
  QStringList arguments;
  arguments << "-n" << "-q" << "-c" << "1" << m_address;

  start(app, arguments);
}


const QString PingProcess::address()
{
  return m_address;
}


bool PingProcess::reachable()
{
  return m_pingable;
}


/* SLOTS */
void PingProcess::done(int state, QProcess::ExitStatus exitState)   // SLOT
{
  Q_UNUSED(exitState);
  if (state == 0)
    m_pingable = true;

  emit executed(m_pingable);
}


void PingProcess::gotError(QProcess::ProcessError error)   // SLOT
{
  switch (error)
  {
    case QProcess::FailedToStart:
      qDebug() << "Failed to start...";
      break;
    default:
      qDebug() << "ERROR!";
  }

  m_pingable = false;
  emit executed(m_pingable);
}

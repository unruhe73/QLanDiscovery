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

#include "nmapprocess.h"

#include <unistd.h>

#include <QtCore/QProcess>
#include <QtCore/QDebug>

#define MAXHOSTNAMELEN 50

NmapProcess::NmapProcess(QObject *parent) :
    QProcess(parent)
{
  m_authenticated = false;
  //char *pcode = "i-love-you";

  pam_handle_t *pamh = NULL;
  struct pam_conv pamc = { misc_conv, NULL };
  char hostname[MAXHOSTNAMELEN];
  char *ruser;
  int retcode = 0;

  char user[] = "root";
  pam_start("su", user, &pamc, &pamh);

  gethostname(hostname, sizeof(hostname));
  if ((retcode = pam_set_item(pamh, PAM_RHOST, hostname)) != PAM_SUCCESS)
  {
    qDebug() << "pam_set_item hostname failed:" << pam_strerror(pamh, retcode);
    return;
  }

  ruser = getlogin();
  if ((retcode = pam_set_item(pamh, PAM_RUSER, ruser)) != PAM_SUCCESS)
  {
    qDebug() << "pam_set_item remote user failed:" << pam_strerror(pamh, retcode);
    return;
  }

  if ((retcode = pam_authenticate(pamh, 0)) != PAM_SUCCESS)
  {
    qDebug() << "pam_authenticate failed:" << pam_strerror(pamh, retcode);
    return;
  }

  m_authenticated = true;

  qDebug() << "Authenticated as root.";
}


void NmapProcess::exec(const QString& address)
{
  if (m_authenticated)
  {
    QStringList arguments;
    QString foo = "/usr/bin/touch /root/touchtest";
    arguments << "-c" << foo;
    QProcess* process = new QProcess(this);
    process->start("/bin/sh", arguments);
    process->waitForFinished();
    qDebug() << "Touch Test Succeeded. Check to see that /root/touchtest exists.";

    //QString cmd = "pkexec nmap -oX mio.xml -O " + address;
  }
}

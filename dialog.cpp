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

#include "dialog.h"

#include "hostqueue.h"
#include "listview.h"
#include "qlandiscoverysettings.h"

#include <QtCore/QDebug>
#include <QtCore/QString>
#include <QtCore/QRegExp>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QDialogButtonBox>
#include <QtGui/QRegExpValidator>


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
  // get the settings
  m_settings = new QLanDiscoverySettings();

  // IP address validation
  QString Octet = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";

  QRegExp rxip;
  rxip.setPattern("^" + Octet + "\\." + Octet + "\\." + Octet + "\\." +
    Octet + "$"); // i.e. the octets can be from 0-199 or 200-249 or 250-255

  QRegExpValidator *valIPAddr = new QRegExpValidator(rxip, 0);

  m_vLayout = new QVBoxLayout(this);

  m_h1Layout = new QHBoxLayout();
  m_from = new QLabel(tr("IP &from:"));
  m_fromEdit = new QLineEdit();
  m_fromEdit->setText(m_settings->startAddress());
  m_from->setBuddy(m_fromEdit);
  m_fromEdit->setValidator(valIPAddr);
  m_h1Layout->addWidget(m_from);
  m_h1Layout->addWidget(m_fromEdit);

  m_h2Layout = new QHBoxLayout(this);
  m_to = new QLabel(tr("IP &to:"));
  m_toEdit = new QLineEdit();
  m_toEdit->setText( m_settings->endAddress());
  m_to->setBuddy(m_toEdit);
  m_toEdit->setValidator(valIPAddr);
  m_h2Layout->addWidget(m_to);
  m_h2Layout->addWidget(m_toEdit);

  m_detectedLabel = new QLabel(tr("Detected 0 IPs."));

  m_buttonBox = new QDialogButtonBox;
  m_scanButton = new QPushButton(tr("S&can"));
  m_scanButton->setDefault(true);
  connect(m_scanButton, SIGNAL(clicked()), this, SLOT(scanClick()));

  m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel);
  m_buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("E&xit"));
  m_buttonBox->addButton(m_scanButton, QDialogButtonBox::AcceptRole);
  connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

  m_list = new ListView();

  m_vLayout->addLayout(m_h1Layout);
  m_vLayout->addLayout(m_h2Layout);
  m_vLayout->addWidget(m_detectedLabel);
  m_vLayout->addWidget(m_list);
  m_vLayout->addWidget(m_buttonBox);
  setLayout(m_vLayout);

  m_node = new HostQueue;
  connect(m_node, SIGNAL(executed(QString,bool)), this, SLOT(addToList(const QString&, bool)));
  connect(m_node, SIGNAL(completed()), this, SLOT(enableScan()));
}

Dialog::~Dialog()
{
  m_settings->setRangeAddress(m_fromEdit->text(), m_toEdit->text());
  delete m_node;
  delete m_list;
  delete m_scanButton;
  delete m_buttonBox;
  delete m_detectedLabel;
  delete m_toEdit;
  delete m_fromEdit;
  delete m_to;
  delete m_from;
  delete m_h1Layout;
  delete m_h2Layout;
  delete m_vLayout;
  delete m_settings;
}


void Dialog::disableScan()
{
  m_scanButton->setDisabled(true);
}


/* SLOTS */

void Dialog::scanClick()   // SLOT
{
  if (m_node->isIPv4(m_fromEdit->text()) and m_node->isIPv4(m_toEdit->text()))
  {
    m_list->clean();
    m_detectedLabel->setText(tr("Detected 0 IPs."));
    m_node->add(m_fromEdit->text(), m_toEdit->text());
    if (m_node->error() == NO_ERROR)
      disableScan();
    else
      m_detectedLabel->setText(tr("IP range is invalid!"));
  }
}


void Dialog::addToList(const QString& address, bool cond)   // SLOT
{
  if (cond)
  {
    m_list->add(address);
    m_detectedLabel->setText(tr("Detected %1 IPs.").arg(m_list->count()));
  }
}


void Dialog::enableScan()   // SLOT
{
  m_scanButton->setDisabled(false);
}

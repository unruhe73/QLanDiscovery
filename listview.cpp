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

#include <QtWidgets/QHeaderView>
#include <QtCore/QDebug>

#include "listview.h"

ListView::ListView(QWidget *parent) :
    QTreeWidget(parent)
{
  header()->hide();
  m_root = 0;
  setAutoScroll(true);
  setSortingEnabled(true);
  sortByColumn(0, Qt::AscendingOrder);
}


ListView::~ListView()
{
  clean();
}


void ListView::clean()
{
  int count = m_items.count();
  for (int i = 0; i < count; ++i)
  {
    QTreeWidgetItem *obj = m_items.takeAt(0);
    qDebug() << "*** removing" << obj->text(0);
    delete obj;
  }

  delete m_root;

  m_root = 0;
  clear();
}


int ListView::count()
{
  int value = m_items.count();

  if (m_root)
    value++;

  return value;
}


/* SLOTS */
void ListView::add(const QString &address)   // SLOT
{
  if (m_root == 0)
  {
    m_root = new QTreeWidgetItem();
    setColumnCount(1);
    addTopLevelItem( m_root );
    m_root->setText(0, address);
  }
  else
  {
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, address);
    m_items.append(item);
    addTopLevelItem(item);
  }
}

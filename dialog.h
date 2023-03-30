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

#ifndef DIALOG_H
#define DIALOG_H

#include <QtWidgets/QDialog>

class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QLineEdit;
class QLabel;
class QTreeWidget;
class QPushButton;
class QDialogButtonBox;

class HostQueue;
class ListView;
class QLanDiscoverySettings;

class Dialog : public QDialog
{
    Q_OBJECT

  public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

  private:
    void disableScan();

  private slots:
    void scanClick();
    void addToList(const QString& address, bool cond);
    void enableScan();

  private:
    QVBoxLayout *m_vLayout;
    QHBoxLayout *m_h1Layout;
    QHBoxLayout *m_h2Layout;
    QLabel *m_from;
    QLabel *m_to;
    QLineEdit *m_fromEdit;
    QLineEdit *m_toEdit;
    QLabel *m_detectedLabel;
    ListView *m_list;
    QPushButton *m_scanButton;
    QDialogButtonBox *m_buttonBox;
    QLanDiscoverySettings *m_settings;

    HostQueue *m_node;
};

#endif // DIALOG_H

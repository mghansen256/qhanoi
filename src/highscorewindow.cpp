/** ===========================================================
 * @file
 *
 * @date   2016-10-03
 * @brief  Highscore window for QHanoi
 *
 * @author Copyright (C) 2009, 2016 by Michael G. Hansen
 *         <a href="mailto:mike at mghansen dot de">mike at mghansen dot de</a>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#include <QComboBox>

#include "highscorewindow.h"

CHighScoreWindow::CHighScoreWindow(int defNumDisks, HighscoreHash *highlist, QWidget *parent)
    : QDialog(parent)
{
    highscores = highlist;

    setWindowTitle(tr("Hanoi-Highscore"));

    // construct the window-layout:
    QVBoxLayout *vbox = new QVBoxLayout;
    QHBoxLayout *hbox = new QHBoxLayout;

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QLabel *mylabel = new QLabel(tr("&Number of disks:"));
    hbox->addWidget(mylabel);

    QComboBox *comboBox = new QComboBox;
    mylabel->setBuddy(comboBox);
    for (int i=3; i<=9; i++) {
        comboBox->addItem(QString::number(i));
    }
    comboBox->setCurrentIndex(defNumDisks-3);
    connect(comboBox, SIGNAL(activated(int)), this, SLOT(numDisksChanged(int)));

    hbox->addWidget(comboBox);

    vbox->addLayout(hbox);

    tableWidget = new QTableWidget(10, 3, this);
    tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    vbox->addWidget(tableWidget);

    QPushButton *closeButton = new QPushButton(tr("Close"));
    vbox->addWidget(closeButton);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    setLayout(vbox);

    // display the highscores:
    displayScores(defNumDisks);

}

void CHighScoreWindow::numDisksChanged(int index)
{
    if (index>=0)
        displayScores(index+3);

}

void CHighScoreWindow::displayScores(int numDisks)
{
    // clear the table:
    tableWidget->clear();

    // set the headers:
    QTableWidgetItem *newItem = new QTableWidgetItem(tr("Name"));
    tableWidget->setHorizontalHeaderItem(0, newItem);

    newItem = new QTableWidgetItem(tr("Clicks"));
    tableWidget->setHorizontalHeaderItem(1, newItem);

    newItem = new QTableWidgetItem(tr("Time"));
    tableWidget->setHorizontalHeaderItem(2, newItem);

    // get the highscores for numDisks:
    HighscoreList *scores = highscores->value(numDisks);
    if (scores==0)	// TODO: fail better!
        return;

    for (int i=0; i<scores->count(); i++) {
        CHighscore *ascore = scores->at(i);
        if (ascore==0) continue;

        newItem = new QTableWidgetItem(ascore->name);
        tableWidget->setItem(i, 0, newItem);

        newItem = new QTableWidgetItem(QString::number(ascore->numClicks));
        tableWidget->setItem(i, 1, newItem);

        int seconds = ascore->elapsedTime%60;
        int minutes = (ascore->elapsedTime%3600)/60;
        int hours = ascore->elapsedTime/3600;
        newItem = new QTableWidgetItem(QString("%1:%2:%3").arg(hours).arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0')));
        tableWidget->setItem(i, 2, newItem);

    }

    // make sure everything displays okay:
    tableWidget->resizeRowsToContents();
    tableWidget->resizeColumnsToContents();
    /*tableWidget->resizeColumnToContents(0);
    tableWidget->resizeColumnToContents(1);
    tableWidget->resizeColumnToContents(2);
    tableWidget->horizontalHeader()->setResizeMode(0, QHeaderView::Interactive);
    tableWidget->horizontalHeader()->resizeSections(QHeaderView::Stretch);*/

    tableWidget->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);

}


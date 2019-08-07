/** ===========================================================
 * @file
 *
 * @date   2016-10-03
 * @brief  Playing area for QHanoi
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

#include "playfield.h"
#include "diskarea.h"
#include <QHBoxLayout>

CPlayField::CPlayField(QWidget *parent)
    : QWidget(parent)
{
    numDisks = 9;
    numClicks = 0;
    elapsedTime = 0;
    gameRunning = false;
    gameDone = false;
    mytimer.setInterval(1000);
    connect(&mytimer, &QTimer::timeout,
            this, &CPlayField::timeChange);

    QGridLayout *gridLayout = new QGridLayout;

    // create the status-display:
    QHBoxLayout *hboxLayout = new QHBoxLayout;
    QLabel *mylabel = new QLabel(tr("Clicks:"));
    hboxLayout->addWidget(mylabel);
    labelNumClicks = new QLabel("0");
    hboxLayout->addWidget(labelNumClicks);
    mylabel = new QLabel(tr("Time:"));
    hboxLayout->addWidget(mylabel);
    labelElapsedTime = new QLabel("0");
    hboxLayout->addWidget(labelElapsedTime);

    pauseButton = new QPushButton(tr("&Pause"));
    connect(pauseButton, &QPushButton::clicked,
            this, &CPlayField::doPause);
    hboxLayout->addWidget(pauseButton);
    
    QWidget *dummywidget = new QWidget();
    dummywidget->setLayout(hboxLayout);
    gridLayout->addWidget(dummywidget, 0, 0, 1, 3);

    // create the buttons:
    QPushButton *mybutton = new QPushButton("1");
    connect(mybutton, &QPushButton::clicked,
            this, &CPlayField::PoleButtonClicked1);
    gridLayout->addWidget(mybutton, 1, 0);
    mybutton = new QPushButton("2");
    connect(mybutton, &QPushButton::clicked,
            this, &CPlayField::PoleButtonClicked2);
    gridLayout->addWidget(mybutton, 1, 1);
    mybutton = new QPushButton("3");
    connect(mybutton, &QPushButton::clicked,
            this, &CPlayField::PoleButtonClicked3);
    gridLayout->addWidget(mybutton, 1, 2);

    // create the disk-area:
    mydiskarea = new CDiskArea;
    gridLayout->addWidget(mydiskarea, 2, 0, 1, 3);
    gridLayout->setRowStretch(2, 10);

    setLayout(gridLayout);

    doReset();

}

// sets the number of disks:
void CPlayField::setNumDisks(int num)
{
    // store the number of disks:
    numDisks = num;

    // reset the game:
    doReset();

}

// the user clicked one of the pole-buttons:
void CPlayField::PoleButtonClicked1()
{
    PoleButtonClicked(1);
}

void CPlayField::PoleButtonClicked2()
{
    PoleButtonClicked(2);
}

void CPlayField::PoleButtonClicked3()
{
    PoleButtonClicked(3);
}

void CPlayField::PoleButtonClicked(int poleno)
{
    if (gameDone) {
            return;
    }

    // make sure the game is running:
    startOrResume();

    // do we already have a lifted disk?
    int flydisk = mydiskarea->flydisk;
    if (flydisk>0) {

        bool couldDrop = false;
        // find the top-disk on poleno:
        int i;
        for (i=8; i>=0; i--) {
            int diskno = mydiskarea->disksOnPole[poleno-1][i];
            if (diskno>0) {
                if (diskno<flydisk) {
                    mydiskarea->disksOnPole[poleno-1][i+1] = flydisk;
                    mydiskarea->flydisk = 0;
                    couldDrop = true;
                }
                break;
            }
        }
        if (i<0) {
            mydiskarea->disksOnPole[poleno-1][0] = flydisk;
            mydiskarea->flydisk = 0;
            couldDrop = true;
        }
        if (!couldDrop) {
            numClicks++;
        } else {
            checkIfDone();
        }

    } else {
        mydiskarea->flypole = poleno;

        // find top disk and lift it:
        for (int i=8; i>=0; i--) {
            int diskno = mydiskarea->disksOnPole[poleno-1][i];
            if (diskno>0) {
                mydiskarea->flydisk = diskno;
                mydiskarea->disksOnPole[poleno-1][i] = 0;
                break;
            }
        }
        numClicks++;
    }

    mydiskarea->update();
    showNumClicks();

}

// resets the game
void CPlayField::doReset()
{
    // reset number of clicks and time:
    mytimer.stop();
    pauseButton->setEnabled(false);
    numClicks = 0;
    elapsedTime = 0;
    gameRunning = false;
    gameDone = false;

    // reset the status of the game:
    mydiskarea->flydisk = 0;
    for (int i=0; i<9; i++) {
        int iniDisk = 0;
        if (i<numDisks) {
            iniDisk = (i+1) + (9-numDisks);
        }

        mydiskarea->disksOnPole[0][i] = iniDisk;
        mydiskarea->disksOnPole[1][i] = 0;
        mydiskarea->disksOnPole[2][i] = 0;
    }

    // update the display:
    mydiskarea->update();
    showNumClicks();
    showElapsedTime();
}

void CPlayField::showNumClicks()
{
    labelNumClicks->setText(QString::number(numClicks));
}

void CPlayField::showElapsedTime()
{
    int seconds = elapsedTime%60;
    int minutes = (elapsedTime%3600)/60;
    int hours = elapsedTime/3600;
    labelElapsedTime->setText(QString("%1:%2:%3").arg(hours).arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0')));
}

void CPlayField::timeChange()
{
    elapsedTime++;
    showElapsedTime();
}

void CPlayField::startOrResume()
{
    if (!gameRunning) {
        // tell the timer to continue:
        mytimer.start();
        gameRunning = true;
        pauseButton->setEnabled(true);
    }
}

void CPlayField::checkIfDone()
{
    // ATTENTION: The check below is correct, it has to check for 9, because that is the smallest disk!!!
    if (mydiskarea->disksOnPole[2][numDisks-1]==9) {
        mytimer.stop();
        pauseButton->setEnabled(false);
        gameRunning = false;
        gameDone = true;
        emit gameFinished(numDisks, numClicks, elapsedTime);
    }
}

// returns the number of disks
int CPlayField::getNumDisks()
{
    return numDisks;
}

void CPlayField::doPause()
{
    // pause the game:
    mytimer.stop();
    gameRunning = false;

    // disable the pause-button:
    pauseButton->setEnabled(false);
}


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

#ifndef __PLAYFIELD_H
#define __PLAYFIELD_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QTimer>

#include "diskarea.h"

class CPlayField : public QWidget
{
    Q_OBJECT
public:
    CPlayField(QWidget *parent = 0);
    
    void startOrResume();
    void setNumDisks(int num);
    int getNumDisks();
    void PoleButtonClicked(int poleno);

public slots:
    void PoleButtonClicked1();
    void PoleButtonClicked2();
    void PoleButtonClicked3();
    void doReset();
    void doPause();
    void timeChange();

signals:
    void gameFinished(int nDisks, int nClicks, int nTime);

private:
    QLabel *labelNumClicks;
    QLabel *labelElapsedTime;
    void showNumClicks();
    void showElapsedTime();
    QTimer mytimer;
    bool gameRunning;
    bool gameDone;
    void checkIfDone();
    int numClicks;
    int elapsedTime;
    int numDisks;
    CDiskArea *mydiskarea;
    QPushButton *pauseButton;
};


#endif // __PLAYFIELD_H

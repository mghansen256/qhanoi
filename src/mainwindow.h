/** ===========================================================
 * @file
 *
 * @date   2016-10-03
 * @brief  Main window for QHanoi
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

#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QDomDocument>

#include "playfield.h"
#include "highscores.h"

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CMainWindow();
    ~CMainWindow();

private slots:
    void about();
    void changeNumDisks(bool checked);
    void gameFinished(int nDisks, int nClicks, int nTime);
    void showHighscores();

private:
    void deleteHighscoresForNumDisks(int nD);
    void createMenus();
    void createActions();
    void saveSettings();
    void loadSettings();
    QString getConfigFileName();

    CPlayField myplayfield;
    
    QMenu *gameMenu;
    QAction *newGameAct;
    QAction *pauseGameAct;
    QAction *resumeGameAct;
    QAction *highscoreAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *quitAct;
    
    QMenu *sizeMenu;
    QActionGroup *sizeGroup;
    QAction *sizeActs[9-2];

    HighscoreHash highscores;

protected:
    virtual void closeEvent(QCloseEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);

};

#endif // __MAINWINDOW_H


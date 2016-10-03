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

#ifndef __HIGHSCOREWINDOW_H
#define __HIGHSCOREWINDOW_H

#include <QDialog>
#include <QTabWidget>

#include "highscores.h"

class CHighScoreWindow : public QDialog
{
    Q_OBJECT

public:
    CHighScoreWindow(int defNumDisks, HighscoreHash *highlist, QWidget* parent = 0);
    void displayScores(int numDisks);

public slots:
    void numDisksChanged(int index);

private:
    QTableWidget *tableWidget;
    HighscoreHash *highscores;
};

#endif // __HIGHSCOREWINDOW_H


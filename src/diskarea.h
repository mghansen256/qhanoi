/** ===========================================================
 * @file
 *
 * @date   2016-10-03
 * @brief  Disk display area for QHanoi
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

#ifndef __DISKAREA_H
#define __DISKAREA_H

#include <QWidget>
#include <vector>

typedef std::vector<int> intvector;

class CDiskArea : public QWidget
{
    Q_OBJECT
public:
    CDiskArea(QWidget *parent = 0);
    intvector disksOnPole[3];
    int flydisk;
    int flypole;

protected:
    void paintEvent(QPaintEvent *event);
};


#endif // __DISKAREA_H

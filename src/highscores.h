/** ===========================================================
 * @file
 *
 * @date   2016-10-03
 * @brief  Highscore entry for QHanoi
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

#ifndef __HIGHSCORES_H
#define __HIGHSCORES_H

#include <QtGui>
#include <QDomDocument>

class CHighscore
{
public:
	CHighscore();
	CHighscore(QString thename, int nClicks, int nTime);
	CHighscore(QDomElement element);
	QDomElement writeToNode(QDomDocument &dom);
	void fromNode(QDomElement element);


	QString name;
	int numClicks;
	int elapsedTime;

};

typedef QList<CHighscore*> HighscoreList;
typedef QHash<int, HighscoreList*> HighscoreHash; 


#endif // __HIGHSCORES_H

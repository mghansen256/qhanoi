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

#include "highscores.h"

CHighscore::CHighscore()
{
    numClicks = 0;
    elapsedTime = 0;

}

CHighscore::CHighscore(QDomElement element)
{
    fromNode(element);
}

QDomElement CHighscore::writeToNode(QDomDocument &dom)
{
    QDomElement myel = dom.createElement("singlescore");
    myel.setAttribute("name", name);
    myel.setAttribute("numclicks", QString::number(numClicks));
    myel.setAttribute("elapsedtime", QString::number(elapsedTime));

    return myel;
}

void CHighscore::fromNode(QDomElement element)
{
    name = element.attribute("name");
    numClicks = element.attribute("numclicks").toInt();
    elapsedTime = element.attribute("elapsedtime").toInt();
}

CHighscore::CHighscore(QString thename, int nClicks, int nTime)
{
    name = thename;
    numClicks = nClicks;
    elapsedTime = nTime;
}

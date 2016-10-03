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

#include <QPainter>

#include "diskarea.h"

CDiskArea::CDiskArea(QWidget *parent)
	: QWidget(parent)
{
    setPalette(QPalette(QColor(128, 128, 128)));
    setAutoFillBackground(true);

    // no disk flying right now:
    flydisk = 0;
    flypole = 0;

    // initialize the disk-lists:
    for (int i=0; i<9; i++) {
        disksOnPole[0].push_back(0);
        disksOnPole[1].push_back(0);
        disksOnPole[2].push_back(0);
    }

} // CDiskArea::CDiskArea(QWidget *parent)

#define da_area_width	300
#define da_area_height	200

#define da_base_width	280
#define da_base_height	15
#define da_base_to_bottom 10

#define da_base_margin	((int)((da_base_width-3*(da_pole_margin+da_pole_width))*0.5))
#define da_pole_height	150
#define da_pole_width	6
#define da_disk_maxwidth 50
#define da_disk_vmargin	3
#define da_disk_hmargin	35
#define da_pole_margin	((int)(da_disk_maxwidth+da_disk_hmargin-da_pole_width*0.5))
#define da_flydisk_top	10
#define da_disk_height	10
#define da_disk_margin	3

#define da_base_left	((int)((da_area_width-da_base_width)*0.5))
#define da_disk_shrink	5

/*#define da_base_height 50
#define da_base_width 900
#define da_base_to_bottom 0.02
#define da_pole_height 0.8
#define da_pole_width 0.02
#define da_pole_margin 0.06
#define da_disk_maxwidth 0.2
#define da_disk_height 0.05
#define da_disk_shrink 0.02
#define da_disk_margin 0.015
#define da_flydisk_top 0.05 */

// returns the x-middle of a pole:
float inline poleXMiddle(int poleno)
{
    return da_base_left + da_base_margin + (da_pole_margin+da_pole_width)*0.5 + (poleno-1)*(da_pole_margin+da_pole_width);

    //return (1.0-(3.0*da_disk_maxwidth+4.0*da_pole_margin))/2.0 + (float)poleno*da_pole_margin+(-0.5+(float)poleno)*da_disk_maxwidth;

} // float poleXMiddle(int poleno)

void CDiskArea::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // we draw on 1000x1000 pixels, let QT scale this to the real window:
    painter.translate(0, height());
    painter.scale((float)width()/(float)da_area_width, (float)height()/(float)da_area_height);

    // this could all be done a lot better, but it works, so what the heck :-)
    const int w = da_area_width; //1000;//width();
    const int h = da_area_height; //1000;//height();

    // draw the base on which the poles are standing:
    painter.setBrush(Qt::blue);
    painter.setPen(Qt::NoPen);
    painter.drawRect(da_base_left, -(da_base_to_bottom+da_base_height), da_base_width, da_base_height);

    // draw the poles:
    painter.setBrush(Qt::green);
    for (float i=1; i<=3; i++) {
        painter.drawRect(poleXMiddle(i) - 0.5*da_pole_width, -(da_pole_height+da_base_height+da_base_to_bottom), da_pole_width, da_pole_height);
    }

    // now draw the disks:
    painter.setBrush(Qt::red);
    for (int i=0; i<=2; i++) {
        for (int j=0; j<9; j++) {
            float diskno = disksOnPole[i][j];

            if (diskno>0) {
                // pole i, disk-position j, disk diskno:
                painter.drawRect(
                        //printf("l: %f t: %f w: %f h: %f\n",
                        // from the left:
                        poleXMiddle(i+1)-0.5*(da_disk_maxwidth-(diskno-1)*da_disk_shrink),

                        // from the bottom:
                        -(da_base_height+da_base_to_bottom + (1+j)*da_disk_height + j*da_disk_margin),

                        // width:
                        da_disk_maxwidth-(diskno-1)*da_disk_shrink,

                        // height:
                        da_disk_height
                    );
            }
        }
    }

    // draw the 'flying' disk if there is one:
    if (flydisk>0) {
        float flydisk_width = da_disk_maxwidth-(flydisk-1)*da_disk_shrink;

        painter.drawRect(
                // left:
                poleXMiddle(flypole) - 0.5*flydisk_width,

                // top:
                -(da_area_height-da_flydisk_top),

                // width:
                flydisk_width,

                // height:
                da_disk_height
            );
    }
    /*painter.setViewport(10, -190, 300, 300);
    imagePole.render(&painter);*/
}

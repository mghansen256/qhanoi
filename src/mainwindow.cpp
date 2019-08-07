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

#include "mainwindow.h"

// local includes

#include "highscorewindow.h"

CMainWindow::CMainWindow()
    : QMainWindow()
{
    setCentralWidget(&myplayfield);

    createActions();
    createMenus();

    setWindowTitle(tr("Hanoi"));
    setMinimumSize(300, 200);
    resize(500, 400);

    connect(&myplayfield, SIGNAL(gameFinished(int, int, int)), this, SLOT(gameFinished(int, int, int)));

    // load settings:
    loadSettings();

}

void CMainWindow::createActions()
{
    newGameAct = new QAction(tr("&New Game"), this);
    connect(newGameAct, SIGNAL(triggered()), &myplayfield, SLOT(doReset()));

    quitAct = new QAction(tr("&Quit"), this);
    quitAct->setStatusTip(tr("Quit Hanoi."));
    connect(quitAct, SIGNAL(triggered()), this, SLOT(close()));

    highscoreAct = new QAction(tr("Show Highscores"), this);
    connect(highscoreAct, SIGNAL(triggered()), this, SLOT(showHighscores()));

    aboutAct = new QAction(tr("About Hanoi"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    sizeGroup = new QActionGroup(this);
    for (int i=0; i<(9-2); i++) {
            sizeActs[i] = new QAction(tr("%1 Disks").arg(i+3), this);
            sizeActs[i]->setCheckable(true);
            sizeGroup->addAction(sizeActs[i]);
            connect(sizeActs[i], SIGNAL(triggered(bool)), this, SLOT(changeNumDisks(bool)));
    }
    sizeActs[0]->setChecked(true);

}

// this gets called when the size-option is changed
void CMainWindow::changeNumDisks(bool checked)
{
    // we only react to "checked=true"-events
    if (checked) {
        // find the checked action:
        for (int i=0; i<=(9-3); i++) {
            if (sizeActs[i]->isChecked()) {

                // tell the playing-field about it:
                myplayfield.setNumDisks(i+3);

                return;
            }
        }
    }
}

void CMainWindow::createMenus()
{
    gameMenu = menuBar()->addMenu(tr("&Game"));
    gameMenu->addAction(newGameAct);
    gameMenu->addSeparator();
    gameMenu->addAction(highscoreAct);
    gameMenu->addAction(aboutAct);
    gameMenu->addAction(aboutQtAct);
    gameMenu->addSeparator();
    gameMenu->addAction(quitAct);

    sizeMenu = menuBar()->addMenu(tr("&Size"));
    for (int i=0; i<(9-2); i++) {
        sizeMenu->addAction(sizeActs[i]);
    }

} // void CMainWindow::createMenus()

void CMainWindow::about()
{
    QMessageBox::about(this, tr("About Hanoi"), tr("<h1>About Hanoi</h1><br/>This is a cool game. Visit its homepage: <a href=\"http://www.mghansen\">www.mghansen.de</a>"));

}

// returns the name of the configuration-file
QString CMainWindow::getConfigFileName()
{
    return "hanoirc.xml";

}

void CMainWindow::deleteHighscoresForNumDisks(int nD)
{
    HighscoreList *scores = highscores.value(nD);

    if (scores!=0) {
        while (scores->count()>0) {
            delete scores->at(scores->count()-1);
            scores->removeAt(scores->count()-1);
        }
    }

    delete scores;

    highscores.remove(nD);

}

// load settings from disk
void CMainWindow::loadSettings()
{
    // specify default-settings:
    int numDisks = 3;
    for (int i=3; i<=9; i++) {
        HighscoreList *defscores = new HighscoreList;
        for (int j=0; j<=9; j++) {
            defscores->append(new CHighscore("Merlin", (j+1)*10, (j+1)*11));
        }
        highscores.insert(i, defscores);
    }
    bool configLoaded = false;
    QDomDocument *domDocument = new QDomDocument;

    QFile file(getConfigFileName());
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        if (domDocument->setContent(&file, true)) {
            QDomElement root = domDocument->documentElement();
            configLoaded = root.tagName() == "hanoi";
            if (configLoaded) {
                configLoaded = root.hasAttribute("version") && (root.attribute("version") == "0.1");
            }
        }
    }

    // did the configuration load okay?
    /*if (!configLoaded) {
            
            printf("Creating new document!\n");
            // no, create default settings:
            delete domDocument;
            domDocument = new QDomDocument;

            QDomProcessingInstruction instr = domDocument->createProcessingInstruction("xml", "version=\"1.0\" ");
            domDocument->appendChild(instr);
            instr = domDocument->createProcessingInstruction("xml", "encoding=\"utf-8\" ");
            domDocument->appendChild(instr);

            QDomElement root = domDocument->createElement("hanoi");
            root.setAttribute("version", "0.1");
            QDomElement settings = domDocument->createElement("settings");
            root.appendChild(settings);
            QDomElement nodeNumDisks = domDocument->createElement("numdisks");
            QDomText nodeNumDisksValue = domDocument->createTextNode("3");
            nodeNumDisks.appendChild(nodeNumDisksValue);
            settings.appendChild(nodeNumDisks);

            domDocument->appendChild(root);

    }*/

    // extract the number of disks:
    QDomElement root = domDocument->documentElement();
    QDomNode settings = root.firstChildElement("settings");
    if (!root.isNull()) {
        QDomElement nodeNumDisks = settings.firstChildElement("numdisks");
        if (!nodeNumDisks.isNull()) {
            numDisks = nodeNumDisks.text().toInt();
            if (numDisks<3) {
                numDisks = 3;
            } else if (numDisks>9) {
                numDisks = 9;
            }
        }
    }

    // tell everybody about the number of disks:
    sizeActs[numDisks-3]->setChecked(true);
    myplayfield.setNumDisks(numDisks);

    // extract the highscores:
    QDomNode n = root.firstChildElement("scores");
    while (!n.isNull()) {
        QDomElement e = n.toElement();

        int disksHere = e.attribute("numdisks").toInt();

        // delete default-scores:
        deleteHighscoresForNumDisks(disksHere);
        
        HighscoreList *newlist = new HighscoreList;
        QDomNode h = n.firstChild();
        while (!h.isNull()) {
            newlist->append(new CHighscore(h.toElement()));

            h = h.nextSibling();
        }

        highscores.insert(disksHere, newlist);

        n = n.nextSibling();	
    }

    delete domDocument;

} // void CMainWindow::loadSettings()

// save settings to disk
void CMainWindow::saveSettings()
{
	// construct a DOM:

	QDomDocument *domDocument = new QDomDocument;

	QDomProcessingInstruction instr = domDocument->createProcessingInstruction("xml", "version=\"1.0\" ");
	domDocument->appendChild(instr);
/*	instr = domDocument->createProcessingInstruction("xml", "encoding=\"utf-8\" ");
	domDocument->appendChild(instr);*/

	QDomElement root = domDocument->createElement("hanoi");
	root.setAttribute("version", "0.1");

	// settings:
	QDomElement settings = domDocument->createElement("settings");
	QDomElement nodeNumDisks = domDocument->createElement("numdisks");
	QDomText nodeNumDisksValue = domDocument->createTextNode(QString::number(myplayfield.getNumDisks()));
	nodeNumDisks.appendChild(nodeNumDisksValue);
	settings.appendChild(nodeNumDisks);

	root.appendChild(settings);

	// highscores:
	for (int i=3; i<=9; i++) {
		HighscoreList *someList = highscores.value(i);

		if (someList==0)
			continue;

		QDomElement elHighscores = domDocument->createElement("scores");
		elHighscores.setAttribute("numdisks", QString::number(i));

		for (int j=0; j<someList->count(); j++) {
			CHighscore *somescore = someList->at(j);
			if (somescore!=0) {
				elHighscores.appendChild(somescore->writeToNode(*domDocument));
			}

		}
		root.appendChild(elHighscores);
	}

	// attach root-node to DOM:
	domDocument->appendChild(root);

	// save to file:
	QFile file(getConfigFileName()+".new");
	if (file.open(QFile::WriteOnly | QFile::Text)) {
		QTextStream out(&file);
		domDocument->save(out, 4);
	} else {
		printf("Error, could not write to file!\n");
	}

	delete domDocument;

} // void CMainWindow::saveSettings()

CMainWindow::~CMainWindow()
{
	// delete all scores:
	for (int i=3; i<=9; i++) {
		deleteHighscoresForNumDisks(i);
	}
} // CMainWindow::~CMainWindow()

void CMainWindow::gameFinished(int nDisks, int nClicks, int nTime)
{
	if ((nDisks>9)||(nDisks<3))
		return;	//TODO: error

	HighscoreList *scores = highscores.value(nDisks);

	// TODO: add list if not there!
	if (scores==0) {
		scores = new HighscoreList;
		highscores.insert(nDisks, scores);
	}

	// check whether the game is worthy of being in the highscores:
	int scorepos = -1;
	if (scores->count()==0) {
		scorepos = 0;
	} else {
		for (int i=0; i<scores->count(); i++) {
			CHighscore *singlescore = scores->at(i);
			if (singlescore) {
				if ((singlescore->elapsedTime>nTime)&&(singlescore->numClicks>nClicks)) {
					scorepos = i;
					break;
				}
			}
		}
	}

	if (scorepos<0) {
		return;
	}

	// ask for the name:
	bool ok;
	QString username = QInputDialog::getText(this, tr("Congratulations!"), tr("Congratulations! You made it!\nPlease enter your name for the highscore-list!"), QLineEdit::Normal, "", &ok);

	if (!ok || username.isEmpty())
		return;

	// add the user to the highscores:
	CHighscore *newscore = new CHighscore(username, nClicks, nTime);

	// add our score:
	scores->insert(scorepos, newscore);

	// if there are more than 10 elements in the list, remove the last one!
	while (scores->count()>10) {
		delete scores->at(scores->count()-1);
		scores->removeAt(scores->count()-1);
	}

	// display the highscore-list:
	showHighscores();

	// save settings:
	saveSettings();

} // void CMainWindow::gameFinished(int nDisks, int nClicks, int nTime)

void CMainWindow::showHighscores()
{
	CHighScoreWindow *scoreShower = new CHighScoreWindow(myplayfield.getNumDisks(), &highscores, this);
	scoreShower->show();

} // void CMainWindow::showHighscores()

void CMainWindow::closeEvent(QCloseEvent *event)
{
	// save the settings:
	saveSettings();

	// okay, we can be closed!
	event->accept();

} // void CMainWindow::closeEvent(QCloseEvent *event)

void CMainWindow::keyPressEvent(QKeyEvent *event)
{
	QString keyText = event->text();
	if ((keyText=="1")||(keyText=="2")||(keyText=="3")) {
		int poleNumber = keyText.toInt();
		myplayfield.PoleButtonClicked(poleNumber);
		event->accept();
	} else {
		QMainWindow::keyPressEvent(event);
	}
} // void CMainWindow::keyPressEvent(QKeyEvent *event)

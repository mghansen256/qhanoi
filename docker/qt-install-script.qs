// script for installing Qt without user intervention
//
// Copyright (C) 2019 Michael G. Hansen
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// inspired by:
// - https://doc.qt.io/qtinstallerframework/noninteractive.html
// - https://github.com/winie/qt-android-docker
// - https://stackoverflow.com/questions/25105269/silent-install-qt-run-installer-on-ubuntu-server

function Controller()
{
    installer.autoRejectMessageBoxes;
    installer.setMessageBoxAutomaticAnswer("OverwriteTargetDirectory", QMessageBox.Yes);
    // the ones below for some reason do not work
    // looks like a Windows-only option to me
    //installer.setMessageBoxAutomaticAnswer("stopProcessesForUpdates", QMesssageBox.Ignore);
    //installer.setMessageBoxAutomaticAnswer("installationError", QMesssageBox.Ok);
    
    // when running the installer without --platform minimal, it finishes
    // without this callback
    installer.installationFinished.connect(function()
    {
        gui.clickButton(buttons.NextButton);
    });
}

Controller.prototype.WelcomePageCallback = function()
{
    // https://stackoverflow.com/questions/25105269/silent-install-qt-run-installer-on-ubuntu-server
    // press next with a delay, because the next button is initially disabled
    gui.clickButton(buttons.NextButton, 3000);
}

Controller.prototype.IntroductionPageCallback = function()
{
    // https://stackoverflow.com/questions/25105269/silent-install-qt-run-installer-on-ubuntu-server
    // press next with a delay, because the next button is initially disabled
    gui.clickButton(buttons.NextButton, 3000);
}

Controller.prototype.LicenseAgreementPageCallback = function()
{
    var pageWidget = gui.currentPageWidget();
    if (pageWidget != null)
    {
        pageWidget.AcceptLicenseRadioButton.setChecked(true);
    }
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.TargetDirectoryPageCallback = function()
{
    var pageWidget = gui.currentPageWidget();
    if (pageWidget != null)
    {
        // TODO: include the Qt version here?
        pageWidget.TargetDirectoryLineEdit.setText("/android/Qt/");
    }
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.ComponentSelectionPageCallback = function()
{
    var pageWidget = gui.currentPageWidget();
    if (pageWidget != null)
    {
        // for a quick installation to test this script,
        // install only qtcreator
        //pageWidget.deselectAll();
        //pageWidget.selectComponent("qt.tools.qtcreator");
        pageWidget.selectAll();
        // these component names may be very qt version dependent.
        pageWidget.deselectComponent("qt.qt5.5123.src");
        pageWidget.deselectComponent("qt.qt5.5123.doc");
        pageWidget.deselectComponent("qt.tools.doc");
        pageWidget.deselectComponent("qt.tools.examples");
    }

    gui.clickButton(buttons.NextButton);
}

// does this even show up on Linux?
Controller.prototype.StartMenuDirectoryPageCallback = function()
{
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.ReadyForInstallationPageCallback = function()
{
    gui.clickButton(buttons.CommitButton);
}

Controller.prototype.PerformInstallationPageCallback = function()
{
    gui.clickButton(buttons.CommitButton);
}

Controller.prototype.FinishedPageCallback = function()
{
    var pageWidget = gui.currentPageWidget();
    if (pageWidget != null)
    {
        var checkBoxForm = pageWidget.LaunchQtCreatorCheckBoxForm;
        if (checkBoxForm && checkBoxForm.launchQtCreatorCheckBox)
        {
            // do not run anything after finishing the installation
            checkBoxForm.launchQtCreatorCheckBox.setChecked(false);
        }
    }
    gui.clickButton(buttons.FinishButton);
}

Controller.prototype.CredentialsPageCallback = function()
{
    gui.clickButton(buttons.NextButton);
}

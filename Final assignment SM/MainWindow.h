/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "StateMachine.h"
#include "Led.h"
#include "manometer.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
QT_END_NAMESPACE

class MainWindow: public QDialog
{
   Q_OBJECT

#define JPG_WIDTH 200
#define JPG_HEIGHT 100
public:
   MainWindow();
   void enableButtons(bool enable);
   void setDisplay(const QString& text);
   void setLogger(const QString& text);
   void setDebugLogger(const QString& text);


   Led *led1;
   Led *led2;

   ManoMeter *manw;
   ManoMeter *manf;

private:
   void createMenu();
   void createHorizontalGroupBoxes();
   void createVerticalGroupBox();
   void createGridGroupBox();
   void createFormGroupBox();

   enum { NumGridRows = 3, NumButtons = 17};

   QMenuBar *menuBar;
   QGroupBox *horizontalGroupBox1;
   QGroupBox *horizontalGroupBox2;
   QGroupBox *gridGroupBox;
   QGroupBox *verticalGroupBox;
   QGroupBox *inputGroupBox;
   QGroupBox *outputGroupBox;
   QGroupBox *meterGroupBox;

   QTextEdit *display;
   QTextEdit *logDisplay;
   QTextEdit *debugDisplay;
   //QLabel *labels[NumGridRows];
   QPushButton *buttons[NumButtons];
   QDialogButtonBox *buttonBox;

   QMenu *fileMenu;
   QAction *exitAction;

   //**************************************************************************
   StateMachine *pStateMachine;
   //SM_settings *pSM_settings;
   event_SM event;

private slots:
   void button0();
   void button1();
   void button2();
   void button3();
   void button4();
   void button5();
   void button6();
   void button7();
   void button8();
   void button9();
   void buttonokay();
   void buttonback();
   void buttonDisableDebug();
   void buttonHideDebug();
   void buttonRowDetected();
   void buttonWallDetected();
   void buttonBackWallDetected();

public slots:
   void toggleLed(Led *Led_tobetoggled);
   void toggleLedback(Led *Led_tobetoggled);
   void setmanometer(ManoMeter *manometer, int i);
};

#endif // MAINWINDOW_H

/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
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
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
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

#include <QtWidgets>

#include "dialog.h"

//! [0]
Dialog::Dialog()
{
   createMenu();
   createHorizontalGroupBox();
   createHorizontalGroupBoxLed();
   createGridGroupBox();
   createFormGroupBox();
   //! [0]
   //!

   //! [1]
   bigEditor = new QTextEdit;
   bigEditor->setPlainText(tr("This widget takes up all the remaining space "
                              "in the top-level layout."));

   buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                    | QDialogButtonBox::Cancel);

   connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
   connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
   //! [1]

   //! [2]
   QVBoxLayout *mainLayout = new QVBoxLayout;
   //! [2] //! [3]
   mainLayout->setMenuBar(menuBar);
   //! [3] //! [4]
   mainLayout->addWidget(horizontalGroupBoxLed);
   mainLayout->addWidget(horizontalGroupBox);
   mainLayout->addWidget(gridGroupBox);
   mainLayout->addWidget(formGroupBox);
   mainLayout->addWidget(bigEditor);
   mainLayout->addWidget(buttonBox);
   //! [4] //! [5]
   setLayout(mainLayout);

   //led->updateWithBackground();

   timer = new QTimer(this);  // toggling led2
   connect(timer, SIGNAL(timeout()), this, SLOT(oneSecondToggleLed2()));
   timer->start(1000);

   setWindowTitle(tr("Basic Layouts LEDSs"));
}
//! [5]

//! [6]
void Dialog::createMenu()
{
   menuBar = new QMenuBar;

   fileMenu = new QMenu(tr("&File"), this);
   exitAction = fileMenu->addAction(tr("E&xit"));
   menuBar->addMenu(fileMenu);

   connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));
}
//! [6]

//! [7]
void Dialog::createHorizontalGroupBox()
{
   horizontalGroupBox = new QGroupBox(tr("Horizontal layout"));
   QHBoxLayout *layout = new QHBoxLayout;

   for (int i = 0; i < NumButtons; ++i) {
      buttons[i] = new QPushButton(tr("Button %1").arg(i + 1));
      layout->addWidget(buttons[i]);
   }
   connect(buttons[0], SIGNAL(pressed()), this, SLOT(toggleLed1()));
   horizontalGroupBox->setLayout(layout);
}
//! [7]

//! [8]
void Dialog::createGridGroupBox()
{
   gridGroupBox = new QGroupBox(tr("Grid layout for LEDs"));
   //! [8]
   QGridLayout *layout = new QGridLayout(this);
   layout->setRowMinimumHeight(0, 40);

   //! [9]
//   for (int i = 0; i < NumGridRows; ++i) {
//      labels[i] = new QLabel(tr("Line %1:").arg(i + 1));
//      lineEdits[i] = new QLineEdit;
//      layout->addWidget(labels[i], i + 1, 0);
//      layout->addWidget(lineEdits[i], i + 1, 1);
//   }

   //! [9] //! [10]
   //smallEditor = new QTextEdit;
   //smallEditor->setPlainText(tr("This widget takes up about two thirds of the "
   //                             "grid layout."));
   //layout->addWidget(smallEditor, 0, 2, 4, 1);
   //! [10]
   //!
   ledg1 = new Led(this);
   QLabel *textl1 = new QLabel("on");
   textl1->setAlignment(Qt::AlignCenter);
   ledg2 = new Led(this);
   QLabel *textl2 = new QLabel("on");
   textl2->setAlignment(Qt::AlignCenter);
   ledg3 = new Led(this);
   QLabel *textl3 = new QLabel("off");
   textl3->setAlignment(Qt::AlignCenter);

   layout->addWidget(ledg1, 0, 0);
   layout->addWidget(textl1, 1, 0);
   layout->addWidget(ledg2, 0, 1);
   layout->addWidget(textl2, 1, 1);
   layout->addWidget(ledg3, 0, 2);
   layout->addWidget(textl3, 1, 2);

   ledg1->setColor(QColor(255,0, 0));
   ledg2->setColor(QColor(0, 255, 0));
   ledg3->setColor(QColor(0,0,255));

   //! [11]
   gridGroupBox->setLayout(layout);
}
//! [11]

//! [12]
void Dialog::createFormGroupBox()
{
   formGroupBox = new QGroupBox(tr("Form layout"));
   QFormLayout *layout = new QFormLayout;
   layout->addRow(new QLabel(tr("Line 1:")), new QLineEdit);
   layout->addRow(new QLabel(tr("Line 2, long text:")), new QComboBox);
   layout->addRow(new QLabel(tr("Line 3:")), new QSpinBox);
   formGroupBox->setLayout(layout);
}
//! [12]

//! [Led]
void Dialog::createHorizontalGroupBoxLed()
{
   horizontalGroupBoxLed = new QGroupBox(tr("Horizontal layout Leds"));
   QHBoxLayout *layout = new QHBoxLayout;
   QLabel *label = new QLabel(this);
   //label->setText("-------------------");

   led = new Led(this);
   led->setColor(QColor(255, 0, 0));
   led->setEnabled(true);
   layout->addWidget(label);
   layout->addWidget(led);
   horizontalGroupBoxLed->setLayout(layout);
}
//!

void Dialog::toggleLed1() {
   led1_ON = !led1_ON;
   if(led1_ON)
      ledg1->setColor(QColor(255,0,0));
   else
      ledg1->setColor(QColor(0,0,0));
}

void Dialog::oneSecondToggleLed2() {
   led2_ON = !led2_ON;
   if(led2_ON)
      ledg2->setColor(QColor(0,255,0));
   else
      ledg2->setColor(QColor(20,20,255));
}


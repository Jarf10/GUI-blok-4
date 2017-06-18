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

#include <QtWidgets>
#include <QColor>
#include <QLabel>
#include <QPixmap>

#include "AppInfo.h"
#include "MainWindow.h"

MainWindow::MainWindow()
{
   pStateMachine = new StateMachine(this);

   createMenu();
   createVerticalGroupBox();
   createHorizontalGroupBoxes();
   createGridGroupBox();

   buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                    | QDialogButtonBox::Cancel);
   connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
   connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

   QVBoxLayout *mainLayout = new QVBoxLayout;
   mainLayout->setMenuBar(menuBar);
   mainLayout->addWidget(horizontalGroupBox2);
   mainLayout->addWidget(horizontalGroupBox1);
   mainLayout->addWidget(gridGroupBox);
   mainLayout->addWidget(buttonBox);

   setLayout(mainLayout);
   setWindowTitle(tr(APPNAME_VERSION));
   pStateMachine->handleEvent(E_SM_initialise);
}

void MainWindow::enableButtons(bool enable) {
   for (int i = 0; i < NumButtons; i++) {
      buttons[i]->setEnabled(enable);
   }
}

void MainWindow::setLogger(const QString &text) {
   logDisplay->moveCursor(QTextCursor::End);
   logDisplay->insertPlainText("\n" + text);
   logDisplay->moveCursor(QTextCursor::End);
}

void MainWindow::setDebugLogger(const QString &text){
   debugDisplay->moveCursor(QTextCursor::End);
   debugDisplay->insertPlainText("\n" + text);
   debugDisplay->moveCursor(QTextCursor::End);
}

void MainWindow::createMenu()
{
   menuBar = new QMenuBar;
   fileMenu = new QMenu(tr("&File"), this);
   exitAction = fileMenu->addAction(tr("E&xit"));
   menuBar->addMenu(fileMenu);
   connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));
}

void MainWindow::createVerticalGroupBox(){

   verticalGroupBox = new QGroupBox(tr("Screen buttons"));
   QVBoxLayout *layout = new QVBoxLayout;

   buttons[12] = new QPushButton(tr("Disable debug screen"));
   buttons[12]->setStyleSheet("background-color: red;");
   layout->addWidget(buttons[12]);
   connect(buttons[12], SIGNAL(released()), this, SLOT(buttonDisableDebug()));

   buttons[13] = new QPushButton(tr("Hide debug screen"));
   buttons[13]->setStyleSheet("background-color: red;");
   layout->addWidget(buttons[13]);
   connect(buttons[13], SIGNAL(released()), this, SLOT(buttonHideDebug()));

   verticalGroupBox->setLayout(layout);

}

void MainWindow::createHorizontalGroupBoxes()
{
   // HorizontalGroupBox 1 -----------------------------------------------------
   horizontalGroupBox1 = new QGroupBox(tr("IO"));
   inputGroupBox = new QGroupBox(tr("Input"));
   outputGroupBox = new QGroupBox(tr("Output"));
   meterGroupBox = new QGroupBox(tr("Meters"));
   QHBoxLayout *layout_IO = new QHBoxLayout;
   QGridLayout *layout_input = new QGridLayout;
   QGridLayout *layout_output = new QGridLayout;
   QVBoxLayout *layout_meters = new QVBoxLayout;

   buttons[0] = new QPushButton(tr("1"));
   layout_input->addWidget(buttons[0], 0, 0);
   connect(buttons[0], SIGNAL(released()), this, SLOT(button1()));

   buttons[1] = new QPushButton(tr("2"));
   layout_input->addWidget(buttons[1], 0, 1);
   connect(buttons[1], SIGNAL(released()), this, SLOT(button2()));

   buttons[2] = new QPushButton(tr("3"));
   layout_input->addWidget(buttons[2], 0 , 2);
   connect(buttons[2], SIGNAL(released()), this, SLOT(button3()));

   buttons[3] = new QPushButton(tr("4"));
   layout_input->addWidget(buttons[3]);
   connect(buttons[3], SIGNAL(released()), this, SLOT(button4()));

   buttons[4] = new QPushButton(tr("5"));
   layout_input->addWidget(buttons[4]);
   connect(buttons[4], SIGNAL(released()), this, SLOT(button5()));

   buttons[5] = new QPushButton(tr("6"));
   layout_input->addWidget(buttons[5]);
   connect(buttons[5], SIGNAL(released()), this, SLOT(button6()));

   buttons[6] = new QPushButton(tr("7"));
   layout_input->addWidget(buttons[6]);
   connect(buttons[6], SIGNAL(released()), this, SLOT(button7()));

   buttons[7] = new QPushButton(tr("8"));
   layout_input->addWidget(buttons[7]);
   connect(buttons[7], SIGNAL(released()), this, SLOT(button8()));

   buttons[8] = new QPushButton(tr("9"));
   layout_input->addWidget(buttons[8]);
   connect(buttons[8], SIGNAL(released()), this, SLOT(button9()));

   buttons[9] = new QPushButton(tr("0"));
   layout_input->addWidget(buttons[9], 4, 1);
   connect(buttons[9], SIGNAL(released()), this, SLOT(button0()));

   buttons[10] = new QPushButton(tr("OKAY"));
   buttons[10]->setStyleSheet("background-color: green;");
   layout_input->addWidget(buttons[10]);
   connect(buttons[10], SIGNAL(released()), this, SLOT(buttonokay()));

   buttons[11] = new QPushButton(tr("BACK"));
   buttons[11]->setStyleSheet("background-color: red;");
   layout_input->addWidget(buttons[11], 4, 0);
   connect(buttons[11], SIGNAL(released()), this, SLOT(buttonback()));

   led1 = new Led(this);
   QLabel *textl1 = new QLabel("Motor1");
   textl1->setAlignment(Qt::AlignCenter);

   layout_output->addWidget(led1, 0, 0);
   layout_output->addWidget(textl1, 1, 0);
   led1->setColor(QColor(0 , 0, 0));

   led2 = new Led(this);
   QLabel *textl2 = new QLabel("Motor2");
   textl2->setAlignment(Qt::AlignCenter);

   layout_output->addWidget(led2, 0, 1);
   layout_output->addWidget(textl2, 1, 1);
   led2->setColor(QColor(0,0,0));

   manw = new ManoMeter(this);
   QLabel *textm1 = new QLabel("Water switch");
   textm1->setAlignment(Qt::AlignCenter);
   manw->setMinimumSize((QSize(150,150)));
   manw->setMaximum(100.0);
   manw->setSuffix(" [%] ");
   manw->setValue(0);
   layout_meters->addWidget(textm1, 0);
   layout_meters->addWidget(manw, 1);

   manf = new ManoMeter(this);
   QLabel *textm2 = new QLabel("Food switch");
   textm2->setAlignment(Qt::AlignCenter);
   manf->setMinimumSize((QSize(150,150)));
   manf->setMaximum(100.0);
   manf->setSuffix(" [%] ");
   manf->setValue(0);
   layout_meters->addWidget(textm2, 2);
   layout_meters->addWidget(manf, 3);

   buttons[14] = new QPushButton(tr("Row detected"));
   buttons[14]->setStyleSheet("background-color: yellow;");
   layout_output->addWidget(buttons[14], 0, 3);
   connect(buttons[14], SIGNAL(released()), this, SLOT(buttonRowDetected()));

   buttons[15] = new QPushButton(tr("Wall Detected"));
   buttons[15]->setStyleSheet("background-color: yellow;");
   layout_output->addWidget(buttons[15], 1, 3);
   connect(buttons[15], SIGNAL(released()), this, SLOT(buttonWallDetected()));

   buttons[16] = new QPushButton(tr("Back wall Detected"));
   buttons[16]->setStyleSheet("background-color: yellow;");
   layout_output->addWidget(buttons[16], 2, 3);
   connect(buttons[16], SIGNAL(released()), this, SLOT(buttonBackWallDetected()));

   inputGroupBox->setLayout(layout_input);
   outputGroupBox->setLayout(layout_output);
   meterGroupBox->setLayout(layout_meters);
   layout_IO->addWidget(inputGroupBox);
   layout_IO->addWidget(outputGroupBox);
   layout_IO->addWidget(meterGroupBox);
   horizontalGroupBox1->setLayout(layout_IO);

   // HorizontalGroupBox 2 -----------------------------------------------------
   horizontalGroupBox2 = new QGroupBox(tr("Screen"));
   QHBoxLayout *layout2 = new QHBoxLayout;

   logDisplay = new QTextEdit("Logging started", this);
   logDisplay->setOverwriteMode(false);
   logDisplay->setReadOnly(true);
   logDisplay->setMinimumHeight(180);
   layout2->addWidget(logDisplay);

   debugDisplay = new QTextEdit("Debug log started", this);
   debugDisplay->setOverwriteMode(false);
   debugDisplay->setReadOnly(true);
   layout2->addWidget(debugDisplay);

   layout2->addWidget(verticalGroupBox);
   horizontalGroupBox2->setLayout(layout2);
   enableButtons(false);
}

void MainWindow::createGridGroupBox()
{
   gridGroupBox = new QGroupBox(tr("Display"));
   QGridLayout *layout = new QGridLayout;

   QPixmap *image1 = new QPixmap(":/jpg/cyclaam.jpg");  // in CVMresources.qrc
   QLabel *label1 = new QLabel;
   label1->setPixmap(*image1);
   label1->setPixmap(image1->scaled(JPG_WIDTH, JPG_HEIGHT, Qt::KeepAspectRatio));
   layout->addWidget(label1, 0, 0);

   QPixmap *image2 = new QPixmap(":/jpg/Malva.jpg");  // in CVMresources.qrc
   QLabel *label2 = new QLabel;
   label2->setPixmap(*image2);
   label2->setPixmap(image2->scaled(JPG_WIDTH, JPG_HEIGHT, Qt::KeepAspectRatio));
   layout->addWidget(label2, 0, 1);

   QPixmap *image3 = new QPixmap(":/jpg/lantana.jpg");  // in CVMresources.qrc
   QLabel *label3 = new QLabel;
   label3->setPixmap(*image3);
   label3->setPixmap(image3->scaled(JPG_WIDTH, JPG_HEIGHT, Qt::KeepAspectRatio));
   layout->addWidget(label3, 0, 2);

   QPixmap *image4 = new QPixmap(":/jpg/Sundeville.jpg");  // in CVMresources.qrc
   QLabel *label4 = new QLabel;
   label4->setPixmap(*image4);
   label4->setPixmap(image4->scaled(JPG_WIDTH, JPG_HEIGHT, Qt::KeepAspectRatio));
   layout->addWidget(label4, 0, 3);

   QPixmap *image5 = new QPixmap(":/jpg/Tibouchina.jpg");  // in CVMresources.qrc
   QLabel *label5 = new QLabel;
   label5->setPixmap(*image5);
   label5->setPixmap(image5->scaled(JPG_WIDTH, JPG_HEIGHT, Qt::KeepAspectRatio));
   layout->addWidget(label5, 0, 4);

   gridGroupBox->setLayout(layout);
}

//----------------------------------------------------------- GUI event handlers
void MainWindow::button0()
{
   pStateMachine->handleEvent(E_PRESSED_0);
}

void MainWindow::button1()
{
   pStateMachine->handleEvent(E_PRESSED_1);
}

void MainWindow::button2()
{
   pStateMachine->handleEvent(E_PRESSED_2);
}

void MainWindow::button3()
{
   pStateMachine->handleEvent(E_PRESSED_3);
}

void MainWindow::button4()
{
   pStateMachine->handleEvent(E_PRESSED_4);
}

void MainWindow::button5()
{
   pStateMachine->handleEvent(E_PRESSED_5);
}

void MainWindow::button6()
{
   pStateMachine->handleEvent(E_PRESSED_6);
}

void MainWindow::button7()
{
   pStateMachine->handleEvent(E_PRESSED_7);
}

void MainWindow::button8()
{
   pStateMachine->handleEvent(E_PRESSED_8);
}

void MainWindow::button9()
{
   pStateMachine->handleEvent(E_PRESSED_9);
}

void MainWindow::buttonokay()
{
   pStateMachine->handleEvent(E_PRESSED_OKAY);
}

void MainWindow::buttonback()
{
   pStateMachine->handleEvent(E_PRESSED_BACK);
}

void MainWindow::buttonDisableDebug()
{
   if(debugDisplay->isEnabled()){
      debugDisplay->setEnabled(false);
   }
   else{debugDisplay->setEnabled(true);}
}

void MainWindow::buttonHideDebug()
{
   if(debugDisplay->isHidden()){
      debugDisplay->show();
   }
   else{debugDisplay->hide();}
}

void MainWindow::buttonRowDetected()
{
   pStateMachine->handleEvent(E_ROW_DETECTED);
}

void MainWindow::buttonWallDetected()
{
   pStateMachine->handleEvent(E_WALL_DETECTED);
}

void MainWindow::buttonBackWallDetected()
{
   pStateMachine->handleEvent(E_BACKWALL_DETECTED);
}

void MainWindow::toggleLed(Led *Led_tobetoggled)
{
   QColor currentcollor = Led_tobetoggled->color();
   if(currentcollor == (QColor(0, 0, 0)))
      Led_tobetoggled->setColor(QColor(0,200,0));
   else
      Led_tobetoggled->setColor(QColor(0,0,0));
}

void MainWindow::toggleLedback(Led *Led_tobetoggled)
{
   QColor currentcollor = Led_tobetoggled->color();
   if(currentcollor == (QColor(0, 0, 0)))
      Led_tobetoggled->setColor(QColor(0,0,200));
   else
      Led_tobetoggled->setColor(QColor(0,0,0));
}

void MainWindow::setmanometer(ManoMeter *manometer, int i)
{
   manometer->setValue(i);
}

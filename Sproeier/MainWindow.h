
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "SM.h"
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

public:
   MainWindow();
   void enableCentButtons(bool enable);
   void setDisplay(const QString& text);
   void setLogger(const QString& text);

private:
   void createMenu();
   void createHorizontalGroupBoxes();
   void createGridGroupBox();
   void createFormGroupBox();

   enum { NumGridRows = 3, NumButtons = 7 };

   QMenuBar *menuBar;
   QGroupBox *horizontalGroupBox1;
   QGroupBox *horizontalGroupBox2;
   QGroupBox *gridGroupBox;

   QTextEdit *display;
   QTextEdit *logDisplay;
   //QLabel *labels[NumGridRows];
   QPushButton *buttons[NumButtons];
   QDialogButtonBox *buttonBox;

   QMenu *fileMenu;
   QAction *exitAction;

   //**************************************************************************
   StateMachine *pStateMachine;
   event_e event;

private slots:
   void coin5C();
   void coin10C();
   void coin20C();
   void coin50C();
   void coin100C();
   void Trash_coin();
   void Return_coin();
};

#endif // MAINWINDOW_H

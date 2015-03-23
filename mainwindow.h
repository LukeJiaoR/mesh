#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#if QT_VERSION >= 0x050000
#include <QtWidgets/QMainWindow>
//#else
//#include <QtGui/QMainWindow>
//#endif
#include "glwidget.h"

class GLWidget;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *e);

private slots:
    void on_actionOPEN_triggered();

private:

    Ui::MainWindow *ui;

    QPushButton *createButton();

    QPushButton *button;

    GLWidget *glWidget;

};

#endif // MAINWINDOW_H

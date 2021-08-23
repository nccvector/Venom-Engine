#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MyOpenGLWidget.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

// private slots:
//     void on_pushButton_clicked();

public:
    Ui::MainWindow *ui;

    MyOpenGLWidget *openglWidget;
};
#endif // MAINWINDOW_H

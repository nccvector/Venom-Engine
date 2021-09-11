#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QTOgreWindow.h"

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

    QTOgreWindow *ogreWindow;
};
#endif // MAINWINDOW_H

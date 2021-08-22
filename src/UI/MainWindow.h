#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Magnum/Platform/GLContext.h> // Platform

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace Magnum;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Platform::GLContext& context, QWidget *parent = nullptr);
    ~MainWindow();

// private slots:
//     void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

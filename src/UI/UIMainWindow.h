/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UIMAINWINDOW_H
#define UIMAINWINDOW_H

#include <QtCore>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include <QDebug>


QT_BEGIN_NAMESPACE

class UIMainWindow
{
public:
    QAction *actionNew;
    QAction *actionSave;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *glContainer;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuView;
    QMenu *menuWindow;
    QMenu *menuHelp;
    QStatusBar *statusbar;
    QDockWidget *HeirarchyPanel;
    QWidget *HeirarchyContents;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QDockWidget *AssetsPanel;
    QWidget *AssetsContent;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButton_3;
    QPushButton *pushButton_9;
    QPushButton *pushButton_6;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButton_2;
    QPushButton *pushButton_7;
    QDockWidget *InspectorPanel;
    QWidget *InspectorContents;
    QVBoxLayout *verticalLayout_5;
    QPushButton *pushButton_8;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1176, 676);
        QFont font;
        font.setFamily(QStringLiteral("Segoe UI"));
        font.setPointSize(10);
        font.setStrikeOut(false);
        MainWindow->setFont(font);

        // Loading stylesheet
        QFile file("stylesheet.qss");
        file.open(QFile::ReadOnly);
        QString stylesheet = QLatin1String(file.readAll());
        MainWindow->setStyleSheet(stylesheet);

        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QStringLiteral("actionCopy"));
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName(QStringLiteral("actionPaste"));
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QStringLiteral("action_2"));
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QStringLiteral("action_3"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        glContainer = new QHBoxLayout();
        glContainer->setObjectName(QStringLiteral("glContainer"));

        horizontalLayout->addLayout(glContainer);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1176, 31));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuWindow = new QMenu(menubar);
        menuWindow->setObjectName(QStringLiteral("menuWindow"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        HeirarchyPanel = new QDockWidget(MainWindow);
        HeirarchyPanel->setObjectName(QStringLiteral("HeirarchyPanel"));
        HeirarchyPanel->setMinimumSize(QSize(160, 60));
        QFont font1;
        font1.setFamily(QStringLiteral("Segoe UI"));
        font1.setPointSize(10);
        font1.setStrikeOut(true);
        HeirarchyPanel->setFont(font1);
        HeirarchyPanel->setStyleSheet(QStringLiteral("border-color: rgb(238, 238, 236);"));
        HeirarchyContents = new QWidget();
        HeirarchyContents->setObjectName(QStringLiteral("HeirarchyContents"));
        verticalLayout = new QVBoxLayout(HeirarchyContents);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton = new QPushButton(HeirarchyContents);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        HeirarchyPanel->setWidget(HeirarchyContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), HeirarchyPanel);
        AssetsPanel = new QDockWidget(MainWindow);
        AssetsPanel->setObjectName(QStringLiteral("AssetsPanel"));
        AssetsPanel->setMinimumSize(QSize(291, 160));
        AssetsContent = new QWidget();
        AssetsContent->setObjectName(QStringLiteral("AssetsContent"));
        horizontalLayout_2 = new QHBoxLayout(AssetsContent);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        pushButton_4 = new QPushButton(AssetsContent);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        verticalLayout_2->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(AssetsContent);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        verticalLayout_2->addWidget(pushButton_5);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        pushButton_3 = new QPushButton(AssetsContent);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout_3->addWidget(pushButton_3);

        pushButton_9 = new QPushButton(AssetsContent);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));

        verticalLayout_3->addWidget(pushButton_9);

        pushButton_6 = new QPushButton(AssetsContent);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        verticalLayout_3->addWidget(pushButton_6);


        horizontalLayout_2->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        pushButton_2 = new QPushButton(AssetsContent);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout_4->addWidget(pushButton_2);

        pushButton_7 = new QPushButton(AssetsContent);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        verticalLayout_4->addWidget(pushButton_7);


        horizontalLayout_2->addLayout(verticalLayout_4);

        AssetsPanel->setWidget(AssetsContent);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(8), AssetsPanel);
        InspectorPanel = new QDockWidget(MainWindow);
        InspectorPanel->setObjectName(QStringLiteral("InspectorPanel"));
        InspectorPanel->setMinimumSize(QSize(160, 62));
        InspectorContents = new QWidget();
        InspectorContents->setObjectName(QStringLiteral("InspectorContents"));
        verticalLayout_5 = new QVBoxLayout(InspectorContents);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        pushButton_8 = new QPushButton(InspectorContents);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        verticalLayout_5->addWidget(pushButton_8);

        InspectorPanel->setWidget(InspectorContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), InspectorPanel);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuWindow->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionSave);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuView->addAction(action);
        menuWindow->addAction(action_2);
        menuHelp->addAction(action_3);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionNew->setText(QApplication::translate("MainWindow", "New", Q_NULLPTR));
        actionSave->setText(QApplication::translate("MainWindow", "Save", Q_NULLPTR));
        actionCopy->setText(QApplication::translate("MainWindow", "Copy", Q_NULLPTR));
        actionPaste->setText(QApplication::translate("MainWindow", "Paste", Q_NULLPTR));
        action->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        action_2->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        action_3->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", Q_NULLPTR));
        menuView->setTitle(QApplication::translate("MainWindow", "View", Q_NULLPTR));
        menuWindow->setTitle(QApplication::translate("MainWindow", "Window", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
        pushButton_9->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
        pushButton_8->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public UIMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
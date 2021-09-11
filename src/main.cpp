#include "MainWindow.h"

#include <QtCore>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    // Loading stylesheet
    QFile file("BreezeDark.qss");
    file.open(QFile::ReadOnly);
    QString stylesheet = QLatin1String(file.readAll());
    w.setStyleSheet(stylesheet);

    return a.exec();
}


// /*

// Place the include along with your other includes where you will be creating and/or calling the above QTOgreWindow:

// */


// #include "QTOgreWindow.h"

// /*

// In the method you are creating/calling a QTOgreWindow:

// */

// QTOgreWindow* ogreWindow = new QTOgreWindow();
// QWidget* renderingContainer = QWidget::createWindowContainer(ogreWindow);

// /*

// As an example, the below method places the QTOgreWindow we just created inside of a QTabWidget as a tab.

// */

// mainTabs->addTab(renderingContainer, tr("New Ogre Window"));
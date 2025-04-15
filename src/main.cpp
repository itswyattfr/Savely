#include "include/mainwindow.h"
#include <QApplication>
#include <QDir>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QDir qmlDir(QCoreApplication::applicationDirPath() + "/qml");
    if (!qmlDir.exists())
    {
        qWarning() << "QML directory does not exist:" << qmlDir.path();
        return -1;
    }

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
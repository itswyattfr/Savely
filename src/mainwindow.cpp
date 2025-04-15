#include "include/mainwindow.h"

#include <QQmlApplicationEngine>
#include <QQuickWidget>
#include <QVBoxLayout>
#include <QFile>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    setupUI();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QQuickWidget *qmlWidget = new QQuickWidget(this);
    qmlWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

    QString qmlFilePath = QCoreApplication::applicationDirPath() + "/qml/main.ui.qml";
    if (QFile::exists(qmlFilePath))
    {
        qmlWidget->setSource(QUrl::fromLocalFile(qmlFilePath));
    }
    else
    {
        qDebug() << "QML UI file not found:" << qmlFilePath;
    }

    mainLayout->addWidget(qmlWidget);
    setCentralWidget(centralWidget);
}
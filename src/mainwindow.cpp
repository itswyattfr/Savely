#include "include/mainwindow.h"

#include <QTabWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QListWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QTextEdit>
#include <QLineEdit>
#include <QFormLayout>
#include <QMenu>
#include <QPainterPath>
#include <QPainter>
#include <QRegion>
#include <QScreen>
#include <QDialog>
#include <QTextBrowser>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), isDragging(false), networkManager(new QNetworkAccessManager(this))
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    currentVersion = "1.0.0";

    setupUI();
    setupStyleSheet();
    applyRoundedCorners();
    fetchLatestVersion();

    resize(800, 600);
    setWindowTitle("Savely - Game Save Manager");
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    createTitleBar();
    mainLayout->addWidget(titleBar);

    createTabWidget();
    mainLayout->addWidget(tabWidget);

    setCentralWidget(centralWidget);
}

void MainWindow::createTitleBar()
{
    titleBar = new QWidget(this);
    titleBar->setObjectName("titleBar");
    titleBar->setFixedHeight(40);

    QHBoxLayout *titleLayout = new QHBoxLayout(titleBar);
    titleLayout->setContentsMargins(15, 0, 10, 0);

    logoLabel = new QLabel("SAVELY", titleBar);
    logoLabel->setObjectName("logoLabel");

    menuButton = new QPushButton("≡", titleBar);
    menuButton->setObjectName("menuButton");
    menuButton->setFixedSize(30, 30);
    
    optionsMenu = new QMenu(this);
    optionsMenu->addAction("Settings", this, &MainWindow::showSettingsDialog);
    optionsMenu->addAction("Plugins", this, &MainWindow::showPluginsDialog);
    optionsMenu->addAction("Info", this, &MainWindow::showInfoDialog);

    minimizeButton = new QPushButton("−", titleBar);
    minimizeButton->setObjectName("minimizeButton");
    minimizeButton->setFixedSize(30, 30);

    closeButton = new QPushButton("×", titleBar);
    closeButton->setObjectName("closeButton");
    closeButton->setFixedSize(30, 30);

    titleLayout->addWidget(logoLabel);
    titleLayout->addStretch();
    titleLayout->addWidget(menuButton);
    titleLayout->addSpacing(5);
    titleLayout->addWidget(minimizeButton);
    titleLayout->addWidget(closeButton);

    connect(closeButton, &QPushButton::clicked, this, &MainWindow::closeApplication);
    connect(minimizeButton, &QPushButton::clicked, this, &MainWindow::minimizeApplication);
    connect(menuButton, &QPushButton::clicked, this, &MainWindow::showMenuOptions);
}

void MainWindow::createTabWidget()
{
    tabWidget = new QTabWidget(this);
    tabWidget->setObjectName("tabWidget");
    
    QWidget *saveCollectionTab = new QWidget(tabWidget);
    QVBoxLayout *saveCollectionLayout = new QVBoxLayout(saveCollectionTab);

    QListWidget *saveList = new QListWidget(saveCollectionTab);
    saveList->setObjectName("saveList");

    QPushButton *importSaveButton = new QPushButton("Import Save", saveCollectionTab);
    QPushButton *exportSaveButton = new QPushButton("Export Save", saveCollectionTab);
    QPushButton *deleteSaveButton = new QPushButton("Delete Save", saveCollectionTab);

    QHBoxLayout *saveButtonsLayout = new QHBoxLayout();
    saveButtonsLayout->addWidget(importSaveButton);
    saveButtonsLayout->addWidget(exportSaveButton);
    saveButtonsLayout->addWidget(deleteSaveButton);

    saveCollectionLayout->addWidget(new QLabel("Your Saves:"));
    saveCollectionLayout->addWidget(saveList);
    saveCollectionLayout->addLayout(saveButtonsLayout);

    QWidget *gameManagerTab = new QWidget(tabWidget);
    QVBoxLayout *gameManagerLayout = new QVBoxLayout(gameManagerTab);

    QListWidget *gameList = new QListWidget(gameManagerTab);
    gameList->setObjectName("gameList");


    // Sample Games
    gameList->addItem("Elden Ring");
    gameList->addItem("Cyberpunk 2077");
    gameList->addItem("Baldur's Gate 3");
    gameList->addItem("Starfield");

    QPushButton *addGameButton = new QPushButton("Add Game", gameManagerTab);
    QPushButton *removeGameButton = new QPushButton("Remove Game", gameManagerTab);
    QPushButton *configurePathsButton = new QPushButton("Configure Paths", gameManagerTab);

    QHBoxLayout *gameButtonsLayout = new QHBoxLayout();
    gameButtonsLayout->addWidget(addGameButton);
    gameButtonsLayout->addWidget(removeGameButton);
    gameButtonsLayout->addWidget(configurePathsButton);

    gameManagerLayout->addWidget(new QLabel("Games:"));
    gameManagerLayout->addWidget(gameList);
    gameManagerLayout->addLayout(gameButtonsLayout);


    QWidget *settingsTab = new QWidget(tabWidget);
    QVBoxLayout *settingsLayout = new QVBoxLayout(settingsTab);

    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("Default Save Location:", new QLineEdit("/Users/Saves"));
    formLayout->addRow("Backup Frequency:", new QLineEdit("Daily"));
    formLayout->addRow("Theme:", new QLineEdit("Dark"));

    QPushButton *saveSettingsButton = new QPushButton("Save Settings", settingsTab);
    saveSettingsButton->setObjectName("actionButton");

    settingsLayout->addLayout(formLayout);
    settingsLayout->addStretch();
    settingsLayout->addWidget(saveSettingsButton);

    tabWidget->addTab(saveCollectionTab, "Save Collection");
    tabWidget->addTab(gameManagerTab, "Game Manager");
    tabWidget->addTab(settingsTab, "Settings");
}

void MainWindow::setupStyleSheet()
{
    // TODO: Reformat Styling, possibly implement it better
    setStyleSheet(R"(
        QMainWindow {
            background-color: transparent;
        }
        
        QWidget#centralWidget {
            background-color: #2D2D2D;
            border-radius: 10px;
        }
        
        #titleBar {
            background-color: #1E1E1E;
            border-top-left-radius: 10px;
            border-top-right-radius: 10px;
            border-bottom: 1px solid #444444;
        }
        
        #logoLabel {
            color: #4A9EFF;
            font-size: 16px;
            font-weight: bold;
        }
        
        #minimizeButton, #closeButton, #menuButton {
            background-color: transparent;
            border: none;
            color: #AAAAAA;
            font-size: 16px;
            border-radius: 15px;
        }
        
        #menuButton {
            font-size: 18px;
            font-weight: bold;
        }
        
        #minimizeButton:hover, #closeButton:hover, #menuButton:hover {
            background-color: #444444;
        }
        
        #closeButton:hover {
            color: #FF6B6B;
        }
        
        #menuButton:hover {
            color: #4A9EFF;
        }
        
        QTabWidget::pane {
            border: none;
            background-color: #2D2D2D;
            border-bottom-left-radius: 10px;
            border-bottom-right-radius: 10px;
        }
        
        QTabBar::tab {
            background-color: #1E1E1E;
            color: #BBBBBB;
            padding: 8px 20px;
            border: 1px solid #444444;
            border-bottom: none;
            border-top-left-radius: 4px;
            border-top-right-radius: 4px;
            min-width: 120px;
        }
        
        QTabBar::tab:selected {
            background-color: #3A3A3A;
            color: #FFFFFF;
        }
        
        QListWidget {
            background-color: #363636;
            border: 1px solid #444444;
            border-radius: 4px;
            color: #FFFFFF;
        }
        
        QPushButton {
            background-color: #4A9EFF;
            color: #FFFFFF;
            border: none;
            border-radius: 4px;
            padding: 6px 16px;
        }
        
        QPushButton:hover {
            background-color: #3A8EEF;
        }
        
        QPushButton:pressed {
            background-color: #2A7EDF;
        }
        
        QLabel {
            color: #FFFFFF;
            font-size: 12px;
        }
        
        QLineEdit {
            background-color: #363636;
            border: 1px solid #444444;
            border-radius: 4px;
            padding: 5px;
            color: #FFFFFF;
        }
        
        #actionButton {
            background-color: #5FB75F;
        }
        
        #actionButton:hover {
            background-color: #4FA74F;
        }
        
        QMenu {
            background-color: #2D2D2D;
            border: 1px solid #444444;
            border-radius: 5px;
            padding: 5px;
        }
        
        QMenu::item {
            padding: 5px 25px 5px 20px;
            color: #FFFFFF;
        }
        
        QMenu::item:selected {
            background-color: #4A9EFF;
            color: #FFFFFF;
        }
        
        QDialog {
            background-color: #2D2D2D;
            border: 1px solid #444444;
            border-radius: 10px;
        }
        
        QTextBrowser {
            background-color: #363636;
            border: 1px solid #444444;
            border-radius: 4px;
            color: #FFFFFF;
        }
    )");
}

void MainWindow::applyRoundedCorners()
{
    QPainterPath path;
    path.addRoundedRect(rect(), 10, 10);
    QRegion mask = QRegion(path.toFillPolygon().toPolygon());
    setMask(mask);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    path.addRoundedRect(rect(), 10, 10);
    painter.fillPath(path, QColor(45, 45, 45));

    painter.setPen(QPen(QColor(68, 68, 68), 1));
    painter.drawPath(path);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (titleBar->rect().contains(event->pos()) && event->button() == Qt::LeftButton)
    {
        isDragging = true;
        dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (isDragging && (event->buttons() & Qt::LeftButton))
    {
        move(event->globalPosition().toPoint() - dragPosition);
        event->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isDragging = false;
    }
}

void MainWindow::showMenuOptions()
{
    optionsMenu->exec(menuButton->mapToGlobal(QPoint(0, menuButton->height())));
}

void MainWindow::showSettingsDialog()
{
    QMessageBox::information(this, "Settings", "Settings dialog would open here.");
}

void MainWindow::showPluginsDialog()
{
    QMessageBox::information(this, "Plugins", "Plugins dialog would open here.");
}

void MainWindow::showInfoDialog()
{
    QDialog infoDialog(this);
    infoDialog.setWindowTitle("Savely Information");
    infoDialog.setFixedSize(400, 300);
    infoDialog.setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    infoDialog.setAttribute(Qt::WA_TranslucentBackground);

    QVBoxLayout *layout = new QVBoxLayout(&infoDialog);


    QWidget *dialogTitleBar = new QWidget(&infoDialog);
    dialogTitleBar->setObjectName("titleBar");
    dialogTitleBar->setFixedHeight(40);

    QHBoxLayout *dialogTitleLayout = new QHBoxLayout(dialogTitleBar);
    dialogTitleLayout->setContentsMargins(15, 0, 10, 0);

    QLabel *dialogTitle = new QLabel("Application Information", dialogTitleBar);
    dialogTitle->setObjectName("logoLabel");

    QPushButton *dialogCloseButton = new QPushButton("×", dialogTitleBar);
    dialogCloseButton->setObjectName("closeButton");
    dialogCloseButton->setFixedSize(30, 30);

    dialogTitleLayout->addWidget(dialogTitle);
    dialogTitleLayout->addStretch();
    dialogTitleLayout->addWidget(dialogCloseButton);

    QTextBrowser *infoBrowser = new QTextBrowser(&infoDialog);
    infoBrowser->setOpenExternalLinks(true);

    QString infoText = "<h2>Savely - Game Save Manager</h2>";
    infoText += "<p>Current Version: " + currentVersion + "</p>";
    infoText += "<p>Latest Version: " + (latestVersion.isEmpty() ? "Checking..." : latestVersion) + "</p>";
    infoText += "<p>Savely is a powerful save manager for your games.</p>";
    infoText += "<p>Features:</p>";
    infoText += "<ul>";
    infoText += "<li>Organize game saves</li>";
    infoText += "<li>Back up your progress</li>";
    infoText += "<li>Manage multiple games</li>";
    infoText += "<li>Customize save locations</li>";
    infoText += "</ul>";
    infoText += "<p>Visit <a href='https://github.com/savely/savely'>GitHub Repository</a></p>";
    infoBrowser->setHtml(infoText);

    QPushButton *closeInfoButton = new QPushButton("Close", &infoDialog);

    layout->addWidget(dialogTitleBar);
    layout->addWidget(infoBrowser);
    layout->addWidget(closeInfoButton);

    connect(dialogCloseButton, &QPushButton::clicked, &infoDialog, &QDialog::accept);
    connect(closeInfoButton, &QPushButton::clicked, &infoDialog, &QDialog::accept);
  
    QPainterPath path;
    path.addRoundedRect(infoDialog.rect(), 10, 10);
    infoDialog.setMask(QRegion(path.toFillPolygon().toPolygon()));

  
    infoDialog.exec();
}

void MainWindow::fetchLatestVersion()
{
    QUrl apiUrl("https://api.github.com/repos/itswyattfr/savely/releases/latest");
    QNetworkRequest request(apiUrl);

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, [this, reply]()
            { onVersionInfoReceived(reply); });
}

void MainWindow::onVersionInfoReceived(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject obj = doc.object();

        if (obj.contains("tag_name"))
        {
            latestVersion = obj["tag_name"].toString();
            if (latestVersion.startsWith('v'))
            {
                latestVersion.remove(0, 1);
            }
        }
    }
    else
    {
        latestVersion = "Failed to fetch";
    }

    reply->deleteLater();
}

void MainWindow::closeApplication()
{
    QApplication::quit();
}

void MainWindow::minimizeApplication()
{
    setWindowState(Qt::WindowMinimized);
}

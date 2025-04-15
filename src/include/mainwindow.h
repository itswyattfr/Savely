#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPoint>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class QTabWidget;
class QPushButton;
class QMenu;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void closeApplication();
    void minimizeApplication();
    void showMenuOptions();
    void showSettingsDialog();
    void showPluginsDialog();
    void showInfoDialog();
    void onVersionInfoReceived(QNetworkReply *reply);

private:
    void setupUI();
    void createTitleBar();
    void createTabWidget();
    void setupStyleSheet();
    void applyRoundedCorners();
    void fetchLatestVersion();

    QTabWidget *tabWidget;
    QPushButton *closeButton;
    QPushButton *minimizeButton;
    QPushButton *menuButton;
    QMenu *optionsMenu;
    QWidget *titleBar;
    QLabel *logoLabel;

    bool isDragging;
    QPoint dragPosition;

    QNetworkAccessManager *networkManager;
    QString latestVersion;
    QString currentVersion;
};

#endif // MAINWINDOW_H
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

class QLineEdit;
class QLabel;
class QPushButton;
class QStackedWidget;
class QWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    // Navigation
    void showHomePage();
    void showBagTagPage();

    // Printing
    void printDC();
    void printNL();
    void printMH();

private:
    // Pages
    QWidget *createHomePage();
    QWidget *createBagTagPage();

    // Helpers
    QPushButton *createMenuButton(const QString &text);
    QPushButton *createBagButton(const QString &text);

    // Printing
    void printBagTag(const QString &bagType);

    // Main page controller
    QStackedWidget *pages;

    // Bag tag widgets
    QLineEdit *initial;
    QLabel *printerStatus;
};

#endif
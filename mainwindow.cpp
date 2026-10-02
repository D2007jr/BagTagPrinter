#include "mainwindow.h"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QMessageBox>
#include <QDateTime>
#include <QFont>
#include <QApplication>

#include <QPrinter>
#include <QPrinterInfo>
#include <QPainter>
#include <QPageSize>
#include <QPageLayout>
#include <QMarginsF>
#include <QIcon>






// =====================================================
// MAIN WINDOW
// =====================================================

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowIcon(QIcon(":/Oceanside_Utility_Printer.ico"));
    setWindowTitle("Bag Tag Printer Utility");

    resize(800, 550);

    // ---------------------------------------------
    // STACKED WIDGET
    // ---------------------------------------------

    pages = new QStackedWidget(this);

    setCentralWidget(pages);

    // Create our pages
    pages->addWidget(createHomePage());
    pages->addWidget(createBagTagPage());

    // Start on Home
    pages->setCurrentIndex(0);
}


// =====================================================
// HOME PAGE
// =====================================================

QWidget *MainWindow::createHomePage()
{
    QWidget *page = new QWidget();

    QVBoxLayout *layout = new QVBoxLayout(page);

    layout->setContentsMargins(60, 40, 60, 40);
    layout->setSpacing(25);


    // -------------------------------------------------
    // TITLE
    // -------------------------------------------------

    QLabel *company = new QLabel("OCEANSIDE CLEANERS");

    QFont companyFont;
    companyFont.setPointSize(28);
    companyFont.setBold(true);

    company->setFont(companyFont);
    company->setAlignment(Qt::AlignCenter);


    QLabel *subtitle = new QLabel("BAG TAG SYSTEM");

    QFont subtitleFont;
    subtitleFont.setPointSize(18);

    subtitle->setFont(subtitleFont);
    subtitle->setAlignment(Qt::AlignCenter);


    layout->addStretch();

    layout->addWidget(company);
    layout->addWidget(subtitle);

    layout->addSpacing(35);


    // -------------------------------------------------
    // MENU BUTTONS
    // -------------------------------------------------

    QPushButton *bagTagsButton =
        createMenuButton("BAG TAGS");

    QPushButton *settingsButton =
        createMenuButton("SETTINGS");

    QPushButton *exitButton =
        createMenuButton("EXIT");

    layout->addWidget(bagTagsButton);
    layout->addWidget(settingsButton);
    layout->addWidget(exitButton);

    layout->addStretch();


    // -------------------------------------------------
    // BUTTON CONNECTIONS
    // -------------------------------------------------

    connect(
        bagTagsButton,
        &QPushButton::clicked,
        this,
        &MainWindow::showBagTagPage
        );


   //PLACEHOLDER
    connect(
        settingsButton,
        &QPushButton::clicked,
        this,
        [this]()
        {
            QMessageBox::information(
                this,
                "Settings",
                "PLACEHOLDER");
        }
        );


    connect(
        exitButton,
        &QPushButton::clicked,
        qApp,
        &QApplication::quit
        );


    return page;
}


// =====================================================
// BAG TAG PAGE
// =====================================================

QWidget *MainWindow::createBagTagPage()
{
    QWidget *page = new QWidget();

    QVBoxLayout *mainLayout =
        new QVBoxLayout(page);

    mainLayout->setContentsMargins(
        40,
        30,
        40,
        30
        );

    mainLayout->setSpacing(20);


    // -------------------------------------------------
    // TITLE
    // -------------------------------------------------

    QLabel *title =
        new QLabel("BAG TAG Utility");

    QFont titleFont;
    titleFont.setPointSize(26);
    titleFont.setBold(true);

    title->setFont(titleFont);

    title->setAlignment(
        Qt::AlignCenter
        );

    mainLayout->addWidget(title);

    mainLayout->addSpacing(20);


    // -------------------------------------------------
    // INITIALS
    // -------------------------------------------------

    QHBoxLayout *initialLayout =
        new QHBoxLayout();


    QLabel *initialLabel =
        new QLabel("Initials:");

    QFont labelFont;
    labelFont.setPointSize(18);
    labelFont.setBold(true);

    initialLabel->setFont(labelFont);


    initial =
        new QLineEdit();

    initial->setPlaceholderText(
        "Example: DN"
        );

    initial->setMaxLength(3);

    initial->setFixedHeight(55);


    QFont inputFont;
    inputFont.setPointSize(22);

    initial->setFont(inputFont);


    initialLayout->addWidget(
        initialLabel
        );

    initialLayout->addWidget(
        initial
        );


    mainLayout->addLayout(
        initialLayout
        );

    mainLayout->addSpacing(25);


    // -------------------------------------------------
    // BAG BUTTONS
    // -------------------------------------------------

    QHBoxLayout *buttonLayout =
        new QHBoxLayout();

    buttonLayout->setSpacing(15);


    QPushButton *dcButton =
        createBagButton("DC");

    QPushButton *nlButton =
        createBagButton("N/L");

    QPushButton *mhButton =
        createBagButton("M/H");


    buttonLayout->addWidget(dcButton);

    buttonLayout->addWidget(nlButton);

    buttonLayout->addWidget(mhButton);


    mainLayout->addLayout(
        buttonLayout
        );


    mainLayout->addSpacing(20);


    // -------------------------------------------------
    // PRINTER STATUS
    // -------------------------------------------------

    printerStatus =
        new QLabel();

    QFont statusFont;
    statusFont.setPointSize(12);

    printerStatus->setFont(
        statusFont
        );

    printerStatus->setAlignment(
        Qt::AlignCenter
        );


    mainLayout->addWidget(
        printerStatus
        );


    // -------------------------------------------------
    // CHECK FOR EPSON
    // -------------------------------------------------

    bool epsonFound = false;

    const QList<QPrinterInfo> printers =
        QPrinterInfo::availablePrinters();


    for (const QPrinterInfo &printer : printers)
    {
        if (
            printer.printerName().contains(
                "EPSON",
                Qt::CaseInsensitive
                )
            )
        {
            epsonFound = true;

            printerStatus->setText(
                "Printer Ready: "
                + printer.printerName()
                );

            break;
        }
    }


    if (!epsonFound)
    {
        printerStatus->setText(
            "WARNING: EPSON printer not found."
            );
    }


    mainLayout->addStretch();


    // -------------------------------------------------
    // BACK BUTTON
    // -------------------------------------------------

    QPushButton *backButton =
        new QPushButton("BACK");


    backButton->setFixedHeight(60);


    QFont backFont;
    backFont.setPointSize(18);
    backFont.setBold(true);

    backButton->setFont(
        backFont
        );


    backButton->setStyleSheet(
        "QPushButton {"
        "background-color: #555555;"
        "color: white;"
        "border-radius: 10px;"
        "}"
        ""
        "QPushButton:hover {"
        "background-color: #444444;"
        "}"
        ""
        "QPushButton:pressed {"
        "background-color: #333333;"
        "}"
        );


    mainLayout->addWidget(
        backButton
        );


    // -------------------------------------------------
    // CONNECTIONS
    // -------------------------------------------------

    connect(
        dcButton,
        &QPushButton::clicked,
        this,
        &MainWindow::printDC
        );


    connect(
        nlButton,
        &QPushButton::clicked,
        this,
        &MainWindow::printNL
        );


    connect(
        mhButton,
        &QPushButton::clicked,
        this,
        &MainWindow::printMH
        );


    connect(
        backButton,
        &QPushButton::clicked,
        this,
        &MainWindow::showHomePage
        );


    return page;
}


// =====================================================
// NAVIGATION
// =====================================================

void MainWindow::showHomePage()
{
    pages->setCurrentIndex(0);
}


void MainWindow::showBagTagPage()
{
    pages->setCurrentIndex(1);

    // Automatically put cursor
    // in Initials box
    initial->setFocus();
}


// =====================================================
// HOME MENU BUTTON
// =====================================================

QPushButton *MainWindow::createMenuButton(
    const QString &text)
{
    QPushButton *button =
        new QPushButton(text);


    button->setMinimumHeight(80);


    QFont font;
    font.setPointSize(22);
    font.setBold(true);

    button->setFont(font);


    button->setStyleSheet(
        "QPushButton {"
        "background-color: #1f4fd8;"
        "color: white;"
        "border-radius: 12px;"
        "padding: 10px;"
        "}"
        ""
        "QPushButton:hover {"
        "background-color: #183fae;"
        "}"
        ""
        "QPushButton:pressed {"
        "background-color: #102d82;"
        "}"
        );


    return button;
}


// =====================================================
// BAG TYPE BUTTON
// =====================================================

QPushButton *MainWindow::createBagButton(
    const QString &text)
{
    QPushButton *button =
        new QPushButton(text);


    button->setMinimumSize(
        180,
        120
        );


    QFont font;
    font.setPointSize(30);
    font.setBold(true);

    button->setFont(font);


    button->setStyleSheet(
        "QPushButton {"
        "background-color: #1f77ff;"
        "color: white;"
        "border-radius: 12px;"
        "}"
        ""
        "QPushButton:hover {"
        "background-color: #155dcc;"
        "}"
        ""
        "QPushButton:pressed {"
        "background-color: #0f469b;"
        "}"
        );


    return button;
}


// =====================================================
// PRINT BUTTON FUNCTIONS
// =====================================================

void MainWindow::printDC()
{
    printBagTag("DC");
}


void MainWindow::printNL()
{
    printBagTag("N/L");
}


void MainWindow::printMH()
{
    printBagTag("M/H");
}


// =====================================================
// PRINT BAG TAG
// =====================================================

void MainWindow::printBagTag(
    const QString &bagType)
{
    QString dn =
        initial->text().trimmed();


    // -------------------------------------------------
    // REQUIRE INITIALS
    // -------------------------------------------------

    if (dn.isEmpty())
    {
        QMessageBox::warning(
            this,
            "Initials Required",
            "Please enter Initials before printing."
            );

        initial->setFocus();

        return;
    }


    // -------------------------------------------------
    // FIND EPSON PRINTER
    // -------------------------------------------------

    QString printerName;


    const QList<QPrinterInfo> printers =
        QPrinterInfo::availablePrinters();


    for (
        const QPrinterInfo &printerInfo :
        printers
        )
    {
        if (
            printerInfo.printerName().contains(
                "EPSON",
                Qt::CaseInsensitive
                )
            )
        {
            printerName =
                printerInfo.printerName();

            break;
        }
    }


    if (printerName.isEmpty())
    {
        QMessageBox::critical(
            this,
            "Printer Error",
            "EPSON printer could not be found."
            );

        return;
    }


    // -------------------------------------------------
    // CREATE PRINTER
    // -------------------------------------------------

    QPrinter printer(
        QPrinter::HighResolution
        );


    printer.setPrinterName(
        printerName
        );


    // -------------------------------------------------
    // TAG SIZE
    // -------------------------------------------------

    QPageSize tagSize(
        QSizeF(80.0, 50.0),
        QPageSize::Millimeter,
        "BagTag"
        );


    QPageLayout pageLayout(
        tagSize,
        QPageLayout::Portrait,
        QMarginsF(0, 0, 0, 0),
        QPageLayout::Millimeter
        );


    printer.setPageLayout(
        pageLayout
        );


    printer.setFullPage(true);


    // -------------------------------------------------
    // START PRINTER
    // -------------------------------------------------

    QPainter painter;


    if (!painter.begin(&printer))
    {
        QMessageBox::critical(
            this,
            "Printing Error",
            "Could not start printer."
            );

        return;
    }


    QRectF page =
        printer.pageRect(
            QPrinter::DevicePixel
            );


    // -------------------------------------------------
    // ROTATE TAG SIDEWAYS
    // -------------------------------------------------

    painter.translate(
        page.width(),
        0
        );


    painter.rotate(90);


    QRectF tag(
        0,
        0,
        page.height(),
        page.width()
        );


    const qreal margin = 45;


    QRectF content =
        tag.adjusted(
            margin,
            margin,
            -margin,
            -margin
            );


    // -------------------------------------------------
    // INITIALS
    // -------------------------------------------------

    QFont dnFont("Arial");

    dnFont.setPixelSize(42);
    dnFont.setBold(true);

    painter.setFont(
        dnFont
        );


    QRectF dnRect(
        content.left(),
        content.top(),
        content.width() * 0.35,
        content.height() * 0.25
        );


    painter.drawText(
        dnRect,
        Qt::AlignLeft |
            Qt::AlignTop,
        dn
        );


    // -------------------------------------------------
    // BAG TYPE
    // -------------------------------------------------

    QFont bagFont("Arial");

    bagFont.setPixelSize(100);
    bagFont.setBold(true);

    painter.setFont(
        bagFont
        );


    painter.drawText(
        content,
        Qt::AlignCenter,
        bagType
        );


    // -------------------------------------------------
    // CURRENT DATE / TIME
    // -------------------------------------------------

    QDateTime now =
        QDateTime::currentDateTime();


    QString dateTime =
        now.toString("h:mm AP")
        +
        "\n"
        +
        now.toString("MM/dd/yy");


    QFont dateFont("Arial");

    dateFont.setPixelSize(32);
    dateFont.setBold(true);

    painter.setFont(
        dateFont
        );


    QRectF dateRect(
        content.left()
            + content.width() * 0.65,

        content.top()
            + content.height() * 0.65,

        content.width() * 0.35,

        content.height() * 0.35
        );


    painter.drawText(
        dateRect,
        Qt::AlignRight |
            Qt::AlignBottom,
        dateTime
        );


    // -------------------------------------------------
    // FINISH
    // -------------------------------------------------

    painter.end();
}
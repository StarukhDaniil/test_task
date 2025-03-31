#include "mainwindow.h"
#include "myconstants.h"
//#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QObject>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , centralWidget(new QWidget())
    , layout(new QGridLayout())
    , resetBtn(new QPushButton("Reset"))
    , writeAddrBtn(new QPushButton("Write address"))
    , readAddrBtn(new QPushButton("Read address"))
    , addrLabel(new QLabel("Address:"))
    , addrInput(new QLineEdit())
{

    // changing font for each element
    QFont mainFont;
    mainFont.setPointSize(16);
    resetBtn->setFont(mainFont);
    writeAddrBtn->setFont(mainFont);
    readAddrBtn->setFont(mainFont);
    addrLabel->setFont(mainFont);
    addrInput->setFont(mainFont);

    // resizing elements
    resetBtn->setMinimumSize(myConstants::basicMinBtnWidth, myConstants::basicMinBtnHeight);
    writeAddrBtn->setMinimumSize(myConstants::basicMinBtnWidth, myConstants::basicMinBtnHeight);
    readAddrBtn->setMinimumSize(myConstants::basicMinBtnWidth, myConstants::basicMinBtnHeight);
    addrInput->setMinimumSize(myConstants::basicMinLineEditWidth, myConstants::basicMinLineEditHeight);
    addrLabel->setMinimumSize(myConstants::basicMinLabelWidth, myConstants::basicMinLabelHeight);
    resetBtn->setMaximumSize(myConstants::basicMaxBtnWidth, myConstants::basicMaxBtnHeight);
    writeAddrBtn->setMaximumSize(myConstants::basicMaxBtnWidth, myConstants::basicMaxBtnHeight);
    readAddrBtn->setMaximumSize(myConstants::basicMaxBtnWidth, myConstants::basicMaxBtnHeight);
    addrInput->setMaximumSize(myConstants::basicMaxLineEditWidth, myConstants::basicMaxLineEditHeight);
    addrLabel->setMaximumSize(myConstants::basicMaxLabelWidth, myConstants::basicMaxLabelHeight);

    // placing elements in grid:
    //
    // resetBtn--writeAddrBtn--readAddrBtn
    // -----------addrLabel---------------
    // -----------addrInput---------------
    layout->addWidget(resetBtn, 0, 0);
    layout->addWidget(writeAddrBtn, 0, 1);
    layout->addWidget(readAddrBtn, 0, 2);
    layout->addWidget(addrLabel, 1, 1);
    layout->addWidget(addrInput, 2, 1);
    layout->setSpacing(5);

    // setting up layout and central widget
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
}

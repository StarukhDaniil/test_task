#include "mainwindow.h"
#include "myconstants.h"
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , centralWidget(new QWidget(this))
    , layout(new QGridLayout())
    , resetBtn(new QPushButton("Reset", this))
    , writeAddrBtn(new QPushButton("Write address", this))
    , readAddrBtn(new QPushButton("Read address", this))
    , addrLabel(new QLabel("Address:", this))
    , addrInput(new QLineEdit(this))
    , output(new QListWidget(this))
{

    // changing font for each element
    QFont mainFont;
    mainFont.setPointSize(16);
    resetBtn->setFont(mainFont);
    writeAddrBtn->setFont(mainFont);
    readAddrBtn->setFont(mainFont);
    addrLabel->setFont(mainFont);
    addrInput->setFont(mainFont);
    output->setFont(mainFont);

    // resizing elements
    resetBtn->setMinimumSize(myConstants::basicMinBtnWidth, myConstants::basicMinBtnHeight);
    resetBtn->setMaximumSize(myConstants::basicMaxBtnWidth, myConstants::basicMaxBtnHeight);

    writeAddrBtn->setMinimumSize(myConstants::basicMinBtnWidth, myConstants::basicMinBtnHeight);
    writeAddrBtn->setMaximumSize(myConstants::basicMaxBtnWidth, myConstants::basicMaxBtnHeight);

    readAddrBtn->setMinimumSize(myConstants::basicMinBtnWidth, myConstants::basicMinBtnHeight);
    readAddrBtn->setMaximumSize(myConstants::basicMaxBtnWidth, myConstants::basicMaxBtnHeight);

    addrInput->setMinimumSize(myConstants::basicMinLineEditWidth, myConstants::basicMinLineEditHeight);
    addrInput->setMaximumSize(myConstants::basicMaxLineEditWidth, myConstants::basicMaxLineEditHeight);

    addrLabel->setMinimumSize(myConstants::basicMinLabelWidth, myConstants::basicMinLabelHeight);
    addrLabel->setMaximumSize(myConstants::basicMaxLabelWidth, myConstants::basicMaxLabelHeight);

    output->setMinimumSize(myConstants::basicMinListWidth, myConstants::basicMinListHeight);
    output->setMaximumSize(myConstants::basicMaxListWidth, myConstants::basicMaxListHeight);

    // placing elements in grid:
    //
    // writeAddrBtn--resetBtn--readAddrBtn
    // -addrLabel-------------------------
    // -addrInput-------------------------
    layout->addWidget(writeAddrBtn, 0, 0);
    layout->addWidget(resetBtn, 0, 1);
    layout->addWidget(readAddrBtn, 0, 2);
    layout->addWidget(addrLabel, 1, 0);
    layout->addWidget(addrInput, 2, 0);
    layout->addWidget(output, 1, 1, 2, 2);
    layout->setSpacing(5);

    // setting up layout and central widget
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // connecting writeBDAddrBtn to sending input
    QObject::connect(writeAddrBtn, &QPushButton::clicked, this, &MainWindow::askForInput,
                     Qt::DirectConnection);
}

QPushButton* MainWindow::getResetBtn() {
    return resetBtn;
}

QPushButton* MainWindow::getReadBDAddrBtn() {
    return readAddrBtn;
}

QPushButton* MainWindow::getWriteBDAddrBtn() {
    return writeAddrBtn;
}

QLineEdit* MainWindow::getInput() {
    return addrInput;
}

QListWidget* MainWindow::getOutput() {
    return output;
}

// slot that emits signal to send input from user
void MainWindow::askForInput() {
    emit writeBDAddr(addrInput->text());
}

// adds output to QListWidget
void MainWindow::writeResponse(const QString& response) {
    output->addItem(response);
}

MainWindow::~MainWindow()
{
}

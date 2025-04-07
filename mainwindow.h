#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPushButton* getResetBtn();
    QPushButton* getReadBDAddrBtn();
    QPushButton* getWriteBDAddrBtn();
    QLineEdit* getInput();
    QListWidget* getOutput();

private:
    QWidget* centralWidget;
    QGridLayout* layout;
    QLabel* addrLabel;
    QLineEdit* addrInput;
    QPushButton* resetBtn;
    QPushButton* writeAddrBtn;
    QPushButton* readAddrBtn;
    QListWidget* output;

public slots:
    void writeResponse(const QString& response);
    void askForInput();
signals:
    // sends input from input QLineEdit
    void writeBDAddr(const QString& input);
};
#endif // MAINWINDOW_H

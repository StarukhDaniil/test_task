#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>

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

private:
    QWidget* centralWidget;
    QGridLayout* layout;
    QPushButton* resetBtn;
    QPushButton* writeAddrBtn;
    QPushButton* readAddrBtn;
    QLabel* addrLabel;
    QLineEdit* addrInput;
};
#endif // MAINWINDOW_H

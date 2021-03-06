#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidgetItem>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void slotLabelClicked(bool t,int x,int y);    // Slot which will consume signal

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    int cnt_border;
    int cnt_values;

    QPixmap *qpix;

    void findValue(int x,int y,float *p1,float *p2);
};
#endif // MAINWINDOW_H

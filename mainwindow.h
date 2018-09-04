#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QtCore>
#include <QtGui>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    bool isNumber(QString a);
    void multiply();
    void add();
    ~MainWindow();

private slots:
    void on_rB_2_textChanged(const QString &arg1);

    void on_cA_textChanged(const QString &arg1);

    void on_rB_textChanged(const QString &arg1);

    void on_cB_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QStandardItemModel *modelB;
    QStandardItemModel *modelR;
};

#endif // MAINWINDOW_H

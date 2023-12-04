#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileInfoList>
#include <QDebug>
#include <QDateTime>
#include <QVector>
#include <iostream>
#include <QLineEdit>
#include <QPushButton>
#include <QTextBrowser>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void packageFiles(QString dirSource);

private slots:
    void on_dirPushButton_clicked();

    void on_execPushButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<QString> dirVector;
//    QLineEdit* dirLineEdit;

};
#endif // MAINWINDOW_H

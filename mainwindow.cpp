#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_dirPushButton_clicked()
{
    QString dirPath = QFileDialog::getExistingDirectory(this, "选择目录", "./", QFileDialog::ShowDirsOnly);
    ui->dirLineEdit->setText(dirPath);
}


void MainWindow::on_execPushButton_clicked()
{
    QString dirPath = ui->dirLineEdit->text();
    if (dirPath.isEmpty()) {
        QMessageBox::critical(this, "提示", "请选择要整理的目录");
        return;
    }
    packageFiles(dirPath);
}

void MainWindow::packageFiles(QString dirSource)
{
    // 遍历目录
    QDir dir(dirSource);
    QFileInfoList fileList = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Dirs);
    foreach (auto fileInfo, fileList)
    {
        if (fileInfo.isDir())
        {
            qDebug() << "文件夹： "  << fileInfo.absoluteFilePath()
                     << "创建时间：" << fileInfo.created().toString("yyyy-MM-dd hh:mm:ss")
                        << "创建时间：" << fileInfo.lastModified().toString()
                           << "创建时间：" << fileInfo.baseName()
                              << "创建时间：" << fileInfo.path()
                     << endl;
            dirVector.append(fileInfo.absoluteFilePath());
        }
    }
    // 遍历文件，根据文件修改时间，创建/移动到对应的“年-月”目录
    foreach (auto fileInfo, fileList)
    {
        if (fileInfo.isFile())
        {
            QString dirDestStr = fileInfo.lastModified().toString("yyyy-MM");
            QString dirDestAbs = fileInfo.path() + "/" + dirDestStr;
            qDebug() << "dest: " << dirDestStr << ",,, " << dirDestAbs
                     << ",,,aa " << fileInfo.absoluteFilePath()
                     << endl;
            // 如果不存在，则创建
            QDir dirDest(dirDestAbs);
            if (!dirDest.exists())
            {
                dirDest.mkdir(dirDestAbs);
            }
            // 移动文件
            const QString& f = fileInfo.absoluteFilePath();
            const QString& d = dirDestAbs + "/" + fileInfo.baseName();
            qDebug() << "ff: " << f << ",,, " << d
                     << endl;
            qDebug() << "rest: " << QFile::rename(f, d) << endl;
        }
    }
}


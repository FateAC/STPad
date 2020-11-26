#ifndef CODEFORMAT_H
#define CODEFORMAT_H

#include <QTextStream>
#include <QProcess>
#include <QCoreApplication>
#include "ui_mainwindow.h"

class CodeFormat
{
public:
    void autoformat(QString curFile, Ui::MainWindow *ui);
};

#endif // CODEFORMAT_H

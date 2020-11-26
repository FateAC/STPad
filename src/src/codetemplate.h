#ifndef CODETEMPLATE_H
#define CODETEMPLATE_H

#include <QFileDialog>
#include <QTextStream>
#include <QCoreApplication>
#include <QApplication>
#include <QDebug>
#include "src/codeeditor.h"

class CodeTemplate
{
public:
    void setTemplate(QString curFile, CodeEditor *codeEditor);
};

#endif // CODETEMPLATE_H

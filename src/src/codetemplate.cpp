#include "codetemplate.h"

void CodeTemplate::setTemplate(QString curFile, CodeEditor *codeEditor){
    if(curFile.isEmpty())
        return;
    QString filetype = curFile.section("/",-1,-1).split(".").at(1);
    QString dir = QCoreApplication::applicationDirPath() + "/plugins/Template/";
    QFile file(dir + "template." + filetype);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        return;
    }
    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    codeEditor->editor->setText(in.readAll());
    QApplication::restoreOverrideCursor();
}

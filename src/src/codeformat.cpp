#include "codeformat.h"
#include "mainwindow.h"

void CodeFormat::autoformat(QString m_curFile, Ui::MainWindow *ui){
    //--style=google --pad-oper --break-closing-braces
    QString dir = QCoreApplication::applicationDirPath() + "/plugins/AStyle/";
    QProcess process;
    process.setWorkingDirectory(dir);
    QStringList cmd = QStringList()<<"--suffix=none"<<"--style=google"<<"--pad-oper"<<"--break-closing-braces"<<m_curFile;
    qDebug()<<cmd<<endl;
    process.start(dir+"AStyle.exe", cmd);
    if(!process.waitForStarted()){
        process.close();
        ui->error_textEdit->setText("Auto-Format Failed");
        return;
    }
    if(process.waitForFinished()){
        ui->error_textEdit->setText("Auto-Format Successful");
    }
    else{
        ui->error_textEdit->setText("Auto-Format Failed");
    }
    process.close();
}

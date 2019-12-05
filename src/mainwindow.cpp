#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>
#include <QProcess>
#include <QDesktopServices>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->gridLayout->addWidget(codeEditor->editor);
    setWindowState(Qt::WindowMaximized);
    setWindowTitle(curFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::codeSubmit(){
    save();
    QStringList input;
    input << ui->problom_lineEdit->text()
          << ui->account_lineEdit->text()
          << ui->password_lineEdit->text()
          << curFile;
    QString dir = QCoreApplication::applicationDirPath() + "/Python/CodeSubmit/";
    QProcess process;
    process.setWorkingDirectory(dir);
    process.start(dir+"CodeSubmit.exe");
    process.waitForStarted();
    foreach (QString i, input) {
        process.write(i.toStdString().data());
        process.write("\r\n");
    }
    process.waitForFinished();
    process.close();
}

void MainWindow::problemCrawler(){
    QString problemID = ui->problom_lineEdit->text();
    QString dir = QCoreApplication::applicationDirPath() + "/Python/ProblemDownload/";
    QProcess process;
    process.setWorkingDirectory(dir);
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start(dir+"ProblemDownload.exe");
    process.waitForStarted();
    process.write(problemID.toStdString().data());
    process.write("\r\n");
    process.waitForFinished(10000);
    QString getStr = QString(process.readAllStandardOutput());
    qDebug()<<getStr<<endl;
    QDesktopServices::openUrl(QUrl("file:///"+dir + "problems/" + problemID + ".pdf"));
    process.close();
}

void MainWindow::autoformat(){
    save();
    QString m_curFile = curFile;
    //--style=google --pad-oper --break-closing-braces
    newFile();
    QString dir = QCoreApplication::applicationDirPath() + "/plugins/AStyle/";
    QProcess process;
    process.setWorkingDirectory(dir);
    process.start(dir+"AStyle.exe",QStringList()<<"--suffix=none"<<"--style=google"<<"--pad-oper"<<"--break-closing-braces"<<m_curFile);
    if(!process.waitForStarted()){
        process.close();
        ui->error_textEdit->setText("Auto-Format Failed");
        return;
    }
    if(process.waitForFinished()){
        loadFile(m_curFile);
        ui->error_textEdit->setText("Auto-Format Successful");
    }
    else{
        ui->error_textEdit->setText("Auto-Format Failed");
    }
    process.close();
}

bool MainWindow::build(){
    save();
    ui->output_textEdit->clear();
    QString dir = curFile.section("/",0,-2);
    QString filename = curFile.section("/",-1,-1).split(".").at(0);
    QString filetype = curFile.section("/",-1,-1).split(".").at(1);
    QString allFilename = filename + "." + filetype;
    QString cmd;
    if(filetype == "c")
        cmd = "gcc";
    else if(filetype == "cpp")
        cmd = "g++";
    else if(cmd.isEmpty()){
        ui->error_textEdit->setText("The type of file is wrong!");
        return false;
    }
    QProcess process;
    process.setWorkingDirectory(dir);
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start(cmd,QStringList()<<allFilename<<"-o"<<filename);
    if(!process.waitForStarted()){
        process.close();
        ui->error_textEdit->setText("Build Failed");
        return false;
    }
    if(process.waitForFinished()){
        QString getStr = process.readAllStandardOutput();
        process.close();
        if(!getStr.isEmpty()){
            ui->error_textEdit->setText(getStr);
            return false;
        }
        ui->error_textEdit->setText("Build Successful");
        return true;
    }
    else{
        process.close();
        ui->error_textEdit->setText("Build Failed");
        return false;
    }
}

void MainWindow::run(){
    ui->output_textEdit->clear();
    QString cmd;
    QString dir = curFile.section("/",0,-2);
    QString filename = curFile.section("/",-1,-1).split(".").at(0);
    cmd = dir + "/" + filename + ".exe";

    QProcess process;
    process.start(cmd);
    if(!process.waitForStarted()){
        ui->error_textEdit->setText("Run Failed");
        process.close();
        return;
    }
    QString input = ui->input_textEdit->toPlainText();
    process.write(input.toStdString().data());
    process.write("\r\n");
    if(process.waitForFinished(7000)){
        QString getStr = QString(process.readAllStandardOutput());
        ui->output_textEdit->setText(getStr);
        ui->error_textEdit->setText("Run Successful");
    }
    process.close();
}

void MainWindow::newFile(){
    if (maybeSave()) {
        codeEditor->editor->clear();
        setCurrentFile("");
    }
}


bool MainWindow::maybeSave(){
    if(codeEditor->editor->isModified()){
        QMessageBox box;
        box.setWindowTitle(tr("警告"));
        box.setIcon(QMessageBox::Warning);
        box.setText(curFile+tr("尚未保存，是否保存?"));
        QPushButton *yesBtn = box.addButton(tr("是(&Y)"), QMessageBox::YesRole);
        box.addButton(tr("否(&N)"), QMessageBox::NoRole);
        QPushButton *cancelBtn = box.addButton(tr("取消"), QMessageBox::RejectRole);
        box.exec();
        if(box.clickedButton()==yesBtn)
            return save();
        else if(box.clickedButton()==cancelBtn)
            return false;
    }
    return true;
}

bool MainWindow::save(){
    if(curFile.isEmpty()) return saveAs();
    else return saveFile(curFile);
}

bool MainWindow::saveAs(){
    QString fileName = QFileDialog::getSaveFileName(this);
    if (fileName.isEmpty()) return false;
    return saveFile(fileName);
}

bool MainWindow::saveFile(const QString &fileName){
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        return false;
    }
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << codeEditor->editor->text();
    QApplication::restoreOverrideCursor();
    setCurrentFile(fileName);
    return true;
}

bool MainWindow::loadFile(const QString &fileName){
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        return false;
    }
    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    codeEditor->editor->setText(in.readAll());
    QApplication::restoreOverrideCursor();
    setCurrentFile(fileName);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    codeEditor->editor->setModified(false);
    setWindowModified(false);

    QString shownName;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    else
        shownName = QFileInfo(curFile).fileName();

    setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Application")));
}

void MainWindow::on_actionNew_triggered()
{
    newFile();
}

void MainWindow::on_actionSave_triggered()
{
    save();
}

void MainWindow::on_actionSave_As_triggered()
{
    saveAs();
}

void MainWindow::on_actionOpen_triggered()
{
    if(maybeSave()){
        QString fileName =
                QFileDialog::getOpenFileName(this, tr("開啟檔案"), tr(""), tr("C/Cpp File(*.c *.cpp)"));
        if(!fileName.isEmpty()){
            loadFile(fileName);
        }
    }
}

void MainWindow::on_actionCopy_triggered()
{
    codeEditor->editor->copy();
}

void MainWindow::on_actionCut_triggered()
{
    codeEditor->editor->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    codeEditor->editor->paste();
}

void MainWindow::on_actionRedo_triggered()
{
    codeEditor->editor->redo();
}

void MainWindow::on_actionUndo_triggered()
{
    codeEditor->editor->undo();
}

void MainWindow::on_actionselect_all_triggered()
{
    codeEditor->editor->selectAll();
}

void MainWindow::on_actionBuild_triggered()
{
    build();
}

void MainWindow::on_actionRun_triggered()
{
    run();
}

void MainWindow::on_actionBuild_and_run_triggered()
{
    if(build())
        run();
}

void MainWindow::on_actionAStyle_triggered()
{
    autoformat();
}

void MainWindow::on_inputClear_pbtn_clicked()
{
    ui->input_textEdit->clear();
}

void MainWindow::on_outputClear_pbtn_clicked()
{
    ui->output_textEdit->clear();
}

void MainWindow::on_problem_pbtn_clicked()
{
    problemCrawler();
}

void MainWindow::on_codeSubmit_clicked()
{
    codeSubmit();
}

#include "newprojectdialog.h"
#include "ui_newprojectdialog.h"
#include "mainwindow.h"
#include <QDesktopWidget>

NewProjectDialog::NewProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProjectDialog)
{
    ui->setupUi(this);
    setWindowTitle("New Project");
    setWindowIcon(QIcon(":/images/images/newproject.png"));
    QDesktopWidget dw;
    this->setFixedSize(int(dw.width()*0.5), int(dw.height()*0.5));
}

NewProjectDialog::~NewProjectDialog()
{
    delete ui;
}

void NewProjectDialog::on_create_pbtn_clicked()
{
    //read infomation
    filetype =  projectTitle =  createPath = "";
    if(ui->c_checkBox->isChecked())
        filetype = "c";
    else if(ui->cpp_checkBox->isChecked())
        filetype = "cpp";
    projectTitle = ui->title_lineEdit->text();
    createPath = ui->path_lineEdit->text();

    if(filetype.isEmpty() || projectTitle.isEmpty() || createPath.isEmpty()){
        QMessageBox box;
        box.setWindowTitle(tr("警告"));
        box.setIcon(QMessageBox::Warning);
        box.setText(tr("請完整選填"));
        box.exec();
    }
    else{
        if(createPath[createPath.length()-1] != "/")
            createPath.append("/");
        QDir dir(createPath + projectTitle);
        if(dir.exists()){
            QMessageBox box;
            box.setWindowTitle(tr("警告"));
            box.setIcon(QMessageBox::Warning);
            box.setText(tr("資料夾已存在"));
            box.exec();
        }
        else{
            dir.mkpath(createPath + projectTitle);
            QFile file(createPath + projectTitle + "/main." + filetype);
            if(!file.open(QFile::WriteOnly | QFile::Text)){
                dir.remove(createPath + projectTitle);
                QMessageBox box;
                box.setWindowTitle(tr("警告"));
                box.setIcon(QMessageBox::Warning);
                box.setText(tr("檔案建立失敗"));
                box.exec();
            }
            else{
                QString Data = createPath + projectTitle + "/main." + filetype;
                emit sendNewProjectFilenameData(Data);
                this->close();
            }
        }
    }

}

void NewProjectDialog::on_path_pushButton_clicked()
{
    QString dir =
            QFileDialog::getExistingDirectory(
                this, tr("Open Directory"),"",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->path_lineEdit->setText(dir);
}

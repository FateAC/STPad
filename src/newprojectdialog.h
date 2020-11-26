#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>
#include <QIcon>
#include <QMessageBox>
#include <QDir>

namespace Ui {
class NewProjectDialog;
}

class NewProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewProjectDialog(QWidget *parent = nullptr);
    ~NewProjectDialog();

signals:
    void sendNewProjectFilenameData(QString);

private slots:
    void on_create_pbtn_clicked();
    void on_path_pushButton_clicked();

private:
    Ui::NewProjectDialog *ui;
    QString filetype;
    QString projectTitle;
    QString createPath;
};

#endif // NEWPROJECTDIALOG_H

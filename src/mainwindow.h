#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <src/codeeditor.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void newFile();
    bool maybeSave();
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    bool loadFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    bool build();
    void run();
    void autoformat();
    void problemCrawler();
    void codeSubmit();

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionCopy_triggered();
    void on_actionCut_triggered();
    void on_actionPaste_triggered();
    void on_actionRedo_triggered();
    void on_actionUndo_triggered();
    void on_actionselect_all_triggered();
    void on_actionBuild_triggered();
    void on_actionRun_triggered();
    void on_actionBuild_and_run_triggered();
    void on_inputClear_pbtn_clicked();
    void on_outputClear_pbtn_clicked();
    void on_actionAStyle_triggered();
    void on_problem_pbtn_clicked();

    void on_codeSubmit_clicked();

private:
    Ui::MainWindow *ui;
    QString curFile;
    CodeEditor *codeEditor = new CodeEditor();
};
#endif // MAINWINDOW_H

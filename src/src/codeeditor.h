#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercpp.h>
#include <Qsci/qsciapis.h>

class CodeEditor
{
public:
    QsciScintilla *editor = new QsciScintilla();
    CodeEditor();
};

#endif // CODEEDITOR_H

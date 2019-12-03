#include "codeeditor.h"

CodeEditor::CodeEditor()
{
    //UTF-8
    editor->SendScintilla(QsciScintilla::SCI_SETCODEPAGE,QsciScintilla::SC_CP_UTF8);

    //Font
    QFont font;
    font.setFamily("Courier New");
    font.setFixedPitch(true);
    font.setPointSize(14);
    editor->setFont(font);

    //LineNumbers
    editor->setMarginType(0,QsciScintilla::NumberMargin);
    editor->setMarginLineNumbers(0,true);
    editor->setMarginWidth(0,35);
    //editor->setMarginsBackgroundColor(Qt::gray);

    //CaretLine
    editor->setCaretLineVisible(true);
    //editor->setCaretLineBackgroundColor(Qt::lightGray);

    //Lexer Cpp
    QsciLexer *lexerCPP = new QsciLexerCPP();
    lexerCPP->setDefaultFont(font);
    editor->setLexer(lexerCPP);

    //AutoCompletion
    editor->setAutoCompletionSource(QsciScintilla::AcsAll);
    editor->setAutoCompletionCaseSensitivity(true);
    editor->setAutoCompletionThreshold(1);

    //Tab
    editor->setTabWidth(4);
    editor->setTabIndents(true);
    editor->setAutoIndent(true);
    //editor->setIndentationGuides(QsciScintilla::SC_IV_LOOKBOTH);

    //BraceMatching
    editor->setBraceMatching(QsciScintilla::SloppyBraceMatch);
}

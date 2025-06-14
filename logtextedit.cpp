#include "logtextedit.h"
#include <QTextBlock>    // 关键修复：包含 QTextBlock
#include <QTextCursor>   // 关键修复：包含 QTextCursor
#include <QScrollBar>
#include <QDateTime>

LogTextEdit::LogTextEdit(QWidget *parent) : QTextEdit(parent) {
    QFont font;
    font.setPointSize(10);
    setFont(font);
    setReadOnly(true);
    setLineWrapMode(QTextEdit::NoWrap);
}

void LogTextEdit::appendLog(const QString &message,const QColor &color) {
    QString timestamp = QDateTime::currentDateTime().toString("[yyyy-mm-dd hh:mm:ss]   ");
    QString fullMessage = timestamp + message;
    QTextDocument *doc = document();
    if (doc->blockCount() >= 100) {
        // 删除第一个文本块
        QTextCursor cursor(doc->firstBlock());
        cursor.select(QTextCursor::BlockUnderCursor);  // 选中整个块
        cursor.removeSelectedText();
        cursor.deleteChar();  // 删除块末尾的换行符
    }

    QTextCursor cursor(doc);
    cursor.movePosition(QTextCursor::End);  // 移动到文档末尾
    QTextBlockFormat blockFormat;
    blockFormat.setLineHeight(100, QTextBlockFormat::ProportionalHeight);

    // 设置字符格式：颜色
    QTextCharFormat charFormat;
    charFormat.setForeground(color);

    // 应用格式并插入文本
    cursor.mergeBlockFormat(blockFormat);
    cursor.setCharFormat(charFormat);
    cursor.insertText(fullMessage + "\n");
    QScrollBar *vScroll = verticalScrollBar();
    vScroll->setValue(vScroll->maximum());
}

void LogTextEdit::appendLog(const QString &message) {
    appendLog(message,Qt::black);
}

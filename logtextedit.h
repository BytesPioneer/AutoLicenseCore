#ifndef LOGTEXTEDIT_H
#define LOGTEXTEDIT_H

#include <QTextEdit>

class LogTextEdit : public QTextEdit {
    Q_OBJECT
public:
    explicit LogTextEdit(QWidget *parent = nullptr);

public slots:
    void appendLog(const QString &message,const QColor &color);
    void appendLog(const QString &message);
};

#endif // LOGTEXTEDIT_H

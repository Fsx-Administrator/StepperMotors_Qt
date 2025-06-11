#pragma once

#include <QTextEdit>
#include <qglobal.h>

class DebugConsole : public QTextEdit
{
    Q_OBJECT

public:
    explicit DebugConsole(QWidget *parent = nullptr);
    virtual ~DebugConsole() = default;

public slots:
    void appendAnswer(const QString &answer);
    void appendRequest(const QString &request);
    void appendSection(const QString &section);

private:
    const QString _ANSWER_TEMPLATE_;
    const QString _REQUEST_TEMPLATE_;
    const QString _SECTION_TEMPLATE_;

};

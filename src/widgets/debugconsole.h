#pragma once

#include <QTextEdit>
#include <qglobal.h>

class DebugConsole : public QTextEdit
{
    Q_OBJECT

public:
    explicit DebugConsole(QWidget *parent = nullptr) noexcept;
    virtual ~DebugConsole() noexcept = default;

public slots:
    void appendAnswer(const QString &answer) noexcept;
    void appendRequest(const QString &request) noexcept;
    void appendSection(const QString &section) noexcept;

private:
    const QString _ANSWER_TEMPLATE_;
    const QString _REQUEST_TEMPLATE_;
    const QString _SECTION_TEMPLATE_;

};

#include "debugconsole.h"

#include <QTime>


DebugConsole::DebugConsole(QWidget *parent) noexcept
    : QTextEdit(parent)
    , _ANSWER_TEMPLATE_(R"(<font color="DarkBlue">Answer :: %1 :: <font color="Black">%2)")
    , _REQUEST_TEMPLATE_(R"(<font color="DarkGreen">Request :: %1 :: <font color="Black">%2)")
    , _SECTION_TEMPLATE_(R"(<font color="DarkRed">( ----- %1 ----- ))")
{}

void DebugConsole::appendAnswer(const QString &answer) noexcept
{
    append(_ANSWER_TEMPLATE_.arg(QTime::currentTime().toString("hh:mm:ss"), answer));
}

void DebugConsole::appendRequest(const QString &request) noexcept
{
    append(_REQUEST_TEMPLATE_.arg(QTime::currentTime().toString("hh:mm:ss"), request));
}

void DebugConsole::appendSection(const QString &section) noexcept
{
    append(_SECTION_TEMPLATE_.arg(section));
}

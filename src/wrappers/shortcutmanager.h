#pragma once

#include "common.h"

#include <QShortcut>

class ShortcutManager
{

public:
    static void registerShortcut(const QKeySequence &key, QObject *parent, Functor auto functor)
    {
        new QShortcut(key, parent, functor, Qt::WindowShortcut);
    }

};

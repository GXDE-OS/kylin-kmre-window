/*
 * Peony-Qt
 *
 * Copyright (C) 2020, KylinSoft Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Authors: Yue Lan <lanyue@kylinos.cn>
 *
 */

#ifndef PLASMASHELLMANAGER_H
#define PLASMASHELLMANAGER_H

#include <QObject>
#include <QWindow>
#include <KWayland/Client/plasmawindowmanagement.h>
#include <KWayland/Client/plasmashell.h>
#include <KWayland/Client/shell.h>

class PlasmaShellManager : public QObject
{
    Q_OBJECT
public:
    static PlasmaShellManager *getInstance();

    bool setAppWindowActive();
    bool setAppWindowKeepAbove(bool keep);
    bool setMaximized(QWindow *window);
    bool setRole(QWindow *window, KWayland::Client::PlasmaShellSurface::Role role);
    bool setPos(QWindow *window, const QPoint &pos);
    bool supportPlasmaShell();
    bool supportShell();
    bool supportPlasmaWindowManagement();

private:
    explicit PlasmaShellManager(QObject *parent = nullptr);

    KWayland::Client::PlasmaShell *m_plasmaShell = nullptr;
    KWayland::Client::Shell *m_shell = nullptr;
    KWayland::Client::PlasmaWindowManagement *m_windowManager = nullptr;
    KWayland::Client::PlasmaWindow *m_appWindow = nullptr;

    bool isFirstCreate = true;
};

#endif // PLASMASHELLMANAGER_H

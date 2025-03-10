/*
 * Copyright (c) KylinSoft Co., Ltd. 2016-2024.All rights reserved.
 *
 * Authors:
 *  Alan Xie    xiehuijun@kylinos.cn
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <QString>
#include "singleton.h"

class DisplayControlDecoder;

class DisplayConnection : public kmre::SingletonP<DisplayConnection>
{
public:
    bool enableDisplayUpdateForEmu(int displayId, bool enable);

private:
    DisplayConnection();
    ~DisplayConnection();

    bool connectEmuSocket();
    void disconnectEmuSocket();
    int initDisplayControl();
    int initEmulator();

    DisplayControlDecoder *mDecoder = nullptr;
    QString mEmuglSocketPath;
    int mEmuglConnectFd = -1;

    friend SingletonP<DisplayConnection>;
};

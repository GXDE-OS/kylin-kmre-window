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
#include <memory>

namespace KmreEnv 
{
    void envCheck();
    bool isKylinOSPro();
    bool isOpenKylin();
    bool isKmreEnvStopped();
    void kmreEnvStopped();
    QString GetContainerSocketPath();
    QString GetAndroidPath();
    QString GetAndroidDataPath();
    QString GetConfigPath();
    QString GetGlobalConfigPath();
    QString GetKmreConfigFile();
}

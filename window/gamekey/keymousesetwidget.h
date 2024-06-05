/*
 * Copyright (c) KylinSoft Co., Ltd. 2016-2024.All rights reserved.
 *
 * Authors:
 * Zero Liu    liuzenghui1@kylinos.cn
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

#ifndef KEYMOUSESETWIDGET_H
#define KEYMOUSESETWIDGET_H

#include <QWidget>
#include <QSlider>

class KeyMouseSetWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KeyMouseSetWidget(QWidget *parent = nullptr);
    ~KeyMouseSetWidget();

private:
    QSlider* mTransparencySlider = nullptr;

signals:
    void addKeyMouseKey(int type);
    void saveGameKeys(bool isJoystick);
    void clearGameKeys(bool isJoystick);

};

#endif // KEYMOUSESETWIDGET_H

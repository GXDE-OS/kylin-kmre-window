/*
 * Copyright (C) 2013 ~ 2021 KylinSoft Ltd.
 *
 * Authors:
 *  Kobe Lee    lixiang@kylinos.cn
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

#ifndef STARTCONTROL_H
#define STARTCONTROL_H

#include <QObject>

class StartControl : public QObject
{
    Q_OBJECT
public:
    explicit StartControl(QObject *parent = nullptr);
    void startEnvSilently();

public slots:
    void onImageLoaded();
    void onFinished();

signals:

private:
    

};

#endif // STARTCONTROL_H

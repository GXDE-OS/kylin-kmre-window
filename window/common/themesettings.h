/*
 * Copyright (c) KylinSoft Co., Ltd. 2016-2025.All rights reserved.
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

#ifndef __KMRE_THEME_SETTINGS_H__
#define __KMRE_THEME_SETTINGS_H__

#include <QObject>
#include <QPalette>
#include <QColor>
#include <QIcon>

class QGSettings;
class QSize;

namespace kmre {

/*
 * 跟随系统深浅色主题:
 * 1. 部分桌面环境（如非 UKUI 桌面）的平台主题不会给应用程序提供深色调色板，
 *    导致系统深色模式下界面仍是白底，这里统一检测系统深浅色模式并应用深色调色板；
 * 2. 部分平台主题上报的图标主题名在本机并不存在，导致 QIcon::fromTheme
 *    找不到任何图标（标题栏等处按钮无图标），这里从系统设置中读取真实的
 *    图标主题名进行修正。
 */
class ThemeSettings : public QObject
{
    Q_OBJECT

public:
    static ThemeSettings *getInstance();

    // 必须在 QApplication 创建后、任何界面创建前调用
    void initialize();

    bool isDarkTheme() const {return mIsDarkTheme;}

    // 返回与当前主题背景对比度足够的图标前景色
    QColor symbolicIconColor() const;

    // 加载符号图标并按指定颜色着色（color 为无效颜色时按当前主题自动选择；
    // name 找不到时使用 fallbackName）
    static QIcon loadSymbolicIcon(const QString &name, const QColor &color = QColor(),
                                  const QString &fallbackName = QString());
    // 将图片重着色为指定颜色（保留原透明度）
    static QPixmap drawColoredPixmap(const QPixmap &source, const QColor &color);

Q_SIGNALS:
    void darkThemeChanged(bool dark);

private Q_SLOTS:
    void onGSettingsChanged(const QString &key);

private:
    explicit ThemeSettings();
    ~ThemeSettings() override;

    void updateTheme();
    void fixIconTheme();
    void applyPalette(bool dark);
    bool systemThemeIsDark() const;

private:
    bool mIsDarkTheme = false;
    bool mInitialized = false;
    bool mUsingCustomPalette = false;// 当前是否使用的是自定义深色调色板
    QPalette mDefaultPalette;// 平台主题提供的原始调色板
    QGSettings *mUkuiStyleGSettings = nullptr;
    QGSettings *mGnomeInterfaceGSettings = nullptr;
};

}

#endif // __KMRE_THEME_SETTINGS_H__

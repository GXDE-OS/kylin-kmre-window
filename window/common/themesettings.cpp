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

#include "themesettings.h"

#include <QApplication>
#include <QColor>
#include <QIcon>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QSize>
#include <QStringList>

#include <QGSettings>

#include <syslog.h>

#define UKUI_STYLE_SCHEMA       "org.ukui.style"
#define GNOME_INTERFACE_SCHEMA  "org.gnome.desktop.interface"

namespace kmre {

static bool paletteIsLight(const QPalette &palette)
{
    // 界面以 Window/Base 作为主要背景色，两者都为浅色时才认为当前是浅色界面
    return (palette.color(QPalette::Window).lightness() >= 128
            && palette.color(QPalette::Base).lightness() >= 128);
}

ThemeSettings *ThemeSettings::getInstance()
{
    static ThemeSettings instance;
    return &instance;
}

ThemeSettings::ThemeSettings()
    : QObject()
{
}

ThemeSettings::~ThemeSettings()
{
}

void ThemeSettings::initialize()
{
    if (mInitialized || !qApp) {
        return;
    }
    mInitialized = true;

    mDefaultPalette = qApp->palette();
    // 部分平台主题提供的调色板 resolveMask 为 0（所有颜色角色均为未解析状态），
    // 直接设置回去不生效，这里强制所有颜色角色显式生效
    mDefaultPalette.setResolveMask(~0u);

    if (QGSettings::isSchemaInstalled(UKUI_STYLE_SCHEMA)) {
        mUkuiStyleGSettings = new QGSettings(UKUI_STYLE_SCHEMA, QByteArray(), this);
        connect(mUkuiStyleGSettings, &QGSettings::changed, this, &ThemeSettings::onGSettingsChanged);
    }
    if (QGSettings::isSchemaInstalled(GNOME_INTERFACE_SCHEMA)) {
        mGnomeInterfaceGSettings = new QGSettings(GNOME_INTERFACE_SCHEMA, QByteArray(), this);
        connect(mGnomeInterfaceGSettings, &QGSettings::changed, this, &ThemeSettings::onGSettingsChanged);
    }

    fixIconTheme();

    updateTheme();
}

bool ThemeSettings::systemThemeIsDark() const
{
    if (QGSettings::isSchemaInstalled(UKUI_STYLE_SCHEMA)) {
        QGSettings settings(UKUI_STYLE_SCHEMA);
        if (settings.keys().contains("styleName")) {
            const QString styleName = settings.get("style-name").toString();
            return (styleName.contains("dark", Qt::CaseInsensitive)
                    || styleName.contains("black", Qt::CaseInsensitive));
        }
    }

    if (QGSettings::isSchemaInstalled(GNOME_INTERFACE_SCHEMA)) {
        QGSettings settings(GNOME_INTERFACE_SCHEMA);
        if (settings.keys().contains("colorScheme")) {
            const QString colorScheme = settings.get("color-scheme").toString();
            if (colorScheme.contains("dark")) {
                return true;
            }
            if (!colorScheme.isEmpty() && colorScheme.contains("light")) {
                return false;
            }
        }
        if (settings.keys().contains("gtkTheme")) {
            return settings.get("gtk-theme").toString().contains("dark", Qt::CaseInsensitive);
        }
    }

    return false;
}

void ThemeSettings::fixIconTheme()
{
    QString iconTheme;
    if (mUkuiStyleGSettings && mUkuiStyleGSettings->keys().contains("iconThemeName")) {
        iconTheme = mUkuiStyleGSettings->get("icon-theme-name").toString();
    }
    if (iconTheme.isEmpty() && mGnomeInterfaceGSettings && mGnomeInterfaceGSettings->keys().contains("iconTheme")) {
        iconTheme = mGnomeInterfaceGSettings->get("icon-theme").toString();
    }

    if (!iconTheme.isEmpty() && iconTheme != QIcon::themeName()) {
        syslog(LOG_INFO, "[ThemeSettings] Fix icon theme from '%s' to '%s'",
               QIcon::themeName().toStdString().c_str(), iconTheme.toStdString().c_str());
        QIcon::setThemeName(iconTheme);
        QIcon::setFallbackThemeName("hicolor");
    }
}

void ThemeSettings::updateTheme()
{
    const bool dark = systemThemeIsDark();
    const bool themeChanged = (dark != mIsDarkTheme);
    mIsDarkTheme = dark;

    // 平台主题没有提供深色调色板（界面仍是白底）时，手动应用深色调色板；
    // 切回浅色模式时恢复平台主题原始调色板
    if (dark) {
        if (paletteIsLight(qApp->palette())) {
            syslog(LOG_INFO, "[ThemeSettings] Apply dark palette.");
            applyPalette(true);
        }
    }
    else if (mUsingCustomPalette) {
        syslog(LOG_INFO, "[ThemeSettings] Restore default palette.");
        applyPalette(false);
    }

    if (themeChanged) {
        syslog(LOG_INFO, "[ThemeSettings] System theme changed, current theme: %s", dark ? "Dark" : "Light");
        Q_EMIT darkThemeChanged(dark);
    }
}

void ThemeSettings::applyPalette(bool dark)
{
    mUsingCustomPalette = dark;
    if (!dark) {
        qApp->setPalette(mDefaultPalette);
        return;
    }

    QPalette palette(mDefaultPalette);
    palette.setColor(QPalette::Window, QColor(0x26, 0x26, 0x26));
    palette.setColor(QPalette::WindowText, QColor(0xf2, 0xf2, 0xf2));
    palette.setColor(QPalette::Base, QColor(0x25, 0x26, 0x27));
    palette.setColor(QPalette::AlternateBase, QColor(0x2d, 0x2e, 0x2f));
    palette.setColor(QPalette::ToolTipBase, QColor(0x40, 0x41, 0x43));
    palette.setColor(QPalette::ToolTipText, QColor(0xf2, 0xf2, 0xf2));
    palette.setColor(QPalette::PlaceholderText, QColor(0x8c, 0x8c, 0x8c));
    palette.setColor(QPalette::Text, QColor(0xf2, 0xf2, 0xf2));
    palette.setColor(QPalette::Button, QColor(0x2d, 0x2e, 0x2f));
    palette.setColor(QPalette::ButtonText, QColor(0xf2, 0xf2, 0xf2));
    // 注意: chameleon 等样式会用 BrightText 绘制菜单等文字，
    // 这里必须给与主题一致的高对比浅色，不能按惯例设为红色
    palette.setColor(QPalette::BrightText, QColor(0xf2, 0xf2, 0xf2));
    palette.setColor(QPalette::Light, QColor(0x3c, 0x3d, 0x3f));
    palette.setColor(QPalette::Midlight, QColor(0x33, 0x34, 0x36));
    palette.setColor(QPalette::Mid, QColor(0x2a, 0x2b, 0x2c));
    palette.setColor(QPalette::Dark, QColor(0x1a, 0x1b, 0x1c));
    palette.setColor(QPalette::Shadow, QColor(0x10, 0x10, 0x10));
    palette.setColor(QPalette::Link, QColor(0x3d, 0x6b, 0xe5));
    palette.setColor(QPalette::LinkVisited, QColor(0x6a, 0x4c, 0xdb));
    palette.setColor(QPalette::Highlight, QColor(0x3d, 0x6b, 0xe5));
    palette.setColor(QPalette::HighlightedText, QColor(0xf2, 0xf2, 0xf2));
    palette.setColor(QPalette::Accent, QColor(0x3d, 0x6b, 0xe5));
    palette.setColor(QPalette::Disabled, QPalette::Window, QColor(0x2d, 0x2e, 0x2f));
    palette.setColor(QPalette::Disabled, QPalette::Base, QColor(0x30, 0x31, 0x32));
    palette.setColor(QPalette::Disabled, QPalette::WindowText, QColor(0x7d, 0x7d, 0x7d));
    palette.setColor(QPalette::Disabled, QPalette::Text, QColor(0x7d, 0x7d, 0x7d));
    palette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(0x7d, 0x7d, 0x7d));
    palette.setColor(QPalette::Disabled, QPalette::Highlight, QColor(0x2d, 0x2e, 0x2f));
    palette.setColor(QPalette::Disabled, QPalette::HighlightedText, QColor(0x7d, 0x7d, 0x7d));
    // 强制所有颜色角色显式生效，避免未解析的角色沿用上一版调色板的颜色
    palette.setResolveMask(~0u);
    qApp->setPalette(palette);
}

QColor ThemeSettings::symbolicIconColor() const
{
    // 图标位于 Window/Base 背景之上，按背景亮度选择前景色以保证对比度
    if (mIsDarkTheme
            || qApp->palette().color(QPalette::Base).lightness() < 128) {
        return QColor(0xf2, 0xf2, 0xf2);
    }
    return QColor(0x44, 0x44, 0x44);
}

QPixmap ThemeSettings::drawColoredPixmap(const QPixmap &source, const QColor &color)
{
    if (source.isNull() || !color.isValid()) {
        return source;
    }

    QImage image(source.size(), QImage::Format_ARGB32_Premultiplied);
    image.setDevicePixelRatio(source.devicePixelRatio());
    image.fill(Qt::transparent);

    QPainter painter(&image);
    painter.drawPixmap(0, 0, source);
    // 保留原图片透明度，将颜色替换为指定颜色
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(image.rect(), color);
    painter.end();

    QPixmap pixmap = QPixmap::fromImage(image);
    pixmap.setDevicePixelRatio(source.devicePixelRatio());
    return pixmap;
}

QIcon ThemeSettings::loadSymbolicIcon(const QString &name, const QColor &color, const QString &fallbackName)
{
    QIcon sourceIcon = QIcon::fromTheme(name,
        fallbackName.isEmpty() ? QIcon() : QIcon::fromTheme(fallbackName));
    if (sourceIcon.isNull()) {
        syslog(LOG_WARNING, "[ThemeSettings] Can not find icon '%s'!", name.toStdString().c_str());
        return QIcon();
    }

    const QColor iconColor = color.isValid() ? color : getInstance()->symbolicIconColor();
    QPixmap pixmap = sourceIcon.pixmap(QSize(24, 24));
    return QIcon(drawColoredPixmap(pixmap, iconColor));
}

void ThemeSettings::onGSettingsChanged(const QString &key)
{
    Q_UNUSED(key);

    // 图标主题和深浅色模式都可能被修改，这里统一重新读取
    fixIconTheme();
    updateTheme();
}

}

# Copyright (c) KylinSoft Co., Ltd. 2016-2024.All rights reserved.
#
# Authors:
#  Kobe Lee    lixiang@kylinos.cn
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; version 3.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

TEMPLATE = subdirs

SUBDIRS += \
    window \
    startapp \
    settings-daemon \
    settings-ui \
    sensor

message("Builld Architecture:" $$QT_ARCH)
contains(QT_ARCH, i386) {
    message("Enable gps module")
    SUBDIRS += gps
}
contains(QT_ARCH, x86_64) {
    message("Enable gps module")
    SUBDIRS += gps
}
contains(QT_ARCH, armhf) {
    message("Enable gps module")
    SUBDIRS += gps
}
contains(QT_ARCH, arm64) {
    message("Enable gps module")
    SUBDIRS += gps
}

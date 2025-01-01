/*
 * 用于让 kmre 支持安装在星火上上架的 UEngine 安卓应用
*/
#include <QCoreApplication>
#include <QDebug>
#include <QProcess>
#include "commandoption.h"
#include <iostream>

int launch(QStringList argv)
{
    CommandOption option(argv);
    if (option.isSetOption("package")) {
        QString package = option.getOptionValue("package");
        return std::system(("startapp '" + package + "'").toUtf8());
    }
    qDebug() << "参数有误";
    return -1;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList arguments = a.arguments();
    if (arguments.count() == 1) {
        qDebug() << "请输入参数";
        return 1;
    }
    if (arguments[1] == "launch") {
        return launch(arguments);
    }

}

#include "commandoption.h"
#include <QDebug>

CommandOption::CommandOption(QStringList arguments)
{
    setArguments(arguments);
}

QString CommandOption::RemoveSymbol(QString text)
{
    if (text.count() > 2 && text.mid(0, 2) == "--") {
        text = text.mid(2);
    }
    else {
        if (text.count() > 1 && text.at(1) == "-") {
            text = text.mid(1);
        }
    }
    return text.split("=").first();
}


void CommandOption::setArguments(QStringList arguments)
{
    m_arguments = arguments;
}

bool CommandOption::isSetOption(QString option)
{
    for (QString i: m_arguments) {
        i = RemoveSymbol(i);
        if (i == option) {
            return true;
        }
    }
    return false;
}

QString CommandOption::getOptionValue(QString option)
{
    int optionIndex = -1;
    for (int i = 0; i < m_arguments.count(); ++i) {
        QString iStr = m_arguments[i];
        iStr = RemoveSymbol(iStr);
        if (iStr == option) {
            // 读取参数对应的数值
            optionIndex = i;
            break;
        }
    }
    if (optionIndex == -1) {
        return "";
    }
    // 解析参数
    QString indexValue = m_arguments[optionIndex];
    QString nextIndexValue = "";
    if (optionIndex + 1 < m_arguments.count()) {
        nextIndexValue = m_arguments[optionIndex + 1];
    }
    if (indexValue.contains("=")) {
        return indexValue.split("=")[1];
    }
    return nextIndexValue;
}

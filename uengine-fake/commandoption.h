#ifndef COMMANDOPTION_H
#define COMMANDOPTION_H

#include <QObject>
#include <QStringList>

class CommandOption
{
public:
    CommandOption(QStringList arguments);
    void setArguments(QStringList arguments);
    bool isSetOption(QString option);
    QString getOptionValue(QString option);

private:
    QStringList m_arguments;
    QString RemoveSymbol(QString text);
};

#endif // COMMANDOPTION_H

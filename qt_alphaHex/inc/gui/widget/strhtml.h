#ifndef STRHTML_H
#define STRHTML_H

#include <QString>
#include <QColor>

extern void strToHtmlFilter(QString &str);

extern void strToHtml(QString &str,QColor crl);

extern void imgPathToHtml(QString &path);

#endif // STRHTML_H

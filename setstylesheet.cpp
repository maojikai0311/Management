#include "setstylesheet.h"

void Stylesheet::StyleSheet(QString filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)){
        qDebug() << "open centerstyle.css file is failed!";
        return;
    }
    QString strPath = file.readAll();
    qApp->setStyleSheet(strPath);
    file.close();
}

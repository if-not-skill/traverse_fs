#include "filesystemreader.h"

#include <QDir>
#include <QCryptographicHash>

#define MONTH_LIMIT 12


FileSystemReader::FileSystemReader()
{

}

void FileSystemReader::printFilesAlg1(const QString &path)
{
    for(const QString& elem : QDir(path).entryList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::SortFlag::DirsFirst))
    {
        QString fullPath = path + "\\" + elem;

        if(QDir(fullPath).exists())
        {
            printFilesAlg1(fullPath);
        }
        else
        {
            printFileInfo(fullPath);
        }
    }
}

void FileSystemReader::printFilesAlg2(const QString &path)
{
    QStringList dirList;
    for(const QString& elem : QDir(path).entryList(QDir::AllEntries | QDir::NoDotAndDotDot))
    {
        QString fullPath = path + "\\" + elem;

        if(QDir(fullPath).exists())
        {
            dirList.append(fullPath);
        }
        else
        {
            printFileInfo(fullPath);
        }
    }

    for(const QString& elem : dirList)
    {
        printFilesAlg2(elem);
    }
}

void FileSystemReader::printFilesAlg3(const QString &path)
{
    for(int desiredMonth = 0; desiredMonth < MONTH_LIMIT; ++desiredMonth)
    {
        showedHeader = false;
        printFilterAlg3Internal(path, desiredMonth);
        if(showedHeader) qDebug() << "\n";
    }
}

void FileSystemReader::printFileInfo(const QString &filePath)
{
    info.setFile(filePath);
    QString hash = calculateHashForFile(filePath);

    qDebug() << hash << QString::number(info.size()) << info.birthTime().toString("yyyy-MM-dd hh:mm") << filePath;
}

void FileSystemReader::printFilterAlg3Internal(const QString &path, int month)
{
    for(const QString& elem : QDir(path).entryList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::SortFlag::DirsFirst))
    {
        QString fullPath = path + "\\" + elem;

        if(QDir(fullPath).exists())
        {
            printFilterAlg3Internal(fullPath, month);
        }
        else
        {
            info.setFile(fullPath);

            const qint64 secs = info.birthTime().secsTo(QDateTime::currentDateTime());
            const int fileMonth = secs / 60 / 60 / 24 / 30;

            if(fileMonth == month)
            {
                if(showedHeader == false)
                {
                    showedHeader = true;
                    qDebug() << QString("older than %1 months").arg(month);
                }

                printFileInfo(fullPath);
            }
        }
    }
}

QString FileSystemReader::calculateHashForFile(const QString &filePath)
{
    QCryptographicHash hash(QCryptographicHash::Algorithm::Md5);
    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly)) return QString(32, ' ');

    hash.addData(file.readAll());
    return hash.result().toHex();
}

#ifndef FILESYSTEMREADER_H
#define FILESYSTEMREADER_H

#include <QString>
#include <QFileInfo>


class FileSystemReader
{
public:
    FileSystemReader();

    void printFilesAlg1(const QString& path);
    void printFilesAlg2(const QString& path);
    void printFilesAlg3(const QString& path);

private:
    void printFileInfo(const QString& filePath);
    void printFilterAlg3Internal(const QString& path, int month);

    QString calculateHashForFile(const QString& filePath);

private:
    QFileInfo   info;
    bool        showedHeader;

};

#endif // FILESYSTEMREADER_H

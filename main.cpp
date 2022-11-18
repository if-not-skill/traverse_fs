#include <QCoreApplication>
#include "filesystemreader.h"

#define ALGORITHM_INDEX 2
#define PATH_INDEX      3
#define CORRECT_ARGS    4

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if(argc != CORRECT_ARGS)
    {
        qWarning() << "Not correct number of params:" << argc;
        return -1;
    }

    const int algorithm = atoi(argv[ALGORITHM_INDEX]);
    if(algorithm <= 0 || algorithm > 3)
    {
        qWarning() << "Algorithm is specified incorrectly";
        return -2;
    }

    QString rootPath = argv[PATH_INDEX];

    qDebug() << "path:" << rootPath;
    qDebug() << "algorithm:" << algorithm << "\n";

    FileSystemReader filePrinter;
    switch(algorithm)
    {
    case 1:
        filePrinter.printFilesAlg1(rootPath);
        break;
    case 2:
        filePrinter.printFilesAlg2(rootPath);
        break;
    case 3:
        filePrinter.printFilesAlg3(rootPath);
        break;
    }

    return a.exec();
}

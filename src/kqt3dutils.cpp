#include "kqt3dutils.h"

#include <QFile>

namespace kqt3d {

QByteArray readFile(QString filename) {
    QByteArray fileContent;
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Read the file here
        fileContent = file.readAll();
        file.close();
    }
    return fileContent;
}

}

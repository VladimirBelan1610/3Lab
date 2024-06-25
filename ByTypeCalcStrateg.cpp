#include "ByTypeCalcStrateg.h"
#include <QDir>
#include <QMap>
#include <QStringList>




QMap<QString, double> ByTypeCalcStrateg::calculateSize(const QString& directory)
{
    QMap<QString, double> map; //Словарь, содержащий имя файла и его размер
    QFileInfo file(directory); // Создаем объект типа QFileInfo для проверки информации о его текущей позиции в файловой системе

    if (file.isDir()) { // Проверка, является ли текущий файл директорией (папкой)
        QDir dir(directory); //объект типа QDir, передавая в него текущий путь, для работы с директориями
        QFileInfoList filelist = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks); //Получаем список файлов из текущей директории

        for (const QFileInfo& fileInfo : filelist) { // Проходимся по файлам из списка
            QString type = fileInfo.suffix(); //Вычисляем расширение файла с помощью метода suffix()
            int file_size = fileInfo.size(); //Вычисляем размер текущего файла
            map[type] += file_size; // Заносим в словарь размер файла к соответствующему типу
        }

        QStringList subDirList = dir.entryList(QDir::NoDotAndDotDot | QDir::Dirs); // Получаем список поддиректорий (исключая родительскую
        // и текущую директории)
        for (const QString& subDirName : subDirList) { //Проходимся по каждой поддиректории из списка
            QString subDirPath = directory + "/" + subDirName; // Формируем полный путь к поддиректории
            QMap<QString, double> subDirMap = this->calculateSize(subDirPath); //Рекурсивно вызываем метод calculate для текущей поддиректории
            //с уровнем вложенности 0 и результат записываем в словарь для хранения информации о поддиректориях
            for (auto it = subDirMap.begin(); it != subDirMap.end(); ++it) { //Проходимся по элементам словаря поддиректорий
                map[it.key()] += it.value(); //Заносим в словарь-результат тип файла и его размер в поддиректории
            }
        }
    }
    return map;
}

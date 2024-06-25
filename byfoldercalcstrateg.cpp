#include "ByFolderCalcStrateg.h"
#include <QDir>
int calculateFolderSize(const QString& folderPath) //путь к папке, размер которой нужно вычислить.
    //Параметр передается по константной ссылке для эффективности.
{
    QDir dir(folderPath); //Создается объект QDir, который представляет директорию, путь к которой передан в параметре folderPath.
    //Этот объект будет использоваться для работы с содержимым директории.
    dir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
    dir.setSorting(QDir::Size | QDir::Reversed);

    //setFilter: Устанавливает фильтры для включения в список файлов и директорий:
    //- QDir::Files: Включает файлы.
    //- QDir::Dirs: Включает директории.
    //- QDir::NoDotAndDotDot: Исключает специальные записи . (текущая директория) и .. (родительская директория).
    //- QDir::Hidden: Включает скрытые файлы и директории.
    //- QDir::System: Включает системные файлы и директории.
    //**setSorting**: Устанавливает порядок сортировки:
    //- QDir::Size: Сортировка по размеру.
    //- QDir::Reversed: В обратном порядке (от большего к меньшему).

    QFileInfoList list = dir.entryInfoList(); //Получает список всех файлов и директорий в текущей директории, удовлетворяющих
                                             //установленным фильтрам, в виде объекта QFileInfoList.
    qint64 totalSize = 0; //Инициализируется переменная totalSize, которая будет использоваться для накопления общего размера всех файлов и директорий.

    //Если текущий элемент (fileInfo) является директорией (fileInfo.isDir()), рекурсивно
    //вызывается функция calculateFolderSize для этой директории, и ее размер добавляется к totalSize.

    for (const QFileInfo& fileInfo : list) {
        if (fileInfo.isDir()) {
            totalSize += calculateFolderSize(fileInfo.absoluteFilePath()); //Если текущий элемент является файлом, его размер
            //(fileInfo.size()) добавляется к totalSize.
        } else {
            totalSize += fileInfo.size(); //записываем размер файла в totalSize
        }
    }


    return (totalSize); //Возвращает накопленный общий размер всех файлов и директорий.
}
QMap<QString, double> ByFolderCalcStrateg::calculateSize(const QString& directory) //ассоциативный контейнер, где ключом является имя
    //файла или папки, а значением — их размер. QString& directory — путь к директории, для которой нужно вычислить размеры файлов и
    //подпапок.
{
    QDir dir(directory); //Создается объект QDir, который представляет директорию, путь к которой передан в параметре directory.
    //Этот объект будет использоваться для работы с содержимым директории.
    dir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
    dir.setSorting(QDir::Size | QDir::Reversed);

    //setFilter: Устанавливает фильтры для включения в список файлов и директорий:
    // - QDir::Files: Включает файлы.
    // - QDir::Dirs: Включает директории.
    // - QDir::NoDotAndDotDot: Исключает специальные записи . (текущая директория) и .. (родительская директория).
    // - QDir::Hidden: Включает скрытые файлы и директории.
    // - QDir::System: Включает системные файлы и директории.
    // setSorting: Устанавливает порядок сортировки:
    // - QDir::Size: Сортировка по размеру.
    //- QDir::Reversed: В обратном порядке (от большего к меньшему).

    QFileInfoList list = dir.entryInfoList(); //Получает список всех файлов и директорий в текущей директории, удовлетворяющих
    //установленным фильтрам, в виде объекта QFileInfoList.
    QMap<QString, double> folderSizes; //Инициализируется ассоциативный контейнер QMap, который будет использоваться для хранения
    //размеров файлов и папок. Ключом является имя файла или папки (QString), а значением — их размер (double).

    for (const QFileInfo& fileInfo : list) { //Цикл проходит по каждому элементу в списке list.
        if (fileInfo.isDir()) { //Если текущий элемент (fileInfo) является директорией (fileInfo.isDir()), вызывается функция
            //calculateFolderSize для этой директории, чтобы вычислить ее размер. Затем этот размер добавляется в контейнер
            //folderSizes с именем директории в качестве ключа.
            double folderSize = calculateFolderSize(fileInfo.absoluteFilePath());
            folderSizes.insert(fileInfo.fileName(), folderSize); // Если текущий элемент является файлом, его размер преобразуется в
            //тип double и добавляется в контейнер folderSizes с именем файла в качестве ключа.
        } else {

            // Эта функция-член класса QFileInfo возвращает размер файла в байтах как значение типа qint64 (целое число 64-битной длины, знаковое).
            double fileSize = static_cast<double>(fileInfo.size()); //Оператор static_cast используется для явного преобразования
            //одного типа данных в другой. В данном случае, он преобразует значение типа qint64 в значение типа double.
            folderSizes.insert(fileInfo.fileName(), fileSize); //Метод insert класса QMap вставляет новую пару ключ-значение в карту.
            //fileInfo.fileName() - Этот метод класса QFileInfo возвращает имя файла (без пути) в виде строки (QString).
            //Это имя используется как ключ в карте. Значение переменной fileSize, которое было преобразовано в тип double,
            //используется как значение в карте.
        }
    }

    return folderSizes;
}

# Лабораторная работа No1: Создание процессов

## Описание

Этот репозиторий содержит программу, состоящую из трех компонентов: Main, Creator и Reporter, созданных для выполнения лабораторной работы No1 на кафедре технологии программирования в Белорусском государственном университете.

## Структура Программы

### Утилита Creator

Утилита Creator создает бинарный файл, имя которого и количество записей в котором получает через командную строку. Записи файла вводятся с консоли и имеют следующую структуру:

```c++
struct employee
{
    int num;            // идентификационный номер сотрудника
    char name[10];      // имя сотрудника
    double hours;       // количество отработанных часов
};
```
### Утилита Reporter

Утилита Reporter создает текстовый файл, содержащий упорядоченный список сотрудников с начисленной заработной платой. Отчет формируется на основе бинарного файла, созданного программой Creator.

1. Утилита получает через командную строку следующие данные:
   1. Имя исходного бинарного файла.
   2. Имя файла отчета.
   3. Оплата за час работы.

2. Отчет содержит следующие строки:
   1. Заголовок: Отчет по файлу «имя исходного бинарного файла».
   2. Строка: Номер сотрудника, имя сотрудника, часы, зарплата.
   3. Список сотрудников по строкам. Каждая строка содержит информацию из соответствующей записи бинарного файла, а последний столбец строки - начисленную зарплату = кол-ву отработанных часов * оплату за час работы.

## Программа Main

Программа Main выполняет следующие действия:
1. Запрашивает с консоли имя бинарного файла и количество записей в этом файле.
2. Запускает утилиту Creator, которой передает через командную строку имя создаваемого бинарного файла и количество записей в этом файле.
3. Ждет завершения работы утилиты Creator.
4. Выводит содержимое созданного бинарного файла на консоль.
5. Запрашивает с консоли:
   1. Имя файла отчета.
   2. Оплату за час работы.
6. Запускает утилиту Reporter, которой передает через командную строку:
   1. Имя исходного бинарного файла.
   2. Имя файла отчета.
   3. Оплату за час работы.
7. Ждет завершения работы утилиты Reporter.
8. Выводит отчет на консоль.
9. Завершает свою работу.

## Примечание

Для ожидания завершения работы процессов Creator и Reporter используется функция:
```c++
DWORD WaitForSingleObject(
    HANDLE hHandle, // дескриптор объекта
    DWORD dwMilliseconds // интервал ожидания в миллисекундах
);
```
    где второй параметр установить равным INFINITE, например
    WaitForSingleObject(hCreator, INFINITE);
    здесь hCreator – дескриптор процесса Creator.

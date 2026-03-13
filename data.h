#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Структура для описания книги
typedef struct {
    char title[100];
    char author[100];
    int year;
    char genre[50];
    int pages;
} Book;

// Структура для каталога книг
typedef struct {
    Book* books; // Динамический массив книг
    int size;    // Текущий размер каталога
    int capacity; // Максимальная вместимость каталога
} Catalog;

// Инициализация каталога
void initCatalog(Catalog* catalog, int initialCapacity);
// Расширение массива на определенное количество элементов
void expandCatalog(Catalog* catalog, int additionalCapacity);
// Добавление книги в конец каталога
void addBook(Catalog* catalog);
// Вставка книги на указанную позицию
void insertBook(Catalog* catalog, int position);
// Удаление книги по индексу
void removeBookByIndex(Catalog* catalog, int index);
// Удаление последней книги из каталога
void removeLastBook(Catalog* catalog);
// Редактирование книги по индексу
void editBook(Catalog* catalog);
// Сортировка массива книг по выбранному полю (метод пузырька)
void sortBooks(Catalog* catalog);
// Вывод всех книг в каталоге
void displayCatalog(const Catalog* catalog);
// Очистка списка и освобождение памяти
void clearCatalog(Catalog* catalog);
// Функция поиска книг
void searchBooks(const Catalog* catalog);
// Сохранение каталога в файл
void saveCatalogToFile(const Catalog* catalog, const char* filename);
// Загрузка каталога из файла
void loadCatalogFromFile(Catalog* catalog, const char* filename);

#endif // DATA_H
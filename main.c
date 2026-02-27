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
void initCatalog(Catalog* catalog, int initialCapacity) {
    catalog->books = (Book*)malloc(initialCapacity * sizeof(Book));
    // Cначала пустой, с выделенной памятью на 5 книг
    catalog->size = 0;
    catalog->capacity = initialCapacity;
}

// Расширение массива на определённое количество элементов
void expandCatalog(Catalog* catalog, int additionalCapacity) {
    int newCapacity = catalog->capacity + additionalCapacity;
    Book* newBooks = (Book*)malloc(newCapacity * sizeof(Book));

    // Копируем существующие книги
    for (int i = 0; i < catalog->size; ++i) {
        newBooks[i] = catalog->books[i];
    }

    // Освобождаем старую память
    free(catalog->books);
    catalog->books = newBooks;
    catalog->capacity = newCapacity;
}

// Добавление книги в конец каталога
void addBook(Catalog* catalog) {
    // Если массив заполнен, расширяем его на 5 элементов
    // можно сделать на 1 элемент, но тогда слишком часто будет пересоздание памяти в expandCatalog
    if (catalog->size >= catalog->capacity) {
        expandCatalog(catalog, 5);
    }

    // Ввод данных о новой книге
    Book newBook;
    printf("Введите название книги: ");
    fgets(newBook.title, sizeof(newBook.title), stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0';

    printf("Введите автора книги: ");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0';

    printf("Введите год издания: ");
    scanf("%d", &newBook.year);
    getchar();

    printf("Введите жанр книги: ");
    fgets(newBook.genre, sizeof(newBook.genre), stdin);
    newBook.genre[strcspn(newBook.genre, "\n")] = '\0';

    printf("Введите количество страниц: ");
    scanf("%d", &newBook.pages);
    getchar();

    // Добавляем книгу в конец каталога
    catalog->books[catalog->size] = newBook;
    catalog->size++;
    printf("Книга добавлена в каталог!\n");
}

// Удаление книги из каталога по индексу
void removeBook(Catalog* catalog) {
    int index;
    printf("Введите индекс книги для удаления (от 0 до %d): ", catalog->size - 1);
    scanf("%d", &index);
    getchar();

    if (index < 0 || index >= catalog->size) {
        printf("Некорректный индекс.\n");
        return;
    }

    // Сдвигаем все элементы после найденного на одну позицию влево
    for (int i = index; i < catalog->size - 1; ++i) {
        catalog->books[i] = catalog->books[i + 1];
    }

    catalog->size--;

    printf("Книга удалена из каталога!\n");
}

// Удаление последней книги из каталога
void removeLastBook(Catalog* catalog) {
    // Проверка на пустоту
    if (catalog->size == 0) {
        printf("Каталог пуст. Нечего удалять.\n");
        return;
    }

    catalog->size--;

    // Уменьшаем размер массива, так как удален последний элемент
    int newCapacity = catalog->size;
    Book* newBooks = (Book*)malloc(newCapacity * sizeof(Book));

    // Копируем существующие книги
    for (int i = 0; i < catalog->size; ++i) {
        newBooks[i] = catalog->books[i];
    }

    // Освобождаем старую память
    free(catalog->books);
    catalog->books = newBooks;
    catalog->capacity = newCapacity;

    printf("Последняя книга удалена из каталога!\n");
}

// Редактирование книги по индексу
void editBook(Catalog* catalog) {
    int index;
    printf("Введите индекс книги для редактирования (от 0 до %d): ", catalog->size - 1);
    scanf("%d", &index);
    getchar();

    if (index < 0 || index >= catalog->size) {
        printf("Некорректный индекс.\n");
        return;
    }

    Book* book = &catalog->books[index];
    int choice;

    do {
        printf("\n--- Редактирование книги ---\n");
        printf("1. Название\n");
        printf("2. Автор\n");
        printf("3. Год издания\n");
        printf("4. Жанр\n");
        printf("5. Количество страниц\n");
        printf("6. Завершить редактирование\n");
        printf("Выберите поле для редактирования: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Введите новое название: ");
                fgets(book->title, sizeof(book->title), stdin);
                book->title[strcspn(book->title, "\n")] = '\0';
                break;
            case 2:
                printf("Введите нового автора: ");
                fgets(book->author, sizeof(book->author), stdin);
                book->author[strcspn(book->author, "\n")] = '\0';
                break;
            case 3:
                printf("Введите новый год издания: ");
                scanf("%d", &book->year);
                getchar();
                break;
            case 4:
                printf("Введите новый жанр: ");
                fgets(book->genre, sizeof(book->genre), stdin);
                book->genre[strcspn(book->genre, "\n")] = '\0';
                break;
            case 5:
                printf("Введите новое количество страниц: ");
                scanf("%d", &book->pages);
                getchar();
                break;
            case 6:
                printf("Редактирование завершено.\n");
                break;
            default:
                printf("Некорректный выбор. Попробуйте снова.\n");
        }
    } while (choice != 6);
}

// Поиск книг по критерию
void searchBooks(const Catalog* catalog) {
    int choice;
    printf("\n--- Поиск книг ---\n");
    printf("1. По названию\n");
    printf("2. По автору\n");
    printf("3. По жанру\n");
    printf("4. По году издания\n");
    printf("5. По диапазону количества страниц\n");
    printf("Выберите критерий поиска: ");
    scanf("%d", &choice);
    getchar();

    bool found = false;
    char searchString[100];
    int searchYear, minPages, maxPages;

    switch (choice) {
        case 1:
            printf("Введите название для поиска: ");
            fgets(searchString, sizeof(searchString), stdin);
            searchString[strcspn(searchString, "\n")] = '\0';
            for (int i = 0; i < catalog->size; ++i) {
                if (strstr(catalog->books[i].title, searchString) != NULL) {
                    printf("\n--- Книга найдена ---\n");
                    printf("Индекс: %d\n", i);
                    printf("Название: %s\n", catalog->books[i].title);
                    printf("Автор: %s\n", catalog->books[i].author);
                    printf("Год издания: %d\n", catalog->books[i].year);
                    printf("Жанр: %s\n", catalog->books[i].genre);
                    printf("Количество страниц: %d\n", catalog->books[i].pages);
                    found = true;
                }
            }
            break;
        case 2:
            printf("Введите автора для поиска: ");
            fgets(searchString, sizeof(searchString), stdin);
            searchString[strcspn(searchString, "\n")] = '\0';
            for (int i = 0; i < catalog->size; ++i) {
                if (strstr(catalog->books[i].author, searchString) != NULL) {
                    printf("\n--- Книга найдена ---\n");
                    printf("Индекс: %d\n", i);
                    printf("Название: %s\n", catalog->books[i].title);
                    printf("Автор: %s\n", catalog->books[i].author);
                    printf("Год издания: %d\n", catalog->books[i].year);
                    printf("Жанр: %s\n", catalog->books[i].genre);
                    printf("Количество страниц: %d\n", catalog->books[i].pages);
                    found = true;
                }
            }
            break;
        case 3:
            printf("Введите жанр для поиска: ");
            fgets(searchString, sizeof(searchString), stdin);
            searchString[strcspn(searchString, "\n")] = '\0';
            for (int i = 0; i < catalog->size; ++i) {
                if (strstr(catalog->books[i].genre, searchString) != NULL) {
                    printf("\n--- Книга найдена ---\n");
                    printf("Индекс: %d\n", i);
                    printf("Название: %s\n", catalog->books[i].title);
                    printf("Автор: %s\n", catalog->books[i].author);
                    printf("Год издания: %d\n", catalog->books[i].year);
                    printf("Жанр: %s\n", catalog->books[i].genre);
                    printf("Количество страниц: %d\n", catalog->books[i].pages);
                    found = true;
                }
            }
            break;
        case 4:
            printf("Введите год издания для поиска: ");
            scanf("%d", &searchYear);
            getchar();
            for (int i = 0; i < catalog->size; ++i) {
                if (catalog->books[i].year == searchYear) {
                    printf("\n--- Книга найдена ---\n");
                    printf("Индекс: %d\n", i);
                    printf("Название: %s\n", catalog->books[i].title);
                    printf("Автор: %s\n", catalog->books[i].author);
                    printf("Год издания: %d\n", catalog->books[i].year);
                    printf("Жанр: %s\n", catalog->books[i].genre);
                    printf("Количество страниц: %d\n", catalog->books[i].pages);
                    found = true;
                }
            }
            break;
        case 5:
            printf("Введите минимальное количество страниц: ");
            scanf("%d", &minPages);
            printf("Введите максимальное количество страниц: ");
            scanf("%d", &maxPages);
            getchar();
            for (int i = 0; i < catalog->size; ++i) {
                if (catalog->books[i].pages >= minPages && catalog->books[i].pages <= maxPages) {
                    printf("\n--- Книга найдена ---\n");
                    printf("Индекс: %d\n", i);
                    printf("Название: %s\n", catalog->books[i].title);
                    printf("Автор: %s\n", catalog->books[i].author);
                    printf("Год издания: %d\n", catalog->books[i].year);
                    printf("Жанр: %s\n", catalog->books[i].genre);
                    printf("Количество страниц: %d\n", catalog->books[i].pages);
                    found = true;
                }
            }
            break;
        default:
            printf("Некорректный выбор.\n");
    }

    if (!found) {
        printf("Книги не найдены.\n");
    }
}

// Вывод всех книг в каталоге
void displayCatalog(const Catalog* catalog) {
    if (catalog->size == 0) {
        printf("Каталог пуст.\n");
        return;
    }

    printf("\n--- Каталог книг ---\n");
    for (int i = 0; i < catalog->size; ++i) {
        const Book* book = &catalog->books[i];
        printf("Индекс: %d\n", i);
        printf("Название: %s\n", book->title);
        printf("Автор: %s\n", book->author);
        printf("Год издания: %d\n", book->year);
        printf("Жанр: %s\n", book->genre);
        printf("Количество страниц: %d\n\n", book->pages);
    }
}

// Очистка списка и освобождение памяти
void clearCatalog(Catalog* catalog) {
    free(catalog->books);
    catalog->books = NULL;
    catalog->size = 0;
    catalog->capacity = 0;
    printf("Каталог очищен, память освобождена.\n");
}

int main() {
    Catalog catalog;
    initCatalog(&catalog, 5);

    int choice;
    do {
        printf("\n--- Меню ---\n");
        printf("1. Добавить книгу\n");
        printf("2. Удалить книгу по индексу\n");
        printf("3. Удалить последнюю книгу\n");
        printf("4. Редактировать книгу\n");
        printf("5. Поиск книг\n");
        printf("6. Показать каталог\n");
        printf("7. Очистить каталог\n");
        printf("8. Выйти\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                addBook(&catalog);
                break;
            case 2:
                removeBook(&catalog);
                break;
            case 3:
                removeLastBook(&catalog);
                break;
            case 4:
                editBook(&catalog);
                break;
            case 5:
                searchBooks(&catalog);
                break;
            case 6:
                displayCatalog(&catalog);
                break;
            case 7:
                clearCatalog(&catalog);
                break;
            case 8:
                printf("Выход из программы.\n");
                break;
            default:
                printf("Некорректный выбор. Попробуйте снова.\n");
        }
    } while (choice != 8);

    // Освобождение памяти перед завершением программы
    if (catalog.books != NULL) {
        free(catalog.books);
    }

    return 0;
}

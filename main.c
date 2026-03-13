#include "data.c"
#include "data.h"
#include <windows.h>

int main() {
    // Устанавливаем кодировку UTF-8 для консоли
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Catalog catalog;
    initCatalog(&catalog, 5);

    int choice;
    do {
        printf("\n--- Меню ---\n");
        printf("1. Добавить книгу\n");
        printf("2. Вставить книгу на позицию\n");
        printf("3. Удалить книгу по индексу\n");
        printf("4. Удалить последнюю книгу\n");
        printf("5. Редактировать книгу\n");
        printf("6. Поиск книг\n");
        printf("7. Сортировать книги\n");
        printf("8. Показать каталог\n");
        printf("9. Очистить каталог\n");
        printf("10. Сохранить каталог в файл\n");
        printf("11. Загрузить каталог из файла\n");
        printf("12. Выйти\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                addBook(&catalog);
                break;
            case 2: {
                int position;
                printf("Введите позицию для вставки (от 0 до %d): ", catalog.size);
                scanf("%d", &position);
                getchar();
                insertBook(&catalog, position);
                break;
            }
            case 3: {
                int index;
                printf("Введите индекс книги для удаления (от 0 до %d): ", catalog.size - 1);
                scanf("%d", &index);
                getchar();
                removeBookByIndex(&catalog, index);
                break;
            }
            case 4:
                removeLastBook(&catalog);
                break;
            case 5:
                editBook(&catalog);
                break;
            case 6:
                searchBooks(&catalog);
                break;
            case 7:
                sortBooks(&catalog);
                break;
            case 8:
                displayCatalog(&catalog);
                break;
            case 9:
                clearCatalog(&catalog);
                break;
            case 10: {
                char filename[100];
                printf("Введите имя файла для сохранения: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                saveCatalogToFile(&catalog, filename);
                break;
            }
            case 11: {
                char filename[100];
                printf("Введите имя файла для загрузки: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                loadCatalogFromFile(&catalog, filename);
                break;
            }
            case 12:
                printf("Выход из программы.\n");
                break;
            default:
                printf("Некорректный выбор. Попробуйте снова.\n");
        }
    } while (choice != 12);

    // Освобождение памяти перед завершением программы
    if (catalog.books != NULL) {
        free(catalog.books);
    }

    return 0;
}
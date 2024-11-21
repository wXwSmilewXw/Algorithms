#include <stdlib.h> 
#include <stdio.h>  
#include <string.h> 
#include "vector.h" 

typedef struct Vector {
    size_t size; // Текущий размер вектора
    Data* data; // Указатель на массив данных
    size_t capacity; // Общая ёмкость вектора
    FFree* distruct; // Указатель на функцию distruct для освобождения данных
} Vector;

// Функция для создания вектора с заданной функцией освобождения памяти
Vector *vector_create(FFree f) {
    size_t initial_capacity = 4; // Начальная емкость вектора

    Vector* vec = (Vector *)malloc(sizeof(Vector)); // Выделение памяти для структуры вектора
    
    if (!vec) { // Проверка успешности выделения памяти
        fprintf(stderr, "Ошибка выделения памяти для структуры"); 
        return NULL; 
    }

    vec->data = (Data *)malloc(initial_capacity * sizeof(Data)); // Выделение памяти для массива данных

    if (!vec->data) { // Проверка успешности выделения массива данных
        free(vec); // Освобождение памяти структуры вектора
        fprintf(stderr, "Ошибка выделения памяти для массива"); 
        return NULL; 
    }

    vec->distruct = f; // Установка функции деструктора
    vec->size = 0; // Инициализация размера вектора
    vec->capacity = initial_capacity; // Установка емкости вектора
    return vec; // Возврат указателя на созданный вектор
}

// Функция для удаления вектора
void vector_delete(Vector *vector) {
    if (vector == NULL) { // Проверка на NULL
        fprintf(stderr, "Ошибка удаления"); 
        return; 
    }

    if (vector->distruct != NULL) { // Проверка наличия функции деструктора
        for (size_t i = 0; i < vector->size; i++) { // Цикл по всем элементам вектора
            void* ptr = (void*)vector->data[i]; // Получение элемента
            vector->distruct(ptr); // Вызов функции деструктора для элемента
        }
    }
    
    free(vector->data); // Освобождение памяти массива данных
    vector->data = NULL; // Обнуление указателя на данные
    vector->size = 0; // Обнуление размера
    vector->capacity = 0; // Обнуление емкости
    free(vector); // Освобождение памяти структуры вектора
}

// Функция для получения элемента вектора по индексу
Data vector_get(const Vector *vector, size_t index) {
    if (vector == NULL || index >= vector->size) { // Проверка на NULL и выход за размер
        return NULL; 
    }
    Data element = vector->data[index]; // Получение элемента по индексу

    if (element == NULL) { // Проверка на NULL
        return NULL;
    }

    return element; // Возврат элемента
}

// Функция для установки значения элемента вектора по индексу
void vector_set(Vector *vector, size_t index, Data value) {
    // Проверка на NULL - если вектор пуст, выводим сообщение об ошибке и выходим из функции
    if (vector == NULL) {
        fprintf(stderr, "Ошибка: вектор пуст!\n"); 
        return;
    }


    vector_resize(vector, vector->size+1); // Увеличиваем размер вектора до необходимого
    

    // Если элемент на указанном индексе существует, вызываем деструктор для освобождения памяти
    if (vector->data[index] != NULL) {
        vector->distruct(vector->data[index]); // Вызов деструктора
    }
    
    // Устанавливаем новое значение на указанном индексе
    vector->data[index] = value; // Установка нового значения
}

// Функция для получения текущего размера вектора
size_t vector_size(const Vector *vector) {
    return vector->size; // Возврат размера вектора
}

// Функция для изменения размера вектора
void vector_resize(Vector *v, size_t new_size) {
    if (v == NULL) return; // Проверка на NULL 

    if (new_size > v->capacity) { // Если новый размер превышает емкость
        size_t new_capacity = (v->capacity == 0) ? 1 : v->capacity * 2;
        while (new_capacity < new_size) {
            new_capacity = 2; // Увеличиваем емкость до нужного размера
        }

        Data new_data = (Data*)malloc(new_capacity * sizeof(Data)); // Выделение памяти для нового массива
        if (new_data == NULL) { // Проверка успешности выделения памяти
            return;
    }

        if (v->data != NULL) { // Проверка наличия данных
            memcpy(new_data, v->data, v->size * sizeof(Data)); // Копирование старых данных в новый массив
            free(v->data); // Освобождение старого массива
        }

        // Инициализация оставшихся элементов NULL (если требуется)
        memset(new_data + v->size, 0, (new_capacity - v->size) * sizeof(Data));

        v->data = new_data; // Установка нового массива данных
        v->capacity = new_capacity; // Обновление емкости
    }

    // Устанавливаем новый размер вектора (если он больше текущего)
    if (new_size > v->size) {
        v->size = new_size; // Обновляем размер
    }
}

// Функция для добавления элемента в конец вектора
void push_back(Vector *vector, Data value) {
    if (vector == NULL) { // Проверка на NULL
        return;
    }

    if (vector->size >= vector->capacity) { // Проверка на заполнение вектора
        vector_resize(vector, vector->size + 1); // Увеличение размера
    }
    vector->data[vector->size++] = value; // Добавление элемента и увеличение размера
}

// Функция для удаления элемента из конца вектора
Data pop_back(Vector *vector) {
    if (vector == NULL || vector->size == 0) { // Проверка на NULL и пустоту вектора
        printf("Ошибка: стек пуст!\n"); 
        return NULL;
    }
    
    return vector->data[--vector->size]; // Уменьшение размера и возврат последнего элемента
}

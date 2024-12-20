#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef void* Data; // Определяем тип Data как указатель на произвольный тип

typedef void (FFree)(void*); // Определяем тип функции, которая освобождает память

typedef struct Vector Vector;
// Определяем структуру вектора, содержащую информацию о размере, данных и ёмкости

#ifdef __cplusplus // Проверяем, компилируется ли код в C++
extern "C" { // Указываем, что следующие функции имеют C-совместимый интерфейс
#endif

// Объявление функций для работы с вектором
Vector *vector_create(FFree f); // Создание вектора

void vector_delete(Vector *vector); // Удаление вектора и освобождение памяти

Data vector_get(const Vector *vector, size_t index); // Получение элемента вектора по индексу

void vector_set(Vector *vector, size_t index, Data value); // Установка значения элемента вектора

size_t vector_size(const Vector *vector); // Получение текущего размера вектора
size_t vector_capacity(const Vector *vector); // Получение текущей емкости вектора

void vector_resize(Vector *vector, /*size_t new_size*/ size_t new_capacity); // Изменение размера вектора

void push_back(Vector *vector, Data value); // Добавление элемента в конец вектора

Data pop_back(Vector *vector); // Удаление последнего элемента из вектора

#ifdef __cplusplus
}
#endif

#endif

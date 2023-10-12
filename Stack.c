#include <stdio.h>
#include <stdlib.h>


struct Stack;   // Структура, отвечающая за элементы очереди
struct Stack *init(int);    // Инициализация очереди
void Push(struct Stack **, int);    // Добавление элемента в очередь
int Pop(struct Stack *);   // Чтение элемента из очереди с последующим удалением


int main()
{
    int a = 10;
    int result = 0;

    struct Stack *list = init(a);   // Инициализация очереди
    Push(&list, 5); // Добавление значения в очередь
    Push(&list, 6);
    Push(&list, 7);
    result = Pop(list);   // Получение значения
    printf("%d\n", result);
    result = Pop(list);
    printf("%d\n", result);
    result = Pop(list);
    printf("%d\n", result);
    Push(&list, 8);
    result = Pop(list);
    printf("%d\n", result);
    result = Pop(list);
    printf("%d\n", result);
    Push(&list, 9);
    Push(&list, 11);
    result = Pop(list);
    printf("%d\n", result);
    result = Pop(list);
    printf("%d\n", result);
    Push(&list, -13);
    Push(&list, -99);
    result = Pop(list);
    printf("%d\n", result);
    result = Pop(list);
    printf("%d\n", result);
    Push(&list, 1);
    result = Pop(list);
    printf("%d\n", result);


    return 0;
}


struct Stack
{
    int data;   // Числовой элемент очереди
    struct Stack *next; // Указатель на следующий элемент очереди
};

struct Stack *init(int element)
{
    struct Stack *p = NULL; // Создание указателя на структуру

    if((p = malloc(sizeof(struct Stack))) == NULL)  // Выделение памяти под структуру
    {
        printf("Unable to allocate memory: ");
        exit(1);
    }

    p -> data = element;    // Присваивание введённого значения полю данных
    p -> next = NULL;   // Установка на нулевой указатель

    return p;
}

void Push(struct Stack **list ,int element)
{
    struct Stack *new_element = init(element);  // Создание нового элемента

    struct Stack *tmp = *list;  // Сохранение оригинального указателя на голову

    while(tmp -> next != NULL)
    {
        tmp = tmp -> next;
    }

    tmp -> next = new_element;
}

int Pop(struct Stack *list)
{
    int res = 0;    // Результат извлеения из очереди
    int i = 0, j;   // Переменные счётчики числа элементов стека
    struct Stack *tmp = list, *p = list;   // Сохранение указателя на вершину стека

    while(list -> next != NULL) // Обход списка
    {
        list = list -> next;
        i++;
    }
    i--;

    res = list -> data; // Получение элемента стека

    struct Stack *to_delete = list; // Переназначение указателя на последний элемент

    for(j = 0; j < i; j++)
    {
    tmp = tmp -> next;    // Очередной обход списка до предпоследнего элемента
    }

    tmp -> next = NULL; // Присвоение предпоследнему элементу нулевого указателя

    // Сохранение первого листа списка
    if(p -> next != NULL) free(to_delete);    // Очистка памяти по последнему указателю

    return res;    // Возвращение значения
}

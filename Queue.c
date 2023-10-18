#include <stdio.h>
#include <stdlib.h>

struct Queue;   // Структура, отвечающая за элементы очереди
struct Queue *init(int);    // Инициализация очереди
void Push(struct Queue **, int);    // Добавление элемента в очередь
struct Queue *Pop(struct Queue *);   // Чтение элемента из очереди с последующим удалением

int res = 0;    // Результат извлеения из очереди

int main()
{
    int elem = 0, cont = 0;

    printf("\t# Queue #\n");
    printf("Enter element: ");
    scanf("%d", &elem);
    struct Queue *list = init(elem);   // Инициализация очереди
    printf("Continue(any integer) or not(0): ");
    scanf("%d", &cont);
    if(cont == 0) goto printing;

    while(cont != 0)
    {
        printf("Enter element: ");
        scanf("%d", &elem);
        Push(&list, elem);
        printf("Continue(any integer) or not(0): ");
        scanf("%d", &cont);
    }
    printf("+----------+\n| elements |\n+----------+\n");
    while(list != NULL)
    {
        list = Pop(list);
        printf("|%9d |\n+----------+\n", res);
    }
    goto ret;

    printing:
    list = Pop(list);
    printf("+----------+\n|  element |\n+----------+\n");
    printf("|%9d |\n+----------+\n", res);

    ret:
    return 0;
}


struct Queue
{
    int data;   // Числовой элемент очереди
    struct Queue *next; // Указатель на следующий элемент очереди
};

struct Queue *init(int element)
{
    struct Queue *p = NULL; // Создание указателя на структуру

    if((p = malloc(sizeof(struct Queue))) == NULL)  // Выделение памяти под структуру
    {
        printf("Unable to allocate memory: ");
        exit(1);
    }

    p -> data = element;    // Присваивание введённого значения полю данных
    p -> next = NULL;   // Установка на нулевой указатель

    return p;
}

void Push(struct Queue **list ,int element)
{
    struct Queue *tmp = *list;  // Сохранение оригинального указателя на голову

    if(tmp != NULL) // Проверка на существование списка
    {
    struct Queue *new_element = init(element);  // Создание нового элемента

    while(tmp -> next != NULL)
    {
        tmp = tmp -> next;
    }

    tmp -> next = new_element;
    }
    else if(tmp == NULL)    // Инициализация списка, если его нет
    {
        *list = init(element);
    }
}

struct Queue *Pop(struct Queue *list)
{
    res = list -> data; // Получение элемента очереди

    struct Queue *to_delete = list; // Переназначение указателя на первый элемент
    list = list -> next;    //Переназначение первого указателя на следующий
    free(to_delete);    // Очистка памяти по предыдущему указателю

    return list;    // Возвращение нового указателя на вершину очереди
}

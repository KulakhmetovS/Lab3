#include <stdio.h>
#include <stdlib.h>

struct Queue;   // Структура, отвечающая за элементы очереди
struct Queue *init(int, int);    // Инициализация очереди
void Push(struct Queue **, int, int);    // Добавление элемента в очередь
struct Queue *Priority(struct Queue *);  // Сортировка элементов в соответствии с их приоритетом
struct Queue *QueueSort(struct Queue *, int);   //Создание отсортированной очереди
struct Queue *Pop(struct Queue *);   // Чтение элемента из очереди с последующим удалением

int res = 0;    // Результат извлечения из очереди
int pr = 0; // Результат извлечения приоритета
int *array; // Указатель на массив с приоритетами

int main()
{
    int element = 0, prio = 0, cont = 0;
    struct Queue *list = NULL;  // Указатель на начало очереди

    printf("\t# Priority Queue #\n");
    init:   // Метка на случай, если приоритет =< 0
    printf("Enter integer and priority(>0): ");
    scanf("%d%d", &element, &prio);
    if(prio > 0)
    {
        list = init(element, prio);   // Инициализация очереди
    }
    else
    {
        printf("priority must be more than 0\n");
        goto init;
    }

    printf("Continue(any integer) or not(0): ");
    scanf("%d", &cont);
    if(cont == 0) goto printing;

    while(cont != 0)
    {
        entering:   // Метка на случай, если приоритет =< 0
        printf("Enter integer and priority(>0): ");
        scanf("%d%d", &element, &prio);

        if(prio > 0)
        {
            Push(&list, element, prio);
        }
        else
        {
            printf("priority must be more than 0\n");
            goto entering;
        }

        printf("Continue(any integer) or not(0): ");
        scanf("%d", &cont);
        if(cont == 0) break;
    }

    // Вывод отсортированной очереди
    printf("+----------+----------+\n| elements | priority |\n+----------+----------+\n");
    while(list != NULL)
    {
        list = Pop(list);
        printf("|%9d |%9d |\n+----------+----------+\n", res, pr);
    }

    goto ret;

    printing:
    printf("+----------+----------+\n| element  | priority |\n+----------+----------+\n");
    Pop(list);
    printf("|%9d |%9d |\n+----------+----------+\n", res, pr);

    ret:
    return 0;
}


struct Queue
{
    int data;   // Числовой элемент очереди
    int priority;   // Приоритет очереди
    struct Queue *next; // Указатель на следующий элемент очереди
};

struct Queue *init(int element, int prio)
{
    struct Queue *p = NULL; // Создание указателя на структуру

    p = malloc(sizeof(struct Queue));   // Выделение памяти под структуру

    p -> data = element;    // Присваивание введённого значения полю данных
    p -> priority = prio;   // Присваивание введённого приоритета
    p -> next = NULL;   // Установка на нулевой указатель

    return p;
}

void Push(struct Queue **list ,int element, int prio)
{
    struct Queue *tmp = *list;  // Сохранение оригинального указателя на голову

    if(tmp != NULL) // Проверка на существование списка
    {
    struct Queue *new_element = init(element, prio);  // Создание нового элемента

    while(tmp -> next != NULL)
    {
        tmp = tmp -> next;
    }

    tmp -> next = new_element;
    }
    else if(tmp == NULL)    // Инициализация списка, если его нет
    {
        *list = init(element, prio);
    }
}

struct Queue *Priority(struct Queue *list)
{
    int n = 0, j = 0;
    int num = 1;
    struct Queue *tmp = list;

    // Узнаём количество элементов в списке
    while(tmp -> next != NULL)
    {
        num++;
        tmp = tmp -> next;
    }
    tmp = list;

    array = calloc(num, 4);  // Создаём массив приоритетов

    for(j = 0; j < num; j++)
    {
        array[j] = tmp -> priority; // Запись приоритетов в массив
        tmp = tmp -> next;
    }
    tmp = list;

    // Сортировка массива пузырьком (от большего к меньшему)
    if(num > 1)
    {
        for(j = 0; j < num - 1; j++)
        {
            for(int k = 0; k < num - 1; k++)
            {
                if(array[k] < array[k + 1])
                {
                    n = array[k];
                    array[k] = array[k + 1];
                    array[k + 1] = n;
                }
            }
        }
    }

    list = QueueSort(list, num);    // Получение указателя на отсортированный список

    return list;
}

struct Queue *QueueSort(struct Queue *list, int size)
{
    struct Queue *tmp = list, *pointer = NULL;
    int *arr = calloc(size, 4), i = 0;  // Создаём массив для элементов

    // Проходим по массиву и списку, сравнивая приоритеты
    for(i = 0; i < size; i++)
    {
        tmp = list;
        while(tmp != NULL)
        {
            if(tmp -> priority == array[i])
            {
                Push(&pointer, tmp -> data, array[i]);  // Запись элементов и приоритетов в новую очередь
                tmp -> priority = 0;    // Обнуление прочитанного приоритета
            }
            tmp = tmp -> next;
        }
    }

    // Освобождаем память
    free(arr);
    free(array);

    while(list != NULL)
    {
    struct Queue *to_delete = list;
    list = list -> next;
    free(to_delete);
    }

    return pointer;
}

struct Queue *Pop(struct Queue *list)
{
    list = Priority(list);
    res = list -> data; // Получение элемента очереди
    pr = list -> priority;  // Получение приоритета элемента очереди

    struct Queue *to_delete = list; // Переназначение указателя на первый элемент
    list = list -> next;    //Переназначение первого указателя на следующий
    free(to_delete);    // Очистка памяти по предыдущему указателю

    return list;    // Возвращение нового указателя на вершину очереди
}

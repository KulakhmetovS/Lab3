#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct Queue;   // Структура, отвечающая за элементы очереди
struct Queue *init(int, int);    // Инициализация очереди
void Push(struct Queue **, int, int);    // Добавление элемента в очередь
int Priority(struct Queue *);  // Сортировка элементов в соответствии с их приоритетом
struct Queue *Pop(struct Queue *);   // Чтение элемента из очереди с последующим удалением

int res = 0;    // Результат извлеения из очереди
int *array;


int main()
{
    int a = 10;

    // Третьим параметром Push() введите приоритет элемента
    struct Queue *list = init(a, 11);   // Инициализация очереди
    Push(&list, 5, 3); // Добавление значения в очередь
    Push(&list, 8, 1);
    Push(&list, 6, 3);
    Push(&list, 8, 11);
    list = Pop(list);   // Получение значения и нового указателя череди
    printf("%d\n", res);
    list = Pop(list);
    printf("%d\n", res);
    list = Pop(list);
    printf("%d\n", res);
    list = Pop(list);
    printf("%d\n", res);
    list = Pop(list);
    printf("%d\n", res);

    Push(&list, 24, 9);
    Push(&list, 18, 11);
        list = Pop(list);
    printf("%d\n", res);
    list = Pop(list);
    printf("%d\n", res);


    return 0;
}


struct Queue
{
    int data;   // Числовой элемент очереди
    int priority;   // Приоритет элемента
    struct Queue *next; // Указатель на следующий элемент очереди
};

struct Queue *init(int element, int prt)
{
    struct Queue *p = NULL; // Создание указателя на структуру

    if((p = malloc(sizeof(struct Queue))) == NULL)  // Выделение памяти под структуру
    {
        printf("Unable to allocate memory: ");
        exit(1);
    }

    p -> data = element;    // Присваивание введённого значения полю данных
    p -> priority = prt;
    p -> next = NULL;   // Установка на нулевой указатель

    return p;
}

void Push(struct Queue **list ,int element, int prt)
{
    struct Queue *tmp = *list;  // Сохранение оригинального указателя на голову

    if(tmp != NULL) // Проверка на существование списка
    {
    struct Queue *new_element = init(element, prt);  // Создание нового элемента

    while(tmp -> next != NULL)
    {
        tmp = tmp -> next;
    }

    tmp -> next = new_element;
    }
    else if(tmp == NULL)    // Инициализация списка, если его нет
    {
        *list = init(element, prt);
    }
}

int Priority(struct Queue *list)
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

    array = calloc(num, 4);  // Создаём массив

    for(j = 0; j < num; j++)
    {
        array[j] = tmp -> priority; // Запись в массив приоритетов
        tmp = tmp -> next;
    }
    tmp = list;

    // Сортировка массива пузырьком (от большего к меньшиму)

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

    /*for(j = 0; j < num; j++)
    printf("%d ", array[j]);*/

    return num;
}

struct Queue *Pop(struct Queue *list)
{
    int i = Priority(list);
    struct Queue *head = list, *prev;

    if(head -> priority == array[0])    // Если элемент первый
    {
        res = head -> data;
        list = head -> next;    //Переназначение первого указателя на следующий
        free(head);
        head = list;
        return list;
    }
    else
    {
        prev = list;    // Указатель на предыдущий элемент
        head = list -> next;    // Указатель на следующий элемент
    }

    for(int j = 0; j < i; j++) // Если элемент в середине
    {
        if(head -> priority == array[0])
        {
            res = head -> data;
            if(head -> next != NULL)
            {
                prev -> next = head -> next;
                free(head);
                head = prev -> next;
                return list;
            }
            else    // Если элементв конце
            {
                prev -> next = NULL;
                free(head);
                return list;
            }
        }
        else
        {
            prev = head -> next;
            head = prev -> next;
        }
    }

    return list;
}

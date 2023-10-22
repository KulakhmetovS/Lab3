#include <stdio.h>
#include <stdlib.h>

struct Queue;   // Структура, отвечающая за элементы очереди
struct Queue *init(int, int);    // Инициализация очереди
void Push(struct Queue **, int, int);    // Добавление элемента в очередь
struct Queue *Priority(struct Queue *);  // Сортировка элементов в соответствии с их приоритетом
struct Queue *QueueSort(struct Queue *, int);   //Создание отсортированной очереди
struct Queue *Pop(struct Queue *);   // Чтение элемента из очереди
struct Queue *DeleteElement(struct Queue *, int, int);  // Удаление элемента
void DeleteQueue(struct Queue *);   // Удаление всей очереди

int res = 0;    // Результат извлечения из очереди
int pr = 0; // Результат извлечения приоритета
int array[1000]; // Указатель на массив с приоритетами


int main()
{
    float operation = 0;
    struct Queue *list = NULL, *sortq = NULL;
    int element = 0, priority = 0;

    printf(" # Priority Queue #\n\n\tMenu\n");
    printf(" 1 - add new element\n 2 - see list\n 3 - delete element\n 4 - delete queue\n 0 - quit\n");

    while(1)
    {
        label:
        printf("Choose operation: ");
        scanf("%f", &operation);
        if((operation > 4) || (operation < 0))
        {
            printf("Invalid operation! Try again\n");
            goto label;
        }
        else if(operation == 0) // Окончание программы
        {
            break;
        }
        else if(operation == 1) // Ввод элементов в приоритетную очередь
        {
            entering:
            printf("Enter element(any integer) and priority(>0): ");
            scanf("%d%d", &element, &priority);
            if(priority <= 0)
            {
                printf("priority must be more than 0!\n");
                goto entering;
            }
            Push(&list, element, priority);
        }
        else if(operation == 2) // Вывод всей очереди
        {
            if(list == NULL)
            {
                printf("list is empty\n");
                goto label;
            }
            list = Priority(list);
            sortq = list;
            printf("+----------+----------+\n| elements | priority |\n+----------+----------+\n");
            while(list != NULL)
            {
                list = Pop(list);
                printf("|%9d |%9d |\n+----------+----------+\n", res, pr);
            }
            list = sortq;
        }
        else if(operation == 3) // Удвление элемента очереди
        {
            printf("Enter element and priority you need to delete: ");
            scanf("%d%d", &element, &priority);
            list = DeleteElement(list, element, priority);
        }
        else if(operation == 4) // Удвление всей очереди
        {
            list = Priority(list);
            DeleteQueue(list);
            list = NULL;
        }
        else
        {
            printf("Invalid operation\n");
            goto label;
        }
    }


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

    //array = calloc(num, 4);  // Создаём массив приоритетов

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
    int i = 0;  // Создаём массив для элементов

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
    //free(arr);
    //free(array);

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
    res = list -> data; // Получение элемента очереди
    pr = list -> priority;  // Получение приоритета элемента очереди

    //struct Queue *to_delete = sortq; // Переназначение указателя на первый элемент
    list = list -> next;    //Переназначение первого указателя на следующий
    //free(to_delete);    // Очистка памяти по предыдущему указателю

    return list;    // Возвращение нового указателя на вершину очереди
}

struct Queue *DeleteElement(struct Queue *list, int element, int prio)
{
    if(list == NULL)
    {
        printf("List is empty");
        return list;
    }

    struct Queue *tmp = list, *head = NULL, *prev = NULL;
    int flag = 0;

    if((tmp -> data == element) && (tmp -> priority == prio))
    {
        head = tmp;
        tmp = tmp -> next;
        free(head);
        list = tmp;
        flag = 1;
    }
    else
    {
        prev = tmp;
        head = tmp -> next;
    }

    while(head != NULL)
    {
        if((head -> data == element) && (head -> priority == prio))
        {
            if(head -> next != NULL)
            {
                prev -> next = head -> next;
                free(head);
                head = prev -> next;
                flag = 1;
            }
            else
            {
                prev -> next = NULL;
                free(head);
                flag = 1;
            }
        }
        else
        {
            prev = head;
            head = head -> next;
        }
    }

    if(flag == 0)
    {
        printf("Element not found!\n");
    }

    return list;
}

void DeleteQueue(struct Queue *list)
{
    struct Queue *to_delete = NULL;
    while(list != NULL)
    {
        to_delete = list; // Переназначение указателя на первый элемент
        list = list -> next;    //Переназначение первого указателя на следующий
        free(to_delete);    // Очистка памяти по предыдущему указателю
    }
    printf("list deleted\n");
}

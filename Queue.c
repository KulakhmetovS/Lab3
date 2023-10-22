#include <stdio.h>
#include <stdlib.h>

struct Queue;   // Структура, отвечающая за элементы очереди
struct Queue *init(int);    // Инициализация очереди
void Push(struct Queue **, int);    // Добавление элемента в очередь
struct Queue *Pop(struct Queue *);   // Чтение элемента из очереди
struct Queue *DeleteElement(struct Queue *, int);  // Удаление элемента
void DeleteQueue(struct Queue *);   // Удаление всей очереди



int res = 0;    // Результат извлеения из очереди

int main()
{
    int elem = 0;
    float operation = 0;
    struct Queue *list = NULL, *queue = NULL;

    printf(" # Queue #\n\n\tMenu\n");
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
            printf("Enter element(any integer): ");
            scanf("%d", &elem);
            Push(&list, elem);
        }
        else if(operation == 2) // Вывод всей очереди
        {
            if(list == NULL)
            {
                printf("list is empty\n");
                goto label;
            }
            queue = list;
            printf("+----------+\n| elements |\n+----------+\n");
            while(list != NULL)
            {
                list = Pop(list);
                printf("|%9d |\n+----------+\n", res);
            }
            list = queue;
        }
        else if(operation == 3) // Удвление элемента очереди
        {
            printf("Enter element you need to delete: ");
            scanf("%d", &elem);
            list = DeleteElement(list, elem);
        }
        else if(operation == 4) // Удвление всей очереди
        {
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

    list = list -> next;    //Переназначение первого указателя на следующий

    return list;    // Возвращение нового указателя на вершину очереди
}

struct Queue *DeleteElement(struct Queue *list, int elem)
{
if(list == NULL)
    {
        printf("List is empty");
        return list;
    }

    struct Queue *tmp = list, *head = NULL, *prev = NULL;
    int flag = 0;

    if(tmp -> data == elem)
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
        if(head -> data == elem)
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

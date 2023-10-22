#include <stdio.h>
#include <stdlib.h>


struct Stack;   // Структура, отвечающая за элементы очереди
struct Stack *init(int);    // Инициализация очереди
void Push(struct Stack **, int);    // Добавление элемента в очередь
//int Pop(struct Stack *);   // Чтение элемента из очереди с последующим удалением
void Printing(struct Stack *);
struct Stack *DeleteElement(struct Stack *, int);  // Удаление элемента
void DeleteStack(struct Stack *);   // Удаление всей очереди


int main()
{
    int element = 0;
    struct Stack *list = NULL, *pointer = NULL;
    float operation = 0;

    printf(" # Stack #\n\n\tMenu\n");
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
            scanf("%d", &element);
            Push(&list, element);
        }
        else if(operation == 2) // Вывод всей очереди
        {
            if(list == NULL)
            {
                printf("list is empty\n");
                goto label;
            }
            pointer = list;
            Printing(list);
            list = pointer;
        }
        else if(operation == 3) // Удвление элемента очереди
        {
            printf("Enter element you need to delete: ");
            scanf("%d", &element);
            list = DeleteElement(list, element);
        }
        else if(operation == 4) // Удвление всей очереди
        {
            DeleteStack(list);
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
    struct Stack *tmp = *list;  // Сохранение оригинального указателя на голову

    if(tmp != NULL)
    {
    struct Stack *new_element = init(element);  // Создание нового элемента

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

void Printing(struct Stack *list)
{
    int i = 0, j;   // Переменные счётчики числа элементов стека
    struct Stack *tmp = list;   // Сохранение указателя на вершину стека

    while(tmp != NULL) // Обход списка
    {
        tmp = tmp -> next;
        i++;
    }
    i--;

    tmp = list;
    printf("+----------+\n| elements |\n+----------+\n");
    while(i >= 0)
    {
        for(j = 0; j < i; j++)
        {
            tmp = tmp -> next;
        }
        printf("|%9d |\n+----------+\n", tmp -> data);
        tmp = list;
        i--;
    }
}

void DeleteStack(struct Stack *list)
{
    struct Stack *to_delete = NULL;
    while(list != NULL)
    {
        to_delete = list; // Переназначение указателя на первый элемент
        list = list -> next;    //Переназначение первого указателя на следующий
        free(to_delete);    // Очистка памяти по предыдущему указателю
    }
    printf("list deleted\n");
}

struct Stack *DeleteElement(struct Stack *list, int elem)
{
if(list == NULL)
    {
        printf("List is empty");
        return list;
    }

    struct Stack *tmp = list, *head = NULL, *prev = NULL;
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

#include <stdio.h>
#include <stdlib.h>


struct Stack;   // Структура, отвечающая за элементы очереди
struct Stack *init(int);    // Инициализация очереди
void Push(struct Stack **, int);    // Добавление элемента в очередь
int Pop(struct Stack *);   // Чтение элемента из очереди с последующим удалением


int main()
{
    int result = 0, elem = 0, cont = 0, size = 0;

    printf("\t# Stack #\n");
    printf("Enter element: ");
    scanf("%d", &elem);
    struct Stack *list = init(elem);   // Инициализация очереди
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
        size++;
    }

    printf("+----------+\n| elements |\n+----------+\n");
    for(int i = 0; i <= size; i++)
    {
        result = Pop(list);
        printf("|%9d |\n+----------+\n", result);
    }

    goto ret;

    printing:
    result = Pop(list);
    printf("+----------+\n|  element |\n+----------+\n");
    printf("|%9d |\n+----------+\n", result);

    ret:
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

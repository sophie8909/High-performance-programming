#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



struct node
{
    int index;
    double max;
    double min;
    struct node *next;
} typedef node;

node *createNode(int index, double max, double min)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->index = index;
    newNode->max = max;
    newNode->min = min;
    newNode->next = NULL;
    return newNode;
}


void update(node *head, int index, double max, double min)
{
    node *temp = head;
    while (temp->next != NULL)
    {
        // If the index is already in the list, update the max and min values
        if (temp->next->index == index)
        {
            temp->next->max = max;
            temp->next->min = min;
            return;
        }
        // If the index is not in the list, add it to the list and keep the list sorted
        else if (temp->next->index > index)
        {
            node *newNode = createNode(index, max, min);
            newNode->next = temp->next;
            temp->next = newNode;
            return;
        }
        temp = temp->next;
    }
    // If the list is empty or node is the last, add the first node
    node *newNode = createNode(index, max, min);
    newNode->next = NULL;
    temp->next = newNode;

}

void delete(node *head, int index)
{
    node *temp = head;
    while (temp->next != NULL)
    {
        if (temp->next->index == index)
        {
            node *temp2 = temp->next;
            temp->next = temp->next->next;
            free(temp2);
            return;
        }
        temp = temp->next;
    }
}

void print(node *head)
{
    node *temp = head;
    printf("day\tmin\tmax\n");
    while (temp->next != NULL)
    {
        printf("%d\t%f\t%f\n", temp->next->index, temp->next->max, temp->next->min);
        temp = temp->next;
    }
}

void freeList(node *head)
{
    node *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main()
{
    char op;
    bool isStop = false;
    node *head = createNode(0, -1, -1);
    int index;
    double max, min;
    while(isStop == false)
    {
        printf("Enter command: ");
        scanf(" %c", &op);
        switch (op)
        {
            case 'A':
                scanf("%d %lf %lf", &index, &max, &min);
                update(head, index, max, min);
                break;
            case 'D':
                scanf("%d", &index);
                delete(head, index);
                break;
            case 'P':
                print(head);
                break;
            case 'Q':
                isStop = true;
                break;
            default:
                printf("Invalid input\n");
                break;
        }
    }
    freeList(head);
    return 0;
}
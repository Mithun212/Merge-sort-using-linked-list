#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Link list node */
struct Node {
    int data;
    struct Node* next;
};

/* function declaration */
struct Node* SortedMerge(struct Node* a, struct Node* b);
void FrontBackSplit(struct Node* source,
                    struct Node** frontRef, struct Node** backRef);
void MergeSort(struct Node** headRef);

/*  function to check if a number contains the digit '3' */
bool hasDigitThree(int num) {
    if (num == 0) return false;
    while (num != 0) {
        if (abs(num % 10) == 3) return true;
        num /= 10;
    }
    return false;
}

/* function to free a node */
void freeNode(struct Node* node) {
    free(node);
}

void MergeSort(struct Node** headRef)
{
    struct Node* head = *headRef;
    struct Node* a;
    struct Node* b;

    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }

    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);

    /* Recursively sort the sublists */
    MergeSort(&a);
    MergeSort(&b);

    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b);
}

/* Merge two sorted linked lists and eliminate numbers containing '3' */
struct Node* SortedMerge(struct Node* a, struct Node* b)
{
    struct Node dummy;
    struct Node* tail = &dummy;
    dummy.next = NULL;

    while (a != NULL && b != NULL) {
        if (hasDigitThree(a->data)) {
            struct Node* temp = a;
            a = a->next;
            freeNode(temp);
            temp = NULL;
            continue;
        }
        if (hasDigitThree(b->data)) {
            struct Node* temp = b;
            b = b->next;
            freeNode(temp);
            temp = NULL;
            continue;
        }
        if (a->data <= b->data) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }

    /* Append the remaining nodes of 'a' or 'b' */
    while (a != NULL) {
        if (hasDigitThree(a->data)) {
            struct Node* temp = a;
            a = a->next;
            freeNode(temp);
            temp = NULL;
        } else {
            tail->next = a;
            tail = tail->next;
            a = a->next;
        }
    }
    while (b != NULL) {
        if (hasDigitThree(b->data)) {
            struct Node* temp = b;
            b = b->next;
            freeNode(temp);
            temp = NULL;
        } else {
            tail->next = b;
            tail = tail->next;
            b = b->next;
        }
    }

    return dummy.next;
}

void FrontBackSplit(struct Node* source,
                    struct Node** frontRef, struct Node** backRef)
{
    struct Node* fast;
    struct Node* slow;
    slow = source;
    fast = source->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

void printList(struct Node* node)
{
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
}

void push(struct Node** head, int new_data)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = *head;
    *head = new_node;
    new_node = NULL;
}

int main()
{
    struct Node* a = NULL;

    push(&a, 15);
    push(&a, 10);
    push(&a, 5);
    push(&a, 20);
    push(&a, 3);
    push(&a, 2);
    push(&a, 13);
    push(&a, 32);


    MergeSort(&a);

    printf("Sorted Linked List is: \n");
    printList(a);

    getchar();
    return 0;
}


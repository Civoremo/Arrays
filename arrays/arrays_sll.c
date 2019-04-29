#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct node {
  int val;
  struct node *next;
} node_t;

void list_append(node_t *head, int val) {
  node_t *current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = malloc(sizeof(node_t));
  current->next->val = val;
  current->next->next = NULL;
}

// Create a new item and set its value
// Link the new item to point to the head of the list
// Set the head of the list to be our new item
void list_prepend(node_t **head, int val) {
  node_t *new_node;
  new_node = malloc(sizeof(node_t));

  new_node->val = val;
  new_node->next = *head;
  *head = new_node;
}

int pop_end(node_t *head) {
  int retval = 0;
  if (head->next == NULL) {
    retval = head->val;
    free(head);
    return retval;
  }

  node_t *current = head;
  while (current->next->next != NULL) {
    current = current->next;
  }

  retval = current->next->val;
  free(current->next);
  current->next = NULL;
  return retval;
}

// Take the next item that the head points to and save it
// Free the head item
// Set the head to be the next item that we've stored on the side
int pop_first(node_t **head) {
  int retval = -1;
  node_t *next_node = NULL;

  if (*head == NULL) {
    return -1;
  }

  next_node = (*head)->next;
  retval = (*head)->val;
  free(*head);
  *head = next_node;

  return retval;
}


// Iterate to the node before the node we wish to delete
// Save the node we wish to delete in a temporary pointer
// Set the previous node's next pointer to point to the node after the node we wish to delete
// Delete the node using the temporary pointer
int pop_atVal(node_t **head, int n) {
  int i = 0;
  int retval = -1;
  node_t *current = *head;
  node_t *temp_node = NULL;

  if (n == 0) {
    return pop_first(head);
  }

  for (i = 0; i < n-1; i++) {
    if (current->next == NULL) {
      return -1;
    }
    current = current->next;
  }

  temp_node = current->next;
  retval = temp_node->val;
  current->next = temp_node->next;
  free(temp_node);
}

void print_list(node_t *head) {
  node_t *current = head;

  while (current != NULL) {
    printf("%d\n", current->val);
    current = current->next;
  }
}

int main(void) {
  node_t  *head = NULL;
  head = malloc(sizeof(node_t));
  if(head == NULL) {
    return 1;
  }

  head->val = 1;
  head->next = NULL;

  list_append(head, 3);
  list_append(head, 5);
  list_append(head, 2);
  list_append(head, 7);
  printf("Adding items to end of list\n");
  print_list(head);

  list_prepend(&head, 9);
  list_prepend(&head, 9);
  list_prepend(&head, 11);
  printf("Adding item to beginning of list\n");
  print_list(head);

  int temp = pop_end(head);
  printf("Popped at end value: %d\n", temp);
  temp = pop_first(&head);
  printf("Popped at beginning value: %d\n", temp);
  temp = pop_atVal(&head, 2);
  printf("Popped at index value: %d\n", temp);

  printf("Final list after above adjustments\n");
  print_list(head);

  return 0;
}

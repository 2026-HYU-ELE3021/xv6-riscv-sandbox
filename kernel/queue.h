#ifndef _QUEUE_H_
#define _QUEUE_H_

#define MAX_QUEUE_SIZE 512

// Queue

struct queue {
  struct spinlock lock;

  int head;
  int tail;

  void *data[MAX_QUEUE_SIZE + 1];
};

#endif
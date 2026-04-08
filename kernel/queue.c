#include "types.h"
#include "riscv.h"
#include "spinlock.h"
#include "queue.h"
#include "defs.h"

int _queue_size_without_lock(struct queue *q) {
  return (q->tail - q->head + 1 + (MAX_QUEUE_SIZE + 1)) % (MAX_QUEUE_SIZE + 1);
}

void queue_init(struct queue *q) {
  initlock(&q->lock, "queue");
  acquire(&q->lock);
  q->head = 0;
  q->tail = -1;
  release(&q->lock);
}

int queue_push(struct queue *q, void *entry) {
  acquire(&q->lock);
  if (_queue_size_without_lock(q) >= MAX_QUEUE_SIZE) {
    release(&q->lock);
    return -1;
  }

  q->tail = (q->tail + 1) % (MAX_QUEUE_SIZE + 1);
  q->data[q->tail] = entry;
  release(&q->lock);
  return 0;
}

void *queue_peek(struct queue *q) {
  acquire(&q->lock);
  if (_queue_size_without_lock(q) <= 0) {
    release(&q->lock);
    return 0;
  }

  void *result = q->data[q->head];
  release(&q->lock);
  return result;
}

void *queue_pop(struct queue * q) {
  acquire(&q->lock);
  if (_queue_size_without_lock(q) <= 0) {
    release(&q->lock);
    return 0;
  }

  void *result = q->data[q->head];
  q->head = (q->head + 1) % (MAX_QUEUE_SIZE + 1);
  release(&q->lock);
  return result;
}

int queue_size(struct queue *q) {
  acquire(&q->lock);
  int result = _queue_size_without_lock(q);
  release(&q->lock);

  return result;
}

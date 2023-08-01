#include <defs.h>
#include <sem.h>
#include <stdio.h>

SEMAPHORE_INIT(my_semaphore, 0); // init a semaphore lock with a default counter value. In this case
				 // the value is zero it means, at most 1 tasklet or thread can aquire the semaphore at any time

int factorial_result = 0;

int factorial10() { // simple sequential factorial computation
  int i = 10, f = 1;
  for (; i > 0; i--) {
    f = i * f;
  }
  return f;
}

int producer() {
  factorial_result = factorial10(); // compute the factorial
  sem_give(&my_semaphore); // try to release the semaphore
  sem_give(&my_semaphore);

  int result_producer = (me() << 24) | factorial_result; // some wiered operation?
  return result_producer;
}

int consumer() {
  sem_take(&my_semaphore); // try to take semaphore

  int result_consumer = (me() << 24) | factorial_result;
  return result_consumer;
}

int (*tasks[])(void) = {consumer, producer, consumer};
int main() { return tasks[me()](); }

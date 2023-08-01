#include <stdio.h>
#include <defs.h>
#include <mutex.h>


#define UNDEFINED_VAL (-1)
int shared_variable = UNDEFINED_VAL; 

MUTEX_INIT(my_mutex); // macro for initializing a mutex lock for tasklets
		      // this mutex is defined in gloabal scope, therefore it is shared among all the DPUs tasklets

int main(){
	mutex_lock(my_mutex);

	if (shared_variable == UNDEFINED_VAL){
		shared_variable = 1 << me(); 
	}

	mutex_unlock(my_mutex);


	return shared_variable;
}

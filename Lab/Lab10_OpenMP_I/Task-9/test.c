#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int main()
{

    omp_set_nested(0);
#pragma omp parallel num_threads(2)
    {
        int id_p = omp_get_thread_num();
        #pragma omp parallel num_threads(2)
        {
            int id = omp_get_thread_num();
            printf("thread %d from parent thread %d\n", id, id_p);
        }
    }


    return 0;
}
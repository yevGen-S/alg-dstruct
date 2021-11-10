
#include <stdio.h>
#include <stdlib.h>
#include "bfs.h"
/*
 *

 *
 * Processor: AMD Ryzen 5 3500U with Radeon Vega Mobile Gfx   (8 CPUs), ~2.1GHz
                   Memory: 8192MB RAM
      Available OS Memory: 6092MB RAM



Stress test:
 Number of vertices: 50000
 Memory used: 4 GB
 Execution time: 28.334860 s


 */



int main(){
    FILE* file = fopen("dataset_for_bfs_test.txt","w+");
    if (file == NULL){
        fprintf(stderr,"%s","Error of opening file");
        exit(ERROR_FILE_OPENING);
    }

    StressTest(file);

    return 0;
}

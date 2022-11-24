#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<limits.h>  
#include<time.h>
#include<sched.h>
struct sched_param param1;
struct sched_param param2;
struct sched_param param3;

//creating threads

void *A(){ 
    struct timespec start,end;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&start);
    int i;
    for(i= 0; i<ULONG_MAX;i++); 
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&end);
    long time = (end.tv_nsec - start.tv_nsec)*1e9;
    time = (end.tv_sec - start.tv_sec)+ time;
    return (void *)time;
}
void *B(){
    struct timespec start,end;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&start);
    int i;
    for(i= 0; i<ULONG_MAX;i++); 
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&end);
    long time = (end.tv_nsec - start.tv_nsec)*1e9;
    time = (end.tv_sec - start.tv_sec)+ time;
    return (void *)time;
}
void *C(){
    struct timespec start,end;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&start);
    int i;
    for(i= 0; i<ULONG_MAX;i++); 
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&end);
    long time = (end.tv_nsec - start.tv_nsec)*1e9;
    time = (end.tv_sec - start.tv_sec)+ time;
    return (void *)time;
}
//now creating the main function

int main (void){
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    int id1=1;
    int id2=2;
    int id3=3;

    void *result1;
    void *result2;
    void *result3;

    pthread_create(&thread1,NULL,A,(void *)&id1);
    pthread_create(&thread2,NULL,B,(void *)&id2);
    pthread_create(&thread3,NULL,C,(void *)&id3);
    param1.sched_priority = 0;
    param2.sched_priority = 50;
    param3.sched_priority = 50;
    pthread_setschedparam(thread1,SCHED_FIFO,&param1);
    pthread_setschedparam(thread2,SCHED_FIFO,&param2);
    pthread_setschedparam(thread3,SCHED_FIFO,&param3);
    pthread_join(thread1,&result1);
    pthread_join(thread2,&result2);
    pthread_join(thread3,&result3);
    FILE *fp;
    fp = fopen("thread.txt","w");
    fprintf(fp,"%ld,%ld,%ld",(long) result1/1000,(long)result2/1000,(long)result3/1000);
    fclose(fp);
    printf("%ld,%ld,%ld",(long) result1/1000,(long)result2/1000,(long)result3/1000);   
}
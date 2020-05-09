#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h>
#include <stdlib.h>

//declaring semaphores 
sem_t male;
sem_t female; 
sem_t fcount_sem; 
sem_t mcount_sem; 
sem_t Bathroom ; 
sem_t antiStarv; // a semaphore to avoid starvation 
//initializing counters for both male and female
int femaleCount= 0;
int maleCount= 0;
int users=0; 
int n_male; 
int m_female;

//function for women entering the bathrrom 
void woman_wants_to_enter()
{
//to avoid starvation 
sem_wait(&antiStarv);
sem_wait(&female);
if(femaleCount==0)
sem_wait(&Bathroom);
femaleCount++;
//users++;
sem_post(&female);
sem_post(&antiStarv);
sem_wait(&fcount_sem);
printf("A female enters. (Female count:");
printf("%d",femaleCount);
printf(") \n");
//return NULL;
}

void woman_leaves()
{
sem_post(&fcount_sem);
sem_wait(&female);
//users--;
femaleCount --;
printf("A female leaves. (Females count: ");
printf("%d",femaleCount);
printf(")\n");
if(femaleCount==0)
sem_post(&Bathroom);
sem_post(&female);

//return NULL;
}

//function for men entering the bathrrom 
void man_wants_to_enter()
{
//to avoid starvation 
sem_wait(&antiStarv);
sem_wait(&male);
if(maleCount==0)
sem_wait(&Bathroom);
maleCount++;
//users++;
sem_post(&male);
sem_post(&antiStarv);
sem_wait(&mcount_sem);
printf("A male enters.(Males count: ");
printf("%d",maleCount);
printf(")\n");
//return NULL;
}

void man_leaves()
{
sem_post(&mcount_sem);
sem_wait(&male); 
maleCount --;
users--;
printf("A male leaves. (Males count: ");
printf("%d",maleCount);
printf(")\n");
if(maleCount==0)
sem_post(&Bathroom);
sem_post(&male);

//return NULL;
}

//female thread 
void* female_thread(void* arg)
{
for(int i=0; i<100; i++)
{
woman_wants_to_enter();
usleep(200);
woman_leaves();
}
return NULL;
}

//male thread 
void* male_thread(void* arg)
{
for(int i=0; i<100; i++)
{
man_wants_to_enter();
usleep(400);
man_leaves();
}

return NULL;
}


int main(int argc, char *argv[]) {
sem_init(& female,0,1);
sem_init(& male,0,1);
sem_init(& mcount_sem,0,5);
sem_init(& fcount_sem,0,5);
sem_init(& Bathroom,0,1);
sem_init(& antiStarv,0,1);
//static number of women/men
/*n_male= 12;
m_female= 20; 
pthread_t women[20]; 
pthread_t men[12];*/
//dynamically entering number of men/women 
n_male= atoi(argv[1]); //taking the number of men who visit the Bathroom
m_female= atoi(argv[2]); //number of women
pthread_t *women; 
pthread_t *men;
men=(pthread_t*)malloc(sizeof(pthread_t)*n_male);
women=(pthread_t*)malloc(sizeof(pthread_t)*m_female);
int iterator; 
if(n_male>m_female)
iterator=n_male;

else 
iterator=m_female; 

for(int i=0; i< iterator;i++ )
{
if(i<m_female)
{
pthread_create(&women[i],NULL,female_thread,NULL);
}

if(i<n_male)
{
pthread_create(&men[i],NULL,male_thread,NULL);
}
}
for(int i=0; i< m_female;i++)
{ 
pthread_join(women[i],NULL);
}
for(int i=0; i< n_male;i++)
{ 
pthread_join(men[i],NULL) ; 
}

sem_destroy(& female);
sem_destroy(& male);
sem_destroy(& mcount_sem);
sem_destroy(& fcount_sem);
sem_destroy(& antiStarv); 
sem_destroy(& Bathroom);
free(men);
free(women);
return 0;
} 


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define CNT 10

 

int buffer =CNT;

sem_t freePos;
sem_t busyPos;
pthread_mutex_t mux;

 typedef enum Product{
Water = 0,
Cola = 1,
Nuts = 2,
Bread = 3,
Patato = 4,
Chips = 5,
Tomatoes = 6,
Cucember = 7,
Greens = 8,
Onion = 9
}Product;

typedef struct sklad
{
    int barkod;
    Product product;
    double price;

}sklad;

typedef struct noded {
    sklad data;
    struct noded* prev;
    struct noded* next;
} node_dll;

node_dll* head = NULL;

void push(node_dll** head, sklad data){
    node_dll* node = malloc(sizeof(node_dll));
    node->data = data;
    node->next = *head;
    node->prev = NULL;
    if (*head != NULL){
        (*head)->prev = node;
    }
    *head = node;
}

void print_elements(node_dll* head){
    node_dll* current = head;
    while (current != NULL){
        printf("%d\n", current->data.product);
        current = current->next;
    }
    putchar('\n');

}


void* getNth(node_dll* head, Product value){
    node_dll* current = head;
    Product prod = current->data.product;
    int counter = 0;
    while (current != NULL){
        if (prod = value){
           return current;
        }
        counter++;
        current= current->next;
        prod=current->data.product;
    }
   
}


void deleteNth(node_dll** head, Product value){
    if (*head == NULL){
        return;
    }

    node_dll* temp = *head;
    Product prod = temp->data.product;
    if (value == prod){
         temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }
  
    node_dll* prev = temp;
    while (temp != NULL && prod != value) {
        prev = temp;
        temp = temp->next;
    }
    prev->next = temp->next;
    free(temp);
}




Product getProduct(int);

int getBarkod();

double getPrice();

void createProduct(node_dll** head,int num){
    
 sklad el ;
    el.product = getProduct(num);
    el.barkod = getBarkod();
    el.price = getPrice();
   push(&head,el);
}

void* producer(void* args){
   
    while (1){
        int x = rand() % 10+0;
        sleep(1);
        sem_wait(&freePos);
        pthread_mutex_lock(&mux);
        if (buffer < CNT)
        {
            createProduct(&head,x);
         buffer++;
        }
        pthread_mutex_unlock(&mux);
        sem_post(&busyPos);
    }
}

void* consumer(void* args){
    while(1){
        Product x = rand() % 10+0;
        sleep(1);
        sem_wait(&busyPos);
        pthread_mutex_lock(&mux);
        if (buffer > 0)
        {
            deleteNth(&head,x);
            buffer --;
        }
        pthread_mutex_unlock(&mux);
        sem_post(&freePos);
        printf("Thread: %ld Consumed: %d\n", pthread_self(), x);
    }
}

int main(int argc,char* argv[]){
   
    Product prod ;
    char name[100];
    int producers;
    int consumers;
     srand(time(NULL));
     sem_init(&freePos, 0, buffer);
    sem_init(&busyPos, 0, 0);
    pthread_mutex_init(&mux, NULL);
    
    if (argc < 2)
    {
       producers = 5;
       consumers = 6;
    }else{
        producers = atoi(argv[1]);
        consumers = atoi(argv[2]);
    }
    
   pthread_t thp[producers];
    pthread_t thc[consumers];

       for (int i = 0; i < producers; i++){
        if(pthread_create(&thp[i], NULL,producer, NULL) != 0){
            perror("create thread:");
            return EXIT_FAILURE;
        }

        for (int i = 0; i < consumers; i++){
        if(pthread_create(&thc[i], NULL,consumer, NULL) != 0){
            perror("create thread:");
            return EXIT_FAILURE;
        }
    }
     

     for (int i = 0; i < producers; i++){
        if(pthread_join(thp[i], NULL) != 0){
            perror("join thread:");
            return EXIT_FAILURE;
        }

    for (int i = 0; i < consumers; i++){
        if(pthread_join(thc[i], NULL) != 0){
            perror("join thread:");
            return EXIT_FAILURE;
        }

}


Product getProduct(int val){
    Product pr = val;
    return pr;
}

int getBarkod(){
int num = rand()%100+1;
return num;
}

double getPrice(){
    double price[]={10.0,2.5,7.86,9.0,13.8,12.99,3.50,4.0,9.75,11};
    double price1 = price[rand()%10+0];
    return price1;
}
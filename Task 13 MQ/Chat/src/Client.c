#include "Client.h"
#define QUEUE_RD_SERVER "/queuerds11"
#define QUEUE_WR_SERVER "/queuewrs11"
extern WINDOW *massage_win;
char chat_buf[100];
char massage_buf[100];
char user_buf[50];
char tmp_buf[100];
int counter_user = 0, counter_chat = 0;
mqd_t mqdes_rds, mqdes_wrs;
int exits = 0;

int main(){
    int tmp, text_counter = 0; 
    char name[50];
    int status;
    pthread_t thread;
    printf("Введите ваше имя для присоединения к чату(Макс 50 сим): ");
    fgets(name, 50, stdin);
 
    mqdes_rds = mq_open(QUEUE_RD_SERVER, O_RDWR);
    mqdes_wrs = mq_open(QUEUE_WR_SERVER, O_RDWR);
    if(mqdes_rds == -1 || mqdes_wrs == -1){
        printf("ERR open\n");
        return 1;
    } 

    init_graf();
    
    strcat(massage_buf, "3 connected ");
    strcat(massage_buf, name);

    pthread_create(&thread, NULL, thread_chat, NULL);
    if(mq_send(mqdes_rds, massage_buf, 30, 10) == -1){
        printf("ERR send\n");
        return 1;
    }

    while(exits != 1){
        tmp = getch();

        switch(tmp){
            case 10:
                if(massage_buf[0] == '/'){
                    if(massage_buf[1] == 'q')
                        exits = 1;
                }
                else{
                    strcat(tmp_buf, "5 ");
                    strcat(tmp_buf, name);
                    tmp_buf[strlen(tmp_buf) - 1] = '\000';
                    strcat(tmp_buf, ": ");
                    strcat(tmp_buf, massage_buf);
                    if(mq_send(mqdes_rds, tmp_buf, 30, 10) == -1){
                        printf("ERR send\n");
                        return 1;
                    }
                    tmp_buf[0] = '\000';
                    massage_buf[0] = '\000';
                    text_counter = 0;
                }
                break;
            case 127:
                if(text_counter > 0){
                    text_counter -= 1;
                    massage_buf[text_counter] = '\000';
                } 
                else{
                    massage_buf[0] = '\000';
                    text_counter = 0;
                }
                break;
            default:
                if(tmp > 39 && tmp < 127 && tmp != 91){
                    massage_buf[text_counter] = tmp;
                    text_counter++;
                    massage_buf[text_counter] = '\000';
                    wrefresh(massage_win);
                }
        }
        refmas();

    }
    
    massage_buf[0] = '\000';
    strcat(massage_buf, "4 Disconnected ");
    strcat(massage_buf, name);
    if(mq_send(mqdes_rds, massage_buf, 30, 10) == -1){
        printf("ERR send\n");
        return 1;
    }

    //pthread_join(thread, (void *)&status);
    end_graf();
    printf("%d\n", tmp); 
    if(mq_close(mqdes_rds) == -1 || mq_close(mqdes_wrs) == -1){
        printf("ERR close\n");
        return 1;
    }
    return 0;
}
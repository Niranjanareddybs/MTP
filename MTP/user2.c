
#include "msocket.h"

#define MAX_MESSAGE_LENGTH 1023
int main(int argv,char* argc[]){
    if(argv!=3){
        printf("Usage: ./user2 <user_port> <destination_port>\n");
        exit(1);
    }
    size_t bytes_read;
    int destination_port = atoi(argc[2]);
    int user_port = atoi(argc[1]);
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(user_port);
    inet_aton("127.0.0.1",&serv_addr.sin_addr);
    char buffer[1024];
    int i=0;

    //the received data  is stored in the file destination_port_r.txt
    char rfile[100];
    sprintf(rfile,"%dr.txt",destination_port);
    int fp_receive = open(rfile,O_CREAT | O_WRONLY | O_TRUNC, 0666);

    char sfile[100];
    sprintf(sfile,"%d.txt",user_port);
    int fp_send = open(sfile, O_RDONLY , 0666);

    int sockfd = m_socket(AF_INET,SOCK_MTP, 0);
    m_bind(sockfd,"127.0.0.1",user_port,"127.0.0.1",destination_port);
    

    while(1){
        socklen_t addr_len=sizeof(serv_addr);
        memset(buffer,'\0',sizeof(buffer));
        int retval = m_recvfrom(sockfd,buffer,1024,0,(struct sockaddr*)&serv_addr,&addr_len);
        if(retval<0){
            continue;
        }
        if(strcmp(buffer,"\r\n")==0) break;
        write(fp_receive,buffer,strlen(buffer));
        fsync(fp_receive);
    }
    printf("Receive Successful\n");
    // int message=0;
    // while ((bytes_read = read(fp_send, buffer, MAX_MESSAGE_LENGTH)) > 0) {
    //     message++;
    //     int retval=-1;
     
    //     while(retval<0){
    //         retval = m_sendto(sockfd,buffer,bytes_read,0,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    //     }
    // }

    // int retval = m_sendto(sockfd,"\r\n",3,0,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    // printf("Send Succesfull\n");
    // while(1){}
    close(fp_receive);
    close(fp_send);

    return 0;
}
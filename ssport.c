#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
	struct sockaddr_in addr;
	struct sockaddr_in6 addr6;
	struct timeval timeout;
	//protocolo tcp ipv4
	void tcp(int ipv, char *ip){
		int sock = 0, cnx = 0;
		if(ipv == 4){
			for(int ports=1; ports <= 65535; ports++){
				addr.sin_family = AF_INET;
				addr.sin_addr.s_addr = inet_addr(ip);
				addr.sin_port = htons(ports);
				sock = socket(AF_INET, SOCK_STREAM, 0);
				timeout.tv_sec = 0;
				timeout.tv_usec = 1;
				setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
				setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
				if(sock < 0){
					perror("TCP IPv4 sock error");
					exit(1);
				}
				cnx = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
				if(cnx == 0){
					printf("*Porta %d do host %s aberta...\n", ports, ip);
				}
			close(sock);	
			}
		}

		//ipv6

		else if(ipv == 6){
			for(int ports=1; ports <= 65535; ports++){
				addr6.sin6_family = AF_INET6;
				inet_pton(AF_INET6, ip, &addr6.sin6_addr);
				addr6.sin6_port = htons(ports);
				sock = socket(AF_INET6, SOCK_STREAM, 0);
				if(sock < 0){
					perror("TCP IPv6 Sock error");
					exit(1);
				}
				cnx = connect(sock, (struct sockaddr *)&addr6, sizeof(addr6));
				if(cnx == 0){
					printf("*Porta %d do host %s aberta...\n", ports, ip);
				}
			close(sock);
			}
		}
	}
    
	// protocolo udp
	void udp(int ipv, char *ip){
		int sock = 0, cnx = 0;
		if(ipv == 4){
			struct sockaddr_in addr;
			for(int ports=1; ports <= 65535; ports++){
				addr.sin_family = AF_INET;
				addr.sin_addr.s_addr = inet_addr(ip);
				addr.sin_port = htons(ports);
				sock = socket(AF_INET, SOCK_DGRAM, 0);
				timeout.tv_sec = 0;
				timeout.tv_usec = 1;
				setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
				setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
				if(sock < 0){
					perror("UDP IPv4 sock error");
					exit(1);
				}
				cnx = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
				if(cnx == 0){
					printf("*Porta %d do host %s aberta...\n", ports, ip);
				}
			close(sock);	
			}
		}

		if(ipv == 6){
			for(int ports=1; ports <= 65535; ports++){
				addr6.sin6_family = AF_INET6;
				inet_pton(AF_INET6, ip, &addr6.sin6_addr);
				addr6.sin6_port = htons(ports);
				sock = socket(AF_INET6, SOCK_DGRAM, 0);
				if(sock < 0){
					perror("UDP IPv6 ock error");
					exit(1);
				}
				cnx = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
				if(cnx == 0){
					printf("*Porta %d do host %s aberta...\n", ports, ip);
				}
			close(sock);	
			}
		}
	}

    
	int main(int argc, char *argv[]){
		// ./ssport <ip> <tcp/udp> <4/6>
		int ipv = atoi(argv[3]);
		char *protocolo = argv[2];
		char *ip = argv[1];
		printf("Escaneando portas...\n");
		if(strcmp(protocolo, "tcp") == 0){
			tcp(ipv, ip);
		}
		else if(strcmp(protocolo, "udp") == 0){
			udp(ipv, ip);
		}

		return 0;
	}

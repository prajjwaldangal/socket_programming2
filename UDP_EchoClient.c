// UDP Echo Client
/*
  We only calculate delay with respect to timely receipt of ACK
  from the UDP Server. That we way we can resend the frame.

  Also, there might be a problem with the delay function that 
  was supplied from the book.

  The gettimeoftheday seems to be working though as can be seen
  in the attached screenshot after running ./UDP_client.
*/

#include <stdlib.h>
#include <strings.h>
#include <stdio.h>

#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define SERVER_UDP_PORT         5000
#define MAXLEN                  4096
#define DEFLEN                  64
#define MAX_ACK_DELAY           10

long delay(struct timeval t1, struct timeval t2);
int main(int argc, char **argv)
{
    int     data_size = DEFLEN, port = SERVER_UDP_PORT;
    int     i, j, sd, server_len;
    char    *pname, *host, rbuf[MAXLEN], sbuf[MAXLEN];
    struct  hostent         *hp;
    struct  sockaddr_in     server;
    struct  timeval         start, end;
	  unsigned long address;
    long d;

    pname = argv[0];
   	argc--;
   	argv++;
   	if (argc > 0 && (strcmp(*argv, "-s") == 0)) {
   		if (--argc > 0 && (data_size = atoi(*++argv))) {
          argc--;
          argv++;
      }
      else {
 	        fprintf(stderr,
            "Usage: %s [-s data_size] host [port]\n", pname);
            exit(1);
      }
      if (argc > 0) {
          host = *argv;
          if (--argc > 0)
            port = atoi(*++argv);
      }
    }
	  else {
		  fprintf(stderr,
          "Usage: %s [-s data_size] host [port]\n", pname);
          exit(1);
	  }

	  if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
          fprintf(stderr, "Can't create a socket\n");
          exit(1);
        }

    bzero((char *)&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    if ((hp = gethostbyname(host)) == NULL) {
            fprintf(stderr, "Can't get server's IP address\n");
            exit(1);
    }
    bcopy(hp->h_addr, (char *) &server.sin_addr, hp->h_length);

	  if (data_size > MAXLEN) {
        fprintf(stderr, "Data is too big\n");
        exit(1);
    }
	  for (i = 0; i < data_size; i++) {
        j = (i < 26) ? i : i % 26;
        sbuf[i] = 'a' + j;
    } // construct data to send to the server
    printf("UDP request will timeout after 10s\n");
    gettimeofday(&start, NULL); /* start delay measurement */
	  server_len = sizeof(server);
    if (sendto(sd, sbuf, data_size, 0, (struct sockaddr *)
        &server, server_len) == -1) {
        fprintf(stderr, "sendto error\n");
        exit(1);
    }
    while (!(recvfrom(sd, rbuf, MAXLEN, 0, (struct sockaddr *)
        &server, &server_len) < 0)){
            if (strncmp(rbuf, "ACK", 3) == 0){
              break;
            } else {
              gettimeofday(&end, NULL);
              d = delay(start, end);
              if (d < 10 * 10^6) {
                printf("ACK received in client.\n");
              } else {
                printf("Request timeout.\nProgram exiting..");
                exit(1)
              }
              fprintf(stderr, "ack error\n");
            }
    }
    if (recvfrom(sd, rbuf, MAXLEN, 0, (struct sockaddr *)
            &server, &server_len) < 0) {
        fprintf(stderr, "recvfrom error\n");
        exit(1);
    }
    // gettimeofday(&end, NULL); /* end delay measurement */ 
    if (strncmp(sbuf, rbuf, data_size) != 0)
        printf("Data is corrupted\n");
    close(sd);
    return(0);
}

long delay(struct timeval t1, struct timeval t2) {
        long d;
        d = (t2.tv_sec - t1.tv_sec) * 1000;
        d += ((t2.tv_usec - t1.tv_usec + 500) / 1000);
        return(d);
}

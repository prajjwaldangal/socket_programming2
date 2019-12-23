UDP_successful.png contains one screenshot of the UDP server responding to
the client's requests. Please download it or zoom out on the 
browser and have a look.

In that screenshot, the top portion is the server side UDP (./UDP_server) while the bottom portion is the client side UDP (./UDP_client -s 2 localhost). For the client, we have to specify the data size using -s flag following which we specify the server address (localhost in this case). 

As you can see in server's output, it receives a string of size 's' from the client. The string is nothing but English alphabets starting from a to s-1 other alphabets. You can also see how the client stops and waits for acknowledgement before it sends any other data. This is implemented in lines 96-111 in UDP_EchoClient.c. Since the client doesn't complain with a 'Data is corrupted' message, we can safely assume that the UDP communication was successful.

The UDP_EchoClient.c and UDP_EchoServer.c files contain additional comments. 

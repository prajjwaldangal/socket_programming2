![Alt text](./UDP_successful.png?raw=true "Optional Title")
The above screenshot pertains to a UDP server. Please zoom out on the browser and have a look, if it's too large.

In the screenshot, the top portion is the server side UDP (./UDP_server) while the bottom portion is the client side UDP (./UDP_client -s 2 localhost). For the client, we have to specify the data size using -s flag following which we specify the server address (localhost in this case). The data size refers to the length of English alphabet string to send to the server.

You can also see how the client stops and waits for acknowledgement before it sends any other data. This is implemented in lines 96-111 in UDP_EchoClient.c. Since the client doesn't complain with a 'Data is corrupted' message, we can safely assume that the UDP communication was successful.

The UDP_EchoClient.c and UDP_EchoServer.c files contain additional comments. 

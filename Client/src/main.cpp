#include "Client.h"
#include <iostream>


int main(int argc, char* argv[])
{
    std::cout<<"Prepaing client info"<<std::endl;
    ClientInfo clientInformations;
    clientInformations.SetClientInfo();
    std::cout<<"Client prepared"<<std::endl;
    GrpcClient client{"localhost:50051", clientInformations};
    client.SendMessages();
    return 0;
}

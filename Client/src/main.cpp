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
//    HelloMsg request;
//    request.set_medicaldeviceid(15);
//    request.set_medicaldevicename("Medical Device for tracking");
//    HelloMsgReponse response;
//    // Call
//    auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
//    std::unique_ptr<MedDataExchange::Stub> stub = MedDataExchange::NewStub(channel);
//    grpc::ClientContext context;
//    // hello
//    grpc::Status status = stub->Hello(&context, request, &response);
//    std::cout<<"Client received: Hello" << std::endl;
//    std::cout<<"Device name: " << response.medicalservername() << std::endl;
//    std::cout<<"Device id: " <<response.medicalserverid() << std::endl;
//    // probe
//    ProbeMsg probeRequest;
//    ProbeMsgResponse probeResponse;
//    probeRequest.set_medicaldeviceid(15);
//    probeRequest.set_medicaldevicename("Medical Device for tracking");
//    probeRequest.set_medicaldevicetype("unknown tpye x78");
//    grpc::ClientContext context2;
//    grpc::Status status2 = stub->Probe(&context2, probeRequest, &probeResponse);
//    std::cout<<"Client received: Probe" <<std::endl;
//    std::cout<<"Device name: "<<probeResponse.medicalservername() <<std::endl;
//    std::cout<<"Device id: "<<probeResponse.medicalserverid() <<std::endl;
//    std::cout<<"Device type: "<<probeResponse.probematch() << std::endl;
//    // getDatabase
//    GetDatabaseRequest dbRequest;
//    GetDatabaseResponse dbResponse;
//    dbRequest.set_databasename("Some db name");
//    dbRequest.set_accesskey("123xcvy7d5");
//    grpc::ClientContext context3;
//    grpc::Status status3 = stub->GetDatabase(&context3, dbRequest, &dbResponse);
//    std::cout<<"Database response: "<<std::endl;
//    std::cout<<"Database name: "<< dbResponse.databasename()<<std::endl;
//    std::cout<<"Database status: "<< dbResponse.databasestate() <<std::endl;
//    std::cout<<"Access granted: "<< dbResponse.accessgranted() <<std::endl;
    return 0;
}

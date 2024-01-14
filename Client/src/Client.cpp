#include "Client.h"


void GrpcClient::SendHello() {
    grpc::ClientContext context;
    HelloMsg request{m_clientInfo.helloMsg};
    HelloMsgReponse response;
    grpc::Status status = m_stub->Hello(&context, request, &response);
    std::cout<<"*** Client received following answer (Hello message) ***"<<std::endl;
    std::cout<<"    Device name: " << response.medicalservername() << std::endl;
    std::cout<<"    Device id: " <<response.medicalserverid() << std::endl;
}
void GrpcClient::SendProbe() {
    grpc::ClientContext context;
    ProbeMsg request{m_clientInfo.probeMsg};
    ProbeMsgResponse response;
    grpc::Status status = m_stub->Probe(&context, request, &response);
    std::cout<<"*** Client received following answer (Probe message) ***"<<std::endl;
    std::cout<<"    Device name: "<<response.medicalservername() <<std::endl;
    std::cout<<"    Device id: "<<response.medicalserverid() <<std::endl;
    std::cout<<"    Probe match value: ";
    if(response.probematch()) {
        std::cout<<"true "<<std::endl;
    } else {
        std::cout<<"false "<<std::endl;
    }

}
void GrpcClient::SendGetDatabase() {
    grpc::ClientContext context;
    GetDatabaseRequest request{m_clientInfo.dbRequest};
    GetDatabaseResponse response;
    grpc::Status status = m_stub->GetDatabase(&context, request, &response);
    std::cout<<"*** Client received following answer (GetDatabase message) ***"<<std::endl;
    std::cout<<"    Database name: "<< response.databasename()<<std::endl;
    std::cout<<"    Database status: "<< response.databasestate() <<std::endl;
    std::cout<<"    Access granted: ";
    if(response.accessgranted()){
        std::cout<<"true"<<std::endl;
    } else {
        std::cout<<"false"<<std::endl;
    }

}
void GrpcClient::SendSubscribe() {
    grpc::ClientContext context;
    SubscribeRequest request{m_clientInfo.subRequest};
    SubscribeResponse response;
    grpc::Status status = m_stub->Subscribe(&context, request, &response);
    std::cout<<"*** Client received following answer (Subscribe message) ***"<<std::endl;
    std::cout<<"    Report list: " << std::endl;
    for(auto& item : response.allowedreports()) {
        std::cout<<"    - Report name: "<< item.reportname() <<std::endl;
        std::cout<<"    - Report id: "<< item.reportid() <<std::endl;
        std::cout<<"    - Report allowed: ";
        if(item.allowed()) {
            std::cout<<"true"<<std::endl;
        } else {
            std::cout << "false" <<std::endl;
        }
    }
}

void GrpcClient::SendMessages(){
    SendHello();
    SendProbe();
    SendGetDatabase();
    SendSubscribe();
}

#include <myproto/MedInfo.grpc.pb.h>
#include <myproto/MedInfo.pb.h>
#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>
#include <iostream>

class MedDataExchangeService final : public MedDataExchange::Service {
public:
    virtual ::grpc::Status Hello(::grpc::ServerContext* context,
                                 const ::HelloMsg* request,
                                 ::HelloMsgReponse* response) {
        std::cout<<"Device id: " << request->medicaldeviceid() << std::endl;
        std::cout<<"Device name "<< request->medicaldevicename() << std::endl;
        response->set_medicalserverid(27);
        response->set_medicalservername("Medical-Server-7861x87");
        return ::grpc::Status::OK;
     }
};

int main(int argc, char* argv[])
{
     grpc::ServerBuilder builder;
     builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());

     MedDataExchangeService my_service;
     builder.RegisterService(&my_service);

     std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
     std::cout<<"Server started" <<std::endl;
     server->Wait();
    return 0;
}

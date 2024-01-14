#include "Server.h"


int main(int argc, char* argv[])
{
     grpc::ServerBuilder builder;
     builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());

     ServerInformation basicInfo{"MedicalServerForBasicOperations", 196547};
     GrpcServer grpcServer{basicInfo};
//     MedDataExchangeService my_service;
     builder.RegisterService(&grpcServer);

     std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
     std::cout<<"Grpc Server started" <<std::endl;
     server->Wait();
    return 0;
}

#include <myproto/MedInfo.grpc.pb.h>
#include <myproto/MedInfo.pb.h>

#include <grpc/grpc.h>
#include <grpcpp/create_channel.h>

#include <iostream>


int main(int argc, char* argv[])
{
    HelloMsg request;
    request.set_medicaldeviceid(15);
    request.set_medicaldevicename("Medical Device for tracking");
    HelloMsgReponse response;
    // Call
    auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
    std::unique_ptr<MedDataExchange::Stub> stub = MedDataExchange::NewStub(channel);
    grpc::ClientContext context;
    grpc::Status status = stub->Hello(&context, request, &response);
    std::cout<<"Client received: " << std::endl;
    std::cout<<"Device name: " << response.medicalservername() << std::endl;
    std::cout<<"Device id: " <<response.medicalserverid() << std::endl;
    return 0;
}

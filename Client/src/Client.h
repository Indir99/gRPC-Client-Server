#include <myproto/MedInfo.grpc.pb.h>
#include <myproto/MedInfo.pb.h>

#include <grpc/grpc.h>
#include <grpcpp/create_channel.h>
#include "ClientInfo.h"

class GrpcClient {
public:
    GrpcClient(const grpc::string& target, ClientInfo clInfo) {
        m_channel = grpc::CreateChannel(target, grpc::InsecureChannelCredentials());
        m_stub = MedDataExchange::NewStub(m_channel);
        m_clientInfo = clInfo;
    }

    void SendMessages();
private:
    void SendHello();
    void SendProbe();
    void SendGetDatabase();
    void SendSubscribe();
    std::unique_ptr<MedDataExchange::Stub> m_stub;
    std::shared_ptr<grpc::Channel> m_channel;
    ClientInfo m_clientInfo;
};

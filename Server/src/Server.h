#include <myproto/MedInfo.grpc.pb.h>
#include <myproto/MedInfo.pb.h>
#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>
#include "ServerInfo.h"

class GrpcServer final : public MedDataExchange::Service {
public:

    GrpcServer(ServerInformation serverInfo)
        : m_serverInfo{serverInfo} {}

    virtual ::grpc::Status Hello(::grpc::ServerContext* context,
                                 const ::HelloMsg* request,
                                 ::HelloMsgReponse* response) override;

    virtual ::grpc::Status Probe(::grpc::ServerContext* context,
                                 const ::ProbeMsg* request,
                                 ::ProbeMsgResponse* response) override;

    virtual ::grpc::Status GetDatabase(::grpc::ServerContext* context,
                                       const ::GetDatabaseRequest* request,
                                       ::GetDatabaseResponse* response) override;

    virtual ::grpc::Status Subscribe(::grpc::ServerContext* context, const ::SubscribeRequest* request, ::SubscribeResponse* response) override;
//        std::cout<<"Subscribe request content: "<<std::endl;
//        std::cout<<"Request type: "<<request->requesttype()<<std::endl;
//        std::cout<<"Reports: " <<std::endl;
//        for(auto& item : request->reports()) {
//            std::cout<<"Report name: "<< item.reportname() << std::endl;
//            std::cout<<"Report id"<< item.reportid() <<std::endl;
//        }
//        // validate reports something like that
//        // Create and populate a ReportAllowed message
//        ReportAllowed report1;
//        report1.set_reportid(1);
//        report1.set_reportname("Report 1");
//        report1.set_allowed(true);

//        // Create and populate another ReportAllowed message
//        ReportAllowed report2;
//        report2.set_reportid(2);
//        report2.set_reportname("Report 2");
//        report2.set_allowed(false);

//        response->add_allowedreports()->CopyFrom(report1);
//        response->add_allowedreports()->CopyFrom(report2);

//        return ::grpc::Status::OK;
//    }
private:
    bool ValidateDevice(const ::ProbeMsg* data);
    bool ValidateDeviceById(int id);
    bool ValidateDatabase(const ::GetDatabaseRequest* database);
    std::string ReadDatabaseStatus(std::string databaseName);
    ReportAllowed ValidateReport(const Report& report);
    ServerInformation m_serverInfo;
};

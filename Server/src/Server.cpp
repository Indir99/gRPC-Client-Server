#include "Server.h"


::grpc::Status GrpcServer::Hello(::grpc::ServerContext* context,
                                 const ::HelloMsg* request,
                                 ::HelloMsgReponse* response) {

    std::cout<<"*** New message received (Hello) ***" <<std::endl;
    std::cout<<"    Device id: " << request->medicaldeviceid() << std::endl;
    std::cout<<"    Device name: "<< request->medicaldevicename() << std::endl;
    response->set_medicalserverid(m_serverInfo.serverId);
    response->set_medicalservername(m_serverInfo.serverName);
    return ::grpc::Status::OK;
}

::grpc::Status GrpcServer::Probe(::grpc::ServerContext* context,
                                 const ::ProbeMsg* request,
                                 ::ProbeMsgResponse* response) {

    std::cout<<"*** New message received (Probe) ***" <<std::endl;
    std::cout<<"    Device id: " << request->medicaldeviceid() << std::endl;
    std::cout<<"    Device name: "<< request->medicaldevicename() << std::endl;
    std::cout<<"    Device type:" << request->medicaldevicetype() << std::endl;
    bool probeMatch{ValidateDevice(request)};
    response->set_medicalserverid(m_serverInfo.serverId);
    response->set_medicalservername(m_serverInfo.serverName);
    response->set_probematch(probeMatch);
    return ::grpc::Status::OK;
}

::grpc::Status GrpcServer::GetDatabase(::grpc::ServerContext* context,
                                       const ::GetDatabaseRequest* request,
                                       ::GetDatabaseResponse* response) {

    std::cout<<"*** New message received (GetDatabase) ***" <<std::endl;
    std::cout<<"    Database name: "<< request->databasename()<<std::endl;
    std::cout<<"    Databas access key: "<< request->accesskey()<<std::endl;
    response->set_databasename(request->databasename());
    response->set_databasestate(ReadDatabaseStatus(request->databasename()));
    response->set_accessgranted(ValidateDatabase(request));
    return ::grpc::Status::OK;
}

::grpc::Status GrpcServer::Subscribe(::grpc::ServerContext* context, const ::SubscribeRequest* request, ::SubscribeResponse* response) {
    std::cout<<"*** New message received (Subscribe) ***" <<std::endl;
    std::cout<<"    Request type: "<<request->requesttype()<<std::endl;
    std::cout<<"    Reports list:  " <<std::endl;
    for(auto& item : request->reports()) {
        std::cout<<"    - Report name: "<< item.reportname() << std::endl;
        std::cout<<"    - Report id: "<< item.reportid() <<std::endl;
    }
    // Report validation
    for(auto& item : request->reports()) {
        ReportAllowed report{ValidateReport(item)};
        response->add_allowedreports()->CopyFrom(report);

    }
    return ::grpc::Status::OK;
}

bool GrpcServer::ValidateDevice(const ::ProbeMsg* data) {
    //TODO: Consider other ways of validation
    return ValidateDeviceById(data->medicaldeviceid());
}
bool GrpcServer::ValidateDeviceById(int id){
    // TODO: Add validation
    return true;
}

bool GrpcServer::ValidateDatabase(const ::GetDatabaseRequest* database) {
    //TODO: Add validation
    return true;
}
std::string GrpcServer::ReadDatabaseStatus(std::string databaseName) {
    // TODO: Add status check
    return "Present";
}

ReportAllowed GrpcServer::ValidateReport(const Report& report){
    //TODO: Add validation
    ReportAllowed allowredReport;
    allowredReport.set_reportname(report.reportname());
    allowredReport.set_reportid(report.reportid());
    allowredReport.set_allowed(true);
    return allowredReport;
}

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

    virtual ::grpc::Status Subscribe(::grpc::ServerContext* context,
                                     const ::SubscribeRequest* request,
                                     ::SubscribeResponse* response) override;

    virtual ::grpc::Status StartReportsTypaA(::grpc::ServerContext* context,
                                             const ::RequestReportA* request,
                                             ::grpc::ServerWriter< ::PatientData>* writer) override;

    virtual ::grpc::Status StartReportsTypaB(::grpc::ServerContext*
                                             context, const ::RequestReportB* request,
                                             ::grpc::ServerWriter< ::TherapyData>* writer) override;
private:
    bool ValidateDevice(const ::ProbeMsg* data);
    bool ValidateDeviceById(int id);
    bool ValidateDatabase(const ::GetDatabaseRequest* database);
    std::string ReadDatabaseStatus(std::string databaseName);
    ReportAllowed ValidateReport(const Report& report);
    std::vector<PatientData> PreparePatientDataVecor();
    PatientData PreparePatientData(std::string patientID,
                                   std::string patientFirstName,
                                   std::string patientLastName,
                                   std::string bloodPressure,
                                   std::string temperature,
                                   std::string heartRate);

    std::vector<TherapyData> PrepareTherapyDataVecor();
    TherapyData PrepareTherapyData(std::string patientID,
                                   std::string patientFirstName,
                                   std::string patientLastName,
                                   std::string doctorID,
                                   std::string doctorFirstName,
                                   std::string doctorLastName,
                                   std::string therapyName,
                                   std::string therapyStatus);

    ServerInformation m_serverInfo;
};

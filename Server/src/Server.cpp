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

::grpc::Status GrpcServer::StartReportsTypaA(::grpc::ServerContext* context,
                                             const ::RequestReportA* request,
                                             ::grpc::ServerWriter< ::PatientData>* writer) {
    std::cout<<"*** New message received (Start reports (Type: A) ***" <<std::endl;
    std::cout<<"Request status: "<< request->status() << std::endl;
    auto PatientDataList{PreparePatientDataVecor()};
    for(const auto& item : PatientDataList){
        writer->Write(item);
    }
    return ::grpc::Status::OK;
}


::grpc::Status GrpcServer::StartReportsTypaB(::grpc::ServerContext*
                                             context, const ::RequestReportB* request,
                                             ::grpc::ServerWriter< ::TherapyData>* writer) {
    std::cout<<"*** New message received (Start reports (Type: B) ***" <<std::endl;
    std::cout<<"Request status: "<< request->status() << std::endl;
    auto TherapyDataList{PrepareTherapyDataVecor()};
    for(const auto& item : TherapyDataList) {
        writer->Write(item);
    }
    return ::grpc::Status::OK;
}


std::vector<PatientData> GrpcServer::PreparePatientDataVecor() {
    std::vector<PatientData> patVector;
    patVector.push_back(PreparePatientData("0001", "John", "Davis", "120/80", "36.8", "70"));
    patVector.push_back(PreparePatientData("0001", "John", "Davis", "130/85", "38.2", "75"));
    patVector.push_back(PreparePatientData("0001", "John", "Davis", "115/75", "37.4", "80"));
    return patVector;
}

PatientData GrpcServer::PreparePatientData(std::string patientID,
                                           std::string patientFirstName,
                                           std::string patientLastName,
                                           std::string bloodPressure,
                                           std::string temperature,
                                           std::string heartRate) {

    auto currentTime = std::chrono::system_clock::now();
    std::time_t currentTimeT = std::chrono::system_clock::to_time_t(currentTime);
    char timeBuffer[80];
    std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", std::localtime(&currentTimeT));
    std::string formattedTime(timeBuffer);

    PatientData patient;
    patient.set_patientid(patientID);
    patient.set_patientfirstname(patientFirstName);
    patient.set_patientlastname(patientLastName);
    patient.set_bloodpressure(bloodPressure);
    patient.set_temperature(temperature);
    patient.set_heartrate(heartRate);
    patient.set_time(formattedTime);
    return patient;
}

std::vector<TherapyData> GrpcServer::PrepareTherapyDataVecor() {
    std::vector<TherapyData> therVector;
    therVector.push_back(PrepareTherapyData("P001", "John", "Davis", "D001", "Dr. Smith", "Cardiologist", "Medication A", "Scheduled"));
    therVector.push_back(PrepareTherapyData("P001", "John", "Davis", "D001", "Dr. Smith", "Cardiologist", "Medication A", "Started"));
    therVector.push_back(PrepareTherapyData("P001", "John", "Davis", "D001", "Dr. Smith", "Cardiologist", "Medication A", "In Progress"));
    therVector.push_back(PrepareTherapyData("P001", "John", "Davis", "D001", "Dr. Smith", "Cardiologist", "Medication A", "In Progress"));
    therVector.push_back(PrepareTherapyData("P001", "John", "Davis", "D001", "Dr. Smith", "Cardiologist", "Medication A", "Completed"));
    return therVector;
}
TherapyData GrpcServer::PrepareTherapyData(std::string patientID,
                                           std::string patientFirstName,
                                           std::string patientLastName,
                                           std::string doctorID,
                                           std::string doctorFirstName,
                                           std::string doctorLastName,
                                           std::string therapyName,
                                           std::string therapyStatus) {
    auto currentTime = std::chrono::system_clock::now();
    std::time_t currentTimeT = std::chrono::system_clock::to_time_t(currentTime);
    char timeBuffer[80];
    std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", std::localtime(&currentTimeT));
    std::string formattedTime(timeBuffer);

    TherapyData therpay;
    therpay.set_patientid(patientID);
    therpay.set_patientfirstname(patientFirstName);
    therpay.set_patientlastname(patientLastName);
    therpay.set_doctorid(doctorID);
    therpay.set_doctorfirstname(doctorFirstName);
    therpay.set_doctortlastname(doctorLastName);
    therpay.set_therapyname(therapyName);
    therpay.set_therapystatus(therapyStatus);
    therpay.set_time(formattedTime);
    return therpay;
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

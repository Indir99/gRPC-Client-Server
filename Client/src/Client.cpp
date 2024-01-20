#include "Client.h"


namespace {
std::string GetCurrentTime(){
    auto currentTime = std::chrono::system_clock::now();
    std::time_t currentTimeT = std::chrono::system_clock::to_time_t(currentTime);
    char timeBuffer[80];
    std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", std::localtime(&currentTimeT));
    return std::string{timeBuffer};
}
} // namespace

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

void GrpcClient::StartReportA(){
    grpc::ClientContext context;
    RequestReportA request{m_clientInfo.reportA};
    PatientData patient;
    std::unique_ptr< ::grpc::ClientReader< ::PatientData>> reader {
        m_stub->StartReportsTypaA(&context, request)
    };
    while(reader->Read(&patient)) {
        std::cout<<"*** New Report (Type A) with following data: ***"<<std::endl;
        std::cout<<"    - Patient id: "<<patient.patientid() << std::endl;
        std::cout<<"    - Patient first name: "<<patient.patientfirstname() << std::endl;
        std::cout<<"    - Patient last name: "<<patient.patientlastname() << std::endl;
        std::cout<<"    - Blood pressure: "<<patient.bloodpressure() << std::endl;
        std::cout<<"    - Temperature: "<<patient.temperature() << std::endl;
        std::cout<<"    - Heart rate: "<<patient.heartrate() << std::endl;
        std::cout<<"    - Time: "<< patient.time() <<std::endl;
    }
}

void GrpcClient::StartReportB(){
    grpc::ClientContext context;
    RequestReportB request{m_clientInfo.reportB};
    TherapyData therapy;
    std::unique_ptr< ::grpc::ClientReader< ::TherapyData>> reader {
        m_stub->StartReportsTypaB(&context, request)
    };
    while(reader->Read(&therapy)) {
        std::cout<<"*** New Report (Type B) with following data: ***"<<std::endl;
        std::cout<<"    - Patient id: "<<therapy.patientid() << std::endl;
        std::cout<<"    - Patient first name: "<<therapy.patientfirstname() << std::endl;
        std::cout<<"    - Patient last name: "<<therapy.patientlastname() << std::endl;
        std::cout<<"    - Doctor id: "<<therapy.doctorid() <<std::endl;
        std::cout<<"    - Doctor name: "<<therapy.doctorfirstname() <<std::endl;
        std::cout<<"    - Doctor title: "<<therapy.doctortlastname() <<std::endl;
        std::cout<<"    - Therapy name: "<<therapy.therapyname() <<std::endl;
        std::cout<<"    - Therapy status: "<< therapy.therapystatus() <<std::endl;
        std::cout<<"    - Time: "<<therapy.time() <<std::endl;
    }
}

void GrpcClient::SetNewMeasurement(){
    grpc::ClientContext context;
    MeasurementOperation request;
    request.set_patientid("P001");
    request.set_operation("Start measurements");
    request.set_time(GetCurrentTime());
    MeasurementOperationConfirmation response;
    grpc::Status status = m_stub->SetNewMeasurement(&context, request, &response);
    std::cout<<"*** Client received following answer (SetNewMeasurement message) ***"<<std::endl;
    std::cout<<"Confirmation status: "<< response.confirmation() <<std::endl;
}

void GrpcClient::SetValue(){
    grpc::ClientContext context;
    SetValueOperation request;
    request.set_patientid("POO1");
    request.set_operation("Change the dose!");
    request.set_value("85");
    request.set_time(GetCurrentTime());
    SetValueOperationConfirmation response;
    grpc::Status status = m_stub->SetValue(&context, request, &response);
    std::cout<<"*** Client received following answer (SetValue message) ***"<<std::endl;
    std::cout<<"Confirmation status: "<< response.confirmation() <<std::endl;
}

void GrpcClient::SendBye(){
    grpc::ClientContext context;
    ByeMsg request{m_clientInfo.byeMsg};
    ByeMsgResponse response;
    grpc::Status status = m_stub->Bye(&context, request, &response);
    std::cout<<"*** Client received following answer (Bye message) ***"<<std::endl;
    std::cout<<"Confirmation status: "<< response.confirmation() <<std::endl;
}

void GrpcClient::SendMessages(){
    SendHello();
    SendProbe();
    SendGetDatabase();
    SendSubscribe();
    StartReportA();
    StartReportB();
    SetNewMeasurement();
    SetValue();
    SendBye();

}

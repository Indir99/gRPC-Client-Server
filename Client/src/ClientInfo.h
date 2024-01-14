#include <iostream>
#include <myproto/MedInfo.pb.h>


constexpr int CLIENT_ID{};
constexpr std::array CLIENT_NAME{"Medical Device For Patient Monitoring"};
constexpr std::array CLIENT_TYPE{"MedDevFPMVer1.7"};
constexpr std::array DATABASE_NAME{"Patient Database"};
constexpr std::array DATABASE_ACCESS_KEY{"ack1232dbPat"};
constexpr std::array START_STATUS{"START"};
const std::vector<std::pair<int, std::string>> reportVector{
    {25, "ReportTypeA"},
    {27, "ReportTypeB"}
};

struct ClientInfo {
    int clientId;
    std::string clientName;
    std::string clientType;
    std::string databaseName;
    std::string databaseAccessKey;
    HelloMsg helloMsg;
    ProbeMsg probeMsg;
    RequestReportA reportA;
    RequestReportB reportB;
    GetDatabaseRequest dbRequest;
    SubscribeRequest subRequest;
    std::vector<Report> repVector;


    void SetClientInfo() {
        clientId = CLIENT_ID;
        clientName = CLIENT_NAME.front();
        clientType = CLIENT_TYPE.front();
        databaseName = DATABASE_NAME.front();
        databaseAccessKey = DATABASE_ACCESS_KEY.front();
        // hello msg
        helloMsg.set_medicaldevicename(clientName);
        helloMsg.set_medicaldeviceid(clientId);
        // probe msg
        probeMsg.set_medicaldeviceid(clientId);
        probeMsg.set_medicaldevicename(clientName);
        probeMsg.set_medicaldevicetype(clientType);
        // database msg
        dbRequest.set_databasename(databaseName);
        dbRequest.set_accesskey(databaseAccessKey);
        // subscribe message
        subRequest = PrepareReports();
        reportA.set_status(START_STATUS.front());
        reportB.set_status(START_STATUS.front());
    }
    SubscribeRequest PrepareReports() {
        SubscribeRequest subreq;
        subreq.set_requesttype("Subscribe_to_Server_Reports");
        for(auto& item : reportVector) {
            Report report;
            report.set_reportid(item.first);
            report.set_reportname(item.second);
            repVector.push_back(report);
            subreq.add_reports()->CopyFrom(report);
        }
        return subreq;
    }
};


#include "GraphRPCService.h"

GraphRPCService::GraphRPCService() {

}

GraphRPCService::~GraphRPCService() {

}

void GraphRPCService::add_graph(RpcController* controller, const GraphRequest* request, GraphResponse* response, Closure* done) {
    done->Run();
}

void GraphRPCService::add_vertex(RpcController* controller, const GraphRequest* request, GraphResponse* response, Closure* done) {
    done->Run();
}

void GraphRPCService::add_edge(RpcController* controller, const GraphRequest* request, GraphResponse* response, Closure* done) {
    done->Run();
}

void GraphRPCService::delete_graph(RpcController* controller, const GraphRequest* request, GraphResponse* response, Closure* done) {
    done->Run();
}

void GraphRPCService::delete_vertex(RpcController* controller, const GraphRequest* request, GraphResponse* response, Closure* done) {
    done->Run();
}

void GraphRPCService::delete_edge(RpcController* controller, const GraphRequest* request, GraphResponse* response, Closure* done) {
    done->Run();
}

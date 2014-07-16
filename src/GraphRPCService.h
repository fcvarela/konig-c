#ifndef KONIG_GRAPH_RPC_SERVICE_H
#define KONIG_GRAPH_RPC_SERVICE_H

#include "graphproto.pb.h"

using namespace graphproto;
using namespace google::protobuf;

class GraphRPCService : public GraphService {
public:
    GraphRPCService();
    ~GraphRPCService();

    void add_graph(RpcController* controller, const GraphRequest* request, GraphResponse* response, Closure* done);
    void add_vertex(RpcController* controller, const GraphRequest* request, GraphResponse* response, Closure* done);
    void add_edge(RpcController* controller, const GraphRequest* request, GraphResponse* response, Closure* done);
    void delete_graph(RpcController* controller, const GraphRequest* request, GraphResponse* response, Closure* done);
    void delete_vertex(RpcController* controller, const GraphRequest* request, GraphResponse* response, Closure* done);
    void delete_edge(RpcController* controller, const GraphRequest* request, GraphResponse* response, Closure* done);
};

#endif

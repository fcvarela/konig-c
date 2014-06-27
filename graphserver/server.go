package graphserver

import (
	"../graph"
	"../graphproto.pb"
	"code.google.com/p/goprotobuf/proto"
)

type GraphServer struct {
	Name   string
	Graphs *graph.GraphList
}

type GraphService int

func NewGraphServer() (*GraphServer, error) {
	gs := GraphServer{}
	gs.Graphs = graph.NewGraphList()
	return &GraphServer{}, nil
}

func (gs *GraphServer) Startup() {
	graphproto.ListenAndServeGraphService("tcp", ":1984", new(GraphService))
}

func (gs *GraphServer) Shutdown() {

}

func (s *GraphService) Newgraph(args *graphproto.NewGraphRequest, reply *graphproto.NewGraphResponse) error {
	reply.Res = proto.Int32(0)
	return nil
}

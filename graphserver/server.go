package graphserver

import (
	"bitbucket.org/fcvarela/konig/graph"
	"bitbucket.org/fcvarela/konig/graphproto.pb"
	"code.google.com/p/goprotobuf/proto"
)

type GraphService int

func Startup() {
	graphproto.ListenAndServeGraphService("tcp", ":1984", new(GraphService))
}

func Shutdown() {

}

func (s *GraphService) AddGraph(args *graphproto.GraphRequest, reply *graphproto.GraphResponse) error {
	graph_id, _ := graph.AddGraph()
	reply.ObjId = proto.Uint64(graph_id)
	return nil
}

func (s *GraphService) AddVertex(args *graphproto.GraphRequest, reply *graphproto.GraphResponse) error {
	vertex_id, _ := graph.AddVertex(args.GetObjId1())
	reply.ObjId = proto.Uint64(vertex_id)
	return nil
}

func (s *GraphService) AddEdge(args *graphproto.GraphRequest, reply *graphproto.GraphResponse) error {
	graph.AddEdge(args.GetObjId1(), args.GetObjId2(), args.GetObjId3())
	return nil
}

func (s *GraphService) DeleteGraph(args *graphproto.GraphRequest, reply *graphproto.GraphResponse) error {
	graph.DeleteGraph(args.GetObjId1())
	return nil
}

func (s *GraphService) DeleteVertex(args *graphproto.GraphRequest, reply *graphproto.GraphResponse) error {
	graph.DeleteVertex(args.GetObjId1(), args.GetObjId2())
	return nil
}

func (s *GraphService) DeleteEdge(args *graphproto.GraphRequest, reply *graphproto.GraphResponse) error {
	graph.DeleteEdge(args.GetObjId1(), args.GetObjId2(), args.GetObjId3())
	return nil
}

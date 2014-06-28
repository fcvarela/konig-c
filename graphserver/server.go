package graphserver

import (
	"bitbucket.org/fcvarela/konig/graphproto.pb"
	"code.google.com/p/goprotobuf/proto"
)

type GraphService int

func Startup() {
	graphproto.ListenAndServeGraphService("tcp", ":1984", new(GraphService))
}

func Shutdown() {

}

func (s *GraphService) Newgraph(args *graphproto.NewGraphRequest, reply *graphproto.NewGraphResponse) error {
	reply.Res = proto.Int32(0)
	return nil
}

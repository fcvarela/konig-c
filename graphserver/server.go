package graphserver

import (
	"../graph"
)

type GraphServer struct {
	Name   string
	Graphs graph.GraphList
}

func NewGraphServer() (*GraphServer, error) {
	return &GraphServer{}, nil
}

func (s *GraphServer) Shutdown() {

}

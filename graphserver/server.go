package graphserver

import (
	"errors"
)

type GraphServer struct {
	name string
}

func (s *GraphServer) Bootstrap() error {
	return nil
	return errors.New("Could not bootstrap graphserver")
}

func (s *GraphServer) Shutdown() {

}

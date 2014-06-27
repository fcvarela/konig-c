package main

import (
	"./graphrenderer"
	"./graphserver"
)

func main() {
	var g graphrenderer.GraphRenderer
	err := g.Bootstrap()
	if err != nil {
		panic(err.Error())
	}

	var s graphserver.GraphServer
	err = s.Bootstrap()
	if err != nil {
		panic(err.Error())
	}

	for !g.Finished {
		g.Frame()
	}

	g.Shutdown()
	s.Shutdown()
}

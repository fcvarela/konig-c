package main

import (
	"./graphrenderer"
	"./graphserver"
)

func main() {
	// create our renderer
	gr, err := graphrenderer.NewGraphRenderer()
	if err != nil {
		panic(err.Error())
	}

	// create a server to manipulate graphs
	gs, err := graphserver.NewGraphServer()

	for !gr.Finished {
		gr.Frame()
	}

	gs.Shutdown()
	gr.Shutdown()
}

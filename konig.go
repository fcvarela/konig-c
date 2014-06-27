package main

import (
	"./graphrenderer"
	"./graphserver"
)

func main() {
	// create a server to manipulate graphs and fire it up
	// on separate goroutine
	gs, err := graphserver.NewGraphServer()
	if err != nil {
		panic(err.Error())
	}

	go gs.Startup()

	// create our renderer with the server as the api
	gr, err := graphrenderer.NewGraphRenderer(gs.Graphs)
	if err != nil {
		panic(err.Error())
	}

	for !gr.Finished {
		gr.Frame()
	}

	gs.Shutdown()
	gr.Shutdown()
}

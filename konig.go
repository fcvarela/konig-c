package main

import (
	"bitbucket.org/fcvarela/konig/graphrenderer"
	"bitbucket.org/fcvarela/konig/graphserver"
)

func main() {
	// create a server to manipulate graphs and fire it up
	// on separate goroutine
	go graphserver.Startup()

	// create our renderer with the server as the api
	gr, err := graphrenderer.NewGraphRenderer()
	if err != nil {
		panic(err.Error())
	}

	for !gr.Finished {
		gr.Frame()
	}

	graphserver.Shutdown()
	gr.Shutdown()
}

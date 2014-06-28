package main

import (
	"bitbucket.org/fcvarela/konig/graph"
	"bitbucket.org/fcvarela/konig/graphproto.pb"
	"code.google.com/p/goprotobuf/proto"
	"fmt"
	"log"
)

func testprotorpcclient() {
	fmt.Println("Starting")
	stub, client, err := graphproto.DialGraphService("tcp", "127.0.0.1:1984")
	if err != nil {
		log.Fatal(`graphproto.DialGraphService("tcp", "127.0.0.1:1984"):`, err)
	}
	defer client.Close()

	var args graphproto.NewGraphRequest
	var reply graphproto.NewGraphResponse

	for i := 0; i < 10000; i++ {
		args.Name = proto.String("hello, world")
		if err = stub.Newgraph(&args, &reply); err != nil {
			log.Fatal("graphproto error:", err)
		}
		if i%1000 == 0 {
			fmt.Printf("Result: (%s)=%d\n", args.GetName(), reply.GetRes())
		}
	}
}

func testgraphapiclient() {
	graph_id, err := graph.AddGraph()
	if err != nil {
		panic(err.Error())
	}

	var vertices []uint64
	for j := 0; j < 10e6; j++ {
		vid, err := graph.AddVertex(graph_id)
		if err != nil {
			panic(err.Error())
		}
		vertices = append(vertices, vid)
	}

	for j := 0; j < 10e6; j++ {
		graph.AddEdge(graph_id, vertices[j], vertices[(j+1)%100])
	}
}

func main() {
	// testprotorpcclient()
	testgraphapiclient()
}

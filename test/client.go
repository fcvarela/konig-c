package main

import (
	"bitbucket.org/fcvarela/konig/graphproto.pb"
	"code.google.com/p/goprotobuf/proto"
	"fmt"
	"log"
)

func main() {
	fmt.Println("Starting")
	stub, client, err := graphproto.DialGraphService("tcp", "127.0.0.1:1984")
	if err != nil {
		log.Fatal(`graphproto.DialGraphService("tcp", "127.0.0.1:1984"):`, err)
	}
	defer client.Close()

	// create one graph
	var args graphproto.GraphRequest
	var reply graphproto.GraphResponse

	if err = stub.AddGraph(&args, &reply); err != nil {
		log.Fatal("Could not create graph:", err)
	}

	graph_id := reply.GetObjId()

	// add vertices and edges
	var req graphproto.GraphRequest
	var resp graphproto.GraphResponse

	var vertices []uint64
	for j := 0; j < 1e5; j++ {
		if j%1000 == 0 {
			log.Println(j)
		}
		// prepare the args
		req.ObjId1 = proto.Uint64(graph_id)

		if err = stub.AddVertex(&req, &resp); err != nil {
			log.Fatal("Could not add vertex:", err)
		}

		vertices = append(vertices, resp.GetObjId())
	}

	for j := 0; j < 1e5; j++ {
		if j%1000 == 0 {
			log.Println(j)
		}
		req.ObjId2 = proto.Uint64(vertices[j])
		req.ObjId3 = proto.Uint64(vertices[(j+1)%100])
		if err = stub.AddEdge(&req, &resp); err != nil {
			log.Fatal("Could not add edge:", err)
		}
	}
}

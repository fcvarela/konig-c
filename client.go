package main

import (
	"./graphproto.pb"
	"code.google.com/p/goprotobuf/proto"
	"fmt"
	"log"
)

func main() {
	fmt.Println("Starting")
	stub, client, err := graphproto.DialGraphService("tcp", "127.0.0.1:1984")
	if err != nil {
		log.Fatal(`arith.DialGraphService("tcp", "127.0.0.1:1984"):`, err)
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

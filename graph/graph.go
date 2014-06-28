package graph

type Vertex struct {
	ID        uint64
	Neighbors map[uint64]bool
}

type Graph struct {
	ID       uint64
	Vertices map[uint64]Vertex
}

var gl = make(map[uint64]Graph)
var gl_opcounter uint64 = 0

func GetGraphs() map[uint64]Graph {
	return gl
}

func AddGraph() (id uint64, err error) {
	gl_opcounter += 1
	id = gl_opcounter
	gl[id] = Graph{id, make(map[uint64]Vertex)}
	return id, nil
}

func DelegeGraph(id uint64) error {
	for k := range gl[id].Vertices {
		for kk := range gl[id].Vertices[k].Neighbors {
			delete(gl[id].Vertices[k].Neighbors, kk)
		}
		delete(gl[id].Vertices, k)
	}
	return nil
}

// API CALL
func AddVertex(graph_id uint64) (id uint64, err error) {
	gr := gl[graph_id]
	return gr.addVertex()
}

func (gr *Graph) addVertex() (id uint64, err error) {
	gl_opcounter += 1
	id = gl_opcounter
	gr.Vertices[id] = Vertex{id, make(map[uint64]bool)}
	return id, nil
}

// API CALL
func DeleteVertex(graph_id uint64, vertex_id uint64) error {
	gr := gl[graph_id]
	return gr.deleteVertex(vertex_id)
}

func (gr *Graph) deleteVertex(id uint64) error {
	// iterate though our neighbors
	for k := range gr.Vertices[id].Neighbors {
		// remove this vertex from their list of neighbors too
		delete(gr.Vertices[k].Neighbors, id)
		delete(gr.Vertices[id].Neighbors, k)
	}
	delete(gr.Vertices, id)
	return nil
}

// API CALL
func AddEdge(graph_id uint64, id1 uint64, id2 uint64) error {
	gr := gl[graph_id]
	return gr.addEdge(id1, id2)
}

func (gr *Graph) addEdge(id1 uint64, id2 uint64) error {
	gr.Vertices[id1].Neighbors[id2] = true
	gr.Vertices[id2].Neighbors[id1] = true
	return nil
}

// API CALL
func DeleteEdge(graph_id uint64, id1 uint64, id2 uint64) error {
	gr := gl[graph_id]
	return gr.deleteEdge(id1, id2)
}

func (gr *Graph) deleteEdge(id1 uint64, id2 uint64) error {
	delete(gr.Vertices[id1].Neighbors, id2)
	delete(gr.Vertices[id2].Neighbors, id1)
	return nil
}

package graph

type Node struct {
	name string
}

type Edge struct {
	name string
}

type Graph struct {
	Name  string
	Nodes []Node
	Edges []Edge
}

type GraphList struct {
	Graphs []Graph
}

func (gl *GraphList) Bootstrap() error {
	gl.Graphs = make([]Graph, 0)
	return nil
}

func (gl *GraphList) NewGraph(name string) error {
	graph := Graph{}

	graph.Name = "random"
	graph.Nodes = make([]Node, 0)
	graph.Edges = make([]Edge, 0)

	gl.Graphs = append(gl.Graphs, graph)

	return nil
}

package graphrenderer

import (
	"bitbucket.org/fcvarela/konig/graph"
	"errors"
	"fmt"
	gl "github.com/fcvarela/gl"
	glfw "github.com/go-gl/glfw3"
)

type GraphRenderer struct {
	window           *glfw.Window
	Finished         bool
	GLContextVersion string
}

func errorCallback(err glfw.ErrorCode, desc string) {
	fmt.Printf("%v: %v\n", err, desc)
}

func NewGraphRenderer() (*GraphRenderer, error) {
	glfw.SetErrorCallback(errorCallback)

	if !glfw.Init() {
		return nil, errors.New("Can't init glfw!")
	}

	// make sure we get a core profile
	glfw.WindowHint(glfw.ContextVersionMajor, 4)
	glfw.WindowHint(glfw.ContextVersionMinor, 1)
	glfw.WindowHint(glfw.OpenglForwardCompatible, glfw.True)
	glfw.WindowHint(glfw.OpenglProfile, glfw.OpenglCoreProfile)

	monitor, err := glfw.GetPrimaryMonitor()
	if err != nil {
		return nil, err
	}

	videomode, err := monitor.GetVideoMode()
	if err != nil {
		return nil, err
	}

	gr := GraphRenderer{}
	gr.window, err = glfw.CreateWindow(videomode.Width/2.0, videomode.Height/2.0, "Konig", nil, nil)
	if err != nil {
		return nil, err
	}

	gr.window.MakeContextCurrent()
	gr.GLContextVersion = gl.GetString(gl.VERSION)
	fmt.Println(gr.GLContextVersion)
	gr.Finished = false

	glfw.SwapInterval(1)
	gl.Init()

	gr.InitScene()

	return &gr, nil
}

func (g *GraphRenderer) InitScene() {
	gl.Enable(gl.DEPTH_TEST)
	gl.Disable(gl.LIGHTING)

	gl.ClearColor(0.5, 0.5, 0.5, 1.0)
	gl.ClearDepth(1.0)
	gl.DepthFunc(gl.LEQUAL)

	w, h := g.window.GetSize()
	gl.Viewport(0, 0, w, h)
	gl.MatrixMode(gl.PROJECTION)
	gl.LoadIdentity()
	gl.Frustum(-1, 1, -1, 1, 1.0, 10.0)
	gl.MatrixMode(gl.MODELVIEW)
	gl.LoadIdentity()
}

func (g *GraphRenderer) Update() {
	glfw.PollEvents()

	// copy graphs positions and adj lists into buffers

	// run opencl kernel to update into copy

	// graceful shutdown
	if g.window.ShouldClose() {
		g.Finished = true
	}
}

func (g *GraphRenderer) Cull() {

}

func (g *GraphRenderer) Draw() {
	gl.Clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT)

	gl.MatrixMode(gl.MODELVIEW)
	gl.LoadIdentity()

	graphs := graph.GetGraphs()
	for g := range graphs {
		verts := graph.ListVertices(g)
		if verts == nil {
			fmt.Println("Error getting vertices")
		} else {
			fmt.Println("SUCCESS")
		}
	}

	g.window.SwapBuffers()
}

func (g *GraphRenderer) Frame() {
	g.Update()
	g.Cull()
	g.Draw()
}

func (g *GraphRenderer) Shutdown() {
	glfw.Terminate()
}

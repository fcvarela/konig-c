package graphrenderer

import (
	"../graph"
	"errors"
	"fmt"
	gl "github.com/fcvarela/gl"
	glfw "github.com/go-gl/glfw3"
)

type GraphRenderer struct {
	window           *glfw.Window
	Finished         bool
	GLContextVersion string
	GraphList        *graph.GraphList
}

func errorCallback(err glfw.ErrorCode, desc string) {
	fmt.Printf("%v: %v\n", err, desc)
}

func NewGraphRenderer(graphlist *graph.GraphList) (*GraphRenderer, error) {
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
	gr.Finished = false
	gr.GraphList = graphlist

	return &gr, nil
}

func (g *GraphRenderer) Update() {
	glfw.PollEvents()

	// graceful shutdown
	if g.window.ShouldClose() {
		g.Finished = true
	}
}

func (g *GraphRenderer) Cull() {

}

func (g *GraphRenderer) Draw() {
	if !g.window.ShouldClose() {
		g.window.SwapBuffers()
	}
}

func (g *GraphRenderer) Frame() {
	g.Update()
	g.Cull()
	g.Draw()
}

func (g *GraphRenderer) Shutdown() {
	glfw.Terminate()
}

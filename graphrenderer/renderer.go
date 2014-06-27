package graphrenderer

import (
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

func (g *GraphRenderer) Bootstrap() error {
	glfw.SetErrorCallback(errorCallback)

	if !glfw.Init() {
		return errors.New("Can't init glfw!")
	}

	// make sure we get a core profile
	glfw.WindowHint(glfw.ContextVersionMajor, 4)
	glfw.WindowHint(glfw.ContextVersionMinor, 1)
	glfw.WindowHint(glfw.OpenglForwardCompatible, glfw.True)
	glfw.WindowHint(glfw.OpenglProfile, glfw.OpenglCoreProfile)

	monitor, err := glfw.GetPrimaryMonitor()
	if err != nil {
		return err
	}

	videomode, err := monitor.GetVideoMode()
	if err != nil {
		return err
	}

	g.window, err = glfw.CreateWindow(videomode.Width/2.0, videomode.Height/2.0, "Konig", nil, nil)
	if err != nil {
		return err
	}

	g.window.MakeContextCurrent()
	g.GLContextVersion = gl.GetString(gl.VERSION)
	g.Finished = false

	return nil
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
		//Do OpenGL stuff
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

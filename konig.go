package main

import (
	"fmt"
	gl "github.com/fcvarela/gl"
	glfw "github.com/go-gl/glfw3"
	"log"
)

func errorCallback(err glfw.ErrorCode, desc string) {
	fmt.Printf("%v: %v\n", err, desc)
}

func main() {
	glfw.SetErrorCallback(errorCallback)

	if !glfw.Init() {
		panic("Can't init glfw!")
	}
	defer glfw.Terminate()

	// make sure we get a core profile
	glfw.WindowHint(glfw.ContextVersionMajor, 4)
	glfw.WindowHint(glfw.ContextVersionMinor, 1)
	glfw.WindowHint(glfw.OpenglForwardCompatible, glfw.True)
	glfw.WindowHint(glfw.OpenglProfile, glfw.OpenglCoreProfile)

	monitor, err := glfw.GetPrimaryMonitor()
	if err != nil {
		panic(err)
	}

	videomode, err := monitor.GetVideoMode()
	if err != nil {
		panic(err)
	}

	window, err := glfw.CreateWindow(videomode.Width, videomode.Height, "Testing", monitor, nil)
	if err != nil {
		panic(err)
	}

	window.MakeContextCurrent()
	log.Println("Created window with OpenGL version:", gl.GetString(gl.VERSION))

	for !window.ShouldClose() {
		//Do OpenGL stuff
		window.SwapBuffers()
		glfw.PollEvents()
	}
}

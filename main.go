package main

import rl "github.com/gen2brain/raylib-go/raylib"

const PADDING = 100

func main() {

	var display = rl.GetCurrentMonitor()
	rl.InitWindow(int32(rl.GetMonitorWidth(display)), int32(rl.GetMonitorHeight(display)), "no2grm")
	defer rl.CloseWindow()

	if !rl.IsWindowFullscreen() {
		rl.ToggleBorderlessWindowed()
	}

	rl.SetTargetFPS(60)
	rl.SetExitKey(rl.KeyNull)

	var maxBounds = newBounds(PADDING, int32(rl.GetScreenWidth())-PADDING, PADDING, int32(rl.GetScreenHeight())-PADDING)
	var rec = newState(25, 15, 15, maxBounds)
	rec.declareStates(&HOME, &CREATE)

	for !rl.WindowShouldClose() {
		if !rec.fn.handleEvents() {
			break
		}
		rec.fn.draw()
	}
}

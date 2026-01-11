package main

import rl "github.com/gen2brain/raylib-go/raylib"

var HOME = Home{}

type Home struct {
	rec *State
}

func (h *Home) setRec(rec *State) {
	h.rec = rec
}

func (h *Home) getRec() *State {
	return h.rec
}

func (h *Home) handleEvents() bool {
	if rl.IsKeyPressed(rl.KeyEscape) {
		return false
	}
	if rl.IsKeyPressed(rl.KeyN) {
		h.rec.fn = &CREATE
	}
	return true
}

func (h *Home) draw() {
	const TitleText = "HOME"
	const TitleSize = 40
	const NewText = "Press N to create a new Nonogram"
	const NewSize = 20
	rl.BeginDrawing()
	{
		rl.ClearBackground(h.rec.style.background)
		rl.DrawText(TitleText, (int32(rl.GetScreenWidth())-rl.MeasureText(TitleText, TitleSize))/2, int32(rl.GetScreenHeight())/2-TitleSize, TitleSize, h.rec.style.foreground)
		rl.DrawText(NewText, (int32(rl.GetScreenWidth())-rl.MeasureText(NewText, NewSize))/2, int32(rl.GetScreenHeight())/2+NewSize, NewSize, h.rec.style.foreground)
	}
	rl.EndDrawing()
}

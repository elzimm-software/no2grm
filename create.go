package main

import (
	rl "github.com/gen2brain/raylib-go/raylib"
)

var CREATE = Create{}

type Create struct {
	rec *State
}

func (c *Create) setRec(rec *State) {
	c.rec = rec
}

func (c *Create) getRec() *State {
	return c.rec
}

func (c *Create) handleEvents() bool {
	if rl.IsKeyPressed(rl.KeyEscape) {
		c.rec.fn = &HOME
	}
	solidTest := c.checkAndAddAt(rl.MouseButtonLeft, Solid, Cross)
	crossTest := c.checkAndAddAt(rl.MouseButtonRight, Cross, Solid)
	noteTest := c.checkAndAddAt(rl.MouseButtonMiddle, Note, Solid, Cross)

	if solidTest() || crossTest() || noteTest() {
		for _, p := range c.rec.line {
			c.rec.grid.setCell(&p, c.rec.fill)
		}
		c.rec.drag = Draw
		c.rec.fill = Empty
		c.rec.line = c.rec.line[:0]
	}
	return true
}

func (c *Create) draw() {
	rl.BeginDrawing()
	{
		rl.ClearBackground(c.rec.style.background)
		rl.DrawFPS(0, 0)
		c.rec.grid.colorCells(c.rec.cellSize, &c.rec.bounds, &c.rec.style)
		c.rec.colorTempCells()
		c.rec.grid.drawGrid(c.rec.cellSize, &c.rec.bounds, c.rec.style.foreground)
	}
	rl.EndDrawing()
}

func (c *Create) checkAndAddAt(mouseButton rl.MouseButton, fill FillType, protected ...FillType) func() bool {
	testFn := func() bool {
		return rl.IsMouseButtonReleased(mouseButton) && c.rec.fill == fill
	}
	if (rl.IsMouseButtonPressed(mouseButton) && c.rec.fill == Empty) || (rl.IsMouseButtonDown(mouseButton) && c.rec.fill == fill) {
		p := c.rec.findCellXY(rl.GetMousePosition())
		if p.x < c.rec.grid.nCols && p.y < c.rec.grid.nRows {
			index := c.rec.grid.getIndex(&p)
			if c.rec.grid.cells[index] == fill && c.rec.fill == Empty {
				c.rec.drag = Clear
			}
			c.rec.fill = fill
			under := c.rec.grid.cells[index]
			for _, prot := range protected {
				if under == prot {
					return testFn
				}
			}
			c.rec.addTempCell(p)
		}
	}
	return testFn
}

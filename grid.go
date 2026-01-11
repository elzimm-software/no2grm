package main

import (
	rl "github.com/gen2brain/raylib-go/raylib"
)

type FillType int

const (
	Empty FillType = iota
	Solid
	Cross
	Note
)

type DragType int

const (
	Draw DragType = iota
	Clear
)

type Style struct {
	foreground rl.Color
	background rl.Color
	thickness  float32
	radius     float32
}

func newStyle(foreground rl.Color, background rl.Color, thickness float32, radius float32) *Style {
	s := Style{
		foreground: foreground,
		background: background,
		thickness:  thickness,
		radius:     radius,
	}
	return &s
}

type Point struct {
	x int32
	y int32
}

func newPoint(x int32, y int32) Point {
	p := Point{
		x: x,
		y: y,
	}
	return p
}

type Grid struct {
	nRows       int32
	nCols       int32
	rowMaxRules int
	colMaxRules int
	rowRules    []Rules
	colRules    []Rules
	cells       []FillType
}

func newGrid(nRows int32, nCols int32) *Grid {
	g := Grid{
		nRows:       nRows,
		nCols:       nCols,
		rowMaxRules: 0,
		colMaxRules: 0,
		cells:       make([]FillType, nRows*nCols),
	}
	return &g
}

func (g *Grid) getXY(index int32) (int32, int32) {
	return index % g.nCols, index / g.nCols
}

func (g *Grid) getIndex(p *Point) int32 {
	return p.y*g.nCols + p.x
}

func (g *Grid) setCell(p *Point, fill FillType) {
	if p.x >= g.nCols || p.y >= g.nRows || p.x < 0 || p.y < 0 {
		return
	}
	index := g.getIndex(p)
	switch g.cells[index] {
	case Empty:
		g.cells[index] = fill
	case Solid:
		if fill == Solid {
			g.cells[index] = Empty
		}
	case Cross:
		if fill == Cross {
			g.cells[index] = Empty
		}
	case Note:
		if fill == Note {
			g.cells[index] = Empty
		} else {
			g.cells[index] = fill
		}
	}
}

func (g *Grid) drawGrid(cellSize int32, bounds *Bounds, color rl.Color) {
	for i := range g.nCols + 1 {
		x := i*cellSize + bounds.left
		rl.DrawLine(x, bounds.top, x, bounds.bottom, color)
	}
	for i := range g.nRows + 1 {
		y := i*cellSize + bounds.top
		rl.DrawLine(bounds.left, y, bounds.right, y, color)
	}
}

func (g *Grid) colorCells(cellSize int32, bounds *Bounds, style *Style) {
	for i := range g.nRows * g.nCols {
		x, y := g.getXY(i)
		cellBounds := bounds.getCellBoundsAt(x, y, cellSize)
		cellBounds.fillBounds(g.cells[i], style)
	}
}

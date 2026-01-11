package main

import (
	"fmt"
	rl "github.com/gen2brain/raylib-go/raylib"
	"slices"
)

type StateFn interface {
	setRec(rec *State)
	getRec() *State
	handleEvents() bool
	draw()
}

type State struct {
	fn       StateFn
	fill     FillType
	line     []Point
	grid     Grid
	bounds   Bounds
	cellSize int32
	drag     DragType
	style    Style
}

func newState(cellSize int32, nRows int32, nCols int32, bounds *Bounds) *State {
	g := newGrid(nRows, nCols)
	s := State{
		fn:       &HOME,
		fill:     Empty,
		line:     make([]Point, 0, nRows*nCols),
		grid:     *g,
		bounds:   *bounds.computeBounds(cellSize, g.nRows, g.nCols),
		cellSize: cellSize,
		drag:     Draw,
		style:    *newStyle(rl.RayWhite, rl.Color{R: 0x33, G: 0x33, B: 0x33, A: 0xff}, 2.0, 4.0),
	}
	fmt.Println(bounds)
	fmt.Println(s.bounds)
	return &s
}

func (s *State) declareStates(states ...StateFn) {
	for _, sf := range states {
		sf.setRec(s)
	}
}

func (s *State) findCellXY(v rl.Vector2) Point {
	return newPoint(int32((v.X-float32(s.bounds.left))/float32(s.cellSize)), int32((v.Y-float32(s.bounds.top))/float32(s.cellSize)))
}

func (s *State) addTempCell(p Point) {
	if len(s.line) == 0 {
		s.line = append(s.line, p)
		return
	}
	if slices.Contains(s.line, p) {
		return
	}
	index := s.grid.getIndex(&p)
	if (s.drag == Clear && s.grid.cells[index] == s.fill) || (s.drag == Draw && s.grid.cells[index] != s.fill) {
		s.line = append(s.line, p)
	}
}

func (s *State) colorTempCells() {
	var fill FillType
	if s.drag == Clear {
		fill = Empty
	} else {
		fill = s.fill
	}

	for _, p := range s.line {
		cellBounds := s.bounds.getCellBoundsAt(p.x, p.y, s.cellSize)
		cellBounds.fillBounds(fill, &s.style)
	}
}

package main

import rl "github.com/gen2brain/raylib-go/raylib"

type Bounds struct {
	left   int32
	right  int32
	top    int32
	bottom int32
}

func newBounds(left int32, right int32, top int32, bottom int32) *Bounds {
	b := Bounds{
		left:   left,
		right:  right,
		top:    top,
		bottom: bottom,
	}
	return &b
}

func (b *Bounds) computeBounds(cellSize int32, nRows int32, nCols int32) *Bounds {
	width := cellSize * nCols
	height := cellSize * nRows
	horizontalOffset := (b.right - b.left - width) / 2
	verticalOffset := (b.bottom - b.top - height) / 2
	newB := Bounds{
		left:   b.left + horizontalOffset,
		right:  b.right - horizontalOffset,
		top:    b.top + verticalOffset,
		bottom: b.bottom - verticalOffset,
	}
	return &newB
}

func (b *Bounds) getUpperAt(y int32, cellSize int32) int32 {
	return b.top + y*cellSize
}

func (b *Bounds) getLeftAt(x int32, cellSize int32) int32 {
	return b.left + x*cellSize
}

func (b *Bounds) getUpperLeftAt(x int32, y int32, cellSize int32) (int32, int32) {
	return b.getLeftAt(x, cellSize), b.getUpperAt(y, cellSize)
}

func (b *Bounds) getCellBoundsAt(x int32, y int32, cellSize int32) *Bounds {
	left, top := b.getUpperLeftAt(x, y, cellSize)
	return newBounds(left, left+cellSize, top, top+cellSize)
}

func (b *Bounds) drawSolid(color rl.Color) {
	cellSize := b.right - b.left
	rl.DrawRectangle(b.left, b.top, cellSize, cellSize, color)
}

func (b *Bounds) drawCross(thickness float32, color rl.Color) {
	rl.DrawLineEx(rl.NewVector2(float32(b.left), float32(b.top)), rl.NewVector2(float32(b.right), float32(b.bottom)), thickness, color)
	rl.DrawLineEx(rl.NewVector2(float32(b.left), float32(b.bottom)), rl.NewVector2(float32(b.right), float32(b.top)), thickness, color)
}

func (b *Bounds) drawNote(radius float32, color rl.Color) {
	cellSize := b.right - b.left
	rl.DrawCircle(b.left+cellSize/2, b.top+cellSize/2, radius, color)
}

func (b *Bounds) fillBounds(fill FillType, style *Style) {
	switch fill {
	case Solid:
		b.drawSolid(style.foreground)
	case Empty:
		b.drawSolid(style.background)
	case Cross:
		b.drawSolid(style.background)
		b.drawCross(style.thickness, style.foreground)
	case Note:
		b.drawSolid(style.background)
		b.drawNote(style.radius, style.foreground)
	}
}

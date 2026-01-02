# Nono File Specification

Nonograms are stored in `.nono` files.

**Warning:** No intermediate game state is stored, only the rules.

## Header

### Magic Bytes

`89 4e 4f 32 0d 0a`

### Version Number

`<version number (curr: 0x01)>`

### Flags

`<flags (1 byte)>`

| Bit | Value            |
|-----|------------------|
| 0   | Checksum Present |
| 1   | Unused           |
| 2   | Unused           |
| 3   | Unused           |
| 4   | Unused           |
| 5   | Unused           |
| 6   | Unused           |
| 7   | Unused           |


### Header Size

`10`

### Data Size

`<data size (4 byte, LE)>`

### Padding

`00 00 00`

## Data

### Row Count

`<row count (2 bytes)`

### Row

`<rule count (2 bytes)>` `<rule (2 bytes)>...`

### Column Count

`<column count>`

### Column

`<rule count (2 bytes)>` `<rule (2 bytes)>...`

## Checksum

`<checksum>`
# Nonogram Rule Format (.nono) \[v1.0\]

**Endianness:** Little-Endian

**Alignment:** 4-byte header, 2-byte data

## Header Structure (16 bytes)

| Offset | Size | Field       | Type    | Description                                                |
|--------|------|-------------|---------|------------------------------------------------------------|
| 0      | 6    | Magic Bytes | char[6] | `89 4E 4F 32 0D 0A`                                        |
| 6      | 1    | Version     | uint8   | Current version `0x01`                                     |
| 7      | 1    | Flags       | uint8   | See [**Flags**](#Flags) table                              |
| 8      | 1    | Header Size | uint8   | Fixed at `0x10`                                            |
| 9      | 3    | Padding     | byte[3] | Reserved; Must be `00 00 00`                               |
| 12     | 4    | Data Size   | uint32  | Total byte length of the [**Data**](#Data-Structure) block |

### Flags

| Bit | Name         | Description                                                                   |
|-----|--------------|-------------------------------------------------------------------------------|
| 0   | HAS_CHECKSUM | If set, a 4-byte CRC32 checksum follows the [**Data**](#Data-Structure) block |
| 1-7 | RESERVED     | Must be set to `0x00`                                                         |

## Data Structure

### Ruleset
*(Not used here; defined for reference below)*

| Field      | Size             | Description                        |
|------------|------------------|------------------------------------|
| Rule Count | 2 bytes          | Total number of rules in set ($N$) |
| Rules      | $N\times2$ bytes | $N$ consecutive 2-byte rules       |


### Row Definitions

| Field     | Size     | Description                                    |
|-----------|----------|------------------------------------------------|
| Row Count | 2 bytes  | Total number of [**Rulesets**](#Ruleset) ($M$) |
| Rulesets  | Variable | $M$ consecutive [**Rulesets**](#Ruleset)       |

### Column Definitions

| Field        | Size     | Description                                    |
|--------------|----------|------------------------------------------------|
| Column Count | 2 bytes  | Total number of [**Rulesets**](#Ruleset) ($K$) |
| Rulesets     | Variable | $K$ consecutive [**Rulesets**](#Ruleset)       |

## Checksum

If [**Flags**](#Flags) **Bit 0** is set, a checksum is present immediately following the [**Data**](#Data-Structure) block.

- **Type:** CRC32, 4 bytes
- **Scope:** [**Data**](#Data-Structure) block only

## Notes

- If [**Magic Bytes**](#Header-Structure-16-bytes) are altered in any way, file should be considered corrupted.

- No intermediate state is stored, only [**Rulesets**](#Ruleset) and their arrangement.

- Header size may be altered in future versions, prefer [**Header Size**](#Header-Structure-16-bytes) field.

- Empty rows/columns are treated as a ruleset with a single rule of 0, not an empty ruleset.

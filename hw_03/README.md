# Huffman archiver

## About

This is a small CLI archiver that uses [Huffman coding](https://en.wikipedia.org/wiki/Huffman_coding) to encode file's bytes.

## Build

Simply `make`

## Usage

```
program_name (-c | -u) -f input_file_name -o output_file_name [-v | -s]
```

`-c` or `-u` specifies whether you want to compress or decompress a file.

`-v` and `-s` stand for verbose and silent respectively.

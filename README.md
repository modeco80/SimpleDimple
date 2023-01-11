## SimpleDimple

A simple SAR1 utility written in C++20.

## Building

```bash
$ git clone https://github.com/modeco80/SimpleDimple.git
$ cd SimpleDimple
$ cmake -Bbuild -DCMAKE_BUILD_TYPE=Release
$ cmake --build build -j $(nproc)
# ... profit?
```

## The Libraries

### `libsd`

Provides IO readers and writers for data files, along with the structures.

Structure documentation is seperately managed as a .hexpat in [/hexpat](https://github.com/modeco80/SimpleDimple/tree/master/hexpat).

## The Tools

### `simpledimple`

The utility itself.


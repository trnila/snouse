# snouse - Raspberry Pico Snooze Mouse
Keeps your computer awake with simulated mouse activity.

## Build & flash
```sh
$ cmake -S . -B build
$ cmake --build build
$ picotool load -f build/snouse.uf2
```

## Build stl models
```sh
$ cmake -S . -B build && cmake --build build --target stls
```
Generated `.stls` are stored in `build/stls`.

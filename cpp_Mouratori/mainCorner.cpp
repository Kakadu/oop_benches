#include <benchmark/benchmark.h>
#include "shapes.h"

const int MAX_SHAPES_COUNT = 100;

u32 ShapesCount = 0;

shape_base **Shapes = nullptr;

static void DoSetupVTBL(const benchmark::State& state) {
    ShapesCount = MAX_SHAPES_COUNT;
    Shapes = initVTBL(ShapesCount, Shapes);
}

static void DoTeardownVTBL(const benchmark::State& state) {
    deinitVTBL(ShapesCount, Shapes);
    ShapesCount = 0;
}

static void BM_CornerAreaVTBL(benchmark::State& state) {
  for (auto _ : state)
    CornerAreaVTBL(ShapesCount, Shapes);
}

static void BM_CornerAreaVTBL4(benchmark::State& state) {
  for (auto _ : state)
    CornerAreaVTBL4(ShapesCount, Shapes);
}

BENCHMARK(BM_CornerAreaVTBL)->Setup(DoSetupVTBL)->Teardown(DoTeardownVTBL);
BENCHMARK(BM_CornerAreaVTBL4)->Setup(DoSetupVTBL)->Teardown(DoTeardownVTBL);

shape_union *ShapesSwitch = nullptr;

static void DoSetupSwitch(const benchmark::State&) {
    ShapesCount = MAX_SHAPES_COUNT;
    ShapesSwitch = initSwitch(ShapesCount, ShapesSwitch);
}

static void DoTeardownSwitch(const benchmark::State&) {
    deinitSwitch(ShapesCount, ShapesSwitch);
    ShapesSwitch = nullptr;
    ShapesCount = 0;
}

static void BM_CornerAreaSwitch(benchmark::State& state) {
  for (auto _ : state)
    CornerAreaSwitch(ShapesCount, ShapesSwitch);
}

static void BM_CornerAreaSwitch4(benchmark::State& state) {
  for (auto _ : state)
    CornerAreaSwitch4(ShapesCount, ShapesSwitch);
}

BENCHMARK(BM_CornerAreaSwitch)->Setup(DoSetupSwitch)->Teardown(DoTeardownSwitch);
BENCHMARK(BM_CornerAreaSwitch4)->Setup(DoSetupSwitch)->Teardown(DoTeardownSwitch);

static void DoSetupTable(const benchmark::State&) {
    ShapesCount = MAX_SHAPES_COUNT;
    ShapesSwitch = initSwitch(ShapesCount, ShapesSwitch);
}

static void DoTeardownTable(const benchmark::State&) {
    deinitSwitch(ShapesCount, ShapesSwitch);
    ShapesSwitch = nullptr;
    ShapesCount = 0;
}

static void BM_CornerAreaTable(benchmark::State& state) {
  for (auto _ : state)
    CornerAreaTable(ShapesCount, ShapesSwitch);
}

static void BM_CornerAreaTable4(benchmark::State& state) {
  for (auto _ : state)
    CornerAreaTable4(ShapesCount, ShapesSwitch);
}

BENCHMARK(BM_CornerAreaTable)->Setup(DoSetupTable)->Teardown(DoTeardownTable);
BENCHMARK(BM_CornerAreaTable4)->Setup(DoSetupTable)->Teardown(DoTeardownTable);


BENCHMARK_MAIN();

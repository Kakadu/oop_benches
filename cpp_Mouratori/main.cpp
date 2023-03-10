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

static void BM_TotalAreaVTBL(benchmark::State& state) {
  for (auto _ : state)
    TotalAreaVTBL(ShapesCount, Shapes);
}

static void BM_TotalAreaVTBL4(benchmark::State& state) {
  for (auto _ : state)
    TotalAreaVTBL4(ShapesCount, Shapes);
}

BENCHMARK(BM_TotalAreaVTBL)->Setup(DoSetupVTBL)->Teardown(DoTeardownVTBL);
BENCHMARK(BM_TotalAreaVTBL4)->Setup(DoSetupVTBL)->Teardown(DoTeardownVTBL);

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

static void BM_TotalAreaSwitch(benchmark::State& state) {
  for (auto _ : state)
    TotalAreaSwitch(ShapesCount, ShapesSwitch);
}

static void BM_TotalAreaSwitch4(benchmark::State& state) {
  for (auto _ : state)
    TotalAreaSwitch4(ShapesCount, ShapesSwitch);
}

BENCHMARK(BM_TotalAreaSwitch)->Setup(DoSetupSwitch)->Teardown(DoTeardownSwitch);
BENCHMARK(BM_TotalAreaSwitch4)->Setup(DoSetupSwitch)->Teardown(DoTeardownSwitch);

static void DoSetupTable(const benchmark::State&) {
    ShapesCount = MAX_SHAPES_COUNT;
    ShapesSwitch = initSwitch(ShapesCount, ShapesSwitch);
}

static void DoTeardownTable(const benchmark::State&) {
    deinitSwitch(ShapesCount, ShapesSwitch);
    ShapesSwitch = nullptr;
    ShapesCount = 0;
}

static void BM_TotalAreaTable(benchmark::State& state) {
  for (auto _ : state)
    TotalAreaTable(ShapesCount, ShapesSwitch);
}

static void BM_TotalAreaTable4(benchmark::State& state) {
  for (auto _ : state)
    TotalAreaTable4(ShapesCount, ShapesSwitch);
}

BENCHMARK(BM_TotalAreaTable)->Setup(DoSetupTable)->Teardown(DoTeardownTable);
BENCHMARK(BM_TotalAreaTable4)->Setup(DoSetupTable)->Teardown(DoTeardownTable);


BENCHMARK_MAIN();

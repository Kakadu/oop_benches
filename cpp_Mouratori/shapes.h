#pragma once

typedef float f32;
typedef size_t u32;

class shape_base;

shape_base** initVTBL(u32 count, shape_base** Shapes);
void deinitVTBL(u32 ShapesCount, shape_base** Shapes);

f32 TotalAreaVTBL(u32 ShapeCount, shape_base **Shapes);
f32 TotalAreaVTBL4(u32 ShapeCount, shape_base **Shapes);

f32 CornerAreaVTBL(u32 ShapeCount, shape_base **Shapes);
f32 CornerAreaVTBL4(u32 ShapeCount, shape_base **Shapes);

enum shape_type : u32 {
    ShapeSquare,
    ShapeRectanle,
    ShapeTriangle,
    ShapeCircle,
    ShapeCount
};
struct shape_union {
    shape_type Type;
    f32 Width;
    f32 Height;
};

shape_union* initSwitch(u32 count, shape_union* Shapes);
void deinitSwitch(u32 ShapesCount, shape_union* Shapes);

f32 TotalAreaSwitch(u32 ShapeCount, shape_union *Shapes);
f32 TotalAreaSwitch4(u32 ShapeCount, shape_union *Shapes);
f32 CornerAreaSwitch(u32 ShapeCount, shape_union *Shapes);
f32 CornerAreaSwitch4(u32 ShapeCount, shape_union *Shapes);

shape_union* initTable(u32 count, shape_union* Shapes);
void deinitTable(u32 ShapesCount, shape_union* Shapes);

f32 TotalAreaTable(u32 ShapeCount, shape_union *Shapes);
f32 TotalAreaTable4(u32 ShapeCount, shape_union *Shapes);
f32 CornerAreaTable(u32 ShapeCount, shape_union *Shapes);
f32 CornerAreaTable4(u32 ShapeCount, shape_union *Shapes);

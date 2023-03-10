#include <math.h>
#include <cassert>
#include "shapes.h"

const f32 Pi32 = M_PI;

class shape_base
{
public:
    shape_base() {}
    virtual f32 Area() = 0;
    virtual u32 CornerCount() = 0;
};


class square : public shape_base
{
public:
    square(f32 SideInit) : Side(SideInit) {}
    virtual f32 Area() { return Side*Side; }
    virtual u32 CornerCount() { return 4; }
private:
    f32 Side;
};

class rectangle: public shape_base
{
public:
    rectangle(f32 WidthInit, f32 HeightInit): Width(WidthInit), Height(HeightInit) {}
    virtual f32 Area() { return Width*Height; }
    virtual u32 CornerCount() { return 4; }
private:
    f32 Width, Height;
};

class triangle: public shape_base
{
public:
    triangle(f32 BaseInit, f32 HeightInit): Base(BaseInit), Height(HeightInit) {}
    virtual f32 Area() { return 0.5f * Base * Height; }
    virtual u32 CornerCount() { return 3; }
private:
    f32 Base, Height;
};

class circle: public shape_base
{
public:
    circle(f32 RadiusInit): Radius(RadiusInit) {}
    virtual f32 Area() { return Pi32 * Radius * Radius; }
    virtual u32 CornerCount() { return 0; }
private:
    f32 Radius;
};

shape_base** initVTBL(u32 ShapesCount, shape_base** Shapes) {
    Shapes = new shape_base*[100];
    for (u32 i=0; i<ShapesCount; ++i)
        switch (i%4) {
        case 0:
            Shapes[i] = new rectangle(5.0f, 4.0f);
            break;
        case 1:
            Shapes[i] = new triangle(5.0f, 5.0f);
            break;
        case 2:
            Shapes[i] = new square(5.0f);
            break;
        default:
            Shapes[i] = new circle(5.0f);
            break;
        }
    return Shapes;
}

void deinitVTBL(u32 ShapesCount, shape_base** Shapes) {
    for (u32 i=0; i<ShapesCount; ++i)
        delete Shapes[i];
    delete[] Shapes;
    Shapes = nullptr;
}

f32 TotalAreaVTBL(u32 ShapeCount, shape_base **Shapes)
{
    f32 acc = 0.0f;
    for (u32 i = 0; i<ShapeCount; ++i)
        acc += Shapes[i]->Area();
    return acc;
}

f32 CornerAreaVTBL(u32 ShapeCount, shape_base **Shapes)
{
    f32 acc = 0.0f;
    for (u32 i = 0; i<ShapeCount; ++i)
        acc += (1.f / (1.f + (f32)Shapes[i]->CornerCount())) *
                Shapes[i]->Area();
    return acc;
}

f32 TotalAreaVTBL4(u32 ShapeCount, shape_base **Shapes)
{
    f32 acc0 = 0.0f;
    f32 acc1 = 0.0f;
    f32 acc2 = 0.0f;
    f32 acc3 = 0.0f;

    u32 Count  = ShapeCount/4;
    while (Count--) {
        acc0 += Shapes[0]->Area();
        acc1 += Shapes[1]->Area();
        acc2 += Shapes[2]->Area();
        acc3 += Shapes[3]->Area();

        Shapes += 4;
    }
    return acc0 + acc1 + acc2 + acc3;
}

f32 CornerAreaVTBL4(u32 ShapeCount, shape_base **Shapes)
{
    f32 acc0 = 0.0f;
    f32 acc1 = 0.0f;
    f32 acc2 = 0.0f;
    f32 acc3 = 0.0f;

    u32 Count  = ShapeCount/4;
    while (Count--) {
        acc0 += (1.f / (1.f + (f32)Shapes[0]->CornerCount())) *
                Shapes[0]->Area();
        acc1 += (1.f / (1.f + (f32)Shapes[1]->CornerCount())) *
                Shapes[1]->Area();
        acc2 += (1.f / (1.f + (f32)Shapes[2]->CornerCount())) *
                Shapes[2]->Area();
        acc3 += (1.f / (1.f + (f32)Shapes[3]->CornerCount())) *
                Shapes[3]->Area();

        Shapes += 4;
    }
    return acc0 + acc1 + acc2 + acc3;
}

/* ****************** Switches ********************************************** */

shape_union* initSwitch(u32 ShapesCount, shape_union* Shapes) {
    Shapes = new shape_union[100];
    for (u32 i=0; i<ShapesCount; ++i)
        switch (i%4) {
        case 0:
            Shapes[i].Type = ShapeRectanle;
            Shapes[i].Width = 5.0f;
            Shapes[i].Height = 4.0f;
            break;
        case 1:
            Shapes[i].Type = ShapeTriangle;
            Shapes[i].Width = 5.0f;
            Shapes[i].Height = 4.0f;
            break;
        case 2:
            Shapes[i].Type = ShapeSquare;
            Shapes[i].Width = 5.0f;
            Shapes[i].Height = 0.0f;
            break;
        default:
            Shapes[i].Type = ShapeCircle;
            Shapes[i].Width = 5.0f;
            break;
        }
    return Shapes;
}

void deinitSwitch(u32 ShapesCount, shape_union* Shapes) {
    delete[] Shapes;
    Shapes = nullptr;
}

f32 GetAreaSwitch(shape_union Shape)
{
    f32 Result = 0.0f;
    switch (Shape.Type)
    {
    case ShapeSquare:
        Result = Shape.Width * Shape.Width;
        break;
    case ShapeRectanle:
        Result = Shape.Width * Shape.Height;
        break;
    case ShapeTriangle:
        Result = 0.5f * Shape.Width * Shape.Height;
        break;
    case ShapeCircle:
        Result = Pi32 * Shape.Width * Shape.Width;
        break;
     case ShapeCount: break;
    }
    return Result;
}

f32 GetCornerCountSwitch(shape_union Shape)
{
    f32 Result = 0.0f;
    switch (Shape.Type)
    {
    case ShapeSquare:
        Result = 4;
        break;
    case ShapeRectanle:
        Result = 4;
        break;
    case ShapeTriangle:
        Result = 3;
        break;
    case ShapeCircle:
        Result = 0;
        break;
     case ShapeCount: break;
    }
    return Result;
}

f32 TotalAreaSwitch(u32 ShapeCount, shape_union *Shapes)
{
    f32 acc = 0.0f;
    for (u32 i = 0; i<ShapeCount; ++i)
        acc += GetAreaSwitch(Shapes[i]);
    return acc;
}

f32 TotalAreaSwitch4(u32 ShapeCount, shape_union *Shapes)
{
    f32 acc0 = 0.0f;
    f32 acc1 = 0.0f;
    f32 acc2 = 0.0f;
    f32 acc3 = 0.0f;

    u32 Count  = ShapeCount/4;
    while (Count--) {
        acc0 += GetAreaSwitch(Shapes[0]);
        acc1 += GetAreaSwitch(Shapes[1]);
        acc2 += GetAreaSwitch(Shapes[2]);
        acc3 += GetAreaSwitch(Shapes[3]);

        Shapes += 4;
    }
    return acc0 + acc1 + acc2 + acc3;
}

f32 CornerAreaSwitch(u32 ShapeCount, shape_union *Shapes)
{
    f32 acc = 0.0f;
    for (u32 i = 0; i<ShapeCount; ++i)
        acc += (1.f / (1.f + (f32)GetCornerCountSwitch(Shapes[i]))) *
                GetAreaSwitch(Shapes[i]);
    return acc;
}

f32 CornerAreaSwitch4(u32 ShapeCount, shape_union *Shapes)
{
    f32 acc0 = 0.0f;
    f32 acc1 = 0.0f;
    f32 acc2 = 0.0f;
    f32 acc3 = 0.0f;

    u32 Count  = ShapeCount/4;
    while (Count--) {
        acc0 += (1.f / (1.f + (f32)GetCornerCountSwitch(Shapes[0]))) *
                GetAreaSwitch(Shapes[0]);
        acc1 += (1.f / (1.f + (f32)GetCornerCountSwitch(Shapes[0]))) *
                GetAreaSwitch(Shapes[0]);
        acc2 += (1.f / (1.f + (f32)GetCornerCountSwitch(Shapes[0]))) *
                GetAreaSwitch(Shapes[0]);
        acc3 += (1.f / (1.f + (f32)GetCornerCountSwitch(Shapes[0]))) *
                GetAreaSwitch(Shapes[0]);

        Shapes += 4;
    }
    return acc0 + acc1 + acc2 + acc3;
}
/* ************ Tables ********************************************* */

shape_union* initTable(u32 ShapesCount, shape_union* Shapes) {
    return initSwitch(ShapesCount, Shapes);
}

void deinitTable(u32 ShapesCount, shape_union* Shapes) {
    deinitTable(ShapesCount, Shapes);
}

f32 const CTable[ShapeCount] = { 1.0f, 1.0f, 0.5f, Pi32 };

f32 GetAreaTable(shape_union Shape)
{
    return CTable[Shape.Type] * Shape.Width * Shape.Width;
}

f32 const CCornerTable[ShapeCount] = {
    1.0f / (1.0f + 4.0f),
    1.0f / (1.0f + 4.0f),
    0.5f / (1.0f + 3.0f),
    Pi32
};

f32 GetCornerAreaTable(shape_union Shape)
{
    return CCornerTable[Shape.Type] * Shape.Width * Shape.Width;
}

f32 TotalAreaTable(u32 ShapeCount, shape_union *Shapes)
{
    f32 acc = 0.0f;
    for (u32 i = 0; i<ShapeCount; ++i)
        acc += GetAreaTable(Shapes[i]);
    return acc;
}

f32 TotalAreaTable4(u32 ShapeCount, shape_union *Shapes)
{
    f32 acc0 = 0.0f;
    f32 acc1 = 0.0f;
    f32 acc2 = 0.0f;
    f32 acc3 = 0.0f;

    u32 Count  = ShapeCount/4;
    while (Count--) {
        acc0 += GetAreaTable(Shapes[0]);
        acc1 += GetAreaTable(Shapes[1]);
        acc2 += GetAreaTable(Shapes[2]);
        acc3 += GetAreaTable(Shapes[3]);

        Shapes += 4;
    }
    return acc0 + acc1 + acc2 + acc3;
}

f32 CornerAreaTable(u32 ShapeCount, shape_union *Shapes)
{
    f32 acc = 0.0f;
    for (u32 i = 0; i<ShapeCount; ++i)
        acc += GetCornerAreaTable(Shapes[i]);
    return acc;
}

f32 CornerAreaTable4(u32 ShapeCount, shape_union *Shapes)
{
    f32 acc0 = 0.0f;
    f32 acc1 = 0.0f;
    f32 acc2 = 0.0f;
    f32 acc3 = 0.0f;

    u32 Count  = ShapeCount/4;
    while (Count--) {
        acc0 += GetCornerAreaTable(Shapes[0]);
        acc1 += GetCornerAreaTable(Shapes[1]);
        acc2 += GetCornerAreaTable(Shapes[2]);
        acc3 += GetCornerAreaTable(Shapes[3]);

        Shapes += 4;
    }
    return acc0 + acc1 + acc2 + acc3;
}

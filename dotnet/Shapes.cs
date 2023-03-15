using System.Text;
using BenchmarkDotNet.Attributes;
using BenchmarkDotNet.Running;

abstract class Shapes {
  public float Width  { get; set; }
  public float Height { get; set; }
  public abstract float Area();
  public abstract uint CornerCount();
}

class Square : Shapes {
  public Square(float Width) {
    this.Width = this.Height = Width;
  }
  public override float Area() { return Width * Width; }
  public override uint CornerCount() { return 4; }
}

class Rectangle : Shapes {
  public Rectangle(float Width, float Height ) {
    this.Width = Width;
    this.Height = Height;
  }
  public override float Area()  { return Width * Height; }
  public override uint CornerCount() { return 4; }
}

class Circle : Shapes {
  public Circle(float Radius) {
    this.Width = Radius;
  }
  public override float Area()  { return Width / 2 * (float)Math.PI; }
  public override uint CornerCount() { return 0; }
}

class Triangle : Shapes {
  public Triangle(float Width, float Height) {
    this.Width = Width;
    this.Height = Height;
  }
  public override float Area() { return Width * Height / 2; }
  public override uint CornerCount() { return 3; }
}

class ShapesBench {
  public static float TotalAreaVTBL(uint Count, Shapes[] arr) {
    var acc = 0.0f;
    foreach (var s in arr)
      acc += s.Area();
    return acc;
  }
  public static float CornerAreaVTBL(uint Count, Shapes[] arr) {
    var acc = 0.0f;
    foreach (var s in arr)
      acc += (1.0f / (1.0f + s.CornerCount())) * s.Area();
    return acc;
  }

}

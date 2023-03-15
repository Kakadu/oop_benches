using System.Text;
using BenchmarkDotNet.Attributes;
using BenchmarkDotNet.Running;

[MemoryDiagnoser]
public class Program
{
/*
    int n = 10_000;

    [Benchmark]
    public string Builder()
    {
        StringBuilder output = new StringBuilder();

        for (int i = 0; i < n; i++)
        {
            output.Append("falcon").Append(i);
        }

        return output.ToString();
    }

    [Benchmark]
    public string Interpolation()
    {
        string output = string.Empty;

        for (int i = 0; i < n; i++)
        {
            output = $"{output}falcon{i}";
        }

        return output;
    }

    [Benchmark]
    public string Addition()
    {
        string output = string.Empty;

        for (int i = 0; i < n; i++)
        {
            output += "falcon" + i;
        }

        return output.ToString();
    }
*/
    Shapes[] array = null;
    uint ShapesCount = 100;

    [GlobalSetup]
    public void Setup()
    {
        array = new Shapes[ShapesCount];
        for (var i=0; i<ShapesCount; i++) {
          switch (i%4) {
            case 0: array[i] = new Rectangle(5.0f, 4.0f); break;
            case 1: array[i] = new Triangle(5.0f, 4.0f); break;
            case 2: array[i] = new Square(5.0f); break;
            default: array[i] = new Circle(5.0f);
              break;
          }
        }
    }
    [Benchmark]
    public void TotalAreaVTBL()
    {
        ShapesBench.TotalAreaVTBL(ShapesCount, array);
    }
    static void Main(string[] args)
    {
        var summary = BenchmarkRunner.Run<Program>();
        //var x = new Shapes();
    }
}

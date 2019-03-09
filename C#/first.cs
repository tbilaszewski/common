using System;
using System.Collections.Generic;

public class Greetings 
    {
        private String className;
        public int number;
        
        public Greetings( String name ) => Name = name;

        public string Name
        {
            get => className;
            set => className = value;
        }
        public void print() 
        {
            Console.WriteLine("heeeelllo, "+ this.className);
        }
    }

public class Shape
{
    public string color { get; protected set;}

    public Shape() => this.color = "not specified";

    public virtual void draw()
    {
        Console.WriteLine("Default draw()"+this.color);
    }
}

public class Rectangle : Shape
{
    public Rectangle(string color) => this.color = color;
    public Rectangle() => this.color = base.color;
    public override void draw() 
    {
        Console.WriteLine("Rectangle "+this.color);
    }
}
public class Square : Rectangle
{
    public Square(string color) => this.color = color;
    public Square() => this.color = base.color;
    public override void draw() 
    {
        Console.WriteLine("Square "+this.color);
    }
}
public class Triangle : Shape
{
    public Triangle(string color) => this.color = color;
    public Triangle() => this.color = base.color;
    public override void draw() 
    {
        Console.WriteLine("Triangle "+this.color);
    }
}

public class Circle : Shape
{
    public Circle(string color) => this.color = color;
    public Circle() => this.color = base.color;
    public override void draw() 
    {
        Console.WriteLine("Circle "+this.color);
    }
}


class Program {
    
    
  static void Main() 
  {
      Greetings Greeting = new Greetings("tomek");
      
      Greeting.print();
      Greeting.number = 1;
      Console.WriteLine(Greeting.number);

    Console.WriteLine("-----------------");

    Shape shape_def = new Shape();
    var shapes = new List<Shape>
        {
            new Square("red"),
            new Triangle("green"),
            new Circle(),
            new Rectangle("red")
        };
    foreach (var shape in shapes)
    {
        shape.draw();
        
    }

      
  }
}

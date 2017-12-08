	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <math.h>

// my methods all return type double and they only take the this parameter

	typedef double (*VirtualMethodPointer)(void *);
	//(*VirtualMethodPointer is a pointer point to a Virtual function)
	//return type for the pointed function is double
	//void * means the argument can be any type of pointer.


	typedef VirtualMethodPointer * VTableType;
	//Vpointer points to Vtable

// Start of Class Shape

	#define PI 3.14159

	typedef struct Shape Shape;

	struct Shape
	{
	    VTableType VPointer;
	    char name[40];
	};

	double area(Shape * _this)
    {
        return 0.0;
    }

    double draw(Shape * _this)
    {
    	printf("you should never see this");
        return 0.0;
    }

    VirtualMethodPointer Shape_VTable [] =
    {
        (VirtualMethodPointer)area, // VTable[0] - the first virtual method
        (VirtualMethodPointer)draw // VTable[1] - the second virtual method
    };

    Shape * Shape_Shape(Shape * _this, char n[])
    {
        _this->VPointer = Shape_VTable;
        strcat(_this->name,"        ");
        strcat(_this->name,n);
        // Constructors usually return void, but it makes the example simpler
        return _this;
    }

// Start of Circle Class
    typedef struct Circle Circle;
    struct Circle
        // extends Shape
    {
        VTableType VPointer;
        double radius;
        char name[40];
    };

    double Circle_area(Circle * _this)
    {
        return PI * _this->radius * _this->radius;
    }
    double Circle_draw(Circle *_this)
    {
    	printf("%s: radius = %0.0f\n",_this->name,_this->radius);
		double center_x= _this->radius,center_y =_this->radius;
		for(double y = 2*_this->radius; y> 0; y--)
		{
			for(double x = 0; x<2* _this->radius; x++)
			{
				double differ = (x-center_x)*(x-center_x)+
						(y-center_y)*(y-center_y);
				differ = sqrt(differ);
				//System.out.print(differ);
			
				if(fabs(differ)<_this->radius)
				{
					printf("* ");
				}
				else
				{
					printf("  ");
				}
			}
			printf("\n");
		}
		printf("\n");
		return 0.0;
    }

    VirtualMethodPointer Circle_VTable [] =

    {
        (VirtualMethodPointer)Circle_area, // Over-ride area
        (VirtualMethodPointer)Circle_draw // over-ride draw
    };


    Circle * Circle_Circle(Circle * _this, double newRadius, char n[])
    {
        Shape_Shape((Shape *)_this, n); // call parents constructor
        _this->radius = newRadius;
        _this->VPointer = Circle_VTable; // set the vpointer AFTER parent
        return _this;
    }

// Start of Triangle Class
    typedef struct Triangle Triangle;
    struct Triangle
        // extends Shape
    {
        VTableType VPointer;
        double myHeight;
        double myBase;
        char name[40];
    };

    double Triangle_area(Triangle * _this)
    {
        return _this->myHeight* _this->myBase/2;
    }
    double Triangle_draw(Triangle *_this)
    {
    	printf("%s: height = %0.0f, base = %0.0f\n",_this->name,_this->myHeight,_this->myBase);
		for(double h = 1; h<= _this->myHeight; h++)
		{
			double numPerLine = h/_this->myHeight * _this->myBase;
			//System.out.print(numPerLine);
			for(int i = 0; i<numPerLine; i++)
			{
				printf("*");	
			}
			printf("\n");
		}
		printf("\n");
		return 0.0;
    }

    VirtualMethodPointer Triangle_VTable [] =

    {
        (VirtualMethodPointer)Triangle_area, // Over-ride area
        (VirtualMethodPointer)Triangle_draw // over-ride draw
    };


    Triangle * Triangle_Triangle(Triangle * _this, double myH, double myB, char n[])
    {
    	char temp[40] = "        ";
    	strcat(temp,n);
        Shape_Shape((Shape *)_this, temp); // call parents constructor
        _this->myHeight = myH;
        _this->myBase = myB;
        _this->VPointer = Triangle_VTable; // set the vpointer AFTER parent
        return _this;
    }


// Start of Square Class
    typedef struct Square Square;
    struct Square
        // extends Shape
    {
        VTableType VPointer;
        double side;
        char name[40];
    };

    double Square_area(Square * _this)
    {
        return _this->side * _this->side;
    }
    double Square_draw(Square *_this)
    {
    	printf("%s:side = %0.0f\n",_this->name, _this->side);
		for(int i = 0; i<_this->side;i++)
		{
			for(int m = 0; m<_this->side; m++)
			{
				printf("* ");
			}
			printf("\n");
		}
		printf("\n");
		return 0.0;
    }

    VirtualMethodPointer Square_VTable [] =

    {
        (VirtualMethodPointer)Square_area, // Over-ride area
        (VirtualMethodPointer)Square_draw // over-ride draw
    };


    Square * Square_Square(Square * _this, double s, char n[])
    {
        Shape_Shape((Shape *)_this, n); // call parents constructor
        _this->side = s;
        _this->VPointer = Square_VTable; // set the vpointer AFTER parent
        return _this;
    }



// Start of Rectangle Class
    typedef struct Rectangle Rectangle;
    struct Rectangle
        // extends Shape
    {
        VTableType VPointer;
        double width;
        double height;
        char name[40];
    };

    double Rectangle_area(Rectangle * _this)
    {
        return _this->height * _this->width;
    }
    double Rectangle_draw(Rectangle *_this)
    {
    	printf("%s:height = %0.0f, width = %0.0f\n", _this->name,_this->height,_this->width);
		for(int m = 1; m<= _this->height; m++)
		{
			for(int i = 1; i<= _this->width; i++)
			{
				printf("* ");
			}
		printf("\n");
		}
		printf("\n");
		return 0.0;
    }

    VirtualMethodPointer Rectangle_VTable [] =

    {
        (VirtualMethodPointer)Rectangle_area, // Over-ride area
        (VirtualMethodPointer)Rectangle_draw // over-ride draw
    };


    Rectangle * Rectangle_Rectangle(Rectangle * _this, double h, double w, char n[])
    {
    	char temp[40] = "        ";
    	strcat(temp,n);
        Shape_Shape((Shape *)_this, temp); // call parents constructor
        _this->height = h;
        _this->width = w;
        _this->VPointer = Rectangle_VTable; // set the vpointer AFTER parent
        return _this;
    }







	int main()
	{
        Shape * s = (Shape *)Circle_Circle((Circle *)calloc(1,sizeof(Circle)), 5.0, "FirstCircle");
        (s->VPointer[1])(s);
		/*
		Circle * c;
		Triangle * t;
		Square * s;
		Rectangle * r;
	
		c = Circle_Circle((Circle *)malloc(sizeof(Circle)), 10.0, "FirstCircle");
		printf("%s area : is %0.2f\n", c->name,(c->VPointer[0])(c));
		(c->VPointer[1])(c);
		t = Triangle_Triangle((Triangle *)malloc(sizeof(Triangle)), 5,5, "FirstTriangle");
		printf("%s area : is %0.2f\n", t->name,(t->VPointer[0])(t));
		(t->VPointer[1])(t);
		s = Square_Square((Square *)malloc(sizeof(Square)), 5, "FirstSquare");
		printf("%s area : is %0.2f\n", s->name,(s->VPointer[0])(s));
		(s->VPointer[1])(s);
		r = Rectangle_Rectangle((Rectangle *)malloc(sizeof(Rectangle)), 10,5, "FirstRectangle");
		printf("%s area : is %0.2f\n", r->name,(r->VPointer[0])(r));
		(r->VPointer[1])(r);
		*/


		Shape * a [] = {
			(Shape *)Triangle_Triangle((Triangle *)calloc(1,sizeof(Triangle)), 5,5, "FirstTriangle"),
			(Shape *)Triangle_Triangle((Triangle *)calloc(1,sizeof(Triangle)), 4,3, "SecondTriangle"),
        	(Shape *)Circle_Circle((Circle *)calloc(1,sizeof(Circle)), 5.0, "FirstCircle"),
        	(Shape *)Circle_Circle((Circle *)calloc(1,sizeof(Circle)), 10.0, "SecondCircle"),
        	(Shape *)Square_Square((Square *)calloc(1,sizeof(Square)), 5, "FirstSquare"),
        	(Shape *)Square_Square((Square *)calloc(1,sizeof(Square)), 10, "SecondSquare"),
        	(Shape *)Rectangle_Rectangle((Rectangle *)calloc(1,sizeof(Rectangle)), 4,8, "FirstRectangle"),
        	(Shape *)Rectangle_Rectangle((Rectangle *)calloc(1,sizeof(Rectangle)), 8,4, "SecondRectangle"),
        };

    double total_area = 0;
    for (int i=0; i<sizeof(a)/sizeof(*a); i++)
    {
        total_area = total_area + (a[i]->VPointer[0])(a[i]);
    }

    for (int i=0; i<sizeof(a)/sizeof(*a); i++)
    {
        (a[i]->VPointer[1])(a[i]);
        free(a[i]);
    }
    printf("The total area of the shapes on this picture is %0.3f square units.\n", total_area);
		return 0;
};






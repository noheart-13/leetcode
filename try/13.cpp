class Cube :public Container
{
public:
	Cube(double a) :Container(a) {}
	double area()
	{
		return 6 * radius * radius;
	}
	double volume()
	{
		return radius * radius * radius;
	}
	void print()
	{
		cout << "the sidelength of cube is:" << radius << endl << "the area of cube is:" << 6 * radius * radius << endl << "the volume of cube is:" << radius * radius * radius << endl;
	}
};
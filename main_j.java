// We generate the thisfile.h with:
// javac thisfile.java
// javah thisfile
// In Java an externa wrapper is mandatory

public class main_j {
	native int square(int i);
	native int cube(int i);
	native void print(int i, double [] array);
	native void printstr(String str);

	static {
		System.loadLibrary("modulejava");
    }

	static public void main(String argv[])
	{
		// First Part
		main_j libfun = new main_j() ;

		for(int i = 0; i < 5; ++i) {
			System.out.printf("%d\tx^2=%2d\tx^3=%2d\n",
							  i,libfun.square(i),libfun.cube(i));
		}

		// Second part
		int size = 6;
		double[] array = new double[size];

		for(int i = 0; i < size; ++i)
			array[i] = i + 1;

		libfun.print(size, array);

		// Third part
		String str="my string";
		libfun.printstr(str);
    }

}

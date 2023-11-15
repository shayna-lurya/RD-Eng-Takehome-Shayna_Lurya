/*
This program is supplement to the Programming Exercise "Find Closest Shape" here:
https://mail.google.com/mail/u/0/#inbox/FMfcgzGwHflsSfCDWbnZnXmprLXfdQCM?projector=1&messagePartId=0.1

Here we complete a portion of Step 1: 
 - Generate a 2D matrix of a size determined by user input.
 - Initialize number of shapes to be printed in the matrix. 
 - The matrix is populated with a random distribution of 1's and 0's.

Notes:
- The implementation is not complete, but I am prepared to discuss the potential solutions during the interview!
- I aim to demonstrate my understanding of object oriented programming, data structures, and algorithms.
- This file should be split into .h and .cpp files. 
- Sources: I reviewed lecture slides from my CS curriculum at UCLA: http://careynachenberg.weebly.com/cs-slides.html
*/

#include <iostream>
#include <unordered_set>
#include <vector>
#include <ctime>   // For time() function
using namespace std;

// Define a struct to represent points in 2D space
struct Point
{
    int x;
    int y;
    int value;

    Point(int x, int y, int value) : x(x), y(y), value(value) {}
};

// Util for displaying matrices.
void displayMatrix(const vector<vector<int> > &matrix)
{
    for (const auto &row : matrix)
    {
        for (int value : row)
        {
            cout << value << " ";
        }
        cout << endl;
    }
}

// Test that a shape is in a straight line:
// If the number of unique values in both X and Y coordinates is 1 or less, then the line is straight.
// This doesn't work right now because it doesn't actually access the value of the points. 
bool isShapeStraightLine(const vector<Point> &points)
{
    unordered_set<int> xCoords;
    unordered_set<int> yCoords;

    for (const Point &point : points)
    {
        xCoords.insert(point.x);
    }

    for (const Point &point : points)
    {
        yCoords.insert(point.y);
    }

    if (xCoords.size() > 1 && yCoords.size() > 1)
    { // Not a straight line
        cout << "The shape is not in a straight line." << endl;
        return false;
    }
    else
    {
        cout << "The shape is in a straight line" << endl;
        return true;
    }
};

int main()
{

    // Get user input for height and width
    int height, width, shapes;
    cout << "Enter the height of the 2D array: ";
    cin >> height;

    cout << "Enter the width of the 2D array: ";
    cin >> width;

    // The number of allowed shapes depends on the size of the matrix.
    // We will define the maximum number of shapes as 1/4th the number of total points in the matrix (width*height).
    // Constraints on shapes:
    // Shapes must have at least two consecutive points.
    // There must exist at least one shape that is not a straight line. Therefore, one shape must contain three points.
    // Therefore a 4x3 matrix would have 3 shapes max (3*4)/4.
    // Input
    // {{0, 0, 0, 0},
    //  {0, 0, 0, 0},
    //  {0, 0, 0, 0}}
    // Output with 3 shapes.
    // {{1, 1, 0, 2},
    //  {0, 1, 0, 2},
    //  {3, 3, 3, 0}}

    // Validate input for shapes.
    int max_num_shapes = (width * height) / 4;
    cout << "Enter the number of shapes. Value must be between 1 and " << max_num_shapes << ": ";
    cin >> shapes;
   
    while (shapes > max_num_shapes)
    {
        cout << "Invalid input. Value must be between 1 and " << max_num_shapes << ":" << endl;
        cin >> shapes;
    }

    // Here we generate a random matrix of 1s by creating Points.
    // These points could be stored in a Shapes container.
    // Details on random shape generation are at bottom of file.

    // We could have a vector of point vectors to represent shapes.
    vector<vector<Point> > shapeVector;
    vector<Point> shape;
    
    vector<vector<int> > matrix(height, vector<int>(width, 0));

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {

            // Do a 50/50 coin toss on whether to place a 1 or a 0.
            Point newPoint(height, width, 0);

            if (rand() % 2 == 0){
                newPoint = Point(height, width, 1);
                matrix[i][j]=1;
            }
            else{
              newPoint = Point(height, width, 0);
              matrix[i][j]=0;
            }
        shape.push_back(newPoint);
        }
        // Push this coordinate to a vector representing this shape.
        // In this case there will be only one shape.
    }
    // When the shape is complete, add the shape to a container so it may be added to the final matrix.
    shapeVector.push_back(shape);

    // Display our matrix.
    cout << "Input matrix" << endl;
    displayMatrix(matrix);

    // To generate the desired output matrix with shape detection, I believe we would a convolutional filter or transform.
    // Numpy and Pytorch contain libraries that could accomplish this more easily.
    // I would experiment with a filter to instantiate Sobel edge detection. Something like this:
         // int filter[3][3] = {{0, 1, 0},
        //                     {1, -1, 1},
        //                     {0, 1, 0}};
    

    // Tests
    // isShapeStraightLine should return true if the shape is straight, false if it is not.
    // It does not function as of now, but here is a sample instantiation:


    // Test bool isShapeStraightLine(const vector<Point> &points)
    vector<vector<int> > shapeNotStraight(3, vector<int>(3, 0));
    vector<vector<int> > shapeStraight(3, vector<int>(3, 0));
    vector<Point> notStraight;
    vector<Point> Straight;

    // Generate matrix that does NOT have straight line:
    // {{0,1,0},
    //  {0,1,0},
    //  {0,1,1}},

    // IsShapeStraightLine should return false.

    //Initialize matrix and call function.

        
    for(int i=0; i<3; i++){
            for(int j = 0; j < 3; j++){
                if(j==1){
                    notStraight.push_back(Point(i,j,1));
                    shapeNotStraight[i][j] = 1;
                
                }
            }
        }
     // Make this not straight by adding a 1 at the corner.
     shapeNotStraight[2][2] = 1;

    isShapeStraightLine(notStraight);
    displayMatrix(shapeNotStraight);
    
    // Generate straight vertical line 3x3 matrix.
    // Straight line:
    // {{0,1,0},
    //  {0,1,0},
    //  {0,1,0}},

    // IsShapeStraightLine should return true.
    for(int i=0; i<3; i++){
            for(int j = 0; j < 3; j++){
                if(j==1){
                    Straight.push_back(Point(i,j,1));
                    shapeStraight[i][j] = 1;
                }
                
            }
        }

    isShapeStraightLine(Straight);
    displayMatrix(shapeStraight);

    return 0;

}

// Steps to generate random matrix:
// For each number of shapes, add Points to a vector.
// At the end, push vector to matrix and display.
// Make decision using weights:
// 1. Do nothing (0)
// 2. Add new shape.
// 3. Add to current shape.
// Some to consider for weight activation:
// - Check the position of points to the left and above.
  // - Does this point belong to another shape?
  // - Is the current shape complete (has at least three points)
  // - How many shapes are remaining in proportion to number of remaining spaces?
  // - Does there exist a shape that is not a straight line?
  // - Do there exist two shapes that touch?

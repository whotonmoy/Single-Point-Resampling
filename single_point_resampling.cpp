#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void resizeImage(const char* inputFileName, const char* outputFileName, int originalWidth, int originalHeight, int newWidth, int newHeight);

int main()
{
    // Input FileName name hard coded because I could not get it to cin the file name.
    // Input FileName must be changed in the code to the name of the input file to get the desired result
    const char* inputFileName = "museum.raw";
    const char* outputFileName = "resized_picture.raw";
    int originalWidth, originalHeight, newWidth, newHeight;

    /*cout << "Enter the name of the File with the extension" << endl;*/
    
    // Enter the size of the picture that is being used
    cout << "\nEnter the Original Width and Height of the picture respectively" << endl;
    cin >> originalWidth;
    cin >> originalHeight;

    // Enter the new size of the picture that is to be achieved after resizing 
    cout << "\nEnter the New Width and Height of the picture respectively" << endl;
    cin >> newWidth;
    cin >> newHeight;

    // Resize the image and save it to the output file
    resizeImage(inputFileName, outputFileName, originalWidth, originalHeight, newWidth, newHeight);

    cout << "Image resized and saved to " << outputFileName << endl;

    return 0;
}

// Function to resize an image using single-point resampling
void resizeImage(const char* inputFileName, const char* outputFileName, int originalWidth, int originalHeight, int newWidth, int newHeight)
{
    // Calculate the scaling factors for width and height
    double scaleX = (double)newWidth / originalWidth;
    double scaleY = (double)newHeight / originalHeight;

    // Open the input file for reading
    ifstream inputFile(inputFileName, ios::binary);
    if (!inputFile.is_open()) {
        cerr << "Error: Cannot open input file." << endl;
        return;
    }

    // Open the output file for writing
    ofstream outputFile(outputFileName, ios::binary);
    if (!outputFile.is_open()) {
        cerr << "Error: Cannot create output file." << endl;
        return;
    }

    // Calculate the new image data size
    int newSize = newWidth * newHeight;

    // Read the input image data into a vector
    vector<unsigned char> imageData(originalWidth * originalHeight);
    inputFile.read(reinterpret_cast<char*>(&imageData[0]), imageData.size());

    // Create a vector for the resized image data
    vector<unsigned char> resizedImageData(newSize);

    // Perform the single-point resampling
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            // Calculate the corresponding position in the original image
            int srcX = static_cast<int>(x / scaleX);
            int srcY = static_cast<int>(y / scaleY);

            // Calculate the index for the original image
            int srcIndex = srcY * originalWidth + srcX;

            // Calculate the index for the resized image
            int dstIndex = y * newWidth + x;

            // Copy the pixel value from the original to the resized image
            resizedImageData[dstIndex] = imageData[srcIndex];
        }
    }

    // Write the resized image data to the output file
    outputFile.write(reinterpret_cast<char*>(&resizedImageData[0]), newSize);
}
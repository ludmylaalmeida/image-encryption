#include <iostream>
#include <string>
#include "FibLFSR.hpp"
#include <SFML/Graphics.hpp>

using namespace std;

void transform( sf::Image& image, FibLFSR* seed){

    sf::Uint8 red_substitute, green_substitute, blue_substitute;

    /* image width */
    int width = image.getSize().x;
    /* image height */
    int height = image.getSize().y;

    int new_int = 0;

    // for each pixel (x, y) extract the red, green and blue
    for( int i = 0; i != width; i++){
        for( int j = 0; j != height ; j++ ){

            sf::Color pixel = image.getPixel(i,j);

            /* get red component */
            new_int = seed->generate(30);
            red_substitute = pixel.r ^ ((sf::Uint8)new_int);

            /* get green component */
            new_int = seed->generate(30);
            green_substitute = pixel.g ^ ((sf::Uint8)new_int);

            /* get blue component */
            new_int = seed->generate(30);
            blue_substitute = pixel.b ^ ((sf::Uint8)new_int);

            /* Create new Color */
            sf::Color new_color(red_substitute, green_substitute, blue_substitute);

            /* Set new color */
            image.setPixel(i, j, new_color);
        }
    }
}


int main() {

    /* source filename */
    string original_file;

    /* output filename */
    string encryption_file;

    /* FibLFSR seed */
    string seed;

    /* Read three arguments from the command line: source image filename, output image filename, and FibLFSR seed. */
    cin >> original_file >> encryption_file >> seed;

    sf::Image image;
    image.loadFromFile(original_file);

    /* seed */
    FibLFSR fibLfsr(seed);

    /* create windows */
    sf::RenderWindow window1(sf::VideoMode(591,827), "Original Image");
    sf::RenderWindow window2(sf::VideoMode(591,827), "Encrypted Image");

    // Original Image texture and sprite
    sf::Texture bg;
    if (!bg.loadFromFile(original_file)) {
        cout << "Error loading image\n";
    }

    sf::Sprite original_image;
    original_image.setTexture(bg);
    
    sf::Image image;
    image.loadFromFile(original_file);

    transform(image, &fibLfsr);

    /* Save new Image to File */
    if(!image.saveToFile(encryption_file)){
        cout << "Error saving the image\n";
    }

    /* Encrypted Image Texture and Sprite */
    sf::Texture image_encryption;
    image_encryption.loadFromFile(encryption_file);

    sf::Sprite image_bg_encryption;
    image_bg_encryption.setTexture(image_encryption);

    while (window1.isOpen() && window2.isOpen() ) {

        sf::Event event1;
        while (window1.pollEvent(event1)) {
            if (event1.type == sf::Event::Closed)
                window1.close();
        }

        while (window2.pollEvent(event1)) {
            if (event1.type == sf::Event::Closed)
                window2.close();
        }

        window1.clear();
        window1.draw(original_image);
        window1.display();

        window2.clear();
        window2.draw(image_bg_encryption);
        window2.display();
    }

    return 0;
}


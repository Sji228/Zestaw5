//KRYKUN SERHII GRUPA 1 04.07.2024
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

class Canvas {
public:
    virtual ~Canvas() {}
    virtual void drawPixel(int x, int y, char symbol) = 0;
    virtual void render(const std::string &outputFile) = 0;
};

class ASCIICanvas : public Canvas {
private:
    int width, height;
    std::vector<std::vector<char>> pixels;

public:
    ASCIICanvas(int w, int h) : width(w), height(h), pixels(h, std::vector<char>(w, ' ')) {}

    void drawPixel(int x, int y, char symbol) override {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            pixels[y][x] = symbol;
        }
    }

    void render(const std::string &outputFile) override {
        std::ofstream outFile(outputFile);
        if (outFile.is_open()) {
            outFile << "|";
            for (int i = 0; i < width; ++i) outFile << "=";
            outFile << "|" << std::endl;

            for (int y = 0; y < height; ++y) {
                outFile << "|";
                for (int x = 0; x < width; ++x) {
                    outFile << pixels[y][x];
                }
                outFile << "|" << std::endl;
            }

            outFile << "|";
            for (int i = 0; i < width; ++i) outFile << "=";
            outFile << "|" << std::endl;

            outFile.close();
        }
    }
};

class Figure {
public:
    virtual ~Figure() {}
    virtual void draw(Canvas &canvas) = 0;
};

class Circle : public Figure {
private:
    int centerX, centerY, radius;
    char symbol;

public:
    Circle(int x, int y, int r, char s) : centerX(x), centerY(y), radius(r), symbol(s) {}

    void draw(Canvas &canvas) override {
        for (int y = -radius; y <= radius; ++y) {
            for (int x = -radius; x <= radius; ++x) {
                if (x * x + y * y <= radius * radius) {
                    canvas.drawPixel(centerX + x, centerY + y, symbol);
                }
            }
        }
    }
};

class Rectangle : public Figure {
protected:
    int x, y, width, height;
    char symbol;

public:
    Rectangle(int x, int y, int w, int h, char s) : x(x), y(y), width(w), height(h), symbol(s) {}

    void draw(Canvas &canvas) override {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                canvas.drawPixel(x + j, y + i, symbol);
            }
        }
    }
};

class Square : public Rectangle {
public:
    Square(int x, int y, int side, char s) : Rectangle(x, y, side, side, s) {}
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <config file>" << std::endl;
        return 1;
    }

    std::ifstream configFile(argv[1]);
    if (!configFile.is_open()) {
        std::cerr << "Unable to open config file" << std::endl;
        return 1;
    }

    int canvasWidth, canvasHeight;
    std::string outputFile;
    char emptySymbol;
    std::vector<Figure*> figures;

    configFile >> canvasWidth >> canvasHeight;
    configFile >> outputFile;
    configFile >> emptySymbol;

    ASCIICanvas canvas(canvasWidth, canvasHeight);

    std::string figureType;
    while (configFile >> figureType) {
        if (figureType == "Circle") {
            int x, y, radius;
            char symbol;
            configFile >> x >> y >> radius >> symbol;
            figures.push_back(new Circle(x, y, radius, symbol));
        } else if (figureType == "Rectangle") {
            int x, y, width, height;
            char symbol;
            configFile >> x >> y >> width >> height >> symbol;
            figures.push_back(new Rectangle(x, y, width, height, symbol));
        } else if (figureType == "Square") {
            int x, y, side;
            char symbol;
            configFile >> x >> y >> side >> symbol;
            figures.push_back(new Square(x, y, side, symbol));
        }
    }

    for (Figure* figure : figures) {
        figure->draw(canvas);
    }

    canvas.render(outputFile);

    for (Figure* figure : figures) {
        delete figure;
    }

    return 0;
}


#include "tgaimage.h"
#include "model.h"
#include "geometry.hpp"
#include <limits>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor green = TGAColor(  0, 255,   0, 255);
const TGAColor red   = TGAColor(255,   0,   0, 255);
const TGAColor blue  = TGAColor(  0,   0, 255, 255);

void rasterize(Vec2i p0, Vec2i p1, TGAImage &image, TGAColor color, int *ybuffer) {
    if (p0.x > p1.x) std::swap(p0, p1);
    for (int x = p0.x; x <= p1.x; x++) {
        float a = (x - p0.x) / static_cast<float>(p1.x - p0.x);
        int y = static_cast<int>((p1.y - p0.y)*a + p0.y);
        if (ybuffer[x] < y) {
            ybuffer[x] = y;
            image.set(x, 0, color);
        }
    }
}

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    bool steep = false;
    if (std::abs(x0-x1) < std::abs(y0-y1)) {
        std::swap(x0,y0);
        std::swap(x1,y1);
        steep = true;
    }

    if (x0 > x1) {
        std::swap(x0,x1);
        std::swap(y0,y1);
    }
    int dx = x1-x0;
    int dy = y1-y0;
    int derror2 = std::abs(dy)*2;
    int error2 = 0;
    int y = y0;
    for (int x = x0; x <= x1; x++) {
        if (steep) {
            image.set(y,x,color);
        } else {
            image.set(x,y,color);
        }
        error2 += derror2;

        if (error2 > dx) {
            y += (y1 > y0 ? 1 : -1);
            error2 -= dx*2;
        }
    }
}

void line(Vec2i v1, Vec2i v2, TGAImage &image, TGAColor color) {
    int x0, x1, y0, y1;
    x0 = v1.x; y0 = v1.y;
    x1 = v2.x; y1 = v2.y;
    line(x0, y0, x1, y1, image, color);
}

void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color) {
    if (t0.y==t1.y && t0.y==t2.y) return;
    if (t0.y > t1.y) std::swap(t0, t1);
    if (t1.y > t2.y) std::swap(t1, t2);
    if (t0.y > t1.y) std::swap(t0, t1);
    int l02 = t2.y - t0.y;
    int l01 = t1.y - t0.y;
    int l12 = t2.y - t1.y;

    for (int i = 0; i < l02; i++) {
        bool second_half = i > l01 || l01 == 0;
        float alpha = static_cast<float>(i)/l02;
        float beta = second_half ? static_cast<float>(i - l01)/l12
                                 : static_cast<float>(i)/l01;
        Vec2i A = t0 + (t2 - t0) * alpha;
        Vec2i B = second_half ? t1 + (t2 - t1) * beta
                              : t0 + (t1 - t0) * beta;

        if (A.x > B.x) std::swap(A, B);
        for (int j = A.x; j <= B.x; j++ ) {
            image.set(j, t0.y + i, color);
        }
    }
}

int main(int argc, char** argv) {
    int width  = 900;
    int height = 900;
    TGAImage image(width, height, TGAImage::RGB);
    Model m;
    m.readModel("../african_head.obj");
    Vec3f light_dir = {0, 0, -1};
    for (size_t i=0; i < m.sizeFace(); i++) {
        Face face = m.face(i);
        Vec2i screen_coords[3];
        Vec3f world_coords[3];
        for (size_t j=0; j<3; j++) {
            Vec3f v = m.getVertex(face[j]-1);
            screen_coords[j] = Vec2i((v.x+1.)*width/2., (v.y+1.)*height/2.);
            world_coords[j]  = v;
        }
        Vec3f n = (world_coords[2]-world_coords[0])^(world_coords[1]-world_coords[0]);
        n.normalize();
        float intensity = n*light_dir;
        if (intensity>0) {
            triangle(screen_coords[0], screen_coords[1], screen_coords[2], image, TGAColor(intensity*255, intensity*255, intensity*255, 255));
        }
    }

//    {
//        TGAImage scene(width, height, TGAImage::RGB);

//        // scene "2d mesh"
//        line(Vec2i(20, 34),   Vec2i(744, 400), scene, red);
//        line(Vec2i(120, 434), Vec2i(444, 400), scene, green);
//        line(Vec2i(330, 463), Vec2i(594, 200), scene, blue);

//        // screen line
//        line(Vec2i(10, 10), Vec2i(790, 10), scene, white);

//        scene.flip_vertically(); // i want to have the origin at the left bottom corner of the image
//        scene.write_tga_file("scene.tga");
//    }

//    TGAImage render(width, 16, TGAImage::RGB);
//    int ybuffer[width];
//    for (int i=0; i<width; i++) {
//        ybuffer[i] = std::numeric_limits<int>::min();
//    }
//    rasterize(Vec2i(20, 34),   Vec2i(744, 400), render, red,   ybuffer);
//    rasterize(Vec2i(120, 434), Vec2i(444, 400), render, green, ybuffer);
//    rasterize(Vec2i(330, 463), Vec2i(594, 200), render, blue,  ybuffer);
//    render.write_tga_file("buffer.tga");


//    int zbuffer[width*height];
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
	return 0;
}

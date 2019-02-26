#include "tgaimage.h"
#include "model.h"
#include "geometry.hpp"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor green = TGAColor(  0, 255,   0, 255);
const TGAColor red   = TGAColor(255,   0,   0, 255);

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
    if (t0.y > t1.y) std::swap(t0, t1);
    if (t1.y > t2.y) std::swap(t1, t2);
    if (t0.y > t1.y) std::swap(t0, t1);
    float tg1 = 0.0f;
    float tg2 = 0.0f;
    float tg3 = 0.0f;
    if (t0.y != t1.y)
        tg1 = (t1.x - t0.x)/static_cast<float>(t1.y - t0.y);
    tg2 = (t2.x - t0.x)/static_cast<float>(t2.y - t0.y);

    for (int i = t0.y; i <= t1.y; i++) {
        float dx1 = t0.x + (i-t0.y)*tg1 + 0.5f;
        float dx2 = t0.x + (i-t0.y)*tg2 + 0.5f;
        if (dx1 > dx2) std::swap(dx1, dx2);
        for (int j = static_cast<int>(dx1);
             j <= static_cast<int>(dx2); j++ ) {
            image.set(j, i, color);
        }
    }
    if (t1.y != t2.y)
        tg3 = (t2.x - t1.x)/static_cast<float>(t2.y - t1.y);
    for (int i = t1.y; i <= t2.y; i++) {
        float dx1 = t1.x + (i-t1.y)*tg3 + 0.5f;
        float dx2 = t0.x + (i-t0.y)*tg2 + 0.5f;
        if (dx1 > dx2) std::swap(dx1, dx2);
        for (int j = static_cast<int>(dx1);
             j <= static_cast<int>(dx2); j++ ) {
            image.set(j, i, color);
        }
    }
    line(t0, t1, image, color);
    line(t1, t2, image, color);
    line(t2, t0, image, color);
}

int main(int argc, char** argv) {
    int width = 600;
    int height = 600;
    TGAImage image(width, height, TGAImage::RGB);

    //Vec2i t0[3] = {Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80)};
    Vec2i t0[3] = {Vec2i(10, 70),   Vec2i(50, 70),  Vec2i(70, 70)};
    Vec2i t1[3] = {Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180)};
    Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)};
//    triangle(t0[0], t0[1], t0[2], image, white);
//    triangle(t1[0], t1[1], t1[2], image, white);
//    triangle(t2[0], t2[1], t2[2], image, white);

    Model m;
    m.readModel("../african_head.obj");
//    for (size_t i = 0; i < m.sizeFace(); i++) {
//        std::vector<int> f = m.face(i);
//        Vec2i wc[3] = {{0,0}, {0,0}, {0,0}};
//        for (size_t j = 0; j < 3; j++) {
//            Point3D v = m.getVertex(f[j]-1);
//            wc[j] = Vec2i((v.x+1.)*width/2., (v.y+1.)*height/2.);
//        }
//        triangle(wc[0], wc[1], wc[2], image, TGAColor(rand()%255, rand()%255, rand()%255, 255));
//    }
//    std::vector<Triangle> triangles = m.getTriangles(z);
//    for (auto tr : triangles) {
//        Vec2i t0 = Vec2i((tr.p1.x+1.)*width/2., (tr.p1.y+1.)*height/2.);
//        Vec2i t1 = Vec2i((tr.p2.x+1.)*width/2., (tr.p2.y+1.)*height/2.);
//        Vec2i t2 = Vec2i((tr.p3.x+1.)*width/2., (tr.p3.y+1.)*height/2.);
//        triangle(t0, t1, t2, image, TGAColor(rand()%255, rand()%255, rand()%255, 255));
//    }
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
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}

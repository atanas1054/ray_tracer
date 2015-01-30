#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>
#include <rt/world.h>
#include <rt/renderer.h>
#include <rt/loaders/obj.h>
#include <rt/groups/bvh.h>
#include <rt/groups/simplegroup.h>
#include <rt/groups/kdtree.h>
#include <rt/groups/MotionBlur.h>
#include <rt/solids/sphere.h>
#include <rt/solids/quad.h>
#include <rt/solids/aabox.h>
#include <rt/solids/triangle.h>
#include <rt/solids/aabox.h>
#include <rt/solids/disc.h>
#include <rt/solids/infiniteplane.h>
#include <rt/primmod/instance.h>
#include <rt/cameras/perspective.h>
#include <rt/cameras/dofperspective.h>
#include <rt/integrators/casting.h>
#include <rt/integrators/castingdist.h>
#include <rt/integrators/recraytrace.h>
#include <rt/lights/pointlight.h>
#include <rt/lights/directional.h>
#include <rt/lights/projectivelight.h>
#include <rt/lights/arealight.h>
#include <rt/lights/spotlight.h>
#include <rt/materials/phong.h>
#include <rt/materials/lambertian.h>
#include <rt/materials/mirror.h>
#include <rt/materials/glass.h>
#include <rt/materials/fuzzymirror.h>
#include <rt/materials/flatmaterial.h>
#include <rt/textures/constant.h>
#include <rt/textures/imagetex.h>
#include <rt/textures/perlin.h>
#include <rt/primmod/bmap.h>
#include <rt/coordmappers/tmapper.h>
#include <iostream>
#include <time.h>

using namespace rt;



void rendering_competition() {
	
    Image img(800,600);
	
    BVH* scene = new BVH();
	BVH* cup = new BVH();
	BVH* sphere = new BVH();
	BVH* sphere1 = new BVH();
	BVH* chair_obj = new BVH();

	//BVH* sphere = new BVH();
	MotionBlur* chair = new MotionBlur();
	MotionBlur* sphere_ = new MotionBlur();
		
	loadOBJ(scene, "models/", "room.obj");
	loadOBJ(sphere, "models/", "sphere.obj");
	loadOBJ(sphere1, "models/", "sphere1.obj");
	loadOBJ(cup, "models/", "cup.obj");
	loadOBJ(chair_obj, "models/", "chair.obj");
	
	
	chair_obj->rebuildIndex();

	sphere->setMaterial(new MirrorMaterial(2.485, 3.433));
	sphere->rebuildIndex();

	Texture* blacktex1 = new ConstantTexture(RGBColor::rep(0.0f));
	Texture* whitetex1 = new ConstantTexture(RGBColor::rep(1.0f));

	sphere1->setMaterial(new LambertianMaterial(blacktex1, whitetex1));
	sphere1->rebuildIndex();

	cup->setMaterial(new LambertianMaterial(blacktex1, whitetex1));
	cup->rebuildIndex();


	chair->add(chair_obj);
	chair->translate(-Vector(1.33416f,-2.71494f,-0.12571f));
	chair->rotate(Point(1.33468f,-2.71482f,-0.12573f)-Point(1.04338f,-3.29067f,-0.12278f),-pi/9);
	chair->translate(Vector(1.33416f,-2.71494f,-0.12571f));

	Instance* inst1 = new Instance(chair_obj);
	inst1->translate(-Vector(1.33416f,-2.71494f,-0.12571f));
	inst1->rotate(Point(1.33468f,-2.71482f,-0.12573f)-Point(1.04338f,-3.29067f,-0.12278f),-pi/9);
	inst1->translate(Vector(1.33416f,-2.71494f,-0.12571f));


	sphere_->add(sphere1);
	sphere_->translate(Point(1.55016f,-2.11429f,1.13691f)-Point(1.99071f,-2.0549f,1.07969f));
	
	Instance* inst2 = new Instance(sphere1);
	inst2->translate(Point(1.55016f,-2.11429f,1.13691f)-Point(1.99071f,-2.0549f,1.07969f));
	

	//Bump map
	Texture* wt = new ConstantTexture(RGBColor::rep(1));
	Texture* bt = new ConstantTexture(RGBColor::rep(0));
	Texture* gt = new ImageTexture("models/wall1.png");
	Material* lambbrick = new LambertianMaterial(bt, gt);
	//multiply the points here to get smaller pattern
	Point* tri1 = new Point[3];
	tri1[0] = 2*Point(1,1,0);
	tri1[1] = 2*Point(1, 0, 0);
	tri1[2] = 2*Point(0, 0, 0);
	Point* tri2 = new Point[3];
	tri2[0] = 2*Point(1,1,0);
	tri2[1] = 2*Point(0, 0, 0);
	tri2[2] = 2*Point(0, 1, 0);
	//front wall
	CoordMapper* trimap1 = new TriangleMapper(tri1[0], tri1[1], tri1[2]);
	CoordMapper* trimap2 = new TriangleMapper(tri2[0], tri2[1], tri2[2]);
	Texture* bumpbrick = new ImageTexture("models/wall1.png");
	scene->add(new BumpMapper(
            new Triangle(Point(6.34551, 0.59627, -0.14699), Point(6.34551, 0.59627, 3.71617), Point(-0.83251, 0.59627, 3.71617), trimap1, lambbrick),
            bumpbrick, tri1[0], tri1[1], tri1[2], 0.05)
            );
	scene->add(new BumpMapper(
            new Triangle(Point(6.34551, 0.59627, -0.14699), Point(-0.83251, 0.59627, 3.71617), Point(-0.83251, 0.59627, -0.14699), trimap2, lambbrick),
            bumpbrick, tri2[0], tri2[1], tri2[2], 0.05)
            );
	//right wall
	scene->add(new BumpMapper(
            new Triangle(Point(6.04508, -7.59944, -0.15968), Point(6.04508, -7.59944, 3.70348), Point(6.04508, 0.94939, 3.70348), trimap1, lambbrick),
            bumpbrick, tri1[0], tri1[1], tri1[2], 0.05)
            );
	scene->add(new BumpMapper(
            new Triangle(Point(6.04508, -7.59944, -0.15968), Point(6.04508, 0.94939, 3.70348), Point(6.04508, 0.9494, -0.15968), trimap2, lambbrick),
            bumpbrick, tri2[0], tri2[1], tri2[2], 0.05)
            );

	//Perlin noise texture

	 PerlinTexture* perlinTex = new PerlinTexture(RGBColor(1.0f,1.0f,0.9f), RGBColor(0.5f,0.5f,1.0f));
     perlinTex->addOctave(0.5f, 5.0f);
     perlinTex->addOctave(0.25f, 10.0f);
     perlinTex->addOctave(0.125f, 20.0f);
     perlinTex->addOctave(0.125f, 40.0f);
     FlatMaterial* perlin = new FlatMaterial(perlinTex);
	
	 LambertianMaterial* lamb = new LambertianMaterial(new ConstantTexture(RGBColor::rep(0.0f)), perlinTex);

	//floor
	scene->add(new Quad(Point(-0.84819f,-7.32295f,-0.1205),Point(-0.84819f,1.19039f,-0.1205f)-Point(-0.84819f,-7.32295f,-0.1205f),Point(6.34768f,-7.32295f,-0.1205f)-Point(-0.84819f,-7.32295f,-0.1205f),nullptr,lamb));

	scene->add(sphere);
	scene->add(cup);
	scene->add(chair);
	scene->add(inst1);
	scene->add(inst2);
	scene->add(sphere_);
	

	clock_t start = clock();

	scene->rebuildIndex();

	std::cout << ((double) (clock() - start) / CLOCKS_PER_SEC) << " seconds to build the BVH" "\n";

    World world;
    world.scene = scene;

	ConstantTexture* lightsrctex = new ConstantTexture(RGBColor::rep(150000.0f*0.015f*0.01f));
	Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
	Material* lightsource = new LambertianMaterial(lightsrctex, lightsrctex);
	Disc* light = new Disc(Point(3.27691f, -2.57511f, 2.41388f),Vector(0,0,1) ,0.23, nullptr, lightsource);
	AreaLight als(light);
	scene->add(light);
	world.light.push_back(&als);
	//world.light.push_back(new ProjectiveLight(Point(3.18619f,-2.72447f,2.99402f),RGBColor::rep(150000.0f*0.007f*0.007f)));

	
	//world.light.push_back(new PointLight(Point(3.27691f, -2.57511f, 2.58388f),RGBColor::rep(150000.0f*0.007f*0.007f)));
	
	world.light.push_back(new PointLight(Point(5.40733f,-6.94448f,3.32905f),RGBColor::rep(150000.0f*0.013f*0.01f)));
	world.light.push_back(new PointLight(Point(0.03841f,-6.3863f, 3.15896f),RGBColor::rep(150000.0f*0.013f*0.01f)));

	world.light.push_back(new PointLight(Point(-0.21887f,-5.00706f, 2.22723f),RGBColor::rep(150000.0f*0.008f*0.01f)));


	//world.light.push_back(new SpotLight(Point(3.27691f, -2.57511f, 2.58388f), Vector(0, 0, -2.58388f),  pi/6, 6.0f, RGBColor::rep(150000.0f*0.011f*0.01f)));

	PerspectiveCamera cam1(Point(-0.44221f, -7.13732f, 3.16076f), Vector(0.612599f,0.80506f, -0.3550f), Vector(0.13844f,0.26561f,0.95408f), pi/3.5, pi/2.5);
	RecursiveRayTracingIntegrator integrator(&world);
	//RayCastingIntegrator integrator(&world);
    //RayCastingDistIntegrator integrator(&world, RGBColor(1.0f,0.2f,0.0f), 4.0f, RGBColor(0.2f,1.0f,0.0f), 12.0f);
	
	clock_t start1 = clock();
    Renderer engine1(&cam1, &integrator);
	engine1.setSamples(1);
	engine1.render(img);
    img.writePNG("1-sample.png");

	std::cout << ((double) (clock() - start1) / CLOCKS_PER_SEC) << " seconds to render" "\n";
	int kkk;
	std::cin >> kkk;


}

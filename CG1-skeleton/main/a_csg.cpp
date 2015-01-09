
#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>
#include <rt/world.h>
#include <rt/renderer.h>
#include <rt/cameras/perspective.h>
#include <rt/lights/pointlight.h>
#include <rt/textures/constant.h>
#include <rt/materials/lambertian.h>
#include <rt/groups/simplegroup.h>
#include <rt/groups/csg.h>
#include <rt/groups/csgsolids/csgsphere.h>
#include <rt/groups/csgsolids/csgaabox.h>
#include <rt/solids/sphere.h>
#include <rt/solids/quad.h>
#include <rt/integrators/raytrace.h>
#include <rt/integrators/casting.h>
#include <rt/integrators/castingdist.h>
#include <rt/integrators/recraytrace.h>
#include <rt/coordmappers/world.h>

using namespace rt;
/*
void a_csg(){

	Texture* redtex = new ConstantTexture(RGBColor(.7f,0.f,0.f));
	Texture* greentex = new ConstantTexture(RGBColor(0.f,.7f,0.f));
	Texture* bluetex = new ConstantTexture(RGBColor(0.f,0.f,0.7f));
	Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
	Texture* whitetex = new ConstantTexture(RGBColor::rep(1.0f));
	Material** materials = new Material*[3];
	materials[0] = new LambertianMaterial(blacktex, bluetex);
	materials[1] = new LambertianMaterial(blacktex, redtex);
	materials[2] = new LambertianMaterial(blacktex, greentex);

	Image img(400, 400);
	World world;
	SimpleGroup* scene = new SimpleGroup();
	world.scene = scene;
	PerspectiveCamera cam(Point(0.0f, 0.0f, -75.0f), Vector(0, 0, 1), Vector(0, 1, 0), 0.686f, 0.686f);

	scene->add(new Sphere(Point(0.0f, 0.0f, 0.0f), 10, nullptr, materials[1]));

	world.light.push_back(new PointLight(Point(50.0f,50.0f,0.0f), RGBColor::rep(10000)));

	world.light.push_back(new PointLight(Point(-50.0f,50.0f,0.0f), RGBColor::rep(10000)));

	RayTracingIntegrator integrator(&world);
	//RayCastingIntegrator integrator(&world);

	Renderer engine(&cam, &integrator);
	engine.render(img);
	img.writePNG("a7-csg.png");
}*/

Texture* redtex;
Texture* greentex;
Texture* bluetex;
Texture* blacktex;
Texture* whitetex;

void initTextures() {
    redtex = new ConstantTexture(RGBColor(.7f,0.f,0.f));
    greentex = new ConstantTexture(RGBColor(0.f,.7f,0.f));
    bluetex = new ConstantTexture(RGBColor(0.f,0.f,0.7f));
    blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    whitetex = new ConstantTexture(RGBColor::rep(1.0f));
}

void a7prepMaterialsCSG(Material** materials) {
    materials[0] = new LambertianMaterial(blacktex, whitetex);
    materials[1] = new LambertianMaterial(blacktex, redtex);
    materials[2] = new LambertianMaterial(blacktex, greentex);

    materials[3] = new LambertianMaterial(blacktex, whitetex);

    materials[4] = new LambertianMaterial(blacktex, whitetex);
}

void a7renderCornellboxCSG(float scale, const char* filename, Material** materials) {
    Image img(400, 400);
    World world;
    SimpleGroup* scene = new SimpleGroup();
    world.scene = scene;

    PerspectiveCamera cam(Point(278*scale, 273*scale, -800*scale), Vector(0, 0, 1), Vector(0, 1, 0), 0.686f, 0.686f);


    Material* grey = materials[0];
    Material* leftWallMaterial = materials[1];
    Material* rightWallMaterial = materials[2];
    
    Material* sphereMaterial = materials[3];
    Material* floorMaterial = materials[4];

    scene->add(new Quad(Point(000.f,000.f,000.f)*scale, Vector(550.f,000.f,000.f)*scale, Vector(000.f,000.f,560.f)*scale, nullptr, floorMaterial)); //floor
    scene->add(new Quad(Point(550.f,550.f,000.f)*scale, Vector(-550.f,000.f,000.f)*scale, Vector(000.f,000.f,560.f)*scale, nullptr, grey)); //ceiling
    scene->add(new Quad(Point(000.f,000.f,560.f)*scale, Vector(550.f,000.f,000.f)*scale, Vector(000.f,550.f,000.f)*scale, nullptr, grey)); //back wall
    scene->add(new Quad(Point(000.f,000.f,000.f)*scale, Vector(000.f,000.f,560.f)*scale, Vector(000.f,550.f,000.f)*scale, nullptr, rightWallMaterial)); //right wall
    scene->add(new Quad(Point(550.f,550.f,000.f)*scale, Vector(000.f,000.f,560.f)*scale, Vector(000.f,-550.f,000.f)*scale, nullptr, leftWallMaterial)); //left wall

    //scene->add(new Sphere(Point(150.0f, 100.0f, 150.0f)*scale, 99.0f*scale, nullptr, sphereMaterial));

	WorldMapper* wm = new WorldMapper(Float4::rep(1));
	scene->add(
		new CSG(
			CSG::CombineType::DIFFERENCE,
			new CSG(
				CSG::CombineType::UNION,
				new CSGAABox(Point(300.0f, 180.0f, 100.0f)*scale, Point(100.0f, 0.0f, 300.0f)*scale, wm, sphereMaterial),
				new CSG(CSG::CombineType::INTERSECT, 
					new CSGSphere(Point(150.0f, 100.0f, 150.0f)*scale, 119.0f*scale, wm, sphereMaterial),
					new CSGSphere(Point(250.0f, 100.0f, 120.0f)*scale, 119.0f*scale, wm, sphereMaterial),
					nullptr, nullptr
				),
				nullptr, nullptr
			),
			new CSGSphere(Point(270.0f, 140.0f, 80.0f)*scale, 70.0f*scale, wm, sphereMaterial),
			wm, sphereMaterial
		)
	);

    //point light
    world.light.push_back(new PointLight(Point((278)*scale,529.99f*scale,(279.5f)*scale),RGBColor::rep(150000.0f*scale*scale)));
    world.light.push_back(new PointLight(Point((298)*scale,179.99f*scale,(-159.5f)*scale),RGBColor::rep(50000.0f*scale*scale)));

    world.light.push_back(new PointLight(Point(490*scale,159.99f*scale,109.5f*scale),RGBColor(40000.0f*scale*scale,0,0)));
    world.light.push_back(new PointLight(Point(40*scale,159.99f*scale,149.5f*scale),RGBColor(5000.0f*scale*scale,30000.0f*scale*scale,5000.0f*scale*scale)));

    RayTracingIntegrator integrator(&world);
	//RecursiveRayTracingIntegrator integrator(&world);
	//RayCastingIntegrator integrator(&world);
	//RayCastingDistIntegrator integrator(&world, RGBColor(1.0f,0.2f,0.0f), 0.4f, RGBColor(0.2f,1.0f,0.0f), 2.0f);

    Renderer engine(&cam, &integrator);
    engine.render(img);
    img.writePNG(filename);
}

void a_csg(){

	Material** materials = new Material*[5];
    initTextures();
    a7prepMaterialsCSG(materials);
    a7renderCornellboxCSG(0.001f, "a7-csg.png", materials);
    delete [] materials;
}